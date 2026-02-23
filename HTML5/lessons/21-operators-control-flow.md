# 第 21 課：運算子和控制流程

## 📚 本課學習目標

- 掌握各種運算子的使用
- 學會 if/else 條件判斷
- 了解 switch 語句
- 掌握迴圈（for、while）

## ➕ 算術運算子

```javascript
let a = 10;
let b = 3;

console.log(a + b);  // 13 加法
console.log(a - b);  // 7  減法
console.log(a * b);  // 30 乘法
console.log(a / b);  // 3.333... 除法
console.log(a % b);  // 1  餘數
console.log(a ** b); // 1000 次方
```

## 📊 比較運算子

```javascript
let x = 5;

console.log(x == 5);   // true  相等（值相等）
console.log(x === 5);  // true  嚴格相等（值和型別都相等）
console.log(x == '5'); // true
console.log(x === '5'); // false

console.log(x != 5);   // false 不相等
console.log(x !== '5'); // true  嚴格不相等

console.log(x > 3);    // true  大於
console.log(x < 10);   // true  小於
console.log(x >= 5);   // true  大於等於
console.log(x <= 5);   // true  小於等於
```

## 🔀 if/else 條件判斷

```javascript
let age = 18;

if (age >= 18) {
    console.log('已成年');
} else {
    console.log('未成年');
}

// else if
let score = 85;

if (score >= 90) {
    console.log('優秀');
} else if (score >= 80) {
    console.log('良好');
} else if (score >= 60) {
    console.log('及格');
} else {
    console.log('不及格');
}
```

## 🔁 迴圈

### for 迴圈

```javascript
// 印出 1 到 10
for (let i = 1; i <= 10; i++) {
    console.log(i);
}

// 陣列迴圈
let colors = ['紅', '綠', '藍'];
for (let i = 0; i < colors.length; i++) {
    console.log(colors[i]);
}
```

### while 迴圈

```javascript
let count = 0;

while (count < 5) {
    console.log(count);
    count++;
}
```

請參考範例：`examples/lesson-21/example-01-operators.html`

## 📝 本課重點回顧

- ✅ 算術運算子：+、-、*、/、%、**
- ✅ 比較運算子：==、===、!=、!==、>、<、>=、<=
- ✅ if/else 用於條件判斷
- ✅ for 和 while 用於重複執行代碼

## 🎯 課後練習

1. 建立成績判定程式
2. 使用迴圈印出九九乘法表
3. 建立簡單的猜數字遊戲

---

[← 上一課：變數和資料型別](./20-variables-datatypes.md) | [返回目錄](../README.md) | [下一課：函式 →](./22-functions.md)
