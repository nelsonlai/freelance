# Robotaxi 硬體與通訊基礎 - 20 堂課每日教材包

> 面向智能駕駛開發者，涵蓋 CPU 架構、匯流排、資料傳輸介面與車載通訊協定。  
> 每堂課 1.5~2 小時，含理論與實驗。

---

## 第一階段：車載計算與匯流排基礎（1–5）

### Day 1 - Robotaxi 硬體總覽與架構設計
- **內容**
  - 中央計算單元（CPU/GPU/AI ASIC）
  - 感測器（LiDAR、Radar、Camera）
  - 通訊介面與資料流
  - 功能安全（ISO 26262）簡介
- **資源**
  - [NVIDIA DRIVE](https://developer.nvidia.com/drive)
- **實驗**
  - 繪製 Robotaxi 系統方塊圖

### Day 2 - CPU 與 SoC 架構
- **內容**
  - ARM vs x86 車載平台
  - CPU 核心、快取、指令集
  - SoC 整合
- **資源**
  - [ARM Architecture Reference](https://developer.arm.com/documentation/)
- **實驗**
  - `lscpu` 查看 CPU 資訊

### Day 3 - 系統匯流排概念
- **內容**
  - 匯流排角色
  - 並行 vs 串行匯流排
- **資源**
  - [Bus Architecture Basics](https://en.wikipedia.org/wiki/Bus_(computing))

### Day 4 - PCI Express (PCIe)
- **內容**
  - PCIe 層級架構
  - Lane 與速度
- **實驗**
  - `lspci` 觀察 PCIe 裝置

### Day 5 - Ethernet 與車載以太網
- **內容**
  - Ethernet 基礎 (MAC, PHY)
  - 車載 100BASE-T1 / 1000BASE-T1
- **實驗**
  - Wireshark 抓封包

---

## 第二階段：車載通訊介面（6–12）

### Day 6 - CAN Bus
- **內容**
  - CAN 標準帧 / 擴展帧
  - CAN FD
- **實驗**
  - CAN 分析儀讀取訊號

### Day 7 - LIN Bus
- **內容**
  - LIN 架構與節點
- **實驗**
  - 模擬車窗控制

### Day 8 - I²C
- **內容**
  - 主從架構、速度模式
- **實驗**
  - 讀取 I²C 溫度感測器

### Day 9 - SPI
- **內容**
  - 全雙工、時序模式
- **實驗**
  - SPI 與 Flash 讀寫

### Day 10 - I²S
- **內容**
  - 音訊串列匯流排原理
- **實驗**
  - I²S 麥克風錄音

### Day 11 - UART / RS-232 / RS-485
- **內容**
  - 非同步通訊原理
- **實驗**
  - 串口調試

### Day 12 - USB
- **內容**
  - USB 協議與車載應用
- **實驗**
  - 連接 USB 攝像頭

---

## 第三階段：車載影像與顯示（13–15）

### Day 13 - MIPI DSI
- **內容**
  - MIPI 協議族簡介
- **實驗**
  - 顯示屏連接與測試

### Day 14 - MIPI CSI
- **內容**
  - 車載攝像頭介面
- **實驗**
  - 讀取 CSI 攝像頭影像

### Day 15 - GPU 與影像處理硬體加速
- **內容**
  - CUDA / OpenCL
- **實驗**
  - GPU 加速影像處理

---

## 第四階段：系統整合與實作（16–20）

### Day 16 - 多匯流排整合與資料同步
- **內容**
  - PTP 與 IEEE 1588
- **實驗**
  - 多感測器時間同步

### Day 17 - 電源管理與可靠性設計
- **內容**
  - EMI/EMC 與車規
- **實驗**
  - 模擬電源干擾測試

### Day 18 - 車載資料記錄與診斷
- **內容**
  - OBD-II 與 UDS
- **實驗**
  - 讀取車速與轉速

### Day 19 - QNX / Linux 實時系統整合
- **內容**
  - RTOS 與 POSIX API
- **實驗**
  - 撰寫簡單驅動

### Day 20 - Robotaxi 硬體系統專題
- **內容**
  - 設計多感測器資料採集系統
- **實驗**
  - 最終 Demo 與文件撰寫
