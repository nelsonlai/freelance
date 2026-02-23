# 第 19 課：JavaScript 基礎介紹

## 📚 本課學習目標

- 理解什麼是 JavaScript 及其用途
- 學會在網頁中使用 JavaScript
- 掌握基本的輸出方法
- 了解 JavaScript 的基本語法

## 🌟 什麼是 JavaScript？

**JavaScript** 是一種程式語言，讓網頁能夠「動起來」，實現互動功能。

### HTML、CSS、JavaScript 的關係

```
HTML      → 網頁的結構（骨架）
CSS       → 網頁的樣式（外觀）
JavaScript → 網頁的行為（互動）
```

### JavaScript 可以做什麼？

- ✅ 響應使用者操作（點擊、輸入等）
- ✅ 動態改變網頁內容
- ✅ 表單驗證
- ✅ 建立動畫效果
- ✅ 與伺服器通訊（AJAX）
- ✅ 建立網頁應用程式

## 🔧 JavaScript 的使用方式

### 1. 內嵌 JavaScript（Inline）

直接在 HTML 標籤中使用：

```html
<button onclick="alert('你好！')">點我</button>
```

**不建議使用**，因為會混合 HTML 和 JavaScript。

### 2. 內部 JavaScript（Internal）

在 `<script>` 標籤中撰寫：

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>JavaScript 範例</title>
</head>
<body>
    <h1>我的網頁</h1>
    <button id="myButton">點我</button>
    
    <script>
        // JavaScript 代碼寫在這裡
        document.getElementById('myButton').onclick = function() {
            alert('你點了按鈕！');
        };
    </script>
</body>
</html>
```

### 3. 外部 JavaScript（External）★ 推薦

將 JavaScript 寫在獨立的 `.js` 檔案中：

**script.js**
```javascript
// JavaScript 代碼
document.getElementById('myButton').onclick = function() {
    alert('你點了按鈕！');
};
```

**index.html**
```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>JavaScript 範例</title>
</head>
<body>
    <h1>我的網頁</h1>
    <button id="myButton">點我</button>
    
    <!-- 引入外部 JavaScript 檔案 -->
    <script src="script.js"></script>
</body>
</html>
```

## 📢 JavaScript 輸出方法

### 1. console.log() - 主控台輸出

```javascript
console.log('這是主控台訊息');
console.log(123);
console.log(true);
```

**查看方式**：按 F12 開啟開發者工具 → Console 標籤

### 2. alert() - 彈出警告框

```javascript
alert('這是警告訊息');
```

### 3. document.write() - 寫入網頁

```javascript
document.write('這段文字會顯示在網頁上');
```

**注意**：不建議在頁面載入後使用，會覆蓋整個頁面。

### 4. innerHTML - 改變元素內容

```javascript
document.getElementById('demo').innerHTML = '新的內容';
```

## 💻 實作練習 1：第一個 JavaScript 程式

請參考 `examples/lesson-19/example-01-first-javascript.html`

## 📝 JavaScript 基本語法

### 1. 註解

```javascript
// 這是單行註解

/*
   這是
   多行
   註解
*/
```

### 2. 區分大小寫

```javascript
let name = 'John';
let Name = 'Jane';  // 不同的變數
```

### 3. 分號

```javascript
console.log('Hello');  // 建議加分號
console.log('World')   // 也可以不加（會自動插入）
```

**建議**：養成加分號的習慣。

### 4. 空白和換行

```javascript
// 可讀性好
let x = 5;
let y = 10;
let sum = x + y;

// 可讀性差
let x=5;let y=10;let sum=x+y;
```

## 💻 實作練習 2：輸出方法示範

請參考 `examples/lesson-19/example-02-output-methods.html`

## 🔍 開發者工具

### 打開開發者工具

- **Windows/Linux**: F12 或 Ctrl + Shift + I
- **Mac**: Cmd + Option + I

### 常用標籤

1. **Console（主控台）**
   - 查看 `console.log()` 輸出
   - 執行 JavaScript 代碼
   - 查看錯誤訊息

2. **Elements（元素）**
   - 查看和修改 HTML/CSS
   - 即時預覽變化

3. **Sources（來源）**
   - 查看 JavaScript 檔案
   - 設定中斷點除錯

4. **Network（網路）**
   - 查看網路請求
   - 檢查載入速度

## 💻 實作練習 3：互動範例

請參考 `examples/lesson-19/example-03-interactive.html`

## 🎯 JavaScript 執行順序

### Script 標籤位置

```html
<!DOCTYPE html>
<html>
<head>
    <!-- 在 head 中：頁面未載入完成就執行 -->
    <script src="early.js"></script>
</head>
<body>
    <h1>標題</h1>
    
    <!-- 在 body 末尾：頁面載入完成後執行（推薦） -->
    <script src="main.js"></script>
</body>
</html>
```

### defer 和 async 屬性

```html
<!-- defer：等 HTML 解析完再執行 -->
<script src="script.js" defer></script>

<!-- async：下載完立即執行 -->
<script src="script.js" async></script>
```

## 🔧 常見錯誤

### 1. 找不到元素

```javascript
// 錯誤：script 在元素之前執行
<script>
    document.getElementById('demo').innerHTML = 'Hello';
</script>
<div id="demo"></div>

// 正確：script 在元素之後
<div id="demo"></div>
<script>
    document.getElementById('demo').innerHTML = 'Hello';
</script>
```

### 2. 拼字錯誤

```javascript
// 錯誤
consle.log('Hello');  // consle 拼錯

// 正確
console.log('Hello');
```

### 3. 缺少引號

```javascript
// 錯誤
console.log(Hello);  // Hello 沒有引號

// 正確
console.log('Hello');
```

## 📝 本課重點回顧

- ✅ JavaScript 是網頁的行為層，實現互動功能
- ✅ 推薦使用外部 JavaScript 檔案
- ✅ console.log() 用於除錯，輸出到主控台
- ✅ alert() 顯示彈出警告框
- ✅ innerHTML 可以改變元素內容
- ✅ JavaScript 區分大小寫
- ✅ 建議將 script 標籤放在 body 末尾
- ✅ 使用開發者工具（F12）查看輸出和錯誤

## 🎯 課後練習

1. **基礎練習**：建立第一個 JavaScript 程式
   - 在網頁中顯示「Hello, JavaScript!」
   - 使用 console.log() 輸出訊息
   - 建立一個按鈕，點擊後彈出警告框

2. **進階挑戰**：互動問候
   - 建立一個按鈕
   - 點擊後改變頁面標題的文字
   - 使用 innerHTML 修改內容

3. **實戰練習**：簡單計算機
   - 建立兩個輸入框和一個按鈕
   - 點擊按鈕後顯示兩數相加的結果
   - 將結果顯示在網頁上

## 🔗 下一課預告

在下一課中，我們將學習 JavaScript 的變數和資料型別，了解如何儲存和處理資料！

---

[← 上一課：CSS 進階技巧](./18-css-advanced.md) | [返回目錄](../README.md) | [下一課：變數和資料型別 →](./20-variables-datatypes.md)
