# 第 26 課：表單驗證

## 📚 本課學習目標

- 學會驗證表單輸入
- 掌握常見的驗證規則
- 了解錯誤訊息的顯示

## ✅ 表單驗證

```javascript
function validateForm() {
    let name = document.getElementById('name').value;
    let email = document.getElementById('email').value;
    
    // 檢查姓名
    if (name === '') {
        alert('請輸入姓名');
        return false;
    }
    
    // 檢查 Email
    if (!email.includes('@')) {
        alert('Email 格式不正確');
        return false;
    }
    
    return true;
}
```

範例：`examples/lesson-26/example-01-validation.html`

---

[← 上一課](./25-event-handling.md) | [返回目錄](../README.md) | [下一課 →](./27-ajax-fetch.md)
