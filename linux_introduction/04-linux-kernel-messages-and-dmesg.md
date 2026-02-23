# Linux Kernel Messages: How Drivers Log and How to Dump Them

This guide explains how kernel code (including drivers) emits log messages and how you can view or dump those messages from user space.

---

## How the Kernel (and Drivers) Write Messages

### printk()

Kernel code uses **`printk()`** to send text to the kernel log buffer. It is similar to `printf()` but works in kernel context and has an associated **log level**.

```c
#include <linux/printk.h>

// Basic form: printk("format string", ...);
printk("Hello from kernel\n");
printk(KERN_INFO "Device initialized, version %d\n", version);
```

**Log level** is a number that indicates severity. You usually specify it as a macro before the format string (no comma). If you omit it, `DEFAULT_MESSAGE_LOGLEVEL` (often 4 = KERN_WARNING) is used.

### Standard log levels

Defined in `<linux/kernel.h>` (or `<linux/printk.h>`):

| Macro        | Value | Meaning      | Typical use              |
|-------------|-------|--------------|---------------------------|
| `KERN_EMERG`  | 0   | Emergency    | System unusable           |
| `KERN_ALERT`  | 1   | Alert        | Immediate action needed   |
| `KERN_CRIT`   | 2   | Critical     | Critical conditions       |
| `KERN_ERR`    | 3   | Error        | Error conditions          |
| `KERN_WARNING`| 4   | Warning      | Warning conditions        |
| `KERN_NOTICE` | 5   | Notice       | Normal but significant    |
| `KERN_INFO`   | 6   | Informational| Informational             |
| `KERN_DEBUG`  | 7   | Debug        | Debug-level messages      |

Example in a driver:

```c
printk(KERN_ERR "my_driver: failed to map IRQ\n");
printk(KERN_INFO "my_driver: probe completed for %s\n", dev_name(dev));
printk(KERN_DEBUG "my_driver: register value 0x%x\n", reg);
```

### Convenience macros: pr_* and dev_*

The kernel provides shortcuts that include the level and (for `dev_*`) the device:

```c
#include <linux/printk.h>
#include <linux/device.h>   // for dev_* when you have struct device

// pr_* — same as printk(KERN_LEVEL "format", ...)
pr_emerg("system halt\n");
pr_alert("bug detected\n");
pr_crit("critical failure\n");
pr_err("error: %d\n", err);
pr_warn("warning: retry\n");
pr_notice("event occurred\n");
pr_info("info: version %s\n", VER);
pr_debug("debug: val=%d\n", val);

// dev_* — prefix with device name (e.g. "mydev 0000:00:1f.0: ...")
struct device *dev = ...;
dev_emerg(dev, "device unreachable\n");
dev_alert(dev, "firmware required\n");
dev_crit(dev, "hardware fault\n");
dev_err(dev, "probe failed: %d\n", err);
dev_warn(dev, "deprecated option\n");
dev_notice(dev, "link up\n");
dev_info(dev, "driver loaded\n");
dev_dbg(dev, "register dump: 0x%x\n", val);
```

`dev_dbg()` is often compiled out unless you enable dynamic debug or `DEBUG` for that source file.

### Where messages go

- **Kernel log buffer**: A ring buffer in RAM. All `printk()` output goes here first.
- **Console**: If the level is **lower than or equal to** the current **console log level**, the message is also printed to the console (serial, VGA, etc.).
- **User-space readers**: Tools like `dmesg` or services that read `/dev/kmsg` or `/proc/kmsg` read from the same buffer (see below).

---

## Controlling what appears on the console

- **Console log level**: Only messages with numerical level **≤** this value are printed to the console. So a *lower* number = more severe = fewer messages; a *higher* number = less severe = more messages.
- **Default log level**: Set at build time; often 4 (KERN_WARNING) or 7 (everything).
- **Runtime**: You can change the **console** log level via `/proc/sys/kernel/printk` or the `loglevel` kernel parameter so that more or fewer messages go to the console. The kernel buffer still keeps everything (until it wraps).

### /proc/sys/kernel/printk

Four numbers, for example: `7    4    1    7`

1. **Current console log level** (messages with level ≤ this are printed to console).
2. **Default message log level** (used when `printk()` doesn’t specify a level).
3. **Minimum console log level** (lowest value you can set for console).
4. **Default console log level** (used at boot).

```bash
# Show current values
cat /proc/sys/kernel/printk

# Allow all levels on console (e.g. 7 = include debug)
echo 7 | sudo tee /proc/sys/kernel/printk

# Only emergencies on console (quiet)
echo 1 | sudo tee /proc/sys/kernel/printk
```

Changing this does **not** stop the kernel from storing messages in the buffer; it only affects what is echoed to the console. Dumping kernel messages (e.g. with `dmesg`) still shows whatever is in the buffer.

---

## How to Dump Kernel Messages

### 1. dmesg (most common)

**dmesg** reads the kernel ring buffer and prints it to stdout.

```bash
# Full kernel log (all messages in buffer)
dmesg

# Paginated
dmesg | less

# Only last N lines
dmesg | tail -n 100

# Human-readable timestamps (seconds since boot)
dmesg -T

# Or (older syntax)
dmesg --time-format=ctime

# Only messages since last read (clear ring buffer “read” position first; see -C)
dmesg -C          # clear buffer (requires root; not on all systems)
dmesg -c          # print and clear (root)
dmesg -w          # wait (follow) for new messages (like tail -f)
```

**Log levels** (decode the level prefix):

```bash
# Show levels in human-readable form (e.g. <6> -> info)
dmesg -l emerg,alert,crit,err,warn,notice,info,debug

# Only errors and worse
dmesg -l err

# Facility and level (decode both)
dmesg -x
```

**Filtering** (examples):

```bash
# Only lines containing a string
dmesg | grep -i usb
dmesg | grep -i "my_driver"

# Last 50 lines, then filter
dmesg | tail -50 | grep -i error
```

**Saving**:

```bash
# Save full log to file
dmesg > dmesg.txt

# With timestamps
dmesg -T > dmesg_timed.txt
```

### 2. /dev/kmsg (structured, streaming)

**/dev/kmsg** is a character device that exposes kernel messages in a structured format. Reading from it consumes messages (sequential read); multiple readers get the same stream.

```bash
# Stream new kernel messages (requires root)
sudo cat /dev/kmsg

# One-time dump (then exit; may need to run as root)
sudo cat /dev/kmsg
```

**dmesg** on many systems uses `/dev/kmsg` when available. `/dev/kmsg` is the preferred interface for programs that need structured or real-time kernel log data.

### 3. /proc/kmsg (legacy, similar to dmesg)

**/proc/kmsg** is a legacy interface to the kernel log buffer. Only one process can read it at a time (like a single consumer). Often restricted to root.

```bash
# Read kernel messages (root; blocks until new messages or EOF)
sudo cat /proc/kmsg
```

For interactive dumping, **dmesg** is usually easier; for following live, `dmesg -w` or `cat /dev/kmsg` is typical.

### 4. journalctl (when systemd is used)

On systems using **systemd**, the journal may store a copy of kernel messages. You can “dump” them with **journalctl**:

```bash
# Kernel messages only
journalctl -k

# Same, alternate name
journalctl --dmesg

# Since boot
journalctl -k -b

# Last boot
journalctl -k -b -1

# Follow new kernel messages
journalctl -k -f

# With timestamps
journalctl -k -o short-precise

# Export to file
journalctl -k > kernel_log.txt
```

This is a “dump” of what the journal has captured from the kernel, not necessarily the raw ring buffer; for raw buffer, use **dmesg** or **/dev/kmsg**.

### 5. Boot log (first messages)

Right after boot, the buffer contains boot messages. To capture them:

```bash
# Dump current buffer (includes boot messages if buffer not overwritten)
dmesg > boot_dmesg.txt

# Or use systemd’s boot capture (if available)
journalctl -k -b 0 > boot_kernel.txt
```

On some setups, **boot log** is also written to a file (e.g. by the bootloader or initramfs); that’s distribution-specific.

---

## Quick reference

| Goal                         | Command / method                    |
|-----------------------------|-------------------------------------|
| Print kernel buffer         | `dmesg`                             |
| With human-readable time    | `dmesg -T`                          |
| Follow new messages         | `dmesg -w` or `sudo cat /dev/kmsg`  |
| Only errors                 | `dmesg -l err`                      |
| Filter by text              | `dmesg | grep -i "string"`            |
| Save to file                | `dmesg > dmesg.txt`                 |
| Kernel msgs in systemd      | `journalctl -k`                     |
| Change console verbosity    | `echo 7 \| sudo tee /proc/sys/kernel/printk` |

---

## Summary

- **Drivers (and any kernel code)** log with **`printk()`** or the **`pr_*`** / **`dev_*`** macros, using a **log level**.
- Messages go into the **kernel log buffer**; they may also be printed to the **console** if their level is at or above the **console log level**.
- You **dump** those messages with **`dmesg`**, by reading **`/dev/kmsg`** or **`/proc/kmsg`**, or (on systemd) with **`journalctl -k`**. For day-to-day use, **dmesg** is the standard way to dump kernel messages.
