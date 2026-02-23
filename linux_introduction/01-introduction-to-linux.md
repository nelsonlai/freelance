# Introduction to Linux

## What is Linux?

**Linux** is a free, open-source operating system kernel first released by Linus Torvalds in 1991. When people say "Linux," they often mean a complete operating system built around this kernel—a **Linux distribution** (distro)—which includes the kernel, system libraries, user-space tools, and often a desktop environment.

### Key characteristics

- **Open source**: Source code is freely available; you can study, modify, and redistribute it.
- **Multi-user & multi-tasking**: Many users and programs can run at the same time.
- **Portable**: Runs on desktops, servers, embedded devices, and supercomputers.
- **Secure**: User permissions, file ownership, and built-in security mechanisms.

---

## The Linux Architecture

```
┌─────────────────────────────────────────────────────────┐
│  User applications (browsers, editors, scripts)         │
├─────────────────────────────────────────────────────────┤
│  Shell (Bash, Zsh) — command-line interface             │
├─────────────────────────────────────────────────────────┤
│  System libraries (glibc, etc.)                         │
├─────────────────────────────────────────────────────────┤
│  Kernel (process, memory, device, file system, network) │
├─────────────────────────────────────────────────────────┤
│  Hardware (CPU, RAM, disk, network)                      │
└─────────────────────────────────────────────────────────┘
```

- **Kernel**: Manages hardware, memory, processes, and low-level system resources.
- **Shell**: Text interface where you type commands; the default is often **Bash**.
- **User space**: Everything that runs outside the kernel (programs, libraries, tools).

---

## Common Linux Distributions

| Distribution | Typical use | Package manager |
|-------------|-------------|-----------------|
| **Ubuntu**  | Desktop, server, beginners | apt / dpkg |
| **Debian**  | Stable base for many distros | apt / dpkg |
| **Fedora**  | Cutting-edge, developer focus | dnf |
| **CentOS / Rocky** | Enterprise servers | dnf / yum |
| **Arch Linux** | Minimal, do-it-yourself | pacman |

This guide uses **Ubuntu** as the reference when discussing tools and examples.

---

## The File System Hierarchy

Linux organizes everything as files under a single tree starting at **root** (`/`).

| Path | Purpose |
|------|---------|
| `/` | Root of the file system |
| `/home` | User home directories |
| `/etc` | System configuration files |
| `/usr` | User programs and libraries |
| `/var` | Variable data (logs, caches, databases) |
| `/tmp` | Temporary files |
| `/bin`, `/usr/bin` | Executable commands |
| `/sbin`, `/usr/sbin` | System administration commands |
| `/dev` | Device files |
| `/proc` | Virtual files describing processes and system info |

---

## Users, Groups, and Permissions

- Every process and file is owned by a **user** and a **group**.
- **root** (user ID 0) has full administrative access.
- Use `sudo` to run individual commands as root when needed; avoid logging in as root for daily work.

### Basic permission concepts

- **Read (r)**: View file contents or list directory.
- **Write (w)**: Modify file or add/remove files in directory.
- **Execute (x)**: Run file as program or enter directory.

Permissions are shown in groups of three: **owner**, **group**, **others** (e.g. `rwxr-xr--`).

---

## Why Use Linux?

- **Stability and performance** on servers and long-running systems.
- **No license cost** for the OS itself.
- **Flexibility**: Choose your distro, desktop, and tools.
- **Scripting and automation** via shell and other languages.
- **Wide use** in cloud, containers (Docker, Kubernetes), and embedded systems.

---

## Next Steps

- Learn the **shell** and basic commands: see [02-linux-bash-and-shell-scripting.md](02-linux-bash-and-shell-scripting.md).
- Explore **Ubuntu network tools** (DNS, firewall, etc.): see [03-ubuntu-network-tools.md](03-ubuntu-network-tools.md).
