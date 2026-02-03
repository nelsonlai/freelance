# Lesson 2: Destructuring & Spread/Rest

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Extract values from arrays using destructuring
- Extract properties from objects using destructuring
- Use spread operator to expand arrays and objects
- Use rest operator to collect remaining elements
- Apply destructuring in function parameters
- Write cleaner, more readable code

## 📚 What is Destructuring?

**Destructuring** is a way to extract values from arrays or properties from objects into distinct variables. It's like unpacking a box and putting each item in its own container.

## 📦 Array Destructuring

### Basic Array Destructuring
```javascript
let colors = ["red", "green", "blue"];

// Old way
let firstColor = colors[0];
let secondColor = colors[1];
let thirdColor = colors[2];

// New way with destructuring
let [first, second, third] = colors;
console.log(first);  // "red"
console.log(second);  // "green"
console.log(third);   // "blue"
```

### Skipping Elements
```javascript
let numbers = [1, 2, 3, 4, 5];
let [first, , third, , fifth] = numbers;
console.log(first);  // 1
console.log(third);  // 3
console.log(fifth);  // 5
```

### Default Values
```javascript
let colors = ["red"];
let [first, second = "green", third = "blue"] = colors;
console.log(first);   // "red"
console.log(second);  // "green" (default)
console.log(third);   // "blue" (default)
```

### Rest Operator in Arrays
```javascript
let numbers = [1, 2, 3, 4, 5];
let [first, second, ...rest] = numbers;
console.log(first);  // 1
console.log(second); // 2
console.log(rest);   // [3, 4, 5]
```

## 🏠 Object Destructuring

### Basic Object Destructuring
```javascript
let person = {
    name: "Alice",
    age: 30,
    city: "New York"
};

// Old way
let name = person.name;
let age = person.age;
let city = person.city;

// New way with destructuring
let { name, age, city } = person;
console.log(name);  // "Alice"
console.log(age);   // 30
console.log(city);  // "New York"
```

### Renaming Variables
```javascript
let person = {
    name: "Alice",
    age: 30
};

let { name: fullName, age: years } = person;
console.log(fullName);  // "Alice"
console.log(years);    // 30
```

### Default Values
```javascript
let person = {
    name: "Alice"
};

let { name, age = 25, city = "Unknown" } = person;
console.log(name);  // "Alice"
console.log(age);   // 25 (default)
console.log(city);  // "Unknown" (default)
```

### Nested Destructuring
```javascript
let user = {
    name: "Alice",
    address: {
        street: "123 Main St",
        city: "New York"
    }
};

let { name, address: { street, city } } = user;
console.log(name);   // "Alice"
console.log(street); // "123 Main St"
console.log(city);   // "New York"
```

## 🔄 Spread Operator

The **spread operator** (`...`) expands arrays and objects.

### Array Spread
```javascript
let arr1 = [1, 2, 3];
let arr2 = [4, 5, 6];
let combined = [...arr1, ...arr2];
console.log(combined); // [1, 2, 3, 4, 5, 6]

// Copy array
let original = [1, 2, 3];
let copy = [...original];
console.log(copy); // [1, 2, 3]
```

### Object Spread
```javascript
let obj1 = { a: 1, b: 2 };
let obj2 = { c: 3, d: 4 };
let combined = { ...obj1, ...obj2 };
console.log(combined); // { a: 1, b: 2, c: 3, d: 4 }

// Override properties
let person = { name: "Alice", age: 30 };
let updated = { ...person, age: 31 };
console.log(updated); // { name: "Alice", age: 31 }
```

## 📥 Rest Operator

The **rest operator** (`...`) collects remaining elements.

### In Arrays
```javascript
let numbers = [1, 2, 3, 4, 5];
let [first, ...rest] = numbers;
console.log(first); // 1
console.log(rest);   // [2, 3, 4, 5]
```

### In Objects
```javascript
let person = {
    name: "Alice",
    age: 30,
    city: "New York",
    country: "USA"
};

let { name, ...details } = person;
console.log(name);    // "Alice"
console.log(details); // { age: 30, city: "New York", country: "USA" }
```

### In Function Parameters
```javascript
function sum(...numbers) {
    return numbers.reduce((total, num) => total + num, 0);
}

console.log(sum(1, 2, 3));        // 6
console.log(sum(1, 2, 3, 4, 5));   // 15
```

## 🎯 Practice Exercises

### Exercise 1: Array Destructuring
Extract the first, third, and last elements from an array:

**Solution:**
```javascript
let fruits = ["apple", "banana", "orange", "grape", "kiwi"];
let [first, , third, ...rest] = fruits;
let last = rest[rest.length - 1];

console.log("First:", first);   // "apple"
console.log("Third:", third);  // "orange"
console.log("Last:", last);    // "kiwi"
```

### Exercise 2: Object Destructuring
Extract and rename properties from an object:

**Solution:**
```javascript
let student = {
    firstName: "Alice",
    lastName: "Smith",
    grade: 95,
    subject: "Math"
};

let { firstName: fName, lastName: lName, grade: score } = student;
console.log("Name:", fName, lName); // "Alice Smith"
console.log("Score:", score);       // 95
```

### Exercise 3: Spread and Rest
Create a function that combines arrays and uses rest parameters:

**Solution:**
```javascript
function combineArrays(...arrays) {
    return arrays.flat();
}

let arr1 = [1, 2];
let arr2 = [3, 4];
let arr3 = [5, 6];

let result = combineArrays(arr1, arr2, arr3);
console.log(result); // [1, 2, 3, 4, 5, 6]
```

## 🚨 Common Mistakes to Avoid

### 1. Confusing Spread and Rest
```javascript
// Spread - expands
let arr = [1, 2, 3];
let spread = [...arr]; // [1, 2, 3]

// Rest - collects
let [first, ...rest] = arr; // first = 1, rest = [2, 3]
```

### 2. Destructuring Non-existent Properties
```javascript
let obj = { a: 1 };
let { a, b } = obj;
console.log(a); // 1
console.log(b); // undefined
```

### 3. Forgetting Default Values
```javascript
let obj = { a: 1 };
let { a, b = "default" } = obj;
console.log(b); // "default"
```

## 🎯 Key Takeaways

1. **Destructuring** extracts values from arrays/objects
2. **Array destructuring** uses square brackets `[]`
3. **Object destructuring** uses curly braces `{}`
4. **Spread operator** expands arrays/objects
5. **Rest operator** collects remaining elements
6. **Default values** prevent undefined errors
7. **Renaming** allows custom variable names

## 🚀 Next Steps

Excellent! You now understand destructuring and spread/rest operators. In the next lesson, we'll learn about:

- **Template literals** - dynamic string creation
- **String interpolation** - embedding variables in strings
- **Multi-line strings** - cleaner string formatting

## 📚 Additional Resources

- [MDN Destructuring](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Destructuring_assignment)
- [MDN Spread Syntax](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Spread_syntax)
- [JavaScript.info Destructuring](https://javascript.info/destructuring-assignment)

## 🎉 Congratulations!

You've mastered destructuring and spread/rest operators! You now know how to:

- Extract values from arrays and objects efficiently
- Use spread operator to combine and copy data
- Use rest operator to collect remaining elements
- Write cleaner, more readable code

Practice with the exercises, and get ready for Lesson 3 where we'll learn about template literals!

---

**Next Lesson**: [Lesson 3: Template Literals](./lesson3-template-literals.md)
