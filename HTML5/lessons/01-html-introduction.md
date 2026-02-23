# 第 1 課：HTML 基礎介紹

## 📚 本課學習目標

- 理解什麼是 HTML 及其用途
- 認識 HTML 文件的基本結構
- 學會建立第一個 HTML 網頁
- 了解 HTML 標籤的基本概念

## 🌟 什麼是 HTML？

**HTML**（HyperText Markup Language，超文本標記語言）是用來建立網頁的標準標記語言。它不是程式語言，而是一種**標記語言**，用來描述網頁的結構和內容。

### HTML 的特點

- 📝 使用**標籤（Tags）**來標記內容
- 🏗️ 定義網頁的**結構**和**語義**
- 🌐 所有網頁瀏覽器都支援 HTML
- 📖 易於學習和使用

## 🏗️ HTML 文件基本結構

一個完整的 HTML 文件包含以下基本結構：

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>我的第一個網頁</title>
</head>
<body>
    <h1>歡迎來到 HTML 世界！</h1>
    <p>這是我的第一個網頁。</p>
</body>
</html>
```

### 結構解析

| 標籤 | 說明 |
|------|------|
| `<!DOCTYPE html>` | 聲明文件類型為 HTML5 |
| `<html>` | HTML 文件的根元素 |
| `<head>` | 包含網頁的元資料（不顯示在頁面上） |
| `<meta charset="UTF-8">` | 設定字元編碼為 UTF-8 |
| `<meta name="viewport">` | 設定視窗大小，用於響應式設計 |
| `<title>` | 定義網頁標題（顯示在瀏覽器標籤上） |
| `<body>` | 包含網頁的實際內容（顯示在頁面上） |

## 🏷️ HTML 標籤基本概念

### 標籤的結構

HTML 標籤通常成對出現：

```html
<標籤名稱>內容</標籤名稱>
```

例如：
```html
<p>這是一個段落。</p>
<h1>這是一個標題。</h1>
```

### 自封閉標籤

有些標籤不需要結束標籤，稱為**自封閉標籤**：

```html
<br>      <!-- 換行 -->
<hr>      <!-- 水平線 -->
<img src="image.jpg" alt="圖片">  <!-- 圖片 -->
```

### 標籤的屬性

標籤可以包含**屬性**，提供額外的資訊：

```html
<a href="https://www.example.com" target="_blank">連結文字</a>
```

- `href` 和 `target` 是屬性
- `"https://www.example.com"` 和 `"_blank"` 是屬性值

## 💻 實作練習 1：建立第一個網頁

創建一個名為 `my-first-page.html` 的檔案，輸入以下內容：

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>自我介紹</title>
</head>
<body>
    <h1>哈囉！我是張小明</h1>
    <p>我正在學習 HTML5 網頁設計。</p>
    <p>這是我建立的第一個網頁，很興奮！</p>
</body>
</html>
```

**步驟：**
1. 打開文字編輯器（如 VS Code）
2. 複製上面的程式碼
3. 儲存為 `my-first-page.html`
4. 用瀏覽器開啟檔案

## 💻 實作練習 2：加入更多內容

修改上面的網頁，加入以下元素：

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>自我介紹</title>
</head>
<body>
    <h1>哈囉！我是張小明</h1>
    <h2>關於我</h2>
    <p>我正在學習 HTML5 網頁設計。</p>
    <p>這是我建立的第一個網頁，很興奮！</p>
    
    <h2>我的興趣</h2>
    <p>我喜歡程式設計、閱讀和旅行。</p>
    
    <h2>聯絡方式</h2>
    <p>電子郵件：ming@example.com</p>
</body>
</html>
```

## 🔍 常見的 HTML 標籤

| 標籤 | 用途 | 範例 |
|------|------|------|
| `<h1>` ~ `<h6>` | 標題（h1 最大，h6 最小） | `<h1>主標題</h1>` |
| `<p>` | 段落 | `<p>這是一個段落。</p>` |
| `<br>` | 換行 | `第一行<br>第二行` |
| `<hr>` | 水平分隔線 | `<hr>` |
| `<!--  -->` | 註解（不會顯示） | `<!-- 這是註解 -->` |

## 📝 本課重點回顧

- ✅ HTML 是建立網頁的標記語言
- ✅ HTML 文件由 `<!DOCTYPE html>`、`<html>`、`<head>` 和 `<body>` 組成
- ✅ HTML 標籤通常成對出現，如 `<p>內容</p>`
- ✅ 標籤可以包含屬性，提供額外資訊
- ✅ 使用 `<h1>` ~ `<h6>` 建立標題，`<p>` 建立段落

## 🎯 課後練習

1. **基礎練習**：建立一個介紹你最喜歡的電影、書籍或音樂的網頁
   - 使用 `<h1>` 作為主標題
   - 使用 `<h2>` 作為小標題
   - 使用 `<p>` 撰寫至少 3 個段落

2. **進階挑戰**：建立一個「我的一天」網頁
   - 使用不同層級的標題來區分早上、中午、晚上
   - 每個時段寫 2-3 個段落描述你的活動
   - 在適當的地方加入 `<hr>` 分隔線

3. **思考問題**：
   - 為什麼需要 `<!DOCTYPE html>`？
   - `<head>` 和 `<body>` 有什麼不同？
   - 註解標籤 `<!--  -->` 有什麼用途？

## 🔗 下一課預告

在下一課中，我們將學習更多文字格式化的標籤，包括粗體、斜體、底線、刪除線等，讓網頁內容更加豐富多彩！

---

[← 返回目錄](../README.md) | [下一課：文字標籤和格式化 →](./02-text-formatting.md)
