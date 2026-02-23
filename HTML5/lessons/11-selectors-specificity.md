# 第 11 課：選擇器和特異性

## 📚 本課學習目標

- 掌握各種 CSS 選擇器
- 理解選擇器的特異性（優先權）
- 學會組合選擇器
- 了解偽類和偽元素

## 🎯 基本選擇器

### 1. 元素選擇器（Type Selector）

選擇所有指定的 HTML 元素：

```css
p {
    color: blue;
}

h1 {
    font-size: 32px;
}

a {
    text-decoration: none;
}
```

### 2. 類別選擇器（Class Selector）

使用 `.` 選擇具有特定 class 的元素：

```html
<p class="highlight">這段文字會被選中</p>
<p>這段不會</p>
```

```css
.highlight {
    background-color: yellow;
    font-weight: bold;
}
```

**一個元素可以有多個 class：**

```html
<p class="highlight important">多個類別</p>
```

```css
.highlight {
    background-color: yellow;
}

.important {
    color: red;
    font-weight: bold;
}
```

### 3. ID 選擇器（ID Selector）

使用 `#` 選擇具有特定 id 的元素：

```html
<div id="header">網站標題</div>
```

```css
#header {
    background-color: #333;
    color: white;
    padding: 20px;
}
```

**注意：**
- ID 在頁面中必須唯一
- ID 的優先權比 class 高

### 4. 通用選擇器（Universal Selector）

使用 `*` 選擇所有元素：

```css
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}
```

## 💻 實作練習 1：基本選擇器

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 選擇器示範</title>
    <style>
        * {
            margin: 0;
            padding: 0;
        }
        
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        h1 {
            color: #667eea;
            text-align: center;
            margin-bottom: 30px;
        }
        
        p {
            line-height: 1.6;
            margin-bottom: 15px;
        }
        
        .highlight {
            background-color: #FFE66D;
            padding: 5px;
        }
        
        .important {
            color: red;
            font-weight: bold;
        }
        
        #intro {
            background-color: #E8F8F5;
            padding: 20px;
            border-radius: 10px;
            border-left: 5px solid #4ECDC4;
        }
    </style>
</head>
<body>
    <h1>CSS 選擇器示範</h1>
    
    <div id="intro">
        <p>這段文字使用 ID 選擇器設定樣式。</p>
    </div>
    
    <p>這是一般段落。</p>
    <p class="highlight">這段使用 class 選擇器。</p>
    <p class="highlight important">這段同時使用兩個 class。</p>
</body>
</html>
```

## 🔗 組合選擇器

### 1. 群組選擇器（Group Selector）

用逗號分隔，同時選擇多個元素：

```css
h1, h2, h3 {
    color: #333;
    font-family: Arial;
}

.button, .link, .nav-item {
    text-decoration: none;
}
```

### 2. 後代選擇器（Descendant Selector）

用空格分隔，選擇某元素內的所有後代：

```css
div p {
    color: blue;
}

.container a {
    color: red;
}
```

```html
<div>
    <p>會被選中</p>
    <article>
        <p>也會被選中（所有後代）</p>
    </article>
</div>
```

### 3. 子選擇器（Child Selector）

用 `>` 選擇直接子元素：

```css
div > p {
    color: blue;
}
```

```html
<div>
    <p>會被選中（直接子元素）</p>
    <article>
        <p>不會被選中（孫元素）</p>
    </article>
</div>
```

### 4. 相鄰兄弟選擇器（Adjacent Sibling）

用 `+` 選擇緊接在後的兄弟元素：

```css
h1 + p {
    font-size: 20px;
    font-weight: bold;
}
```

```html
<h1>標題</h1>
<p>會被選中（緊接在 h1 後）</p>
<p>不會被選中</p>
```

### 5. 通用兄弟選擇器（General Sibling）

用 `~` 選擇後面所有的兄弟元素：

```css
h1 ~ p {
    color: gray;
}
```

```html
<h1>標題</h1>
<p>會被選中</p>
<div>其他內容</div>
<p>也會被選中</p>
```

## 🎭 偽類選擇器（Pseudo-class）

偽類用來選擇元素的特定狀態：

### 1. 連結偽類

```css
/* 未訪問的連結 */
a:link {
    color: blue;
}

/* 已訪問的連結 */
a:visited {
    color: purple;
}

/* 滑鼠懸停 */
a:hover {
    color: red;
    text-decoration: underline;
}

/* 點擊時 */
a:active {
    color: orange;
}
```

### 2. 常用偽類

```css
/* 第一個子元素 */
p:first-child {
    font-weight: bold;
}

/* 最後一個子元素 */
p:last-child {
    margin-bottom: 0;
}

/* 第 n 個子元素 */
li:nth-child(2) {
    color: red;
}

/* 奇數項 */
tr:nth-child(odd) {
    background-color: #f9f9f9;
}

/* 偶數項 */
tr:nth-child(even) {
    background-color: #fff;
}

/* 獲得焦點時 */
input:focus {
    border-color: blue;
    outline: none;
}

/* 被勾選時 */
input:checked + label {
    color: green;
}

/* 停用狀態 */
input:disabled {
    opacity: 0.5;
}
```

## 💻 實作練習 2：偽類應用

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>偽類選擇器示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 50px auto;
            padding: 20px;
        }
        
        /* 連結樣式 */
        a {
            text-decoration: none;
            padding: 5px 10px;
            border-radius: 3px;
            transition: all 0.3s;
        }
        
        a:link {
            color: #667eea;
            background-color: transparent;
        }
        
        a:visited {
            color: #764ba2;
        }
        
        a:hover {
            background-color: #667eea;
            color: white;
        }
        
        a:active {
            background-color: #5568d3;
        }
        
        /* 表格斑馬條紋 */
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        
        th, td {
            padding: 12px;
            text-align: left;
            border: 1px solid #ddd;
        }
        
        th {
            background-color: #667eea;
            color: white;
        }
        
        tr:nth-child(odd) {
            background-color: #f9f9f9;
        }
        
        tr:nth-child(even) {
            background-color: white;
        }
        
        tr:hover {
            background-color: #E8F8F5;
        }
        
        /* 表單樣式 */
        input[type="text"] {
            padding: 10px;
            border: 2px solid #ddd;
            border-radius: 5px;
            width: 300px;
        }
        
        input[type="text"]:focus {
            border-color: #667eea;
            outline: none;
            box-shadow: 0 0 5px rgba(102, 126, 234, 0.3);
        }
        
        /* 列表樣式 */
        ul {
            list-style: none;
            padding: 0;
        }
        
        li {
            padding: 10px;
            margin: 5px 0;
            background-color: #f5f5f5;
            border-radius: 5px;
        }
        
        li:first-child {
            background-color: #FFE66D;
            font-weight: bold;
        }
        
        li:last-child {
            background-color: #95E1D3;
        }
    </style>
</head>
<body>
    <h1>偽類選擇器示範</h1>
    
    <h2>連結狀態</h2>
    <p>
        <a href="https://www.google.com">未訪問的連結</a> |
        <a href="#">試試 hover 效果</a>
    </p>
    
    <h2>表格斑馬條紋</h2>
    <table>
        <thead>
            <tr>
                <th>姓名</th>
                <th>年齡</th>
                <th>城市</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>張三</td>
                <td>25</td>
                <td>台北</td>
            </tr>
            <tr>
                <td>李四</td>
                <td>30</td>
                <td>台中</td>
            </tr>
            <tr>
                <td>王五</td>
                <td>28</td>
                <td>高雄</td>
            </tr>
            <tr>
                <td>趙六</td>
                <td>32</td>
                <td>台南</td>
            </tr>
        </tbody>
    </table>
    
    <h2>輸入框焦點</h2>
    <input type="text" placeholder="點擊我試試">
    
    <h2>列表項目</h2>
    <ul>
        <li>第一項（特殊樣式）</li>
        <li>第二項</li>
        <li>第三項</li>
        <li>最後一項（特殊樣式）</li>
    </ul>
</body>
</html>
```

## 🎨 偽元素選擇器（Pseudo-element）

偽元素用來選擇元素的特定部分：

```css
/* 第一行 */
p::first-line {
    font-weight: bold;
    color: blue;
}

/* 第一個字母 */
p::first-letter {
    font-size: 32px;
    color: red;
}

/* 在元素前插入內容 */
h2::before {
    content: "★ ";
    color: gold;
}

/* 在元素後插入內容 */
h2::after {
    content: " ★";
    color: gold;
}

/* 選取的文字 */
::selection {
    background-color: yellow;
    color: black;
}
```

## 🏆 選擇器特異性（Specificity）

當多個選擇器套用到同一元素時，特異性決定哪個樣式會生效。

### 特異性權重

從高到低：

1. **內嵌樣式**（style 屬性）：1000
2. **ID 選擇器**：100
3. **類別、屬性、偽類**：10
4. **元素、偽元素**：1

### 計算範例

```css
/* 特異性：1 */
p { color: blue; }

/* 特異性：10 */
.highlight { color: red; }

/* 特異性：100 */
#intro { color: green; }

/* 特異性：11 (10 + 1) */
.highlight p { color: orange; }

/* 特異性：101 (100 + 1) */
#intro p { color: purple; }

/* 特異性：111 (100 + 10 + 1) */
#intro .highlight p { color: pink; }
```

### 優先權規則

1. **特異性高的優先**
2. **特異性相同，後面的優先**
3. **!important 最優先**（不建議使用）

```css
p {
    color: blue;
}

p {
    color: red;  /* 會生效（後面覆蓋前面） */
}

.highlight {
    color: green !important;  /* 最優先 */
}
```

## 📋 屬性選擇器

根據屬性選擇元素：

```css
/* 有 title 屬性的元素 */
[title] {
    cursor: help;
}

/* title 等於 "hello" */
[title="hello"] {
    color: blue;
}

/* class 包含 "btn" */
[class*="btn"] {
    padding: 10px;
}

/* href 開頭是 "https" */
[href^="https"] {
    color: green;
}

/* href 結尾是 ".pdf" */
[href$=".pdf"]::after {
    content: " (PDF)";
}

/* type 是 "text" 的 input */
input[type="text"] {
    border: 2px solid blue;
}
```

## 💻 實作練習 3：選擇器綜合應用

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>選擇器綜合練習</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            line-height: 1.6;
            padding: 40px;
            background-color: #f5f5f5;
        }
        
        .container {
            max-width: 900px;
            margin: 0 auto;
            background-color: white;
            padding: 40px;
            border-radius: 10px;
            box-shadow: 0 5px 20px rgba(0,0,0,0.1);
        }
        
        h1 {
            color: #667eea;
            text-align: center;
            margin-bottom: 30px;
        }
        
        h1::before {
            content: "🎯 ";
        }
        
        h2 {
            color: #764ba2;
            margin: 30px 0 15px;
            padding-left: 15px;
            border-left: 5px solid #667eea;
        }
        
        /* 連結樣式 */
        a {
            color: #667eea;
            text-decoration: none;
            transition: color 0.3s;
        }
        
        a:hover {
            color: #764ba2;
            text-decoration: underline;
        }
        
        a[href^="https"]::after {
            content: " 🔗";
        }
        
        /* 段落樣式 */
        p::first-letter {
            font-size: 1.5em;
            font-weight: bold;
            color: #667eea;
        }
        
        /* 列表樣式 */
        ul {
            list-style: none;
        }
        
        li {
            padding: 10px;
            margin: 5px 0;
            background-color: #f9f9f9;
            border-radius: 5px;
        }
        
        li::before {
            content: "✓ ";
            color: #4ECDC4;
            font-weight: bold;
        }
        
        li:hover {
            background-color: #E8F8F5;
            transform: translateX(5px);
            transition: all 0.3s;
        }
        
        /* 表單樣式 */
        input[type="text"],
        input[type="email"] {
            width: 100%;
            padding: 12px;
            margin: 10px 0;
            border: 2px solid #ddd;
            border-radius: 5px;
            font-size: 16px;
        }
        
        input:focus {
            border-color: #667eea;
            outline: none;
            box-shadow: 0 0 10px rgba(102, 126, 234, 0.2);
        }
        
        button {
            background-color: #667eea;
            color: white;
            padding: 12px 30px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }
        
        button:hover {
            background-color: #5568d3;
        }
        
        /* 選取文字的樣式 */
        ::selection {
            background-color: #FFE66D;
            color: #333;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>CSS 選擇器綜合示範</h1>
        
        <h2>段落和連結</h2>
        <p>
            這是一段示範文字，第一個字母會有特殊樣式。
            這裡有一個<a href="https://www.example.com">外部連結</a>，
            還有一個<a href="page.html">內部連結</a>。
        </p>
        
        <h2>清單項目</h2>
        <ul>
            <li>第一項：hover 試試看</li>
            <li>第二項：每項前面都有打勾符號</li>
            <li>第三項：使用了偽元素</li>
            <li>第四項：組合選擇器的應用</li>
        </ul>
        
        <h2>表單元素</h2>
        <form>
            <input type="text" placeholder="請輸入姓名">
            <input type="email" placeholder="請輸入電子郵件">
            <button type="submit">送出</button>
        </form>
        
        <h2>小提示</h2>
        <p style="background-color: #FFF4E6; padding: 15px; border-radius: 5px;">
            試著選取這些文字，看看選取樣式的變化！
        </p>
    </div>
</body>
</html>
```

## 📝 本課重點回顧

- ✅ 基本選擇器：元素、class、ID、通用
- ✅ 組合選擇器：群組、後代、子、相鄰、通用兄弟
- ✅ 偽類：:hover、:focus、:nth-child() 等
- ✅ 偽元素：::before、::after、::first-letter 等
- ✅ 特異性決定樣式優先權：內嵌 > ID > class > 元素
- ✅ 屬性選擇器：根據屬性選擇元素

## 🎯 課後練習

1. **基礎練習**：建立導覽列
   - 使用 class 選擇器設定樣式
   - 使用 :hover 加入懸停效果
   - 使用 ::after 在連結後加入圖示

2. **進階挑戰**：美化表格
   - 使用 :nth-child(odd) 和 :nth-child(even) 建立斑馬條紋
   - 使用 :hover 加入列的懸停效果
   - 使用 :first-child 和 :last-child 設定特殊樣式

3. **實戰練習**：建立登入表單
   - 使用各種選擇器設定樣式
   - 使用 :focus 改變輸入框焦點樣式
   - 使用偽元素加入圖示或提示
   - 確保特異性運用正確

## 🔗 下一課預告

在下一課中，我們將學習 CSS 盒模型，理解元素的尺寸、邊框、內距和外距如何運作！

---

[← 上一課：CSS 基礎介紹](./10-css-introduction.md) | [返回目錄](../README.md) | [下一課：盒模型和布局基礎 →](./12-box-model.md)
