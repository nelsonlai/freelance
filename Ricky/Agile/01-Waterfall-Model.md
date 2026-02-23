# Waterfall 瀑布式開發模型

## 📖 目錄
- [定義與起源](#定義與起源)
- [核心原則](#核心原則)
- [開發階段](#開發階段)
- [優點與缺點](#優點與缺點)
- [適用場景](#適用場景)
- [實際執行範例](#實際執行範例)

---

## 定義與起源

### 什麼是 Waterfall？

Waterfall（瀑布式）開發模型是一種**線性序列式**的軟體開發方法論，由 Winston Royce 在 1970 年提出。如同瀑布從高處向下流動，開發流程按照固定的階段順序進行，每個階段完成後才能進入下一階段。

### 核心特徵

```
需求分析 ➜ 系統設計 ➜ 實作 ➜ 測試 ➜ 部署 ➜ 維護
   ⬇️        ⬇️       ⬇️     ⬇️     ⬇️      ⬇️
```

- **單向流動**：階段之間按順序進行
- **階段明確**：每個階段有清晰的目標和產出物
- **文檔驅動**：每階段需完整文檔才能進入下一階段
- **變更困難**：回到前一階段的成本高昂

---

## 核心原則

### 1. 階段性完成

每個階段必須完全完成並經過審查，才能進入下一階段。

**檢查點（Gate）**：
- ✅ 階段產出物完成
- ✅ 文檔審查通過
- ✅ 利害關係人簽核

### 2. 文檔為王

每個階段都需要產生詳細的文檔：
- 需求規格書（SRS）
- 系統設計文檔（SDD）
- 測試計劃與測試報告
- 使用者手冊

### 3. 需求凍結

在進入設計階段前，需求必須完全確定並凍結，後續變更需要正式的變更控制流程。

### 4. 品質把關

每個階段都有明確的品質標準和審查機制。

---

## 開發階段

### 階段 1：需求分析（Requirements Analysis）

**目標**：完整收集並記錄系統需求

#### 活動內容
1. **需求收集**
   - 與客戶/使用者訪談
   - 分析現有系統
   - 收集業務流程文件
   - 競品分析

2. **需求分析**
   - 功能需求（Functional Requirements）
   - 非功能需求（Non-functional Requirements）
     - 效能要求
     - 安全要求
     - 可用性要求
     - 擴展性要求

3. **需求文檔化**
   - 撰寫需求規格書（SRS）
   - 使用案例圖（Use Case Diagram）
   - 流程圖（Flow Chart）

#### 產出物
- ✅ 需求規格書（Software Requirements Specification）
- ✅ 使用案例文檔
- ✅ 需求追蹤矩陣

#### 時間佔比
通常佔整個專案的 **10-15%**

---

### 階段 2：系統設計（System Design）

**目標**：將需求轉換為系統架構和詳細設計

#### 2.1 高階設計（High-Level Design, HLD）

1. **系統架構設計**
   ```
   ┌─────────────┐
   │ 前端層      │ ← Web/Mobile UI
   ├─────────────┤
   │ 業務邏輯層  │ ← API/Services
   ├─────────────┤
   │ 資料存取層  │ ← Database Access
   ├─────────────┤
   │ 資料庫層    │ ← MySQL/PostgreSQL
   └─────────────┘
   ```

2. **技術選型**
   - 程式語言
   - 框架與函式庫
   - 資料庫系統
   - 部署平台

3. **模組劃分**
   - 系統模組圖
   - 模組間介面定義

#### 2.2 低階設計（Low-Level Design, LLD）

1. **詳細設計**
   - 類別圖（Class Diagram）
   - 序列圖（Sequence Diagram）
   - 狀態圖（State Diagram）

2. **資料庫設計**
   - ER 圖（Entity-Relationship Diagram）
   - 資料表結構
   - 索引設計

3. **API 設計**
   - RESTful API 規格
   - 請求/回應格式
   - 錯誤處理機制

#### 產出物
- ✅ 系統設計文檔（SDD）
- ✅ 資料庫設計文檔
- ✅ API 規格書
- ✅ 介面設計文檔

#### 時間佔比
通常佔整個專案的 **15-20%**

---

### 階段 3：實作（Implementation/Coding）

**目標**：根據設計文檔進行程式開發

#### 活動內容

1. **環境建置**
   - 開發環境設定
   - 版本控制系統
   - CI/CD 管道建立

2. **編碼實作**
   - 遵循設計文檔
   - 遵循編碼標準
   - 程式碼審查（Code Review）
   - 單元測試撰寫

3. **文檔維護**
   - 程式碼註解
   - API 文檔
   - 技術筆記

#### 開發規範

```python
# 範例：遵循編碼標準
class UserService:
    """
    使用者服務類別
    負責處理使用者相關的業務邏輯
    """
    
    def __init__(self, database):
        """初始化使用者服務"""
        self.db = database
    
    def create_user(self, username, email, password):
        """
        創建新使用者
        
        Args:
            username (str): 使用者名稱
            email (str): 電子郵件
            password (str): 密碼（將被加密）
        
        Returns:
            User: 創建的使用者物件
        
        Raises:
            ValidationError: 當輸入資料不合法
        """
        # 實作邏輯...
        pass
```

#### 產出物
- ✅ 源代碼
- ✅ 單元測試
- ✅ 程式碼文檔
- ✅ 建置腳本

#### 時間佔比
通常佔整個專案的 **30-40%**

---

### 階段 4：測試（Testing）

**目標**：確保系統符合需求並達到品質標準

#### 測試層級

1. **單元測試（Unit Testing）**
   - 測試個別函式/方法
   - 由開發人員執行
   - 自動化測試

2. **整合測試（Integration Testing）**
   - 測試模組間的互動
   - 測試 API 整合
   - 測試第三方服務整合

3. **系統測試（System Testing）**
   - 完整系統功能測試
   - 效能測試
   - 安全測試
   - 壓力測試

4. **驗收測試（Acceptance Testing）**
   - 使用者驗收測試（UAT）
   - 與需求規格書對照
   - 客戶簽核

#### 測試流程

```
1. 測試計劃
   ├─ 測試範圍
   ├─ 測試策略
   └─ 測試時程

2. 測試案例設計
   ├─ 功能測試案例
   ├─ 邊界測試案例
   └─ 異常測試案例

3. 測試執行
   ├─ 執行測試
   ├─ 記錄缺陷
   └─ 追蹤修正

4. 測試報告
   ├─ 測試覆蓋率
   ├─ 缺陷統計
   └─ 品質評估
```

#### 產出物
- ✅ 測試計劃
- ✅ 測試案例
- ✅ 測試報告
- ✅ 缺陷追蹤記錄

#### 時間佔比
通常佔整個專案的 **20-25%**

---

### 階段 5：部署（Deployment）

**目標**：將系統部署到生產環境

#### 活動內容

1. **部署準備**
   - 環境準備（正式環境）
   - 資料遷移計劃
   - 回滾計劃
   - 監控設定

2. **部署執行**
   ```bash
   # 部署檢查清單
   □ 備份現有系統
   □ 資料庫遷移
   □ 應用程式部署
   □ 設定檔更新
   □ 煙霧測試（Smoke Testing）
   □ 效能監控確認
   ```

3. **使用者培訓**
   - 使用者手冊
   - 教育訓練課程
   - 操作示範

4. **上線支援**
   - 技術支援待命
   - 問題快速回應
   - 使用監控

#### 產出物
- ✅ 部署文檔
- ✅ 使用者手冊
- ✅ 操作手冊
- ✅ 培訓教材

#### 時間佔比
通常佔整個專案的 **5-10%**

---

### 階段 6：維護（Maintenance）

**目標**：系統上線後的持續支援與改進

#### 維護類型

1. **修正性維護（Corrective）**
   - 修復 Bug
   - 解決系統問題

2. **適應性維護（Adaptive）**
   - 配合環境變化
   - 作業系統升級
   - 第三方服務更新

3. **完善性維護（Perfective）**
   - 功能增強
   - 效能優化
   - 使用者體驗改善

4. **預防性維護（Preventive）**
   - 程式碼重構
   - 技術債務清理
   - 安全性更新

#### 產出物
- ✅ 維護報告
- ✅ 更新紀錄
- ✅ 問題追蹤

#### 時間佔比
這是**長期持續**的階段，通常是開發時間的 2-3 倍

---

## 優點與缺點

### ✅ 優點

#### 1. 結構清晰
- 每個階段目標明確
- 易於理解和管理
- 適合大型團隊協作

#### 2. 文檔完整
- 詳細的文檔記錄
- 便於知識傳承
- 易於追蹤與稽核

#### 3. 易於管理
- 進度容易追蹤
- 預算容易控制
- 階段性里程碑明確

#### 4. 品質控制
- 每階段都有審查機制
- 問題早期發現
- 符合標準規範

#### 5. 適合固定需求
- 需求明確不變的專案
- 合約型專案
- 政府標案

### ❌ 缺點

#### 1. 缺乏彈性
- 需求變更成本高
- 難以適應市場變化
- 回到前一階段困難

#### 2. 風險集中
- 問題到測試階段才發現
- 整合風險高
- 失敗成本大

#### 3. 回饋延遲
- 客戶要到最後才看到成果
- 誤解需求的風險高
- 無法快速調整方向

#### 4. 時間冗長
- 完整週期時間長
- 市場機會可能錯過
- 投資回報週期長

#### 5. 文檔負擔
- 需要大量文檔維護
- 文檔與實作可能不同步
- 耗費大量時間在文書工作

---

## 適用場景

### ✅ 適合使用 Waterfall 的情況

#### 1. 需求明確且穩定
```
範例：政府電子化表單系統
- 需求由法規明確定義
- 不會頻繁變更
- 需要完整的文檔記錄
```

#### 2. 技術成熟且風險低
```
範例：傳統 CRUD 應用系統
- 使用成熟技術
- 類似專案經驗豐富
- 技術風險可控
```

#### 3. 大型基礎建設專案
```
範例：銀行核心系統升級
- 需要嚴格的變更管理
- 涉及多個部門協調
- 必須確保穩定性
```

#### 4. 合規性要求高
```
範例：醫療資訊系統
- 需要符合法規要求
- 必須有完整文檔
- 需要稽核追蹤
```

#### 5. 固定價格合約
```
範例：外包開發專案
- 範圍需要明確定義
- 預算固定
- 交付物明確
```

### ❌ 不適合使用 Waterfall 的情況

- 需求不明確或會頻繁變更
- 創新型或實驗性專案
- 需要快速上市的產品
- 使用者需求需要驗證
- 新技術探索專案

---

## 實際執行範例

### 案例：線上購物網站開發

讓我們透過一個完整的範例，看看 Waterfall 如何實際執行。

#### 專案背景
- **專案名稱**：企業電商平台
- **客戶**：傳統零售商轉型線上
- **預算**：500 萬台幣
- **時程**：12 個月
- **團隊**：20 人

---

### 階段 1：需求分析（月份 1-2）

#### Week 1-2：需求收集

**活動**
```
1. 利害關係人訪談
   - 業務部門：了解銷售流程
   - IT 部門：了解現有系統
   - 客服部門：了解客戶痛點
   - 倉儲部門：了解物流流程

2. 現狀分析
   - 分析現有紙本訂單流程
   - 分析競爭對手網站
   - 收集客戶回饋

3. 工作坊
   - 舉辦需求工作坊
   - 腦力激盪功能需求
   - 確定優先順序
```

#### Week 3-6：需求分析與文檔

**功能需求**
```
1. 會員系統
   - 會員註冊/登入
   - 個人資料管理
   - 會員等級制度
   - 點數累積

2. 商品管理
   - 商品瀏覽
   - 商品搜尋
   - 商品分類
   - 商品詳情

3. 購物車
   - 加入購物車
   - 修改數量
   - 刪除商品
   - 計算總價

4. 結帳系統
   - 選擇配送方式
   - 選擇付款方式
   - 優惠券使用
   - 訂單確認

5. 訂單管理
   - 訂單查詢
   - 訂單追蹤
   - 訂單取消
   - 退貨處理

6. 後台管理
   - 商品管理
   - 訂單管理
   - 會員管理
   - 報表分析
```

**非功能需求**
```
效能需求：
- 首頁載入時間 < 2 秒
- 支援 10,000 同時線上使用者
- 資料庫查詢回應時間 < 100ms

安全需求：
- SSL/TLS 加密
- 符合 PCI DSS 標準（信用卡）
- 定期安全掃描
- 符合 GDPR 資料保護

可用性需求：
- 系統可用率 99.9%
- 支援 RWD 響應式設計
- 支援主流瀏覽器
```

**產出物**
- ✅ 需求規格書（200 頁）
- ✅ 使用案例文檔（50 個使用案例）
- ✅ 原型圖（Wireframe）
- ✅ 需求簽核

#### 檢查點審查
```
審查項目：
□ 所有需求都有編號
□ 需求可測試
□ 需求之間無衝突
□ 優先順序已確定
□ 客戶已簽核

簽核：客戶、專案經理、技術總監
```

---

### 階段 2：系統設計（月份 3-4）

#### Week 7-10：高階設計

**系統架構**
```
┌────────────────────────────────────────┐
│            Load Balancer               │
└────────┬───────────────────────────────┘
         │
    ┌────┴────┐
    │         │
┌───▼───┐ ┌──▼────┐
│Web    │ │Web    │  ← Nginx + React SPA
│Server1│ │Server2│
└───┬───┘ └──┬────┘
    │        │
    └────┬───┘
         │
┌────────▼─────────┐
│  API Gateway     │
└────────┬─────────┘
         │
    ┌────┴────┐
    │         │
┌───▼───┐ ┌──▼────┐
│API    │ │API    │  ← Node.js + Express
│Server1│ │Server2│
└───┬───┘ └──┬────┘
    │        │
    └────┬───┘
         │
    ┌────┴────┐
    │         │
┌───▼───┐ ┌──▼────┐
│Cache  │ │Message│  ← Redis, RabbitMQ
│       │ │Queue  │
└───────┘ └───────┘
         │
┌────────▼─────────┐
│   MySQL Master   │  ← 主資料庫
└────────┬─────────┘
         │
    ┌────┴────┐
┌───▼───┐ ┌──▼────┐
│MySQL  │ │MySQL  │  ← 從資料庫（讀取分離）
│Slave1 │ │Slave2 │
└───────┘ └───────┘
```

**技術選型決策**
```
前端：
- React 18
- TypeScript
- Ant Design UI
- Redux Toolkit

後端：
- Node.js 20
- Express.js
- TypeScript
- JWT 認證

資料庫：
- MySQL 8.0（主資料庫）
- Redis（快取、Session）
- Elasticsearch（商品搜尋）

第三方服務：
- AWS S3（圖片儲存）
- SendGrid（Email）
- Twilio（SMS）
- Stripe（金流）
```

#### Week 11-12：低階設計

**資料庫設計**
```sql
-- 使用者表
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    email VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    full_name VARCHAR(100),
    phone VARCHAR(20),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    INDEX idx_email (email)
);

-- 商品表
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    category_id INT,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2) NOT NULL,
    stock_quantity INT DEFAULT 0,
    image_url VARCHAR(500),
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    INDEX idx_category (category_id),
    INDEX idx_name (name),
    FOREIGN KEY (category_id) REFERENCES categories(category_id)
);

-- 訂單表
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    total_amount DECIMAL(10, 2) NOT NULL,
    status ENUM('pending', 'paid', 'shipped', 'completed', 'cancelled'),
    shipping_address TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    INDEX idx_user (user_id),
    INDEX idx_status (status),
    INDEX idx_created (created_at),
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- 訂單明細表
CREATE TABLE order_items (
    order_item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL,
    unit_price DECIMAL(10, 2) NOT NULL,
    subtotal DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);
```

**API 設計範例**
```javascript
/**
 * 商品 API 規格
 */

// 1. 取得商品列表
GET /api/v1/products
Query Parameters:
  - page: 頁碼（預設 1）
  - limit: 每頁筆數（預設 20）
  - category: 分類 ID
  - keyword: 搜尋關鍵字
  - sort: 排序方式（price_asc, price_desc, newest）

Response 200:
{
  "success": true,
  "data": {
    "products": [
      {
        "product_id": 1,
        "name": "商品名稱",
        "price": 999,
        "image_url": "https://...",
        "stock_quantity": 100
      }
    ],
    "pagination": {
      "current_page": 1,
      "total_pages": 10,
      "total_count": 200
    }
  }
}

// 2. 取得商品詳情
GET /api/v1/products/:productId

Response 200:
{
  "success": true,
  "data": {
    "product_id": 1,
    "name": "商品名稱",
    "description": "商品描述...",
    "price": 999,
    "stock_quantity": 100,
    "category": {
      "category_id": 5,
      "name": "3C產品"
    },
    "images": [
      "https://...",
      "https://..."
    ]
  }
}

// 3. 建立訂單
POST /api/v1/orders
Headers:
  Authorization: Bearer {token}

Request Body:
{
  "items": [
    {
      "product_id": 1,
      "quantity": 2
    }
  ],
  "shipping_address": {
    "name": "收件人",
    "phone": "0912345678",
    "address": "台北市..."
  },
  "payment_method": "credit_card"
}

Response 201:
{
  "success": true,
  "data": {
    "order_id": 12345,
    "total_amount": 1998,
    "status": "pending",
    "created_at": "2026-02-13T10:30:00Z"
  }
}
```

**產出物**
- ✅ 系統設計文檔（150 頁）
- ✅ 資料庫設計文檔（50 頁）
- ✅ API 規格書（100 個 API）
- ✅ UI/UX 設計稿
- ✅ 設計審查通過

---

### 階段 3：實作（月份 5-9）

#### Month 5：環境建置與基礎架構

**Week 13-14：開發環境**
```bash
# 專案結構建立
ecommerce-platform/
├── frontend/          # React 前端
│   ├── src/
│   ├── public/
│   └── package.json
├── backend/           # Node.js 後端
│   ├── src/
│   ├── tests/
│   └── package.json
├── database/          # 資料庫腳本
│   ├── migrations/
│   └── seeds/
├── docs/              # 文檔
└── docker-compose.yml # Docker 配置
```

**Week 15-16：CI/CD 建立**
```yaml
# .github/workflows/ci.yml
name: CI/CD Pipeline

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Run Tests
        run: npm test
      - name: Code Coverage
        run: npm run coverage
  
  build:
    needs: test
    runs-on: ubuntu-latest
    steps:
      - name: Build Docker Image
        run: docker build -t app:${{ github.sha }} .
      - name: Push to Registry
        run: docker push app:${{ github.sha }}
  
  deploy:
    needs: build
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    steps:
      - name: Deploy to Production
        run: ./deploy.sh
```

#### Month 6-8：核心功能開發

**開發排程**
```
Month 6: 基礎模組
  Week 17-18: 使用者認證系統
  Week 19-20: 商品管理模組

Month 7: 交易模組
  Week 21-22: 購物車功能
  Week 23-24: 結帳流程

Month 8: 後台與整合
  Week 25-26: 後台管理系統
  Week 27-28: 第三方服務整合
```

**實作範例：購物車功能**
```typescript
// backend/src/services/CartService.ts

import { Cart, CartItem } from '../models';
import { ProductService } from './ProductService';

export class CartService {
  private productService: ProductService;

  constructor(productService: ProductService) {
    this.productService = productService;
  }

  /**
   * 加入商品到購物車
   */
  async addToCart(
    userId: number,
    productId: number,
    quantity: number
  ): Promise<Cart> {
    // 1. 驗證商品存在且有足夠庫存
    const product = await this.productService.getById(productId);
    if (!product) {
      throw new Error('商品不存在');
    }
    if (product.stock_quantity < quantity) {
      throw new Error('庫存不足');
    }

    // 2. 取得或建立購物車
    let cart = await Cart.findOne({ where: { user_id: userId } });
    if (!cart) {
      cart = await Cart.create({ user_id: userId });
    }

    // 3. 檢查商品是否已在購物車
    const existingItem = await CartItem.findOne({
      where: {
        cart_id: cart.cart_id,
        product_id: productId
      }
    });

    if (existingItem) {
      // 更新數量
      existingItem.quantity += quantity;
      await existingItem.save();
    } else {
      // 新增商品
      await CartItem.create({
        cart_id: cart.cart_id,
        product_id: productId,
        quantity: quantity,
        unit_price: product.price
      });
    }

    // 4. 重新計算購物車總額
    await this.updateCartTotal(cart.cart_id);

    return this.getCart(userId);
  }

  /**
   * 取得購物車內容
   */
  async getCart(userId: number): Promise<Cart> {
    const cart = await Cart.findOne({
      where: { user_id: userId },
      include: [
        {
          model: CartItem,
          include: [Product]
        }
      ]
    });

    if (!cart) {
      // 建立空購物車
      return Cart.create({ user_id: userId });
    }

    return cart;
  }

  /**
   * 更新購物車總額
   */
  private async updateCartTotal(cartId: number): Promise<void> {
    const items = await CartItem.findAll({
      where: { cart_id: cartId }
    });

    const total = items.reduce((sum, item) => {
      return sum + (item.unit_price * item.quantity);
    }, 0);

    await Cart.update(
      { total_amount: total },
      { where: { cart_id: cartId } }
    );
  }

  /**
   * 清空購物車
   */
  async clearCart(userId: number): Promise<void> {
    const cart = await Cart.findOne({ where: { user_id: userId } });
    if (cart) {
      await CartItem.destroy({ where: { cart_id: cart.cart_id } });
      await Cart.update(
        { total_amount: 0 },
        { where: { cart_id: cart.cart_id } }
      );
    }
  }
}
```

**單元測試範例**
```typescript
// backend/src/services/__tests__/CartService.test.ts

import { CartService } from '../CartService';
import { ProductService } from '../ProductService';

describe('CartService', () => {
  let cartService: CartService;
  let productService: ProductService;

  beforeEach(() => {
    productService = new ProductService();
    cartService = new CartService(productService);
  });

  describe('addToCart', () => {
    it('應該成功加入商品到購物車', async () => {
      // Arrange
      const userId = 1;
      const productId = 101;
      const quantity = 2;

      // Mock product service
      jest.spyOn(productService, 'getById').mockResolvedValue({
        product_id: 101,
        name: '測試商品',
        price: 500,
        stock_quantity: 10
      });

      // Act
      const cart = await cartService.addToCart(userId, productId, quantity);

      // Assert
      expect(cart).toBeDefined();
      expect(cart.items).toHaveLength(1);
      expect(cart.items[0].quantity).toBe(2);
      expect(cart.total_amount).toBe(1000);
    });

    it('庫存不足時應該拋出錯誤', async () => {
      // Arrange
      const userId = 1;
      const productId = 101;
      const quantity = 20;

      jest.spyOn(productService, 'getById').mockResolvedValue({
        product_id: 101,
        name: '測試商品',
        price: 500,
        stock_quantity: 10  // 只有 10 個庫存
      });

      // Act & Assert
      await expect(
        cartService.addToCart(userId, productId, quantity)
      ).rejects.toThrow('庫存不足');
    });
  });
});
```

#### Month 9：程式碼審查與優化

**Week 29-30：程式碼審查**
```
審查項目：
□ 程式碼符合編碼標準
□ 所有函式都有註解
□ 單元測試覆蓋率 > 80%
□ 無明顯效能問題
□ 安全性檢查通過
□ 無硬編碼的敏感資訊
```

**Week 31-32：效能優化**
- 資料庫查詢優化
- API 回應時間優化
- 前端打包優化
- 圖片壓縮與 CDN

---

### 階段 4：測試（月份 10-11）

#### Month 10：系統測試

**Week 33-34：功能測試**
```
測試案例範例：結帳流程

測試編號：TC-001
測試項目：正常結帳流程
前置條件：
  1. 使用者已登入
  2. 購物車有商品
  3. 商品有足夠庫存

測試步驟：
  1. 點選「前往結帳」按鈕
  2. 填寫配送地址
  3. 選擇付款方式「信用卡」
  4. 填寫信用卡資訊
  5. 點選「確認訂單」

預期結果：
  ✓ 顯示訂單確認頁面
  ✓ 訂單狀態為「待付款」
  ✓ 庫存正確扣除
  ✓ 發送確認 Email
  ✓ 購物車已清空

測試編號：TC-002
測試項目：庫存不足處理
...
```

**Week 35-36：效能測試**
```bash
# 使用 Apache JMeter 進行壓力測試

測試場景 1：首頁載入
- 並發使用者：1000
- 持續時間：10 分鐘
- 目標：回應時間 < 2 秒

測試場景 2：商品搜尋
- 並發使用者：500
- 搜尋查詢：100 種不同關鍵字
- 目標：回應時間 < 1 秒

測試場景 3：結帳流程
- 並發使用者：200
- 持續時間：30 分鐘
- 目標：成功率 > 99%
```

#### Month 11：驗收測試

**Week 37-38：UAT 準備**
```
1. 建立 UAT 環境
2. 準備測試資料
3. 建立 UAT 測試案例
4. 培訓測試人員
```

**Week 39-40：UAT 執行**
```
參與人員：
- 業務部門（5 人）
- 客服部門（3 人）
- IT 部門（2 人）

測試重點：
✓ 業務流程是否符合需求
✓ 使用介面是否友善
✓ 報表是否正確
✓ 效能是否可接受

缺陷追蹤：
- 嚴重缺陷：5 個（已修復）
- 中等缺陷：12 個（已修復）
- 輕微缺陷：20 個（排程修復）
```

**產出物**
- ✅ 測試計劃書
- ✅ 測試案例（500+ 個）
- ✅ 測試執行報告
- ✅ 缺陷追蹤報告
- ✅ UAT 簽核文件

---

### 階段 5：部署（月份 12）

#### Week 41-42：部署準備

**基礎設施準備**
```bash
# AWS 資源配置

1. VPC 網路設定
   - Public Subnet（Load Balancer）
   - Private Subnet（應用伺服器）
   - Database Subnet（資料庫）

2. EC2 實例
   - Web Server: t3.large x 2
   - API Server: t3.xlarge x 2
   - Redis: t3.medium x 1

3. RDS 資料庫
   - MySQL 8.0
   - db.t3.large
   - Multi-AZ 部署

4. S3 儲存
   - 商品圖片
   - 靜態資源

5. CloudFront CDN
   - 前端資源分發
   - 圖片快取
```

**資料遷移計劃**
```
1. 商品資料遷移
   ├─ 從舊系統匯出 CSV
   ├─ 資料清理與驗證
   ├─ 圖片上傳至 S3
   └─ 匯入新系統

2. 會員資料遷移
   ├─ 匯出會員清單
   ├─ 密碼重置通知
   └─ 匯入新系統

3. 歷史訂單遷移
   ├─ 近 3 年訂單資料
   └─ 供查詢用途
```

#### Week 43：正式部署

**部署檢查清單**
```
D-Day 前一週：
□ 完整備份現有系統
□ DNS 設定準備
□ SSL 憑證安裝
□ 監控系統設定
□ 告警機制測試

D-Day（部署日）：
時間軸（凌晨 2:00 開始，預估 4 小時）

02:00 - 02:30
□ 公告系統維護
□ 關閉舊系統
□ 最終備份

02:30 - 03:30
□ 資料庫遷移
□ 資料驗證
□ 應用程式部署

03:30 - 04:30
□ 煙霧測試
□ 效能監控
□ 功能驗證

04:30 - 05:00
□ DNS 切換
□ 全面測試
□ 監控觀察

05:00 - 06:00
□ 開放使用
□ 密切監控
□ 準備緊急回滾

D-Day 後：
□ 持續監控 24 小時
□ 收集使用者反饋
□ 準備修正更新
```

**部署腳本範例**
```bash
#!/bin/bash
# deploy.sh

set -e  # 遇到錯誤立即停止

echo "========================================="
echo "開始部署電商平台"
echo "時間: $(date)"
echo "========================================="

# 1. 備份資料庫
echo "1. 備份資料庫..."
mysqldump -u root -p database_name > backup_$(date +%Y%m%d_%H%M%S).sql

# 2. 拉取最新代碼
echo "2. 拉取最新代碼..."
git pull origin main

# 3. 安裝依賴
echo "3. 安裝後端依賴..."
cd backend && npm install --production

echo "4. 建置前端..."
cd ../frontend && npm install && npm run build

# 5. 資料庫遷移
echo "5. 執行資料庫遷移..."
cd ../backend && npm run migrate

# 6. 重啟服務
echo "6. 重啟應用服務..."
pm2 restart ecommerce-api

# 7. 健康檢查
echo "7. 健康檢查..."
sleep 5
curl -f http://localhost:3000/health || exit 1

echo "========================================="
echo "部署完成！"
echo "========================================="
```

#### Week 44：使用者培訓與上線支援

**教育訓練**
```
對象：內部員工（30 人）

Day 1: 前台使用培訓
- 商品瀏覽與搜尋
- 會員註冊與登入
- 購物與結帳流程
- 訂單查詢

Day 2: 後台管理培訓
- 商品上架與管理
- 訂單處理流程
- 會員管理
- 報表查詢

Day 3: 客服培訓
- 常見問題處理
- 系統問題回報
- 緊急聯絡流程
```

**上線支援**
```
支援期間：上線後 2 週

支援團隊（24小時待命）：
- 專案經理 x 1
- 後端工程師 x 2
- 前端工程師 x 1
- DBA x 1

監控項目：
✓ 系統可用率
✓ API 回應時間
✓ 錯誤日誌
✓ 使用者反饋
✓ 訂單成功率

應變措施：
- P0（系統無法使用）：立即回滾
- P1（重大功能異常）：2 小時內修復
- P2（次要功能異常）：24 小時內修復
- P3（介面問題）：7 天內修復
```

**產出物**
- ✅ 部署文檔
- ✅ 運維手冊
- ✅ 使用者手冊
- ✅ 培訓教材
- ✅ 上線報告

---

### 階段 6：維護（持續進行）

#### 維護計劃

**第一個月（上線後）**
```
Week 1-2: 密集監控期
- 每日檢視系統日誌
- 收集使用者反饋
- 快速修復緊急問題

Week 3-4: 優化調整期
- 效能調優
- 使用者體驗改善
- 小功能增強
```

**長期維護**
```
每月活動：
□ 安全性更新
□ 效能報告
□ 備份檢查
□ 容量規劃

每季活動：
□ 系統健檢
□ 使用者滿意度調查
□ 功能優先順序檢視
□ 技術債務清理

每年活動：
□ 重大功能升級
□ 技術架構檢視
□ 災難復原演練
□ 合約續約評估
```

---

## 專案總結

### 時間軸總覽
```
月份 1-2:  需求分析 ████████░░░░░░░░░░░░░░
月份 3-4:  系統設計 ░░░░░░░░████████░░░░░░░░
月份 5-9:  實作開發 ░░░░░░░░░░░░░░░░████████
月份 10-11: 測試階段 ░░░░░░░░░░░░░░░░░░░░████
月份 12:   部署上線 ░░░░░░░░░░░░░░░░░░░░░░██
```

### 資源投入
```
人力配置：
- 專案經理: 1 人 x 12 個月
- 系統分析師: 2 人 x 4 個月
- 架構師: 1 人 x 6 個月
- 後端工程師: 5 人 x 8 個月
- 前端工程師: 4 人 x 7 個月
- UI/UX 設計師: 2 人 x 5 個月
- QA 測試: 3 人 x 4 個月
- DBA: 1 人 x 12 個月
- DevOps: 1 人 x 12 個月

總人月: 約 120 人月
```

### 交付成果
```
✅ 功能完整的電商平台
✅ 完整的系統文檔（600+ 頁）
✅ 使用者手冊與培訓教材
✅ 源代碼（50,000+ 行）
✅ 測試案例（500+ 個）
✅ 自動化測試腳本
✅ 部署與運維文檔
```

### 關鍵成功因素
1. ✅ 需求在早期就凍結
2. ✅ 每階段都有嚴格的審查
3. ✅ 充足的測試時間
4. ✅ 完整的文檔記錄
5. ✅ 有經驗的團隊

### 遇到的挑戰
1. ⚠️ 需求變更（2 次重大變更）
2. ⚠️ 第三方 API 延遲整合
3. ⚠️ 效能調優花費額外時間
4. ⚠️ UAT 發現重大缺陷需要修正

---

## 最佳實踐建議

### 1. 需求管理
- 📋 需求變更必須經過正式的變更控制流程
- 📋 每個需求都要有可追蹤的編號
- 📋 需求優先順序要明確

### 2. 文檔管理
- 📄 使用版本控制管理文檔
- 📄 定期審查文檔與實作的一致性
- 📄 文檔格式統一，易於維護

### 3. 品質控制
- ✅ 每個階段都有明確的完成標準
- ✅ 建立自動化測試
- ✅ 程式碼審查機制

### 4. 風險管理
- 🎯 識別關鍵路徑
- 🎯 預留緩衝時間（20-30%）
- 🎯 定期風險檢視會議

### 5. 溝通管理
- 💬 定期專案報告（週報、月報）
- 💬 利害關係人定期溝通
- 💬 問題升級機制

---

## 延伸閱讀

1. **IEEE 12207** - 軟體生命週期流程標準
2. **PMBOK** - 專案管理知識體系指南
3. **SWEBOK** - 軟體工程知識體系

---

[返回目錄](./README.md) | [下一章：Agile/Scrum 敏捷開發](./02-Agile-Scrum.md)
