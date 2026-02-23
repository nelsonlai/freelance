# 第 23 課：陣列和物件

## 📚 本課學習目標

- 掌握陣列的使用
- 學會物件的建立和操作
- 了解陣列和物件的方法

## 📦 陣列（Array）

```javascript
// 建立陣列
let fruits = ['蘋果', '香蕉', '橘子'];

// 存取元素
console.log(fruits[0]);  // 蘋果

// 新增元素
fruits.push('葡萄');     // 加到最後
fruits.unshift('草莓');  // 加到最前

// 刪除元素
fruits.pop();            // 刪除最後一個
fruits.shift();          // 刪除第一個
```

## 🎨 物件（Object）

```javascript
// 建立物件
let person = {
    name: '小明',
    age: 25,
    city: '台北'
};

// 存取屬性
console.log(person.name);      // 小明
console.log(person['age']);    // 25

// 修改屬性
person.age = 26;

// 新增屬性
person.email = 'ming@example.com';
```

範例：`examples/lesson-23/example-01-arrays-objects.html`

---

[← 上一課](./22-functions.md) | [返回目錄](../README.md) | [下一課 →](./24-dom-manipulation.md)
