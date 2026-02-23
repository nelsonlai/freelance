# 第 10 課：CSS 基礎介紹

## 📚 本課學習目標

- 理解什麼是 CSS 及其用途
- 學會三種 CSS 引入方式
- 掌握 CSS 基本語法
- 了解 CSS 註解和常用屬性

## 🎨 什麼是 CSS？

**CSS（Cascading Style Sheets，層疊樣式表）**是用來控制網頁外觀和版面配置的樣式語言。

### HTML vs CSS

- **HTML**：網頁的結構和內容（骨架）
- **CSS**：網頁的外觀和樣式（皮膚）
- **JavaScript**：網頁的行為和互動（肌肉）

### 範例對比

#### 只有 HTML

```html
<h1>歡迎</h1>
<p>這是一個段落。</p>
```

**效果**：純文字，黑白單調

#### HTML + CSS

```html
<h1 style="color: #4ECDC4; text-align: center;">歡迎</h1>
<p style="color: #666; font-size: 18px;">這是一個段落。</p>
```

**效果**：有顏色、大小、對齊等樣式

## 📝 CSS 基本語法

```css
選擇器 {
    屬性名稱: 屬性值;
    屬性名稱: 屬性值;
}
```

### 範例

```css
p {
    color: blue;
    font-size: 16px;
    margin: 20px;
}
```

**語法說明：**
- `p`：選擇器（選擇要套用樣式的元素）
- `{}`：大括號包含所有樣式規則
- `color: blue;`：樣式聲明（屬性名稱 : 屬性值;）
- `;`：分號分隔每個樣式聲明

## 🔧 三種 CSS 引入方式

### 1. 內嵌樣式（Inline Styles）

直接在 HTML 標籤中使用 `style` 屬性：

```html
<h1 style="color: red; font-size: 32px;">標題</h1>
<p style="color: blue;">段落內容</p>
```

**優點：**
- 優先權最高
- 適合快速測試

**缺點：**
- 不易維護
- 無法重複使用
- HTML 和 CSS 混在一起

**適用情境：**
- 快速測試
- 單一元素的特殊樣式
- 動態產生的樣式（JavaScript）

### 2. 內部樣式表（Internal Stylesheet）

在 `<head>` 標籤中使用 `<style>` 標籤：

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>內部樣式表</title>
    <style>
        h1 {
            color: #4ECDC4;
            text-align: center;
        }
        
        p {
            color: #666;
            font-size: 18px;
            line-height: 1.6;
        }
        
        .highlight {
            background-color: yellow;
            padding: 5px;
        }
    </style>
</head>
<body>
    <h1>歡迎來到我的網站</h1>
    <p>這是一段<span class="highlight">重要</span>的文字。</p>
</body>
</html>
```

**優點：**
- 樣式集中管理
- 可重複使用
- 適合單頁面網站

**缺點：**
- 只能用於單一 HTML 檔案
- 多個頁面無法共用樣式

**適用情境：**
- 單頁面應用
- 頁面特定樣式

### 3. 外部樣式表（External Stylesheet）★ 最推薦

將 CSS 寫在獨立的 `.css` 檔案中：

**styles.css**
```css
/* 這是 CSS 檔案 */
h1 {
    color: #4ECDC4;
    text-align: center;
    margin-bottom: 20px;
}

p {
    color: #666;
    font-size: 18px;
    line-height: 1.6;
}

.highlight {
    background-color: yellow;
    padding: 5px;
}
```

**index.html**
```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>外部樣式表</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <h1>歡迎來到我的網站</h1>
    <p>這是一段<span class="highlight">重要</span>的文字。</p>
</body>
</html>
```

**優點：**
- 多個頁面可共用
- HTML 和 CSS 完全分離
- 易於維護和修改
- 瀏覽器可快取，提升效能

**缺點：**
- 需要額外的 HTTP 請求
- 多一個檔案要管理

**適用情境：**
- 多頁面網站（最常用）
- 大型專案
- 團隊協作

## 💻 實作練習 1：三種方式比較

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 引入方式比較</title>
    
    <!-- 內部樣式表 -->
    <style>
        body {
            font-family: 'Microsoft JhengHei', Arial, sans-serif;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        .section {
            background-color: white;
            padding: 20px;
            margin-bottom: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        h2 {
            color: #667eea;
            border-bottom: 3px solid #667eea;
            padding-bottom: 10px;
        }
        
        .method {
            background-color: #f9f9f9;
            padding: 15px;
            margin: 10px 0;
            border-left: 4px solid #4ECDC4;
        }
    </style>
</head>
<body>
    <h1 style="text-align: center; color: #333;">CSS 引入方式示範</h1>
    
    <div class="section">
        <h2>1. 內嵌樣式（Inline）</h2>
        <div class="method">
            <!-- 這裡使用內嵌樣式 -->
            <p style="color: red; font-size: 20px; font-weight: bold;">
                這段文字使用內嵌樣式（style 屬性）
            </p>
        </div>
    </div>
    
    <div class="section">
        <h2>2. 內部樣式表（Internal）</h2>
        <div class="method">
            <!-- 這裡使用內部樣式表（在 head 中的 style 標籤） -->
            <p class="internal-style">
                這段文字使用內部樣式表
            </p>
        </div>
    </div>
    
    <div class="section">
        <h2>3. 外部樣式表（External）</h2>
        <div class="method">
            <p>外部樣式表需要另外建立 .css 檔案並使用 link 標籤引入</p>
            <code>&lt;link rel="stylesheet" href="styles.css"&gt;</code>
        </div>
    </div>
    
    <style>
        .internal-style {
            color: green;
            font-size: 20px;
            font-weight: bold;
        }
    </style>
</body>
</html>
```

## 📝 CSS 註解

CSS 使用 `/* */` 來寫註解：

```css
/* 這是單行註解 */

/* 
   這是
   多行
   註解
*/

h1 {
    color: blue;  /* 這也是註解 */
    /* font-size: 20px; */ /* 被註解掉的程式碼不會生效 */
}
```

## 🎨 常用的 CSS 屬性分類

### 1. 文字相關

```css
p {
    color: #333;              /* 文字顏色 */
    font-size: 16px;          /* 字體大小 */
    font-family: Arial;       /* 字體 */
    font-weight: bold;        /* 字體粗細 */
    font-style: italic;       /* 斜體 */
    text-align: center;       /* 文字對齊 */
    text-decoration: underline; /* 文字裝飾 */
    line-height: 1.6;         /* 行高 */
    letter-spacing: 2px;      /* 字母間距 */
}
```

### 2. 背景相關

```css
div {
    background-color: #f5f5f5;           /* 背景顏色 */
    background-image: url('bg.jpg');     /* 背景圖片 */
    background-repeat: no-repeat;        /* 背景重複 */
    background-size: cover;              /* 背景大小 */
    background-position: center;         /* 背景位置 */
}
```

### 3. 邊框相關

```css
div {
    border: 2px solid #ddd;    /* 邊框 */
    border-radius: 10px;       /* 圓角 */
    border-color: red;         /* 邊框顏色 */
    border-width: 3px;         /* 邊框寬度 */
    border-style: dashed;      /* 邊框樣式 */
}
```

### 4. 間距相關

```css
div {
    margin: 20px;      /* 外邊距 */
    padding: 15px;     /* 內邊距 */
}
```

### 5. 尺寸相關

```css
div {
    width: 300px;      /* 寬度 */
    height: 200px;     /* 高度 */
    max-width: 100%;   /* 最大寬度 */
    min-height: 50px;  /* 最小高度 */
}
```

## 💻 實作練習 2：基本樣式應用

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 基本樣式練習</title>
    <style>
        body {
            font-family: 'Microsoft JhengHei', Arial, sans-serif;
            margin: 0;
            padding: 0;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
        }
        
        .container {
            max-width: 800px;
            margin: 0 auto;
            padding: 40px 20px;
        }
        
        h1 {
            color: white;
            text-align: center;
            font-size: 48px;
            margin-bottom: 40px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }
        
        .card {
            background-color: white;
            padding: 30px;
            margin-bottom: 20px;
            border-radius: 15px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
        }
        
        .card h2 {
            color: #667eea;
            font-size: 28px;
            margin-top: 0;
            margin-bottom: 15px;
            border-bottom: 3px solid #667eea;
            padding-bottom: 10px;
        }
        
        .card p {
            color: #666;
            font-size: 18px;
            line-height: 1.8;
            margin: 15px 0;
        }
        
        .highlight {
            background-color: #FFE66D;
            padding: 3px 8px;
            border-radius: 3px;
            font-weight: bold;
        }
        
        .button {
            display: inline-block;
            background-color: #4ECDC4;
            color: white;
            padding: 12px 30px;
            text-decoration: none;
            border-radius: 25px;
            font-weight: bold;
            transition: background-color 0.3s;
        }
        
        .button:hover {
            background-color: #38A3A5;
        }
        
        .info-box {
            background-color: #E8F8F5;
            border-left: 5px solid #4ECDC4;
            padding: 15px;
            margin: 20px 0;
        }
        
        .warning-box {
            background-color: #FFF4E6;
            border-left: 5px solid #FFB84D;
            padding: 15px;
            margin: 20px 0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎨 CSS 基本樣式示範</h1>
        
        <div class="card">
            <h2>文字樣式</h2>
            <p>
                這是一段<span class="highlight">重點文字</span>，
                展示如何使用 CSS 來美化文字內容。
            </p>
            <p style="font-style: italic; color: #888;">
                這段文字是斜體並且顏色較淺。
            </p>
        </div>
        
        <div class="card">
            <h2>資訊框</h2>
            <div class="info-box">
                <strong>提示：</strong>這是一個資訊框，使用了邊框和背景顏色。
            </div>
            <div class="warning-box">
                <strong>注意：</strong>這是一個警告框，使用了不同的配色方案。
            </div>
        </div>
        
        <div class="card">
            <h2>按鈕樣式</h2>
            <p>這是一個使用 CSS 美化的按鈕：</p>
            <a href="#" class="button">點擊我</a>
        </div>
        
        <div class="card">
            <h2>總結</h2>
            <p>
                透過 CSS，我們可以輕鬆地控制網頁的外觀，
                包括顏色、字體、間距、邊框等各種視覺效果。
            </p>
        </div>
    </div>
</body>
</html>
```

## 🎨 顏色表示方式

CSS 中有多種方式表示顏色：

### 1. 顏色名稱

```css
color: red;
color: blue;
color: green;
```

### 2. 十六進位（Hexadecimal）

```css
color: #FF0000;  /* 紅色 */
color: #00FF00;  /* 綠色 */
color: #0000FF;  /* 藍色 */
color: #FFF;     /* 白色（簡寫） */
```

### 3. RGB

```css
color: rgb(255, 0, 0);      /* 紅色 */
color: rgb(0, 255, 0);      /* 綠色 */
color: rgba(0, 0, 255, 0.5); /* 藍色，透明度 50% */
```

### 4. HSL

```css
color: hsl(0, 100%, 50%);      /* 紅色 */
color: hsla(120, 100%, 50%, 0.5); /* 綠色，透明度 50% */
```

## 📏 尺寸單位

### 絕對單位

- `px`：像素（最常用）
- `pt`：點
- `cm`：公分
- `mm`：公釐
- `in`：英吋

### 相對單位

- `%`：百分比
- `em`：相對於父元素的字體大小
- `rem`：相對於根元素的字體大小
- `vw`：視窗寬度的 1%
- `vh`：視窗高度的 1%

```css
div {
    width: 300px;      /* 固定 300 像素 */
    width: 50%;        /* 父元素寬度的 50% */
    font-size: 16px;   /* 16 像素 */
    font-size: 1.2em;  /* 父元素字體大小的 1.2 倍 */
    width: 50vw;       /* 視窗寬度的 50% */
}
```

## 📝 本課重點回顧

- ✅ CSS 用來控制網頁的外觀和樣式
- ✅ CSS 語法：選擇器 { 屬性: 值; }
- ✅ 三種引入方式：內嵌、內部、外部（推薦外部）
- ✅ 使用 `/* */` 寫註解
- ✅ 常用屬性：color、font-size、background、border、margin、padding
- ✅ 顏色可用名稱、十六進位、RGB、HSL 表示
- ✅ 單位有絕對（px）和相對（%、em、rem）兩種

## 🎯 課後練習

1. **基礎練習**：美化自我介紹頁面
   - 使用內部樣式表
   - 設定標題顏色和大小
   - 調整段落的字體和行高
   - 加入背景顏色

2. **進階挑戰**：建立個人名片
   - 使用外部樣式表
   - 包含姓名、職稱、聯絡方式
   - 使用不同的文字樣式
   - 加入邊框和圓角
   - 設定背景漸層

3. **實戰練習**：改造之前的 HTML 作業
   - 選擇之前做過的 HTML 作業
   - 加入 CSS 美化
   - 使用至少 10 種不同的 CSS 屬性
   - 嘗試不同的顏色配色方案

## 🔗 下一課預告

在下一課中，我們將深入學習 CSS 選擇器和特異性，了解如何精確地選擇要套用樣式的元素！

---

[← 上一課：HTML5 新功能](./09-html5-features.md) | [返回目錄](../README.md) | [下一課：選擇器和特異性 →](./11-selectors-specificity.md)
