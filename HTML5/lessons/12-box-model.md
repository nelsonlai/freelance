# 第 12 課：盒模型和布局基礎

## 📚 本課學習目標

- 理解 CSS 盒模型的概念
- 掌握 margin、padding、border 的使用
- 學會控制元素的尺寸
- 了解 display 屬性的不同值

## 📦 CSS 盒模型（Box Model）

每個 HTML 元素都可以看作一個「盒子」，由以下部分組成：

```
┌────────────────────────────────┐
│         Margin（外邊距）        │
│  ┌──────────────────────────┐  │
│  │    Border（邊框）         │  │
│  │  ┌────────────────────┐  │  │
│  │  │  Padding（內邊距）  │  │  │
│  │  │  ┌──────────────┐  │  │  │
│  │  │  │   Content    │  │  │  │
│  │  │  │   （內容）    │  │  │  │
│  │  │  └──────────────┘  │  │  │
│  │  └────────────────────┘  │  │
│  └──────────────────────────┘  │
└────────────────────────────────┘
```

### 盒模型的組成

1. **Content（內容）**：實際的文字或圖片內容
2. **Padding（內邊距）**：內容與邊框之間的空間
3. **Border（邊框）**：圍繞在 padding 外的邊框線
4. **Margin（外邊距）**：元素與其他元素之間的空間

## 📏 寬度和高度

### 設定尺寸

```css
div {
    width: 300px;      /* 寬度 */
    height: 200px;     /* 高度 */
    max-width: 500px;  /* 最大寬度 */
    min-height: 100px; /* 最小高度 */
}
```

### box-sizing 屬性

決定寬高的計算方式：

```css
/* 預設值：寬高只包含 content */
.box1 {
    box-sizing: content-box;
    width: 300px;
    padding: 20px;
    border: 5px solid black;
    /* 實際寬度 = 300 + 20*2 + 5*2 = 350px */
}

/* 推薦：寬高包含 padding 和 border */
.box2 {
    box-sizing: border-box;
    width: 300px;
    padding: 20px;
    border: 5px solid black;
    /* 實際寬度 = 300px */
}
```

**全域設定（推薦）：**

```css
* {
    box-sizing: border-box;
}
```

## 🎨 Padding（內邊距）

內容與邊框之間的空間：

```css
/* 四邊相同 */
div {
    padding: 20px;
}

/* 上下、左右 */
div {
    padding: 10px 20px;
}

/* 上、左右、下 */
div {
    padding: 10px 20px 30px;
}

/* 上、右、下、左（順時針） */
div {
    padding: 10px 20px 30px 40px;
}

/* 單獨設定 */
div {
    padding-top: 10px;
    padding-right: 20px;
    padding-bottom: 30px;
    padding-left: 40px;
}
```

## 🔲 Border（邊框）

### 基本邊框

```css
div {
    border: 2px solid #333;
    /* 寬度 樣式 顏色 */
}
```

### 邊框樣式

```css
border-style: solid;    /* 實線 */
border-style: dashed;   /* 虛線 */
border-style: dotted;   /* 點線 */
border-style: double;   /* 雙線 */
border-style: groove;   /* 凹槽 */
border-style: ridge;    /* 山脊 */
border-style: inset;    /* 內嵌 */
border-style: outset;   /* 外凸 */
```

### 單獨設定邊框

```css
div {
    border-top: 3px solid red;
    border-right: 2px dashed blue;
    border-bottom: 1px dotted green;
    border-left: 4px solid orange;
}

/* 或分開設定 */
div {
    border-width: 2px;
    border-style: solid;
    border-color: #333;
}
```

### 圓角邊框

```css
/* 四個角相同 */
div {
    border-radius: 10px;
}

/* 左上、右上、右下、左下 */
div {
    border-radius: 10px 20px 30px 40px;
}

/* 橢圓形圓角 */
div {
    border-radius: 50px / 25px;
}

/* 圓形 */
div {
    width: 100px;
    height: 100px;
    border-radius: 50%;
}

/* 單獨設定 */
div {
    border-top-left-radius: 10px;
    border-top-right-radius: 20px;
    border-bottom-right-radius: 30px;
    border-bottom-left-radius: 40px;
}
```

## 💻 實作練習 1：盒模型示範

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 盒模型示範</title>
    <style>
        * {
            box-sizing: border-box;
        }
        
        body {
            font-family: Arial, sans-serif;
            padding: 40px;
            background-color: #f5f5f5;
        }
        
        h1 {
            text-align: center;
            color: #667eea;
        }
        
        .container {
            max-width: 1000px;
            margin: 0 auto;
        }
        
        .box {
            background-color: #FFE66D;
            border: 5px solid #333;
            padding: 30px;
            margin: 20px;
            width: 300px;
        }
        
        .box-diagram {
            display: flex;
            justify-content: center;
            margin: 40px 0;
        }
        
        .demo-box {
            background-color: #95E1D3;
            border: 10px solid #38A3A5;
            padding: 40px;
            margin: 30px;
            position: relative;
        }
        
        .content {
            background-color: #FF6B6B;
            color: white;
            padding: 20px;
            text-align: center;
        }
        
        .label {
            position: absolute;
            font-size: 14px;
            font-weight: bold;
        }
        
        .rounded {
            border-radius: 20px;
        }
        
        .circle {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            margin: 20px auto;
        }
        
        .border-styles {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 20px;
            margin: 30px 0;
        }
        
        .border-demo {
            padding: 20px;
            text-align: center;
            background-color: white;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>📦 CSS 盒模型示範</h1>
        
        <h2>基本盒模型</h2>
        <div class="box">
            這個盒子有：
            <ul>
                <li>背景色：content 區域</li>
                <li>內邊距：padding: 30px</li>
                <li>邊框：border: 5px solid</li>
                <li>外邊距：margin: 20px</li>
            </ul>
        </div>
        
        <h2>盒模型結構示意</h2>
        <div class="box-diagram">
            <div class="demo-box">
                <div class="content">
                    Content<br>內容區
                </div>
            </div>
        </div>
        
        <h2>圓角邊框</h2>
        <div class="box rounded">
            使用 border-radius: 20px 建立圓角
        </div>
        
        <div class="box circle">
            圓形
        </div>
        
        <h2>各種邊框樣式</h2>
        <div class="border-styles">
            <div class="border-demo" style="border: 3px solid #333;">
                solid<br>實線
            </div>
            <div class="border-demo" style="border: 3px dashed #333;">
                dashed<br>虛線
            </div>
            <div class="border-demo" style="border: 3px dotted #333;">
                dotted<br>點線
            </div>
            <div class="border-demo" style="border: 5px double #333;">
                double<br>雙線
            </div>
            <div class="border-demo" style="border: 5px groove #333;">
                groove<br>凹槽
            </div>
            <div class="border-demo" style="border: 5px ridge #333;">
                ridge<br>山脊
            </div>
        </div>
    </div>
</body>
</html>
```

## 📐 Margin（外邊距）

元素與其他元素之間的空間：

```css
/* 四邊相同 */
div {
    margin: 20px;
}

/* 上下、左右 */
div {
    margin: 10px 20px;
}

/* 上、右、下、左 */
div {
    margin: 10px 20px 30px 40px;
}

/* 單獨設定 */
div {
    margin-top: 10px;
    margin-right: 20px;
    margin-bottom: 30px;
    margin-left: 40px;
}

/* 水平置中 */
div {
    width: 300px;
    margin: 0 auto;
}

/* 負值（重疊） */
div {
    margin-top: -10px;
}
```

### Margin 合併（Collapsing）

垂直方向的 margin 會合併，取較大值：

```html
<style>
    .box1 {
        margin-bottom: 30px;
    }
    
    .box2 {
        margin-top: 20px;
    }
    /* 實際間距是 30px（不是 50px） */
</style>

<div class="box1">盒子1</div>
<div class="box2">盒子2</div>
```

## 📺 Display 屬性

控制元素的顯示類型：

### 主要值

```css
/* 區塊元素（佔滿整行） */
display: block;

/* 行內元素（不換行） */
display: inline;

/* 行內區塊（結合兩者優點） */
display: inline-block;

/* 不顯示 */
display: none;

/* Flexbox */
display: flex;

/* Grid */
display: grid;
```

### block vs inline vs inline-block

```html
<style>
    .block {
        display: block;
        width: 200px;
        height: 100px;
        background-color: #FF6B6B;
        margin: 10px;
    }
    
    .inline {
        display: inline;
        width: 200px;      /* 無效 */
        height: 100px;     /* 無效 */
        background-color: #4ECDC4;
        margin: 10px;
    }
    
    .inline-block {
        display: inline-block;
        width: 200px;      /* 有效 */
        height: 100px;     /* 有效 */
        background-color: #95E1D3;
        margin: 10px;
    }
</style>

<div class="block">Block（佔滿整行）</div>
<div class="block">Block 2</div>

<span class="inline">Inline</span>
<span class="inline">Inline（並排，無法設定寬高）</span>

<div class="inline-block">Inline-block</div>
<div class="inline-block">Inline-block（並排，可設寬高）</div>
```

## 👁️ Visibility 和 Display 的差別

```css
/* 不顯示，不佔空間 */
display: none;

/* 隱藏，但仍佔空間 */
visibility: hidden;

/* 顯示 */
visibility: visible;
```

## 💻 實作練習 2：布局基礎

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>布局基礎練習</title>
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
            max-width: 1200px;
            margin: 0 auto;
            background-color: white;
            padding: 30px;
            border-radius: 10px;
        }
        
        h1 {
            color: #667eea;
            text-align: center;
            margin-bottom: 40px;
        }
        
        h2 {
            color: #764ba2;
            margin: 30px 0 15px;
            padding-bottom: 10px;
            border-bottom: 2px solid #667eea;
        }
        
        /* Block 示範 */
        .block-demo div {
            background-color: #FF6B6B;
            color: white;
            padding: 15px;
            margin: 10px 0;
            border-radius: 5px;
        }
        
        /* Inline 示範 */
        .inline-demo span {
            background-color: #4ECDC4;
            color: white;
            padding: 5px 10px;
            margin: 5px;
            border-radius: 3px;
        }
        
        /* Inline-block 示範 */
        .inline-block-demo .box {
            display: inline-block;
            width: 150px;
            height: 150px;
            background-color: #95E1D3;
            margin: 10px;
            padding: 20px;
            border-radius: 10px;
            vertical-align: top;
        }
        
        /* 卡片範例 */
        .card {
            background-color: white;
            border: 1px solid #ddd;
            border-radius: 10px;
            padding: 20px;
            margin: 20px 0;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
        
        .card h3 {
            color: #667eea;
            margin-bottom: 10px;
        }
        
        .card p {
            color: #666;
            line-height: 1.6;
        }
        
        /* 置中範例 */
        .centered-box {
            width: 300px;
            margin: 20px auto;
            padding: 20px;
            background-color: #FFE66D;
            text-align: center;
            border-radius: 10px;
        }
        
        /* 按鈕範例 */
        .btn {
            display: inline-block;
            padding: 12px 30px;
            background-color: #667eea;
            color: white;
            text-decoration: none;
            border-radius: 25px;
            margin: 5px;
        }
        
        .btn:hover {
            background-color: #5568d3;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>CSS 布局基礎</h1>
        
        <h2>1. Block 元素（佔滿整行）</h2>
        <div class="block-demo">
            <div>第一個區塊</div>
            <div>第二個區塊</div>
            <div>第三個區塊</div>
        </div>
        
        <h2>2. Inline 元素（並排顯示）</h2>
        <div class="inline-demo">
            <span>標籤1</span>
            <span>標籤2</span>
            <span>標籤3</span>
            <span>標籤4</span>
            <span>標籤5</span>
        </div>
        
        <h2>3. Inline-block 元素（並排且可設定寬高）</h2>
        <div class="inline-block-demo">
            <div class="box">盒子1<br>150x150</div>
            <div class="box">盒子2<br>150x150</div>
            <div class="box">盒子3<br>150x150</div>
        </div>
        
        <h2>4. 卡片佈局</h2>
        <div class="card">
            <h3>卡片標題</h3>
            <p>這是一個卡片元件，使用了 padding、margin、border 和 box-shadow。</p>
        </div>
        
        <h2>5. 水平置中</h2>
        <div class="centered-box">
            這個盒子使用 margin: 0 auto 水平置中
        </div>
        
        <h2>6. 按鈕組</h2>
        <div style="text-align: center;">
            <a href="#" class="btn">按鈕 1</a>
            <a href="#" class="btn">按鈕 2</a>
            <a href="#" class="btn">按鈕 3</a>
        </div>
    </div>
</body>
</html>
```

## 🎯 實用技巧

### 1. 重置預設樣式

```css
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}
```

### 2. 水平置中

```css
.container {
    width: 80%;
    max-width: 1200px;
    margin: 0 auto;
}
```

### 3. 垂直置中（單行文字）

```css
div {
    height: 50px;
    line-height: 50px;
}
```

### 4. 清除浮動

```css
.clearfix::after {
    content: "";
    display: block;
    clear: both;
}
```

## 📝 本課重點回顧

- ✅ CSS 盒模型包含：content、padding、border、margin
- ✅ 使用 `box-sizing: border-box` 讓寬高包含 padding 和 border
- ✅ padding 控制內邊距，margin 控制外邊距
- ✅ border 可設定樣式、寬度、顏色
- ✅ border-radius 建立圓角
- ✅ display 控制元素顯示類型：block、inline、inline-block
- ✅ margin 可以用 `0 auto` 實現水平置中

## 🎯 課後練習

1. **基礎練習**：建立個人名片
   - 設定固定寬度並水平置中
   - 使用 padding 和 border
   - 加入圓角和陰影效果

2. **進階挑戰**：建立三欄布局
   - 使用 inline-block 建立三個並排的欄位
   - 每個欄位有邊框、內距和外距
   - 包含標題和內容

3. **實戰練習**：建立產品卡片
   - 建立多個產品卡片（至少3個）
   - 使用 inline-block 讓卡片並排
   - 包含圖片、標題、價格、按鈕
   - 加入 hover 效果

## 🔗 下一課預告

在下一課中，我們將學習文字和顏色樣式，包括字體設定、文字對齊、陰影效果等！

---

[← 上一課：選擇器和特異性](./11-selectors-specificity.md) | [返回目錄](../README.md) | [下一課：文字和顏色樣式 →](./13-text-color-styling.md)
