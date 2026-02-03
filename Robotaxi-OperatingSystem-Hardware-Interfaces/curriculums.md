# 智能駕駛與機器人實習熱身計畫 - 20 天每日教材包

> 適合已有 Python 基礎，準備進入智能駕駛 / 機器人領域實習的同學。  
> 每天 2 小時，4 週完成。內容含學習資源、練習題與程式模板。

---

## 第 1 週：開發環境 & C++ 基礎

### Day 1 - Linux 基礎與 Ubuntu 環境
- **學習資源**
  - [Linux 命令大全](https://man7.org/linux/man-pages/)
  - [Ubuntu 官方下載](https://ubuntu.com/download/desktop)
- **練習**
  1. 安裝 Ubuntu / WSL 2
  2. 練習 `cd`, `ls`, `cp`, `mv`, `chmod`, `grep`
- **程式模板**
  ```bash
  #!/bin/bash
  echo "Hello Linux!"
  ```

### Day 2 - Linux 進階工具與 Bash 腳本
- **資源**
  - [Bash Guide](https://tldp.org/LDP/Bash-Beginners-Guide/html/)
- **練習**
  1. 寫一個自動備份資料夾的 Bash 腳本
  2. 練習 `ps`, `top`, `systemctl`

### Day 3 - C++ 基礎語法復習
- **資源**
  - [C++ 教程 - cppreference](https://en.cppreference.com/w/)
- **練習**
  1. BMI 計算器
- **模板**
  ```cpp
  #include <iostream>
  using namespace std;
  int main() {
      double h, w;
      cin >> h >> w;
      cout << "BMI: " << w / (h*h) << endl;
      return 0;
  }
  ```

### Day 4 - C++ OOP 與 STL
- **資源**
  - [STL 容器教學](https://cplusplus.com/reference/stl/)
- **練習**
  1. 用 `vector` 儲存分數計平均
  2. 練習類別與多型

### Day 5 - C++11/17 語法
- **資源**
  - [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)
- **練習**
  1. lambda 排序
  2. `std::thread` 多執行緒

---

## 第 2 週：系統程式基礎 & ROS2 入門

### Day 6 - 編譯器、鏈接器、加載器
- **資源**
  - [What is Linking](https://en.wikipedia.org/wiki/Linker_(computing))
- **練習**
  1. `g++ -c` 編譯 `.o` 再手動鏈接
  2. `readelf` 看 ELF

### Day 7 - OS 啟動流程與 Bootloader
- **資源**
  - [Linux Boot Process](https://www.thegeekstuff.com/2011/02/linux-boot-process/)
- **練習**
  1. 繪製 Linux / QNX 啟動流程圖

### Day 8 - 任務調度與記憶體管理
- **資源**
  - [Memory Management](https://pages.cs.wisc.edu/~remzi/OSTEP/)
- **練習**
  1. 用 `htop` 觀察優先級
  2. malloc/free 模擬

### Day 9 - ROS2 架構與安裝
- **資源**
  - [ROS2 Docs](https://docs.ros.org/en/humble/)
- **練習**
  1. 安裝 ROS2 Humble
  2. 建立 `my_first_pkg`

### Day 10 - ROS2 節點與話題
- **練習**
  1. C++/Python 節點互傳
  2. `ros2 topic echo` 觀察

---

## 第 3 週：ROS2 進階 & 模擬

### Day 11 - ROS2 服務、動作、參數
- **練習**
  1. ROS Service 計平方
  2. 動態參數調整

### Day 12 - ROS + Gazebo / RViz
- **練習**
  1. Gazebo 載入 TurtleBot3
  2. RViz 顯示位置

### Day 13 - 機器人運動模型與控制
- **練習**
  1. `cmd_vel` 控制前進
  2. 旋轉 90°

### Day 14 - 感測器資料處理
- **練習**
  1. 訂閱 LiDAR 計最短距離

### Day 15 - ROS + OpenCV
- **練習**
  1. 灰階轉換
  2. 邊緣檢測

---

## 第 4 週：導航、SLAM、專題

### Day 16 - SLAM 與 gmapping
- **練習**
  1. LiDAR 建地圖
  2. 存 `.pgm`

### Day 17 - 路徑規劃與導航
- **練習**
  1. 設導航目標

### Day 18 - 軟體整合與 Git
- **練習**
  1. ROS2 專案 Git 倉庫
  2. branch 與 PR

### Day 19 - 專題實作
- **練習**
  1. 自動避障
  2. 顏色追蹤

### Day 20 - 專題發表
- **練習**
  1. 撰寫 README
  2. Demo
