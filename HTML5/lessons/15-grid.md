# 第 15 課：Grid 布局

## 📚 本課學習目標

- 理解 CSS Grid 的概念
- 掌握 Grid 容器和項目屬性
- 學會建立複雜的網格布局
- 了解 Grid vs Flexbox 的使用時機

## 🎯 什麼是 CSS Grid？

**CSS Grid**是二維布局系統，可以同時控制行和列，非常適合建立複雜的網格布局。

### Grid vs Flexbox

| 特性 | Flexbox | Grid |
|------|---------|------|
| 維度 | 一維（行或列） | 二維（行和列） |
| 適用 | 元件內部排列 | 整體頁面布局 |
| 靈活性 | 內容優先 | 布局優先 |

## 🏗️ Grid 基本概念

```html
<div class="grid-container">
    <div class="grid-item">1</div>
    <div class="grid-item">2</div>
    <div class="grid-item">3</div>
</div>
```

```css
.grid-container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr;
    grid-template-rows: 100px 100px;
    gap: 10px;
}
```

### Grid 術語

- **Grid Container**：網格容器
- **Grid Item**：網格項目
- **Grid Line**：網格線
- **Grid Track**：網格軌道（行或列）
- **Grid Cell**：網格儲存格
- **Grid Area**：網格區域

## 📦 Grid 容器屬性

### 1. grid-template-columns/rows

定義列和行的大小：

```css
.grid {
    display: grid;
    
    /* 固定寬度 */
    grid-template-columns: 200px 200px 200px;
    
    /* 百分比 */
    grid-template-columns: 25% 50% 25%;
    
    /* fr 單位（fraction，份數） */
    grid-template-columns: 1fr 2fr 1fr;
    
    /* 混合使用 */
    grid-template-columns: 200px 1fr 2fr;
    
    /* repeat() 函數 */
    grid-template-columns: repeat(3, 1fr);
    
    /* auto-fill 自動填滿 */
    grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
}
```

### 2. gap（間距）

```css
.grid {
    gap: 20px;              /* 行列間距相同 */
    row-gap: 15px;          /* 行間距 */
    column-gap: 25px;       /* 列間距 */
    gap: 15px 25px;         /* 行 列 */
}
```

### 3. grid-template-areas（命名區域）

```css
.grid {
    display: grid;
    grid-template-columns: 1fr 2fr 1fr;
    grid-template-rows: auto 1fr auto;
    grid-template-areas:
        "header header header"
        "sidebar main aside"
        "footer footer footer";
}

.header { grid-area: header; }
.sidebar { grid-area: sidebar; }
.main { grid-area: main; }
.aside { grid-area: aside; }
.footer { grid-area: footer; }
```

### 4. justify-items & align-items

```css
.grid {
    /* 水平對齊 */
    justify-items: start | end | center | stretch;
    
    /* 垂直對齊 */
    align-items: start | end | center | stretch;
    
    /* 簡寫 */
    place-items: center;  /* 水平垂直都置中 */
}
```

### 5. justify-content & align-content

```css
.grid {
    /* 整個網格在容器中的對齊 */
    justify-content: start | end | center | stretch;
    align-content: start | end | center | stretch;
}
```

## 💻 實作練習 1：Grid 基礎

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS Grid 基礎</title>
    <style>
        * {
            box-sizing: border-box;
        }
        
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        h1 {
            text-align: center;
            color: #667eea;
        }
        
        h2 {
            color: #764ba2;
            margin: 30px 0 15px;
        }
        
        .grid {
            display: grid;
            background-color: #E8F8F5;
            padding: 20px;
            border-radius: 10px;
            margin: 20px 0;
        }
        
        .grid-item {
            background-color: #4ECDC4;
            color: white;
            padding: 20px;
            border-radius: 5px;
            text-align: center;
            font-weight: bold;
        }
        
        /* 範例 1：固定列寬 */
        .grid-1 {
            grid-template-columns: 200px 200px 200px;
            gap: 10px;
        }
        
        /* 範例 2：fr 單位 */
        .grid-2 {
            grid-template-columns: 1fr 2fr 1fr;
            gap: 10px;
        }
        
        /* 範例 3：repeat */
        .grid-3 {
            grid-template-columns: repeat(4, 1fr);
            gap: 10px;
        }
        
        /* 範例 4：auto-fill */
        .grid-4 {
            grid-template-columns: repeat(auto-fill, minmax(150px, 1fr));
            gap: 10px;
        }
        
        /* 範例 5：對齊 */
        .grid-5 {
            grid-template-columns: repeat(3, 150px);
            grid-template-rows: repeat(2, 100px);
            gap: 10px;
            justify-content: center;
            align-items: center;
        }
        
        .code {
            background-color: #333;
            color: #FFE66D;
            padding: 5px 10px;
            border-radius: 3px;
            font-family: monospace;
            display: inline-block;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎯 CSS Grid 基礎示範</h1>
        
        <h2>範例 1：固定列寬</h2>
        <p class="code">grid-template-columns: 200px 200px 200px;</p>
        <div class="grid grid-1">
            <div class="grid-item">1</div>
            <div class="grid-item">2</div>
            <div class="grid-item">3</div>
        </div>
        
        <h2>範例 2：fr 單位（彈性比例）</h2>
        <p class="code">grid-template-columns: 1fr 2fr 1fr;</p>
        <div class="grid grid-2">
            <div class="grid-item">1fr</div>
            <div class="grid-item">2fr（兩倍寬）</div>
            <div class="grid-item">1fr</div>
        </div>
        
        <h2>範例 3：repeat() 函數</h2>
        <p class="code">grid-template-columns: repeat(4, 1fr);</p>
        <div class="grid grid-3">
            <div class="grid-item">1</div>
            <div class="grid-item">2</div>
            <div class="grid-item">3</div>
            <div class="grid-item">4</div>
        </div>
        
        <h2>範例 4：auto-fill（自動填滿）</h2>
        <p class="code">grid-template-columns: repeat(auto-fill, minmax(150px, 1fr));</p>
        <div class="grid grid-4">
            <div class="grid-item">1</div>
            <div class="grid-item">2</div>
            <div class="grid-item">3</div>
            <div class="grid-item">4</div>
            <div class="grid-item">5</div>
            <div class="grid-item">6</div>
        </div>
        
        <h2>範例 5：置中對齊</h2>
        <p class="code">justify-content: center; align-items: center;</p>
        <div class="grid grid-5" style="height: 300px;">
            <div class="grid-item">1</div>
            <div class="grid-item">2</div>
            <div class="grid-item">3</div>
        </div>
    </div>
</body>
</html>
```

## 🎨 Grid 項目屬性

### 1. grid-column & grid-row

指定項目跨越的格子：

```css
.item-1 {
    grid-column: 1 / 3;  /* 從第 1 條線到第 3 條線 */
    grid-row: 1 / 2;
}

.item-2 {
    grid-column: span 2;  /* 跨越 2 列 */
    grid-row: span 3;     /* 跨越 3 行 */
}

/* 簡寫 */
.item-3 {
    grid-area: 1 / 1 / 3 / 3;  /* row-start / col-start / row-end / col-end */
}
```

### 2. justify-self & align-self

個別項目的對齊：

```css
.item {
    justify-self: start | end | center | stretch;
    align-self: start | end | center | stretch;
    place-self: center;  /* 簡寫 */
}
```

## 💻 實作練習 2：Grid Template Areas

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Grid Template Areas</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            height: 100vh;
        }
        
        .grid-container {
            display: grid;
            grid-template-columns: 200px 1fr 200px;
            grid-template-rows: auto 1fr auto;
            grid-template-areas:
                "header header header"
                "sidebar main aside"
                "footer footer footer";
            height: 100vh;
            gap: 10px;
            padding: 10px;
        }
        
        .header {
            grid-area: header;
            background-color: #667eea;
            color: white;
            padding: 20px;
            text-align: center;
        }
        
        .sidebar {
            grid-area: sidebar;
            background-color: #4ECDC4;
            padding: 20px;
        }
        
        .main {
            grid-area: main;
            background-color: #FFE66D;
            padding: 20px;
        }
        
        .aside {
            grid-area: aside;
            background-color: #95E1D3;
            padding: 20px;
        }
        
        .footer {
            grid-area: footer;
            background-color: #333;
            color: white;
            padding: 20px;
            text-align: center;
        }
        
        h2 {
            margin-bottom: 15px;
        }
    </style>
</head>
<body>
    <div class="grid-container">
        <header class="header">
            <h1>網站標題</h1>
        </header>
        
        <aside class="sidebar">
            <h2>側邊欄</h2>
            <ul>
                <li>選單 1</li>
                <li>選單 2</li>
                <li>選單 3</li>
            </ul>
        </aside>
        
        <main class="main">
            <h2>主要內容區</h2>
            <p>這是主要內容區域，使用 Grid Template Areas 建立的布局。</p>
        </main>
        
        <aside class="aside">
            <h2>側邊資訊</h2>
            <p>廣告或相關資訊</p>
        </aside>
        
        <footer class="footer">
            <p>&copy; 2026 版權所有</p>
        </footer>
    </div>
</body>
</html>
```

## 💻 實作練習 3：響應式 Grid 布局

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>響應式 Grid 布局</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            background-color: #f5f5f5;
            padding: 20px;
        }
        
        .container {
            max-width: 1400px;
            margin: 0 auto;
        }
        
        h1 {
            text-align: center;
            color: #667eea;
            margin-bottom: 40px;
        }
        
        /* 產品網格 */
        .product-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));
            gap: 25px;
        }
        
        .product-card {
            background-color: white;
            border-radius: 15px;
            overflow: hidden;
            box-shadow: 0 5px 20px rgba(0,0,0,0.1);
            transition: transform 0.3s;
        }
        
        .product-card:hover {
            transform: translateY(-10px);
        }
        
        .product-image {
            height: 200px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-size: 48px;
        }
        
        .product-content {
            padding: 20px;
        }
        
        .product-title {
            color: #333;
            font-size: 20px;
            margin-bottom: 10px;
        }
        
        .product-price {
            color: #667eea;
            font-size: 24px;
            font-weight: bold;
            margin-bottom: 15px;
        }
        
        .product-description {
            color: #666;
            line-height: 1.6;
            margin-bottom: 15px;
        }
        
        .btn {
            display: block;
            width: 100%;
            padding: 12px;
            background-color: #667eea;
            color: white;
            text-align: center;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        
        .btn:hover {
            background-color: #5568d3;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🛍️ 產品展示頁面</h1>
        
        <div class="product-grid">
            <div class="product-card">
                <div class="product-image">📱</div>
                <div class="product-content">
                    <h3 class="product-title">智慧型手機</h3>
                    <p class="product-price">$15,000</p>
                    <p class="product-description">
                        最新款智慧型手機，功能強大，
                        性能卓越，拍照清晰。
                    </p>
                    <button class="btn">加入購物車</button>
                </div>
            </div>
            
            <div class="product-card">
                <div class="product-image">💻</div>
                <div class="product-content">
                    <h3 class="product-title">筆記型電腦</h3>
                    <p class="product-price">$30,000</p>
                    <p class="product-description">
                        輕薄便攜，高效能處理器，
                        適合工作和娛樂。
                    </p>
                    <button class="btn">加入購物車</button>
                </div>
            </div>
            
            <div class="product-card">
                <div class="product-image">⌚</div>
                <div class="product-content">
                    <h3 class="product-title">智慧手錶</h3>
                    <p class="product-price">$8,000</p>
                    <p class="product-description">
                        健康監測、運動追蹤、
                        來電提醒，一錶多用。
                    </p>
                    <button class="btn">加入購物車</button>
                </div>
            </div>
            
            <div class="product-card">
                <div class="product-image">🎧</div>
                <div class="product-content">
                    <h3 class="product-title">藍牙耳機</h3>
                    <p class="product-price">$3,000</p>
                    <p class="product-description">
                        主動降噪、高音質、
                        長續航力，音樂享受。
                    </p>
                    <button class="btn">加入購物車</button>
                </div>
            </div>
            
            <div class="product-card">
                <div class="product-image">📷</div>
                <div class="product-content">
                    <h3 class="product-title">數位相機</h3>
                    <p class="product-price">$25,000</p>
                    <p class="product-description">
                        專業級畫質、4K錄影、
                        捕捉每個精彩瞬間。
                    </p>
                    <button class="btn">加入購物車</button>
                </div>
            </div>
            
            <div class="product-card">
                <div class="product-image">🖱️</div>
                <div class="product-content">
                    <h3 class="product-title">無線滑鼠</h3>
                    <p class="product-price">$800</p>
                    <p class="product-description">
                        人體工學設計、精準定位、
                        無線連接更自由。
                    </p>
                    <button class="btn">加入購物車</button>
                </div>
            </div>
        </div>
    </div>
</body>
</html>
```

## 🎯 Grid 實用技巧

### 1. 完美的響應式布局

```css
.grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
    gap: 20px;
}
```

### 2. 聖杯布局

```css
.layout {
    display: grid;
    grid-template-areas:
        "header header header"
        "nav main aside"
        "footer footer footer";
    grid-template-columns: 200px 1fr 200px;
    grid-template-rows: auto 1fr auto;
    height: 100vh;
}
```

### 3. 圖片畫廊

```css
.gallery {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
    grid-auto-rows: 200px;
    gap: 10px;
}

.gallery-item:nth-child(3n) {
    grid-column: span 2;
    grid-row: span 2;
}
```

## 📝 本課重點回顧

- ✅ CSS Grid 是二維布局系統
- ✅ grid-template-columns/rows 定義網格結構
- ✅ fr 單位表示彈性比例
- ✅ repeat() 函數簡化重複定義
- ✅ auto-fill/auto-fit 實現響應式布局
- ✅ grid-template-areas 命名區域布局
- ✅ gap 設定網格間距
- ✅ Grid 適合頁面整體布局，Flexbox 適合元件內部排列

## 🎯 課後練習

1. **基礎練習**：建立照片牆
   - 使用 Grid 建立 3x3 的照片牆
   - 設定適當的間距
   - 所有照片等寬等高

2. **進階挑戰**：建立部落格首頁
   - 使用 grid-template-areas
   - 包含：header、sidebar、main、footer
   - sidebar 固定寬度，main 自動填滿

3. **實戰練習**：建立產品展示頁
   - 使用 auto-fill 實現響應式
   - 至少 8 個產品卡片
   - 卡片包含圖片、標題、價格、按鈕
   - 加入 hover 效果

## 🔗 下一課預告

在下一課中，我們將學習響應式設計，讓網頁在不同裝置上都能完美呈現！

---

[← 上一課：Flexbox 布局](./14-flexbox.md) | [返回目錄](../README.md) | [下一課：響應式設計 →](./16-responsive-design.md)
