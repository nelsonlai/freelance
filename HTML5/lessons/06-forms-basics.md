# 第 6 課：表單基礎

## 📚 本課學習目標

- 理解表單的用途和基本結構
- 學會建立各種類型的輸入欄位
- 掌握表單控制元件的使用
- 了解表單的基本屬性

## 📝 什麼是表單？

**表單（Form）**是網頁中用來收集使用者輸入資料的重要元素。常見的應用包括：

- 登入/註冊頁面
- 搜尋功能
- 聯絡表單
- 問卷調查
- 訂單表單

## 🏗️ 表單基本結構

```html
<form action="submit.php" method="POST">
    <!-- 表單內容 -->
    <input type="text" name="username">
    <button type="submit">送出</button>
</form>
```

### form 標籤的屬性

| 屬性 | 說明 |
|------|------|
| `action` | 指定表單資料提交的目標 URL |
| `method` | 提交方式：`GET` 或 `POST` |
| `name` | 表單的名稱 |
| `target` | 指定在哪裡顯示回應（`_blank`、`_self` 等） |
| `enctype` | 編碼類型（上傳檔案時使用） |

## 📥 文字輸入欄位

### 1. 單行文字輸入（text）

```html
<form>
    <label for="username">使用者名稱：</label>
    <input type="text" id="username" name="username">
</form>
```

### 2. 密碼輸入（password）

```html
<label for="password">密碼：</label>
<input type="password" id="password" name="password">
```

**特點**：輸入的文字會被隱藏顯示為 ●●●●

### 3. 電子郵件輸入（email）

```html
<label for="email">電子郵件：</label>
<input type="email" id="email" name="email">
```

**特點**：瀏覽器會自動驗證電子郵件格式

### 4. 網址輸入（url）

```html
<label for="website">網站：</label>
<input type="url" id="website" name="website">
```

### 5. 電話輸入（tel）

```html
<label for="phone">電話：</label>
<input type="tel" id="phone" name="phone">
```

### 6. 搜尋輸入（search）

```html
<label for="search">搜尋：</label>
<input type="search" id="search" name="search">
```

## 📝 多行文字輸入

使用 `<textarea>` 建立多行文字輸入框：

```html
<label for="message">留言：</label>
<textarea id="message" name="message" rows="5" cols="40"></textarea>
```

**屬性：**
- `rows`：顯示的行數
- `cols`：顯示的欄數

## 🔢 數字和日期輸入

### 1. 數字輸入（number）

```html
<label for="age">年齡：</label>
<input type="number" id="age" name="age" min="1" max="120">
```

**屬性：**
- `min`：最小值
- `max`：最大值
- `step`：遞增/遞減的步進值

### 2. 範圍滑桿（range）

```html
<label for="volume">音量：</label>
<input type="range" id="volume" name="volume" min="0" max="100" value="50">
```

### 3. 日期輸入（date）

```html
<label for="birthday">生日：</label>
<input type="date" id="birthday" name="birthday">
```

### 4. 時間輸入（time）

```html
<label for="appointment">預約時間：</label>
<input type="time" id="appointment" name="appointment">
```

### 5. 日期時間輸入（datetime-local）

```html
<label for="meeting">會議時間：</label>
<input type="datetime-local" id="meeting" name="meeting">
```

### 6. 月份輸入（month）

```html
<label for="month">選擇月份：</label>
<input type="month" id="month" name="month">
```

### 7. 週次輸入（week）

```html
<label for="week">選擇週次：</label>
<input type="week" id="week" name="week">
```

## 💻 實作練習 1：基本登入表單

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>登入表單</title>
    <style>
        form {
            width: 300px;
            margin: 50px auto;
            padding: 20px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        label {
            display: block;
            margin-top: 10px;
            font-weight: bold;
        }
        input {
            width: 100%;
            padding: 8px;
            margin-top: 5px;
            box-sizing: border-box;
        }
        button {
            width: 100%;
            padding: 10px;
            margin-top: 15px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 3px;
            cursor: pointer;
        }
        button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <form action="/login" method="POST">
        <h2 style="text-align: center;">會員登入</h2>
        
        <label for="username">使用者名稱：</label>
        <input type="text" id="username" name="username" required>
        
        <label for="password">密碼：</label>
        <input type="password" id="password" name="password" required>
        
        <button type="submit">登入</button>
    </form>
</body>
</html>
```

## ☑️ 選擇元件

### 1. 核取方塊（checkbox）

用於多選：

```html
<p>興趣：</p>
<input type="checkbox" id="reading" name="hobby" value="reading">
<label for="reading">閱讀</label><br>

<input type="checkbox" id="travel" name="hobby" value="travel">
<label for="travel">旅行</label><br>

<input type="checkbox" id="music" name="hobby" value="music">
<label for="music">音樂</label>
```

### 2. 單選按鈕（radio）

用於單選：

```html
<p>性別：</p>
<input type="radio" id="male" name="gender" value="male">
<label for="male">男性</label><br>

<input type="radio" id="female" name="gender" value="female">
<label for="female">女性</label><br>

<input type="radio" id="other" name="gender" value="other">
<label for="other">其他</label>
```

**注意**：相同 `name` 的 radio 按鈕為一組，只能選一個。

### 3. 下拉選單（select）

```html
<label for="city">城市：</label>
<select id="city" name="city">
    <option value="">請選擇</option>
    <option value="taipei">台北</option>
    <option value="taichung">台中</option>
    <option value="tainan">台南</option>
    <option value="kaohsiung">高雄</option>
</select>
```

#### 多選下拉選單

```html
<label for="languages">語言（可複選）：</label>
<select id="languages" name="languages" multiple size="4">
    <option value="html">HTML</option>
    <option value="css">CSS</option>
    <option value="js">JavaScript</option>
    <option value="python">Python</option>
</select>
```

#### 選項群組（optgroup）

```html
<label for="food">喜歡的食物：</label>
<select id="food" name="food">
    <optgroup label="中式料理">
        <option value="dumpling">水餃</option>
        <option value="noodle">麵食</option>
    </optgroup>
    <optgroup label="西式料理">
        <option value="pasta">義大利麵</option>
        <option value="pizza">披薩</option>
    </optgroup>
</select>
```

## 🔘 按鈕

### 1. 提交按鈕（submit）

```html
<button type="submit">送出表單</button>
<!-- 或 -->
<input type="submit" value="送出表單">
```

### 2. 重設按鈕（reset）

```html
<button type="reset">重設</button>
<!-- 或 -->
<input type="reset" value="重設">
```

### 3. 一般按鈕（button）

```html
<button type="button" onclick="alert('你點了按鈕！')">點我</button>
```

## 💻 實作練習 2：完整註冊表單

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>會員註冊</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
        }
        form {
            max-width: 500px;
            margin: 30px auto;
            padding: 30px;
            background-color: white;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        h2 {
            text-align: center;
            color: #333;
        }
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
            color: #555;
        }
        input[type="text"],
        input[type="email"],
        input[type="password"],
        input[type="tel"],
        input[type="date"],
        select,
        textarea {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        .radio-group,
        .checkbox-group {
            margin: 10px 0;
        }
        .radio-group label,
        .checkbox-group label {
            display: inline;
            font-weight: normal;
            margin-right: 15px;
        }
        button {
            width: 100%;
            padding: 12px;
            background-color: #2196F3;
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 16px;
            cursor: pointer;
            margin-top: 10px;
        }
        button:hover {
            background-color: #0b7dda;
        }
        button[type="reset"] {
            background-color: #f44336;
        }
        button[type="reset"]:hover {
            background-color: #da190b;
        }
    </style>
</head>
<body>
    <form action="/register" method="POST">
        <h2>會員註冊</h2>
        
        <div class="form-group">
            <label for="username">使用者名稱 *</label>
            <input type="text" id="username" name="username" required>
        </div>
        
        <div class="form-group">
            <label for="email">電子郵件 *</label>
            <input type="email" id="email" name="email" required>
        </div>
        
        <div class="form-group">
            <label for="password">密碼 *</label>
            <input type="password" id="password" name="password" required>
        </div>
        
        <div class="form-group">
            <label for="confirm-password">確認密碼 *</label>
            <input type="password" id="confirm-password" name="confirm_password" required>
        </div>
        
        <div class="form-group">
            <label for="phone">電話號碼</label>
            <input type="tel" id="phone" name="phone">
        </div>
        
        <div class="form-group">
            <label for="birthday">生日</label>
            <input type="date" id="birthday" name="birthday">
        </div>
        
        <div class="form-group">
            <label>性別</label>
            <div class="radio-group">
                <input type="radio" id="male" name="gender" value="male">
                <label for="male">男性</label>
                
                <input type="radio" id="female" name="gender" value="female">
                <label for="female">女性</label>
                
                <input type="radio" id="other" name="gender" value="other">
                <label for="other">其他</label>
            </div>
        </div>
        
        <div class="form-group">
            <label for="city">居住城市</label>
            <select id="city" name="city">
                <option value="">請選擇</option>
                <option value="taipei">台北市</option>
                <option value="new-taipei">新北市</option>
                <option value="taoyuan">桃園市</option>
                <option value="taichung">台中市</option>
                <option value="tainan">台南市</option>
                <option value="kaohsiung">高雄市</option>
            </select>
        </div>
        
        <div class="form-group">
            <label>興趣（可複選）</label>
            <div class="checkbox-group">
                <input type="checkbox" id="reading" name="hobby" value="reading">
                <label for="reading">閱讀</label>
                
                <input type="checkbox" id="travel" name="hobby" value="travel">
                <label for="travel">旅行</label>
                
                <input type="checkbox" id="sports" name="hobby" value="sports">
                <label for="sports">運動</label>
                
                <input type="checkbox" id="music" name="hobby" value="music">
                <label for="music">音樂</label>
            </div>
        </div>
        
        <div class="form-group">
            <label for="bio">自我介紹</label>
            <textarea id="bio" name="bio" rows="4" placeholder="請簡單介紹自己..."></textarea>
        </div>
        
        <button type="submit">註冊</button>
        <button type="reset">清除</button>
    </form>
</body>
</html>
```

## 🎯 輸入欄位的通用屬性

### 常用屬性

```html
<input type="text" 
       name="username"
       id="username"
       value="預設值"
       placeholder="請輸入使用者名稱"
       required
       disabled
       readonly
       maxlength="20"
       size="30">
```

| 屬性 | 說明 |
|------|------|
| `name` | 欄位名稱（提交時使用） |
| `id` | 唯一識別碼（配合 label 使用） |
| `value` | 預設值 |
| `placeholder` | 提示文字（灰色顯示） |
| `required` | 必填欄位 |
| `disabled` | 停用欄位 |
| `readonly` | 只讀（不可修改） |
| `maxlength` | 最大字元數 |
| `size` | 欄位顯示寬度 |
| `autofocus` | 自動取得焦點 |
| `autocomplete` | 自動完成（`on` 或 `off`） |

## 📝 label 標籤

`<label>` 標籤用來為輸入欄位加上說明文字，有兩種使用方式：

### 方式 1：使用 for 屬性

```html
<label for="username">使用者名稱：</label>
<input type="text" id="username" name="username">
```

### 方式 2：包裹輸入欄位

```html
<label>
    使用者名稱：
    <input type="text" name="username">
</label>
```

**好處：**
- 點擊 label 文字會自動聚焦到對應的輸入欄位
- 提升無障礙性
- 提升使用者體驗

## 📝 本課重點回顧

- ✅ 表單使用 `<form>` 標籤建立，`action` 指定提交目標
- ✅ `<input>` 標籤有多種 type：text、password、email、number 等
- ✅ `<textarea>` 用於多行文字輸入
- ✅ checkbox 用於多選，radio 用於單選
- ✅ `<select>` 建立下拉選單，`<option>` 定義選項
- ✅ `<label>` 為輸入欄位提供說明，提升使用者體驗
- ✅ `required` 屬性標記必填欄位
- ✅ `placeholder` 提供提示文字

## 🎯 課後練習

1. **基礎練習**：建立聯絡表單
   - 包含：姓名、電子郵件、電話、主旨、訊息
   - 姓名和電子郵件為必填
   - 訊息欄位使用 textarea
   - 加上送出和重設按鈕

2. **進階挑戰**：建立問卷調查表單
   - 包含個人基本資料（姓名、年齡、性別）
   - 使用 radio 選擇滿意度（非常滿意、滿意、普通、不滿意）
   - 使用 checkbox 選擇改進項目（可複選）
   - 使用 select 選擇從哪裡得知本問卷
   - 加上意見回饋欄位

3. **實戰練習**：建立線上訂購表單
   - 個人資料區：姓名、電話、email、地址
   - 產品選擇：使用 select 選擇產品，number 輸入數量
   - 配送方式：使用 radio 選擇（宅配、超商取貨）
   - 付款方式：使用 radio 選擇（信用卡、ATM轉帳、貨到付款）
   - 備註欄位：使用 textarea
   - 加上完整的樣式美化

## 🔗 下一課預告

在下一課中，我們將學習表單的進階功能，包括表單驗證、新的 HTML5 輸入類型，以及如何群組表單元素！

---

[← 上一課：表格](./05-tables.md) | [返回目錄](../README.md) | [下一課：表單進階 →](./07-forms-advanced.md)
