# 第 22 課：函式

## 📚 本課學習目標

- 理解函式的概念和用途
- 學會宣告和呼叫函式
- 掌握參數和回傳值
- 了解箭頭函式

## 🎯 什麼是函式？

**函式（Function）**是可重複使用的程式碼區塊。

## 📝 函式宣告

```javascript
// 函式宣告
function sayHello() {
    console.log('Hello!');
}

// 呼叫函式
sayHello();  // Hello!
```

## 🔢 參數和回傳值

```javascript
// 帶參數的函式
function greet(name) {
    console.log('你好，' + name);
}

greet('小明');  // 你好，小明

// 帶回傳值的函式
function add(a, b) {
    return a + b;
}

let result = add(5, 3);
console.log(result);  // 8
```

## ➡️ 箭頭函式

```javascript
// 傳統函式
function multiply(a, b) {
    return a * b;
}

// 箭頭函式
const multiply = (a, b) => a * b;
```

範例：`examples/lesson-22/example-01-functions.html`

## 📝 本課重點回顧

- ✅ 函式是可重複使用的程式碼區塊
- ✅ 使用 function 宣告函式
- ✅ 函式可以接收參數和回傳值
- ✅ 箭頭函式提供更簡潔的語法

---

[← 上一課](./21-operators-control-flow.md) | [返回目錄](../README.md) | [下一課 →](./23-arrays-objects.md)
