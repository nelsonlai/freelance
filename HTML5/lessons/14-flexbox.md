# 第 14 課：Flexbox 布局

## 📚 本課學習目標

- 理解 Flexbox 的概念和優勢
- 掌握 Flex 容器和項目的屬性
- 學會使用 Flexbox 建立各種布局
- 解決常見的布局問題

## 🎯 什麼是 Flexbox？

**Flexbox（彈性盒子）**是一種一維布局模型，專門用於在容器中排列和分配空間。

### Flexbox 的優勢

- ✅ 輕鬆實現垂直置中
- ✅ 自動調整元素大小
- ✅ 靈活的排列方向
- ✅ 簡化複雜布局
- ✅ 響應式設計更容易

## 🏗️ 基本概念

### Flex 容器和項目

```html
<div class="container">  <!-- Flex 容器 -->
    <div class="item">1</div>  <!-- Flex 項目 -->
    <div class="item">2</div>
    <div class="item">3</div>
</div>
```

```css
.container {
    display: flex;  /* 啟用 Flexbox */
}
```

### 主軸和交叉軸

- **主軸（Main Axis）**：元素排列的方向
- **交叉軸（Cross Axis）**：垂直於主軸的方向

```
flex-direction: row（預設）
┌──────────────────────────┐
│  主軸 →                   │
│  ↓                       │
│  交                       │
│  叉                       │
│  軸                       │
└──────────────────────────┘
```

## 📦 Flex 容器屬性

### 1. flex-direction（排列方向）

```css
.container {
    display: flex;
    flex-direction: row;           /* 水平排列（預設） */
    flex-direction: row-reverse;   /* 水平反向 */
    flex-direction: column;        /* 垂直排列 */
    flex-direction: column-reverse; /* 垂直反向 */
}
```

### 2. justify-content（主軸對齊）

```css
.container {
    display: flex;
    justify-content: flex-start;    /* 靠左（預設） */
    justify-content: flex-end;      /* 靠右 */
    justify-content: center;        /* 置中 */
    justify-content: space-between; /* 兩端對齊 */
    justify-content: space-around;  /* 環繞對齊 */
    justify-content: space-evenly;  /* 均勻分布 */
}
```

### 3. align-items（交叉軸對齊）

```css
.container {
    display: flex;
    align-items: stretch;     /* 拉伸（預設） */
    align-items: flex-start;  /* 靠上 */
    align-items: flex-end;    /* 靠下 */
    align-items: center;      /* 垂直置中 */
    align-items: baseline;    /* 基線對齊 */
}
```

### 4. flex-wrap（換行）

```css
.container {
    display: flex;
    flex-wrap: nowrap;        /* 不換行（預設） */
    flex-wrap: wrap;          /* 換行 */
    flex-wrap: wrap-reverse;  /* 反向換行 */
}
```

### 5. gap（間距）

```css
.container {
    display: flex;
    gap: 20px;           /* 項目間距 */
    row-gap: 15px;       /* 列間距 */
    column-gap: 25px;    /* 欄間距 */
}
```

## 💻 實作練習 1：Flex 容器屬性

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Flexbox 基礎示範</title>
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
        
        .flex-container {
            display: flex;
            background-color: #E8F8F5;
            padding: 20px;
            margin: 15px 0;
            border-radius: 10px;
            min-height: 150px;
        }
        
        .flex-item {
            background-color: #4ECDC4;
            color: white;
            padding: 20px;
            margin: 5px;
            border-radius: 5px;
            font-weight: bold;
            text-align: center;
        }
        
        /* justify-content 範例 */
        .jc-start { justify-content: flex-start; }
        .jc-center { justify-content: center; }
        .jc-end { justify-content: flex-end; }
        .jc-between { justify-content: space-between; }
        .jc-around { justify-content: space-around; }
        .jc-evenly { justify-content: space-evenly; }
        
        /* align-items 範例 */
        .ai-start { align-items: flex-start; }
        .ai-center { align-items: center; }
        .ai-end { align-items: flex-end; }
        
        /* flex-direction 範例 */
        .fd-row { flex-direction: row; }
        .fd-column { flex-direction: column; }
        
        /* flex-wrap 範例 */
        .fw-wrap { flex-wrap: wrap; }
        
        .code {
            background-color: #333;
            color: #FFE66D;
            padding: 5px 10px;
            border-radius: 3px;
            font-family: monospace;
            display: inline-block;
            margin: 5px 0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎯 Flexbox 布局示範</h1>
        
        <h2>justify-content（主軸對齊）</h2>
        
        <p class="code">justify-content: flex-start;</p>
        <div class="flex-container jc-start">
            <div class="flex-item">1</div>
            <div class="flex-item">2</div>
            <div class="flex-item">3</div>
        </div>
        
        <p class="code">justify-content: center;</p>
        <div class="flex-container jc-center">
            <div class="flex-item">1</div>
            <div class="flex-item">2</div>
            <div class="flex-item">3</div>
        </div>
        
        <p class="code">justify-content: space-between;</p>
        <div class="flex-container jc-between">
            <div class="flex-item">1</div>
            <div class="flex-item">2</div>
            <div class="flex-item">3</div>
        </div>
        
        <p class="code">justify-content: space-evenly;</p>
        <div class="flex-container jc-evenly">
            <div class="flex-item">1</div>
            <div class="flex-item">2</div>
            <div class="flex-item">3</div>
        </div>
        
        <h2>align-items（交叉軸對齊）</h2>
        
        <p class="code">align-items: flex-start;</p>
        <div class="flex-container ai-start">
            <div class="flex-item">1</div>
            <div class="flex-item" style="height: 80px;">2<br>較高</div>
            <div class="flex-item">3</div>
        </div>
        
        <p class="code">align-items: center;</p>
        <div class="flex-container ai-center">
            <div class="flex-item">1</div>
            <div class="flex-item" style="height: 80px;">2<br>較高</div>
            <div class="flex-item">3</div>
        </div>
        
        <h2>flex-direction（排列方向）</h2>
        
        <p class="code">flex-direction: column;</p>
        <div class="flex-container fd-column ai-center">
            <div class="flex-item">1</div>
            <div class="flex-item">2</div>
            <div class="flex-item">3</div>
        </div>
    </div>
</body>
</html>
```

## 🎨 Flex 項目屬性

### 1. flex-grow（伸展比例）

```css
.item {
    flex-grow: 0;  /* 不伸展（預設） */
    flex-grow: 1;  /* 平均分配剩餘空間 */
    flex-grow: 2;  /* 佔用兩倍空間 */
}
```

### 2. flex-shrink（收縮比例）

```css
.item {
    flex-shrink: 1;  /* 正常收縮（預設） */
    flex-shrink: 0;  /* 不收縮 */
}
```

### 3. flex-basis（基礎大小）

```css
.item {
    flex-basis: auto;   /* 自動（預設） */
    flex-basis: 200px;  /* 固定大小 */
    flex-basis: 30%;    /* 百分比 */
}
```

### 4. flex 簡寫

```css
.item {
    /* flex: grow shrink basis */
    flex: 0 1 auto;   /* 預設值 */
    flex: 1;          /* flex: 1 1 0% */
    flex: 2;          /* flex: 2 1 0% */
    flex: 200px;      /* flex: 1 1 200px */
}
```

### 5. align-self（個別對齊）

```css
.item {
    align-self: auto;        /* 繼承容器設定（預設） */
    align-self: flex-start;  /* 靠上 */
    align-self: flex-end;    /* 靠下 */
    align-self: center;      /* 置中 */
}
```

### 6. order（排列順序）

```css
.item-1 { order: 2; }
.item-2 { order: 1; }
.item-3 { order: 3; }
/* 顯示順序：2, 1, 3 */
```

## 💻 實作練習 2：Flex 項目屬性

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Flex 項目屬性</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        h2 {
            color: #667eea;
            margin: 30px 0 15px;
        }
        
        .flex-container {
            display: flex;
            background-color: #E8F8F5;
            padding: 20px;
            margin: 15px 0;
            border-radius: 10px;
            gap: 10px;
        }
        
        .flex-item {
            background-color: #4ECDC4;
            color: white;
            padding: 20px;
            border-radius: 5px;
            text-align: center;
        }
        
        /* flex-grow 範例 */
        .grow-1 { flex-grow: 1; }
        .grow-2 { flex-grow: 2; }
        
        /* flex-basis 範例 */
        .basis-200 { flex-basis: 200px; }
        
        /* align-self 範例 */
        .self-start { align-self: flex-start; }
        .self-center { align-self: center; }
        .self-end { align-self: flex-end; }
    </style>
</head>
<body>
    <div class="container">
        <h1 style="text-align: center; color: #667eea;">Flex 項目屬性</h1>
        
        <h2>flex-grow（伸展比例）</h2>
        <div class="flex-container">
            <div class="flex-item">固定</div>
            <div class="flex-item grow-1">flex-grow: 1</div>
            <div class="flex-item grow-2">flex-grow: 2</div>
        </div>
        
        <h2>flex-basis（基礎大小）</h2>
        <div class="flex-container">
            <div class="flex-item basis-200">flex-basis: 200px</div>
            <div class="flex-item grow-1">自動填滿剩餘空間</div>
        </div>
        
        <h2>align-self（個別對齊）</h2>
        <div class="flex-container" style="height: 200px; align-items: center;">
            <div class="flex-item">預設</div>
            <div class="flex-item self-start">align-self: flex-start</div>
            <div class="flex-item self-end">align-self: flex-end</div>
        </div>
    </div>
</body>
</html>
```

## 🎯 實用範例

### 1. 完美置中

```css
.center-container {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
}
```

### 2. 導覽列

```css
.navbar {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 20px;
}

.nav-links {
    display: flex;
    gap: 20px;
}
```

### 3. 卡片布局

```css
.card-container {
    display: flex;
    flex-wrap: wrap;
    gap: 20px;
}

.card {
    flex: 1 1 300px;  /* 最小寬度 300px */
}
```

### 4. 頁尾固定底部

```css
body {
    display: flex;
    flex-direction: column;
    min-height: 100vh;
}

main {
    flex: 1;  /* 佔滿剩餘空間 */
}
```

## 💻 實作練習 3：完整布局

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Flexbox 完整布局</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            display: flex;
            flex-direction: column;
            min-height: 100vh;
        }
        
        /* 導覽列 */
        header {
            background-color: #667eea;
            color: white;
            padding: 20px;
        }
        
        .navbar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            max-width: 1200px;
            margin: 0 auto;
        }
        
        .nav-links {
            display: flex;
            gap: 30px;
            list-style: none;
        }
        
        .nav-links a {
            color: white;
            text-decoration: none;
        }
        
        /* 主要內容 */
        main {
            flex: 1;
            padding: 40px 20px;
            background-color: #f5f5f5;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        /* 卡片布局 */
        .card-grid {
            display: flex;
            flex-wrap: wrap;
            gap: 20px;
            margin: 20px 0;
        }
        
        .card {
            flex: 1 1 300px;
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        .card h3 {
            color: #667eea;
            margin-bottom: 10px;
        }
        
        /* 頁尾 */
        footer {
            background-color: #333;
            color: white;
            padding: 30px 20px;
        }
        
        .footer-content {
            display: flex;
            justify-content: space-between;
            align-items: center;
            max-width: 1200px;
            margin: 0 auto;
            flex-wrap: wrap;
            gap: 20px;
        }
    </style>
</head>
<body>
    <header>
        <nav class="navbar">
            <h1>我的網站</h1>
            <ul class="nav-links">
                <li><a href="#">首頁</a></li>
                <li><a href="#">關於</a></li>
                <li><a href="#">服務</a></li>
                <li><a href="#">聯絡</a></li>
            </ul>
        </nav>
    </header>
    
    <main>
        <div class="container">
            <h2 style="color: #667eea; margin-bottom: 20px;">我們的服務</h2>
            
            <div class="card-grid">
                <div class="card">
                    <h3>網頁設計</h3>
                    <p>專業的網頁設計服務，打造美觀且實用的網站。</p>
                </div>
                
                <div class="card">
                    <h3>系統開發</h3>
                    <p>客製化系統開發，滿足您的特殊需求。</p>
                </div>
                
                <div class="card">
                    <h3>數位行銷</h3>
                    <p>全方位的數位行銷策略，提升品牌曝光度。</p>
                </div>
                
                <div class="card">
                    <h3>技術支援</h3>
                    <p>專業的技術團隊，提供即時支援服務。</p>
                </div>
                
                <div class="card">
                    <h3>諮詢服務</h3>
                    <p>提供專業的技術諮詢，協助您做出最佳決策。</p>
                </div>
                
                <div class="card">
                    <h3>培訓課程</h3>
                    <p>定期舉辦技術培訓課程，提升團隊能力。</p>
                </div>
            </div>
        </div>
    </main>
    
    <footer>
        <div class="footer-content">
            <p>&copy; 2026 我的網站 版權所有</p>
            <p>聯絡我們：info@example.com</p>
        </div>
    </footer>
</body>
</html>
```

## 📝 本課重點回顧

- ✅ Flexbox 是一維布局模型，簡化元素排列
- ✅ display: flex 啟用 Flexbox
- ✅ justify-content 控制主軸對齊
- ✅ align-items 控制交叉軸對齊
- ✅ flex-wrap 控制是否換行
- ✅ flex-grow、flex-shrink 控制伸縮
- ✅ flex: 1 讓元素平均分配空間
- ✅ gap 設定項目間距

## 🎯 課後練習

1. **基礎練習**：建立導覽列
   - 左側放標誌
   - 右側放選單項目（水平排列）
   - 所有項目垂直置中

2. **進階挑戰**：建立響應式卡片布局
   - 至少 6 張卡片
   - 使用 flex-wrap 自動換行
   - 卡片最小寬度 250px
   - 卡片之間有適當間距

3. **實戰練習**：建立完整頁面布局
   - header 固定在頂部
   - footer 固定在底部
   - main 內容區自動填滿中間
   - 使用 Flexbox 排列所有區塊

## 🔗 下一課預告

在下一課中，我們將學習 CSS Grid 布局，這是更強大的二維布局系統！

---

[← 上一課：文字和顏色樣式](./13-text-color-styling.md) | [返回目錄](../README.md) | [下一課：Grid 布局 →](./15-grid.md)
