# 第 28 課：ES6+ 新特性

## 📚 本課學習目標

- 掌握 ES6 的新語法
- 學會解構賦值
- 了解展開運算子和其他新特性

## ✨ ES6 新特性

### let 和 const

```javascript
let variable = 'can change';
const constant = 'cannot change';
```

### 箭頭函式

```javascript
const add = (a, b) => a + b;
```

### 解構賦值

```javascript
// 陣列解構
let [a, b] = [1, 2];

// 物件解構
let {name, age} = {name: '小明', age: 25};
```

### 展開運算子

```javascript
let arr1 = [1, 2, 3];
let arr2 = [...arr1, 4, 5];  // [1, 2, 3, 4, 5]
```

範例：`examples/lesson-28/example-01-es6.html`

---

[← 上一課](./27-ajax-fetch.md) | [返回目錄](../README.md) | [下一課 →](./29-storage-api.md)
