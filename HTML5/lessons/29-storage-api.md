# 第 29 課：本地儲存和 API

## 📚 本課學習目標

- 學會使用 localStorage
- 了解 sessionStorage
- 掌握資料的儲存和讀取

## 💾 localStorage

```javascript
// 儲存資料
localStorage.setItem('name', '小明');
localStorage.setItem('age', '25');

// 讀取資料
let name = localStorage.getItem('name');
console.log(name);  // 小明

// 刪除資料
localStorage.removeItem('name');

// 清除所有資料
localStorage.clear();

// 儲存物件
let user = {name: '小明', age: 25};
localStorage.setItem('user', JSON.stringify(user));

// 讀取物件
let userData = JSON.parse(localStorage.getItem('user'));
```

範例：`examples/lesson-29/example-01-storage.html`

---

[← 上一課](./28-es6-features.md) | [返回目錄](../README.md) | [下一課 →](./30-final-project.md)
