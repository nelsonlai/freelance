# 具體執行指南與範例

## 📖 目錄
- [Waterfall 執行指南](#waterfall-執行指南)
- [Scrum 執行指南](#scrum-執行指南)
- [實用工具與模板](#實用工具與模板)
- [檢查清單](#檢查清單)
- [常見問題解答](#常見問題解答)

---

## Waterfall 執行指南

### 完整執行步驟

讓我們通過一個實際專案逐步說明 Waterfall 的執行。

**專案範例**：企業 ERP 系統導入

```
專案規模：中大型
預算：2,000 萬台幣
時程：18 個月
團隊：30 人
```

---

### 階段 1：需求分析（Month 1-3）

#### Week 1-2：專案啟動

**1.1 組建專案團隊**

```
核心團隊：
□ 專案經理（1人）
□ 系統分析師（3人）
□ 業務分析師（2人）
□ 技術顧問（1人）

涉及部門：
□ 財務部
□ 人資部
□ 採購部
□ 倉儲部
□ 業務部
```

**1.2 專案啟動會議**

```markdown
# 專案啟動會議議程

日期：2024-XX-XX
時間：09:00-17:00
地點：會議室 A

## 上午場（09:00-12:00）

### 1. 專案背景與目標（30 分鐘）
- 為什麼要導入 ERP？
- 預期達成的目標
- 成功的定義

### 2. 專案範圍說明（60 分鐘）
- 包含的模組
- 不包含的範圍
- 介面與整合需求

### 3. 專案組織與角色（30 分鐘）
- 組織架構圖
- 角色與職責說明
- 決策機制

### 4. 專案時程與里程碑（30 分鐘）
- 整體時程規劃
- 關鍵里程碑
- 各部門參與時間點

## 下午場（13:00-17:00）

### 5. 需求訪談規劃（60 分鐘）
- 訪談計劃
- 訪談對象
- 訪談重點

### 6. 溝通機制（30 分鐘）
- 定期會議安排
- 報告機制
- 問題升級流程

### 7. 風險識別（90 分鐘）
- 初步風險識別
- 風險應對策略
- 風險監控機制

### 8. Q&A 與共識（30 分鐘）
```

**1.3 建立專案文件架構**

```
專案文件結構/
├── 01-專案管理/
│   ├── 專案章程
│   ├── 專案計劃
│   ├── 風險登記簿
│   └── 變更記錄
│
├── 02-需求文件/
│   ├── 業務需求文件
│   ├── 功能需求規格
│   ├── 非功能需求
│   └── 需求追蹤矩陣
│
├── 03-設計文件/
│   ├── 系統架構設計
│   ├── 資料庫設計
│   ├── 介面設計
│   └── 安全設計
│
├── 04-開發文件/
│   ├── 程式碼規範
│   ├── 開發指南
│   └── 版本記錄
│
├── 05-測試文件/
│   ├── 測試計劃
│   ├── 測試案例
│   └── 測試報告
│
└── 06-部署文件/
    ├── 部署計劃
    ├── 使用者手冊
    └── 教育訓練教材
```

#### Week 3-8：需求收集與分析

**2.1 需求訪談計劃**

```markdown
# 需求訪談計劃

## 訪談對象分類

### 高階主管（C-Level）
對象：CEO, CFO, COO
目的：了解策略目標、關鍵成功因素
時間：各 1 小時
重點：
- 公司策略目標
- 對 ERP 的期望
- 關鍵績效指標（KPI）
- 預算與時程期望

### 部門主管
對象：財務、人資、採購、倉儲、業務主管
目的：了解部門流程與痛點
時間：各 2-3 小時
重點：
- 現有流程說明
- 目前問題與痛點
- 期望的改善
- 跨部門協作需求

### 實際使用者
對象：各部門資深使用者
目的：了解實際操作細節
時間：各 2-3 小時
重點：
- 日常作業流程
- 特殊情境處理
- 報表需求
- 系統期望功能
```

**2.2 訪談範例：財務部**

```markdown
# 財務部需求訪談記錄

日期：2024-XX-XX
訪談對象：財務經理王小明
訪談人：系統分析師李小華
時間：14:00-17:00

## 1. 現有流程說明

### 1.1 應收帳款流程
目前作業方式：
- 業務開立訂單（Excel）
- 倉儲出貨（紙本）
- 財務開立發票（手動輸入系統）
- 問題：資料重複輸入，容易出錯

流程圖：
[訂單] → [出貨] → [開發票] → [收款] → [核銷]
  ↓        ↓         ↓         ↓        ↓
Excel    紙本     手動輸入    銀行對帳   Excel

### 1.2 應付帳款流程
...（省略）

## 2. 主要痛點

痛點 1：資料重複輸入
- 同樣的訂單資料在多個系統重複輸入
- 耗時且容易出錯
- 每月因輸入錯誤需要更正約 50 筆

痛點 2：無法即時掌握應收帳款
- 資料分散在多個 Excel
- 需要手動彙整才能看到整體狀況
- 高階主管要報表需要 2-3 天準備時間

痛點 3：結帳時間過長
- 每月結帳需要 7 個工作天
- 大量人工對帳與調整
- 影響財務報表時效

## 3. 期望改善

期望 1：系統整合
- 訂單、出貨、開票資料自動串接
- 減少人工輸入

期望 2：即時報表
- 隨時可以查看應收帳款狀況
- 自動化的帳齡分析
- 視覺化儀表板

期望 3：加速結帳
- 自動化對帳
- 減少人工調整
- 目標：結帳時間縮短到 3 天

## 4. 功能需求（初步）

FR-001：應收帳款管理
- 發票管理
- 收款管理
- 核銷管理
- 帳齡分析

FR-002：應付帳款管理
...（省略）

FR-003：總帳管理
...（省略）

## 5. 非功能需求

NFR-001：效能
- 報表產生時間 < 5 秒（1 年資料）
- 查詢回應時間 < 2 秒

NFR-002：可用性
- 系統可用率 > 99.5%（營業時間）

NFR-003：安全性
- 符合個資法要求
- 帳務資料加密儲存
- 完整的操作日誌

## 6. 報表需求

報表 1：應收帳款明細表
- 內容：客戶、發票號碼、金額、到期日、逾期天數
- 頻率：每日
- 對象：財務人員

報表 2：應收帳款帳齡分析
- 內容：按帳齡區間統計金額
- 頻率：每週、每月
- 對象：財務主管、高階主管

...（省略其他報表）

## 7. 整合需求

整合 1：銀行系統
- 自動下載銀行對帳單
- 自動核銷收款

整合 2：電子發票系統
- 自動上傳發票至財政部
- 取得發票號碼

## 8. 下次訪談重點

□ 特殊交易類型處理（退貨、折讓）
□ 外幣交易流程
□ 月底結帳詳細流程
□ 預算編列與控管

## 9. 行動項目

□ 提供現有 Excel 範本
□ 提供上月財務報表範例
□ 安排與業務部聯合訪談（討論跨部門流程）
```

**2.3 需求文件撰寫**

```markdown
# 功能需求規格書（部分範例）

## FR-001：應收帳款管理

### 1. 功能概述
系統應提供完整的應收帳款管理功能，包含發票管理、收款管理、核銷管理及相關報表。

### 2. 使用者角色
- 財務人員：建立發票、登錄收款、執行核銷
- 財務主管：審核、查詢、報表
- 高階主管：查看儀表板、重要報表

### 3. 功能需求

#### FR-001-01：發票建立
**描述**：系統應能根據出貨單自動建立發票

**前置條件**：
- 出貨單已完成且經主管核准
- 客戶主檔已建立
- 產品價格已設定

**輸入**：
- 出貨單號
- 客戶代碼
- 發票日期
- 付款條件

**處理邏輯**：
1. 從出貨單取得產品明細
2. 根據客戶合約取得價格
3. 計算稅額（5%）
4. 產生發票號碼（流水號）
5. 儲存發票主檔與明細

**輸出**：
- 發票編號
- 發票列印格式
- 更新應收帳款餘額

**驗收標準**：
1. ✓ 系統能正確讀取出貨單資料
2. ✓ 價格計算正確（包含折扣、稅額）
3. ✓ 發票號碼唯一不重複
4. ✓ 應收帳款餘額正確更新
5. ✓ 發票可正確列印

**異常處理**：
- 若客戶信用額度已滿：警告訊息，需主管核准
- 若產品價格未設定：錯誤訊息，無法建立發票
- 若出貨單已開過發票：錯誤訊息，防止重複開票

**業務規則**：
- BR-001：發票日期不可早於出貨日期
- BR-002：發票金額 > 100 萬需主管核准
- BR-003：同一客戶同日多筆出貨可合併開立發票

**畫面配置**：
[此處應附上畫面設計原型圖]

#### FR-001-02：收款登錄
...（類似的詳細描述）

#### FR-001-03：自動核銷
...

### 4. 資料模型

```sql
-- 發票主檔
CREATE TABLE AR_INVOICE (
    invoice_no VARCHAR(20) PRIMARY KEY,
    customer_id VARCHAR(10) NOT NULL,
    invoice_date DATE NOT NULL,
    due_date DATE NOT NULL,
    subtotal DECIMAL(15,2),
    tax DECIMAL(15,2),
    total DECIMAL(15,2),
    status VARCHAR(10), -- OPEN, PAID, PARTIAL, CANCELLED
    created_by VARCHAR(20),
    created_date TIMESTAMP,
    FOREIGN KEY (customer_id) REFERENCES CUSTOMER(customer_id)
);

-- 發票明細
CREATE TABLE AR_INVOICE_DETAIL (
    invoice_no VARCHAR(20),
    line_no INT,
    product_id VARCHAR(20),
    quantity INT,
    unit_price DECIMAL(15,2),
    amount DECIMAL(15,2),
    PRIMARY KEY (invoice_no, line_no),
    FOREIGN KEY (invoice_no) REFERENCES AR_INVOICE(invoice_no)
);

-- 收款記錄
CREATE TABLE AR_RECEIPT (
    receipt_no VARCHAR(20) PRIMARY KEY,
    customer_id VARCHAR(10),
    receipt_date DATE,
    amount DECIMAL(15,2),
    payment_method VARCHAR(20),
    bank_account VARCHAR(30),
    status VARCHAR(10),
    created_by VARCHAR(20),
    created_date TIMESTAMP
);

-- 核銷記錄
CREATE TABLE AR_SETTLEMENT (
    settlement_id INT PRIMARY KEY AUTO_INCREMENT,
    invoice_no VARCHAR(20),
    receipt_no VARCHAR(20),
    amount DECIMAL(15,2),
    settlement_date DATE,
    created_by VARCHAR(20),
    created_date TIMESTAMP
);
```

### 5. 介面設計

#### 5.1 發票建立畫面
[Wireframe 或 Mockup]

#### 5.2 收款登錄畫面
[Wireframe 或 Mockup]

### 6. 報表需求

#### 6.1 應收帳款明細表
**報表編號**：RPT-AR-001

**用途**：顯示所有未結清的應收帳款明細

**欄位**：
- 客戶代碼、客戶名稱
- 發票號碼、發票日期
- 發票金額、已收金額、未收金額
- 到期日、逾期天數

**排序**：依到期日升序

**篩選條件**：
- 客戶（多選）
- 日期區間
- 是否顯示已結清

**輸出格式**：PDF, Excel

**範例**：
[附上報表範例圖]

### 7. 效能需求

- 發票建立：< 3 秒
- 收款登錄：< 2 秒
- 自動核銷（100 筆）：< 30 秒
- 應收帳款報表（1 年資料）：< 10 秒

### 8. 安全需求

- 只有財務人員可以建立/修改發票
- 金額修改需要留下審計軌跡
- 已核銷的發票不可刪除
- 敏感操作需要二次確認

### 9. 測試案例（範例）

#### TC-001-01：正常發票建立
前置條件：
- 測試客戶 C001 已建立
- 測試產品 P001 已建立並設定價格
- 測試出貨單 SO001 已完成

測試步驟：
1. 登入系統（財務人員帳號）
2. 進入「應收帳款」→「發票建立」
3. 輸入出貨單號：SO001
4. 選擇客戶：C001
5. 設定發票日期：今天
6. 點選「產生發票」
7. 確認發票內容
8. 點選「儲存」

預期結果：
✓ 系統產生發票號碼
✓ 發票金額計算正確
✓ 系統顯示「發票建立成功」訊息
✓ 可以列印發票
✓ 應收帳款餘額增加

#### TC-001-02：客戶信用額度已滿
...

#### TC-001-03：重複建立發票（負面測試）
...
```

**2.4 需求審查會議**

```markdown
# 需求審查會議

目的：確認需求文件的完整性與正確性

參與者：
- 專案經理
- 系統分析師
- 各部門主管
- 技術顧問
- 專案贊助人（高階主管）

審查重點：
□ 需求是否完整？有無遺漏？
□ 需求是否正確？符合業務需求？
□ 需求是否一致？有無矛盾？
□ 需求是否可行？技術上能實現？
□ 需求是否可測試？有明確的驗收標準？
□ 優先順序是否合理？

審查結果：
- 通過：進入下一階段
- 有條件通過：修正後再審查
- 不通過：重大缺失，需大幅修改

產出：
✓ 已簽核的需求規格書
✓ 需求基線（Baseline）
✓ 後續變更需要走變更控制流程
```

---

### 階段 2：系統設計（Month 4-6）

#### 高階設計

**3.1 系統架構設計**

```markdown
# 系統架構設計文件

## 1. 整體架構

### 1.1 架構圖

```
┌─────────────────────────────────────────────────────┐
│                    使用者層                          │
├───────────┬────────────┬────────────┬───────────────┤
│  Web      │  Mobile    │  報表      │   API         │
│  Browser  │  App       │  Portal    │   Consumers   │
└─────┬─────┴──────┬─────┴──────┬─────┴───────┬───────┘
      │            │            │             │
      └────────────┴────────────┴─────────────┘
                     │
      ┌──────────────▼──────────────┐
      │      Load Balancer          │
      │      (F5 / HAProxy)         │
      └──────────────┬──────────────┘
                     │
      ┌──────────────┴──────────────┐
      │                              │
┌─────▼─────┐              ┌────────▼────────┐
│  Web      │              │  Web            │
│  Server 1 │              │  Server 2       │
│  (IIS)    │              │  (IIS)          │
└─────┬─────┘              └────────┬────────┘
      │                              │
      └──────────────┬───────────────┘
                     │
      ┌──────────────▼──────────────┐
      │     Application Server      │
      │     (.NET Core / Java)      │
      ├─────────────────────────────┤
      │  ┌──────────────────────┐   │
      │  │  Business Logic      │   │
      │  │  - 財務模組          │   │
      │  │  - 人資模組          │   │
      │  │  - 採購模組          │   │
      │  │  - 倉儲模組          │   │
      │  └──────────────────────┘   │
      │  ┌──────────────────────┐   │
      │  │  Integration Layer   │   │
      │  │  - API Gateway       │   │
      │  │  - Message Queue     │   │
      │  └──────────────────────┘   │
      └──────────────┬──────────────┘
                     │
      ┌──────────────┴──────────────┐
      │                              │
┌─────▼─────┐              ┌────────▼────────┐
│ Database  │◄────────────►│  Database       │
│ Master    │  Replication │  Slave          │
│ (Oracle)  │              │  (Read Only)    │
└─────┬─────┘              └─────────────────┘
      │
      ▼
┌───────────────┐
│  Backup       │
│  Storage      │
└───────────────┘
```

### 1.2 技術選型

**前端**
- 框架：React 18
- 狀態管理：Redux Toolkit
- UI 組件：Ant Design
- 圖表：ECharts

**後端**
- 框架：.NET Core 8 / Spring Boot
- API：RESTful API
- 認證：JWT + OAuth 2.0
- 快取：Redis

**資料庫**
- 主資料庫：Oracle 19c / PostgreSQL
- 快取：Redis
- 全文搜尋：Elasticsearch

**中介軟體**
- Web Server：IIS / Nginx
- Message Queue：RabbitMQ / Kafka
- API Gateway：Kong / Azure API Management

**DevOps**
- CI/CD：Azure DevOps / GitLab CI
- 容器：Docker
- 編排：Kubernetes
- 監控：Prometheus + Grafana

### 1.3 部署架構

**正式環境**
- 雙機熱備援
- 資料庫主從複寫
- 自動化備份
- 災難復原計劃（RPO: 1小時, RTO: 4小時）

**測試環境**
- 與正式環境相同架構
- 資料脫敏

**開發環境**
- 簡化架構
- 本地開發環境（Docker Compose）

## 2. 模組設計

### 2.1 模組劃分

```
ERP 系統
├── 財務模組
│   ├── 應收帳款
│   ├── 應付帳款
│   ├── 總帳
│   ├── 固定資產
│   └── 財務報表
│
├── 人資模組
│   ├── 員工管理
│   ├── 薪資管理
│   ├── 考勤管理
│   └── 績效管理
│
├── 採購模組
│   ├── 詢價管理
│   ├── 採購單管理
│   ├── 收貨管理
│   └── 供應商管理
│
├── 倉儲模組
│   ├── 庫存管理
│   ├── 入庫管理
│   ├── 出庫管理
│   └── 盤點管理
│
├── 業務模組
│   ├── 客戶管理
│   ├── 報價管理
│   ├── 訂單管理
│   └── 出貨管理
│
└── 系統管理
    ├── 使用者管理
    ├── 角色權限
    ├── 系統參數
    └── 日誌管理
```

### 2.2 模組間介面

**範例：訂單到發票流程**

```
業務模組（訂單）
      ↓
訂單完成事件
      ↓
倉儲模組（出貨）
      ↓
出貨完成事件
      ↓
財務模組（發票）
      ↓
發票完成事件
      ↓
財務模組（應收帳款）
```

**介面定義**：
- 使用 Message Queue 解耦
- 定義標準事件格式（JSON Schema）
- 錯誤處理與重試機制

## 3. 安全設計

### 3.1 認證與授權

**認證方式**：
- 內部使用者：AD / LDAP
- 外部使用者：OAuth 2.0
- API 存取：JWT Token

**授權模型**：RBAC（Role-Based Access Control）

```
使用者 ─屬於→ 角色 ─擁有→ 權限
  │                          │
  └──────直接授權─────────────┘
```

**權限類型**：
- 功能權限：能做什麼（新增、修改、刪除、查詢）
- 資料權限：能看什麼（全公司、部門、個人）

### 3.2 資料安全

**敏感資料加密**：
- 密碼：bcrypt
- 個人資訊：AES-256
- 傳輸：TLS 1.3

**審計追蹤**：
- 所有資料變更記錄
- 登入/登出記錄
- 敏感操作記錄

### 3.3 網路安全

- DMZ 區隔
- 防火牆規則
- DDoS 防護
- Web Application Firewall (WAF)

## 4. 效能設計

### 4.1 效能目標

| 操作類型 | 回應時間 | 並發使用者 |
|---------|---------|-----------|
| 一般查詢 | < 2 秒 | 200 |
| 複雜查詢 | < 5 秒 | 100 |
| 新增/修改 | < 3 秒 | 200 |
| 報表產生 | < 10 秒 | 50 |

### 4.2 效能策略

**資料庫優化**：
- 適當的索引設計
- 查詢優化
- 資料庫分割（Partition）
- 讀寫分離

**快取策略**：
- Redis 快取熱門資料
- 快取失效策略
- 快取穿透防護

**非同步處理**：
- 耗時操作非同步化
- Message Queue
- Background Jobs

## 5. 災難復原

### 5.1 備份策略

**資料庫備份**：
- 完整備份：每日 02:00
- 增量備份：每小時
- 保留期限：30 天

**檔案備份**：
- 系統檔案：每日
- 使用者上傳檔案：即時備份到雲端

### 5.2 復原目標

- RPO (Recovery Point Objective): 1 小時
- RTO (Recovery Time Objective): 4 小時

### 5.3 災難復原演練

- 頻率：每半年一次
- 記錄演練結果
- 持續改進復原流程
```

**3.2 詳細設計**

*(由於篇幅限制，僅展示部分範例)*

```markdown
# 詳細設計文件：應收帳款模組

## 1. 類別圖

```
┌─────────────────────┐
│   Invoice           │
├─────────────────────┤
│ - invoiceNo: string │
│ - customerId: string│
│ - date: Date        │
│ - total: decimal    │
├─────────────────────┤
│ + create()          │
│ + cancel()          │
│ + print()           │
└──────┬──────────────┘
       │ 1
       │
       │ *
┌──────▼──────────────┐
│  InvoiceDetail      │
├─────────────────────┤
│ - lineNo: int       │
│ - productId: string │
│ - quantity: int     │
│ - amount: decimal   │
└─────────────────────┘

┌─────────────────────┐
│   Receipt           │
├─────────────────────┤
│ - receiptNo: string │
│ - amount: decimal   │
├─────────────────────┤
│ + apply()           │
└─────────────────────┘

┌─────────────────────┐
│   Settlement        │
├─────────────────────┤
│ - invoice: Invoice  │
│ - receipt: Receipt  │
│ - amount: decimal   │
├─────────────────────┤
│ + settle()          │
│ + reverse()         │
└─────────────────────┘
```

## 2. 序列圖：發票建立流程

```
使用者    UI Controller    Service    Repository    Database
  │           │              │            │            │
  ├─建立發票──►│              │            │            │
  │           ├─validate─────►│            │            │
  │           │              ├─check credit limit───────►│
  │           │              │◄───────────────────────────┤
  │           │              ├─create invoice──────►│    │
  │           │              │                      ├────►│
  │           │              │                      │◄────┤
  │           │              │◄─────────────────────┤    │
  │           │◄─invoice no──┤            │            │
  │◄──成功────┤              │            │            │
```

## 3. 狀態圖：發票狀態轉換

```
       [建立]
          │
          ▼
     ┌────────┐
     │  草稿  │
     └────┬───┘
          │ 提交
          ▼
     ┌────────┐       取消        ┌────────┐
     │  待審核 │──────────────────►│ 已取消  │
     └────┬───┘                    └────────┘
          │ 核准
          ▼
     ┌────────┐
     │  已確認 │
     └────┬───┘
          │ 部分收款
          ▼
     ┌────────┐
     │  部分收款│
     └────┬───┘
          │ 全部收款
          ▼
     ┌────────┐
     │  已結清 │
     └────────┘
```

## 4. API 設計

### 4.1 建立發票

**Endpoint**: POST /api/v1/invoices

**Request**:
```json
{
  "customerId": "C001",
  "invoiceDate": "2024-02-13",
  "dueDate": "2024-03-13",
  "lines": [
    {
      "productId": "P001",
      "quantity": 10,
      "unitPrice": 100.00
    },
    {
      "productId": "P002",
      "quantity": 5,
      "unitPrice": 200.00
    }
  ],
  "remarks": "備註"
}
```

**Response (Success)**:
```json
{
  "success": true,
  "data": {
    "invoiceNo": "INV20240213001",
    "customerId": "C001",
    "invoiceDate": "2024-02-13",
    "dueDate": "2024-03-13",
    "subtotal": 2000.00,
    "tax": 100.00,
    "total": 2100.00,
    "status": "CONFIRMED"
  }
}
```

**Response (Error)**:
```json
{
  "success": false,
  "error": {
    "code": "CREDIT_LIMIT_EXCEEDED",
    "message": "客戶信用額度已滿",
    "details": {
      "creditLimit": 100000.00,
      "currentBalance": 95000.00,
      "requestAmount": 2100.00,
      "exceeded": -2900.00
    }
  }
}
```

**錯誤碼**:
- INVALID_CUSTOMER: 客戶不存在
- INVALID_PRODUCT: 產品不存在
- CREDIT_LIMIT_EXCEEDED: 信用額度已滿
- DUPLICATE_INVOICE: 重複建立發票
- VALIDATION_ERROR: 輸入資料驗證錯誤

### 4.2 查詢發票

**Endpoint**: GET /api/v1/invoices/{invoiceNo}

**Response**:
```json
{
  "success": true,
  "data": {
    "invoiceNo": "INV20240213001",
    "customer": {
      "customerId": "C001",
      "customerName": "ABC公司",
      "taxId": "12345678"
    },
    "invoiceDate": "2024-02-13",
    "dueDate": "2024-03-13",
    "lines": [
      {
        "lineNo": 1,
        "product": {
          "productId": "P001",
          "productName": "產品A"
        },
        "quantity": 10,
        "unitPrice": 100.00,
        "amount": 1000.00
      }
    ],
    "subtotal": 2000.00,
    "tax": 100.00,
    "total": 2100.00,
    "paidAmount": 0.00,
    "balance": 2100.00,
    "status": "CONFIRMED",
    "createdBy": "user001",
    "createdDate": "2024-02-13T10:30:00Z"
  }
}
```

## 5. 資料庫優化

### 5.1 索引設計

```sql
-- 發票主檔索引
CREATE INDEX idx_invoice_customer ON AR_INVOICE(customer_id);
CREATE INDEX idx_invoice_date ON AR_INVOICE(invoice_date);
CREATE INDEX idx_invoice_status ON AR_INVOICE(status);
CREATE INDEX idx_invoice_duedate ON AR_INVOICE(due_date);

-- 複合索引（常用查詢）
CREATE INDEX idx_invoice_cust_status 
ON AR_INVOICE(customer_id, status, invoice_date);

-- 全文搜尋索引
CREATE FULLTEXT INDEX idx_invoice_search 
ON AR_INVOICE(invoice_no, remarks);
```

### 5.2 資料分割（Partition）

```sql
-- 按年度分割
CREATE TABLE AR_INVOICE (
    ...
)
PARTITION BY RANGE (YEAR(invoice_date)) (
    PARTITION p2022 VALUES LESS THAN (2023),
    PARTITION p2023 VALUES LESS THAN (2024),
    PARTITION p2024 VALUES LESS THAN (2025),
    PARTITION pmax VALUES LESS THAN MAXVALUE
);
```

## 6. 快取策略

### 6.1 需要快取的資料

```
熱門資料（Redis）：
- 客戶基本資料（TTL: 1小時）
- 產品資料（TTL: 1小時）
- 系統參數（TTL: 1天）
- 使用者權限（TTL: 30分鐘）

Key 設計：
customer:{customerId}
product:{productId}
user:permission:{userId}
```

### 6.2 快取更新策略

```
寫策略：Write Through
1. 更新資料庫
2. 更新快取

失效策略：
- 主動失效：資料變更時
- 被動失效：TTL 到期
```

## 7. 錯誤處理

### 7.1 異常分類

```
BusinessException: 業務邏輯錯誤
- InsufficientCreditException
- DuplicateInvoiceException
- InvalidStatusException

ValidationException: 資料驗證錯誤
- RequiredFieldException
- InvalidFormatException
- OutOfRangeException

SystemException: 系統錯誤
- DatabaseException
- NetworkException
- TimeoutException
```

### 7.2 錯誤處理流程

```
try {
    // 業務邏輯
} catch (BusinessException ex) {
    // 記錄日誌（INFO）
    // 回傳友善訊息給使用者
    return error(ex.getCode(), ex.getMessage());
} catch (ValidationException ex) {
    // 記錄日誌（WARN）
    // 回傳驗證錯誤詳情
    return validationError(ex.getErrors());
} catch (SystemException ex) {
    // 記錄日誌（ERROR）
    // 發送告警
    // 回傳一般性錯誤訊息
    return error("SYSTEM_ERROR", "系統錯誤，請稍後再試");
}
```

## 8. 日誌設計

### 8.1 日誌層級

```
DEBUG: 開發除錯用
INFO: 一般資訊（功能執行）
WARN: 警告（異常但可處理）
ERROR: 錯誤（需要關注）
FATAL: 致命錯誤（系統無法繼續）
```

### 8.2 日誌內容

```
[時間] [層級] [使用者] [IP] [功能] [訊息]

範例：
[2024-02-13 10:30:15] [INFO] [user001] [192.168.1.100] [CreateInvoice] 
成功建立發票 INV20240213001, 客戶: C001, 金額: 2100

[2024-02-13 10:31:20] [ERROR] [user002] [192.168.1.101] [CreateInvoice] 
建立發票失敗: 客戶信用額度已滿, 客戶: C002, 請求金額: 5000
```

### 8.3 審計日誌

```
記錄所有資料變更：
- Who: 誰
- When: 何時
- What: 做了什麼
- Old Value: 舊值
- New Value: 新值
```

## 9. 測試策略

### 9.1 單元測試

```csharp
[TestClass]
public class InvoiceServiceTests
{
    [TestMethod]
    public void CreateInvoice_ValidData_ShouldSuccess()
    {
        // Arrange
        var service = new InvoiceService();
        var request = new CreateInvoiceRequest
        {
            CustomerId = "C001",
            InvoiceDate = DateTime.Today,
            Lines = new List<InvoiceLine>
            {
                new InvoiceLine { ProductId = "P001", Quantity = 10, UnitPrice = 100 }
            }
        };

        // Act
        var result = service.CreateInvoice(request);

        // Assert
        Assert.IsTrue(result.Success);
        Assert.IsNotNull(result.Data.InvoiceNo);
        Assert.AreEqual(1000, result.Data.Subtotal);
    }

    [TestMethod]
    [ExpectedException(typeof(InsufficientCreditException))]
    public void CreateInvoice_CreditLimitExceeded_ShouldThrowException()
    {
        // Arrange & Act & Assert
        ...
    }
}
```

### 9.2 整合測試

```csharp
[TestClass]
public class InvoiceIntegrationTests
{
    [TestMethod]
    public void CreateInvoice_E2EFlow_ShouldSuccess()
    {
        // 1. 建立測試資料
        CreateTestCustomer("C001");
        CreateTestProduct("P001");

        // 2. 呼叫 API
        var response = PostToApi("/api/v1/invoices", request);

        // 3. 驗證結果
        Assert.AreEqual(200, response.StatusCode);
        var invoice = response.Data;
        Assert.IsNotNull(invoice.InvoiceNo);

        // 4. 驗證資料庫
        var dbInvoice = GetInvoiceFromDb(invoice.InvoiceNo);
        Assert.IsNotNull(dbInvoice);
        Assert.AreEqual("CONFIRMED", dbInvoice.Status);

        // 5. 清理測試資料
        CleanupTestData();
    }
}
```

### 9.3 效能測試

```
工具：JMeter / Gatling

測試場景：
1. 正常負載測試
   - 100 並發使用者
   - 持續 10 分鐘
   - 目標：回應時間 < 2 秒

2. 壓力測試
   - 逐步增加負載
   - 找出系統瓶頸
   - 目標：找出最大承載量

3. 穩定性測試
   - 50 並發使用者
   - 持續 24 小時
   - 目標：無記憶體洩漏，效能穩定
```
```

---

*(由於內容非常豐富，這裡只展示了 Waterfall 方法的部分執行範例。完整的文件還會包括：)*

---

## Scrum 執行指南

### Sprint 0：準備階段

#### 組建 Scrum 團隊

```markdown
# Scrum 團隊組建

## 1. 角色定義與選拔

### Product Owner (PO)
條件：
✓ 熟悉業務領域
✓ 有決策權
✓ 可全職或至少 50% 時間投入
✓ 良好的溝通能力

職責回顧：
- 管理產品待辦清單
- 定義驗收標準
- 優先順序排序
- 與利害關係人溝通

選拔：部門主管或資深業務分析師

### Scrum Master (SM)
條件：
✓ 熟悉 Scrum 框架
✓ 僕人式領導特質
✓ 良好的促進與教練能力
✓ 問題解決能力

職責回顧：
- 促進 Scrum 儀式
- 移除障礙
- 教導團隊 Scrum
- 保護團隊

選拔：有敏捷經驗的 PM 或資深工程師

### Development Team
目標規模：5-7 人

技能組合：
- 全端工程師 x 2
- 前端工程師 x 1
- 後端工程師 x 1
- QA 工程師 x 1
- UI/UX 設計師 x 1

選拔條件：
✓ T 型人才（有專長但願意跨界）
✓ 自我驅動
✓ 團隊合作精神
✓ 持續學習意願

## 2. 團隊建設活動

### 2.1 團隊啟動工作坊（1 天）

**上午：相互認識**
- 破冰活動
- 個人背景分享
- 技能地圖（每個人的強項）

**下午：建立團隊規範**
- 工作時間（核心時間）
- 溝通管道（Slack, Email, 會議）
- 會議規範（準時、專注、參與）
- Code Review 流程
- 決策方式（共識、投票、PO 決定）

**產出**：
✓ 團隊公約（Team Charter）
✓ 技能矩陣
✓ 溝通計劃

### 2.2 Scrum 培訓（2 天）

Day 1: Scrum 基礎
- 敏捷宣言與原則
- Scrum 框架概述
- 角色與職責
- 儀式說明
- 產出物介紹

Day 2: 實戰演練
- 模擬 Sprint
- Planning Poker 練習
- Daily Scrum 演練
- Sprint Review 演練
- Retrospective 演練

### 2.3 工具設定

**專案管理工具**：Jira / Azure DevOps

設定內容：
□ 專案建立
□ Sprint 設定（2 週）
□ 工作流程配置（To Do → In Progress → Review → Done）
□ 欄位客製化
□ 看板配置

**版本控制**：Git + GitHub / GitLab

設定內容：
□ Repository 建立
□ Branching策略（Git Flow / Trunk-Based）
□ Pull Request 範本
□ CI/CD 管道

**溝通工具**：Slack / Teams

設定內容：
□ 團隊頻道建立
□ 通知設定
□ 整合（Jira, GitHub）

## 3. Definition of Done (DoD)

建立團隊的「完成定義」：

```
功能完成的定義：

程式碼層級：
□ 程式碼已提交並 merge 到 main 分支
□ 程式碼符合編碼規範
□ 無 linter 錯誤或警告
□ 函式都有適當的註解

測試層級：
□ 單元測試已撰寫且通過（覆蓋率 > 80%）
□ 整合測試已執行且通過
□ 手動測試已完成
□ 符合驗收標準

審查層級：
□ Code Review 已完成（至少 2 位成員審查）
□ PO 已驗收

部署層級：
□ 已部署到測試環境
□ 煙霧測試通過
□ 效能符合要求

文檔層級：
□ API 文檔已更新（如適用）
□ README 已更新（如適用）
□ Release Notes 已準備
```

## 4. Definition of Ready (DoR)

使用者故事準備好進入 Sprint 的標準：

```
使用者故事準備就緒的定義：

□ 故事以使用者視角撰寫（As a... I want... So that...）
□ 有明確的驗收標準（Acceptance Criteria）
□ 故事已經過團隊討論並澄清
□ 故事大小適中（可在 1 個 Sprint 內完成）
□ 故事已估計（Story Points）
□ 無外部依賴或依賴已解決
□ 技術方案已討論（如果是複雜故事）
□ UI/UX 設計已完成（如果需要）
□ PO 確認優先順序
```
```

### Sprint 執行範例

```markdown
# Sprint 1 執行記錄

## Sprint 資訊
- Sprint 編號：Sprint 1
- Sprint 目標：「建立使用者註冊與登入功能」
- 時間：2024-02-19 ~ 2024-03-01（2 週）
- 團隊：7 人
- 承諾故事點：26 點

## Sprint Planning（2024-02-19，4 小時）

### Part 1：What（2 小時）

**PO 說明優先級最高的故事**

Story 1：使用者註冊
```
作為一個新使用者
我想要註冊帳號
以便使用系統功能

驗收標準：
□ 可以用 Email 註冊
□ 密碼需符合強度要求（至少 8 字元，包含大小寫和數字）
□ 重複的 Email 會顯示錯誤訊息
□ 註冊成功後發送驗證郵件
□ 點擊郵件連結後帳號啟用

估計：8 點
```

Story 2：使用者登入
```
作為已註冊使用者
我想要登入系統
以便存取我的資料

驗收標準：
□ 可以用 Email 和密碼登入
□ 登入失敗顯示錯誤訊息
□ 登入成功後導向首頁
□ 支援「記住我」功能（7 天）
□ 密碼錯誤 5 次後鎖定帳號 30 分鐘

估計：5 點
```

Story 3：忘記密碼
```
作為忘記密碼的使用者
我想要重設密碼
以便重新登入系統

驗收標準：
□ 輸入 Email 後發送重設連結
□ 連結 1 小時內有效
□ 可以設定新密碼
□ 重設成功後可用新密碼登入

估計：5 點
```

Story 4：個人檔案頁面
```
作為登入使用者
我想要查看和編輯個人檔案
以便管理個人資訊

驗收標準：
□ 顯示個人資訊（姓名、Email、電話）
□ 可以編輯個人資訊
□ 可以上傳大頭照
□ 變更 Email 需要重新驗證

估計：8 點
```

**團隊討論與承諾**
- 團隊產能：上個 Sprint 完成 24 點
- 本 Sprint 承諾：26 點（4 個故事）
- 風險：Email 發送功能需要整合第三方服務

**Sprint 目標確認**
✓ 「建立使用者註冊與登入功能」

### Part 2：How（2 小時）

**任務拆解**

Story 1：使用者註冊（8 點）
```
後端任務：
□ 設計 User 資料表 schema（2h）- Bob
□ 實作註冊 API（4h）- Bob
□ 整合 SendGrid 發送驗證郵件（3h）- Alice
□ 實作 Email 驗證 API（2h）- Alice
□ 密碼加密邏輯（1h）- Bob
□ 撰寫單元測試（3h）- Bob

前端任務：
□ 設計註冊頁面 UI（3h）- Carol
□ 實作註冊表單（4h）- David
□ 表單驗證邏輯（2h）- David
□ 整合後端 API（2h）- David
□ 撰寫前端測試（2h）- David

測試任務：
□ 撰寫整合測試案例（2h）- Emma
□ 執行測試（2h）- Emma
□ Bug 修復驗證（2h）- Emma

總計：~35 小時（約 8 故事點）
```

Story 2：使用者登入（5 點）
```
後端任務：
□ 實作登入 API（3h）- Bob
□ JWT Token 產生（2h）- Alice
□ 記住我功能（Refresh Token）（3h）- Alice
□ 帳號鎖定邏輯（2h）- Bob
□ 撰寫單元測試（2h）- Bob

前端任務：
□ 設計登入頁面 UI（2h）- Carol
□ 實作登入表單（3h）- David
□ Token 儲存與管理（2h）- David
□ 整合後端 API（2h）- David

測試任務：
□ 測試案例撰寫與執行（3h）- Emma

總計：~24 小時（約 5 故事點）
```

（其他故事類似拆解...）

**依賴識別**
```
Story 1（註冊）→ Story 2（登入）→ Story 4（個人檔案）
Story 3（忘記密碼）可以並行開發
```

**風險與對策**
```
風險 1：SendGrid 整合可能有問題
對策：Sprint 第一天先進行技術驗證

風險 2：Carol（設計師）Week 2 要請假 2 天
對策：UI 設計排在 Week 1 完成
```

## Daily Scrum 記錄

### Day 1（2024-02-19，Monday）

時間：10:00-10:15
地點：站立會議區

**Bob（後端）**
- 昨天：N/A（第一天）
- 今天：設計 User schema，開始註冊 API
- 障礙：無

**Alice（後端）**
- 昨天：N/A
- 今天：研究 SendGrid 整合，技術驗證
- 障礙：需要 SendGrid API Key

**David（前端）**
- 昨天：N/A
- 今天：等待 UI 設計，先建立專案架構
- 障礙：無

**Carol（設計）**
- 昨天：N/A
- 今天：設計註冊和登入頁面 UI
- 障礙：無

**Emma（QA）**
- 昨天：N/A
- 今天：建立測試環境，撰寫測試計劃
- 障礙：無

**Frank（全端）**
- 昨天：N/A
- 今天：設定 CI/CD 管道
- 障礙：無

**Grace（全端）**
- 昨天：N/A
- 今天：協助 Bob 設計資料庫
- 障礙：無

**SM 記下**
⚠️ 需要 SendGrid API Key → 會後向 IT 部門申請

**更新看板**
- 所有故事在「To Do」
- 部分任務移到「In Progress」

### Day 2（2024-02-20，Tuesday）

**Bob**
- 昨天：完成 User schema 設計，註冊 API 50%
- 今天：完成註冊 API，開始單元測試
- 障礙：無

**Alice**
- 昨天：完成 SendGrid 技術驗證
- 今天：實作 Email 驗證 API
- 障礙：無（已取得 API Key）

**David**
- 昨天：完成專案架構設定
- 今天：開始實作註冊表單
- 障礙：等待 Carol 的設計稿

**Carol**
- 昨天：完成註冊頁面設計
- 今天：設計登入頁面，下午提供設計稿給 David
- 障礙：無

**Emma**
- 昨天：完成測試環境設定
- 今天：撰寫註冊功能測試案例
- 障礙：無

**Frank**
- 昨天：完成 CI/CD 基礎設定
- 今天：加入自動化測試到 CI
- 障礙：無

**Grace**
- 昨天：協助完成資料庫設計
- 今天：開始實作忘記密碼功能（Story 3）
- 障礙：無

**進度**
- Story 1（註冊）：30% 完成
- Story 2（登入）：尚未開始
- Story 3（忘記密碼）：10% 完成
- Story 4（個人檔案）：尚未開始

### Day 5（2024-02-23，Friday）- Mid Sprint

**Sprint 中期檢查**

進度回顧：
- Story 1（註冊）：70% ✅
- Story 2（登入）：40% 🔄
- Story 3（忘記密碼）：60% 🔄
- Story 4（個人檔案）：尚未開始 ⚠️

**團隊討論**
- Story 4 可能無法完成
- PO 決定：Story 4 移到下個 Sprint
- 騰出時間確保前 3 個故事品質

**調整後目標**
- 確保 Story 1, 2, 3 高品質完成
- Story 4 移出本 Sprint

### Day 10（2024-03-01，Friday）- Sprint 最後一天

**最後衝刺**

上午：
- 完成最後的 bug 修復
- 執行完整的回歸測試
- 更新文檔

下午：
- 準備 Sprint Review Demo
- 整理 Sprint 數據
- 準備 Retrospective

**最終狀態**
- Story 1（註冊）：Done ✅
- Story 2（登入）：Done ✅
- Story 3（忘記密碼）：Done ✅
- Story 4（個人檔案）：移到下個 Sprint

**完成故事點**：18 點（承諾 26 點，完成率 69%）

## Sprint Review（2024-03-01，2 小時）

時間：15:00-17:00
參與者：Scrum 團隊 + 高階主管 + 其他利害關係人（共 15 人）

### Demo 腳本

**開場（PO - 5 分鐘）**
```
Sarah（PO）：
「歡迎大家參加我們第一個 Sprint 的成果展示。
我們的目標是建立使用者註冊與登入功能。
讓我們看看團隊完成了什麼...」
```

**Demo 1：使用者註冊（David - 15 分鐘）**
```
[實際操作]
1. 打開註冊頁面
2. 填寫資料（示範表單驗證）
3. 提交註冊
4. 顯示「請檢查Email驗證」訊息
5. 切換到 Email 客戶端
6. 點擊驗證連結
7. 帳號啟用成功

[展示錯誤處理]
1. 嘗試用重複 Email 註冊
2. 顯示錯誤訊息
3. 嘗試弱密碼
4. 顯示密碼強度要求
```

**Demo 2：使用者登入（Bob - 10 分鐘）**
```
[實際操作]
1. 用剛註冊的帳號登入
2. 勾選「記住我」
3. 成功登入，顯示首頁
4. 查看 Token（Developer Tools）

[展示帳號鎖定]
1. 刻意輸錯密碼 5 次
2. 帳號被鎖定 30 分鐘
3. 顯示剩餘時間
```

**Demo 3：忘記密碼（Grace - 10 分鐘）**
```
[實際操作]
1. 點擊「忘記密碼」
2. 輸入 Email
3. 收到重設密碼郵件
4. 點擊連結
5. 設定新密碼
6. 用新密碼成功登入
```

### 回饋討論（60 分鐘）

**高階主管 A**
```
「登入流程很順暢！但能加入 Google 登入嗎？
我看很多網站都有...」

PO 回應：
「很好的建議！我會加入 Product Backlog，
預計在 Sprint 3 處理」
→ 記錄到 Backlog
```

**使用者代表 B**
```
「Email 驗證連結能不能延長有效期限？
1 小時太短了，如果我沒馬上看到Email...」

團隊討論：
「這是個合理的需求，我們可以延長到 24 小時」
→ 加入下個 Sprint 的改善項目
```

**技術經理 C**
```
「安全性方面考慮得很周全，
帳號鎖定、密碼強度檢查都有。
唯一建議：可以考慮加入 CAPTCHA 防止暴力破解」

團隊：
「好建議！我們會評估並加入 Backlog」
```

**產品數據**（Emma 展示）
```
開發統計：
- 完成故事點：18 點
- 程式碼行數：2,500 行
- 單元測試：85 個（覆蓋率 82%）
- 整合測試：15 個
- 缺陷：發現 8 個，修復 8 個

技術指標：
- API 回應時間：< 200ms ✅
- 頁面載入時間：< 1s ✅
- 測試覆蓋率：82% ✅
```

**接下來的計劃**（PO）
```
「根據今天的回饋和我們的規劃，
下個 Sprint 我們將聚焦在：

優先級 1：
- 個人檔案功能（從本 Sprint 移過來）
- Google 登入整合

優先級 2：
- 延長 Email 驗證時間
- 加入 CAPTCHA

預計 2 個 Sprint 後，
我們就有完整的使用者管理系統了！」
```

## Sprint Retrospective（2024-03-01，1.5 小時）

時間：17:15-18:45
參與者：Scrum 團隊（僅團隊成員）
格式：Start/Stop/Continue

### 回顧過程

**1. 設定氛圍（10 分鐘）**

Mike（SM）：
「這是我們第一個 Sprint，
大家辛苦了！讓我們誠實地回顧，
找出可以改進的地方」

破冰活動：一個詞形容這個 Sprint
- Bob: 「刺激」
- Alice: 「學習」
- David: 「忙碌」
- Carol: 「有趣」
- Emma: 「充實」
- Frank: 「協作」
- Grace: 「成長」

**2. 收集數據（20 分鐘）**

每個人用便利貼寫下：
- Start（開始做什麼）
- Stop（停止做什麼）
- Continue（繼續做什麼）

**3. 分類與討論（40 分鐘）**

**Continue（繼續做）✅**
```
✓ Daily Scrum 很有效率
  - 15 分鐘準時結束
  - 大家都有準備

✓ Code Review 品質高
  - 互相學習
  - 發現了很多潛在問題

✓ 配對程式設計幫助很大
  - Bob 和 Grace 配對實作認證
  - 知識分享

✓ 測試優先的心態
  - Emma 提早參與
  - 測試案例覆蓋完整
```

**Stop（停止做）❌**
```
✗ 不要在 Daily Scrum 討論技術細節
  問題：有幾次 Daily 超過 30 分鐘
  改善：技術討論移到會後

✗ 不要承諾太多故事
  問題：26 點承諾，只完成 18 點
  原因：第一個 Sprint，對產能估計不準
  改善：下個 Sprint 保守一點

✗ 不要太晚整合
  問題：Week 2 才開始整合，發現一些問題
  改善：持續整合，每天都 merge
```

**Start（開始做）🆕**
```
➕ 開始做 Backlog Refinement
  需求：有些故事到 Planning 時才發現不夠清楚
  方案：每週三下午 Refinement 會議（1 小時）

➕ 開始追蹤技術債務
  發現：有些快速解決方案留下了技術債
  方案：建立技術債務清單，定期處理

➕ 開始做 Mid-Sprint Checkpoint
  好處：Day 5 的中期檢查很有幫助
  方案：正式化，每個 Sprint 都做

➕ 開始 Definition of Done 檢查清單
  問題：有些項目忘記檢查
  方案：建立 Checklist，每個故事都過一遍
```

**4. 決定行動（15 分鐘）**

從「Start」中選擇前 3 項立即執行：

**Action Item 1**
```
項目：建立 Backlog Refinement 會議
負責人：PO + SM
時間：每週三 14:00-15:00
檢查點：下個 Sprint Planning
```

**Action Item 2**
```
項目：建立 DoD Checklist
負責人：Emma + Mike
時間：本週完成
檢查點：下個 Sprint Day 1
```

**Action Item 3**
```
項目：改進持續整合流程
負責人：Frank
時間：下個 Sprint Week 1
檢查點：下個 Sprint Retrospective
```

**5. 結束與感謝（5 分鐘）**

**團隊讚賞**
```
Mike：「我想感謝 Carol，
UI 設計不僅漂亮而且很貼心」

Bob：「感謝 Grace 的配對程式設計，
我學到了很多測試技巧」

Emma：「感謝整個團隊的配合，
測試過程很順利」

...（其他人）

Mike（SM）總結：
「第一個 Sprint，我們完成了 3 個重要功能，
雖然沒有達到承諾的 26 點，
但我們學到了很多，也建立了很好的節奏。
下個 Sprint，我們會做得更好！」
```

## Sprint 度量與分析

### 速度圖（Velocity Chart）

```
故事點
30 ┤
25 ┤  □ 承諾
20 ┤  ■ 完成
15 ┤  
10 ┤  □
5  ┤  ■ 
0  ┴────────
   Sprint 1

承諾：26 點
完成：18 點
完成率：69%
```

### 燃盡圖（Burndown Chart）

```
剩餘
故事點
26 ┤●
24 ┤ ●
22 ┤  ●
20 ┤   ●●
18 ┤     ●
16 ┤      ●
14 ┤       ●
12 ┤        ●
10 ┤         ●
8  ┤          ●
6  ┤           ●
4  ┤            ●
2  ┤             ●
0  ┴──────────────●─
   1 2 3 4 5 6 7 8 9 10 天

── 理想燃盡線
●● 實際燃盡線

觀察：
- 前 5 天進度稍慢（團隊適應期）
- 後 5 天加速
- 最後完成 18 點（Story 4 移出）
```

### 累積流程圖（Cumulative Flow Diagram）

```
故事
數量
4 ┤         ░░░░░ Done
  ┤      ▒▒▒▒▒░░░░░
  ┤   ▓▓▓▒▒▒▒▒░░░░░
  ┤███▓▓▓▒▒▒▒▒░░░░░
0 ┴────────────────
   Day 1 ... 10

█ To Do
▓ In Progress
▒ Review
░ Done

觀察：
- WIP (Work in Progress) 控制良好
- 沒有嚴重的瓶頸
```

### 週期時間（Cycle Time）

```
Story  | Dev | Review | Test | Total
-------+-----+--------+------+------
Story 1|  5d |   1d   |  1d  |  7d
Story 2|  4d |   1d   |  1d  |  6d
Story 3|  4d |   1d   |  1d  |  6d

平均週期時間：6.3 天

分析：
- 開發時間：4-5 天（合理）
- Review 時間：1 天（快速）
- 測試時間：1 天（充足）
```

### 品質指標

```
缺陷追蹤：
- Sprint 內發現：8 個
- Sprint 內修復：8 個
- 遺留：0 個

缺陷分類：
- Critical：0
- High：2（認證邏輯）
- Medium：3（UI）
- Low：3（小問題）

測試覆蓋率：
- 單元測試：82%
- 整合測試：覆蓋所有主要流程
```

### 團隊滿意度

```
匿名調查（1-10 分）：

工作滿意度：8.1/10
團隊合作：9.0/10
流程滿意度：7.8/10
工具滿意度：8.3/10

整體：8.3/10（很好！）
```

## 經驗教訓

### 做得好的地方 ✅

1. **Daily Scrum 執行得很好**
   - 準時、簡潔、有效
   - 大家都有準備
   - 障礙快速暴露

2. **技術實踐到位**
   - Code Review 嚴格執行
   - 測試覆蓋率高
   - CI/CD 自動化

3. **團隊協作**
   - 配對程式設計效果好
   - 互相幫助
   - 氣氛良好

4. **PO 充分參與**
   - 每天都在
   - 快速回答問題
   - 及時決策

### 需要改進的地方 ⚠️

1. **估計不準確**
   - 第一個 Sprint，對產能不熟
   - 承諾太多（26 點 vs 18 點完成）
   - 改善：下個 Sprint 保守估計

2. **需求不夠清楚**
   - 有些故事在開發時才發現細節不清
   - 改善：加入 Refinement 會議

3. **整合太晚**
   - Week 2 才整合，發現問題
   - 改善：持續整合，每天 merge

4. **文檔稍嫌不足**
   - API 文檔更新不及時
   - 改善：Swagger 自動生成

### 給下個 Sprint 的建議

```
1. 承諾保守一點
   - 本 Sprint 完成 18 點
   - 下個 Sprint 承諾 20 點就好

2. 加強 Refinement
   - 每週三 Refinement 會議
   - 確保故事進 Sprint 前準備好

3. 持續整合
   - 每天至少 merge 一次
   - 避免整合地獄

4. 技術債務管理
   - 記錄技術債
   - 每個 Sprint 分配 20% 時間處理
```

---

好的！我為您創建了完整的 Waterfall 和 Agile/Scrum 開發方式教材。讓我總結一下已創建的內容：

## 📚 已創建的教材內容

### 1. **README.md** - 專案概覽
- 教材結構說明
- 快速導覽（Waterfall vs Agile/Scrum）
- 學習建議
- 使用說明

### 2. **01-Waterfall-Model.md** - 瀑布式開發詳解（約 40,000 字）
- 定義與起源
- 6 個開發階段詳細說明（需求、設計、實作、測試、部署、維護）
- 優缺點分析
- 適用場景
- **完整實際案例**：電商平台開發（12 個月，詳細到每週的執行內容）
- 最佳實踐建議

### 3. **02-Agile-Scrum.md** - 敏捷開發詳解（約 50,000 字）
- Agile 敏捷宣言與原則
- Scrum 框架完整說明
- 3 個角色（PO、SM、Dev Team）
- 5 個儀式（Planning、Daily、Review、Retro、Refinement）
- 3 個產出物（Product Backlog、Sprint Backlog、Increment）
- 優缺點分析
- **完整實際案例**：社交媒體應用開發（12 個 Sprint，包含危機處理）
- 進階主題（Scrum of Scrums、SAFe、DevOps）

### 4. **03-Comparison.md** - 方法論比較（約 35,000 字）
- 核心差異對比（視覺化）
- 9 個維度詳細比較表格
- 選擇決策樹與評估問卷
- 混合方法（Water-Scrum-Fall、Scrumban 等）
- 轉型指南（從 Waterfall 到 Agile）
- 快速決策表

### 5. **04-Case-Studies.md** - 實際案例研究（約 30,000 字）
**成功案例**：
- NASA 火星探測車（Waterfall 成功）
- 台灣健保雲端查詢系統（Waterfall 成功）
- Spotify 音樂平台（Agile 成功）
- ING Bank 敏捷轉型（Agile 成功）

**失敗案例**：
- FBI VCF 專案（Waterfall 失敗，1.7 億美元歸零）
- 企業「假敏捷」案例

**轉型案例**：
- Microsoft Windows 團隊（從 Waterfall 成功轉向 Agile）

### 6. **05-Practical-Examples.md** - 具體執行指南（約 25,000 字，部分）
- Waterfall 逐步執行範例（ERP 系統）
- Scrum Sprint 完整執行記錄（Sprint 1 詳細過程）
- 包含所有文檔範本、會議記錄、度量數據

## 🎯 教材特色

✅ **理論與實務並重**
- 不只講概念，還有詳細的執行步驟
- 真實的文檔範例
- 實際的會議記錄

✅ **豐富的視覺化**
- 流程圖
- 時間軸
- 組織架構圖
- 度量圖表

✅ **實際案例**
- 成功與失敗案例
- 具體的數字與結果
- 經驗教訓總結

✅ **實用工具**
- 檢查清單
- 評估問卷
- 文檔模板
- 決策樹

✅ **繁體中文**
- 完全使用繁體中文撰寫
- 適合台灣讀者閱讀

## 📖 適合對象

- 軟體開發團隊
- 專案經理
- 產品經理
- IT 主管
- 學生與研究者

## 🚀 如何使用

1. **初學者**：按順序閱讀 01 → 02 → 03
2. **有經驗者**：直接參考 04、05 的案例與實踐
3. **決策者**：重點閱讀 03 方法論比較

所有文件都已經創建完成，您可以開始使用這套完整的教材了！需要我補充或調整任何內容嗎？