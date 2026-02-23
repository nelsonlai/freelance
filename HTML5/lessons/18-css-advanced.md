# 第 18 課：CSS 進階技巧

## 📚 本課學習目標

- 掌握 CSS 變數的使用
- 學會 CSS 函數
- 了解進階選擇器
- 掌握實用的 CSS 技巧

## 🎨 CSS 變數（Custom Properties）

CSS 變數讓我們可以重複使用值，方便維護和主題切換。

### 定義和使用變數

```css
:root {
    /* 定義變數 */
    --primary-color: #667eea;
    --secondary-color: #764ba2;
    --spacing: 20px;
    --border-radius: 10px;
}

.button {
    /* 使用變數 */
    background-color: var(--primary-color);
    padding: var(--spacing);
    border-radius: var(--border-radius);
}

/* 預設值 */
.element {
    color: var(--text-color, #333);  /* 如果變數不存在，使用 #333 */
}
```

### 變數作用域

```css
:root {
    --color: blue;  /* 全域變數 */
}

.container {
    --color: red;   /* 區域變數，只在 .container 內有效 */
}

.element {
    color: var(--color);
}
```

## 💻 實作練習 1：主題切換

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 變數示範</title>
    <style>
        :root {
            --bg-primary: #ffffff;
            --bg-secondary: #f5f5f5;
            --text-primary: #333333;
            --text-secondary: #666666;
            --accent-color: #667eea;
            --border-color: #dddddd;
        }
        
        [data-theme="dark"] {
            --bg-primary: #1a1a1a;
            --bg-secondary: #2d2d2d;
            --text-primary: #ffffff;
            --text-secondary: #cccccc;
            --accent-color: #4ECDC4;
            --border-color: #444444;
        }
        
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            background-color: var(--bg-primary);
            color: var(--text-primary);
            transition: all 0.3s ease;
            padding: 40px;
        }
        
        .container {
            max-width: 1000px;
            margin: 0 auto;
        }
        
        h1 {
            text-align: center;
            color: var(--accent-color);
            margin-bottom: 30px;
        }
        
        .theme-switcher {
            text-align: center;
            margin-bottom: 40px;
        }
        
        .theme-btn {
            padding: 12px 30px;
            background-color: var(--accent-color);
            color: white;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            font-size: 16px;
            margin: 0 10px;
            transition: opacity 0.3s;
        }
        
        .theme-btn:hover {
            opacity: 0.8;
        }
        
        .card {
            background-color: var(--bg-secondary);
            border: 1px solid var(--border-color);
            border-radius: 10px;
            padding: 30px;
            margin-bottom: 20px;
        }
        
        .card h2 {
            color: var(--text-primary);
            margin-bottom: 15px;
        }
        
        .card p {
            color: var(--text-secondary);
            line-height: 1.6;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎨 CSS 變數主題切換</h1>
        
        <div class="theme-switcher">
            <button class="theme-btn" onclick="setTheme('light')">☀️ 淺色主題</button>
            <button class="theme-btn" onclick="setTheme('dark')">🌙 深色主題</button>
        </div>
        
        <div class="card">
            <h2>什麼是 CSS 變數？</h2>
            <p>
                CSS 變數（Custom Properties）讓我們可以在 CSS 中定義可重複使用的值。
                這使得主題切換、樣式維護變得更加容易。
            </p>
        </div>
        
        <div class="card">
            <h2>為什麼要使用 CSS 變數？</h2>
            <p>
                使用 CSS 變數可以提高代碼的可維護性，
                讓我們輕鬆實現主題切換、響應式設計等功能。
            </p>
        </div>
        
        <div class="card">
            <h2>如何使用 CSS 變數？</h2>
            <p>
                在 :root 中定義全域變數，然後使用 var() 函數來引用它們。
                也可以在特定選擇器中定義區域變數。
            </p>
        </div>
    </div>
    
    <script>
        function setTheme(theme) {
            if (theme === 'dark') {
                document.body.setAttribute('data-theme', 'dark');
            } else {
                document.body.removeAttribute('data-theme');
            }
        }
    </script>
</body>
</html>
```

## 🔢 CSS 函數

### 1. calc()（計算）

```css
.element {
    width: calc(100% - 50px);
    height: calc(100vh - 80px);
    padding: calc(1rem + 5px);
    font-size: calc(16px + 1vw);
}
```

### 2. min()、max()、clamp()

```css
/* min()：取最小值 */
.element {
    width: min(500px, 100%);  /* 最大不超過 500px */
}

/* max()：取最大值 */
.element {
    width: max(300px, 50%);   /* 最小不低於 300px */
}

/* clamp()：限制範圍 */
.element {
    font-size: clamp(16px, 2vw, 24px);  /* 最小 16px，最大 24px */
    width: clamp(300px, 50%, 800px);
}
```

### 3. 漸層函數

```css
/* 線性漸層 */
background: linear-gradient(45deg, #667eea, #764ba2);

/* 放射漸層 */
background: radial-gradient(circle, #4ECDC4, #38A3A5);

/* 錐形漸層 */
background: conic-gradient(from 90deg, red, yellow, green, blue, red);
```

## 🎯 進階選擇器

### :not()（排除）

```css
/* 選擇所有 div，但排除 .special */
div:not(.special) {
    color: blue;
}

/* 排除第一個和最後一個 */
li:not(:first-child):not(:last-child) {
    border-top: 1px solid #ddd;
}
```

### :is()（匹配）

```css
/* 簡化多個選擇器 */
:is(h1, h2, h3) {
    color: #667eea;
}

/* 等同於 */
h1, h2, h3 {
    color: #667eea;
}
```

### :where()（零特異性）

```css
/* 與 :is() 類似，但特異性為 0 */
:where(h1, h2, h3) {
    color: #667eea;
}
```

### :has()（父選擇器）

```css
/* 如果 div 包含 img，套用樣式 */
div:has(img) {
    border: 2px solid blue;
}

/* 如果表單包含錯誤輸入 */
form:has(input:invalid) {
    border-color: red;
}
```

## 💻 實作練習 2：進階技巧綜合

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 進階技巧</title>
    <style>
        :root {
            --primary: #667eea;
            --secondary: #764ba2;
            --spacing: 20px;
        }
        
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            padding: 40px;
            background-color: #f5f5f5;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        h1 {
            text-align: center;
            background: linear-gradient(135deg, var(--primary), var(--secondary));
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            margin-bottom: 40px;
        }
        
        /* 使用 calc() */
        .section {
            width: calc(100% - 40px);
            margin: var(--spacing) auto;
            padding: var(--spacing);
            background-color: white;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        /* 使用 clamp() 實現響應式字體 */
        .section h2 {
            font-size: clamp(20px, 3vw, 32px);
            color: var(--primary);
            margin-bottom: 15px;
        }
        
        /* Grid with auto-fit */
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: var(--spacing);
            margin: var(--spacing) 0;
        }
        
        .card {
            background: linear-gradient(135deg, #4ECDC4 0%, #95E1D3 100%);
            color: white;
            padding: var(--spacing);
            border-radius: 10px;
            transition: transform 0.3s;
        }
        
        .card:hover {
            transform: translateY(-5px) scale(1.02);
        }
        
        /* 使用 :not() */
        .list li:not(:last-child) {
            border-bottom: 1px solid #ddd;
            padding-bottom: 10px;
            margin-bottom: 10px;
        }
        
        /* 使用 :is() */
        :is(h2, h3, h4) {
            font-weight: bold;
        }
        
        /* Aspect ratio */
        .aspect-box {
            aspect-ratio: 16 / 9;
            background: linear-gradient(45deg, var(--primary), var(--secondary));
            border-radius: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 24px;
        }
        
        /* Custom scrollbar */
        .scrollable::-webkit-scrollbar {
            width: 10px;
        }
        
        .scrollable::-webkit-scrollbar-track {
            background: #f1f1f1;
            border-radius: 10px;
        }
        
        .scrollable::-webkit-scrollbar-thumb {
            background: var(--primary);
            border-radius: 10px;
        }
        
        .scrollable {
            height: 200px;
            overflow-y: auto;
            padding: 15px;
            background-color: #f9f9f9;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🚀 CSS 進階技巧示範</h1>
        
        <div class="section">
            <h2>calc() 函數應用</h2>
            <p>這個區塊的寬度是 calc(100% - 40px)，使用 calc() 可以進行數學計算。</p>
        </div>
        
        <div class="section">
            <h2>clamp() 響應式字體</h2>
            <p>這個標題使用 clamp(20px, 3vw, 32px)，會隨視窗大小自動調整，但有最小和最大限制。</p>
        </div>
        
        <div class="section">
            <h2>Grid Auto-fit</h2>
            <div class="grid">
                <div class="card">卡片 1</div>
                <div class="card">卡片 2</div>
                <div class="card">卡片 3</div>
            </div>
        </div>
        
        <div class="section">
            <h2>Aspect Ratio</h2>
            <div class="aspect-box">
                16:9 比例
            </div>
        </div>
        
        <div class="section">
            <h2>:not() 選擇器</h2>
            <ul class="list">
                <li>項目 1</li>
                <li>項目 2</li>
                <li>項目 3（最後一項沒有底線）</li>
            </ul>
        </div>
        
        <div class="section">
            <h2>客製化捲軸</h2>
            <div class="scrollable">
                <p>這是一個有客製化捲軸的區域。</p>
                <p>內容重複多次以顯示捲軸效果。</p>
                <p>內容重複多次以顯示捲軸效果。</p>
                <p>內容重複多次以顯示捲軸效果。</p>
                <p>內容重複多次以顯示捲軸效果。</p>
                <p>內容重複多次以顯示捲軸效果。</p>
                <p>內容重複多次以顯示捲軸效果。</p>
            </div>
        </div>
    </div>
</body>
</html>
```

## 🎯 實用技巧

### 1. 平滑捲動

```css
html {
    scroll-behavior: smooth;
}
```

### 2. 文字選取顏色

```css
::selection {
    background-color: #667eea;
    color: white;
}
```

### 3. 物件填滿方式

```css
img {
    object-fit: cover;       /* 覆蓋 */
    object-fit: contain;     /* 包含 */
    object-fit: fill;        /* 填滿 */
    object-position: center; /* 位置 */
}
```

### 4. 長寬比

```css
.video-container {
    aspect-ratio: 16 / 9;
}
```

### 5. 捲動吸附

```css
.container {
    scroll-snap-type: y mandatory;
}

.section {
    scroll-snap-align: start;
}
```

### 6. 玻璃效果

```css
.glass {
    background: rgba(255, 255, 255, 0.1);
    backdrop-filter: blur(10px);
    border: 1px solid rgba(255, 255, 255, 0.2);
}
```

## 🎨 CSS 最佳實踐

### 1. 命名規範

```css
/* BEM 命名法 */
.block__element--modifier { }

/* 範例 */
.card { }
.card__title { }
.card__title--large { }
```

### 2. 組織結構

```css
/* 1. 變數 */
:root {
    --primary-color: #667eea;
}

/* 2. 重置樣式 */
* {
    box-sizing: border-box;
}

/* 3. 基本樣式 */
body {
    font-family: Arial;
}

/* 4. 布局 */
.container { }

/* 5. 元件 */
.button { }

/* 6. 工具類 */
.mt-20 { margin-top: 20px; }
```

### 3. 效能優化

```css
/* 使用 transform 而非 position */
.element {
    transform: translateX(100px);  /* 好 */
    /* left: 100px; */              /* 較差 */
}

/* 使用 will-change 提示瀏覽器 */
.animated {
    will-change: transform;
}

/* 避免過度使用陰影和漸層 */
```

## 📝 本課重點回顧

- ✅ CSS 變數提高代碼可維護性
- ✅ calc()、clamp() 實現動態計算
- ✅ :not()、:is()、:has() 進階選擇器
- ✅ aspect-ratio 控制長寬比
- ✅ object-fit 控制圖片填滿方式
- ✅ backdrop-filter 建立模糊效果
- ✅ 使用 BEM 命名規範

## 🎉 CSS 部分完成！

恭喜！您已經完成了 CSS 部分的所有課程。現在您已經掌握了：

- ✅ CSS 基礎語法和選擇器
- ✅ 盒模型和布局
- ✅ Flexbox 和 Grid
- ✅ 響應式設計
- ✅ 動畫和過渡
- ✅ 進階技巧和最佳實踐

接下來，我們將進入 **JavaScript 部分**，學習如何為網頁加入互動功能！

## 🎯 課後練習

1. **基礎練習**：使用 CSS 變數建立主題
   - 定義淺色和深色主題
   - 使用 JavaScript 切換主題
   - 至少 5 個變數

2. **進階挑戰**：建立玻璃效果卡片
   - 使用 backdrop-filter
   - 加入動畫效果
   - 響應式設計

3. **實戰練習**：整合所有技巧
   - 建立一個完整的作品集網站
   - 使用 CSS 變數、Flexbox/Grid
   - 響應式設計、動畫效果
   - 運用本課學到的所有進階技巧

## 🔗 下一課預告

在下一課中，我們將開始學習 JavaScript，了解變數、資料型別等程式設計的基礎概念！

---

[← 上一課：CSS 動畫和過渡](./17-animations-transitions.md) | [返回目錄](../README.md) | [下一課：JavaScript 基礎介紹 →](./19-javascript-introduction.md)
