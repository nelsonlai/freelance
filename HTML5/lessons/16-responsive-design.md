# 第 16 課：響應式設計

## 📚 本課學習目標

- 理解響應式設計的概念和重要性
- 掌握 Media Queries 的使用
- 學會響應式布局技巧
- 了解 Mobile First 設計原則

## 📱 什麼是響應式設計？

**響應式設計（Responsive Web Design）**讓網頁能夠自動適應不同裝置的螢幕尺寸，提供最佳的瀏覽體驗。

### 為什麼需要響應式設計？

- 📱 行動裝置使用率高
- 💻 螢幕尺寸多樣化
- 🎯 提升使用者體驗
- 🔍 改善 SEO 排名
- 💰 降低維護成本（一個網站適用所有裝置）

## 🎯 Viewport 設定

在 HTML 的 `<head>` 中加入 viewport meta 標籤：

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

**參數說明：**
- `width=device-width`：寬度等於裝置寬度
- `initial-scale=1.0`：初始縮放比例為 1
- `maximum-scale=1.0`：最大縮放比例（可選）
- `user-scalable=no`：禁止使用者縮放（不建議）

## 📐 Media Queries（媒體查詢）

Media Queries 讓我們能夠根據螢幕尺寸套用不同的 CSS 樣式。

### 基本語法

```css
/* 當螢幕寬度 <= 768px 時套用 */
@media (max-width: 768px) {
    body {
        font-size: 14px;
    }
}

/* 當螢幕寬度 >= 1200px 時套用 */
@media (min-width: 1200px) {
    .container {
        max-width: 1140px;
    }
}

/* 範圍查詢 */
@media (min-width: 768px) and (max-width: 1199px) {
    .sidebar {
        width: 250px;
    }
}
```

### 常用斷點（Breakpoints）

```css
/* 手機 */
@media (max-width: 575px) { }

/* 平板（直向） */
@media (min-width: 576px) and (max-width: 767px) { }

/* 平板（橫向） */
@media (min-width: 768px) and (max-width: 991px) { }

/* 桌機 */
@media (min-width: 992px) and (max-width: 1199px) { }

/* 大螢幕 */
@media (min-width: 1200px) { }
```

### 其他媒體特性

```css
/* 螢幕方向 */
@media (orientation: portrait) { }   /* 直向 */
@media (orientation: landscape) { }  /* 橫向 */

/* 解析度 */
@media (min-resolution: 2dppx) { }  /* Retina 螢幕 */

/* 深色模式 */
@media (prefers-color-scheme: dark) { }
```

## 💻 實作練習 1：基本響應式布局

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>響應式設計示範</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
        }
        
        /* 預設樣式（桌機） */
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        
        header {
            background-color: #667eea;
            color: white;
            padding: 30px;
            text-align: center;
        }
        
        nav {
            background-color: #764ba2;
            padding: 15px;
        }
        
        nav ul {
            list-style: none;
            display: flex;
            justify-content: center;
            gap: 30px;
        }
        
        nav a {
            color: white;
            text-decoration: none;
            font-size: 18px;
        }
        
        .content {
            display: grid;
            grid-template-columns: 2fr 1fr;
            gap: 30px;
            margin: 30px 0;
        }
        
        main {
            background-color: #f9f9f9;
            padding: 30px;
            border-radius: 10px;
        }
        
        aside {
            background-color: #E8F8F5;
            padding: 30px;
            border-radius: 10px;
        }
        
        footer {
            background-color: #333;
            color: white;
            text-align: center;
            padding: 20px;
        }
        
        /* 平板（<= 992px） */
        @media (max-width: 992px) {
            nav ul {
                gap: 20px;
            }
            
            nav a {
                font-size: 16px;
            }
            
            .content {
                grid-template-columns: 1fr;
            }
        }
        
        /* 手機（<= 768px） */
        @media (max-width: 768px) {
            header {
                padding: 20px;
            }
            
            header h1 {
                font-size: 24px;
            }
            
            nav ul {
                flex-direction: column;
                gap: 10px;
                text-align: center;
            }
            
            .container {
                padding: 10px;
            }
            
            main, aside {
                padding: 20px;
            }
        }
        
        /* 小手機（<= 480px） */
        @media (max-width: 480px) {
            header h1 {
                font-size: 20px;
            }
            
            nav a {
                font-size: 14px;
            }
        }
        
        .device-info {
            background-color: #FFE66D;
            padding: 15px;
            border-radius: 5px;
            margin: 20px 0;
            text-align: center;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1>響應式網站示範</h1>
            <p>調整瀏覽器視窗大小看看效果</p>
        </header>
        
        <nav>
            <ul>
                <li><a href="#">首頁</a></li>
                <li><a href="#">關於</a></li>
                <li><a href="#">服務</a></li>
                <li><a href="#">聯絡</a></li>
            </ul>
        </nav>
        
        <div class="device-info">
            💡 提示：試著調整瀏覽器視窗大小，觀察布局如何改變
        </div>
        
        <div class="content">
            <main>
                <h2>主要內容</h2>
                <p>這是主要內容區域。在桌機上，它會佔據較大的空間。</p>
                <p>在平板和手機上，布局會自動調整為單欄，提供更好的閱讀體驗。</p>
            </main>
            
            <aside>
                <h3>側邊欄</h3>
                <p>這是側邊欄內容。</p>
                <p>在手機上，它會移到主內容下方。</p>
            </aside>
        </div>
        
        <footer>
            <p>&copy; 2026 響應式網站 版權所有</p>
        </footer>
    </div>
</body>
</html>
```

## 🎯 響應式圖片

### 1. max-width 方法

```css
img {
    max-width: 100%;
    height: auto;
}
```

### 2. srcset 屬性

```html
<img src="small.jpg"
     srcset="small.jpg 400w,
             medium.jpg 800w,
             large.jpg 1200w"
     sizes="(max-width: 600px) 400px,
            (max-width: 1000px) 800px,
            1200px"
     alt="響應式圖片">
```

### 3. picture 元素

```html
<picture>
    <source media="(max-width: 600px)" srcset="mobile.jpg">
    <source media="(max-width: 1000px)" srcset="tablet.jpg">
    <img src="desktop.jpg" alt="響應式圖片">
</picture>
```

## 📱 Mobile First 設計

從行動裝置開始設計，再擴展到大螢幕：

```css
/* 預設（手機） */
.container {
    padding: 10px;
}

.grid {
    display: block;
}

/* 平板以上 */
@media (min-width: 768px) {
    .container {
        padding: 20px;
    }
    
    .grid {
        display: grid;
        grid-template-columns: repeat(2, 1fr);
    }
}

/* 桌機以上 */
@media (min-width: 1200px) {
    .container {
        padding: 30px;
        max-width: 1140px;
    }
    
    .grid {
        grid-template-columns: repeat(3, 1fr);
    }
}
```

## 💻 實作練習 2：完整響應式網站

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>完整響應式網站</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            line-height: 1.6;
        }
        
        /* Mobile First 設計 */
        
        /* 預設樣式（手機） */
        .container {
            padding: 15px;
        }
        
        header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 20px 15px;
            text-align: center;
        }
        
        header h1 {
            font-size: 24px;
            margin-bottom: 10px;
        }
        
        nav {
            background-color: #333;
        }
        
        .nav-toggle {
            display: block;
            background-color: #444;
            color: white;
            padding: 15px;
            text-align: center;
            cursor: pointer;
        }
        
        nav ul {
            list-style: none;
            display: none;
        }
        
        nav ul.active {
            display: block;
        }
        
        nav li {
            border-bottom: 1px solid #444;
        }
        
        nav a {
            display: block;
            color: white;
            text-decoration: none;
            padding: 15px;
        }
        
        nav a:hover {
            background-color: #555;
        }
        
        main {
            padding: 20px 0;
        }
        
        .card-grid {
            display: grid;
            grid-template-columns: 1fr;
            gap: 20px;
        }
        
        .card {
            background-color: white;
            border-radius: 10px;
            overflow: hidden;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        .card-image {
            height: 200px;
            background: linear-gradient(135deg, #4ECDC4 0%, #95E1D3 100%);
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 48px;
        }
        
        .card-content {
            padding: 20px;
        }
        
        .card h3 {
            color: #667eea;
            margin-bottom: 10px;
        }
        
        footer {
            background-color: #333;
            color: white;
            text-align: center;
            padding: 30px 15px;
            margin-top: 40px;
        }
        
        /* 平板（>= 768px） */
        @media (min-width: 768px) {
            .container {
                max-width: 750px;
                margin: 0 auto;
                padding: 20px;
            }
            
            header h1 {
                font-size: 36px;
            }
            
            .nav-toggle {
                display: none;
            }
            
            nav ul {
                display: flex !important;
                justify-content: center;
            }
            
            nav li {
                border-bottom: none;
            }
            
            nav a {
                padding: 15px 25px;
            }
            
            .card-grid {
                grid-template-columns: repeat(2, 1fr);
            }
        }
        
        /* 桌機（>= 1200px） */
        @media (min-width: 1200px) {
            .container {
                max-width: 1140px;
            }
            
            header h1 {
                font-size: 48px;
            }
            
            .card-grid {
                grid-template-columns: repeat(3, 1fr);
                gap: 30px;
            }
        }
        
        /* 大螢幕（>= 1600px） */
        @media (min-width: 1600px) {
            .container {
                max-width: 1400px;
            }
            
            .card-grid {
                grid-template-columns: repeat(4, 1fr);
            }
        }
    </style>
</head>
<body>
    <header>
        <h1>🌐 響應式網站</h1>
        <p>適配所有裝置的完美體驗</p>
    </header>
    
    <nav>
        <div class="nav-toggle" onclick="toggleNav()">☰ 選單</div>
        <ul id="navMenu">
            <li><a href="#">首頁</a></li>
            <li><a href="#">產品</a></li>
            <li><a href="#">服務</a></li>
            <li><a href="#">關於</a></li>
            <li><a href="#">聯絡</a></li>
        </ul>
    </nav>
    
    <main>
        <div class="container">
            <h2 style="margin-bottom: 30px; color: #667eea;">產品展示</h2>
            
            <div class="card-grid">
                <div class="card">
                    <div class="card-image">📱</div>
                    <div class="card-content">
                        <h3>產品 1</h3>
                        <p>這是產品描述，在不同裝置上會自動調整布局。</p>
                    </div>
                </div>
                
                <div class="card">
                    <div class="card-image">💻</div>
                    <div class="card-content">
                        <h3>產品 2</h3>
                        <p>響應式設計讓內容在各種螢幕上都能完美呈現。</p>
                    </div>
                </div>
                
                <div class="card">
                    <div class="card-image">⌚</div>
                    <div class="card-content">
                        <h3>產品 3</h3>
                        <p>從手機到大螢幕，提供一致的優質體驗。</p>
                    </div>
                </div>
                
                <div class="card">
                    <div class="card-image">🎧</div>
                    <div class="card-content">
                        <h3>產品 4</h3>
                        <p>Mobile First 設計，優先考慮行動裝置使用者。</p>
                    </div>
                </div>
                
                <div class="card">
                    <div class="card-image">📷</div>
                    <div class="card-content">
                        <h3>產品 5</h3>
                        <p>使用 CSS Grid 和 Flexbox 實現靈活布局。</p>
                    </div>
                </div>
                
                <div class="card">
                    <div class="card-image">🖱️</div>
                    <div class="card-content">
                        <h3>產品 6</h3>
                        <p>Media Queries 讓樣式隨螢幕尺寸變化。</p>
                    </div>
                </div>
            </div>
        </div>
    </main>
    
    <footer>
        <p>&copy; 2026 響應式網站 版權所有</p>
        <p>支援所有裝置 | Mobile First 設計</p>
    </footer>
    
    <script>
        function toggleNav() {
            document.getElementById('navMenu').classList.toggle('active');
        }
    </script>
</body>
</html>
```

## 🎯 響應式設計最佳實踐

### 1. 使用相對單位

```css
/* 不推薦 */
font-size: 16px;
width: 300px;

/* 推薦 */
font-size: 1rem;
width: 100%;
max-width: 300px;
```

### 2. 彈性盒子和網格

```css
/* 使用 Flexbox */
.container {
    display: flex;
    flex-wrap: wrap;
}

/* 使用 Grid */
.grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
}
```

### 3. 隱藏不必要的內容

```css
@media (max-width: 768px) {
    .desktop-only {
        display: none;
    }
}
```

### 4. 觸控友善

```css
/* 足夠大的點擊區域 */
button, a {
    min-height: 44px;
    min-width: 44px;
}
```

## 📝 本課重點回顧

- ✅ 響應式設計讓網頁適應不同裝置
- ✅ 使用 viewport meta 標籤設定視窗
- ✅ Media Queries 根據螢幕尺寸套用樣式
- ✅ 常用斷點：576px、768px、992px、1200px
- ✅ Mobile First 從小螢幕開始設計
- ✅ 使用相對單位和彈性布局
- ✅ 圖片使用 max-width: 100% 自動縮放

## 🎯 課後練習

1. **基礎練習**：響應式導覽列
   - 桌機：水平排列
   - 手機：漢堡選單，點擊展開
   - 使用 Media Queries 切換樣式

2. **進階挑戰**：響應式產品頁面
   - 大螢幕：4 欄
   - 桌機：3 欄
   - 平板：2 欄
   - 手機：1 欄

3. **實戰練習**：完整響應式網站
   - 包含 header、nav、main、footer
   - 至少 3 個不同斷點
   - Mobile First 設計
   - 測試在不同裝置上的效果

## 🔗 下一課預告

在下一課中，我們將學習 CSS 動畫和過渡效果，讓網頁動起來！

---

[← 上一課：Grid 布局](./15-grid.md) | [返回目錄](../README.md) | [下一課：CSS 動畫和過渡 →](./17-animations-transitions.md)
