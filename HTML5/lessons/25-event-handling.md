# 第 25 課：事件處理

## 📚 本課學習目標

- 理解事件的概念
- 學會監聽和處理事件
- 掌握常用的事件類型

## 🎯 什麼是事件？

**事件（Event）**是使用者或瀏覽器執行的動作，如點擊、輸入、載入等。

## 👆 常用事件

```javascript
// 點擊事件
button.addEventListener('click', function() {
    console.log('按鈕被點擊了！');
});

// 輸入事件
input.addEventListener('input', function(event) {
    console.log('輸入值：', event.target.value);
});

// 滑鼠移入/移出
element.addEventListener('mouseenter', function() {
    console.log('滑鼠移入');
});
```

範例：`examples/lesson-25/example-01-events.html`

---

[← 上一課](./24-dom-manipulation.md) | [返回目錄](../README.md) | [下一課 →](./26-form-validation.md)
