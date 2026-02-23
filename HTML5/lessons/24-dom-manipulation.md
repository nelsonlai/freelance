# 第 24 課：DOM 操作

## 📚 本課學習目標

- 理解 DOM 的概念
- 學會選取和操作 HTML 元素
- 掌握修改樣式和內容的方法

## 🌳 什麼是 DOM？

**DOM（Document Object Model）**是網頁的程式化表示，讓 JavaScript 可以存取和操作 HTML 元素。

## 🔍 選取元素

```javascript
// 透過 ID 選取
let element = document.getElementById('myId');

// 透過 class 選取
let elements = document.getElementsByClassName('myClass');

// 透過標籤名稱選取
let paragraphs = document.getElementsByTagName('p');

// 使用 querySelector
let first = document.querySelector('.myClass');
let all = document.querySelectorAll('.myClass');
```

## ✏️ 修改內容

```javascript
// 修改文字內容
element.textContent = '新文字';

// 修改 HTML 內容
element.innerHTML = '<strong>粗體文字</strong>';

// 修改屬性
element.setAttribute('src', 'new-image.jpg');
```

範例：`examples/lesson-24/example-01-dom.html`

---

[← 上一課](./23-arrays-objects.md) | [返回目錄](../README.md) | [下一課 →](./25-event-handling.md)
