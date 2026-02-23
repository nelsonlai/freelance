# 第 27 課：AJAX 和 Fetch API

## 📚 本課學習目標

- 理解 AJAX 的概念
- 學會使用 Fetch API
- 掌握非同步資料請求

## 🌐 Fetch API

```javascript
// GET 請求
fetch('https://api.example.com/data')
    .then(response => response.json())
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('錯誤：', error);
    });

// POST 請求
fetch('https://api.example.com/data', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json'
    },
    body: JSON.stringify({name: '小明', age: 25})
})
    .then(response => response.json())
    .then(data => console.log(data));
```

範例：`examples/lesson-27/example-01-fetch.html`

---

[← 上一課](./26-form-validation.md) | [返回目錄](../README.md) | [下一課 →](./28-es6-features.md)
