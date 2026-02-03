# Linux 50‑Minute Class — Bundle

This bundle contains:
- `linux_50min_lesson.md` — the full teaching pack
- `alloc.c` — userspace memory demo
- `mlock_demo.c` — lock memory to avoid swap
- `hello.c` & `Makefile` — minimal kernel module

## Quick Start

### Userspace demos
```bash
gcc -O2 alloc.c -o alloc && ./alloc 300 &
pid=$!
pmap -x $pid | tail
grep -E 'VmRSS|VmSize|VmLck' /proc/$pid/status

gcc -O2 mlock_demo.c -o mlock_demo && sudo ./mlock_demo
```

### Kernel module (use a VM)
```bash
sudo apt update && sudo apt install -y build-essential linux-headers-$(uname -r)
make
sudo insmod hello.ko who="class"
dmesg | tail -n 10
lsmod | grep hello
sudo rmmod hello
make clean
```
