# 50‑Minute Lesson: Linux OS, Middleware, Kernel, Scheduling, Memory & Drivers

**Audience:** Senior high school / early undergraduate / junior developers

**Prereqs:** Basic C/C++ and command line

**Goal:** Give learners a working mental model of Linux from user space to kernel, then practise with short demos.

---

## Slide Pack (talk track + demos)

### Slide 1 — Why Linux?
- Runs everywhere: cloud, phones, embedded, vehicles, factories
- Strengths: openness, tooling, drivers, security model
- Kernel + GNU userland ≈ "GNU/Linux"

**Notes:** Mention Android uses Linux kernel with different userspace.

---

### Slide 2 — The Big Picture (Layers)
```
+----------------------------+  Applications (your code: C/C++/Python)
|   Apps / Services          |
+----------------------------+  Middleware (glibc, libstdc++, DBus, GStreamer, Qt)
|   Libraries & Middleware   |
+----------------------------+  System Call Interface (read, write, open, ioctl, mmap)
|   Syscall Boundary         |
+----------------------------+  Linux Kernel (scheduler, mm, VFS, net, drivers)
|   Kernel Space             |
+----------------------------+  Hardware (CPU, RAM, PCIe, USB, I2C, disk, NIC)
```

**Notes:** *User space* is unprivileged; *kernel space* is privileged. Middleware = reusable plumbing above syscalls.

---

### Slide 3 — Processes & Threads
- Process = resources (address space, file descriptors) + 1+ threads
- Thread = schedulable unit executing within a process
- Context switch saves/restores CPU state
- Tools: `ps`, `top/htop`, `/proc/<pid>`

**Demo:**
```bash
ps -eLo pid,ppid,tid,class,rtprio,pri,psr,cmd | head
```

---

### Slide 4 — Scheduling Overview
- Classes: **CFS** (normal) and **RT** (FIFO/RR), plus deadline (DL)
- **CFS** targets fairness using virtual runtime and weights (nice levels)
- **RT** ignores CFS fairness; priority 1–99 runs first
- Affinity pins threads to CPUs; preemption types (none/voluntary/full)

**Demo:**
```bash
# See current policy of this shell
chrt -p $$
# Run a task as SCHED_FIFO
sudo chrt -f 50 sleep 2 &  # (explain carefully!)
# Adjust niceness
nice -n 10 yes > /dev/null &
renice -n -10 -p <pid>
# CPU affinity
taskset -pc 0,1 $$
```

**Safety note:** Keep RT demos short; an infinite RT loop can starve the system.

---

### Slide 5 — Memory Management Overview
- Virtual memory per process; pages (commonly 4 KiB), page tables, TLB
- Regions: text, heap, stack, `mmap`-ed files/anonymous
- Page cache accelerates file I/O; demand paging & page faults
- Kernel allocators: buddy (page frames), slab/slub (objects)

**Demo:**
```bash
free -h; vmstat 1 5; cat /proc/meminfo | head
pmap -x $$ | head -20
```

---

### Slide 6 — Tiny C Program: Touching Memory
**alloc.c**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv){
    size_t mb = (argc>1)?strtoul(argv[1], NULL, 10):200; // MB
    size_t bytes = mb * 1024UL * 1024UL;
    char *buf = malloc(bytes);
    if(!buf){perror("malloc"); return 1;}
    for(size_t i=0;i<bytes;i+=4096) buf[i] = 1; // touch each page
    printf("Allocated & touched %zu MB. PID=%d\n", mb, getpid());
    getchar(); // keep process alive to inspect pmap
    return 0;
}
```
**Build/Run:** `gcc -O2 alloc.c -o alloc && ./alloc 500`

**Observe:** `pmap -x <PID> | tail` and `cat /proc/<PID>/smaps | grep -E "^Pss|^Rss" -n`

---

### Slide 7 — Locking Memory (No Swap)
**mlock_demo.c**
```c
#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    size_t sz = 100UL<<20; // 100MB
    void *p = malloc(sz);
    if(!p){perror("malloc"); return 1;}
    if(mlock(p, sz)!=0){perror("mlock");}
    printf("Locked 100MB. Check VmLck in /proc/%d/status\n", getpid());
    getchar();
}
```
**Observe:** `grep VmLck /proc/<PID>/status`

---

### Slide 8 — Device Drivers: What & Why
- Driver = code that lets kernel talk to hardware (or virtual devices)
- Types: char, block, network; buses: PCIe/USB/I²C/SPI
- Linux device model: **bus** ↔ **device** ↔ **driver**; `sysfs` under `/sys`
- Major/minor numbers → `/dev/*` nodes; `udev` creates device files

**Notes:** In embedded, drivers often platform/SoC‑specific; upstreaming benefits maintenance.

---

### Slide 9 — Your First Kernel Module (Hello)
**Requirements:** VM or dev box with headers (`sudo apt install build-essential linux-headers-$(uname -r)`).

**hello.c**
```c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
static char *who = "world";
module_param(who, charp, 0644);
MODULE_PARM_DESC(who, "Name to greet");
static int __init hello_init(void){
    pr_info("hello: init, hello %s\n", who);
    return 0;
}

static void __exit hello_exit(void){
    pr_info("hello: exit, goodbye %s\n", who);
}
module_init(hello_init);
module_exit(hello_exit);
```

**Makefile**
```make
obj-m := hello.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
```

**Build & Load:**
```bash
make
sudo insmod hello.ko who="class"
dmesg | tail -n 5
lsmod | grep hello
sudo rmmod hello
```

**Notes:** Use a VM; a bad module can crash the host.

---

### Slide 10 — Middleware: The Glue Above Syscalls
- **glibc/libstdc++**: standard C/C++ library (wrapping syscalls)
- **systemd**: init, service manager, logging (journald), timers, cgroups
- **DBus**: message bus for inter‑process communication
- **GStreamer**: media pipeline framework
- **ROS/ROS 2**: robotics middleware (pub/sub, services, parameters)
- Benefits: portability, reuse, safety; Costs: complexity, overhead

**Demo idea:** `systemctl status` a service; `busctl list` to peek at DBus.

---

### Slide 11 — Security & Isolation (Short)
- Permissions & capabilities (drop root powers granularly)
- Namespaces & cgroups → containers
- SELinux/AppArmor for MAC policies

**Demo:**
```bash
capsh --print | head
cat /proc/$$/status | grep CapEff
```

---

### Slide 12 — Recap & Q‑Check
- Linux architecture, scheduling, memory, drivers, middleware
- You used: `chrt`, `nice`, `taskset`, `vmstat`, `/proc`, built a module
- **Exit ticket:**
  1. When would you choose RT over CFS?
  2. Why does touching each allocated page matter?
  3. What creates `/dev` nodes?

---

## Cheat Sheets (1‑pagers)

### Scheduling
- Policies: `SCHED_OTHER` (CFS), `SCHED_FIFO`, `SCHED_RR`, `SCHED_DEADLINE`
- Priorities: CFS uses *nice* (−20..19); RT uses 1..99
- Tools: `ps -L -o policy,rtprio ...`, `chrt`, `taskset`, `schedtool`
- Tips: Avoid long‑running RT without yielding; pin noisy threads

### Memory
- `free -h`, `vmstat 1`, `/proc/meminfo`
- `pmap -x <pid>` regions; `/proc/<pid>/smaps` has per‑VMA detail
- `mlock/mlockall` prevent swapping; `madvise` for hints; `numactl` for NUMA

### Drivers
- Types: char/block/net; major/minor; `udevadm info -a -n /dev/ttyUSB0`
- Build: out‑of‑tree module with kernel headers; observe with `dmesg`

---

## Lab Handout (copy/paste)

1) **Inspect scheduling**
```bash
ps -L -p $$ -o pid,tid,cls,rtprio,pri,psr,cmd
chrt -p $$
( sleep 5 & )
ps -eLo pid,tid,cls,rtprio,pri,psr,comm | head
```

2) **Play with nice & affinity**
```bash
nice -n 15 sha1sum /dev/zero &
renice -n -10 -p %1
pidof sha1sum | xargs -I{} taskset -pc 0 {}
```

3) **Memory tour**
```bash
gcc -O2 alloc.c -o alloc && ./alloc 300 &
pid=$!
pmap -x $pid | tail
grep -E 'VmRSS|VmSize|VmLck' /proc/$pid/status
```

4) **Kernel module**
```bash
make && sudo insmod hello.ko who="linux"
dmesg | tail -n +1 | tail -n 10
sudo rmmod hello && make clean
```

---

## Assessment (5 quick questions)
1. Contrast CFS vs RT scheduling; give one use case for RT.
2. What is a page fault and why is it *usually* OK?
3. Where do device nodes live and who creates them?
4. What does `mlock()` do and when would you use it?
5. Why are kernel modules risky on a production system?

**Suggested answers:**
1) CFS (CFS = Completely Fair Scheduler) fairness vs RT deterministic latency; RT for motor control/audio. 2) Access to unmapped page → kernel maps/loads; normal with demand paging. 3) `/dev`, created by `udev` based on kernel events. 4) Pin pages in RAM; prevent swap for low‑latency/crypto keys. 5) Runs in kernel; bugs → crashes/security issues.

---

## Homework / Next Steps
- Write a userspace program that toggles `SCHED_RR` with `pthread_setschedparam` and measures jitter with `clock_nanosleep()`.
- Extend `hello.c` to export a sysfs attribute and read it from `/sys/module/hello/parameters/who`.
- Read: *Linux Device Drivers, 3rd ed.* (LDD3) chapters 1–3 (still conceptually relevant); check your distro’s kernel docs under `/usr/src/linux-headers-$(uname -r)/Documentation`.
- Optional: Explore eBPF for safe, dynamic kernel instrumentation without writing a full driver.

---

## Instructor Tips
- Use a VM snapshot before kernel module demos.
- Have `htop`, `p7zip-full`, `build-essential`, and headers pre‑installed.
- Keep RT demos time‑bounded (`sleep`), and know how to drop into another TTY (Ctrl+Alt+F2) if the UI stalls.

---

## Appendix — Full Files (for copy/paste)
- **hello.c** (module) — see Slide 9.
- **Makefile** (module) — see Slide 9.
- **alloc.c** and **mlock_demo.c** — see Slides 6–7.

**Service peek:**
```bash
systemctl list-units --type=service --state=running | head
busctl list | head
```

*End of pack.*
