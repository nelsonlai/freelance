# PCI (Peripheral Component Interconnect) Architecture and WiFi Driver Integration

## Table of Contents
1. [Introduction](#introduction)
2. [PCI Evolution and Standards](#pci-evolution-and-standards)
3. [PCI Hardware Architecture](#pci-hardware-architecture)
4. [PCI Bus Topology](#pci-bus-topology)
5. [PCI Configuration Space](#pci-configuration-space)
6. [PCI Address Spaces](#pci-address-spaces)
7. [PCI Interrupts](#pci-interrupts)
8. [PCI DMA Operations](#pci-dma-operations)
9. [PCI Power Management](#pci-power-management)
10. [Linux PCI Driver Framework](#linux-pci-driver-framework)
11. [WiFi PCI Driver Implementation](#wifi-pci-driver-implementation)
12. [Complete Driver Lifecycle Example](#complete-driver-lifecycle-example)
13. [Summary](#summary)

---

## Introduction

**PCI (Peripheral Component Interconnect)** is a local bus standard designed for connecting hardware devices to a computer system. Originally developed by Intel in 1992, PCI has evolved through multiple versions and remains a fundamental component of modern computer architectures, particularly in the form of PCI Express (PCIe).

**Key Concepts:**
- **Plug-and-Play:** PCI devices are automatically detected and configured
- **Bus Architecture:** Multiple devices share a common bus
- **Memory-Mapped I/O:** Devices appear in CPU's memory address space
- **DMA Support:** Devices can directly access system memory
- **Hot-Plug Support:** Modern PCIe supports adding/removing devices without shutdown

This document explains PCI hardware architecture, the PCI bus interface, and how Linux WiFi PCI card drivers leverage PCI to communicate with hardware.

---

## PCI Evolution and Standards

### PCI Generations Timeline

```
1992: PCI 1.0      - Original 32-bit, 33 MHz, 132 MB/s
1993: PCI 2.0      - 64-bit support, 66 MHz option
1995: PCI 2.1      - 66 MHz standard, improved specification
1998: PCI 2.2      - Power management, hot-plug support
1999: PCI-X        - Extended PCI for servers (133 MHz, 64-bit)
2003: PCI Express   - Serial point-to-point, revolutionary change
2007: PCIe 2.0      - 5 GT/s, doubled bandwidth
2010: PCIe 3.0      - 8 GT/s, encoding improvements
2017: PCIe 4.0      - 16 GT/s
2019: PCIe 5.0      - 32 GT/s
2022: PCIe 6.0      - 64 GT/s, PAM4 signaling
```

### PCI vs PCI-X vs PCI Express

| Feature | PCI | PCI-X | PCI Express (PCIe) |
|---------|-----|-------|-------------------|
| **Bus Type** | Parallel shared bus | Parallel shared bus | Serial point-to-point |
| **Width** | 32-bit or 64-bit | 64-bit | 1-32 lanes (serial) |
| **Clock** | 33/66 MHz | 66/100/133 MHz | Base clock + data rate |
| **Max Speed** | 133-533 MB/s | 533-1066 MB/s | 250 MB/s (x1) to 128 GB/s (x32) |
| **Topology** | Multi-drop bus | Multi-drop bus | Switched topology |
| **Hot-Plug** | Limited | Limited | Native support |
| **Error Handling** | Basic | Enhanced | Advanced (AER) |
| **Power Management** | Basic | Enhanced | Advanced (ASPM) |

**Note:** Modern WiFi cards typically use **PCI Express** (PCIe), though many are backward compatible with traditional PCI. This document focuses on PCI fundamentals that apply to both.

---

## PCI Hardware Architecture

### Physical Connector Types

#### 1. **Traditional PCI (32-bit, 33 MHz)**
```
Pin Layout (120 pins):
┌─────────────────────────────────────┐
│  Component Side (Pins 1-60)        │
│                                     │
│  [GND] [TRST#] [TDI] [TDO] [TMS]   │  ← JTAG, Control Signals
│  [CLK] [GND] [RST#] [GND] [3.3V]   │  ← Power & Clock
│  [AD31] [AD29] [3.3V] [GND] [...]  │  ← Address/Data Bus
│  [C/BE#3] [...] [PAR] [...] [GND]  │  ← Command/BE, Parity
│  [... pins continue ...]           │
└─────────────────────────────────────┘
┌─────────────────────────────────────┐
│  Solder Side (Pins 62-120)         │
│  [... similar pattern ...]         │
└─────────────────────────────────────┘
```

#### 2. **PCI Express (PCIe) - Modern Standard**
```
PCIe Connector (Variable Length):

PCIe x1:   │██│ (18mm long, 18 pins each side = 36 pins total)
PCIe x4:   │████│ (39mm)
PCIe x8:   │████████│ (56mm)
PCIe x16:  │████████████████│ (89mm) ← Most common for GPUs

Key Signals:
- Lane 0+: Differential pair (transmit)
- Lane 0-: Differential pair (transmit)
- Lane 1+: Differential pair (receive)
- Lane 1-: Differential pair (receive)
- REFCLK+/-: Reference clock
- PRSNT#: Presence detect
- PERST#: Fundamental reset
- PWR: Power pins (3.3V, 12V)
```

**PCIe Advantages:**
- **Point-to-Point:** Each device has dedicated link (no bus contention)
- **Scalable:** x1, x2, x4, x8, x16, x32 lanes
- **Higher Bandwidth:** Serial signaling allows much higher speeds
- **Better Power Management:** Active State Power Management (ASPM)
- **Advanced Features:** Hot-plug, Advanced Error Reporting (AER)

---

### PCI Hardware Signals

#### Core Signals (Traditional PCI)

**Address/Data Bus (AD[31:0]):**
- Multiplexed address and data
- 32-bit data path (64-bit in PCI-X/PCIe)
- Address phase: First clock cycle
- Data phase: Subsequent cycles

**Control Signals:**
- **CLK (Clock):** 33 MHz or 66 MHz system clock
- **RST# (Reset):** Active-low reset signal
- **FRAME#:** Indicates start/duration of transaction
- **IRDY# (Initiator Ready):** Initiator ready for data transfer
- **TRDY# (Target Ready):** Target ready for data transfer
- **DEVSEL# (Device Select):** Target claims transaction
- **IDSEL (Initialization Device Select):** Config space access
- **STOP#:** Target requests transaction termination

**Command/Byte Enables (C/BE#[3:0]):**
- **Address Phase:** Command type (Memory Read, Memory Write, I/O Read, etc.)
- **Data Phase:** Byte enables (which bytes are valid)

**Parity Signals:**
- **PAR:** Parity bit for AD[31:0] and C/BE#[3:0]
- Error detection for data integrity

**Arbitration Signals (Bus Master Only):**
- **REQ# (Request):** Device requests bus ownership
- **GNT# (Grant):** Bus arbiter grants bus access

**Interrupt Signals:**
- **INTA#**, **INTB#**, **INTC#**, **INTD#**: Hardware interrupt lines
- Shared between multiple devices

**System Signals:**
- **LOCK#:** Atomic operation lock
- **SERR# (System Error):** Parity or other system errors
- **PERR# (Parity Error):** Data parity error detected

---

### PCI Electrical Characteristics

#### Traditional PCI
- **Voltage:** 3.3V or 5V (keying prevents insertion in wrong slot)
- **Signaling:** TTL (Transistor-Transistor Logic)
- **Bus Termination:** Required at both ends of bus
- **Clock Distribution:** Single clock distributed to all devices
- **Max Load:** Limited number of devices (typically 4-5 per bus)

#### PCI Express
- **Voltage:** 3.3V (auxiliary), 12V (main power for high-power devices)
- **Signaling:** Differential signaling (LVDS-like)
- **Topology:** Point-to-point (no termination issues)
- **Clock:** Embedded clock (clock data recovery)
- **Scalability:** Each link is independent

---

## PCI Bus Topology

### Traditional PCI Bus Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    CPU & Northbridge                         │
│  ┌──────────┐         ┌──────────────┐                     │
│  │   CPU    │────────▶│ Northbridge  │                     │
│  └──────────┘         │ (Memory Ctrl)│                     │
│                       └──────┬───────┘                     │
└──────────────────────────────┼─────────────────────────────┘
                               │
                               │ Host Bridge
                               │
┌──────────────────────────────▼─────────────────────────────┐
│                    PCI Bus 0 (Primary)                      │
│  ┌──────┐  ┌──────┐  ┌──────┐  ┌──────┐                   │
│  │Device│  │Device│  │Device│  │ PCI  │                   │
│  │  1   │  │  2   │  │  3   │  │Bridge│────▶ PCI Bus 1    │
│  └──────┘  └──────┘  └──────┘  └──────┘                   │
│                                                             │
│  ┌─────────────────────────────────────────────────┐       │
│  │        Shared PCI Bus (Parallel)                │       │
│  │  All devices see all transactions               │       │
│  │  Arbitration required for bus access            │       │
│  └─────────────────────────────────────────────────┘       │
└─────────────────────────────────────────────────────────────┘

PCI Bus 1 (Secondary)
  ┌──────┐  ┌──────┐  ┌──────┐
  │Device│  │Device│  │Device│
  │  4   │  │  5   │  │  6   │
  └──────┘  └──────┘  └──────┘
```

**Characteristics:**
- **Shared Bus:** All devices on same bus share wires
- **Arbitration:** Only one device can drive bus at a time
- **Bus Bridges:** PCI-to-PCI bridges extend bus hierarchy
- **32-bit vs 64-bit:** Cards can be 32-bit or 64-bit (slots support both)

**Bus Numbering:**
- **Bus 0:** Primary bus (connected directly to CPU)
- **Bus 1-N:** Secondary buses (via PCI-to-PCI bridges)

**Device Numbering:**
- Each device on a bus has unique device number (0-31)
- Each device can have multiple functions (0-7)
- Address: **Bus:Device.Function** (e.g., 0000:02:00.0)

---

### PCI Express Topology

```
┌─────────────────────────────────────────────────────────────┐
│                      CPU & Root Complex                      │
│  ┌──────────┐         ┌──────────────┐                     │
│  │   CPU    │────────▶│ Root Complex │                     │
│  └──────────┘         │  (PCIe Root) │                     │
│                       └──────┬───────┘                     │
└──────────────────────────────┼─────────────────────────────┘
                               │
                    ┌──────────┼──────────┐
                    │          │          │
         ┌──────────▼───┐ ┌───▼───┐ ┌───▼───┐
         │  Root Port 1 │ │Root P2│ │Root P3│
         └──────┬───────┘ └───┬───┘ └───┬───┘
                │             │          │
         ┌──────▼────────┐    │    ┌────▼────┐
         │   Device 1    │    │    │ Device 3│
         │  (WiFi Card)  │    │    │ (GPU)   │
         └───────────────┘    │    └─────────┘
                              │
                        ┌─────▼─────┐
                        │   Switch  │ (PCIe Switch)
                        └─────┬─────┘
                 ┌────────────┼────────────┐
            ┌────▼────┐  ┌────▼────┐  ┌───▼────┐
            │ Device 4│  │ Device 5│  │ Device 6│
            └─────────┘  └─────────┘  └─────────┘
```

**PCIe Characteristics:**
- **Point-to-Point:** Each device has dedicated link
- **Switched:** PCIe switches provide multiple downstream ports
- **Scalable:** x1, x4, x8, x16 links (bandwidth proportional to lanes)
- **No Bus Arbitration:** No contention (each link independent)
- **Packet-Based:** Data sent as packets (like network)

**PCIe Link Structure:**
```
Lane 0:  [TX+] ──────────────▶ [RX+]
         [TX-] ──────────────▶ [RX-]
         [RX+] ◀────────────── [TX+]
         [RX-] ◀────────────── [TX-]

x4 Link: 4 such lanes in parallel
x16 Link: 16 such lanes in parallel
```

---

## PCI Configuration Space

### Overview

Every PCI device has a **configuration space** - a standardized register set that allows the system to:
- Identify the device (vendor ID, device ID)
- Determine device capabilities
- Configure device resources (memory addresses, interrupts)
- Control device power states
- Access extended capabilities

### Configuration Space Structure

#### Standard Configuration Header (64 bytes)

```
Offset (hex)   Size   Register Name          Description
─────────────────────────────────────────────────────────────────
0x00           2      Vendor ID              Device manufacturer (0x8086=Intel)
0x02           2      Device ID              Device model number
0x04           2      Command Register       Control device behavior
0x06           2      Status Register        Device status bits
0x08           1      Revision ID            Device revision
0x09           3      Class Code             Device class (0x028000=Network)
0x0C           1      Cache Line Size        Cache line size in 32-bit words
0x0D           1      Latency Timer          PCI latency timer value
0x0E           1      Header Type            Header format (0x00=normal, 0x01=bridge)
0x0F           1      BIST                   Built-In Self-Test
0x10           4      BAR 0                  Base Address Register 0
0x14           4      BAR 1                  Base Address Register 1
0x18           4      BAR 2                  Base Address Register 2
0x1C           4      BAR 3                  Base Address Register 3
0x20           4      BAR 4                  Base Address Register 4
0x24           4      BAR 5                  Base Address Register 5
0x28           4      CardBus CIS Pointer    CardBus information structure
0x2C           2      Subsystem Vendor ID    Subsystem vendor
0x2E           2      Subsystem Device ID    Subsystem device
0x30           4      Expansion ROM Base     ROM base address
0x34           1      Capabilities Pointer   Pointer to capabilities list
0x35           3      Reserved
0x38           4      Reserved               (0x38-0x3B)
0x3C           1      Interrupt Line         IRQ routing
0x3D           1      Interrupt Pin          INTx# used (1=INTA#, 2=INTB#, etc.)
0x3E           1      Min_Gnt                Minimum grant time
0x3F           1      Max_Lat                Maximum latency
```

#### Extended Configuration Space (PCIe)

PCI Express extends configuration space to **4096 bytes (4 KB)** to support:
- Advanced Error Reporting (AER)
- Virtual Channel (VC) capabilities
- Device Serial Number
- Power Budgeting
- Link capabilities and status
- MSI/MSI-X capability structures

### Key Configuration Registers Explained

#### 1. Vendor ID and Device ID
```c
// Example: Ralink WiFi card
Vendor ID: 0x1814 (Ralink Technology)
Device ID: 0x3090 (RT3090 chipset)
```

These IDs uniquely identify the device. Drivers match against these in their `pci_device_id` table.

#### 2. Command Register (0x04)

**Bit Fields:**
```
Bit 0:  I/O Space Enable          (1=enabled)
Bit 1:  Memory Space Enable       (1=enabled)
Bit 2:  Bus Master Enable         (1=DMA enabled) ← Critical for drivers!
Bit 3:  Special Cycles Enable
Bit 4:  Memory Write & Invalidate
Bit 5:  VGA Palette Snoop
Bit 6:  Parity Error Response
Bit 7:  Wait Cycle Control
Bit 8:  System Error Enable
Bit 9:  Fast Back-to-Back Enable
Bit 10: Interrupt Disable         (1=interrupts disabled)
```

**Driver Usage:**
```c
// Enable device and bus mastering
pci_enable_device(pci_dev);        // Sets bits 0, 1 (I/O, Memory enable)
pci_set_master(pci_dev);           // Sets bit 2 (Bus Master Enable)
```

#### 3. Status Register (0x06)

**Bit Fields:**
```
Bit 0-2: Reserved
Bit 3:   Capabilities List         (1=capabilities present)
Bit 4:   66 MHz Capable
Bit 5:   UDF Supported
Bit 6:   Fast Back-to-Back Capable
Bit 7:   Data Parity Detected
Bit 8-10: DEVSEL Timing
Bit 11:  Signaled Target Abort
Bit 12:  Received Target Abort
Bit 13:  Received Master Abort
Bit 14:  Signaled System Error
Bit 15:  Detected Parity Error
```

#### 4. Base Address Registers (BARs) - 0x10 to 0x27

BARs define where device memory and I/O registers are mapped in CPU address space.

**BAR Format:**
```
Bit 0:   Space Indicator          (0=Memory, 1=I/O Port)
For Memory (bit 0 = 0):
  Bit 1-2: Type                   (0=32-bit, 2=64-bit)
  Bit 3:   Prefetchable           (0=no, 1=yes)
  Bit 4-31: Base Address          (aligned to size)
```

**Reading BARs:**
```c
// Device writes 0xFFFFFFFF to BAR, then driver reads it back
// Device clears writable bits, leaving size/type info

u32 bar = pci_read_config_dword(pci_dev, PCI_BASE_ADDRESS_0);

// Example: If BAR reads as 0xFFFFF000:
// - Bit 0 = 0 → Memory space
// - Bits 4-11 cleared → 4KB memory region
// - Base address will be assigned by BIOS/kernel
```

**BAR Types:**
1. **Memory BAR (32-bit):** 32-bit memory address
2. **Memory BAR (64-bit):** Two consecutive BARs form 64-bit address
3. **I/O BAR:** 32-bit I/O port address (rare in modern devices)

**Example from WiFi Driver:**
```c
// From rt2x00pci.c
rt2x00dev->csr.base = pci_ioremap_bar(pci_dev, 0);
// Maps BAR 0 (MMIO space) into kernel virtual address space
```

#### 5. Class Code (0x08-0x0B)

Identifies device function:
```
Byte 0 (offset 0x0B): Base Class
  0x02 = Network Controller
  0x03 = Display Controller (GPU)
  0x04 = Multimedia Device
  0x06 = Bridge Device
  0x0C = Serial Bus Controller (USB, etc.)

Byte 1 (offset 0x0A): Sub-Class
  For Network: 0x80 = Other Network Controller
  For Network: 0x00 = Ethernet Controller
  For Network: 0x80 = 802.11 (WiFi)

Byte 2 (offset 0x09): Programming Interface
  Usually 0x00 for network devices
```

**WiFi Card Example:**
```
Class Code: 0x028000
- Base Class: 0x02 (Network Controller)
- Sub-Class: 0x80 (Other Network Controller)
- Interface: 0x00 (802.11)
```

#### 6. Capabilities Pointer (0x34)

Points to linked list of capability structures in extended config space:
```
Offset 0x34: Points to first capability (e.g., 0x40)

Capability Structure:
  Byte 0: Capability ID (e.g., 0x05 = MSI, 0x11 = MSI-X)
  Byte 1: Next capability pointer (0x00 = end of list)
  Byte 2+: Capability-specific data
```

**Common Capabilities:**
- **0x05:** MSI (Message Signaled Interrupts)
- **0x11:** MSI-X (Extended MSI)
- **0x10:** PCIe (PCI Express capability)
- **0x01:** Power Management

### Accessing Configuration Space

#### From Kernel Drivers

```c
// Read configuration registers
u16 vendor = pci_read_config_word(pci_dev, PCI_VENDOR_ID);
u16 device = pci_read_config_word(pci_dev, PCI_DEVICE_ID);
u8  class = pci_read_config_byte(pci_dev, PCI_CLASS_REVISION);

// Write configuration registers
pci_write_config_byte(pci_dev, PCI_INTERRUPT_LINE, irq);

// Read/write dword (4 bytes)
u32 bar = pci_read_config_dword(pci_dev, PCI_BASE_ADDRESS_0);
pci_write_config_dword(pci_dev, PCI_BASE_ADDRESS_0, new_value);
```

#### Configuration Space Access Mechanisms

**Traditional PCI:**
- Two special I/O ports: `0xCF8` (CONFIG_ADDRESS), `0xCFC` (CONFIG_DATA)
- CPU writes bus/device/function/register to 0xCF8
- CPU reads/writes data from/to 0xCFC

**PCI Express:**
- **ECAM (Enhanced Configuration Access Mechanism):** Memory-mapped config space
- Faster than I/O port method
- Direct memory access to config registers

---

## PCI Address Spaces

PCI devices can have up to three types of addressable regions:

### 1. Configuration Space
- **Size:** 256 bytes (PCI) or 4096 bytes (PCIe)
- **Purpose:** Device identification, resource assignment, capabilities
- **Access:** Via special configuration cycles (not regular memory/I/O)

### 2. I/O Port Space (Legacy)
- **Size:** 64 KB total (system-wide)
- **Purpose:** Device registers (legacy, rarely used now)
- **Access:** `inb()/outb()`, `inw()/outw()`, `inl()/outl()`
- **Example:**
```c
u8 value = inb(0x300);        // Read byte from I/O port 0x300
outb(0x55, 0x301);            // Write byte 0x55 to I/O port 0x301
```

**Modern devices rarely use I/O ports** - MMIO is preferred.

### 3. Memory-Mapped I/O (MMIO) Space
- **Size:** Large (typically 256 KB - 16 MB per device)
- **Purpose:** Device registers and frame buffers
- **Access:** Regular memory reads/writes
- **Example:**
```c
// Driver maps MMIO region
void __iomem *base = pci_ioremap_bar(pci_dev, 0);

// Access registers via memory-mapped addresses
u32 reg = ioread32(base + 0x100);      // Read register at offset 0x100
iowrite32(0x12345678, base + 0x104);   // Write to register at offset 0x104
```

**MMIO Advantages:**
- Faster than I/O ports (no special instructions)
- Can be cached (with care)
- Easier to program
- Supports larger address spaces

**MMIO Considerations:**
- **Write Posting:** CPU may continue before write reaches device
- **Solution:** Use read after write to flush (or memory barriers)
```c
iowrite32(value, reg);
ioread32(safe_reg);    // Flush posted write
```

### Address Translation

```
CPU Virtual Address Space
    ↓ (via ioremap)
CPU Physical Address Space
    ↓ (via Host Bridge/IOMMU)
PCI Bus Address Space
    ↓ (via device BAR)
Device Register/Memory
```

**Example Flow:**
```
1. BIOS/OS assigns physical address: 0xF0000000
2. Kernel maps to virtual address: 0xFFFF8800F0000000
3. Driver accesses: ioread32(0xFFFF8800F0000000 + offset)
4. CPU MMU translates to physical: 0xF0000000
5. Host bridge converts to PCI bus address
6. Device responds to bus address
```

---

## PCI Interrupts

PCI supports multiple interrupt mechanisms:

### 1. Legacy INTx Interrupts

**Shared Interrupt Lines:**
- **INTA#**, **INTB#**, **INTC#**, **INTD#** - 4 interrupt pins
- Multiple devices can share same interrupt line
- Polling required to identify which device asserted interrupt

**Interrupt Routing:**
```
PCI Device INTA# → PCI Bus → PCI Bridge → CPU Interrupt Controller
                                ↓
                        Routed to CPU IRQ (e.g., IRQ 11)
```

**Configuration:**
```c
// Read which INTx# pin device uses
u8 pin = pci_read_config_byte(pci_dev, PCI_INTERRUPT_PIN);
// Returns: 1=INTA#, 2=INTB#, 3=INTC#, 4=INTD#, 0=none

// Read assigned IRQ
int irq = pci_dev->irq;  // Kernel assigns during enumeration
```

**Driver Usage:**
```c
// Register interrupt handler
ret = request_irq(pci_dev->irq, 
                  rt2800mmio_interrupt,
                  IRQF_SHARED,           // Must use IRQF_SHARED for PCI
                  "rt2800pci",
                  rt2x00dev);
```

**Limitations:**
- Shared interrupts require checking device status
- Interrupt sharing can cause latency
- Limited to 4 interrupt sources per device

### 2. MSI (Message Signaled Interrupts)

**How MSI Works:**
- Device writes special message to special memory address
- CPU receives message as interrupt
- **Exclusive interrupt** - no sharing needed
- **No polling** - CPU knows exactly which device interrupted

**MSI Capability Structure:**
```
Offset 0x34 → Points to MSI capability (ID = 0x05)

MSI Capability (16 bytes):
  0x00: Capability ID (0x05) + Next Pointer
  0x02: Message Control Register
  0x04: Message Address Register (low 32 bits)
  0x08: Message Address Register (high 32 bits) - if 64-bit
  0x0C: Message Data Register
  0x10: Mask Bits (optional)
  0x14: Pending Bits (optional)
```

**Driver Usage:**
```c
// Enable MSI
int vectors = pci_alloc_irq_vectors(pci_dev, 1, 1, 
                                    PCI_IRQ_MSI | PCI_IRQ_MSIX);
if (vectors > 0) {
    int irq = pci_irq_vector(pci_dev, 0);
    request_irq(irq, handler, 0, "rt2800pci", dev);
}

// Device now uses MSI instead of INTx
```

**MSI Advantages:**
- Exclusive interrupt (no sharing)
- Lower latency
- No interrupt pin conflicts
- Supports multiple vectors (up to 32)

### 3. MSI-X (Extended MSI)

**Enhanced Version of MSI:**
- Supports **up to 2048 interrupt vectors** (vs 32 for MSI)
- Each vector has independent message address/data
- Vector table in device memory (not config space)
- Better for devices with multiple interrupt sources

**MSI-X Capability:**
```
MSI-X Capability:
  0x00: Capability ID (0x11) + Next Pointer
  0x02: Message Control Register
  0x04-0x08: Table Offset and BIR (BAR Indicator Register)
  0x0C: PBA (Pending Bit Array) Offset and BIR
```

**Driver Usage:**
```c
// Enable MSI-X
int vectors = pci_alloc_irq_vectors(pci_dev, 1, 32,
                                    PCI_IRQ_MSIX);

// Each vector can have different handler
for (i = 0; i < vectors; i++) {
    int irq = pci_irq_vector(pci_dev, i);
    request_irq(irq, handler[i], 0, name[i], dev);
}
```

**WiFi Driver Example:**
```c
// From rt2800pci driver
// Most modern WiFi cards support MSI/MSI-X
// Driver can use either:

if (pci_alloc_irq_vectors(pci_dev, 1, 1, PCI_IRQ_ALL_TYPES) > 0) {
    // MSI/MSI-X available and enabled
    rt2x00dev->irq = pci_irq_vector(pci_dev, 0);
} else {
    // Fall back to INTx
    rt2x00dev->irq = pci_dev->irq;
}
```

### Interrupt Handler Best Practices

```c
static irqreturn_t rt2800mmio_interrupt(int irq, void *dev_instance)
{
    struct rt2x00_dev *rt2x00dev = dev_instance;
    u32 reg;
    
    // 1. Read interrupt status register
    reg = rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR);
    
    // 2. Check if this device caused interrupt (for shared INTx)
    if (!(reg & INT_SOURCE_CSR_RX_DONE | INT_SOURCE_CSR_TX_DONE))
        return IRQ_NONE;  // Not our interrupt
    
    // 3. Acknowledge interrupt (clear status bits)
    rt2x00mmio_register_write(rt2x00dev, INT_SOURCE_CSR, reg);
    
    // 4. Schedule bottom half (tasklet/workqueue) for processing
    tasklet_schedule(&rt2x00dev->rxdone_tasklet);
    tasklet_schedule(&rt2x00dev->txdone_tasklet);
    
    return IRQ_HANDLED;
}
```

---

## PCI DMA Operations

### Direct Memory Access (DMA) Overview

DMA allows PCI devices to transfer data directly to/from system memory **without CPU involvement**, providing high-performance data transfers.

### DMA Address Spaces

```
┌─────────────────────────────────────────────────────┐
│         CPU Virtual Address Space                   │
│  (Driver uses: kmalloc, vmalloc, etc.)             │
│         Virtual Address: 0xFFFF880012345000        │
└────────────────────┬────────────────────────────────┘
                     │ CPU MMU translates
                     ↓
┌─────────────────────────────────────────────────────┐
│         CPU Physical Address Space                  │
│         Physical Address: 0x12345000               │
└────────────────────┬────────────────────────────────┘
                     │ PCI Host Bridge / IOMMU maps
                     ↓
┌─────────────────────────────────────────────────────┐
│         PCI Bus Address Space                       │
│         Bus Address: 0x12345000 (or different)     │
└────────────────────┬────────────────────────────────┘
                     │
                     ↓
┌─────────────────────────────────────────────────────┐
│         Device DMA Engine                           │
│  Reads/writes data directly from/to memory         │
└─────────────────────────────────────────────────────┘
```

### DMA Types

#### 1. **Coherent DMA (Synchronous)**

**Characteristics:**
- CPU and device see **same memory contents** immediately
- Cache-coherent (no cache flushes needed)
- Used for **control structures** (descriptors, status blocks)

**Usage:**
```c
// Allocate coherent DMA buffer
void *coherent_buf;
dma_addr_t dma_handle;

coherent_buf = pci_alloc_consistent(pci_dev, 
                                     size,      // Buffer size
                                     &dma_handle); // Bus address

// Get bus address for device
dma_addr_t bus_addr = dma_handle;

// Device can now DMA to/from this address
// CPU and device always see same data (no cache issues)

// Free when done
pci_free_consistent(pci_dev, size, coherent_buf, dma_handle);
```

**Modern API (Recommended):**
```c
coherent_buf = dma_alloc_coherent(&pci_dev->dev, size, 
                                   &dma_handle, 
                                   GFP_KERNEL);
dma_free_coherent(&pci_dev->dev, size, coherent_buf, dma_handle);
```

#### 2. **Streaming DMA (Asynchronous)**

**Characteristics:**
- Used for **large data transfers** (packets, frames)
- Cache may need flushing
- More efficient than coherent DMA
- Requires explicit cache management

**Usage:**
```c
struct sk_buff *skb;
dma_addr_t dma_handle;

// Map buffer for DMA transfer
dma_handle = pci_map_single(pci_dev,
                            skb->data,      // Virtual address
                            skb->len,       // Length
                            PCI_DMA_TODEVICE); // Direction

// Device can now DMA from this address
// Program device with bus address
write_device_dma_address(device, dma_handle);

// After DMA completes, unmap
pci_unmap_single(pci_dev, dma_handle, skb->len, PCI_DMA_TODEVICE);
```

**DMA Directions:**
```c
PCI_DMA_BIDIRECTIONAL  // Both directions
PCI_DMA_TODEVICE       // CPU → Device (transmit)
PCI_DMA_FROMDEVICE     // Device → CPU (receive)
PCI_DMA_NONE           // Invalid (debugging)
```

**Modern API:**
```c
dma_handle = dma_map_single(&pci_dev->dev, skb->data, 
                            skb->len, DMA_TO_DEVICE);
dma_unmap_single(&pci_dev->dev, dma_handle, 
                 skb->len, DMA_TO_DEVICE);
```

### DMA Descriptors (WiFi Driver Example)

WiFi drivers use DMA descriptors - control structures that tell hardware where data is:

```c
// Descriptor structure (in coherent memory)
struct tx_descriptor {
    dma_addr_t buffer_address;  // Bus address of packet data
    u32 length;                  // Packet length
    u32 flags;                   // Control flags
    u32 status;                  // Completion status
};

// Allocate descriptor ring (coherent DMA)
struct tx_descriptor *desc_ring;
dma_addr_t desc_ring_dma;

desc_ring = dma_alloc_coherent(&pci_dev->dev,
                               sizeof(*desc_ring) * NUM_DESCRIPTORS,
                               &desc_ring_dma,
                               GFP_KERNEL);

// Allocate packet buffers (streaming DMA)
for (i = 0; i < NUM_DESCRIPTORS; i++) {
    struct sk_buff *skb = alloc_skb(MAX_PACKET_SIZE, GFP_KERNEL);
    
    // Map buffer for DMA
    dma_addr_t buf_dma = dma_map_single(&pci_dev->dev,
                                        skb->data,
                                        skb->len,
                                        DMA_TO_DEVICE);
    
    // Fill descriptor
    desc_ring[i].buffer_address = cpu_to_le32(buf_dma);
    desc_ring[i].length = cpu_to_le32(skb->len);
    desc_ring[i].flags = cpu_to_le32(TX_FLAG_VALID);
}

// Tell hardware about descriptor ring
iowrite32(desc_ring_dma, device_base + TX_DESCRIPTOR_RING);
iowrite32(NUM_DESCRIPTORS, device_base + TX_DESCRIPTOR_COUNT);
iowrite32(1, device_base + TX_ENABLE);
```

### DMA Mask Setting

**Purpose:** Tell kernel what address range device can access

```c
// Set DMA mask (maximum address device can access)
// WiFi cards typically 32-bit (4GB limit)
if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) {
    // Device can only access addresses below 4GB
    dev_err(&pci_dev->dev, "32-bit DMA not supported\n");
    return -EIO;
}

// For 64-bit devices
if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(64))) {
    // Device can access full 64-bit address space
}

// Also set coherent mask (for coherent DMA buffers)
dma_set_coherent_mask(&pci_dev->dev, DMA_BIT_MASK(32));
```

**WiFi Driver Example:**
```c
// From rt2x00pci_probe()
if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) {
    rt2x00_probe_err("PCI DMA not supported\n");
    retval = -EIO;
    goto exit_release_regions;
}
```

### Scatter-Gather DMA

For non-contiguous buffers:

```c
struct scatterlist sg[16];
int nents;

// Prepare scatter-gather list
nents = sg_nents(skb->data);

// Map scatter-gather list
nents = dma_map_sg(&pci_dev->dev, sg, nents, DMA_TO_DEVICE);

// Program device with SG list
for (i = 0; i < nents; i++) {
    dma_addr_t addr = sg_dma_address(&sg[i]);
    size_t len = sg_dma_len(&sg[i]);
    // Program device descriptor with addr/len
}

// Unmap when done
dma_unmap_sg(&pci_dev->dev, sg, nents, DMA_TO_DEVICE);
```

---

## PCI Power Management

### Power States (D-States)

```
D0 (Full On):      Full power, device fully operational
D1 (Low Power):    Reduced power, some context preserved
D2 (Lower Power):  More reduced power, more context lost
D3hot (Hot Standby): Powered but not responding
D3cold (Off):      No power, all context lost (requires full reinit)
```

### PCI Power Management Registers

**Power Management Capability Structure:**
```
Offset: Capability Pointer → PM Capability (ID = 0x01)

PM Capability (24 bytes):
  0x00: Capability ID (0x01) + Next Pointer
  0x02: PM Capabilities Register
  0x04: PM Control/Status Register
  0x08: Bridge Support Extensions (if bridge)
  0x0C: Data Register (optional)
```

**PM Control/Status Register:**
```
Bits 0-1:  Power State          (0=D0, 1=D1, 2=D2, 3=D3)
Bit 3:     No Soft Reset        (1=no reset on D0→D3hot→D0)
Bit 8:     PME Enable           (1=enable power management events)
Bit 15:    PME Status           (1=PME asserted)
```

### Driver Power Management

```c
// Set power state
int pci_set_power_state(struct pci_dev *dev, pci_power_t state);

// Examples:
pci_set_power_state(pci_dev, PCI_D0);   // Full power on
pci_set_power_state(pci_dev, PCI_D3hot); // Suspend

// Suspend callback (called by kernel during system suspend)
static int rt2x00pci_suspend(struct device *dev)
{
    struct ieee80211_hw *hw = dev_get_drvdata(dev);
    struct rt2x00_dev *rt2x00dev = hw->priv;
    
    // 1. Stop device operations
    rt2x00lib_suspend(rt2x00dev);
    
    // 2. Save device state (if needed)
    // 3. Set power state to D3
    pci_set_power_state(to_pci_dev(dev), PCI_D3hot);
    
    return 0;
}

// Resume callback
static int rt2x00pci_resume(struct device *dev)
{
    struct ieee80211_hw *hw = dev_get_drvdata(dev);
    struct rt2x00_dev *rt2x00dev = hw->priv;
    
    // 1. Set power state to D0
    pci_set_power_state(to_pci_dev(dev), PCI_D0);
    
    // 2. Restore device state
    // 3. Reinitialize device
    rt2x00lib_resume(rt2x00dev);
    
    return 0;
}
```

### PCIe Active State Power Management (ASPM)

PCIe devices can enter low-power states **while link is active**:

```
L0:  Full power, active state
L0s: Standby (very fast transition, ~1μs)
L1:  Low power (faster transition, ~10μs)
L2/L3: Lower power states (slower, requires reinit)
```

**Kernel controls ASPM automatically** - drivers typically don't need to manage it.

---

## Linux PCI Driver Framework

### Driver Registration

#### 1. Define Device ID Table

```c
// List of supported devices
static const struct pci_device_id rt2800pci_device_table[] = {
    { PCI_DEVICE(0x1814, 0x0601) },  // Vendor:Device
    { PCI_DEVICE(0x1814, 0x0681) },
    { PCI_DEVICE(0x1814, 0x3090) },  // RT3090 WiFi card
    { PCI_DEVICE(0x1814, 0x3091) },  // RT3091
    { PCI_DEVICE(0x1814, 0x3092) },  // RT3092
    { 0, }  // Terminator
};
```

**PCI_DEVICE Macro:**
```c
#define PCI_DEVICE(vend, dev) \
    .vendor = (vend), .device = (dev), \
    .subvendor = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
    .class = 0, .class_mask = 0, \
    .driver_data = 0
```

#### 2. Define Driver Structure

```c
static struct pci_driver rt2800pci_driver = {
    .name       = KBUILD_MODNAME,      // "rt2800pci"
    .id_table   = rt2800pci_device_table,
    .probe      = rt2800pci_probe,     // Called when device found
    .remove     = rt2x00pci_remove,    // Called when device removed
    .driver.pm  = &rt2x00pci_pm_ops,   // Power management callbacks
};
```

#### 3. Register Driver

```c
// Macro that registers driver
module_pci_driver(rt2800pci_driver);

// Expands to:
static int __init rt2800pci_init(void)
{
    return pci_register_driver(&rt2800pci_driver);
}
module_init(rt2800pci_init);

static void __exit rt2800pci_exit(void)
{
    pci_unregister_driver(&rt2800pci_driver);
}
module_exit(rt2800pci_exit);
```

### Probe Function (Device Initialization)

**Called when PCI core finds a matching device:**

```c
static int rt2800pci_probe(struct pci_dev *pci_dev,
                           const struct pci_device_id *id)
{
    struct ieee80211_hw *hw;
    struct rt2x00_dev *rt2x00dev;
    int retval;
    
    // Step 1: Enable PCI device
    retval = pci_enable_device(pci_dev);
    if (retval) {
        rt2x00_probe_err("Enable device failed\n");
        return retval;
    }
    // This enables I/O and Memory spaces, allocates IRQ
    
    // Step 2: Request MMIO/IOP regions
    retval = pci_request_regions(pci_dev, pci_name(pci_dev));
    if (retval) {
        rt2x00_probe_err("PCI request regions failed\n");
        goto exit_disable_device;
    }
    // This reserves BAR address ranges
    
    // Step 3: Enable bus mastering (for DMA)
    pci_set_master(pci_dev);
    // Sets bit 2 in Command Register (Bus Master Enable)
    
    // Step 4: Enable Memory-Write-Invalidate (optional optimization)
    if (pci_set_mwi(pci_dev))
        rt2x00_probe_err("MWI not available\n");
    
    // Step 5: Set DMA mask
    if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) {
        rt2x00_probe_err("PCI DMA not supported\n");
        retval = -EIO;
        goto exit_release_regions;
    }
    // Device can only DMA to addresses below 4GB
    
    // Step 6: Allocate driver data structures
    hw = ieee80211_alloc_hw(sizeof(struct rt2x00_dev), ops->hw);
    if (!hw) {
        retval = -ENOMEM;
        goto exit_release_regions;
    }
    
    // Step 7: Store device pointer
    pci_set_drvdata(pci_dev, hw);
    rt2x00dev = hw->priv;
    rt2x00dev->dev = &pci_dev->dev;
    rt2x00dev->ops = ops;
    rt2x00dev->hw = hw;
    rt2x00dev->irq = pci_dev->irq;  // Assigned IRQ
    
    // Step 8: Map MMIO registers
    retval = rt2x00pci_alloc_reg(rt2x00dev);
    if (retval)
        goto exit_free_device;
    // Maps BAR 0 to virtual address space
    
    // Step 9: Initialize device-specific code
    retval = rt2x00lib_probe_dev(rt2x00dev);
    if (retval)
        goto exit_free_reg;
    
    return 0;
    
exit_free_reg:
    rt2x00pci_free_reg(rt2x00dev);
exit_free_device:
    ieee80211_free_hw(hw);
exit_release_regions:
    pci_clear_mwi(pci_dev);
    pci_release_regions(pci_dev);
exit_disable_device:
    pci_disable_device(pci_dev);
    return retval;
}
```

### Remove Function (Device Cleanup)

**Called when device is removed or driver unloaded:**

```c
void rt2x00pci_remove(struct pci_dev *pci_dev)
{
    struct ieee80211_hw *hw = pci_get_drvdata(pci_dev);
    struct rt2x00_dev *rt2x00dev = hw->priv;
    
    // Step 1: Stop device operations
    rt2x00lib_remove_dev(rt2x00dev);
    
    // Step 2: Free MMIO mappings
    rt2x00pci_free_reg(rt2x00dev);
    
    // Step 3: Free driver data
    ieee80211_free_hw(hw);
    
    // Step 4: Disable bus mastering
    pci_clear_mwi(pci_dev);
    
    // Step 5: Disable device
    pci_disable_device(pci_dev);
    
    // Step 6: Release regions
    pci_release_regions(pci_dev);
}
```

### Device Discovery Process

```
1. System Boot / Device Insertion
   ↓
2. PCI BIOS/Firmware scans buses
   ↓
3. For each device:
   - Reads Vendor ID / Device ID
   - Assigns bus/device/function number
   - Allocates resources (IRQ, MMIO addresses)
   ↓
4. Linux PCI subsystem enumerates devices
   ↓
5. For each registered driver:
   - Compares device ID with driver's id_table
   - If match found → calls driver's .probe()
   ↓
6. Driver initializes device
```

---

## WiFi PCI Driver Implementation

### Complete Driver Structure

Using `rt2800pci` as example:

```c
// File: rt2800pci.c

// 1. Device ID Table
static const struct pci_device_id rt2800pci_device_table[] = {
    { PCI_DEVICE(0x1814, 0x3090) },  // Ralink RT3090
    { PCI_DEVICE(0x1814, 0x3091) },  // Ralink RT3091
    { PCI_DEVICE(0x1814, 0x3092) },  // Ralink RT3092
    // ... more devices ...
    { 0, }
};

// 2. Probe Function
static int rt2800pci_probe(struct pci_dev *pci_dev,
                           const struct pci_device_id *id)
{
    return rt2x00pci_probe(pci_dev, &rt2800pci_ops);
}

// 3. Driver Registration
static struct pci_driver rt2800pci_driver = {
    .name       = KBUILD_MODNAME,
    .id_table   = rt2800pci_device_table,
    .probe      = rt2800pci_probe,
    .remove     = rt2x00pci_remove,
    .driver.pm  = &rt2x00pci_pm_ops,
};

module_pci_driver(rt2800pci_driver);
```

### MMIO Register Access

```c
// From rt2x00pci.c

// Map MMIO region (BAR 0)
static int rt2x00pci_alloc_reg(struct rt2x00_dev *rt2x00dev)
{
    struct pci_dev *pci_dev = to_pci_dev(rt2x00dev->dev);
    
    // Map BAR 0 (device registers) to kernel virtual address
    rt2x00dev->csr.base = pci_ioremap_bar(pci_dev, 0);
    if (!rt2x00dev->csr.base)
        return -ENOMEM;
    
    // Now driver can access registers via:
    // rt2x00mmio_register_read(rt2x00dev, offset)
    // rt2x00mmio_register_write(rt2x00dev, offset, value)
    
    return 0;
}

// Register access functions
static inline void rt2x00mmio_register_write(struct rt2x00_dev *rt2x00dev,
                                             const unsigned int offset,
                                             u32 value)
{
    iowrite32(value, rt2x00dev->csr.base + offset);
}

static inline u32 rt2x00mmio_register_read(struct rt2x00_dev *rt2x00dev,
                                           const unsigned int offset)
{
    return ioread32(rt2x00dev->csr.base + offset);
}
```

### Interrupt Handling

```c
// Interrupt handler
static irqreturn_t rt2800mmio_interrupt(int irq, void *dev_instance)
{
    struct rt2x00_dev *rt2x00dev = dev_instance;
    u32 reg;
    
    // Read interrupt status
    reg = rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR);
    
    // Check interrupt sources
    if (reg & INT_SOURCE_CSR_TX_DONE) {
        tasklet_schedule(&rt2x00dev->txdone_tasklet);
    }
    
    if (reg & INT_SOURCE_CSR_RX_DONE) {
        tasklet_schedule(&rt2x00dev->rxdone_tasklet);
    }
    
    // Acknowledge interrupt
    rt2x00mmio_register_write(rt2x00dev, INT_SOURCE_CSR, reg);
    
    return IRQ_HANDLED;
}

// Register interrupt (in probe)
retval = request_irq(rt2x00dev->irq,
                     rt2800mmio_interrupt,
                     IRQF_SHARED,
                     rt2x00dev->name,
                     rt2x00dev);
```

### DMA Operations

```c
// Transmit DMA setup
int rt2x00queue_write_tx_frame(struct data_queue *queue,
                               struct sk_buff *skb,
                               struct ieee80211_sta *sta,
                               bool immediate)
{
    struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
    struct queue_entry *entry;
    dma_addr_t dma_addr;
    
    // Get available TX queue entry
    entry = rt2x00queue_get_entry(queue, Q_INDEX);
    
    // Map packet buffer for DMA
    dma_addr = dma_map_single(rt2x00dev->dev,
                              skb->data,
                              skb->len,
                              DMA_TO_DEVICE);
    
    // Fill TX descriptor
    rt2800mmio_write_tx_desc(entry, txdesc);
    
    // Program hardware with DMA address
    entry->skb = skb;
    entry->flags = ENTRY_OWNED_DEVICE;
    
    // Kick hardware (start transmission)
    rt2x00queue_kick(queue);
    
    return 0;
}

// Receive DMA setup
// Driver pre-allocates RX buffers and maps them
void rt2x00queue_init_queues(struct rt2x00_dev *rt2x00dev)
{
    // Allocate RX buffers
    for (i = 0; i < queue->limit; i++) {
        struct sk_buff *skb = dev_alloc_skb(queue->data_size);
        
        // Map for DMA
        dma_addr_t dma_addr = dma_map_single(rt2x00dev->dev,
                                             skb->data,
                                             queue->data_size,
                                             DMA_FROM_DEVICE);
        
        // Fill RX descriptor
        entry = rt2x00queue_get_entry(queue, i);
        entry->skb = skb;
        entry->dma = dma_addr;
        
        // Give buffer to hardware
        rt2x00mmio_write_rx_desc(queue, entry);
    }
}
```

---

## Complete Driver Lifecycle Example

### Device Insertion Flow

```
1. User inserts PCIe WiFi card
   ↓
2. PCIe hotplug event
   ↓
3. PCI subsystem detects new device
   ↓
4. Reads configuration space:
   - Vendor ID: 0x1814 (Ralink)
   - Device ID: 0x3090 (RT3090)
   - Class Code: 0x028000 (Network Controller)
   ↓
5. Scans registered drivers
   ↓
6. Matches against rt2800pci_device_table
   ↓
7. Calls rt2800pci_probe()
   ↓
8. Probe sequence:
   a. pci_enable_device()          // Enable device
   b. pci_request_regions()        // Reserve MMIO space
   c. pci_set_master()              // Enable DMA
   d. dma_set_mask()                // Set DMA capability
   e. pci_ioremap_bar()             // Map registers
   f. Read device configuration     // EEPROM, capabilities
   g. Allocate DMA buffers          // TX/RX descriptors
   h. Register interrupt handler    // request_irq()
   i. Register with mac80211        // ieee80211_register_hw()
   j. Create network interface      // wlan0
   ↓
9. Device ready for use
```

### Normal Operation Flow

```
Application sends data
   ↓
Network stack (IP layer)
   ↓
Network device (ndo_start_xmit)
   ↓
MAC80211 (802.11 frame creation)
   ↓
Driver tx() callback
   ↓
Driver operations:
   a. Map packet buffer for DMA      // dma_map_single()
   b. Fill TX descriptor             // DMA address, length
   c. Write descriptor to hardware   // via MMIO
   d. Kick hardware                  // Start DMA
   ↓
Hardware DMA engine:
   a. Reads descriptor
   b. Reads packet from system RAM
   c. Transmits over radio
   d. Generates interrupt when done
   ↓
Interrupt handler:
   a. Reads interrupt status
   b. Processes completed TX
   c. Unmaps DMA buffers             // dma_unmap_single()
   d. Frees sk_buff
   e. Notifies network stack         // ieee80211_tx_status()
```

### Device Removal Flow

```
1. User removes card / Driver unload
   ↓
2. PCI subsystem detects removal
   ↓
3. Calls driver remove()
   ↓
4. Remove sequence:
   a. Unregister from mac80211       // ieee80211_unregister_hw()
   b. Stop all operations             // Stop queues, disable radio
   c. Free interrupt                  // free_irq()
   d. Unmap DMA buffers               // dma_unmap_*()
   e. Free DMA buffers                // dma_free_*()
   f. Unmap MMIO                      // iounmap()
   g. Release regions                 // pci_release_regions()
   h. Disable device                  // pci_disable_device()
   i. Free driver structures
   ↓
5. Device removed
```

---

## Summary

### Key Concepts Recap

| Concept | Description |
|---------|-------------|
| **PCI Configuration Space** | 256-byte (or 4KB) register set for device identification and configuration |
| **BAR (Base Address Register)** | Defines where device MMIO/I/O registers are mapped in CPU address space |
| **MMIO (Memory-Mapped I/O)** | Device registers accessible as memory addresses (preferred method) |
| **DMA (Direct Memory Access)** | Device directly accesses system memory without CPU (high performance) |
| **INTx / MSI / MSI-X** | Interrupt mechanisms (shared pins vs. message-signaled) |
| **Bus Master** | Device can initiate DMA transfers (must be enabled) |
| **Power Management** | D-states for power saving (D0=full power, D3=off) |

### WiFi Driver PCI Operations

1. **Device Discovery:**
   - Kernel matches Vendor/Device ID from config space
   - Calls driver's `probe()` function

2. **Resource Allocation:**
   - MMIO regions (via BARs)
   - Interrupt lines (IRQ assignment)
   - DMA buffers (coherent and streaming)

3. **Register Access:**
   - Map BAR to virtual address (`pci_ioremap_bar`)
   - Access registers via `ioread32()/iowrite32()`

4. **Data Transfer:**
   - Map packet buffers for DMA
   - Program hardware with DMA addresses
   - Hardware performs transfer autonomously
   - Interrupt signals completion

5. **Interrupt Handling:**
   - Hardware generates interrupt
   - Driver reads status register
   - Processes completed operations
   - Schedules bottom-half processing

### Benefits of PCI for WiFi Drivers

1. **Standardized Interface:**
   - Common API across all PCI devices
   - Kernel handles resource allocation
   - Automatic device discovery

2. **High Performance:**
   - Direct memory access (DMA)
   - Efficient interrupt handling (MSI/MSI-X)
   - Memory-mapped registers (fast access)

3. **Hot-Plug Support:**
   - Add/remove devices without reboot (PCIe)
   - Automatic driver binding

4. **Power Management:**
   - Standardized power states
   - System-level power saving

5. **Scalability:**
   - PCIe scales from x1 to x32 lanes
   - Bandwidth proportional to lanes

### Linux PCI API Summary

**Essential Functions:**
```c
// Device management
pci_enable_device()           // Enable device
pci_disable_device()          // Disable device
pci_set_master()              // Enable DMA
pci_request_regions()         // Reserve resources
pci_release_regions()         // Release resources

// Configuration space
pci_read_config_byte/word/dword()
pci_write_config_byte/word/dword()

// Resource access
pci_ioremap_bar()             // Map MMIO
pci_resource_start()          // Get BAR address
pci_resource_len()            // Get BAR size

// DMA
dma_set_mask()                // Set DMA capability
dma_alloc_coherent()          // Allocate coherent DMA
dma_map_single()              // Map buffer for DMA
pci_alloc_irq_vectors()       // Enable MSI/MSI-X

// Power management
pci_set_power_state()         // Set power state
```

---

## Conclusion

PCI (and its modern PCIe evolution) provides a robust, standardized interface for connecting peripheral devices like WiFi cards to computer systems. Understanding PCI hardware architecture, bus operations, and Linux driver integration is essential for developing reliable, high-performance device drivers.

WiFi PCI drivers leverage PCI's capabilities - DMA for high-speed data transfer, MMIO for register access, MSI/MSI-X for efficient interrupts, and power management for battery life - to provide seamless wireless connectivity while maintaining excellent performance.

The Linux PCI framework abstracts much of the complexity, allowing drivers to focus on device-specific functionality while the kernel handles resource allocation, device enumeration, and bus management.

---

## Additional Resources

- **Linux PCI Documentation:** `Documentation/PCI/pci.rst`
- **PCI Driver API:** `Documentation/driver-api/pci/`
- **DMA API:** `Documentation/core-api/dma-api.rst`
- **WiFi Driver Code:** `drivers/net/wireless/ralink/rt2x00/`
- **PCI Specifications:** PCI-SIG website (www.pcisig.com)
- **Linux Device Drivers (LDD3):** Available online at lwn.net/Kernel/LDD3/

---

*Document Generated: 2024*
*Based on Linux Kernel Source Analysis*
