# rt2x00 WiFi PCI Driver: Probe, Init, TX/RX, and Interrupt Flow

This document describes in detail how the **rt2x00-2.0.0-b3** WiFi PCI driver probes the card, initializes it, configures hardware, hooks into the network stack, sends packets from the IP layer through the WiFi card, receives packets from the card up to the IP layer, and handles interrupts. All code references are from the `rt2x00-2.0.0-b3` source tree.

---

## Table of Contents

1. [Overview](#1-overview)
2. [PCI Probe and Device Discovery](#2-pci-probe-and-device-discovery)
3. [Initialization and Configuration](#3-initialization-and-configuration)
4. [Callback and Hook Registration](#4-callback-and-hook-registration)
5. [TX Path: IP Layer → WiFi Card](#5-tx-path-ip-layer--wifi-card)
6. [RX Path: WiFi Card → IP Layer](#6-rx-path-wifi-card--ip-layer)
7. [Interrupt Handling](#7-interrupt-handling)
8. [Data Structures and Rings](#8-data-structures-and-rings)
9. [Summary Diagrams](#9-summary-diagrams)
10. [SSID Discovery (Scanning), Encryption, and Connecting to an SSID](#10-ssid-discovery-scanning-encryption-and-connecting-to-an-ssid)

---

## 1. Overview

### 1.1 Driver Layout

The rt2x00-2.0.0-b3 driver consists of:

| Component | Files | Role |
|-----------|-------|------|
| **PCI layer** | `rt2400pci.c`, `rt2500pci.c`, `rt2x00pci.h` | PCI probe/remove, MMIO, DMA rings, interrupt, device-specific init |
| **Core** | `rt2x00core.c`, `rt2x00core.h` | net_device lifecycle, TX/RX workqueues, ieee80211 glue, config |
| **Device structs** | `rt2x00.h`, `rt2x00dev.h` | Shared types, capabilities, ring helpers |
| **802.11 stack** | `ieee80211/*` | `ieee80211_xmit`, `ieee80211_rx`, management, encryption |

The **network device** is an `alloc_ieee80211()` net_device. The IP layer uses it like any other Ethernet-style interface. The driver plugs into the legacy **ieee80211** stack (not mac80211) via `ieee80211->hard_start_xmit` and related callbacks.

### 1.2 Supported Hardware (rt2400pci)

- **Chipset:** Ralink RT2460 (802.11b)
- **PCI IDs:** `0x1814:0x0101` (see `rt2400pci.c` `rt2x00_device_pci_tbl`)

---

## 2. PCI Probe and Device Discovery

### 2.1 Module Init and Driver Registration

```c
// rt2400pci.c

static int __init rt2x00_pci_init(void)
{
    printk(KERN_INFO "Loading module: %s\n", version);
    return pci_register_driver(&rt2x00_pci_driver);
}

static struct pci_driver rt2x00_pci_driver = {
    .name       = DRV_NAME,              // "rt2400pci"
    .id_table   = rt2x00_device_pci_tbl,
    .probe      = rt2x00_pci_probe,
    .remove     = rt2x00_pci_remove,
    .suspend    = rt2x00_pci_suspend,    // CONFIG_PM
    .resume     = rt2x00_pci_resume,
};

static struct pci_device_id rt2x00_device_pci_tbl[] = {
    { PCI_DEVICE(0x1814, 0x0101), .driver_data = RT2460 },
    { 0, }
};
```

- **`pci_register_driver()`** registers the driver with the PCI subsystem.
- When the PCI core finds a device matching `rt2x00_device_pci_tbl`, it calls **`rt2x00_pci_probe()`**.

### 2.2 Probe Flow: `rt2x00_pci_probe()`

`rt2x00_pci_probe()` (in `rt2400pci.c`) does the following:

```
1. Validate driver_data (RT2460)
2. pci_enable_device(pci_dev)     → enable device, I/O and memory space
3. pci_set_master(pci_dev)        → enable bus mastering (DMA)
4. pci_set_mwi(pci_dev)           → Memory-Write-Invalidate (optional)
5. pci_set_dma_mask(64-bit then 32-bit)  → DMA addressing
6. pci_request_regions(pci_dev)   → reserve BARs (MMIO)
7. rt2x00_core_probe(...)         → allocate net_device, run dev_probe, register netdev
8. net_dev->irq = pci_dev->irq    → store IRQ for later use
9. pci_set_drvdata(pci_dev, net_dev)
```

If any step fails, the probe unwinds (release regions, disable device, etc.) and returns an error.

**Important:** **`rt2x00_dev_probe()`** runs during **core probe** (at load time) and does MMIO mapping, EEPROM, and MAC read. **DMA rings, BBP init, and the IRQ** are set up later in **`rt2x00_dev_radio_on()`**, which runs when the interface is brought up (`ifconfig wlan0 up`).

### 2.3 Core Probe: `rt2x00_core_probe()`

`rt2x00_core_probe()` (in `rt2x00core.c`) allocates the net_device and wires the driver into the stack:

```
1. Check handler has all required callbacks (dev_radio_on, dev_radio_off, dev_update_config, ...).
2. net_dev = alloc_ieee80211(sizeof_dev + sizeof(device) + sizeof(core))
   → alloc_etherdev + ieee80211 allocation; dev->hard_start_xmit = ieee80211_xmit.
3. device = ieee80211_priv(net_dev), core = (void*)device + sizeof(*device).
4. Initialize device, core, handler, workqueue, packet rings (rx, tx, atim, prio, beacon).
5. rt2x00_init_config(core).
6. handler->dev_probe(device, &core->config, priv)  → rt2x00_dev_probe()
7. Set ieee80211 callbacks (hard_start_xmit, handle_*, set_security, etc.).
8. net_dev->open = rt2x00_open, ->stop = rt2x00_stop, ->tx_timeout = rt2x00_tx_timeout, etc.
9. register_netdev(net_dev).
10. set_bit(DEVICE_AWAKE), rt2x00_activate_config(device).
```

So **`rt2x00_dev_probe()`** is the first device-specific hook. It runs during **core probe**, i.e. at **module load / PCI probe** time, **before** `ifconfig up`.

---

## 3. Initialization and Configuration

### 3.1 Device Probe: `rt2x00_dev_probe()`

`rt2x00_dev_probe()` (in `rt2400pci.c`) runs during `rt2x00_core_probe()`:

```
1. priv = pci_dev; clear rt2x00pci; set rx/tx/atim/prio/beacon .data_addr = NULL.
2. csr_addr = ioremap(pci_resource_start(pci_dev, 0), pci_resource_len(pci_dev, 0))
   → map BAR0 (MMIO) into kernel virtual address space.
3. rt2x00_init_eeprom(rt2x00pci, config)
   → detect EEPROM width, read RF type, antenna config, BBP data from EEPROM.
4. rt2x00_init_read_mac(rt2x00pci, device->net_dev)
   → read MAC address from CSR3/CSR4 into net_dev->dev_addr.
5. Reject unsupported RF (e.g. must be RF2420 or RF2421).
6. set_bit(DEVICE_CAP_802_11B).
```

**MMIO access** uses `rt2x00_register_read` / `rt2x00_register_write` (in `rt2x00pci.h`), which wrap `readl` / `writel` on `csr_addr + offset`. BBP and RF are accessed indirectly via `BBPCSR` / `RFCSR` with busy-wait.

### 3.2 Radio On: `rt2x00_dev_radio_on()`

When the user runs `ifconfig wlan0 up`, the net_device **`open`** callback runs:

```c
// rt2x00core.c
net_dev->open = rt2x00_open;
```

`rt2x00_open()` calls **`rt2x00_radio_on(device)`**, which:

1. **`rt2x00_enable_ring()`** for **rx, tx, atim, prio, beacon** (packet rings).
2. Calls **`handler->dev_radio_on(device)`** → **`rt2x00_dev_radio_on()`** (in `rt2400pci.c`).
3. Sets **`DEVICE_RADIO_ON`**.

**`rt2x00_dev_radio_on()`** is where **DMA rings, hardware init, and the interrupt handler** are set up:

```
1. rt2x00_pci_alloc_rings(device)
   → dma_alloc_coherent for rx, tx, atim, prio, beacon rings (descriptor + data).
2. rt2x00_clear_ring() for each ring
   → zero rings; for RX: set RXD W0 (OWNER_NIC=1), W1 (buffer addr), W2 (length);
     for TX: set TXD W0 (VALID=0, OWNER_NIC=0), W1, W2.
3. rt2x00_init_ring_register(rt2x00pci)
   → write TXCSR2–TXCSR6, RXCSR1–RXCSR2 with ring sizes and DMA addresses.
4. rt2x00_init_registers(rt2x00pci)
   → PWRCSR0, PSCSR0–3, TIMECSR, CSR9, CNT3, RXCSR0, MACCSR0–2, RXCSR3, RALINKCSR, LEDCSR,
     then CSR1 soft reset and CSR1 host ready.
5. rt2x00_init_write_mac(rt2x00pci, net_dev)
   → write MAC address to CSR3/CSR4.
6. rt2x00_init_bbp(rt2x00pci)
   → write BBP init values (and EEPROM BBP overrides).
7. Read CSR7, then write it back to clear any pending interrupts.
8. request_irq(pci_dev->irq, rt2x00_interrupt, SA_SHIRQ, net_dev->name, device)
   → register shared IRQ; dev_id = device.
9. Enable interrupts in CSR8 (clear mask bits for TBCN_EXPIRE, TXDONE_*, RXDONE).
```

If any step fails, `rt2x00_dev_radio_on()` frees the rings and returns an error; the interface does not come up.

### 3.3 Configuration Updates

At runtime, configuration changes (channel, rate, BSSID, etc.) go through **`rt2x00_update_config()`** → **`handler->dev_update_config()`** → **`rt2x00_dev_update_config()`**. It dispatches on `update_flags` and updates BBP/RF/CSR as needed (e.g. `UPDATE_CHANNEL` → `rt2x00_dev_update_channel`).

---

## 4. Callback and Hook Registration

### 4.1 PCI / Core Handler Table

The PCI driver provides a **handler** table to the core:

```c
// rt2400pci.c
static struct _rt2x00_dev_handler rt2x00_pci_handler = {
    .dev_module        = THIS_MODULE,
    .dev_probe         = rt2x00_dev_probe,
    .dev_remove        = rt2x00_dev_remove,
    .dev_radio_on      = rt2x00_dev_radio_on,
    .dev_radio_off     = rt2x00_dev_radio_off,
    .dev_update_config = rt2x00_dev_update_config,
    .dev_update_stats  = rt2x00_dev_update_stats,
    .dev_test_tx       = rt2x00_dev_test_tx,
    .dev_xmit_packet   = rt2x00_dev_xmit_packet,
};
```

This is passed to **`rt2x00_core_probe(&rt2x00_pci_handler, pci_dev, ...)`**. The core stores `device->handler` and calls these callbacks at the appropriate times.

### 4.2 ieee80211 Hooks

During **`rt2x00_core_probe()`**, the core overrides ieee80211 callbacks:

```c
core->ieee80211->hard_start_xmit = rt2x00_start_xmit;
core->ieee80211->set_security    = rt2x00_set_security;
core->ieee80211->handle_auth     = rt2x00_handle_auth;
core->ieee80211->handle_deauth   = rt2x00_handle_deauth;
// ... handle_disassoc, handle_probe_request, handle_assoc_response,
//     handle_beacon, handle_probe_response
```

The **network device** still uses **`ieee80211_xmit`** as `dev->hard_start_xmit` (set in `alloc_ieee80211`). The ieee80211 stack converts an incoming `skb` into **`ieee80211_txb`** fragments and then calls **`ieee->hard_start_xmit`**, which is **`rt2x00_start_xmit`**. So the **TX entry point** from the IP layer is:

```
IP → netdev → ieee80211_xmit → ieee80211_txb → ieee->hard_start_xmit (= rt2x00_start_xmit)
```

### 4.3 net_device Ops

The core also sets:

```c
net_dev->open         = rt2x00_open;
net_dev->stop         = rt2x00_stop;
net_dev->change_mtu   = rt2x00_change_mtu;
net_dev->tx_timeout   = rt2x00_tx_timeout;
net_dev->get_stats    = rt2x00_get_stats;
```

So **open/close** and **TX timeout** are handled by the rt2x00 core, which in turn uses the PCI handler for radio and ring operations.

---

## 5. TX Path: IP Layer → WiFi Card

### 5.1 High-Level TX Flow

```
  [IP/Network stack]
         │
         ▼
  dev_queue_xmit(skb)  →  net_device
         │
         ▼
  dev->hard_start_xmit  =  ieee80211_xmit(skb, dev)
         │
         ▼
  [ieee80211 stack: build 802.11 headers, encrypt, fragment]
         │
         ▼
  ieee->hard_start_xmit(txb, dev, priority)  =  rt2x00_start_xmit(txb, net_dev, pri)
         │
         ▼
  [rt2x00: queue skbs to core->tx, schedule work]
         │
         ▼
  rt2x00_delayed_tx (workqueue)
         │
         ▼
  rt2x00_xmit_packet → handler->dev_xmit_packet  =  rt2x00_dev_xmit_packet
         │
         ▼
  [PCI: copy to DMA ring, write TX descriptor, kick hardware via TXCSR0]
         │
         ▼
  [Hardware transmits over air]
```

### 5.2 `ieee80211_xmit` (IP → 802.11)

- **`ieee80211_xmit(skb, dev)`** is the `hard_start_xmit` for the net_device.
- It pulls Ethernet header, builds 802.11 header (addresses, duration, etc.), optionally encrypts, fragments into **`ieee80211_txb`**.
- It then calls **`ieee->hard_start_xmit(txb, dev, priority)`**, which is **`rt2x00_start_xmit`**.

### 5.3 `rt2x00_start_xmit`

```c
// rt2x00core.c
static int rt2x00_start_xmit(struct ieee80211_txb *txb, struct net_device *net_dev, int pri)
{
    struct _rt2x00_device *device = rt2x00_device(net_dev);
    struct _rt2x00_core   *core   = rt2x00_core(device);
    ...
    if (!test_bit(DEVICE_RADIO_ON, &device->flags))
        return -ENOTCONN;

    spin_lock(&core->tx.lock);
    for (each fragment in txb) {
        skb = txb->fragments[counter];
        set seq_ctl, skb->cb (id, packets), priority;
        skb_queue_tail(&core->tx.queue, skb);
    }
    if (core->tx.ready)
        queue_work(core->workqueue, &core->tx.work);  // → rt2x00_delayed_tx
    spin_unlock(&core->tx.lock);
    ieee80211_txb_free(txb);
    return 0;
}
```

So TX frames are **queued** in **`core->tx`** (a **packet ring**), and **`rt2x00_delayed_tx`** is scheduled on the rt2x00 workqueue. **`rt2x00_kick_ring(&core->tx)`** also ensures the TX work is run when there are packets and the ring is ready.

### 5.4 `rt2x00_delayed_tx` (Workqueue)

- **`rt2x00_delayed_tx`** runs on **`core->workqueue`**.
- It drains **`core->tx.queue`**, and for each packet (or fragment group):
  - **`handler->dev_test_tx(device, fragments)`** → **`rt2x00_dev_test_tx`**: checks **`rt2x00_ring_free_entries(&rt2x00pci->tx)`**; returns non‑zero if there isn’t enough space in the **hardware TX ring**.
  - **`rt2x00_xmit_packet(core, ring, rate, xmit_flags)`**:
    - Dequeues an skb, fills duration, IFS, etc.
    - Calls **`handler->dev_xmit_packet(device, skb, RING_TX, rate, xmit_flags)`**.
  - After processing queued skbs, it calls **`dev_xmit_packet(device, NULL, RING_TX, 0, XMIT_START)`** to **kick** the hardware.

### 5.5 `rt2x00_dev_xmit_packet` (PCI → Hardware)

```c
// rt2400pci.c
static int rt2x00_dev_xmit_packet(struct _rt2x00_device *device, struct sk_buff *skb,
                                  u8 ring_type, u16 rate, u16 xmit_flags)
{
    struct _rt2x00_pci *rt2x00pci = rt2x00_priv(device);
    struct _data_ring  *ring;
    struct _txd        *txd;
    void               *data;
    u32                reg;

    rt2x00_register_read(rt2x00pci, TXCSR0, &reg);
    // Set TXCSR0_KICK_TX / KICK_PRIO / KICK_ATIM depending on ring_type.

    if (skb) {
        ring = &rt2x00pci->tx;  // (or prio, atim, beacon)
        txd  = DESC_ADDR(ring);
        data = DATA_ADDR(ring);

        if (TXD still owned by NIC or VALID)
            return -ENOMEM;

        memcpy(data, skb->data, skb->len);
        rt2x00_write_tx_desc(rt2x00pci, txd, skb->len, rate, skb->priority, xmit_flags);
        rt2x00_ring_index_inc(ring);
    }

    if (xmit_flags & XMIT_START)
        rt2x00_register_write(rt2x00pci, TXCSR0, reg);
    return 0;
}
```

- **`DESC_ADDR`** / **`DATA_ADDR`** index into the coherent DMA ring (descriptors first, then data buffers).
- **`rt2x00_write_tx_desc`** fills the **TXD** (valid, length, ack, retry, IFS, PLCP fields, etc.) and sets **`TXD_W0_OWNER_NIC = 1`** so the hardware owns the descriptor.
- **`rt2x00_register_write(..., TXCSR0, reg)`** with **`TXCSR0_KICK_TX`** (or KICK_PRIO/KICK_ATIM) **starts** the hardware TX engine on that ring.

So the **TX path** is: **IP → ieee80211_xmit → rt2x00_start_xmit → queue to core TX → rt2x00_delayed_tx → rt2x00_dev_xmit_packet → DMA ring + TXCSR0 kick → hardware**.

---

## 6. RX Path: WiFi Card → IP Layer

### 6.1 High-Level RX Flow

```
  [Hardware receives 802.11 frame, DMA into RX ring]
         │
         ▼
  [Hardware sets RXD, raises interrupt]
         │
         ▼
  rt2x00_interrupt(irq, dev_instance)
         │
         ▼
  rt2x00_interrupt_rxdone(&rt2x00pci->rx)
         │
         ▼
  [For each completed RXD: rt2x00_ring_rx_packet(device, size, data, rssi)]
         │
         ▼
  rt2x00_rx(device, skb)  →  rt2x00_queue_ring(&core->rx, skb)
         │
         ▼
  queue_work(workqueue, &core->rx.work)  →  rt2x00_delayed_rx
         │
         ▼
  [ieee80211_rx or ieee80211_rx_mgt]
         │
         ▼
  netif_rx(skb)  →  [IP layer]
```

### 6.2 Interrupt and `rt2x00_interrupt_rxdone`

When the device raises an interrupt, **`rt2x00_interrupt`** runs (see [§ 7](#7-interrupt-handling)). It reads **CSR7** (interrupt source), writes it back to clear, then handles **`CSR7_RXDONE`** by calling **`rt2x00_interrupt_rxdone(&rt2x00pci->rx)`**.

**`rt2x00_interrupt_rxdone`** (in `rt2400pci.c`):

```c
while (1) {
    rxd = DESC_ADDR(ring);
    data = DATA_ADDR(ring);

    if (rt2x00_get_field32(rxd->word0, RXD_W0_OWNER_NIC))
        break;   // descriptor still owned by NIC → no more RX

    size = rt2x00_get_field32(rxd->word0, RXD_W0_DATABYTE_COUNT);
    rssi = rt2x00_get_field32(rxd->word2, RXD_W2_RSSI);

    if (CRC error / physical error / low RSSI)
        update stats;
    else
        rt2x00_ring_rx_packet(ring->device, size, data, rssi);

    rt2x00_set_field32(&rxd->word0, RXD_W0_OWNER_NIC, 1);  // give back to NIC
    rt2x00_ring_index_inc(&rt2x00pci->rx);
}
```

- **`RXD_W0_OWNER_NIC`**: 0 = driver can use descriptor; 1 = NIC owns it. The loop breaks when the next descriptor is still owned by the NIC.
- Valid frames are passed to **`rt2x00_ring_rx_packet`**.

### 6.3 `rt2x00_ring_rx_packet` and `rt2x00_rx`

**`rt2x00_ring_rx_packet`** (in `rt2x00dev.h`):

```c
skb = dev_alloc_skb(size + NET_IP_ALIGN);
skb_reserve(skb, NET_IP_ALIGN);
memcpy(skb_put(skb, size), data, size);
((struct _skb_cb *)skb->cb)->rssi = rssi;
rt2x00_rx(device, skb);
```

**`rt2x00_rx`** (in `rt2x00core.c`):

```c
void rt2x00_rx(struct _rt2x00_device *device, struct sk_buff *skb)
{
    rt2x00_queue_ring(&core->rx, skb);
}
```

**`rt2x00_queue_ring`** (in `rt2x00core.h`):

```c
skb_queue_tail(&ring->queue, skb);
if (ring->ready)
    queue_work(ring->core->workqueue, &ring->work);
```

So the RX **packet ring** is **`core->rx`**. When **`ring->ready`** is set, **`rt2x00_delayed_rx`** is run on the workqueue.

### 6.4 `rt2x00_delayed_rx` and Upstream to IP

**`rt2x00_delayed_rx`**:

- Drains **`core->rx.queue`**.
- Fills **`ieee80211_rx_stats`** (rate, channel, freq, rssi, etc.).
- For each skb:
  - **Management frames** (and not monitor): **`ieee80211_rx_mgt`** or **`rt2x00_handle_assoc`**, then `dev_kfree_skb_any`.
  - **Data / other**: **`ieee80211_rx(ieee, skb, &rx_stats)`**.
    - **`ieee80211_rx`** decrypts (if needed), strips 802.11 header, converts to Ethernet format, and passes the skb to **`netif_rx(skb)`**, which delivers it to the **IP layer**.

So **RX path**: **Hardware → interrupt → rxdone → ring_rx_packet → queue_ring → delayed_rx → ieee80211_rx → netif_rx → IP**.

---

## 7. Interrupt Handling

### 7.1 Registration

The interrupt is registered in **`rt2x00_dev_radio_on()`**:

```c
request_irq(rt2x00pci->pci_dev->irq, rt2x00_interrupt, SA_SHIRQ,
            device->net_dev->name, device);
```

- **Handler:** **`rt2x00_interrupt`**.
- **SA_SHIRQ:** shared interrupt.
- **dev_id:** **`device`** (struct _rt2x00_device).
- **Freed** in **`rt2x00_dev_radio_off()`** via **`free_irq(rt2x00pci->pci_dev->irq, device)`**.

### 7.2 Interrupt Registers

**CSR7** (offset `0x1c`): **Interrupt source** (read to see what fired; write same value to clear).

**CSR8** (offset `0x20`): **Interrupt mask**. Bit = 1 **disables** that source.

Relevant bits (from `rt2400pci.h`):

| Bit | CSR7 / CSR8 | Meaning |
|-----|-------------|---------|
| 0   | TBCN_EXPIRE | Beacon timer expired |
| 1   | TWAKE_EXPIRE | Wakeup timer expired |
| 2   | TATIMW_EXPIRE | ATIM window timer |
| 3   | TXDONE_TXRING | TX ring done |
| 4   | TXDONE_ATIMRING | ATIM ring done |
| 5   | TXDONE_PRIORING | Priority ring done |
| 6   | RXDONE | RX done |

On **radio on**, the driver **reads CSR7**, **writes it back** (clear), then **configures CSR8** so that the **mask bits for these sources are 0** (interrupts enabled). On **radio off**, it sets those mask bits to **1** (disable), then **`free_irq`**.

### 7.3 Handler Logic: `rt2x00_interrupt`

```c
static irqreturn_t rt2x00_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
    struct _rt2x00_device *device = (struct _rt2x00_device *)dev_instance;
    struct _rt2x00_pci   *rt2x00pci = rt2x00_priv(device);
    u32 reg = 0;
    u8 ring_type = 0;

    rt2x00_register_read(rt2x00pci, CSR7, &reg);
    rt2x00_register_write(rt2x00pci, CSR7, reg);   // clear by write-back

    if (!reg)
        return IRQ_NONE;

    if (CSR7_TBCN_EXPIRE)   rt2x00_tx(device, RING_BEACON);
    if (CSR7_RXDONE)        rt2x00_interrupt_rxdone(&rt2x00pci->rx);
    if (CSR7_TXDONE_ATIMRING) { rt2x00_interrupt_txdone(&rt2x00pci->atim); ring_type |= RING_ATIM; }
    if (CSR7_TXDONE_PRIORING) { rt2x00_interrupt_txdone(&rt2x00pci->prio); ring_type |= RING_PRIO; }
    if (CSR7_TXDONE_TXRING)   { rt2x00_interrupt_txdone(&rt2x00pci->tx);   ring_type |= RING_TX;   }

    if (ring_type)
        rt2x00_tx(device, ring_type);

    return IRQ_HANDLED;
}
```

- **Read CSR7** → **write same value** clears pending interrupts.
- **RXDONE** → **`rt2x00_interrupt_rxdone`** (process RX ring, queue skbs to **`core->rx`**, schedule **`rt2x00_delayed_rx`**).
- **TXDONE_*** → **`rt2x00_interrupt_txdone`** for the corresponding **data ring** (atim, prio, tx). **`rt2x00_interrupt_txdone`** walks completed TX descriptors, updates stats, clears **VALID**, advances **`index_done`**.
- Then **`rt2x00_tx(device, ring_type)`** is called to **kick** the **packet rings** (tx/prio/atim) so that **`rt2x00_delayed_tx`** can push more packets into the hardware TX ring.

### 7.4 TX Done Processing: `rt2x00_interrupt_txdone`

```c
static void rt2x00_interrupt_txdone(struct _data_ring *ring)
{
    do {
        txd = DESC_ADDR_DONE(ring);
        if (TXD_W0_OWNER_NIC || !TXD_W0_VALID)
            break;

        // update stats from TXD_W0_RESULT, TXD_W0_RETRY_COUNT
        rt2x00_set_field32(&txd->word0, TXD_W0_VALID, 0);
        rt2x00_ring_index_done_inc(ring);
    } while (!rt2x00_ring_empty(ring));
}
```

- **`DESC_ADDR_DONE`** uses **`index_done`**; **`DESC_ADDR`** uses **`index`**.
- Driver reclaims descriptors by clearing **VALID** and advancing **`index_done`**. This frees space in the hardware TX ring for **`dev_test_tx`** / **`dev_xmit_packet`**.

---

## 8. Data Structures and Rings

### 8.1 Two Ring Layers

1. **Packet rings** (`struct _packet_ring` in core):  
   **`core->rx`**, **`core->tx`**, **atim**, **prio**, **beacon**.  
   - Hold **skb** queues and **work** structs for **`rt2x00_delayed_rx`** / **`rt2x00_delayed_tx`** / **`rt2x00_delayed_mgmt`**.

2. **Data rings** (`struct _data_ring` in PCI):  
   **`rt2x00pci->rx`**, **tx**, **atim**, **prio**, **beacon**.  
   - **DMA coherent** memory: **descriptors + data**.
   - **Descriptors**: **RXD** (rx) or **TXD** (tx); **DATA** holds raw frame bytes.
   - **`index`** / **`index_done`** manage producer/consumer.

### 8.2 Descriptor Layout (Conceptual)

- **RXD**: **word0** (OWNER_NIC, CRC, DATABYTE_COUNT, …), **word1** (buffer address), **word2** (RSSI, …).
- **TXD**: **word0** (VALID, OWNER_NIC, IFS, ACK, …), **word1** (buffer address), **word2** (length), **word3**/ **word4** (PLCP, etc.).

**`DESC_BASE`** / **`DATA_BASE`** in `rt2x00pci.h` define the layout; **`__DESC_ADDR`** / **`__DATA_ADDR`** compute per‑entry pointers.

### 8.3 Ring Sizes (rt2400pci)

Defined in **`rt2x00pci.h`** via **`rt2x00_pci_alloc_ring`**:

- **RX:** **RX_ENTRIES**, **DATA_FRAME_SIZE** (2432), **SIZE_DESCRIPTOR**.
- **TX / ATIM / PRIO / BEACON:** **TX_ENTRIES**, **ATIM_ENTRIES**, etc., **MGMT_FRAME_SIZE** (256) or **DATA_FRAME_SIZE**.

---

## 9. Summary Diagrams

### 9.1 Probe and Init

```
  insmod rt2400pci
       │
       ▼
  pci_register_driver
       │
       ▼
  PCI core finds 1814:0101 → rt2x00_pci_probe
       │
       ├─ pci_enable_device, set_master, request_regions
       │
       ▼
  rt2x00_core_probe(handler, pci_dev, ...)
       │
       ├─ alloc_ieee80211 → net_dev
       ├─ init packet rings (rx,tx,atim,prio,beacon)
       ├─ handler->dev_probe → rt2x00_dev_probe
       │     ├─ ioremap BAR0 → csr_addr
       │     ├─ init EEPROM, read MAC
       │     └─ set device caps
       ├─ Override ieee80211 hard_start_xmit = rt2x00_start_xmit
       ├─ net_dev->open = rt2x00_open, etc.
       └─ register_netdev(net_dev)

  ifconfig wlan0 up
       │
       ▼
  rt2x00_open → rt2x00_radio_on
       │
       ├─ rt2x00_enable_ring(rx,tx,atim,prio,beacon)  [packet rings]
       └─ handler->dev_radio_on → rt2x00_dev_radio_on
             ├─ pci alloc DMA rings, clear, init ring regs
             ├─ init regs, BBP, MAC
             ├─ request_irq(rt2x00_interrupt)
             └─ enable interrupts in CSR8
       │
       ▼
  rt2x00_activate_config → rt2x00_link_up (scan / monitor)
       │
       └─ rt2x00_connect (when network chosen) configures BSS, etc.
```

### 9.2 TX Path (Simplified)

```
  IP → dev_queue_xmit
       → ieee80211_xmit (build 802.11, encrypt, fragment)
       → rt2x00_start_xmit (queue to core->tx, queue_work)
       → rt2x00_delayed_tx
       → dev_test_tx / rt2x00_xmit_packet
       → rt2x00_dev_xmit_packet (copy to DMA, write TXD, kick TXCSR0)
       → hardware TX
```

### 9.3 RX Path (Simplified)

```
  hardware RX → DMA to RX ring → raise IRQ
       → rt2x00_interrupt
       → rt2x00_interrupt_rxdone (read RXD, copy to skb)
       → rt2x00_ring_rx_packet → rt2x00_rx → rt2x00_queue_ring(&core->rx)
       → queue_work(rt2x00_delayed_rx)
       → ieee80211_rx / ieee80211_rx_mgt
       → netif_rx → IP
```

### 9.4 Interrupt Handling

```
  IRQ → rt2x00_interrupt
        ├─ read CSR7, write back (clear)
        ├─ RXDONE    → rt2x00_interrupt_rxdone(rx)
        ├─ TXDONE_TX → rt2x00_interrupt_txdone(tx);   rt2x00_tx(RING_TX)
        ├─ TXDONE_PRIO→ rt2x00_interrupt_txdone(prio); rt2x00_tx(RING_PRIO)
        ├─ TXDONE_ATIM→ rt2x00_interrupt_txdone(atim); rt2x00_tx(RING_ATIM)
        └─ TBCN_EXPIRE → rt2x00_tx(RING_BEACON)
```

---

## 10. SSID Discovery (Scanning), Encryption, and Connecting to an SSID

This section describes how the driver **finds SSIDs** (scanning), **supports different encryption methods** (WEP, WPA/WPA2, TKIP, CCMP), and **connects to an SSID** (auth, assoc, config).

### 10.1 How the Driver Finds SSIDs (Scanning)

#### 10.1.1 Triggering a Scan

- **Userspace** requests a scan via **`SIOCSIWSCAN`** (e.g. `iwlist wlan0 scan`). The handler is **`rt2x00_ioctl_set_scan`**.
- If the device is not yet on, it calls **`rt2x00_radio_on`** and **`rt2x00_activate_config`**.
- It then calls **`rt2x00_start_scan(device, scan_req, flags)`**.  
  **`scan_req`** can be `NULL` (default scan) or a **`struct iw_scan_req`** with optional **ESSID**, **BSSID**, **channel list**, and **scan type** (active vs passive).

#### 10.1.2 Scan Request Setup

**`rt2x00_start_scan`** (in `rt2x00core.c`):

1. Sets **`DEVICE_SCANNING`**, takes **`core->scan_sem`**, allocates **`core->scan_req`**.
2. **`IW_SCAN_DEFAULT`**: BSSID = broadcast (`0xff...`); no fixed ESSID.
3. **`IW_SCAN_THIS_ESSID`**: uses **`scan_req->essid`** and **`essid_len`** for a **directed** probe (only that SSID).
4. **`IW_SCAN_THIS_FREQ`**: scan only the **current channel**; otherwise it builds a **channel list** from **`ieee80211_geo`** (2.4 GHz and/or 5 GHz) or from **`scan_req->channel_list`**.
5. Switches to the **first channel**, calls **`rt2x00_update_config`** (so hardware uses that channel).
6. **Active scan**: **`rt2x00_mgmt_snd_probe_req`** sends a **Probe Request** with:
   - **SSID** IE from **`scan_req->essid`** (or empty for broadcast);
   - **Rates** IE;
   - **DA** = **`scan_req->bssid`** (broadcast or specific AP).
7. Schedules **`rt2x00_scan_periodic`** on the workqueue after **`SCAN_TIME`** (`HZ/5`).

So the driver **finds SSIDs** by either **listening for Beacons** (passive) or **sending Probe Requests** (active). Probe Requests can target **any** SSID (empty IE) or a **specific SSID** when the user asks to scan for one.

#### 10.1.3 Periodic Scan and Channel Switching

**`rt2x00_scan_periodic`**:

- If **`IW_SCAN_THIS_FREQ`** or only **one channel**: **`rt2x00_stop_scan`** → scan done, **`SIOCGIWSCAN`** event.
- Otherwise: **switch to next channel** in **`scan_req->channel_list`**, **`rt2x00_update_config`**, and again **`rt2x00_mgmt_snd_probe_req`** when **active**.
- Re-schedules itself after **`SCAN_TIME`** until all channels are done, then **`rt2x00_stop_scan`**.

#### 10.1.4 Where SSIDs Come From: Beacons and Probe Responses

- **Beacons** and **Probe Responses** received from APs are handled in **`rt2x00_delayed_rx`** → **`ieee80211_rx_mgt`** / **`rt2x00_handle_beacon`** / **`rt2x00_handle_probe_resp`**.
- The **ieee80211** stack parses **Information Elements** and fills **`struct ieee80211_network`**:
  - **`MFIE_TYPE_SSID`** → **`network->ssid`**, **`ssid_len`**;
  - **`MFIE_TYPE_DS_SET`** → **`network->channel`**;
  - **`MFIE_TYPE_RATES`** → supported rates;
  - **`MFIE_TYPE_GENERIC`** (OUI `00:50:f2:01`) → **WPA IE** → **`network->wpa_ie`**, **`wpa_ie_len`**;
  - **`MFIE_TYPE_RSN`** → **RSN IE** → **`network->rsn_ie`**, **`rsn_ie_len`**;
  - **`WLAN_CAPABILITY_PRIVACY`** → network uses encryption.
- These **`ieee80211_network`** entries are stored in **`ieee80211->network_list`** and exposed to userspace via **`SIOCGIWSCAN`** (**`rt2x00_ioctl_get_scan`** → **`ieee80211_wx_get_scan`**).

So **SSID discovery** is: **scan (passive/active) → receive Beacons/Probe Responses → parse IEs → store networks → userspace reads scan results**.

#### 10.1.5 Choosing an SSID to Connect To

- User sets **ESSID** via **`SIOCSIWESSID`** (**`rt2x00_ioctl_set_essid`**): copies **`extra`** into **`core->config.user.essid`**, sets **`CONFIG_FIX_ESSID`**, **`COMMIT_ESSID`**.
- Optional **BSSID** via **`SIOCSIWAP`** (**`rt2x00_ioctl_set_wap`**): **`CONFIG_FIX_BSSID`**, **`COMMIT_BSSID`**.
- **`rt2x00_link_periodic`** (link tuner) calls **`rt2x00_search_scan`** to pick an **`ieee80211_network`** from the scan list. **`rt2x00_validate_scan_entry`** filters by:
  - **`CONFIG_FIX_ESSID`**: SSID must match **`config->active.essid`** (and length);
  - **`CONFIG_FIX_BSSID`**: BSSID must match;
  - **`CONFIG_FIX_CHANNEL`**: channel must match;
  - **mode** (Infra vs Ad‑hoc) and **capability** (ESS/IBSS);
  - **encryption**: **`WLAN_CAPABILITY_PRIVACY`** vs **`ieee80211->sec.enabled`** (and **`sec.level`**, **`auth_mode`**) must be consistent.
- The **best match** (e.g. by **RSSI**) is used; then **`rt2x00_connect(device, network, mode)`** runs.

### 10.2 Encryption Methods and Security Setup

#### 10.2.1 Supported Algorithms

The driver works with the **ieee80211** crypto layer. **`range->enc_capa`** advertises:

```c
range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2
                  | IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;
```

**`encoding_size`**: 5 (64‑bit WEP), 13 (128‑bit WEP); **`max_encoding_tokens`** = 4 (WEP keys).

| Type | Module | Cipher | Use |
|------|--------|--------|-----|
| **WEP** | `ieee80211_crypt_wep` | RC4 | Open/shared key, 64/128 bit |
| **TKIP** | `ieee80211_crypt_tkip` | TKIP | WPA (and WPA2) |
| **CCMP** | `ieee80211_crypt_ccmp` | AES-CCMP | WPA2 |

Keys and algorithms are configured via **Wireless Extensions** (**`SIOCSIWENCODE`**, **`SIOCSIWENCODEEXT`**, etc.). The ieee80211 stack maintains **`ieee->crypt[]`** and selects **`ieee80211_get_crypto_ops`** (e.g. `"WEP"`, `"TKIP"`, `"CCMP"`). When **host** encryption/decryption is used, **`ieee80211_xmit`** encrypts and **`ieee80211_rx`** decrypts via **`crypt->ops->encrypt_*`** / **`decrypt_*`**.

#### 10.2.2 Driver Security Hook: `rt2x00_set_security`

The core sets **`ieee->set_security = rt2x00_set_security`**. When the ieee80211 stack updates keys/algos (e.g. after **`SIOCSIWENCODE`**), it calls **`set_security(ieee->dev, &sec)`**.

**`rt2x00_set_security`** (in `rt2x00core.c`):

- Copies **keys**, **key sizes**, **encode alg** per key from **`sec`** into **`core->ieee80211->sec`**.
- Updates **active key**, **auth mode**, **enabled**, **encrypt**, **level**.
- Sets **`COMMIT_ENCRYPTION`** so **`rt2x00_activate_config`** / **`rt2x00_update_config`** apply security-related config.

So **encryption** is configured by **userspace → Wireless Extensions → ieee80211 crypto → `set_security` → driver `sec`** and **`COMMIT_ENCRYPTION`**.

#### 10.2.3 WPA / WPA2 and WPA IE

- **WPA IE** (and RSN) are set via **`SIOCSIWGENIE`** (**`rt2x00_ioctl_set_genie`**): stored in **`core->ieee80211->wpa_ie`**, **`wpa_ie_len`**; **`COMMIT_ENCRYPTION`**.
- **`IW_AUTH_*`** (**`rt2x00_ioctl_set_auth`**): **WPA version** (WPA vs WPA2), **drop unencrypted**, **open WEP**, **WPA enabled**, **RX unencrypted EAPOL**, etc.
- For **Auth** (and **Auth shake**) and **Assoc**, **`rt2x00_create_mgmt_buffer`** can add **WPA/RSN IE** when **`MGMT_BUFFER_CHALLENGE`** and **`wpa_ie`** are set, matching **`wpa_version`** (WPA → **`MFIE_TYPE_GENERIC`**, WPA2 → **`MFIE_TYPE_RSN`**).

Management frames (e.g. WPA Auth) can be **encrypted** via **`rt2x00_encrypt_mgmt_frame`**, which uses **`ieee->crypt[tx_keyidx]`** and **`encrypt_msdu`** / **`encrypt_mpdu`**.

### 10.3 Connecting to an SSID (Auth, Assoc, Config)

#### 10.3.1 High-Level Flow

1. User sets **ESSID** (and optionally **BSSID**, **channel**), **encryption** (WEP/WPA/WPA2, keys, WPA IE), then **`ifconfig wlan0 up`** or similar.
2. **`rt2x00_link_up`** starts **`rt2x00_start_scan`** (or **`rt2x00_connect`** in monitor mode).
3. **Link tuner** (**`rt2x00_link_periodic`**): when **not** connected, **`rt2x00_search_scan`** picks a matching **`ieee80211_network`** (SSID, BSSID, channel, encryption). Then **`rt2x00_connect(device, network, mode)`**.
4. **`rt2x00_connect`**:
   - Stores **`core->network`**, sets **`iw_mode`**, **BSSID**;
   - **`rt2x00_link_up_config`**: copies **SSID**, **BSSID**, **channel**, rates from **`core->network`** into **`config.active`**;
   - **`rt2x00_update_config`** → **`dev_update_config`** (e.g. BBP channel, BSSID filter);
   - Sends **Auth** (**`rt2x00_mgmt_snd_auth`**); for **WPA**, **Auth shake** (**`rt2x00_mgmt_snd_auth_shake`**) with **WPA IE**.
5. **`rt2x00_handle_auth`**: on **Auth response**, checks **`sec`** (encryption, level) and **ieee802_1x**; then **`rt2x00_mgmt_snd_assoc`**.
6. **`rt2x00_handle_assoc_resp`** (via **`handle_assoc_response`**): **`rt2x00_start_connection`** → **`netif_carrier_on`**, **`netif_start_queue`**, **enable beacon** (Ad‑hoc), etc.

#### 10.3.2 Summary

| Step | Driver / stack |
|------|----------------|
| **Find SSIDs** | **Scan** (SIOCSIWSCAN) → Probe Req (optional SSID) / Beacons → parse IEs → **network_list** → SIOCGIWSCAN |
| **Select SSID** | **SIOCSIWESSID** / **SIOCSIWAP** → **config.user**; **rt2x00_search_scan** + **rt2x00_validate_scan_entry** (SSID, BSSID, channel, encryption) |
| **Set encryption** | **SIOCSIWENCODE** / **SIOCSIWENCODEEXT**, **SIOCSIWGENIE**, **IW_AUTH_*** → **ieee->crypt** + **wpa_ie** → **rt2x00_set_security** → **COMMIT_ENCRYPTION** |
| **Connect** | **rt2x00_connect** → **link_up_config** → **Auth** (WPA IE if WPA/WPA2) → **Assoc** → **start_connection** |

So the driver **helps find SSIDs** via **scanning** (active/passive), **stores** them from **Beacons/Probe Responses** (including **WPA/RSN IE**), **filters** by **SSID/BSSID/channel/encryption** when **connecting**, and **supports WEP, WPA, WPA2, TKIP, and CCMP** through the **ieee80211** crypto layer and **`set_security`** / **WPA IE** path.

---

## References (rt2x00-2.0.0-b3)

| Topic | File(s) | Relevant symbols |
|-------|---------|-------------------|
| PCI driver, probe, remove | `rt2400pci.c` | `rt2x00_pci_probe`, `rt2x00_pci_remove`, `rt2x00_pci_init` |
| PCI handler, rings, MMIO | `rt2x00pci.h` | `rt2x00_pci_alloc_ring`, `rt2x00_register_read`/`_write`, `DESC_ADDR` |
| Core probe, open, start_xmit | `rt2x00core.c` | `rt2x00_core_probe`, `rt2x00_open`, `rt2x00_start_xmit` |
| TX/RX work | `rt2x00core.c` | `rt2x00_delayed_tx`, `rt2x00_delayed_rx`, `rt2x00_xmit_packet` |
| Interrupt, RX/TX done | `rt2400pci.c` | `rt2x00_interrupt`, `rt2x00_interrupt_rxdone`, `rt2x00_interrupt_txdone` |
| Device probe, radio on/off | `rt2400pci.c` | `rt2x00_dev_probe`, `rt2x00_dev_radio_on`, `rt2x00_dev_radio_off` |
| Xmit packet, TX desc | `rt2400pci.c` | `rt2x00_dev_xmit_packet`, `rt2x00_write_tx_desc` |
| RX packet, queue | `rt2x00dev.h`, `rt2x00core.h` | `rt2x00_ring_rx_packet`, `rt2x00_rx`, `rt2x00_queue_ring` |
| ieee80211 TX/RX | `ieee80211/ieee80211_tx.c`, `ieee80211_rx.c` | `ieee80211_xmit`, `ieee80211_rx`, `netif_rx` |
| Registers | `rt2400pci.h` | `CSR7`, `CSR8`, `TXCSR0`, `RXD_W0_*`, `TXD_W0_*` |
| Scan, SSID, connect | `rt2x00core.c` | `rt2x00_start_scan`, `rt2x00_scan_periodic`, `rt2x00_mgmt_snd_probe_req`, `rt2x00_search_scan`, `rt2x00_validate_scan_entry`, `rt2x00_connect` |
| Encryption, WPA IE | `rt2x00core.c`, `ieee80211/ieee80211_wx.c` | `rt2x00_set_security`, `rt2x00_create_mgmt_buffer`, `rt2x00_encrypt_mgmt_frame`, `ieee->crypt`, `wpa_ie` |
| Crypto modules | `ieee80211/ieee80211_crypt_*.c` | `ieee80211_crypt_wep`, `ieee80211_crypt_tkip`, `ieee80211_crypt_ccmp` |

---

*Document describes the rt2x00-2.0.0-b3 driver and its PCI probe, initialization, configuration, callbacks, TX/RX paths, interrupt handling, SSID discovery (scanning), encryption support, and connecting to an SSID.*
