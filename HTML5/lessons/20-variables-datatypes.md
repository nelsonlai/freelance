# 第 20 課：變數和資料型別

## 📚 本課學習目標

- 理解變數的概念
- 學會宣告和使用變數
- 掌握 JavaScript 的基本資料型別
- 了解 let、const、var 的區別

## 📦 什麼是變數？

**變數（Variable）**就像一個盒子，用來儲存資料。

```javascript
// 建立一個名為 name 的變數，儲存 '小明'
let name = '小明';

// 建立一個名為 age 的變數，儲存 25
let age = 25;
```

## 🔤 變數宣告

### let（推薦）

```javascript
let name = '小明';      // 宣告並賦值
let age;               // 只宣告
age = 25;              // 之後賦值

// 可以重新賦值
let score = 80;
score = 90;            // ✅ 可以
```

### const（常數，不可變）

```javascript
const PI = 3.14159;    // 宣告常數
// PI = 3.14;          // ❌ 錯誤！不能改變

const birthYear = 2000;
// birthYear = 2001;   // ❌ 錯誤！
```

### var（舊式，不建議）

```javascript
var oldWay = '不建議使用';
```

**建議：**
- 使用 `let` 宣告可變的變數
- 使用 `const` 宣告不變的常數
- 避免使用 `var`

## 📝 變數命名規則

### ✅ 可以使用

```javascript
let name;              // 英文字母
let age2;              // 英文 + 數字
let user_name;         // 底線
let userName;          // 駝峰式（推薦）
let $price;            // 錢號
let _private;          // 底線開頭
```

### ❌ 不可以使用

```javascript
let 2name;             // ❌ 不能以數字開頭
let user-name;         // ❌ 不能用連字號
let user name;         // ❌ 不能有空格
let let;               // ❌ 不能用保留字
```

### 命名慣例

```javascript
// 駝峰式命名（推薦）
let userName = '小明';
let userAge = 25;
let isStudent = true;

// 常數用大寫
const MAX_SIZE = 100;
const API_KEY = 'abc123';
```

## 🎨 資料型別

JavaScript 有 8 種資料型別：

### 1. Number（數字）

```javascript
let age = 25;              // 整數
let price = 19.99;         // 小數
let negative = -10;        // 負數
let billion = 1e9;         // 科學記號：1,000,000,000
```

### 2. String（字串）

```javascript
let name = '小明';         // 單引號
let message = "你好";      // 雙引號
let template = `Hello`;    // 反引號（模板字串）

// 模板字串（可嵌入變數）
let greeting = `你好，${name}！`;
console.log(greeting);     // 你好，小明！
```

### 3. Boolean（布林值）

```javascript
let isStudent = true;
let hasLicense = false;

// 比較運算會得到布林值
let isAdult = age >= 18;   // true 或 false
```

### 4. Undefined（未定義）

```javascript
let x;                     // 只宣告，沒賦值
console.log(x);            // undefined
```

### 5. Null（空值）

```javascript
let data = null;           // 故意設為空
```

### 6. Object（物件）

```javascript
let person = {
    name: '小明',
    age: 25,
    city: '台北'
};
```

### 7. Array（陣列）

```javascript
let colors = ['紅', '綠', '藍'];
let numbers = [1, 2, 3, 4, 5];
```

### 8. Symbol（符號）- 進階

```javascript
let id = Symbol('id');
```

## 🔍 typeof 運算子

檢查資料型別：

```javascript
typeof 123;               // "number"
typeof '文字';            // "string"
typeof true;              // "boolean"
typeof undefined;         // "undefined"
typeof null;              // "object" (JavaScript 的一個 bug)
typeof {};                // "object"
typeof [];                // "object"
typeof function(){};      // "function"
```

## 💻 實作練習

請參考範例檔案：
- `examples/lesson-20/example-01-variables.html`
- `examples/lesson-20/example-02-datatypes.html`

## 🔄 型別轉換

### 轉成字串

```javascript
let num = 123;
let str = String(num);      // "123"
let str2 = num.toString();  // "123"
```

### 轉成數字

```javascript
let str = "123";
let num = Number(str);      // 123
let num2 = parseInt(str);   // 123
let num3 = parseFloat("3.14"); // 3.14
```

### 轉成布林值

```javascript
Boolean(1);                 // true
Boolean(0);                 // false
Boolean("text");            // true
Boolean("");                // false
Boolean(null);              // false
Boolean(undefined);         // false
```

## 📝 本課重點回顧

- ✅ 變數用來儲存資料
- ✅ 使用 let 宣告可變變數，const 宣告常數
- ✅ 變數名稱要有意義，使用駝峰式命名
- ✅ JavaScript 有 8 種資料型別
- ✅ 最常用：Number、String、Boolean、Object、Array
- ✅ 使用 typeof 檢查資料型別
- ✅ 可以進行型別轉換

## 🎯 課後練習

1. **基礎練習**：宣告變數
   - 宣告姓名、年齡、城市變數
   - 使用 console.log() 輸出
   - 使用 typeof 檢查型別

2. **進階挑戰**：個人資料卡
   - 建立多個變數儲存個人資料
   - 使用模板字串組合訊息
   - 顯示在網頁上

3. **實戰練習**：計算程式
   - 宣告兩個數字變數
   - 計算加減乘除
   - 顯示結果

## 🔗 下一課預告

在下一課中，我們將學習運算子和控制流程，包括 if/else、for、while 等！

---

[← 上一課：JavaScript 基礎介紹](./19-javascript-introduction.md) | [返回目錄](../README.md) | [下一課：運算子和控制流程 →](./21-operators-control-flow.md)
