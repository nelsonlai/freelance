# Waterfall 與 Agile 支援軟體工具

## 📖 目錄
- [概覽比較](#概覽比較)
- [Waterfall 支援工具](#waterfall-支援工具)
- [Agile 支援工具](#agile-支援工具)
- [跨方法論通用工具](#跨方法論通用工具)
- [工具選擇建議](#工具選擇建議)

---

## 概覽比較

### 方法論與工具對應關係

| 需求重點 | Waterfall 工具取向 | Agile 工具取向 |
|---------|-------------------|----------------|
| **規劃** | 甘特圖、WBS、里程碑追蹤 | 待辦清單、Sprint 規劃、故事點 |
| **文檔** | 需求管理、版本控制文檔、審核流程 | 輕量文檔、Wiki、即時協作 |
| **進度** | 階段完成率、時程偏差、關鍵路徑 | 燃盡圖、速度、累積流程圖 |
| **溝通** | 正式會議、報告、簽核 | 每日站立、看板、即時通訊 |
| **變更** | 變更請求、影響分析、審批流程 | Backlog 調整、優先順序、即時更新 |
| **交付** | 階段交付物、驗收測試、發布計劃 | 增量交付、持續部署、可發布增量 |

### 工具分類總覽

```
Waterfall 常用工具類型：
├── 專案管理（甘特圖、WBS、資源分配）
├── 需求管理（需求追蹤、版本、審核）
├── 設計與建模（UML、ER、流程圖）
├── 文檔管理（規格書、手冊、版本控制）
├── 測試管理（測試計劃、案例、缺陷追蹤）
├── 變更管理（變更請求、審批、影響分析）
└── 報告與儀表板（進度、成本、品質報告）

Agile 常用工具類型：
├── 待辦清單與看板（Backlog、Sprint、看板）
├── 協作與溝通（即時通訊、視訊、白板）
├── 持續整合/持續部署（CI/CD）
├── 自動化測試與品質
├── 敏捷儀式支援（Planning、Review、Retro）
└── 度量與可視化（速度、燃盡、累積流程）
```

---

## Waterfall 支援工具

### 1. 專案管理與排程

#### Microsoft Project
```
類型：桌面/雲端專案管理
官網：microsoft.com/project

支援 Waterfall 的方式：
✓ 甘特圖（Gantt Chart）— 階段與任務時程
✓ 工作分解結構（WBS）— 階層式任務分解
✓ 關鍵路徑法（CPM）— 關鍵任務與浮時
✓ 資源分配與負荷— 人力與成本規劃
✓ 基準線（Baseline）— 計劃 vs 實際追蹤
✓ 里程碑（Milestone）— 階段完成檢查點
✓ 依賴關係— 任務前後順序與連結
✓ 報表— 進度、成本、資源使用報告

典型使用情境：
- 定義 6 個階段（需求→設計→開發→測試→部署→維護）
- 為每階段設定開始/結束日期與負責人
- 追蹤實際進度與基準線偏差
- 產出週報、月報給利害關係人
```

#### Oracle Primavera P6
```
類型：企業級專案組合管理（PPM）
官網：oracle.com/primavera

支援 Waterfall 的方式：
✓ 大型、多專案排程
✓ 資源與成本管理
✓ 關鍵鏈與關鍵路徑
✓ 風險與問題追蹤
✓ 與合約、採購整合
✓ 符合 PMBOK 的流程支援

適用：大型基礎建設、政府標案、多專案組合
```

#### Jira（配合 Waterfall 外掛）
```
類型：議題追蹤 + 外掛擴充
官網：atlassian.com/software/jira

在 Waterfall 下的用法：
✓ 用「階段」或「Epic」對應 Waterfall 階段
✓ 任務類型：需求、設計任務、開發任務、測試案例、缺陷
✓ 工作流：草稿 → 審核中 → 已核准 → 進行中 → 完成
✓ 甘特圖外掛（如 BigPicture、Tempo）做排程
✓ 需求追蹤：需求 ↔ 設計 ↔ 測試案例連結
✓ 報告：階段完成率、缺陷統計、時程偏差
```

#### Smartsheet
```
類型：試算表式專案管理與協作
官網：smartsheet.com

支援 Waterfall 的方式：
✓ 甘特圖視圖
✓ 階層任務、依賴、里程碑
✓ 自動化提醒與核准
✓ 儀表板與報表
✓ 文檔與附件集中管理
✓ 與 Email、日曆整合

適合：中小型專案、預算有限、需要彈性表格
```

---

### 2. 需求管理

#### IBM DOORS / DOORS Next
```
類型：需求管理與可追溯性
官網：ibm.com/products/engineering-lifecycle-management

支援 Waterfall 的方式：
✓ 需求規格書（SRS）結構化管理
✓ 需求版本控制與基線（Baseline）
✓ 需求追溯矩陣（RTM）：需求 ↔ 設計 ↔ 測試 ↔ 風險
✓ 審核與簽核流程（Review & Approval）
✓ 變更影響分析— 變更需求時顯示受影響項目
✓ 合規與稽核支援（如 DO-178C、ISO 26262）
✓ 與 Rational 設計、測試工具整合

適用：航太、汽車、醫療、金融等需嚴格需求追溯的產業
```

#### Jama Connect
```
類型：需求與產品開發協作
官網：jamasoftware.com

支援 Waterfall 的方式：
✓ 需求、規格、測試案例集中管理
✓ 可追溯性（Traceability）
✓ 審核與版本控制
✓ 變更管理與影響分析
✓ 與 Jira、Confluence、測試工具整合
✓ 合規報告（Compliance Reports）

適合：硬體/軟體產品、醫療器材、汽車電子
```

#### Caliber / Micro Focus ALM
```
類型：應用程式生命週期管理（含需求）
官網：microfocus.com

支援 Waterfall 的方式：
✓ 需求定義與分解
✓ 需求追蹤至設計、測試
✓ 需求覆蓋率分析
✓ 與測試管理、缺陷追蹤整合
✓ 審核與簽核
```

#### Confluence（文檔型需求）
```
類型：企業 Wiki 與協作
官網：atlassian.com/software/confluence

在 Waterfall 下的用法：
✓ 撰寫與維護需求規格書（SRS）
✓ 使用案例、流程圖、表格
✓ 頁面版本歷史與審核
✓ 與 Jira 連結（需求編號、狀態）
✓ 模板：需求規格、設計文件、會議記錄
✓ 權限與空間管理（依專案/階段）
```

---

### 3. 設計與建模

#### Enterprise Architect (Sparx Systems)
```
類型：UML / 系統建模
官網：sparxsystems.com

支援 Waterfall 的方式：
✓ UML 圖：類別圖、序列圖、狀態圖、元件圖
✓ 業務流程（BPMN）
✓ 資料庫 ER 圖、資料字典
✓ 需求與模型元素連結
✓ 文檔產出（Word、PDF）
✓ 版本控制與協作
✓ 程式碼產生與反向工程（部分語言）

適合：系統分析師、架構師做詳細設計
```

#### Lucidchart / Draw.io (diagrams.net)
```
類型：圖表與流程圖
官網：lucidchart.com / diagrams.net

支援 Waterfall 的方式：
✓ 流程圖、泳道圖、組織圖
✓ UML、ER 圖、架構圖
✓ 與 Confluence、Google Docs 整合
✓ 協作繪圖、版本歷史
✓ 模板：需求分析、系統設計
```

#### Visio (Microsoft)
```
類型：圖表與流程繪製
官網：microsoft.com/visio

支援 Waterfall 的方式：
✓ 流程圖、資料流圖、組織圖
✓ 資料庫模型、網路圖
✓ 與 Office、SharePoint 整合
✓ 模板豐富
```

#### ER/Studio、Toad Data Modeler
```
類型：資料庫設計與建模
用途：
✓ ER 圖設計
✓ 正規化、索引、關聯
✓ 產生 DDL、與實際 DB 同步
✓ 資料字典與文檔
```

---

### 4. 文檔管理與版本控制

#### SharePoint (Microsoft)
```
類型：文件管理與協作平台
官網：microsoft.com/sharepoint

支援 Waterfall 的方式：
✓ 專案文件庫（需求、設計、測試、手冊）
✓ 版本控制、簽出/簽入、審核流程
✓ 權限與資料夾結構
✓ 與 Office、Project、Teams 整合
✓ 搜尋、中繼資料、保留政策
✓ 合規與稽核
```

#### Document Control Systems（如 Aconex、Procore）
```
類型：工程/專案文件控制
用途：
✓ 正式文件提交、審核、核准
✓ 版本與修訂追蹤
✓ 分發與通知
✓ 歸檔與檢索
常見於：營建、大型工程、政府專案
```

#### Git + 文檔 Repo（如 Git LFS）
```
類型：版本控制（程式碼 + 文檔）
用途：
✓ 設計檔、規格書用 Markdown/Word 存於 Repo
✓ 變更歷史、分支、Merge
✓ 與開發流程一致
✓ 適合技術團隊主導的 Waterfall 專案
```

---

### 5. 測試管理

#### HP ALM / Micro Focus ALM
```
類型：應用程式生命週期與測試管理
官網：microfocus.com

支援 Waterfall 的方式：
✓ 測試計劃（Test Plan）— 對應階段與需求
✓ 測試案例（Test Case）— 連結需求與設計
✓ 測試執行與結果記錄
✓ 缺陷（Defect）追蹤與連結測試
✓ 需求覆蓋率、測試覆蓋率報告
✓ 測試週期與階段（System Test、UAT）
✓ 與需求、缺陷工具整合
```

#### TestRail
```
類型：測試案例與執行管理
官網：testrail.com

支援 Waterfall 的方式：
✓ 測試計劃、測試套件、測試案例
✓ 測試執行與結果（Pass/Fail）
✓ 與 Jira、GitHub 整合
✓ 報告：覆蓋率、趨勢、缺陷統計
✓ 適合手動與自動化測試並存
```

#### Zephyr (Jira 外掛)
```
類型：Jira 內建測試管理
官網：zephyr.com

支援 Waterfall 的方式：
✓ 在 Jira 內建測試案例、測試週期
✓ 測試執行、結果、與需求/Story 連結
✓ 測試報告
✓ 適合已用 Jira 的團隊
```

#### qTest、TestLink
```
類型：測試管理平台
用途：
✓ 測試計劃、案例、執行、缺陷
✓ 需求追溯
✓ 報告與儀表板
✓ qTest 與 Jira 整合佳；TestLink 開源免費
```

---

### 6. 變更管理

#### ServiceNow (Change Management)
```
類型：IT 服務管理（ITSM）
官網：servicenow.com

支援 Waterfall 的方式：
✓ 變更請求（Change Request）建立與審批
✓ 變更類型：標準、一般、緊急
✓ 審核流程、CAB 會議
✓ 與專案、發布、問題管理整合
✓ 合規與稽核報告
```

#### Jira Service Management（變更專案）
```
類型：服務台 + 專案
官網：atlassian.com/software/jira/service-management

在 Waterfall 下的用法：
✓ 變更請求專案（Change Request Project）
✓ 工作流：提出 → 評估 → 審批 → 排程 → 實施 → 關閉
✓ 影響分析欄位、風險等級
✓ 與開發專案（Jira Software）連結
```

#### 自建流程 + 表單（如 Microsoft Forms + Power Automate）
```
用途：
✓ 變更請求表單
✓ 自動通知、審批路由
✓ 記錄與報表
適合：預算有限、流程簡單的團隊
```

---

### 7. 報告與儀表板（Waterfall）

#### 常見組合
```
專案進度報告：
- Microsoft Project → 甘特圖、時程偏差、資源報表
- Jira + 外掛（e.g. BigPicture）→ 階段完成率、里程碑

需求與品質：
- DOORS / Jama → 需求覆蓋率、追溯矩陣
- ALM / TestRail → 測試進度、缺陷密度、需求覆蓋

高階儀表板：
- Power BI / Tableau — 從 Jira、ALM、Project 取數
- Confluence 儀表板 — 嵌入 Jira 圖表、統計

交付物追蹤：
- SharePoint 文件庫 + 清單 — 交付物清單與連結
- Confluence 空間 — 按階段組織文件與狀態
```

---

## Agile 支援工具

### 1. 待辦清單、Sprint 與看板

#### Jira Software
```
類型：敏捷專案管理與議題追蹤
官網：atlassian.com/software/jira

支援 Agile 的方式：
✓ 專案類型：Scrum、Kanban
✓ 產品待辦清單（Product Backlog）— 故事、Epic、Bug、任務
✓ Sprint 規劃— Sprint 建立、Backlog 拖曳至 Sprint
✓ 看板（Board）— 欄位可自訂（To Do, In Progress, Review, Done）
✓ 故事點、預估、優先順序
✓ 燃盡圖（Burndown）、燃起圖（Burnup）
✓ 速度圖（Velocity）、累積流程圖（CFD）
✓ 篩選器、Sprint 報告、Release 規劃
✓ 與 Confluence、Bitbucket、GitHub、Slack 整合
✓ 外掛生態系（Retrospective、Planning Poker 等）

典型使用情境：
- Product Owner 管理 Backlog、排優先順序
- Sprint Planning 時將 Story 拉進 Sprint
- 每日更新任務狀態、看板可視化
- Sprint Review 前過濾「Done」項目
- Retrospective 後檢視速度與 CFD
```

#### Azure DevOps (Boards)
```
類型：微軟的 DevOps 與敏捷專案管理
官網：azure.microsoft.com/devops

支援 Agile 的方式：
✓ Boards：Backlog、Sprint、看板
✓ Work Items：User Story、Task、Bug、Epic、Feature
✓ 故事點、預估、優先順序、標籤
✓ 衝刺（Sprint）規劃與容量規劃
✓ 查詢、篩選、儀表板（Widgets）
✓ 燃盡、累積流程、速度
✓ 與 Repos（Git）、Pipelines（CI/CD）、Test Plans 整合
✓ 適合 .NET 與微軟生態系
```

#### Linear
```
類型：現代化議題追蹤與產品管理
官網：linear.app

支援 Agile 的方式：
✓ 簡潔的 Backlog、Sprint、Cycles
✓ 快捷鍵與鍵盤優先操作
✓ 自動化規則（狀態變更、指派、標籤）
✓ 與 GitHub、Slack、Figma 整合
✓ 路線圖、里程碑
✓ 適合新創與產品團隊
```

#### ClickUp
```
類型：全能型生產力與專案管理
官網：clickup.com

支援 Agile 的方式：
✓ 清單、看板、甘特、日曆視圖
✓ 任務、子任務、檢查清單
✓ 自訂狀態、Sprint 資料夾
✓ 時間追蹤、目標（Goals）
✓ 文檔、白板、表單
✓ 適合小團隊與混合使用
```

#### Trello
```
類型：看板式協作
官網：trello.com

支援 Agile 的方式：
✓ 看板（Board）— 列表（List）— 卡片（Card）
✓ 標籤、到期日、成員、附件、評論
✓ Power-Up：甘特圖、時間追蹤、自動化
✓ 簡易 Backlog + Doing + Done
✓ 適合輕量 Scrum/Kanban、小團隊
```

#### Asana
```
類型：任務與專案管理
官網：asana.com

支援 Agile 的方式：
✓ 專案、任務、子任務、里程碑
✓ 看板視圖、時間軸（甘特）
✓ 自訂欄位、標籤、依賴
✓ 範本：Sprint 規劃、Backlog
✓ 與 Slack、Google、Microsoft 整合
```

---

### 2. 協作與溝通

#### Slack
```
類型：團隊即時通訊
官網：slack.com

支援 Agile 的方式：
✓ 頻道（#sprint-10、#backend、#urgent）
✓ 與 Jira、GitHub、Azure DevOps 整合— 更新推播到頻道
✓ 視訊通話、螢幕分享（Daily、Planning、Review）
✓ 搜尋歷史、檔案分享
✓ 工作流程自動化（Workflow Builder）
✓ 非同步溝通減少會議
```

#### Microsoft Teams
```
類型：協作與通訊（微軟生態）
官網：microsoft.com/teams

支援 Agile 的方式：
✓ 團隊、頻道、聊天、視訊會議
✓ 與 Azure DevOps、Office、SharePoint 整合
✓ 每日站立、Sprint 審查可開會議
✓ 檔案協作、白板
✓ 適合企業與已用 Microsoft 的組織
```

#### Miro / Mural
```
類型：線上白板與協作
官網：miro.com / mural.co

支援 Agile 的方式：
✓ Sprint Planning：User Story Mapping、優先順序排列
✓ Retrospective：帆船、4Ls、Start/Stop/Continue 模板
✓ Daily Scrum：簡易看板、障礙清單
✓ 腦力激盪、流程圖、線框
✓ 即時協作、投票、計時器
✓ 適合遠端與混合團隊
```

#### Confluence（Agile 用法）
```
類型：知識庫與協作
官網：atlassian.com/software/confluence

支援 Agile 的方式：
✓ 產品願景、Roadmap、Release Notes
✓ Sprint 記錄、Retro 行動項目
✓ 技術設計（ADR）、API 文檔
✓ 與 Jira 雙向連結（Story、Sprint）
✓ 模板：Sprint Review、Retro、Product Backlog Refinement
```

---

### 3. 持續整合 / 持續部署（CI/CD）

#### GitHub Actions
```
類型：CI/CD（整合於 GitHub）
官網：github.com/features/actions

支援 Agile 的方式：
✓ 每次 Push/PR 觸發建置、測試
✓ 自動化部署到 Staging/Production
✓ 與 Jira 整合（commit、PR 關聯 Issue）
✓ 支援容器、多環境、密鑰管理
✓ 每個 Sprint 可頻繁、可預測地發布
```

#### GitLab CI/CD
```
類型：內建於 GitLab 的 CI/CD
官網：gitlab.com

支援 Agile 的方式：
✓ Pipeline：Build → Test → Deploy
✓ 與 GitLab Issues、Milestones 整合（Agile 看板）
✓ 自動化測試、程式碼品質、安全掃描
✓ 環境、變數、權限管理
✓ 適合程式碼與 CI/CD 同平台的團隊
```

#### Jenkins
```
類型：開源 CI 伺服器
官網：jenkins.io

支援 Agile 的方式：
✓ 建置、測試、部署自動化
✓ 外掛豐富（Jira、Slack、Docker、K8s）
✓ 多分支 Pipeline、參數化建置
✓ 適合自建、高度自訂的環境
```

#### Azure Pipelines、CircleCI、Travis CI、Bitbucket Pipelines
```
共通點：
✓ 與程式碼 Repo 整合
✓ 建置、測試、部署自動化
✓ 支援 Docker、K8s、多雲
✓ 讓每個 Sprint 的增量可自動、安全地部署
```

---

### 4. 自動化測試與品質

#### Selenium、Cypress、Playwright
```
類型：自動化 UI / E2E 測試
用途：
✓ 回歸測試自動化，支援頻繁發布
✓ 與 CI 整合，每次建置執行
✓ 減少手動測試負擔，配合短 Sprint
```

#### JUnit、pytest、Jest、xUnit
```
類型：單元測試框架
用途：
✓ 開發時即撰寫測試（TDD）
✓ CI 中執行，快速回饋
✓ 覆蓋率報告，維持 Definition of Done
```

#### SonarQube / SonarCloud
```
類型：程式碼品質與安全
官網：sonarsource.com

支援 Agile 的方式：
✓ 程式碼品質、重複、壞味道、漏洞
✓ 與 CI 整合，每次提交檢查
✓ 品質閘門（Quality Gate）— 未通過可阻擋 Merge
✓ 技術債務可視化，Retro 可討論
```

#### TestRail、Zephyr、Xray（測試管理）
```
在 Agile 下的用法：
✓ 測試案例連結到 User Story
✓ 每個 Sprint 執行對應測試
✓ 自動化測試結果匯入
✓ 覆蓋率與「Done」標準對齊
```

---

### 5. 敏捷儀式與實踐支援

#### Planning Poker / 估計
```
工具範例：
- Jira 外掛：Planning Poker for Jira、Story Points
- 獨立：planningpoker.com、scrumpoker.online
- Miro/Mural 模板：投票與共識

用途：Sprint Planning 時對 Story 做故事點估計
```

#### Daily Stand-up
```
常見做法：
- 實體：看板前 15 分鐘
- 遠端：Slack 非同步（每人貼三句話）或 Zoom/Teams 視訊
- 工具：Jira 看板、Miro 每日站會模板、Geekbot（Slack Bot 收集更新）
```

#### Sprint Review / Demo
```
工具：
- 視訊：Zoom、Teams、Google Meet
- 螢幕分享 + 實際操作
- 簡報（如需要）：Google Slides、Confluence 頁面
- 錄影：Loom、Teams 錄製— 給未參與者回放
```

#### Retrospective
```
工具：
- Miro / Mural：帆船、4Ls、Start/Stop/Continue 模板
- Confluence：Retro 頁面模板、行動項目清單
- Jira：建立 Retro 行動項為 Story/Task 並排入下個 Sprint
- 專用：FunRetro、Retrium、EasyRetro
```

#### Backlog Refinement
```
工具：
- Jira Backlog 視圖：細化、估計、排序
- Confluence：User Story 撰寫模板、Acceptance Criteria 範例
- Miro：User Story Map、優先順序討論
```

---

### 6. 度量與可視化（Agile）

#### Jira 內建報告
```
常用：
- 燃盡圖（Burndown Chart）
- 燃起圖（Burnup Chart）
- 速度圖（Velocity Chart）
- 累積流程圖（Cumulative Flow Diagram）
- Sprint 報告、Epic 報告、版本報告
```

#### Azure DevOps 儀表板
```
常用：
- Sprint 燃盡、剩餘工作
- 累積流程圖
- 速度、品質指標
- 自訂 Widget、查詢圖表
```

#### Power BI / Tableau / Grafana
```
用途：
- 從 Jira、Azure DevOps、GitHub 取數
- 自訂：速度趨勢、週期時間、吞吐量、品質
- 多團隊、多專案儀表板
- 適合高階與多團隊視角
```

#### Screenful、Nave、Customizable Dashboards
```
類型：Jira/敏捷專用儀表板
用途：
✓ 更豐富的敏捷圖表
✓ 多專案彙總
✓ 週期時間、前置時間、WIP
✓ 可對外展示或大螢幕
```

---

## 跨方法論通用工具

### 版本控制
```
Git + GitHub / GitLab / Bitbucket / Azure Repos
- Waterfall：分支對應階段（如 release/phase3-testing）
- Agile：Feature branch、main、tag 對應 Release/Sprint
```

### 文檔與知識庫
```
Confluence、Notion、Google Docs、SharePoint
- Waterfall：規格書、設計文件、手冊、審核記錄
- Agile：產品說明、Sprint 記錄、技術決策、Wiki
```

### 視訊與會議
```
Zoom、Microsoft Teams、Google Meet
- 兩者皆用於：啟動會議、審查、培訓、遠端 Daily/Planning
```

### 時間追蹤（可選）
```
Toggl、Harvest、Jira 時間記錄、Azure DevOps
- Waterfall：任務工時、成本核算
- Agile：容量規劃、改善估計（可選）
```

---

## 工具選擇建議

### 依組織規模與預算

| 情境 | Waterfall 建議 | Agile 建議 |
|------|----------------|------------|
| 小型團隊、預算有限 | Smartsheet + Confluence + 試算表 | Trello/ClickUp + GitHub + Slack |
| 中型團隊、混合專案 | Jira + Confluence + TestRail | Jira Software + Confluence + GitHub Actions |
| 大型、企業、合規要求高 | MS Project / Primavera + DOORS/Jama + ALM | Azure DevOps 或 Jira + 企業版 + CI/CD 套件 |
| 微軟技術棧為主 | MS Project + Azure DevOps + Teams | Azure DevOps (Boards+Pipelines+Repos) + Teams |

### 依產業與合規

| 產業 | 特別常用（Waterfall） | 特別常用（Agile） |
|------|----------------------|-------------------|
| 金融、保險 | DOORS/Jama、ALM、變更管理（ServiceNow） | Jira + 合規外掛、審計日誌、Azure DevOps |
| 醫療、生醫 | DOORS、Jama、ALM、文檔控制 | Jira + 追溯、TestRail、合規報告 |
| 航太、國防 | DOORS、Primavera、Enterprise Architect | 較少純 Agile，多混合或 SAFe + 上述工具 |
| 新創、網路服務 | 較少純 Waterfall | Jira/Linear + GitHub + Slack + Miro |

### 快速對照表

| 用途 | Waterfall 常用工具 | Agile 常用工具 |
|------|-------------------|----------------|
| 專案排程與階段 | MS Project, Primavera, Smartsheet | — |
| 待辦與 Sprint | Jira (用 Epic/階段), Smartsheet | Jira Software, Azure DevOps, Linear, Trello |
| 需求管理 | DOORS, Jama, Confluence | Jira (Story), Confluence, Productboard |
| 設計/建模 | Enterprise Architect, Lucidchart, Visio | Lucidchart, Miro, Confluence |
| 文檔 | SharePoint, Confluence, 文檔控制系統 | Confluence, Notion, Wiki |
| 測試管理 | ALM, TestRail, Zephyr | TestRail, Zephyr, Xray, Azure Test Plans |
| 缺陷追蹤 | Jira, ALM, ServiceNow | Jira, Azure DevOps, GitHub Issues |
| 變更管理 | ServiceNow, Jira SM, 自建流程 | Backlog 優先順序、Jira 狀態流 |
| CI/CD | Jenkins, Azure DevOps, GitLab CI | GitHub Actions, GitLab CI, Jenkins, Azure Pipelines |
| 溝通協作 | Email, 會議, SharePoint | Slack, Teams, Miro, Confluence |
| 報告與儀表板 | Project 報表, Power BI, ALM 報告 | 燃盡/速度/CFD, Power BI, 自訂儀表板 |

---

## 小結

- **Waterfall** 工具重點：階段排程、需求追溯、文檔版本與審核、測試計劃與階段、變更控制、正式報告。
- **Agile** 工具重點：Backlog、Sprint、看板、即時協作、CI/CD、自動化測試、敏捷度量與儀式支援。
- 許多工具可**同時支援**兩種方式（如 Jira、Confluence、Azure DevOps），差別在**使用方式與流程設計**，而非僅在產品種類。

依您的專案規模、產業與合規需求，從上表與各節說明中挑選組合即可；若需要針對某一類工具（例如只列「需求管理」或「CI/CD」）再細化成單一檔案，也可以再說明需求。

---

[返回目錄](./README.md) | [上一章：具體執行指南](./05-Practical-Examples.md)
