# 第 13 課：文字和顏色樣式

## 📚 本課學習目標

- 掌握文字相關的 CSS 屬性
- 學會使用各種字體
- 了解顏色和漸層的應用
- 學會文字和盒子陰影效果

## 🔤 字體屬性

### font-family（字體系列）

```css
p {
    /* 單一字體 */
    font-family: Arial;
    
    /* 備用字體（fallback） */
    font-family: Arial, Helvetica, sans-serif;
    
    /* 包含空格的字體需要引號 */
    font-family: "Times New Roman", Times, serif;
    
    /* 中文字體 */
    font-family: "Microsoft JhengHei", "微軟正黑體", Arial, sans-serif;
}
```

**字體分類：**
- `serif`：襯線字體（如 Times New Roman）
- `sans-serif`：無襯線字體（如 Arial）
- `monospace`：等寬字體（如 Courier）
- `cursive`：草書字體
- `fantasy`：裝飾字體

### font-size（字體大小）

```css
p {
    font-size: 16px;      /* 像素（最常用） */
    font-size: 1em;       /* 相對於父元素 */
    font-size: 1.2rem;    /* 相對於根元素 */
    font-size: 100%;      /* 百分比 */
    font-size: larger;    /* 相對大小 */
}
```

### font-weight（字體粗細）

```css
p {
    font-weight: normal;   /* 正常（400） */
    font-weight: bold;     /* 粗體（700） */
    font-weight: bolder;   /* 更粗 */
    font-weight: lighter;  /* 更細 */
    font-weight: 100;      /* 100-900 的數字 */
}
```

### font-style（字體樣式）

```css
p {
    font-style: normal;   /* 正常 */
    font-style: italic;   /* 斜體 */
    font-style: oblique;  /* 傾斜 */
}
```

### font 簡寫

```css
p {
    /* font: style weight size/line-height family */
    font: italic bold 16px/1.6 Arial, sans-serif;
}
```

## 📝 文字屬性

### text-align（文字對齊）

```css
p {
    text-align: left;      /* 靠左（預設） */
    text-align: right;     /* 靠右 */
    text-align: center;    /* 置中 */
    text-align: justify;   /* 兩端對齊 */
}
```

### text-decoration（文字裝飾）

```css
a {
    text-decoration: none;              /* 無裝飾 */
    text-decoration: underline;         /* 底線 */
    text-decoration: overline;          /* 上劃線 */
    text-decoration: line-through;      /* 刪除線 */
    text-decoration: underline wavy red; /* 樣式 */
}
```

### text-transform（文字轉換）

```css
p {
    text-transform: none;        /* 正常 */
    text-transform: uppercase;   /* 全部大寫 */
    text-transform: lowercase;   /* 全部小寫 */
    text-transform: capitalize;  /* 首字母大寫 */
}
```

### line-height（行高）

```css
p {
    line-height: 1.6;      /* 無單位（推薦） */
    line-height: 24px;     /* 固定值 */
    line-height: 150%;     /* 百分比 */
}
```

### letter-spacing（字母間距）

```css
p {
    letter-spacing: normal;  /* 正常 */
    letter-spacing: 2px;     /* 正值增加間距 */
    letter-spacing: -1px;    /* 負值減少間距 */
}
```

### word-spacing（單字間距）

```css
p {
    word-spacing: 5px;
}
```

### text-indent（首行縮排）

```css
p {
    text-indent: 2em;    /* 縮排兩個字元 */
}
```

### white-space（空白處理）

```css
p {
    white-space: normal;   /* 正常（摺疊空白） */
    white-space: nowrap;   /* 不換行 */
    white-space: pre;      /* 保留空白和換行 */
    white-space: pre-wrap; /* 保留空白但自動換行 */
}
```

## 💻 實作練習 1：文字樣式

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>文字樣式示範</title>
    <style>
        body {
            font-family: 'Microsoft JhengHei', Arial, sans-serif;
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
        }
        
        h1 {
            font-size: 48px;
            font-weight: bold;
            text-align: center;
            color: #667eea;
            margin-bottom: 40px;
        }
        
        h2 {
            font-size: 32px;
            color: #764ba2;
            margin: 30px 0 15px;
            border-bottom: 3px solid #667eea;
            padding-bottom: 10px;
        }
        
        .demo-box {
            background-color: #f9f9f9;
            padding: 20px;
            margin: 15px 0;
            border-radius: 5px;
            border-left: 4px solid #4ECDC4;
        }
        
        .large-text {
            font-size: 24px;
        }
        
        .small-text {
            font-size: 14px;
        }
        
        .bold-text {
            font-weight: bold;
        }
        
        .italic-text {
            font-style: italic;
        }
        
        .uppercase {
            text-transform: uppercase;
        }
        
        .capitalize {
            text-transform: capitalize;
        }
        
        .underline {
            text-decoration: underline;
        }
        
        .line-through {
            text-decoration: line-through;
        }
        
        .center {
            text-align: center;
        }
        
        .right {
            text-align: right;
        }
        
        .justify {
            text-align: justify;
        }
        
        .wide-spacing {
            letter-spacing: 3px;
        }
        
        .tight-spacing {
            letter-spacing: -1px;
        }
        
        .tall-line {
            line-height: 2;
        }
        
        .indent {
            text-indent: 2em;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>文字樣式示範</h1>
        
        <h2>字體大小</h2>
        <div class="demo-box large-text">
            這是大字體（24px）
        </div>
        <div class="demo-box">
            這是正常字體（預設）
        </div>
        <div class="demo-box small-text">
            這是小字體（14px）
        </div>
        
        <h2>字體粗細與樣式</h2>
        <div class="demo-box bold-text">
            這是粗體文字
        </div>
        <div class="demo-box italic-text">
            這是斜體文字
        </div>
        
        <h2>文字轉換</h2>
        <div class="demo-box uppercase">
            This text is uppercase
        </div>
        <div class="demo-box capitalize">
            this text is capitalized
        </div>
        
        <h2>文字裝飾</h2>
        <div class="demo-box underline">
            這是有底線的文字
        </div>
        <div class="demo-box line-through">
            這是有刪除線的文字
        </div>
        
        <h2>文字對齊</h2>
        <div class="demo-box">
            這是靠左對齊（預設）
        </div>
        <div class="demo-box center">
            這是置中對齊
        </div>
        <div class="demo-box right">
            這是靠右對齊
        </div>
        <div class="demo-box justify">
            這是兩端對齊的範例。當文字很長時，
            兩端對齊會讓文字均勻分布在整行中，
            使左右兩邊都對齊。這在印刷品中很常見。
        </div>
        
        <h2>字母間距</h2>
        <div class="demo-box wide-spacing">
            這 是 寬 間 距
        </div>
        <div class="demo-box tight-spacing">
            這是緊密間距
        </div>
        
        <h2>行高</h2>
        <div class="demo-box tall-line">
            這段文字有較高的行高。
            當有多行文字時，
            行高會影響行與行之間的距離。
            較大的行高可以提升閱讀體驗。
        </div>
        
        <h2>首行縮排</h2>
        <div class="demo-box indent">
            這段文字的第一行會縮排兩個字元。
            這在傳統的排版中很常見，
            特別是在段落開頭時使用。
        </div>
    </div>
</body>
</html>
```

## 🎨 顏色設定

### color（文字顏色）

```css
p {
    color: red;                    /* 顏色名稱 */
    color: #FF0000;               /* 十六進位 */
    color: rgb(255, 0, 0);        /* RGB */
    color: rgba(255, 0, 0, 0.5);  /* RGBA（有透明度） */
    color: hsl(0, 100%, 50%);     /* HSL */
}
```

### 背景顏色

```css
div {
    background-color: #f5f5f5;
    background-color: rgba(0, 0, 0, 0.1);
}
```

### 漸層背景

```css
/* 線性漸層 */
div {
    background: linear-gradient(to right, #667eea, #764ba2);
    background: linear-gradient(45deg, red, yellow, green);
    background: linear-gradient(to bottom, rgba(0,0,0,0), rgba(0,0,0,1));
}

/* 放射漸層 */
div {
    background: radial-gradient(circle, #667eea, #764ba2);
    background: radial-gradient(ellipse at top, red, yellow);
}
```

## ✨ 陰影效果

### text-shadow（文字陰影）

```css
h1 {
    /* x偏移 y偏移 模糊 顏色 */
    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3);
    
    /* 多重陰影 */
    text-shadow: 
        2px 2px 4px rgba(0, 0, 0, 0.3),
        -2px -2px 4px rgba(255, 255, 255, 0.8);
}
```

### box-shadow（盒子陰影）

```css
div {
    /* x偏移 y偏移 模糊 擴散 顏色 */
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
    
    /* 內陰影 */
    box-shadow: inset 0 0 10px rgba(0, 0, 0, 0.5);
    
    /* 多重陰影 */
    box-shadow: 
        0 2px 5px rgba(0, 0, 0, 0.1),
        0 10px 40px rgba(0, 0, 0, 0.2);
}
```

## 💻 實作練習 2：顏色和陰影

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>顏色和陰影示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 40px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
        }
        
        .container {
            max-width: 1000px;
            margin: 0 auto;
        }
        
        h1 {
            color: white;
            text-align: center;
            font-size: 48px;
            text-shadow: 3px 3px 6px rgba(0, 0, 0, 0.5);
            margin-bottom: 40px;
        }
        
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin: 30px 0;
        }
        
        .card {
            background-color: white;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            transition: transform 0.3s, box-shadow 0.3s;
        }
        
        .card:hover {
            transform: translateY(-10px);
            box-shadow: 0 20px 40px rgba(0, 0, 0, 0.3);
        }
        
        .card h2 {
            color: #667eea;
            margin-bottom: 15px;
        }
        
        /* 文字陰影範例 */
        .text-shadow-1 {
            font-size: 32px;
            color: #333;
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3);
        }
        
        .text-shadow-2 {
            font-size: 32px;
            color: white;
            text-shadow: 
                2px 2px 0 #667eea,
                4px 4px 0 #764ba2;
        }
        
        .text-shadow-3 {
            font-size: 32px;
            color: white;
            text-shadow: 0 0 10px rgba(102, 126, 234, 0.8);
        }
        
        /* 盒子陰影範例 */
        .box-shadow-1 {
            background-color: #FFE66D;
            padding: 20px;
            margin: 15px 0;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
        }
        
        .box-shadow-2 {
            background-color: #95E1D3;
            padding: 20px;
            margin: 15px 0;
            border-radius: 10px;
            box-shadow: 0 10px 40px rgba(0, 0, 0, 0.2);
        }
        
        .box-shadow-3 {
            background-color: #FF6B6B;
            color: white;
            padding: 20px;
            margin: 15px 0;
            border-radius: 10px;
            box-shadow: inset 0 0 20px rgba(0, 0, 0, 0.3);
        }
        
        /* 漸層背景範例 */
        .gradient-1 {
            background: linear-gradient(to right, #667eea, #764ba2);
            color: white;
            padding: 30px;
            margin: 15px 0;
            border-radius: 10px;
            text-align: center;
            font-size: 20px;
        }
        
        .gradient-2 {
            background: linear-gradient(45deg, #FF6B6B, #FFE66D);
            color: white;
            padding: 30px;
            margin: 15px 0;
            border-radius: 10px;
            text-align: center;
            font-size: 20px;
        }
        
        .gradient-3 {
            background: radial-gradient(circle, #4ECDC4, #38A3A5);
            color: white;
            padding: 30px;
            margin: 15px 0;
            border-radius: 10px;
            text-align: center;
            font-size: 20px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎨 顏色和陰影示範</h1>
        
        <div class="grid">
            <div class="card">
                <h2>文字陰影 1</h2>
                <p class="text-shadow-1">基本陰影</p>
            </div>
            
            <div class="card">
                <h2>文字陰影 2</h2>
                <p class="text-shadow-2">多層陰影</p>
            </div>
            
            <div class="card">
                <h2>文字陰影 3</h2>
                <p class="text-shadow-3">發光效果</p>
            </div>
        </div>
        
        <div class="card">
            <h2>盒子陰影範例</h2>
            
            <div class="box-shadow-1">
                淺陰影效果
            </div>
            
            <div class="box-shadow-2">
                深陰影效果
            </div>
            
            <div class="box-shadow-3">
                內陰影效果
            </div>
        </div>
        
        <div class="card">
            <h2>漸層背景範例</h2>
            
            <div class="gradient-1">
                線性漸層 - 水平
            </div>
            
            <div class="gradient-2">
                線性漸層 - 45度
            </div>
            
            <div class="gradient-3">
                放射漸層
            </div>
        </div>
    </div>
</body>
</html>
```

## 🌈 配色建議

### 常用配色方案

```css
/* 藍色系 */
--primary: #667eea;
--secondary: #764ba2;

/* 綠色系 */
--success: #4ECDC4;
--info: #95E1D3;

/* 警告色系 */
--warning: #FFE66D;
--danger: #FF6B6B;

/* 中性色系 */
--dark: #333333;
--gray: #666666;
--light: #f5f5f5;
```

## 📝 本課重點回顧

- ✅ font-family 設定字體，建議提供備用字體
- ✅ font-size、font-weight、font-style 控制字體樣式
- ✅ text-align 控制文字對齊方式
- ✅ line-height 影響行高和可讀性
- ✅ text-shadow 和 box-shadow 建立陰影效果
- ✅ linear-gradient 和 radial-gradient 建立漸層背景
- ✅ rgba 可設定透明度

## 🎯 課後練習

1. **基礎練習**：文字排版
   - 建立一篇文章頁面
   - 設定標題、段落的字體和大小
   - 調整行高提升可讀性
   - 加入文字陰影

2. **進階挑戰**：建立英雄橫幅（Hero Banner）
   - 使用漸層背景
   - 加入大標題和副標題
   - 使用文字陰影增加層次
   - 加入按鈕並設定 hover 效果

3. **實戰練習**：建立名片設計
   - 使用各種文字樣式
   - 套用配色方案
   - 加入盒子陰影
   - 使用漸層或特殊效果

## 🔗 下一課預告

在下一課中，我們將學習 Flexbox 布局，這是現代 CSS 布局的強大工具，讓元素排列變得更簡單！

---

[← 上一課：盒模型和布局基礎](./12-box-model.md) | [返回目錄](../README.md) | [下一課：Flexbox 布局 →](./14-flexbox.md)
