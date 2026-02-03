// SPDX-License-Identifier: GPL-2.0
/*
 * ctut_kfifo.c - Character device tutorial: ring buffer using kfifo.
 *
 * This is the “stream” version of the tutorial driver.
 *
 * Key differences vs ctut_char.c (file-like buffer):
 * - Uses a FIFO (first-in-first-out) ring buffer.
 * - The device is NON-SEEKABLE: llseek returns -ESPIPE (like a pipe).
 * - Reads consume bytes from the FIFO; writes append bytes into the FIFO.
 * - Supports blocking behavior:
 *     - read() blocks when FIFO empty (unless O_NONBLOCK)
 *     - write() blocks when FIFO full  (unless O_NONBLOCK)
 * - Supports poll()/select()/epoll() readiness.
 *
 * Why kfifo?
 * - The kernel provides kfifo helpers to implement ring buffers safely and
 *   efficiently without re-inventing the wrap-around logic.
 *
 * Build:
 *   make            # builds ctut_kfifo.ko (and ctut_char.ko)
 *
 * Load:
 *   sudo insmod ctut_kfifo.ko
 *   ls -l /dev/ctut_fifo0
 *
 * Test:
 *   make user_test
 *   ./user_test /dev/ctut_fifo0
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/kfifo.h>       /* kfifo_alloc, kfifo_to_user, kfifo_from_user */
#include <linux/wait.h>        /* wait queues for blocking read/write */
#include <linux/poll.h>        /* poll/select support */
#include <linux/ioctl.h>
#include <linux/errno.h>

/*
 * Make the device names DIFFERENT from ctut_char.c so both modules can exist
 * in the same system (you still shouldn’t load both if you don’t need them).
 */
#define CTUT_FIFO_CLASS_NAME  "ctut_fifo"
#define CTUT_FIFO_DEV_NAME    "ctut_fifo0"

/*
 * FIFO capacity.
 *
 * kfifo works best when the size is a power of 2, but it can handle other sizes.
 * Using a power of 2 keeps the mental model simple for beginners.
 */
#define CTUT_FIFO_SIZE        4096

/* ioctl: clear/reset the FIFO (discard all buffered bytes). */
#define CTUT_FIFO_IOCTL_MAGIC  'f'
#define CTUT_FIFO_IOCTL_CLEAR  _IO(CTUT_FIFO_IOCTL_MAGIC, 0x01)

struct ctut_fifo_dev {
	dev_t devt;
	struct cdev cdev;
	struct class *class;
	struct device *device;

	/*
	 * The ring buffer.
	 *
	 * Internally, kfifo maintains head/tail indices and wraps automatically.
	 * Think of it as a circular array of bytes.
	 */
	struct kfifo fifo;

	/*
	 * Concurrency & blocking:
	 *
	 * - Multiple threads/processes can read/write simultaneously.
	 * - We use a mutex to protect FIFO operations (kfifo itself is NOT magically
	 *   safe for all concurrent access patterns unless you use special APIs).
	 *
	 * - For “blocking I/O”, we need wait queues:
	 *   - readers wait until the FIFO becomes non-empty
	 *   - writers wait until the FIFO has space
	 */
	struct mutex lock;
	wait_queue_head_t readq;
	wait_queue_head_t writeq;
};

static struct ctut_fifo_dev g_dev;

static int ctut_fifo_open(struct inode *inode, struct file *file)
{
	struct ctut_fifo_dev *dev = container_of(inode->i_cdev, struct ctut_fifo_dev, cdev);

	file->private_data = dev;
	pr_info("ctut_fifo: open\n");
	return 0;
}

static int ctut_fifo_release(struct inode *inode, struct file *file)
{
	(void)inode;
	(void)file;
	pr_info("ctut_fifo: release\n");
	return 0;
}

/*
 * read() from a FIFO:
 * - If FIFO empty:
 *   - O_NONBLOCK: return -EAGAIN
 *   - else: sleep until data arrives
 * - Else: copy as much as possible to userspace and CONSUME those bytes.
 */
static ssize_t ctut_fifo_read(struct file *file, char __user *buf,
			      size_t count, loff_t *ppos)
{
	struct ctut_fifo_dev *dev = file->private_data;
	unsigned int copied = 0;
	int rc;

	/*
	 * For a stream device, the file offset is not meaningful.
	 * We keep the signature and may still advance *ppos for completeness,
	 * but lseek() is not supported (see .llseek = no_llseek).
	 */
	if (count == 0)
		return 0;

	for (;;) {
		if (mutex_lock_interruptible(&dev->lock))
			return -ERESTARTSYS;

		if (!kfifo_is_empty(&dev->fifo))
			break; /* we have data */

		mutex_unlock(&dev->lock);

		if (file->f_flags & O_NONBLOCK)
			return -EAGAIN;

		/*
		 * Sleep until somebody writes data and wakes us up.
		 * The condition is re-checked after wake-up (important!).
		 */
		rc = wait_event_interruptible(dev->readq,
					      !kfifo_is_empty(&dev->fifo));
		if (rc)
			return rc; /* -ERESTARTSYS if interrupted by signal */
	}

	/*
	 * Copy bytes from FIFO to userspace.
	 * kfifo_to_user() copies up to @count, sets @copied, and returns 0 or -EFAULT.
	 */
	rc = kfifo_to_user(&dev->fifo, buf, count, &copied);
	mutex_unlock(&dev->lock);

	if (rc)
		return rc;

	/*
	 * We consumed bytes, so there is more space for writers now.
	 * Wake up any writers blocked on a full FIFO.
	 */
	wake_up_interruptible(&dev->writeq);

	/* Optional: advance file position (not used for seeking). */
	*ppos += copied;
	return (ssize_t)copied;
}

/*
 * write() to a FIFO:
 * - If FIFO full:
 *   - O_NONBLOCK: return -EAGAIN
 *   - else: sleep until space is available
 * - Else: copy as much as possible from userspace and APPEND into FIFO.
 */
static ssize_t ctut_fifo_write(struct file *file, const char __user *buf,
			       size_t count, loff_t *ppos)
{
	struct ctut_fifo_dev *dev = file->private_data;
	unsigned int copied = 0;
	int rc;

	if (count == 0)
		return 0;

	for (;;) {
		if (mutex_lock_interruptible(&dev->lock))
			return -ERESTARTSYS;

		if (!kfifo_is_full(&dev->fifo))
			break; /* we have space */

		mutex_unlock(&dev->lock);

		if (file->f_flags & O_NONBLOCK)
			return -EAGAIN;

		rc = wait_event_interruptible(dev->writeq,
					      !kfifo_is_full(&dev->fifo));
		if (rc)
			return rc;
	}

	/*
	 * Copy bytes from userspace into the FIFO.
	 * kfifo_from_user() copies up to @count, sets @copied, returns 0 or -EFAULT.
	 */
	rc = kfifo_from_user(&dev->fifo, buf, count, &copied);
	mutex_unlock(&dev->lock);

	if (rc)
		return rc;

	/* We added bytes; wake up any readers waiting for data. */
	wake_up_interruptible(&dev->readq);

	/* Optional: advance file position (not used for seeking). */
	*ppos += copied;
	return (ssize_t)copied;
}

/*
 * poll() support:
 *
 * This allows select(2)/poll(2)/epoll(7) to wait until the device is readable
 * or writable without busy-waiting.
 */
static __poll_t ctut_fifo_poll(struct file *file, poll_table *wait)
{
	struct ctut_fifo_dev *dev = file->private_data;
	__poll_t mask = 0;

	/* Register our wait queues with the poll infrastructure. */
	poll_wait(file, &dev->readq, wait);
	poll_wait(file, &dev->writeq, wait);

	/*
	 * We must check readiness after registering the wait queues to avoid races.
	 * (Data could arrive between check and registration.)
	 */
	if (mutex_lock_interruptible(&dev->lock))
		return EPOLLERR;

	if (!kfifo_is_empty(&dev->fifo))
		mask |= EPOLLIN | EPOLLRDNORM;

	if (!kfifo_is_full(&dev->fifo))
		mask |= EPOLLOUT | EPOLLWRNORM;

	mutex_unlock(&dev->lock);
	return mask;
}

static long ctut_fifo_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ctut_fifo_dev *dev = file->private_data;

	(void)arg;

	if (_IOC_TYPE(cmd) != CTUT_FIFO_IOCTL_MAGIC)
		return -ENOTTY;

	switch (cmd) {
	case CTUT_FIFO_IOCTL_CLEAR:
		if (mutex_lock_interruptible(&dev->lock))
			return -ERESTARTSYS;
		kfifo_reset(&dev->fifo);
		mutex_unlock(&dev->lock);

		/*
		 * After clearing:
		 * - readers should block (or get -EAGAIN if non-blocking)
		 * - writers likely can proceed (space available)
		 * Wake both sides to re-check conditions.
		 */
		wake_up_interruptible(&dev->readq);
		wake_up_interruptible(&dev->writeq);
		return 0;
	default:
		return -ENOTTY;
	}
}

static const struct file_operations ctut_fifo_fops = {
	.owner          = THIS_MODULE,
	.open           = ctut_fifo_open,
	.release        = ctut_fifo_release,
	.read           = ctut_fifo_read,
	.write          = ctut_fifo_write,
	.unlocked_ioctl = ctut_fifo_ioctl,
	.poll           = ctut_fifo_poll,
	.llseek         = no_llseek, /* critical: FIFO is a stream, not a file */
};

static int __init ctut_fifo_init(void)
{
	int rc;

	memset(&g_dev, 0, sizeof(g_dev));
	mutex_init(&g_dev.lock);
	init_waitqueue_head(&g_dev.readq);
	init_waitqueue_head(&g_dev.writeq);

	/* Allocate a device number (major, minor). */
	rc = alloc_chrdev_region(&g_dev.devt, 0, 1, "ctut_kfifo");
	if (rc) {
		pr_err("ctut_fifo: alloc_chrdev_region failed: %d\n", rc);
		return rc;
	}

	/* Allocate the FIFO buffer storage. */
	rc = kfifo_alloc(&g_dev.fifo, CTUT_FIFO_SIZE, GFP_KERNEL);
	if (rc) {
		pr_err("ctut_fifo: kfifo_alloc failed: %d\n", rc);
		goto err_unregister;
	}

	/* Bind file_operations to our device number with cdev. */
	cdev_init(&g_dev.cdev, &ctut_fifo_fops);
	g_dev.cdev.owner = THIS_MODULE;
	rc = cdev_add(&g_dev.cdev, g_dev.devt, 1);
	if (rc) {
		pr_err("ctut_fifo: cdev_add failed: %d\n", rc);
		goto err_kfifo_free;
	}

	/* Create /sys/class/<class>/ and trigger udev for /dev/<node>. */
	g_dev.class = class_create(CTUT_FIFO_CLASS_NAME);
	if (IS_ERR(g_dev.class)) {
		rc = PTR_ERR(g_dev.class);
		pr_err("ctut_fifo: class_create failed: %d\n", rc);
		g_dev.class = NULL;
		goto err_cdev_del;
	}

	g_dev.device = device_create(g_dev.class, NULL, g_dev.devt, NULL, CTUT_FIFO_DEV_NAME);
	if (IS_ERR(g_dev.device)) {
		rc = PTR_ERR(g_dev.device);
		pr_err("ctut_fifo: device_create failed: %d\n", rc);
		g_dev.device = NULL;
		goto err_class_destroy;
	}

	pr_info("ctut_fifo: loaded. dev=%u:%u (/dev/%s) fifo_size=%u\n",
		MAJOR(g_dev.devt), MINOR(g_dev.devt), CTUT_FIFO_DEV_NAME, CTUT_FIFO_SIZE);
	return 0;

err_class_destroy:
	if (g_dev.class)
		class_destroy(g_dev.class);
err_cdev_del:
	cdev_del(&g_dev.cdev);
err_kfifo_free:
	kfifo_free(&g_dev.fifo);
err_unregister:
	unregister_chrdev_region(g_dev.devt, 1);
	return rc;
}

static void __exit ctut_fifo_exit(void)
{
	if (g_dev.device)
		device_destroy(g_dev.class, g_dev.devt);
	g_dev.device = NULL;

	if (g_dev.class)
		class_destroy(g_dev.class);
	g_dev.class = NULL;

	cdev_del(&g_dev.cdev);
	kfifo_free(&g_dev.fifo);
	unregister_chrdev_region(g_dev.devt, 1);

	pr_info("ctut_fifo: unloaded\n");
}

module_init(ctut_fifo_init);
module_exit(ctut_fifo_exit);

MODULE_AUTHOR("Beginner tutorial (generated for learning)");
MODULE_DESCRIPTION("ctut_fifo: character device tutorial using kfifo ring buffer");
MODULE_LICENSE("GPL");

