# Lesson 6: Symbols and Metadata

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand what symbols are and why they're useful
- Create and use symbols as unique identifiers
- Use well-known symbols (Symbol.iterator, Symbol.toPrimitive)
- Implement symbol-based metadata
- Create private properties using symbols
- Build extensible APIs with symbols

## 📚 Symbol Basics

### Creating Symbols
```javascript
// Basic symbol
const id = Symbol('id');
const name = Symbol('name');

// Symbols are always unique
const sym1 = Symbol('test');
const sym2 = Symbol('test');
console.log(sym1 === sym2); // false

// Global symbol registry
const globalSym = Symbol.for('global');
const sameGlobalSym = Symbol.for('global');
console.log(globalSym === sameGlobalSym); // true
```

### Using Symbols as Properties
```javascript
const user = {
    name: 'Alice',
    age: 30
};

const id = Symbol('id');
user[id] = 'user-123';

// Symbol properties don't appear in normal iteration
console.log(Object.keys(user)); // ['name', 'age']
console.log(Object.getOwnPropertySymbols(user)); // [Symbol(id)]
```

## 🔧 Well-Known Symbols

### Symbol.iterator
```javascript
class Counter {
    constructor(max) {
        this.max = max;
    }
    
    [Symbol.iterator]() {
        let count = 0;
        const max = this.max;
        
        return {
            next() {
                if (count < max) {
                    return { value: count++, done: false };
                } else {
                    return { done: true };
                }
            }
        };
    }
}

const counter = new Counter(3);
for (const num of counter) {
    console.log(num); // 0, 1, 2
}
```

### Symbol.toPrimitive
```javascript
class Temperature {
    constructor(celsius) {
        this.celsius = celsius;
    }
    
    [Symbol.toPrimitive](hint) {
        switch (hint) {
            case 'number':
                return this.celsius;
            case 'string':
                return `${this.celsius}°C`;
            case 'default':
                return this.celsius;
        }
    }
}

const temp = new Temperature(25);
console.log(+temp); // 25 (number)
console.log(`${temp}`); // "25°C" (string)
console.log(temp + 5); // 30 (default)
```

## 🎯 Practice Exercises

### Exercise 1: Private Properties
Create a class with private properties using symbols:

**Solution:**
```javascript
const _balance = Symbol('balance');
const _transactions = Symbol('transactions');

class BankAccount {
    constructor(initialBalance = 0) {
        this[_balance] = initialBalance;
        this[_transactions] = [];
    }
    
    deposit(amount) {
        if (amount > 0) {
            this[_balance] += amount;
            this[_transactions].push({ type: 'deposit', amount, date: new Date() });
            return true;
        }
        return false;
    }
    
    withdraw(amount) {
        if (amount > 0 && amount <= this[_balance]) {
            this[_balance] -= amount;
            this[_transactions].push({ type: 'withdrawal', amount, date: new Date() });
            return true;
        }
        return false;
    }
    
    getBalance() {
        return this[_balance];
    }
    
    getTransactions() {
        return [...this[_transactions]]; // Return copy
    }
}

// Usage
const account = new BankAccount(100);
account.deposit(50);
account.withdraw(25);

console.log(account.getBalance()); // 125
console.log(account.getTransactions());
// Private properties are not accessible from outside
console.log(account[_balance]); // undefined (if _balance is not in scope)
```

### Exercise 2: Metadata System
Create a metadata system using symbols:

**Solution:**
```javascript
const METADATA = Symbol('metadata');

function addMetadata(obj, key, value) {
    if (!obj[METADATA]) {
        obj[METADATA] = new Map();
    }
    obj[METADATA].set(key, value);
}

function getMetadata(obj, key) {
    return obj[METADATA]?.get(key);
}

function getAllMetadata(obj) {
    return obj[METADATA] ? Object.fromEntries(obj[METADATA]) : {};
}

// Usage
const user = { name: 'Alice', age: 30 };

addMetadata(user, 'created', new Date());
addMetadata(user, 'version', '1.0');
addMetadata(user, 'tags', ['premium', 'verified']);

console.log(getMetadata(user, 'created'));
console.log(getAllMetadata(user));

// Metadata doesn't interfere with normal properties
console.log(Object.keys(user)); // ['name', 'age']
```

## 🎯 Key Takeaways

1. **Symbols** are unique identifiers
2. **Symbol properties** don't appear in normal iteration
3. **Well-known symbols** enable custom behavior
4. **Symbols** can create private-like properties
5. **Metadata** can be attached without property conflicts

## 🚀 Next Steps

Great! You now understand symbols and metadata. In the next lesson, we'll learn about:

- **Modern build tools** - Webpack and Vite
- **Module bundling** - combining multiple files
- **Development vs production** builds

---

**Next Lesson**: [Lesson 7: Modules with Webpack / Vite](./lesson7-modules-build.md)
