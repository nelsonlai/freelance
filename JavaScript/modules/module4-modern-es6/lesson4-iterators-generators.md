# Lesson 4: Iterators & Generators

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand iterator protocol and iterable objects
- Create custom iterators using Symbol.iterator
- Use generator functions with yield
- Implement lazy evaluation with generators
- Create infinite sequences
- Build custom data structures with iteration

## 📚 Iterator Protocol

### Making Objects Iterable
```javascript
class NumberRange {
    constructor(start, end) {
        this.start = start;
        this.end = end;
    }
    
    [Symbol.iterator]() {
        let current = this.start;
        const end = this.end;
        
        return {
            next() {
                if (current <= end) {
                    return { value: current++, done: false };
                } else {
                    return { done: true };
                }
            }
        };
    }
}

// Usage
const range = new NumberRange(1, 5);
for (const num of range) {
    console.log(num); // 1, 2, 3, 4, 5
}
```

## 🔄 Generator Functions

### Basic Generators
```javascript
function* numberGenerator() {
    yield 1;
    yield 2;
    yield 3;
}

const gen = numberGenerator();
console.log(gen.next().value); // 1
console.log(gen.next().value); // 2
console.log(gen.next().value); // 3
console.log(gen.next().done);  // true
```

### Infinite Generator
```javascript
function* fibonacci() {
    let a = 0, b = 1;
    while (true) {
        yield a;
        [a, b] = [b, a + b];
    }
}

const fib = fibonacci();
console.log(fib.next().value); // 0
console.log(fib.next().value); // 1
console.log(fib.next().value); // 1
console.log(fib.next().value); // 2
```

## 🎯 Practice Exercises

### Exercise 1: Custom Collection
Create a custom collection with iteration:

**Solution:**
```javascript
class CustomCollection {
    constructor() {
        this.items = [];
    }
    
    add(item) {
        this.items.push(item);
    }
    
    *[Symbol.iterator]() {
        for (const item of this.items) {
            yield item;
        }
    }
    
    *filter(predicate) {
        for (const item of this.items) {
            if (predicate(item)) {
                yield item;
            }
        }
    }
    
    *map(transform) {
        for (const item of this.items) {
            yield transform(item);
        }
    }
}

// Usage
const collection = new CustomCollection();
collection.add({ name: 'Alice', age: 30 });
collection.add({ name: 'Bob', age: 25 });
collection.add({ name: 'Charlie', age: 35 });

// Iterate over all items
for (const person of collection) {
    console.log(person.name);
}

// Filter and map
const adults = collection.filter(person => person.age >= 30);
const names = collection.map(person => person.name);
```

## 🎯 Key Takeaways

1. **Symbol.iterator** makes objects iterable
2. **Generator functions** use yield to pause execution
3. **Lazy evaluation** improves memory efficiency
4. **Custom iterators** enable flexible iteration
5. **Infinite sequences** are possible with generators

---

**Next Lesson**: [Lesson 5: Map, Set, WeakMap, WeakSet](./lesson5-collections.md)
