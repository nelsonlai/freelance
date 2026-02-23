# 第 7 課：表單進階

## 📚 本課學習目標

- 掌握表單驗證屬性
- 學會使用 HTML5 新增的輸入類型
- 了解表單元素的群組方式
- 掌握其他進階表單功能

## ✅ HTML5 表單驗證

HTML5 提供內建的表單驗證功能，無需 JavaScript 即可進行基本驗證。

### 1. required 屬性（必填）

```html
<label for="username">使用者名稱（必填）：</label>
<input type="text" id="username" name="username" required>

<label for="email">電子郵件（必填）：</label>
<input type="email" id="email" name="email" required>
```

### 2. pattern 屬性（正則表達式驗證）

```html
<!-- 只允許英文字母和數字 -->
<label for="username">使用者名稱（英數字）：</label>
<input type="text" 
       id="username" 
       name="username" 
       pattern="[A-Za-z0-9]+"
       title="只能包含英文字母和數字">

<!-- 台灣手機號碼格式 -->
<label for="phone">手機號碼（09開頭10碼）：</label>
<input type="tel" 
       id="phone" 
       name="phone" 
       pattern="09[0-9]{8}"
       title="請輸入正確的手機號碼格式">

<!-- 郵遞區號（5碼數字） -->
<label for="zipcode">郵遞區號：</label>
<input type="text" 
       id="zipcode" 
       name="zipcode" 
       pattern="[0-9]{5}"
       title="請輸入5碼郵遞區號">
```

### 3. min 和 max 屬性（數值範圍）

```html
<!-- 數字範圍 -->
<label for="age">年齡（18-120）：</label>
<input type="number" 
       id="age" 
       name="age" 
       min="18" 
       max="120"
       required>

<!-- 日期範圍 -->
<label for="start-date">開始日期：</label>
<input type="date" 
       id="start-date" 
       name="start_date" 
       min="2026-01-01" 
       max="2026-12-31">
```

### 4. minlength 和 maxlength 屬性（字元長度）

```html
<label for="password">密碼（6-20字元）：</label>
<input type="password" 
       id="password" 
       name="password" 
       minlength="6" 
       maxlength="20"
       required>

<label for="bio">自我介紹（最多500字）：</label>
<textarea id="bio" 
          name="bio" 
          maxlength="500" 
          rows="5"></textarea>
```

### 5. step 屬性（步進值）

```html
<!-- 每次增加0.5 -->
<label for="rating">評分：</label>
<input type="number" 
       id="rating" 
       name="rating" 
       min="0" 
       max="5" 
       step="0.5">

<!-- 每次增加10 -->
<label for="price">價格：</label>
<input type="number" 
       id="price" 
       name="price" 
       min="0" 
       step="10">
```

## 💻 實作練習 1：帶驗證的註冊表單

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>會員註冊（含驗證）</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
        }
        form {
            max-width: 500px;
            margin: 30px auto;
            padding: 30px;
            background-color: white;
            border-radius: 8px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        h2 {
            text-align: center;
            color: #333;
        }
        .form-group {
            margin-bottom: 20px;
        }
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
            color: #555;
        }
        input, textarea {
            width: 100%;
            padding: 10px;
            border: 2px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
            font-size: 14px;
        }
        input:focus, textarea:focus {
            outline: none;
            border-color: #4CAF50;
        }
        input:valid {
            border-color: #4CAF50;
        }
        input:invalid:not(:placeholder-shown) {
            border-color: #f44336;
        }
        .hint {
            font-size: 12px;
            color: #777;
            margin-top: 3px;
        }
        button {
            width: 100%;
            padding: 12px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 16px;
            cursor: pointer;
            margin-top: 10px;
        }
        button:hover {
            background-color: #45a049;
        }
        .required::after {
            content: " *";
            color: red;
        }
    </style>
</head>
<body>
    <form action="/register" method="POST">
        <h2>會員註冊</h2>
        
        <div class="form-group">
            <label for="username" class="required">使用者名稱</label>
            <input type="text" 
                   id="username" 
                   name="username" 
                   pattern="[A-Za-z0-9_]{4,20}"
                   title="4-20個字元，只能包含英文、數字和底線"
                   placeholder="請輸入使用者名稱"
                   required>
            <div class="hint">4-20個字元，只能包含英文、數字和底線</div>
        </div>
        
        <div class="form-group">
            <label for="email" class="required">電子郵件</label>
            <input type="email" 
                   id="email" 
                   name="email" 
                   placeholder="example@email.com"
                   required>
            <div class="hint">請輸入有效的電子郵件地址</div>
        </div>
        
        <div class="form-group">
            <label for="password" class="required">密碼</label>
            <input type="password" 
                   id="password" 
                   name="password" 
                   minlength="8"
                   maxlength="20"
                   pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,}"
                   title="至少8個字元，包含大小寫字母和數字"
                   placeholder="請輸入密碼"
                   required>
            <div class="hint">至少8個字元，必須包含大小寫字母和數字</div>
        </div>
        
        <div class="form-group">
            <label for="phone">手機號碼</label>
            <input type="tel" 
                   id="phone" 
                   name="phone" 
                   pattern="09[0-9]{8}"
                   placeholder="0912345678"
                   title="請輸入正確的手機號碼（10碼，09開頭）">
            <div class="hint">格式：0912345678</div>
        </div>
        
        <div class="form-group">
            <label for="age" class="required">年齡</label>
            <input type="number" 
                   id="age" 
                   name="age" 
                   min="18" 
                   max="120"
                   placeholder="18"
                   required>
            <div class="hint">必須年滿18歲</div>
        </div>
        
        <div class="form-group">
            <label for="website">個人網站</label>
            <input type="url" 
                   id="website" 
                   name="website" 
                   placeholder="https://www.example.com">
            <div class="hint">選填，請輸入完整網址</div>
        </div>
        
        <button type="submit">註冊</button>
    </form>
</body>
</html>
```

## 🎨 HTML5 新增的輸入類型

### 1. 顏色選擇器（color）

```html
<label for="color">選擇顏色：</label>
<input type="color" id="color" name="color" value="#ff0000">
```

### 2. 檔案上傳（file）

```html
<!-- 單一檔案 -->
<label for="avatar">上傳頭像：</label>
<input type="file" id="avatar" name="avatar" accept="image/*">

<!-- 多個檔案 -->
<label for="photos">上傳照片（可多選）：</label>
<input type="file" id="photos" name="photos" accept="image/*" multiple>

<!-- 限制檔案類型 -->
<label for="document">上傳文件：</label>
<input type="file" id="document" name="document" accept=".pdf,.doc,.docx">
```

**accept 屬性值：**
- `image/*`：所有圖片格式
- `video/*`：所有視訊格式
- `audio/*`：所有音訊格式
- `.pdf`：PDF 檔案
- `.doc,.docx`：Word 文件

### 3. 隱藏欄位（hidden）

```html
<input type="hidden" name="user_id" value="12345">
<input type="hidden" name="form_token" value="abc123xyz">
```

**用途：**
- 存放不需要使用者看到的資料
- 傳遞額外的系統資訊

## 🏗️ 表單元素群組

### 1. fieldset 和 legend

使用 `<fieldset>` 群組相關的表單元素，`<legend>` 為群組加上標題：

```html
<form>
    <fieldset>
        <legend>個人資料</legend>
        
        <label for="name">姓名：</label>
        <input type="text" id="name" name="name"><br><br>
        
        <label for="email">電子郵件：</label>
        <input type="email" id="email" name="email"><br><br>
    </fieldset>
    
    <fieldset>
        <legend>聯絡資訊</legend>
        
        <label for="phone">電話：</label>
        <input type="tel" id="phone" name="phone"><br><br>
        
        <label for="address">地址：</label>
        <input type="text" id="address" name="address"><br><br>
    </fieldset>
    
    <button type="submit">送出</button>
</form>
```

### 2. optgroup（選項群組）

```html
<label for="course">選擇課程：</label>
<select id="course" name="course">
    <optgroup label="前端開發">
        <option value="html">HTML</option>
        <option value="css">CSS</option>
        <option value="js">JavaScript</option>
    </optgroup>
    <optgroup label="後端開發">
        <option value="php">PHP</option>
        <option value="python">Python</option>
        <option value="nodejs">Node.js</option>
    </optgroup>
    <optgroup label="資料庫">
        <option value="mysql">MySQL</option>
        <option value="mongodb">MongoDB</option>
    </optgroup>
</select>
```

## 💻 實作練習 2：完整的訂購表單

```html
<!DOCTYPE html>
<html lang="zh-TW">
<head>
    <meta charset="UTF-8">
    <title>線上訂購表單</title>
    <style>
        body {
            font-family: 'Microsoft JhengHei', sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            padding: 20px;
        }
        form {
            max-width: 700px;
            margin: 0 auto;
            background-color: white;
            padding: 0;
            border-radius: 10px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.2);
        }
        .form-header {
            background-color: #667eea;
            color: white;
            padding: 30px;
            border-radius: 10px 10px 0 0;
            text-align: center;
        }
        .form-body {
            padding: 30px;
        }
        fieldset {
            border: 2px solid #e0e0e0;
            border-radius: 8px;
            padding: 20px;
            margin-bottom: 20px;
        }
        legend {
            font-size: 18px;
            font-weight: bold;
            color: #667eea;
            padding: 0 10px;
        }
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
            color: #333;
        }
        input, select, textarea {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        .radio-group, .checkbox-group {
            margin: 10px 0;
        }
        .radio-group label,
        .checkbox-group label {
            display: inline-block;
            font-weight: normal;
            margin-right: 15px;
        }
        .form-row {
            display: flex;
            gap: 15px;
        }
        .form-row .form-group {
            flex: 1;
        }
        button {
            width: 100%;
            padding: 15px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 18px;
            cursor: pointer;
            transition: transform 0.2s;
        }
        button:hover {
            transform: translateY(-2px);
        }
        .required::after {
            content: " *";
            color: red;
        }
        .hint {
            font-size: 12px;
            color: #666;
            margin-top: 3px;
        }
    </style>
</head>
<body>
    <form action="/order" method="POST" enctype="multipart/form-data">
        <div class="form-header">
            <h1>線上訂購表單</h1>
            <p>請填寫以下資訊完成訂購</p>
        </div>
        
        <div class="form-body">
            <fieldset>
                <legend>訂購人資訊</legend>
                
                <div class="form-row">
                    <div class="form-group">
                        <label for="name" class="required">姓名</label>
                        <input type="text" 
                               id="name" 
                               name="name" 
                               placeholder="請輸入姓名"
                               required>
                    </div>
                    
                    <div class="form-group">
                        <label for="phone" class="required">手機號碼</label>
                        <input type="tel" 
                               id="phone" 
                               name="phone" 
                               pattern="09[0-9]{8}"
                               placeholder="0912345678"
                               required>
                    </div>
                </div>
                
                <div class="form-group">
                    <label for="email" class="required">電子郵件</label>
                    <input type="email" 
                           id="email" 
                           name="email" 
                           placeholder="example@email.com"
                           required>
                </div>
                
                <div class="form-group">
                    <label for="address" class="required">配送地址</label>
                    <input type="text" 
                           id="address" 
                           name="address" 
                           placeholder="請輸入完整地址"
                           required>
                </div>
            </fieldset>
            
            <fieldset>
                <legend>訂購商品</legend>
                
                <div class="form-group">
                    <label for="product" class="required">選擇商品</label>
                    <select id="product" name="product" required>
                        <option value="">請選擇商品</option>
                        <optgroup label="電子產品">
                            <option value="phone">智慧型手機 - $15,000</option>
                            <option value="laptop">筆記型電腦 - $30,000</option>
                            <option value="tablet">平板電腦 - $12,000</option>
                        </optgroup>
                        <optgroup label="配件">
                            <option value="earphone">藍牙耳機 - $3,000</option>
                            <option value="case">保護殼 - $500</option>
                            <option value="charger">充電器 - $800</option>
                        </optgroup>
                    </select>
                </div>
                
                <div class="form-row">
                    <div class="form-group">
                        <label for="quantity" class="required">數量</label>
                        <input type="number" 
                               id="quantity" 
                               name="quantity" 
                               min="1" 
                               max="99" 
                               value="1"
                               required>
                    </div>
                    
                    <div class="form-group">
                        <label for="color">顏色</label>
                        <select id="color" name="color">
                            <option value="black">黑色</option>
                            <option value="white">白色</option>
                            <option value="blue">藍色</option>
                            <option value="red">紅色</option>
                        </select>
                    </div>
                </div>
            </fieldset>
            
            <fieldset>
                <legend>配送與付款</legend>
                
                <div class="form-group">
                    <label class="required">配送方式</label>
                    <div class="radio-group">
                        <input type="radio" id="home" name="delivery" value="home" checked>
                        <label for="home">宅配到府（免運費）</label>
                        
                        <input type="radio" id="store" name="delivery" value="store">
                        <label for="store">超商取貨</label>
                    </div>
                </div>
                
                <div class="form-group">
                    <label class="required">付款方式</label>
                    <div class="radio-group">
                        <input type="radio" id="credit" name="payment" value="credit" checked>
                        <label for="credit">信用卡</label>
                        
                        <input type="radio" id="atm" name="payment" value="atm">
                        <label for="atm">ATM轉帳</label>
                        
                        <input type="radio" id="cod" name="payment" value="cod">
                        <label for="cod">貨到付款</label>
                    </div>
                </div>
                
                <div class="form-group">
                    <label for="delivery-date">希望到貨日期</label>
                    <input type="date" 
                           id="delivery-date" 
                           name="delivery_date" 
                           min="2026-02-15">
                    <div class="hint">最快3天到貨</div>
                </div>
            </fieldset>
            
            <fieldset>
                <legend>其他資訊</legend>
                
                <div class="form-group">
                    <label for="gift">贈送對象</label>
                    <div class="checkbox-group">
                        <input type="checkbox" id="gift-wrap" name="gift_wrap">
                        <label for="gift-wrap">需要禮物包裝（+$100）</label>
                    </div>
                </div>
                
                <div class="form-group">
                    <label for="invoice">發票寄送</label>
                    <input type="email" 
                           id="invoice" 
                           name="invoice_email" 
                           placeholder="電子發票寄送信箱（選填）">
                </div>
                
                <div class="form-group">
                    <label for="note">備註</label>
                    <textarea id="note" 
                              name="note" 
                              rows="4" 
                              placeholder="其他需求或說明..."
                              maxlength="200"></textarea>
                    <div class="hint">最多200字</div>
                </div>
            </fieldset>
            
            <button type="submit">確認訂購</button>
        </div>
    </form>
</body>
</html>
```

## 🎯 其他進階屬性

### 1. autocomplete 屬性

```html
<!-- 開啟自動完成 -->
<input type="text" name="name" autocomplete="on">

<!-- 關閉自動完成 -->
<input type="password" name="password" autocomplete="off">

<!-- 指定自動完成類型 -->
<input type="text" name="name" autocomplete="name">
<input type="email" name="email" autocomplete="email">
<input type="tel" name="phone" autocomplete="tel">
```

### 2. autofocus 屬性

```html
<!-- 頁面載入時自動聚焦到此欄位 -->
<input type="text" name="search" autofocus>
```

### 3. multiple 屬性

```html
<!-- 可選擇多個檔案 -->
<input type="file" name="files" multiple>

<!-- 可選擇多個選項 -->
<select name="skills" multiple size="5">
    <option value="html">HTML</option>
    <option value="css">CSS</option>
    <option value="js">JavaScript</option>
</select>
```

### 4. novalidate 屬性

```html
<!-- 停用表單驗證（用於測試） -->
<form action="/submit" method="POST" novalidate>
    <!-- 表單內容 -->
</form>
```

### 5. formnovalidate 屬性

```html
<form action="/submit" method="POST">
    <input type="email" name="email" required>
    
    <!-- 這個按鈕不會觸發驗證 -->
    <button type="submit" formnovalidate>儲存草稿</button>
    
    <!-- 這個按鈕會觸發驗證 -->
    <button type="submit">正式送出</button>
</form>
```

## 📝 本課重點回顧

- ✅ 使用 `required`、`pattern`、`min`、`max` 等屬性進行表單驗證
- ✅ `minlength` 和 `maxlength` 控制字元長度
- ✅ `pattern` 屬性使用正則表達式驗證格式
- ✅ HTML5 新增 color、file 等輸入類型
- ✅ 使用 `<fieldset>` 和 `<legend>` 群組表單元素
- ✅ `accept` 屬性限制檔案上傳類型
- ✅ `multiple` 屬性允許多選檔案或選項
- ✅ 使用 `autocomplete` 提升使用者體驗

## 🎯 課後練習

1. **基礎練習**：建立活動報名表單
   - 包含姓名、email、電話（使用 pattern 驗證）
   - 年齡限制（18歲以上）
   - 選擇參加場次（使用 radio）
   - 飲食偏好（使用 checkbox 多選）
   - 特殊需求（textarea，最多300字）

2. **進階挑戰**：建立求職申請表單
   - 個人資料區（使用 fieldset 群組）
   - 學歷背景（多個學歷可用多組 fieldset）
   - 工作經驗（textarea）
   - 上傳履歷（file，限制 PDF）
   - 期望薪資（number，範圍限制）
   - 可上班日期（date，不能早於今天）

3. **實戰練習**：建立問卷調查表單
   - 至少包含 3 個 fieldset 區塊
   - 使用各種不同的輸入類型
   - 套用完整的表單驗證
   - 加入美觀的 CSS 樣式
   - 確保所有必填欄位都有明確標示

## 🔗 下一課預告

在下一課中，我們將學習 HTML5 的語義化標籤，包括 `<header>`、`<nav>`、`<article>`、`<section>` 等，讓網頁結構更清晰、更有意義！

---

[← 上一課：表單基礎](./06-forms-basics.md) | [返回目錄](../README.md) | [下一課：HTML5 語義化標籤 →](./08-semantic-html.md)
