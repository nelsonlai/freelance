# 第 17 課：CSS 動畫和過渡

## 📚 本課學習目標

- 掌握 CSS Transitions 的使用
- 學會建立 CSS Animations
- 了解 Transform 屬性
- 學會實作常見的動畫效果

## ⚡ CSS Transitions（過渡）

Transitions 讓CSS 屬性的變化變得平滑。

### 基本語法

```css
.element {
    transition: property duration timing-function delay;
}
```

### 範例

```css
button {
    background-color: #667eea;
    transition: background-color 0.3s ease;
}

button:hover {
    background-color: #5568d3;
}
```

### transition 屬性

```css
.box {
    /* 單一屬性 */
    transition-property: background-color;
    transition-duration: 0.3s;
    transition-timing-function: ease;
    transition-delay: 0.1s;
    
    /* 簡寫 */
    transition: background-color 0.3s ease 0.1s;
    
    /* 多個屬性 */
    transition: background-color 0.3s, transform 0.5s;
    
    /* 所有屬性 */
    transition: all 0.3s ease;
}
```

### timing-function（時間函數）

```css
transition-timing-function: ease;           /* 預設，慢-快-慢 */
transition-timing-function: linear;         /* 線性 */
transition-timing-function: ease-in;        /* 慢-快 */
transition-timing-function: ease-out;       /* 快-慢 */
transition-timing-function: ease-in-out;    /* 慢-快-慢 */
transition-timing-function: cubic-bezier(0.68, -0.55, 0.265, 1.55); /* 自訂 */
```

## 💻 實作練習 1：Transition 效果

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Transition 效果示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 40px;
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
        
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 30px;
            margin: 30px 0;
        }
        
        .card {
            background-color: white;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            text-align: center;
        }
        
        /* 範例 1：背景色變化 */
        .btn-1 {
            padding: 15px 30px;
            background-color: #667eea;
            color: white;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }
        
        .btn-1:hover {
            background-color: #5568d3;
        }
        
        /* 範例 2：大小變化 */
        .box-1 {
            width: 100px;
            height: 100px;
            background-color: #4ECDC4;
            margin: 20px auto;
            border-radius: 10px;
            transition: transform 0.3s ease;
        }
        
        .box-1:hover {
            transform: scale(1.2);
        }
        
        /* 範例 3：陰影變化 */
        .box-2 {
            width: 100px;
            height: 100px;
            background-color: #FFE66D;
            margin: 20px auto;
            border-radius: 10px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            transition: box-shadow 0.3s ease;
        }
        
        .box-2:hover {
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
        }
        
        /* 範例 4：位移 */
        .box-3 {
            width: 100px;
            height: 100px;
            background-color: #FF6B6B;
            margin: 20px auto;
            border-radius: 10px;
            transition: transform 0.3s ease;
        }
        
        .box-3:hover {
            transform: translateY(-10px);
        }
        
        /* 範例 5：旋轉 */
        .box-4 {
            width: 100px;
            height: 100px;
            background-color: #95E1D3;
            margin: 20px auto;
            border-radius: 10px;
            transition: transform 0.5s ease;
        }
        
        .box-4:hover {
            transform: rotate(45deg);
        }
        
        /* 範例 6：組合效果 */
        .box-5 {
            width: 100px;
            height: 100px;
            background-color: #667eea;
            margin: 20px auto;
            border-radius: 10px;
            transition: all 0.3s ease;
        }
        
        .box-5:hover {
            transform: scale(1.1) rotate(5deg);
            box-shadow: 0 10px 30px rgba(102, 126, 234, 0.4);
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>⚡ Transition 效果示範</h1>
        <p style="text-align: center;">移動滑鼠到元素上查看效果</p>
        
        <div class="grid">
            <div class="card">
                <h3>背景色變化</h3>
                <button class="btn-1">Hover me</button>
            </div>
            
            <div class="card">
                <h3>縮放</h3>
                <div class="box-1"></div>
            </div>
            
            <div class="card">
                <h3>陰影</h3>
                <div class="box-2"></div>
            </div>
            
            <div class="card">
                <h3>位移</h3>
                <div class="box-3"></div>
            </div>
            
            <div class="card">
                <h3>旋轉</h3>
                <div class="box-4"></div>
            </div>
            
            <div class="card">
                <h3>組合效果</h3>
                <div class="box-5"></div>
            </div>
        </div>
    </div>
</body>
</html>
```

## 🎬 Transform（變形）

Transform 可以移動、旋轉、縮放、傾斜元素。

### Transform 函數

```css
/* 位移 */
transform: translate(50px, 100px);    /* X, Y */
transform: translateX(50px);          /* X 軸 */
transform: translateY(100px);         /* Y 軸 */

/* 縮放 */
transform: scale(1.5);                /* 放大 1.5 倍 */
transform: scale(0.5);                /* 縮小 0.5 倍 */
transform: scaleX(2);                 /* X 軸縮放 */
transform: scaleY(0.5);               /* Y 軸縮放 */

/* 旋轉 */
transform: rotate(45deg);             /* 旋轉 45 度 */
transform: rotateX(45deg);            /* X 軸旋轉 */
transform: rotateY(45deg);            /* Y 軸旋轉 */

/* 傾斜 */
transform: skew(10deg, 20deg);        /* X, Y */
transform: skewX(10deg);              /* X 軸 */
transform: skewY(20deg);              /* Y 軸 */

/* 組合 */
transform: translate(50px, 100px) rotate(45deg) scale(1.5);
```

### transform-origin（變形原點）

```css
transform-origin: center;             /* 預設 */
transform-origin: top left;           /* 左上角 */
transform-origin: 50% 50%;           /* 中心點 */
transform-origin: 100px 50px;        /* 指定位置 */
```

## 🎨 CSS Animations（動畫）

Animations 可以建立複雜的動畫效果。

### 基本語法

```css
/* 定義動畫 */
@keyframes animationName {
    0% {
        opacity: 0;
    }
    100% {
        opacity: 1;
    }
}

/* 使用動畫 */
.element {
    animation: animationName 2s ease infinite;
}
```

### animation 屬性

```css
.element {
    animation-name: fade;
    animation-duration: 2s;
    animation-timing-function: ease;
    animation-delay: 0.5s;
    animation-iteration-count: 3;      /* 或 infinite */
    animation-direction: normal;       /* 或 reverse, alternate */
    animation-fill-mode: forwards;     /* 或 backwards, both */
    animation-play-state: running;     /* 或 paused */
    
    /* 簡寫 */
    animation: fade 2s ease 0.5s 3 normal forwards;
}
```

### @keyframes 寫法

```css
/* 方式 1：百分比 */
@keyframes slide {
    0% {
        transform: translateX(0);
    }
    50% {
        transform: translateX(100px);
    }
    100% {
        transform: translateX(0);
    }
}

/* 方式 2：from/to */
@keyframes fade {
    from {
        opacity: 0;
    }
    to {
        opacity: 1;
    }
}
```

## 💻 實作練習 2：動畫效果

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>CSS 動畫示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 40px;
            background-color: #f5f5f5;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        h1 {
            text-align: center;
            color: #667eea;
            animation: fadeIn 1s ease;
        }
        
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 30px;
            margin: 30px 0;
        }
        
        .card {
            background-color: white;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            text-align: center;
        }
        
        .animated-box {
            width: 100px;
            height: 100px;
            margin: 20px auto;
            border-radius: 10px;
        }
        
        /* 動畫 1：淡入 */
        @keyframes fadeIn {
            from {
                opacity: 0;
            }
            to {
                opacity: 1;
            }
        }
        
        .fade-box {
            background-color: #4ECDC4;
            animation: fadeIn 2s ease infinite alternate;
        }
        
        /* 動畫 2：彈跳 */
        @keyframes bounce {
            0%, 100% {
                transform: translateY(0);
            }
            50% {
                transform: translateY(-30px);
            }
        }
        
        .bounce-box {
            background-color: #FFE66D;
            animation: bounce 1s ease infinite;
        }
        
        /* 動畫 3：旋轉 */
        @keyframes rotate {
            from {
                transform: rotate(0deg);
            }
            to {
                transform: rotate(360deg);
            }
        }
        
        .rotate-box {
            background-color: #FF6B6B;
            animation: rotate 3s linear infinite;
        }
        
        /* 動畫 4：脈衝 */
        @keyframes pulse {
            0%, 100% {
                transform: scale(1);
            }
            50% {
                transform: scale(1.2);
            }
        }
        
        .pulse-box {
            background-color: #95E1D3;
            animation: pulse 1.5s ease infinite;
        }
        
        /* 動畫 5：搖擺 */
        @keyframes shake {
            0%, 100% {
                transform: translateX(0);
            }
            10%, 30%, 50%, 70%, 90% {
                transform: translateX(-10px);
            }
            20%, 40%, 60%, 80% {
                transform: translateX(10px);
            }
        }
        
        .shake-box {
            background-color: #667eea;
            animation: shake 0.8s ease infinite;
        }
        
        /* 動畫 6：漸層變化 */
        @keyframes colorChange {
            0% {
                background-color: #FF6B6B;
            }
            25% {
                background-color: #4ECDC4;
            }
            50% {
                background-color: #FFE66D;
            }
            75% {
                background-color: #95E1D3;
            }
            100% {
                background-color: #FF6B6B;
            }
        }
        
        .color-box {
            animation: colorChange 4s linear infinite;
        }
        
        /* 載入動畫 */
        @keyframes spin {
            from {
                transform: rotate(0deg);
            }
            to {
                transform: rotate(360deg);
            }
        }
        
        .loader {
            width: 50px;
            height: 50px;
            border: 5px solid #f3f3f3;
            border-top: 5px solid #667eea;
            border-radius: 50%;
            margin: 20px auto;
            animation: spin 1s linear infinite;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎨 CSS 動畫示範</h1>
        
        <div class="grid">
            <div class="card">
                <h3>淡入淡出</h3>
                <div class="animated-box fade-box"></div>
            </div>
            
            <div class="card">
                <h3>彈跳</h3>
                <div class="animated-box bounce-box"></div>
            </div>
            
            <div class="card">
                <h3>旋轉</h3>
                <div class="animated-box rotate-box"></div>
            </div>
            
            <div class="card">
                <h3>脈衝</h3>
                <div class="animated-box pulse-box"></div>
            </div>
            
            <div class="card">
                <h3>搖擺</h3>
                <div class="animated-box shake-box"></div>
            </div>
            
            <div class="card">
                <h3>顏色變化</h3>
                <div class="animated-box color-box"></div>
            </div>
        </div>
        
        <div class="card">
            <h3>載入動畫</h3>
            <div class="loader"></div>
        </div>
    </div>
</body>
</html>
```

## 🌟 實用動畫範例

### 1. 按鈕點擊效果

```css
.button {
    transition: transform 0.1s;
}

.button:active {
    transform: scale(0.95);
}
```

### 2. 卡片翻轉

```css
.card {
    transition: transform 0.6s;
    transform-style: preserve-3d;
}

.card:hover {
    transform: rotateY(180deg);
}
```

### 3. 載入動畫

```css
@keyframes loading {
    0%, 100% {
        transform: scale(0);
    }
    50% {
        transform: scale(1);
    }
}

.dot {
    animation: loading 1.4s infinite ease-in-out;
}
```

## 📝 本課重點回顧

- ✅ Transition 讓屬性變化平滑
- ✅ Transform 可以移動、旋轉、縮放元素
- ✅ Animation 建立複雜的動畫效果
- ✅ @keyframes 定義動畫步驟
- ✅ timing-function 控制動畫速度曲線
- ✅ 使用 all 可以過渡所有屬性
- ✅ infinite 讓動畫無限循環

## 🎯 課後練習

1. **基礎練習**：按鈕動畫
   - 建立一個按鈕
   - hover 時改變背景色和大小
   - active 時有按下效果
   - 加入適當的 transition

2. **進階挑戰**：卡片動畫
   - 建立多張卡片
   - hover 時卡片上浮並顯示陰影
   - 卡片內容淡入
   - 使用 transform 和 transition

3. **實戰練習**：載入動畫
   - 建立一個載入指示器
   - 使用 @keyframes 建立旋轉動畫
   - 加入彈跳效果
   - 建立多種不同風格的載入動畫

## 🔗 下一課預告

在最後一課中，我們將學習 CSS 的進階技巧，包括變數、Flex/Grid 進階應用等！

---

[← 上一課：響應式設計](./16-responsive-design.md) | [返回目錄](../README.md) | [下一課：CSS 進階技巧 →](./18-css-advanced.md)
