# 第 3 課：列表和連結

## 📚 本課學習目標

- 掌握三種列表類型的使用方法
- 學會建立巢狀列表
- 了解超連結的各種用法
- 掌握連結的不同目標和類型

## 📋 HTML 列表

HTML 提供三種列表類型：無序列表、有序列表和定義列表。

### 1. 無序列表（Unordered List）

使用 `<ul>` 和 `<li>` 標籤建立，項目前會顯示圓點符號。

```html
<h3>我的興趣</h3>
<ul>
    <li>閱讀</li>
    <li>旅行</li>
    <li>攝影</li>
    <li>程式設計</li>
</ul>
```

**顯示效果：**
- 閱讀
- 旅行
- 攝影
- 程式設計

### 2. 有序列表（Ordered List）

使用 `<ol>` 和 `<li>` 標籤建立，項目前會顯示數字。

```html
<h3>煮飯步驟</h3>
<ol>
    <li>洗米</li>
    <li>加水</li>
    <li>放入電鍋</li>
    <li>按下開關</li>
    <li>等待煮熟</li>
</ol>
```

**顯示效果：**
1. 洗米
2. 加水
3. 放入電鍋
4. 按下開關
5. 等待煮熟

### 有序列表的屬性

```html
<!-- 從 5 開始編號 -->
<ol start="5">
    <li>第五項</li>
    <li>第六項</li>
</ol>

<!-- 反向編號 -->
<ol reversed>
    <li>第一項</li>
    <li>第二項</li>
    <li>第三項</li>
</ol>

<!-- 使用字母編號 -->
<ol type="A">
    <li>選項 A</li>
    <li>選項 B</li>
    <li>選項 C</li>
</ol>

<!-- 使用羅馬數字 -->
<ol type="I">
    <li>第一項</li>
    <li>第二項</li>
</ol>
```

**type 屬性值：**
- `1`：數字（預設）
- `A`：大寫字母
- `a`：小寫字母
- `I`：大寫羅馬數字
- `i`：小寫羅馬數字

### 3. 定義列表（Definition List）

使用 `<dl>`、`<dt>` 和 `<dd>` 標籤，適合用來顯示術語和定義。

```html
<h3>HTML 術語解釋</h3>
<dl>
    <dt>HTML</dt>
    <dd>超文本標記語言，用於建立網頁結構。</dd>
    
    <dt>CSS</dt>
    <dd>層疊樣式表，用於設定網頁的外觀和版面。</dd>
    
    <dt>JavaScript</dt>
    <dd>程式語言，用於實現網頁的互動功能。</dd>
</dl>
```

**顯示效果：**

**HTML**  
　　超文本標記語言，用於建立網頁結構。

**CSS**  
　　層疊樣式表，用於設定網頁的外觀和版面。

**JavaScript**  
　　程式語言，用於實現網頁的互動功能。

## 🏗️ 巢狀列表

列表可以互相巢狀，建立多層結構：

```html
<h3>課程大綱</h3>
<ol>
    <li>HTML 基礎
        <ul>
            <li>標籤和元素</li>
            <li>屬性</li>
            <li>文件結構</li>
        </ul>
    </li>
    <li>CSS 樣式
        <ul>
            <li>選擇器</li>
            <li>盒模型</li>
            <li>布局</li>
        </ul>
    </li>
    <li>JavaScript 程式設計
        <ul>
            <li>變數和資料型別</li>
            <li>函式</li>
            <li>DOM 操作</li>
        </ul>
    </li>
</ol>
```

## 💻 實作練習 1：建立購物清單

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>購物清單</title>
</head>
<body>
    <h1>超市購物清單</h1>
    
    <h2>今天要買的東西</h2>
    <ul>
        <li>水果
            <ul>
                <li>蘋果 5 顆</li>
                <li>香蕉 1 串</li>
                <li>橘子 10 顆</li>
            </ul>
        </li>
        <li>蔬菜
            <ul>
                <li>高麗菜 1 顆</li>
                <li>番茄 5 顆</li>
                <li>青椒 3 顆</li>
            </ul>
        </li>
        <li>日用品
            <ul>
                <li>衛生紙</li>
                <li>洗碗精</li>
            </ul>
        </li>
    </ul>
</body>
</html>
```

## 🔗 超連結（Links）

超連結使用 `<a>` 標籤建立，是網頁之間導航的基礎。

### 1. 基本連結語法

```html
<a href="目標網址">連結文字</a>
```

### 2. 外部連結

連結到其他網站：

```html
<p>訪問 <a href="https://www.google.com">Google</a></p>
<p>學習 <a href="https://developer.mozilla.org">MDN Web Docs</a></p>
```

### 3. 內部連結

連結到同一網站的其他頁面：

```html
<!-- 相對路徑 -->
<a href="about.html">關於我們</a>
<a href="products/list.html">產品列表</a>
<a href="../index.html">回首頁</a>

<!-- 絕對路徑 -->
<a href="/contact.html">聯絡我們</a>
```

**路徑說明：**
- `about.html`：同一資料夾
- `products/list.html`：子資料夾
- `../index.html`：上一層資料夾
- `/contact.html`：網站根目錄

### 4. 連結目標（target 屬性）

```html
<!-- 在新分頁開啟 -->
<a href="https://www.example.com" target="_blank">在新分頁開啟</a>

<!-- 在同一分頁開啟（預設） -->
<a href="https://www.example.com" target="_self">在同一分頁開啟</a>
```

**target 屬性值：**
- `_blank`：在新視窗或分頁開啟
- `_self`：在同一框架中開啟（預設）
- `_parent`：在父框架中開啟
- `_top`：在整個視窗中開啟

### 5. 電子郵件連結

```html
<a href="mailto:example@email.com">寄信給我們</a>

<!-- 帶主旨和內容 -->
<a href="mailto:example@email.com?subject=詢問&body=您好">寄信給我們</a>
```

### 6. 電話連結

```html
<a href="tel:+886912345678">撥打電話：0912-345-678</a>
```

### 7. 錨點連結（頁面內跳轉）

```html
<!-- 定義錨點 -->
<h2 id="section1">第一節</h2>
<h2 id="section2">第二節</h2>
<h2 id="section3">第三節</h2>

<!-- 連結到錨點 -->
<nav>
    <a href="#section1">跳到第一節</a> |
    <a href="#section2">跳到第二節</a> |
    <a href="#section3">跳到第三節</a>
</nav>

<!-- 回到頁面頂端 -->
<a href="#top">回到頂端</a>
```

### 8. 下載連結

```html
<a href="files/document.pdf" download>下載 PDF 檔案</a>
<a href="images/photo.jpg" download="我的照片.jpg">下載圖片</a>
```

## 💻 實作練習 2：建立導覽選單

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>我的網站</title>
</head>
<body>
    <header>
        <h1>歡迎來到我的網站</h1>
        <nav>
            <ul>
                <li><a href="#home">首頁</a></li>
                <li><a href="#about">關於我</a></li>
                <li><a href="#portfolio">作品集</a></li>
                <li><a href="#contact">聯絡方式</a></li>
            </ul>
        </nav>
    </header>
    
    <main>
        <section id="home">
            <h2>首頁</h2>
            <p>歡迎來到我的個人網站！</p>
        </section>
        
        <section id="about">
            <h2>關於我</h2>
            <p>我是一位網頁設計師，熱愛程式設計。</p>
        </section>
        
        <section id="portfolio">
            <h2>作品集</h2>
            <ul>
                <li><a href="projects/project1.html">專案一</a></li>
                <li><a href="projects/project2.html">專案二</a></li>
                <li><a href="projects/project3.html">專案三</a></li>
            </ul>
        </section>
        
        <section id="contact">
            <h2>聯絡方式</h2>
            <ul>
                <li>電子郵件：<a href="mailto:me@example.com">me@example.com</a></li>
                <li>電話：<a href="tel:+886912345678">0912-345-678</a></li>
                <li>網站：<a href="https://www.example.com" target="_blank">www.example.com</a></li>
            </ul>
        </section>
    </main>
    
    <footer>
        <p><a href="#top">回到頂端</a></p>
        <p>&copy; 2026 版權所有</p>
    </footer>
</body>
</html>
```

## 🎨 連結的輔助屬性

### title 屬性

提供額外的提示資訊：

```html
<a href="https://www.example.com" title="點擊前往範例網站">範例網站</a>
```

### rel 屬性

定義連結關係：

```html
<!-- 告訴搜尋引擎不要追蹤這個連結 -->
<a href="https://www.example.com" rel="nofollow">外部連結</a>

<!-- 提升安全性（用於 target="_blank"） -->
<a href="https://www.example.com" target="_blank" rel="noopener noreferrer">
    安全的外部連結
</a>
```

## 📝 本課重點回顧

- ✅ 使用 `<ul>` 建立無序列表，`<ol>` 建立有序列表
- ✅ 使用 `<dl>`、`<dt>`、`<dd>` 建立定義列表
- ✅ 列表可以巢狀使用，建立多層結構
- ✅ 使用 `<a>` 標籤建立超連結
- ✅ `href` 屬性指定連結目標
- ✅ `target="_blank"` 在新分頁開啟連結
- ✅ 使用 `#id` 建立錨點連結，實現頁面內跳轉
- ✅ `mailto:` 建立郵件連結，`tel:` 建立電話連結

## 🎯 課後練習

1. **基礎練習**：建立一個食譜頁面
   - 使用有序列表列出烹飪步驟
   - 使用無序列表列出所需材料
   - 每個材料項目可以巢狀列出詳細份量

2. **進階挑戰**：建立一個個人履歷網站
   - 使用定義列表顯示個人資料（姓名、年齡、地址等）
   - 建立一個導覽選單，包含：簡介、學歷、經歷、技能、聯絡
   - 使用錨點連結讓導覽選單可以跳轉到對應區塊
   - 在底部加入「回到頂端」連結

3. **實戰練習**：建立一個推薦網站清單
   - 至少包含 10 個網站連結
   - 將網站分類（學習、娛樂、工具等）
   - 使用巢狀列表組織分類
   - 所有外部連結都在新分頁開啟

## 🔗 下一課預告

在下一課中，我們將學習如何在網頁中加入圖片和多媒體元素（音訊、視訊），讓網頁更加生動！

---

[← 上一課：文字標籤和格式化](./02-text-formatting.md) | [返回目錄](../README.md) | [下一課：圖片和多媒體 →](./04-images-media.md)
