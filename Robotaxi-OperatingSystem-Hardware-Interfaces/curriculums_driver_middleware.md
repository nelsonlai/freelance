# Linux / QNX Driver 與中間件硬體溝通 - 20 堂課每日教材包

> 本課程專注於 Linux/QNX 驅動與中間件開發，涵蓋如何與 Robotaxi 硬體匯流排與介面溝通，並附示範程式碼。

---

## 第一階段：驅動開發基礎（1–5）

### Day 1 - 驅動程式開發概述
- **內容**
  - User space vs Kernel space
  - Linux 與 QNX 驅動開發差異
- **資源**
  - [Linux Device Drivers, Third Edition](https://lwn.net/Kernel/LDD3/)

### Day 2 - 建立簡單 Linux 字元驅動
- **內容**
  - 字元裝置 (char device) 原理
- **範例程式**
  ```c
  #include <linux/module.h>
  #include <linux/fs.h>
  static int __init hello_init(void) {
      printk(KERN_INFO "Hello Driver\n");
      return 0;
  }
  static void __exit hello_exit(void) {
      printk(KERN_INFO "Goodbye Driver\n");
  }
  module_init(hello_init);
  module_exit(hello_exit);
  MODULE_LICENSE("GPL");
  ```

### Day 3 - Device Tree 與硬體描述
- **內容**
  - DTS / DTB 介紹
- **範例**
  ```dts
  my_device@0 {
      compatible = "vendor,mydev";
      reg = <0x00 0x1000>;
  };
  ```

### Day 4 - QNX Resource Manager 架構
- **內容**
  - QNX 驅動與 /dev 介面
- **範例**
  ```c
  resmgr_attach(...); // 建立資源管理器
  ```

### Day 5 - 中斷處理 (IRQ Handling)
- **內容**
  - request_irq() 與中斷上下文
- **範例**
  ```c
  static irqreturn_t my_isr(int irq, void *dev_id) {
      printk(KERN_INFO "Interrupt!\n");
      return IRQ_HANDLED;
  }
  ```

---

## 第二階段：匯流排與通訊介面驅動（6–12）

### Day 6 - PCIe 裝置驅動
- **內容**
  - PCIe 配置空間讀寫
- **範例**
  ```c
  pci_read_config_dword(dev, offset, &val);
  ```

### Day 7 - Ethernet Driver
- **內容**
  - net_device 結構
- **範例**
  ```c
  netif_start_queue(ndev);
  ```

### Day 8 - CAN Bus Driver
- **內容**
  - SocketCAN 架構
- **範例**
  ```c
  int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  bind(s, ...);
  ```

### Day 9 - I²C 驅動
- **內容**
  - i2c_client 與 i2c_adapter
- **範例**
  ```c
  i2c_smbus_read_byte_data(client, reg);
  ```

### Day 10 - SPI 驅動
- **範例**
  ```c
  spi_sync(spi, &msg);
  ```

### Day 11 - I²S 音訊驅動
- **內容**
  - ALSA 與 I²S
- **範例**
  ```c
  snd_pcm_writei(handle, buffer, frames);
  ```

### Day 12 - UART 驅動
- **範例**
  ```c
  serial8250_register_port(&uart);
  ```

---

## 第三階段：影像與多媒體（13–15）

### Day 13 - USB 攝像頭驅動 (UVC)
- **範例**
  ```c
  v4l2_open(...);
  ```

### Day 14 - MIPI DSI 顯示驅動
- **範例**
  ```c
  mipi_dsi_dcs_write(...);
  ```

### Day 15 - MIPI CSI 攝像頭驅動
- **範例**
  ```c
  v4l2_subdev_call(...);
  ```

---

## 第四階段：中間件與應用層整合（16–20）

### Day 16 - 驅動與中間件通訊
- **內容**
  - ioctl 與 sysfs
- **範例**
  ```c
  int val;
  ioctl(fd, MY_CMD, &val);
  ```

### Day 17 - ROS2 與驅動整合
- **範例**
  ```cpp
  auto pub = node->create_publisher<std_msgs::msg::String>("topic", 10);
  ```

### Day 18 - QNX 驅動與中間件範例
- **範例**
  ```c
  resmgr_attach(...);
  ```

### Day 19 - 實時資料傳輸
- **內容**
  - DMA 與 Zero-copy
- **範例**
  ```c
  dma_map_single(...);
  ```

### Day 20 - 硬體通訊專題
- **內容**
  - 同時管理多介面
- **實作**
  - 整合 PCIe + CAN + Ethernet
