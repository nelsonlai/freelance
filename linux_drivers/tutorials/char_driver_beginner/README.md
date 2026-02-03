# Beginner Character Driver Tutorial (Linux)

This tutorial shows how a **character device driver** works by building small,
heavily-commented kernel modules that create `/dev` nodes, then implement common
character-driver file operations.

It’s meant for beginners who already know C and basic Linux command-line usage.

> Source tree reference: the upstream Linux kernel lives at
> [`torvalds/linux`](https://github.com/torvalds/linux).

---

## What is a “character device”?

A **character device** is a device file that is accessed as a stream of bytes
(like a file): you read/write bytes, and the driver decides what that means.

Common examples:
- Serial ports: `/dev/ttyS0`
- Input devices (historically): `/dev/input/*`
- Many misc/simple kernel interfaces

This differs from **block devices** (disks) where I/O is usually in blocks and
goes through the block layer.

---

## The end-to-end data flow

When a user program does:

```c
int fd = open("/dev/ctut0", O_RDWR);
write(fd, "hello", 5);
read(fd, buf, sizeof(buf));
```

The flow (simplified) is:

1. `open("/dev/ctut0")` hits the **VFS** (Virtual Filesystem).
2. The VFS sees `/dev/ctut0` is a special file whose type is “character device”,
   and it has a **device number**: `(major, minor)`.
3. The VFS uses that `(major, minor)` to find the driver that registered that
   device and calls the driver’s `file_operations`.
4. Your driver’s callbacks run in kernel context:
   - `.open` when opened
   - `.read` on `read(2)`
   - `.write` on `write(2)`
   - `.unlocked_ioctl` on `ioctl(2)`
   - `.release` when closed

In code, the VFS jumps into your functions through a table like:

```c
static const struct file_operations fops = {
  .owner          = THIS_MODULE,
  .open           = ctut_open,
  .read           = ctut_read,
  .write          = ctut_write,
  .llseek         = ctut_llseek,
  .unlocked_ioctl = ctut_ioctl,
  .release        = ctut_release,
};
```

---

## The key kernel objects (mental model)

### Device numbers: `dev_t`, major, minor

- **Major**: identifies the driver (more precisely, a range owned by a driver)
- **Minor**: identifies a particular device instance within that driver

Your driver usually:
- allocates a major (dynamically) + some minors with `alloc_chrdev_region()`
- registers callbacks with `cdev_add()`

### `struct cdev`

`cdev` is the kernel object that ties your `(major, minor)` range to your
`file_operations`.

### `struct class` + `device_create()` (auto `/dev` node)

To get a convenient `/dev/ctut0` created automatically on most distros, the
driver:

- creates a class with `class_create()`
- creates a device with `device_create()`

`udev` (userspace device manager) listens for these device events and typically
creates the `/dev` node for you.

---

## The example driver you’ll build

Files in this folder (two versions):

- `ctut_char.c`: **file-like** device backed by a linear buffer (supports `llseek`)
- `ctut_kfifo.c`: **stream** device backed by a ring buffer (`kfifo`), non-seekable
- `Makefile`: builds the module against your **running** kernel headers
- `user_test.c`: tiny userspace program to open/read/write/ioctl the device

### Version 1: file-like buffer (`ctut_char.c`)

The device behaves like a small “RAM-backed file”:

- Writes append/overwrite into an internal buffer.
- Reads return bytes from that buffer based on the file offset.
- `llseek()` changes the file offset.
- An `ioctl()` can clear the buffer.

### Version 2: stream ring buffer (`ctut_kfifo.c`)

This version behaves like a **byte stream** (like a pipe/tty):

- Writes append bytes into a FIFO.
- Reads consume bytes from the FIFO.
- `lseek()` is **not supported** (`-ESPIPE`), because stream devices don’t have a meaningful file offset.
- If the FIFO is empty:
  - blocking `read()` sleeps until data arrives
  - `O_NONBLOCK` `read()` returns `-EAGAIN`
- If the FIFO is full:
  - blocking `write()` sleeps until space is available
  - `O_NONBLOCK` `write()` returns `-EAGAIN`
- `poll()` is implemented so `select/poll/epoll` can wait for readable/writable.

This is **not** a production driver; it’s a teaching scaffold.

---

## Build + load (out-of-tree module)

This builds the module against whatever kernel you’re currently running.

1) Build:

```bash
cd /path/to/linux_drivers/tutorials/char_driver_beginner
make
```

2) Load:

```bash
# Choose ONE:
sudo insmod ctut_char.ko      # creates /dev/ctut0
# or:
sudo insmod ctut_kfifo.ko     # creates /dev/ctut_fifo0

dmesg | tail -n 50
ls -l /dev/ctut0 /dev/ctut_fifo0 2>/dev/null || true
```

3) Try it:

```bash
make user_test
./user_test /dev/ctut0        # for ctut_char
./user_test /dev/ctut_fifo0   # for ctut_kfifo
```

4) Unload:

```bash
sudo rmmod ctut_char ctut_kfifo 2>/dev/null || true
```

If you don’t see `/dev/ctut0`, check `dmesg` and confirm your system runs
`udev` (most do). You can also create the node manually if needed, but the whole
point of `device_create()` here is to avoid that.

---

## Common beginner gotchas (important!)

- **Never trust user pointers**: use `copy_to_user()` / `copy_from_user()`.
- **Check return values**: many kernel APIs can fail.
- **Concurrency**: multiple processes can read/write the device at the same time.
  This tutorial uses a `mutex` to protect the buffer.
- **Offsets matter**: `read()`/`write()` should use and update `*ppos`.
- **Kernel log spam**: don’t `pr_info()` on every byte; keep logs reasonable.
- **Licensing**: modules should have a license tag; this tutorial uses GPL.

---

## Where to go next

After you understand this module, consider:

- Switching the storage to a circular buffer (ring).
- Supporting blocking reads with `wait_event_interruptible()` and `poll()`.
- Using `kfifo` helper APIs.
- Adding sysfs attributes via `device_create_file()` or `dev_groups`.

