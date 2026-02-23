# 第 9 課：HTML5 新功能

## 📚 本課學習目標

- 了解 HTML5 引入的新功能
- 學會使用 Canvas 繪圖
- 認識 SVG 向量圖形
- 掌握本地儲存和其他 API

## 🎨 Canvas 繪圖

`<canvas>` 元素提供一個畫布，可以使用 JavaScript 在上面繪製圖形。

### 基本設置

```html
<canvas id="myCanvas" width="400" height="300" style="border: 1px solid #000;">
    您的瀏覽器不支援 Canvas
</canvas>

<script>
    // 取得 canvas 元素
    const canvas = document.getElementById('myCanvas');
    const ctx = canvas.getContext('2d');
    
    // 繪製矩形
    ctx.fillStyle = '#FF0000';
    ctx.fillRect(50, 50, 150, 100);
    
    // 繪製圓形
    ctx.beginPath();
    ctx.arc(300, 100, 50, 0, 2 * Math.PI);
    ctx.fillStyle = '#0000FF';
    ctx.fill();
</script>
```

### Canvas 基本繪圖範例

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Canvas 繪圖範例</title>
    <style>
        canvas {
            border: 2px solid #333;
            display: block;
            margin: 20px auto;
        }
    </style>
</head>
<body>
    <h2 style="text-align: center;">Canvas 繪圖示範</h2>
    
    <canvas id="myCanvas" width="600" height="400"></canvas>
    
    <script>
        const canvas = document.getElementById('myCanvas');
        const ctx = canvas.getContext('2d');
        
        // 繪製填滿的矩形
        ctx.fillStyle = '#FF6B6B';
        ctx.fillRect(50, 50, 150, 100);
        
        // 繪製邊框矩形
        ctx.strokeStyle = '#4ECDC4';
        ctx.lineWidth = 3;
        ctx.strokeRect(250, 50, 150, 100);
        
        // 繪製圓形
        ctx.beginPath();
        ctx.arc(125, 250, 60, 0, 2 * Math.PI);
        ctx.fillStyle = '#95E1D3';
        ctx.fill();
        ctx.strokeStyle = '#38A3A5';
        ctx.lineWidth = 2;
        ctx.stroke();
        
        // 繪製線條
        ctx.beginPath();
        ctx.moveTo(250, 200);
        ctx.lineTo(350, 280);
        ctx.lineTo(450, 200);
        ctx.strokeStyle = '#F38181';
        ctx.lineWidth = 4;
        ctx.stroke();
        
        // 繪製文字
        ctx.font = '30px Arial';
        ctx.fillStyle = '#333';
        ctx.fillText('Hello Canvas!', 200, 350);
    </script>
</body>
</html>
```

### Canvas 用途

- 🎮 遊戲開發
- 📊 資料視覺化
- 🎨 圖像處理
- 📈 圖表繪製
- ✏️ 手寫簽名

## 🖼️ SVG 向量圖形

**SVG（Scalable Vector Graphics）**是基於 XML 的向量圖形格式，可以無限縮放而不失真。

### 內嵌 SVG

```html
<svg width="200" height="200">
    <!-- 圓形 -->
    <circle cx="100" cy="100" r="80" fill="#4ECDC4" />
    
    <!-- 矩形 -->
    <rect x="50" y="50" width="100" height="100" fill="#FF6B6B" opacity="0.5" />
</svg>
```

### SVG 基本圖形

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>SVG 圖形範例</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
        }
        .svg-container {
            margin: 20px 0;
            padding: 20px;
            background-color: #f5f5f5;
            border-radius: 5px;
        }
        h3 {
            color: #333;
        }
    </style>
</head>
<body>
    <h2>SVG 圖形示範</h2>
    
    <div class="svg-container">
        <h3>基本圖形</h3>
        <svg width="400" height="200">
            <!-- 圓形 -->
            <circle cx="50" cy="50" r="40" fill="#FF6B6B" />
            
            <!-- 橢圓 -->
            <ellipse cx="150" cy="50" rx="60" ry="40" fill="#4ECDC4" />
            
            <!-- 矩形 -->
            <rect x="230" y="10" width="80" height="80" fill="#95E1D3" />
            
            <!-- 圓角矩形 -->
            <rect x="330" y="10" width="60" height="80" rx="10" ry="10" fill="#F38181" />
            
            <!-- 線條 -->
            <line x1="10" y1="120" x2="390" y2="120" stroke="#333" stroke-width="2" />
            
            <!-- 折線 -->
            <polyline points="50,150 100,180 150,140 200,170 250,130" 
                      fill="none" stroke="#FF6B6B" stroke-width="3" />
            
            <!-- 多邊形 -->
            <polygon points="350,150 330,180 360,190 380,180" fill="#95E1D3" />
        </svg>
    </div>
    
    <div class="svg-container">
        <h3>漸層和效果</h3>
        <svg width="400" height="200">
            <defs>
                <!-- 定義線性漸層 -->
                <linearGradient id="grad1" x1="0%" y1="0%" x2="100%" y2="0%">
                    <stop offset="0%" style="stop-color:#FF6B6B;stop-opacity:1" />
                    <stop offset="100%" style="stop-color:#4ECDC4;stop-opacity:1" />
                </linearGradient>
                
                <!-- 定義放射漸層 -->
                <radialGradient id="grad2">
                    <stop offset="0%" style="stop-color:#FFE66D;stop-opacity:1" />
                    <stop offset="100%" style="stop-color:#FF6B6B;stop-opacity:1" />
                </radialGradient>
            </defs>
            
            <!-- 使用漸層 -->
            <rect x="20" y="20" width="150" height="100" fill="url(#grad1)" />
            <circle cx="280" cy="70" r="50" fill="url(#grad2)" />
        </svg>
    </div>
    
    <div class="svg-container">
        <h3>文字和路徑</h3>
        <svg width="400" height="150">
            <!-- 文字 -->
            <text x="20" y="40" font-family="Arial" font-size="30" fill="#333">
                SVG 文字
            </text>
            
            <!-- 曲線路徑 -->
            <path d="M 50 100 Q 150 50 250 100 T 450 100" 
                  stroke="#4ECDC4" 
                  stroke-width="3" 
                  fill="none" />
        </svg>
    </div>
</body>
</html>
```

### SVG vs Canvas

| 特性 | SVG | Canvas |
|------|-----|--------|
| 類型 | 向量圖形 | 點陣圖形 |
| 縮放 | 無限縮放不失真 | 放大會模糊 |
| 效能 | 元素少時較好 | 元素多時較好 |
| 互動 | 每個元素可單獨操作 | 需要重繪 |
| 適用 | 圖標、圖表 | 遊戲、動畫 |

## 💾 本地儲存（Local Storage）

HTML5 提供 Web Storage API，讓網頁可以在瀏覽器中儲存資料。

### localStorage（永久儲存）

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>Local Storage 示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 600px;
            margin: 50px auto;
            padding: 20px;
        }
        input, button {
            padding: 10px;
            margin: 5px;
            font-size: 16px;
        }
        #output {
            margin-top: 20px;
            padding: 15px;
            background-color: #f5f5f5;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <h2>Local Storage 示範</h2>
    
    <div>
        <input type="text" id="nameInput" placeholder="輸入你的名字">
        <button onclick="saveName()">儲存</button>
        <button onclick="loadName()">讀取</button>
        <button onclick="clearName()">清除</button>
    </div>
    
    <div id="output"></div>
    
    <script>
        // 儲存資料
        function saveName() {
            const name = document.getElementById('nameInput').value;
            localStorage.setItem('userName', name);
            alert('已儲存：' + name);
        }
        
        // 讀取資料
        function loadName() {
            const name = localStorage.getItem('userName');
            const output = document.getElementById('output');
            if (name) {
                output.innerHTML = '<strong>儲存的名字：</strong>' + name;
            } else {
                output.innerHTML = '<em>尚未儲存任何資料</em>';
            }
        }
        
        // 清除資料
        function clearName() {
            localStorage.removeItem('userName');
            document.getElementById('output').innerHTML = '<em>已清除資料</em>';
        }
        
        // 頁面載入時自動讀取
        window.onload = function() {
            loadName();
        };
    </script>
</body>
</html>
```

### sessionStorage（暫時儲存）

```javascript
// 只在目前分頁有效，關閉分頁後資料會消失
sessionStorage.setItem('key', 'value');
const value = sessionStorage.getItem('key');
sessionStorage.removeItem('key');
sessionStorage.clear(); // 清除所有
```

## 📍 地理定位（Geolocation）

HTML5 Geolocation API 可以取得使用者的地理位置。

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>地理定位示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 600px;
            margin: 50px auto;
            padding: 20px;
            text-align: center;
        }
        button {
            padding: 15px 30px;
            font-size: 18px;
            background-color: #4ECDC4;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        button:hover {
            background-color: #38A3A5;
        }
        #result {
            margin-top: 30px;
            padding: 20px;
            background-color: #f5f5f5;
            border-radius: 5px;
            text-align: left;
        }
    </style>
</head>
<body>
    <h2>地理定位示範</h2>
    <p>點擊按鈕取得你的位置</p>
    
    <button onclick="getLocation()">取得我的位置</button>
    
    <div id="result"></div>
    
    <script>
        function getLocation() {
            const result = document.getElementById('result');
            
            if (navigator.geolocation) {
                result.innerHTML = '<p>正在取得位置...</p>';
                
                navigator.geolocation.getCurrentPosition(
                    function(position) {
                        const lat = position.coords.latitude;
                        const lon = position.coords.longitude;
                        const accuracy = position.coords.accuracy;
                        
                        result.innerHTML = `
                            <h3>您的位置：</h3>
                            <p><strong>緯度：</strong> ${lat}</p>
                            <p><strong>經度：</strong> ${lon}</p>
                            <p><strong>精確度：</strong> ${accuracy} 公尺</p>
                            <p><a href="https://www.google.com/maps?q=${lat},${lon}" target="_blank">
                                在 Google 地圖上查看
                            </a></p>
                        `;
                    },
                    function(error) {
                        result.innerHTML = '<p style="color: red;">無法取得位置：' + 
                                         error.message + '</p>';
                    }
                );
            } else {
                result.innerHTML = '<p style="color: red;">您的瀏覽器不支援地理定位</p>';
            }
        }
    </script>
</body>
</html>
```

## 🎬 拖放（Drag and Drop）

HTML5 支援原生的拖放功能。

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>拖放示範</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
        }
        .container {
            display: flex;
            gap: 20px;
            margin-top: 20px;
        }
        .box {
            width: 200px;
            height: 200px;
            border: 3px dashed #ccc;
            border-radius: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            background-color: #f9f9f9;
        }
        .box.over {
            border-color: #4ECDC4;
            background-color: #E8F8F5;
        }
        .item {
            width: 100px;
            height: 100px;
            background-color: #FF6B6B;
            color: white;
            display: flex;
            align-items: center;
            justify-content: center;
            border-radius: 10px;
            cursor: move;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <h2>拖放示範</h2>
    <p>將紅色方塊拖放到右邊的框框中</p>
    
    <div class="container">
        <div class="box" id="box1">
            <div class="item" draggable="true" id="item">
                拖動我
            </div>
        </div>
        
        <div class="box" id="box2">
            放到這裡
        </div>
    </div>
    
    <script>
        const item = document.getElementById('item');
        const boxes = document.querySelectorAll('.box');
        
        // 開始拖動
        item.addEventListener('dragstart', function(e) {
            e.dataTransfer.effectAllowed = 'move';
            e.dataTransfer.setData('text/html', this.innerHTML);
        });
        
        // 處理拖放區域
        boxes.forEach(box => {
            box.addEventListener('dragover', function(e) {
                if (e.preventDefault) {
                    e.preventDefault();
                }
                e.dataTransfer.dropEffect = 'move';
                this.classList.add('over');
                return false;
            });
            
            box.addEventListener('dragleave', function() {
                this.classList.remove('over');
            });
            
            box.addEventListener('drop', function(e) {
                if (e.stopPropagation) {
                    e.stopPropagation();
                }
                this.classList.remove('over');
                
                // 移動元素
                const draggedItem = document.getElementById('item');
                this.innerHTML = '';
                this.appendChild(draggedItem);
                
                return false;
            });
        });
    </script>
</body>
</html>
```

## 🎥 其他 HTML5 API

### 1. History API（瀏覽歷史）

```javascript
// 加入歷史記錄
history.pushState({page: 1}, "Title", "?page=1");

// 取代當前歷史記錄
history.replaceState({page: 2}, "Title", "?page=2");

// 前進/後退
history.back();
history.forward();
history.go(-2); // 後退兩頁
```

### 2. 全螢幕 API

```javascript
// 進入全螢幕
element.requestFullscreen();

// 退出全螢幕
document.exitFullscreen();

// 檢查是否全螢幕
if (document.fullscreenElement) {
    console.log('目前是全螢幕模式');
}
```

### 3. 網頁通知 API

```javascript
// 請求權限
Notification.requestPermission().then(function(permission) {
    if (permission === "granted") {
        // 顯示通知
        new Notification("通知標題", {
            body: "通知內容",
            icon: "icon.png"
        });
    }
});
```

## 💻 實作練習：整合應用

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>HTML5 功能整合示範</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Microsoft JhengHei', Arial, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }
        .container {
            max-width: 1000px;
            margin: 0 auto;
        }
        h1 {
            color: white;
            text-align: center;
            margin-bottom: 30px;
        }
        .card {
            background: white;
            border-radius: 10px;
            padding: 30px;
            margin-bottom: 20px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
        }
        .card h2 {
            color: #667eea;
            margin-bottom: 15px;
        }
        button {
            padding: 12px 24px;
            background-color: #667eea;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            margin: 5px;
        }
        button:hover {
            background-color: #5568d3;
        }
        canvas {
            border: 2px solid #ddd;
            border-radius: 5px;
            display: block;
            margin: 15px 0;
        }
        #notesList {
            list-style: none;
            margin-top: 15px;
        }
        #notesList li {
            background-color: #f9f9f9;
            padding: 10px;
            margin: 5px 0;
            border-radius: 5px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        input[type="text"] {
            padding: 10px;
            width: 70%;
            border: 2px solid #ddd;
            border-radius: 5px;
            font-size: 16px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🚀 HTML5 功能整合示範</h1>
        
        <!-- Canvas 繪圖 -->
        <div class="card">
            <h2>🎨 Canvas 繪圖</h2>
            <canvas id="drawCanvas" width="600" height="300"></canvas>
            <button onclick="drawShapes()">繪製圖形</button>
            <button onclick="clearCanvas()">清除畫布</button>
        </div>
        
        <!-- Local Storage 筆記 -->
        <div class="card">
            <h2>📝 筆記本（Local Storage）</h2>
            <input type="text" id="noteInput" placeholder="輸入筆記內容">
            <button onclick="addNote()">新增筆記</button>
            <button onclick="clearNotes()">清除全部</button>
            <ul id="notesList"></ul>
        </div>
        
        <!-- 地理定位 -->
        <div class="card">
            <h2>📍 地理定位</h2>
            <button onclick="getLocation()">取得我的位置</button>
            <div id="locationResult" style="margin-top: 15px;"></div>
        </div>
    </div>
    
    <script>
        // Canvas 繪圖功能
        const canvas = document.getElementById('drawCanvas');
        const ctx = canvas.getContext('2d');
        
        function drawShapes() {
            clearCanvas();
            
            // 繪製矩形
            ctx.fillStyle = '#FF6B6B';
            ctx.fillRect(50, 50, 150, 100);
            
            // 繪製圓形
            ctx.beginPath();
            ctx.arc(350, 100, 60, 0, 2 * Math.PI);
            ctx.fillStyle = '#4ECDC4';
            ctx.fill();
            
            // 繪製文字
            ctx.font = '24px Arial';
            ctx.fillStyle = '#333';
            ctx.fillText('Hello HTML5!', 200, 220);
            
            // 繪製線條
            ctx.beginPath();
            ctx.moveTo(50, 250);
            ctx.lineTo(550, 250);
            ctx.strokeStyle = '#95E1D3';
            ctx.lineWidth = 5;
            ctx.stroke();
        }
        
        function clearCanvas() {
            ctx.clearRect(0, 0, canvas.width, canvas.height);
        }
        
        // Local Storage 筆記功能
        function addNote() {
            const input = document.getElementById('noteInput');
            const note = input.value.trim();
            
            if (note === '') {
                alert('請輸入筆記內容');
                return;
            }
            
            // 取得現有筆記
            let notes = JSON.parse(localStorage.getItem('notes') || '[]');
            notes.push({
                id: Date.now(),
                text: note,
                date: new Date().toLocaleString('zh-TW')
            });
            
            // 儲存
            localStorage.setItem('notes', JSON.stringify(notes));
            
            input.value = '';
            displayNotes();
        }
        
        function displayNotes() {
            const notesList = document.getElementById('notesList');
            const notes = JSON.parse(localStorage.getItem('notes') || '[]');
            
            notesList.innerHTML = '';
            notes.forEach(note => {
                const li = document.createElement('li');
                li.innerHTML = `
                    <div>
                        <strong>${note.text}</strong>
                        <br>
                        <small>${note.date}</small>
                    </div>
                    <button onclick="deleteNote(${note.id})">刪除</button>
                `;
                notesList.appendChild(li);
            });
        }
        
        function deleteNote(id) {
            let notes = JSON.parse(localStorage.getItem('notes') || '[]');
            notes = notes.filter(note => note.id !== id);
            localStorage.setItem('notes', JSON.stringify(notes));
            displayNotes();
        }
        
        function clearNotes() {
            if (confirm('確定要清除所有筆記嗎？')) {
                localStorage.removeItem('notes');
                displayNotes();
            }
        }
        
        // 地理定位功能
        function getLocation() {
            const result = document.getElementById('locationResult');
            
            if (!navigator.geolocation) {
                result.innerHTML = '<p style="color: red;">您的瀏覽器不支援地理定位</p>';
                return;
            }
            
            result.innerHTML = '<p>正在取得位置...</p>';
            
            navigator.geolocation.getCurrentPosition(
                function(position) {
                    const lat = position.coords.latitude;
                    const lon = position.coords.longitude;
                    
                    result.innerHTML = `
                        <p><strong>緯度：</strong> ${lat.toFixed(6)}</p>
                        <p><strong>經度：</strong> ${lon.toFixed(6)}</p>
                        <a href="https://www.google.com/maps?q=${lat},${lon}" 
                           target="_blank" 
                           style="color: #667eea;">
                            在 Google 地圖上查看
                        </a>
                    `;
                },
                function(error) {
                    result.innerHTML = '<p style="color: red;">無法取得位置</p>';
                }
            );
        }
        
        // 頁面載入時顯示筆記
        window.onload = function() {
            displayNotes();
        };
    </script>
</body>
</html>
```

## 📝 本課重點回顧

- ✅ Canvas 提供點陣圖形繪製功能，適合遊戲和動畫
- ✅ SVG 是向量圖形，可無限縮放不失真
- ✅ localStorage 永久儲存資料，sessionStorage 暫時儲存
- ✅ Geolocation API 可取得使用者位置
- ✅ HTML5 支援原生拖放功能
- ✅ 各種 API 讓網頁功能更強大

## 🎯 課後練習

1. **基礎練習**：建立簡單的繪圖工具
   - 使用 Canvas 建立畫布
   - 提供選擇顏色的功能
   - 提供清除畫布的按鈕
   - 使用 localStorage 儲存畫作

2. **進階挑戰**：建立待辦事項應用
   - 可新增、編輯、刪除待辦事項
   - 使用 localStorage 永久保存
   - 顯示完成/未完成狀態
   - 可拖放排序事項

3. **實戰練習**：建立個人記帳本
   - 記錄收入和支出
   - 使用 Canvas 或 SVG 顯示圖表
   - 使用 localStorage 儲存資料
   - 可匯出資料（下載功能）
   - 計算總收入、支出、結餘

## 🎉 HTML 部分完成！

恭喜！您已經完成了 HTML 部分的所有課程。現在您已經掌握了：

- ✅ HTML 基本結構和標籤
- ✅ 文字格式化和列表
- ✅ 連結、圖片和多媒體
- ✅ 表格和表單
- ✅ 語義化標籤
- ✅ HTML5 新功能

接下來，我們將進入 **CSS 部分**，學習如何美化網頁，打造專業的視覺效果！

## 🔗 下一課預告

在下一課中，我們將開始學習 CSS，了解如何為網頁加上樣式，包括顏色、字型、間距等基本樣式設定！

---

[← 上一課：HTML5 語義化標籤](./08-semantic-html.md) | [返回目錄](../README.md) | [下一課：CSS 基礎介紹 →](./10-css-introduction.md)
