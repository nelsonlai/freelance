# 第 8 課：HTML5 語義化標籤

## 📚 本課學習目標

- 理解語義化標籤的重要性
- 掌握 HTML5 新增的結構性標籤
- 學會建立語義化的網頁結構
- 了解語義化標籤對 SEO 和無障礙的好處

## 🌟 什麼是語義化標籤？

**語義化標籤（Semantic Tags）**是具有明確意義的 HTML 標籤，能夠清楚描述內容的性質和用途。

### 為什麼需要語義化？

#### ❌ 非語義化寫法

```html
<div id="header">
    <div id="nav">
        <a href="/">首頁</a>
    </div>
</div>
<div id="main">
    <div class="post">
        <h2>文章標題</h2>
        <p>文章內容...</p>
    </div>
</div>
<div id="footer">
    版權所有
</div>
```

#### ✅ 語義化寫法

```html
<header>
    <nav>
        <a href="/">首頁</a>
    </nav>
</header>
<main>
    <article>
        <h2>文章標題</h2>
        <p>文章內容...</p>
    </article>
</main>
<footer>
    版權所有
</footer>
```

### 語義化的好處

1. **📖 可讀性更好**：代碼更容易理解和維護
2. **🔍 SEO 優化**：搜尋引擎更容易理解網頁結構
3. **♿ 無障礙性**：螢幕閱讀器能更好地解讀內容
4. **🔧 維護性**：團隊協作更容易
5. **🎯 明確性**：每個標籤都有特定的用途

## 🏗️ HTML5 結構性標籤

### 1. `<header>` - 頁首

用於網頁或區塊的頁首，通常包含標題、導覽列、標誌等。

```html
<header>
    <h1>我的部落格</h1>
    <p>分享生活點滴</p>
    <nav>
        <a href="/">首頁</a>
        <a href="/about">關於</a>
        <a href="/contact">聯絡</a>
    </nav>
</header>
```

**可以有多個 header：**
```html
<header>
    <!-- 網站主要 header -->
    <h1>網站標題</h1>
</header>

<article>
    <header>
        <!-- 文章的 header -->
        <h2>文章標題</h2>
        <p>作者：張三 | 日期：2026-02-11</p>
    </header>
    <p>文章內容...</p>
</article>
```

### 2. `<nav>` - 導覽列

包含網站的主要導覽連結。

```html
<nav>
    <ul>
        <li><a href="/">首頁</a></li>
        <li><a href="/products">產品</a></li>
        <li><a href="/about">關於我們</a></li>
        <li><a href="/contact">聯絡我們</a></li>
    </ul>
</nav>
```

**注意**：不是所有連結都要放在 `<nav>` 中，只有主要導覽才需要。

### 3. `<main>` - 主要內容

網頁的主要內容區域，每個頁面只能有一個 `<main>`。

```html
<main>
    <h1>歡迎來到我的網站</h1>
    <p>這是主要內容區域。</p>
    
    <article>
        <h2>最新文章</h2>
        <p>文章內容...</p>
    </article>
</main>
```

### 4. `<article>` - 文章

獨立、完整的內容單元，可以單獨分發或重複使用。

```html
<article>
    <header>
        <h2>如何學習 HTML5</h2>
        <p>作者：李四 | 發布時間：2026-02-11</p>
    </header>
    
    <p>HTML5 是現代網頁開發的基礎...</p>
    <p>學習 HTML5 需要掌握以下重點...</p>
    
    <footer>
        <p>分類：教學 | 標籤：HTML, 前端</p>
    </footer>
</article>
```

**適用場景：**
- 部落格文章
- 新聞報導
- 論壇貼文
- 評論

### 5. `<section>` - 區塊

相關內容的主題性分組。

```html
<article>
    <h1>網頁設計完整指南</h1>
    
    <section>
        <h2>什麼是網頁設計？</h2>
        <p>網頁設計是...</p>
    </section>
    
    <section>
        <h2>網頁設計的重要性</h2>
        <p>好的網頁設計能夠...</p>
    </section>
    
    <section>
        <h2>如何開始學習</h2>
        <p>學習網頁設計可以從...</p>
    </section>
</article>
```

### 6. `<aside>` - 側邊欄

與主要內容相關但可以獨立的內容，如側邊欄、廣告、相關連結等。

```html
<main>
    <article>
        <h1>主要文章內容</h1>
        <p>文章正文...</p>
    </article>
    
    <aside>
        <h3>相關文章</h3>
        <ul>
            <li><a href="#">相關文章 1</a></li>
            <li><a href="#">相關文章 2</a></li>
        </ul>
        
        <h3>廣告</h3>
        <p>廣告內容...</p>
    </aside>
</main>
```

### 7. `<footer>` - 頁尾

網頁或區塊的頁尾，通常包含版權、聯絡資訊、相關連結等。

```html
<footer>
    <p>&copy; 2026 我的網站版權所有</p>
    <nav>
        <a href="/privacy">隱私政策</a> |
        <a href="/terms">使用條款</a> |
        <a href="/contact">聯絡我們</a>
    </nav>
</footer>
```

## 💻 實作練習 1：部落格文章頁面

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>我的部落格</title>
    <style>
        body {
            font-family: 'Microsoft JhengHei', Arial, sans-serif;
            line-height: 1.6;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        header {
            background-color: #333;
            color: white;
            padding: 20px;
            text-align: center;
        }
        nav {
            background-color: #444;
            padding: 10px;
        }
        nav a {
            color: white;
            text-decoration: none;
            margin: 0 15px;
        }
        main {
            display: flex;
            gap: 20px;
            margin-top: 20px;
        }
        article {
            flex: 3;
            background-color: #f9f9f9;
            padding: 20px;
            border-radius: 5px;
        }
        article header {
            background-color: transparent;
            color: #333;
            padding: 0;
            text-align: left;
            border-bottom: 2px solid #ddd;
            padding-bottom: 10px;
            margin-bottom: 20px;
        }
        aside {
            flex: 1;
            background-color: #e9e9e9;
            padding: 20px;
            border-radius: 5px;
        }
        footer {
            background-color: #333;
            color: white;
            text-align: center;
            padding: 20px;
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <header>
        <h1>我的技術部落格</h1>
        <p>分享程式開發心得</p>
    </header>
    
    <nav>
        <a href="/">首頁</a>
        <a href="/articles">文章</a>
        <a href="/about">關於我</a>
        <a href="/contact">聯絡</a>
    </nav>
    
    <main>
        <article>
            <header>
                <h2>HTML5 語義化標籤完整指南</h2>
                <p>
                    <time datetime="2026-02-11">2026年2月11日</time> |
                    作者：張大明 |
                    分類：前端開發
                </p>
            </header>
            
            <section>
                <h3>什麼是語義化標籤？</h3>
                <p>
                    語義化標籤是 HTML5 引入的重要特性，
                    它讓網頁結構更加清晰，也更容易被搜尋引擎和輔助技術理解。
                </p>
            </section>
            
            <section>
                <h3>為什麼要使用語義化標籤？</h3>
                <p>
                    使用語義化標籤有許多好處，包括提升 SEO、
                    改善無障礙性、讓程式碼更易讀等。
                </p>
            </section>
            
            <section>
                <h3>常用的語義化標籤</h3>
                <p>
                    HTML5 提供了許多語義化標籤，如 header、nav、
                    main、article、section、aside 和 footer 等。
                </p>
            </section>
            
            <footer>
                <p>
                    標籤：
                    <a href="#">HTML5</a>
                    <a href="#">語義化</a>
                    <a href="#">前端</a>
                </p>
            </footer>
        </article>
        
        <aside>
            <section>
                <h3>關於作者</h3>
                <p>張大明是一位資深前端工程師，擁有10年開發經驗。</p>
            </section>
            
            <section>
                <h3>熱門文章</h3>
                <ul>
                    <li><a href="#">CSS Flexbox 完全指南</a></li>
                    <li><a href="#">JavaScript ES6 新特性</a></li>
                    <li><a href="#">響應式設計最佳實踐</a></li>
                </ul>
            </section>
            
            <section>
                <h3>分類</h3>
                <ul>
                    <li><a href="#">HTML (15)</a></li>
                    <li><a href="#">CSS (23)</a></li>
                    <li><a href="#">JavaScript (32)</a></li>
                    <li><a href="#">React (18)</a></li>
                </ul>
            </section>
        </aside>
    </main>
    
    <footer>
        <p>&copy; 2026 我的技術部落格 版權所有</p>
        <nav>
            <a href="/privacy">隱私政策</a> |
            <a href="/terms">使用條款</a> |
            <a href="/sitemap">網站地圖</a>
        </nav>
    </footer>
</body>
</html>
```

## 🎯 其他語義化標籤

### 1. `<figure>` 和 `<figcaption>`

用於圖片、圖表、程式碼等內容及其說明：

```html
<figure>
    <img src="chart.png" alt="銷售數據圖表">
    <figcaption>圖 1：2026 年第一季銷售數據</figcaption>
</figure>
```

### 2. `<time>` - 時間

標記日期或時間：

```html
<p>文章發布於 <time datetime="2026-02-11">2026年2月11日</time></p>
<p>活動時間：<time datetime="2026-03-15T14:00">3月15日下午2點</time></p>
```

### 3. `<mark>` - 標記

標記重要或相關的文字：

```html
<p>搜尋結果：HTML5 是<mark>現代網頁</mark>開發的基礎</p>
```

### 4. `<details>` 和 `<summary>`

建立可折疊的內容區塊：

```html
<details>
    <summary>什麼是 HTML5？</summary>
    <p>HTML5 是最新版本的超文本標記語言，增加了許多新功能和語義化標籤。</p>
</details>

<details open>
    <summary>課程內容</summary>
    <ul>
        <li>HTML 基礎</li>
        <li>CSS 樣式</li>
        <li>JavaScript 程式</li>
    </ul>
</details>
```

### 5. `<address>` - 聯絡資訊

標記聯絡資訊：

```html
<address>
    聯絡人：張小明<br>
    電子郵件：<a href="mailto:ming@example.com">ming@example.com</a><br>
    電話：<a href="tel:+886912345678">0912-345-678</a><br>
    地址：台北市信義區信義路五段7號
</address>
```

## 💻 實作練習 2：完整的企業網站首頁

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>科技公司 - 創新未來</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Microsoft JhengHei', Arial, sans-serif;
            line-height: 1.6;
        }
        header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 15px 0;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 0 20px;
        }
        header .container {
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        header h1 {
            font-size: 24px;
        }
        nav ul {
            list-style: none;
            display: flex;
            gap: 20px;
        }
        nav a {
            color: white;
            text-decoration: none;
            transition: opacity 0.3s;
        }
        nav a:hover {
            opacity: 0.8;
        }
        .hero {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 100px 20px;
            text-align: center;
        }
        .hero h2 {
            font-size: 48px;
            margin-bottom: 20px;
        }
        main {
            padding: 60px 20px;
        }
        .services {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 30px;
            margin-bottom: 60px;
        }
        .service-card {
            background-color: #f9f9f9;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        .service-card h3 {
            color: #667eea;
            margin-bottom: 15px;
        }
        .about {
            background-color: #f5f5f5;
            padding: 60px 20px;
        }
        footer {
            background-color: #333;
            color: white;
            padding: 40px 20px;
        }
        footer .container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 30px;
        }
        footer h3 {
            margin-bottom: 15px;
        }
        footer ul {
            list-style: none;
        }
        footer a {
            color: #ccc;
            text-decoration: none;
        }
        footer a:hover {
            color: white;
        }
    </style>
</head>
<body>
    <header>
        <div class="container">
            <h1>🚀 創新科技公司</h1>
            <nav>
                <ul>
                    <li><a href="#home">首頁</a></li>
                    <li><a href="#services">服務</a></li>
                    <li><a href="#about">關於我們</a></li>
                    <li><a href="#contact">聯絡</a></li>
                </ul>
            </nav>
        </div>
    </header>
    
    <section class="hero" id="home">
        <div class="container">
            <h2>創新科技，改變未來</h2>
            <p>我們致力於提供最先進的技術解決方案</p>
        </div>
    </section>
    
    <main class="container">
        <section id="services">
            <h2 style="text-align: center; margin-bottom: 40px; font-size: 36px;">我們的服務</h2>
            
            <div class="services">
                <article class="service-card">
                    <h3>網頁開發</h3>
                    <p>
                        提供專業的網頁設計與開發服務，
                        從企業官網到電子商務平台，
                        打造符合您需求的完美網站。
                    </p>
                </article>
                
                <article class="service-card">
                    <h3>行動應用</h3>
                    <p>
                        開發 iOS 和 Android 行動應用程式，
                        提供流暢的使用者體驗，
                        協助您的業務延伸到行動裝置。
                    </p>
                </article>
                
                <article class="service-card">
                    <h3>雲端服務</h3>
                    <p>
                        提供雲端架構規劃與部署服務，
                        確保系統的穩定性和擴展性，
                        降低營運成本。
                    </p>
                </article>
                
                <article class="service-card">
                    <h3>AI 解決方案</h3>
                    <p>
                        運用人工智慧技術，
                        為企業提供智慧化解決方案，
                        提升營運效率和競爭力。
                    </p>
                </article>
                
                <article class="service-card">
                    <h3>資料分析</h3>
                    <p>
                        專業的資料分析服務，
                        協助企業從大數據中發掘商業洞察，
                        制定更好的決策。
                    </p>
                </article>
                
                <article class="service-card">
                    <h3>技術諮詢</h3>
                    <p>
                        提供專業的技術諮詢服務，
                        協助企業規劃技術架構，
                        選擇最適合的技術方案。
                    </p>
                </article>
            </div>
        </section>
        
        <section class="about" id="about" style="margin: 0 -20px; padding: 60px 20px;">
            <div class="container">
                <h2 style="text-align: center; margin-bottom: 30px; font-size: 36px;">關於我們</h2>
                
                <article>
                    <p style="font-size: 18px; text-align: center; max-width: 800px; margin: 0 auto;">
                        創新科技公司成立於 2015 年，我們是一群充滿熱情的技術專家，
                        致力於為客戶提供最優質的技術服務。
                        我們相信科技能夠改變世界，並持續創新，追求卓越。
                    </p>
                </article>
                
                <details style="max-width: 800px; margin: 30px auto; padding: 20px; background: white; border-radius: 5px;">
                    <summary style="font-weight: bold; cursor: pointer;">我們的使命</summary>
                    <p style="margin-top: 15px;">
                        透過創新技術解決方案，協助企業數位轉型，
                        提升競爭力，創造更大的商業價值。
                    </p>
                </details>
                
                <details style="max-width: 800px; margin: 30px auto; padding: 20px; background: white; border-radius: 5px;">
                    <summary style="font-weight: bold; cursor: pointer;">我們的願景</summary>
                    <p style="margin-top: 15px;">
                        成為業界最受信賴的技術服務提供商，
                        以卓越的技術和服務，引領產業創新發展。
                    </p>
                </details>
            </div>
        </section>
    </main>
    
    <footer id="contact">
        <div class="container">
            <section>
                <h3>關於公司</h3>
                <p>創新科技公司致力於提供最優質的技術服務，協助企業數位轉型。</p>
            </section>
            
            <section>
                <h3>快速連結</h3>
                <nav>
                    <ul>
                        <li><a href="#services">服務項目</a></li>
                        <li><a href="#about">關於我們</a></li>
                        <li><a href="#">客戶案例</a></li>
                        <li><a href="#">部落格</a></li>
                    </ul>
                </nav>
            </section>
            
            <section>
                <h3>聯絡我們</h3>
                <address>
                    <p>電話：<a href="tel:+88622345678">02-2345-6789</a></p>
                    <p>Email：<a href="mailto:info@techcompany.com">info@techcompany.com</a></p>
                    <p>地址：台北市信義區信義路五段7號</p>
                </address>
            </section>
            
            <section>
                <h3>追蹤我們</h3>
                <nav>
                    <ul>
                        <li><a href="#">Facebook</a></li>
                        <li><a href="#">Instagram</a></li>
                        <li><a href="#">LinkedIn</a></li>
                        <li><a href="#">Twitter</a></li>
                    </ul>
                </nav>
            </section>
        </div>
        
        <div class="container" style="text-align: center; margin-top: 40px; padding-top: 20px; border-top: 1px solid #555;">
            <p>&copy; <time datetime="2026">2026</time> 創新科技公司 版權所有</p>
        </div>
    </footer>
</body>
</html>
```

## 📝 語義化標籤使用原則

### ✅ 應該做的

1. **選擇最合適的標籤**：根據內容的語義選擇標籤
2. **保持結構清晰**：合理嵌套，避免過度複雜
3. **使用正確的標題層級**：h1 到 h6 要有邏輯順序
4. **為 img 加上 alt**：提升無障礙性
5. **使用 nav 包裹導覽**：主要導覽使用 nav 標籤

### ❌ 不應該做的

1. **不要只用 div**：能用語義化標籤就不要用 div
2. **不要為了樣式選標籤**：標籤選擇應基於內容，不是外觀
3. **不要跳過標題層級**：不要從 h1 直接跳到 h3
4. **不要濫用 section**：沒有明確主題不要用 section
5. **不要把所有東西放進 article**：article 應該是獨立完整的內容

## 📝 本課重點回顧

- ✅ 語義化標籤讓網頁結構更清晰、更有意義
- ✅ `<header>` 用於頁首，`<footer>` 用於頁尾
- ✅ `<nav>` 包含主要導覽連結
- ✅ `<main>` 是主要內容區，每頁只能有一個
- ✅ `<article>` 用於獨立完整的內容
- ✅ `<section>` 用於主題性分組
- ✅ `<aside>` 用於側邊欄或相關內容
- ✅ 語義化標籤提升 SEO、無障礙性和可維護性

## 🎯 課後練習

1. **基礎練習**：將一個使用 div 的網頁改寫成語義化結構
   - 找一個舊的網頁範例
   - 識別各個區塊的用途
   - 使用適當的語義化標籤重寫

2. **進階挑戰**：建立個人作品集網站
   - 使用完整的語義化標籤結構
   - 包含：header、nav、main、article、aside、footer
   - 至少展示 3 個作品（使用 article）
   - 加入側邊欄顯示個人資訊（使用 aside）

3. **實戰練習**：建立新聞網站首頁
   - 頁首包含網站標誌和導覽列
   - 主要區域顯示多篇新聞（每篇用 article）
   - 側邊欄顯示熱門新聞和廣告（使用 aside）
   - 每篇新聞都有標題、發布時間、內容摘要
   - 頁尾包含版權和相關連結

## 🔗 下一課預告

在下一課中，我們將學習 HTML5 的其他新功能，包括 Canvas、SVG、地理定位、本地儲存等進階特性！

---

[← 上一課：表單進階](./07-forms-advanced.md) | [返回目錄](../README.md) | [下一課：HTML5 新功能 →](./09-html5-features.md)
