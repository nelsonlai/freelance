// SPDX-License-Identifier: GPL-2.0
/*
 * ctut_char.c - A beginner-friendly character device driver tutorial.
 *
 * This is intentionally small and heavily commented.
 *
 * What you get when you load this module:
 *   - A single character device with an auto-created /dev node:
 *       /dev/ctut0
 *
 * What it supports:
 *   - open()/close()
 *   - read()/write() from/to a fixed-size in-kernel buffer
 *   - llseek() to change the file offset
 *   - ioctl() to clear the buffer
 *
 * What it does NOT try to teach:
 *   - interrupt handling, DMA, real hardware I/O
 *   - advanced blocking I/O, poll/select
 *   - multi-device instantiation and hotplug
 *
 * Build this as an out-of-tree module using the Makefile in this folder.
 */

#include <linux/module.h>      /* Core header for loading LKMs into the kernel */
#include <linux/init.h>        /* Macros used to mark up functions e.g. __init */
#include <linux/fs.h>          /* alloc_chrdev_region(), struct file_operations */
#include <linux/cdev.h>        /* struct cdev, cdev_init(), cdev_add() */
#include <linux/device.h>      /* class_create(), device_create() */
#include <linux/uaccess.h>     /* copy_to_user(), copy_from_user() */
#include <linux/mutex.h>       /* mutex, mutex_lock(), mutex_unlock() */
#include <linux/slab.h>        /* kzalloc(), kfree() */
#include <linux/ioctl.h>       /* _IO() family */
#include <linux/errno.h>       /* Error codes */

/*
 * Device naming:
 * - The class name shows up under /sys/class/<class_name>/
 * - The device node name becomes /dev/<device_name> (typically created by udev)
 */
#define CTUT_CLASS_NAME  "ctut"
#define CTUT_DEV_NAME    "ctut0"

/*
 * A simple fixed-size buffer for demonstration.
 * In real drivers, data often comes from hardware, not a memory buffer.
 */
#define CTUT_BUF_SIZE    4096

/*
 * ioctl commands
 *
 * ioctl is a generic “control channel” for device-specific operations.
 * The kernel uses command numbers; userspace passes them via ioctl(fd, cmd, arg).
 *
 * For this tutorial, we only implement a “clear buffer” command that takes
 * no argument.
 */
#define CTUT_IOCTL_MAGIC  'c'
#define CTUT_IOCTL_CLEAR  _IO(CTUT_IOCTL_MAGIC, 0x01)

/*
 * Per-device state.
 *
 * Even though this tutorial registers only ONE device instance, writing code as
 * if multiple devices could exist keeps the structure realistic.
 */
struct ctut_dev {
	/* Char device registration */
	dev_t devt;            /* Encodes (major, minor) */
	struct cdev cdev;      /* Connects devt to file_operations */

	/* Auto /dev node plumbing */
	struct class *class;   /* /sys/class/ctut/ */
	struct device *device; /* /sys/class/ctut/ctut0 and /dev/ctut0 */

	/* “Device data” for read/write */
	char *buf;             /* Kernel memory holding bytes */
	size_t data_len;       /* How many bytes currently valid in buf */
	struct mutex lock;     /* Protects buf + data_len */
};

static struct ctut_dev g_dev;

/*
 * open() is called when userspace opens /dev/ctut0.
 *
 * - inode identifies the device file on disk (and includes the device number).
 * - file is the “open file description” for this open instance.
 *
 * Common pattern:
 * - Use container_of(inode->i_cdev, ...) to find your device struct.
 * - Store a pointer in file->private_data for later ops.
 */
static int ctut_open(struct inode *inode, struct file *file)
{
	struct ctut_dev *dev = container_of(inode->i_cdev, struct ctut_dev, cdev);

	file->private_data = dev;

	/* It’s OK to log on open/close; avoid spamming per-byte operations. */
	pr_info("ctut: open\n");
	return 0;
}

/*
 * release() is called on close(2) when the last reference to the file is gone.
 */
static int ctut_release(struct inode *inode, struct file *file)
{
	(void)inode;
	(void)file;
	pr_info("ctut: release\n");
	return 0;
}

/*
 * read() should copy data from kernel space into userspace.
 *
 * Userspace passes:
 * - buf: userspace pointer where we should place the bytes
 * - count: max bytes to read
 * - *ppos: current file offset; we should update it
 *
 * Important:
 * - NEVER directly dereference userspace pointers in the kernel.
 * - Use copy_to_user().
 *
 * Return value:
 * - >= 0: number of bytes actually read (0 means EOF)
 * - < 0: negative errno (e.g. -EFAULT, -ERESTARTSYS)
 */
static ssize_t ctut_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
	struct ctut_dev *dev = file->private_data;
	ssize_t ret;
	size_t avail;
	size_t to_copy;
	loff_t pos;

	/* Defensive: treat negative offsets as invalid. */
	if (*ppos < 0)
		return -EINVAL;

	pos = *ppos;

	/*
	 * We guard the buffer with a mutex because multiple processes can
	 * concurrently call read/write (or same process via threads).
	 */
	if (mutex_lock_interruptible(&dev->lock))
		return -ERESTARTSYS;

	/*
	 * EOF behavior:
	 * If file offset is at/after current data length, read returns 0.
	 */
	if (pos >= dev->data_len) {
		ret = 0;
		goto out_unlock;
	}

	avail = dev->data_len - pos;
	to_copy = min(count, avail);

	if (copy_to_user(buf, dev->buf + pos, to_copy)) {
		ret = -EFAULT;
		goto out_unlock;
	}

	*ppos = pos + to_copy;
	ret = (ssize_t)to_copy;

out_unlock:
	mutex_unlock(&dev->lock);
	return ret;
}

/*
 * write() should copy data from userspace into kernel space.
 *
 * This tutorial uses a fixed-size buffer. We write starting at the current
 * file offset. If you write beyond the end, we clamp to the buffer size.
 */
static ssize_t ctut_write(struct file *file, const char __user *buf,
			  size_t count, loff_t *ppos)
{
	struct ctut_dev *dev = file->private_data;
	ssize_t ret;
	loff_t pos;
	size_t space;
	size_t to_copy;
	size_t new_end;

	if (*ppos < 0)
		return -EINVAL;

	pos = *ppos;

	if (mutex_lock_interruptible(&dev->lock))
		return -ERESTARTSYS;

	/* If offset is already beyond our buffer, we can’t store anything. */
	if (pos >= CTUT_BUF_SIZE) {
		ret = -ENOSPC;
		goto out_unlock;
	}

	space = CTUT_BUF_SIZE - pos;
	to_copy = min(count, space);

	if (copy_from_user(dev->buf + pos, buf, to_copy)) {
		ret = -EFAULT;
		goto out_unlock;
	}

	/* Update “file length” (data_len) if we extended beyond previous end. */
	new_end = pos + to_copy;
	if (new_end > dev->data_len)
		dev->data_len = new_end;

	*ppos = pos + to_copy;
	ret = (ssize_t)to_copy;

out_unlock:
	mutex_unlock(&dev->lock);
	return ret;
}

/*
 * llseek() implements lseek(2).
 *
 * The VFS provides a helper: fixed_size_llseek().
 * It bounds the file position to [0, max].
 *
 * For our “RAM-backed file” device, max is CTUT_BUF_SIZE.
 */
static loff_t ctut_llseek(struct file *file, loff_t off, int whence)
{
	return fixed_size_llseek(file, off, whence, CTUT_BUF_SIZE);
}

/*
 * unlocked_ioctl() handles ioctl(2) without taking the Big Kernel Lock (BKL).
 *
 * In modern kernels, .unlocked_ioctl is the standard ioctl callback.
 * (There is also .compat_ioctl for 32-bit compat on 64-bit kernels if needed.)
 */
static long ctut_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ctut_dev *dev = file->private_data;

	(void)arg; /* unused in this tutorial */

	/*
	 * Validate magic so random ioctl numbers don’t accidentally match.
	 */
	if (_IOC_TYPE(cmd) != CTUT_IOCTL_MAGIC)
		return -ENOTTY;

	switch (cmd) {
	case CTUT_IOCTL_CLEAR:
		if (mutex_lock_interruptible(&dev->lock))
			return -ERESTARTSYS;
		memset(dev->buf, 0, CTUT_BUF_SIZE);
		dev->data_len = 0;
		mutex_unlock(&dev->lock);
		return 0;
	default:
		return -ENOTTY;
	}
}

/*
 * file_operations: this is the “jump table” the VFS uses to call your driver.
 *
 * Note: .owner helps prevent the module from being unloaded while in use.
 */
static const struct file_operations ctut_fops = {
	.owner          = THIS_MODULE,
	.open           = ctut_open,
	.release        = ctut_release,
	.read           = ctut_read,
	.write          = ctut_write,
	.llseek         = ctut_llseek,
	.unlocked_ioctl = ctut_ioctl,
};

/*
 * Module init/exit
 *
 * init:
 *  - allocate a device number (major+minor)
 *  - init and add cdev (hooks fops to the device number)
 *  - create a class and device (for /dev node creation)
 *  - allocate the internal buffer
 *
 * exit:
 *  - destroy device + class
 *  - delete cdev
 *  - unregister device numbers
 *  - free memory
 */
static int __init ctut_init(void)
{
	int rc;

	memset(&g_dev, 0, sizeof(g_dev));

	mutex_init(&g_dev.lock);

	/*
	 * Step 1: allocate a device number range.
	 *
	 * We request 1 minor number.
	 * On success, g_dev.devt contains both major and minor encoded.
	 */
	rc = alloc_chrdev_region(&g_dev.devt, 0, 1, "ctut_char");
	if (rc) {
		pr_err("ctut: alloc_chrdev_region failed: %d\n", rc);
		return rc;
	}

	/*
	 * Step 2: init and add a cdev, which binds our fops to this dev number.
	 */
	cdev_init(&g_dev.cdev, &ctut_fops);
	g_dev.cdev.owner = THIS_MODULE;

	rc = cdev_add(&g_dev.cdev, g_dev.devt, 1);
	if (rc) {
		pr_err("ctut: cdev_add failed: %d\n", rc);
		goto err_unregister;
	}

	/*
	 * Step 3: create a class and device so that /dev/ctut0 appears.
	 *
	 * On systems with udev, device_create() triggers udev to create /dev node.
	 */
	g_dev.class = class_create(CTUT_CLASS_NAME);
	if (IS_ERR(g_dev.class)) {
		rc = PTR_ERR(g_dev.class);
		pr_err("ctut: class_create failed: %d\n", rc);
		g_dev.class = NULL;
		goto err_cdev_del;
	}

	g_dev.device = device_create(g_dev.class, NULL, g_dev.devt, NULL, CTUT_DEV_NAME);
	if (IS_ERR(g_dev.device)) {
		rc = PTR_ERR(g_dev.device);
		pr_err("ctut: device_create failed: %d\n", rc);
		g_dev.device = NULL;
		goto err_class_destroy;
	}

	/*
	 * Step 4: allocate our internal buffer.
	 *
	 * kzalloc() gives zeroed memory; this makes the device start “empty”.
	 */
	g_dev.buf = kzalloc(CTUT_BUF_SIZE, GFP_KERNEL);
	if (!g_dev.buf) {
		rc = -ENOMEM;
		pr_err("ctut: kzalloc failed\n");
		goto err_device_destroy;
	}

	g_dev.data_len = 0;

	pr_info("ctut: loaded. dev=%u:%u (/dev/%s)\n",
		MAJOR(g_dev.devt), MINOR(g_dev.devt), CTUT_DEV_NAME);
	return 0;

err_device_destroy:
	if (g_dev.device)
		device_destroy(g_dev.class, g_dev.devt);
err_class_destroy:
	if (g_dev.class)
		class_destroy(g_dev.class);
err_cdev_del:
	cdev_del(&g_dev.cdev);
err_unregister:
	unregister_chrdev_region(g_dev.devt, 1);
	return rc;
}

static void __exit ctut_exit(void)
{
	/* Reverse order of init: free resources safely. */
	kfree(g_dev.buf);
	g_dev.buf = NULL;

	if (g_dev.device)
		device_destroy(g_dev.class, g_dev.devt);
	g_dev.device = NULL;

	if (g_dev.class)
		class_destroy(g_dev.class);
	g_dev.class = NULL;

	cdev_del(&g_dev.cdev);
	unregister_chrdev_region(g_dev.devt, 1);

	pr_info("ctut: unloaded\n");
}

module_init(ctut_init);
module_exit(ctut_exit);

MODULE_AUTHOR("Beginner tutorial (generated for learning)");
MODULE_DESCRIPTION("ctut: beginner character device driver tutorial");
MODULE_LICENSE("GPL");

