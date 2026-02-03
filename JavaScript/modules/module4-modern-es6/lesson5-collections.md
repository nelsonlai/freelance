# Lesson 5: Map, Set, WeakMap, WeakSet

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use Map for key-value pairs with any key type
- Use Set for unique value collections
- Understand WeakMap and WeakSet for memory management
- Choose the right collection type for different use cases
- Implement efficient data structures
- Avoid memory leaks with weak collections

## 📚 Map Collection

### Basic Map Usage
```javascript
// Creating and using Map
const userMap = new Map();

// Set values
userMap.set('alice', { name: 'Alice', age: 30 });
userMap.set('bob', { name: 'Bob', age: 25 });

// Get values
console.log(userMap.get('alice')); // { name: 'Alice', age: 30 }

// Check if key exists
console.log(userMap.has('alice')); // true

// Delete entries
userMap.delete('bob');

// Get size
console.log(userMap.size); // 1

// Iterate over Map
for (const [key, value] of userMap) {
    console.log(`${key}: ${value.name}`);
}
```

### Map vs Object
```javascript
// Object limitations
const obj = {};
obj[1] = 'one';
obj['1'] = 'one string'; // Overwrites previous
console.log(obj); // { '1': 'one string' }

// Map advantages
const map = new Map();
map.set(1, 'one');
map.set('1', 'one string'); // Different keys
console.log(map.get(1)); // 'one'
console.log(map.get('1')); // 'one string'
```

## 📚 Set Collection

### Basic Set Usage
```javascript
// Creating and using Set
const uniqueNumbers = new Set();

// Add values
uniqueNumbers.add(1);
uniqueNumbers.add(2);
uniqueNumbers.add(1); // Duplicate ignored

console.log(uniqueNumbers.size); // 2

// Check if value exists
console.log(uniqueNumbers.has(1)); // true

// Delete values
uniqueNumbers.delete(2);

// Iterate over Set
for (const num of uniqueNumbers) {
    console.log(num);
}
```

### Set Operations
```javascript
const set1 = new Set([1, 2, 3, 4]);
const set2 = new Set([3, 4, 5, 6]);

// Union
const union = new Set([...set1, ...set2]);
console.log(union); // Set {1, 2, 3, 4, 5, 6}

// Intersection
const intersection = new Set([...set1].filter(x => set2.has(x)));
console.log(intersection); // Set {3, 4}

// Difference
const difference = new Set([...set1].filter(x => !set2.has(x)));
console.log(difference); // Set {1, 2}
```

## 🔗 WeakMap and WeakSet

### WeakMap for Private Data
```javascript
const privateData = new WeakMap();

class User {
    constructor(name, age) {
        this.name = name;
        // Store private data in WeakMap
        privateData.set(this, { age, secret: 'hidden' });
    }
    
    getAge() {
        return privateData.get(this).age;
    }
    
    getSecret() {
        return privateData.get(this).secret;
    }
}

const user = new User('Alice', 30);
console.log(user.getAge()); // 30
console.log(user.getSecret()); // 'hidden'
// privateData is not accessible from outside
```

### WeakSet for Tracking
```javascript
const processedElements = new WeakSet();

function processElement(element) {
    if (processedElements.has(element)) {
        console.log('Element already processed');
        return;
    }
    
    // Process the element
    console.log('Processing element');
    processedElements.add(element);
}

const div1 = document.createElement('div');
const div2 = document.createElement('div');

processElement(div1); // "Processing element"
processElement(div1); // "Element already processed"
processElement(div2); // "Processing element"
```

## 🎯 Practice Exercises

### Exercise 1: Cache Implementation
Create a cache using Map:

**Solution:**
```javascript
class Cache {
    constructor(maxSize = 100) {
        this.cache = new Map();
        this.maxSize = maxSize;
    }
    
    set(key, value) {
        // Remove oldest entry if cache is full
        if (this.cache.size >= this.maxSize) {
            const firstKey = this.cache.keys().next().value;
            this.cache.delete(firstKey);
        }
        
        this.cache.set(key, value);
    }
    
    get(key) {
        const value = this.cache.get(key);
        
        // Move to end (LRU behavior)
        if (value !== undefined) {
            this.cache.delete(key);
            this.cache.set(key, value);
        }
        
        return value;
    }
    
    has(key) {
        return this.cache.has(key);
    }
    
    clear() {
        this.cache.clear();
    }
    
    size() {
        return this.cache.size;
    }
}

// Usage
const cache = new Cache(3);
cache.set('user:1', { name: 'Alice' });
cache.set('user:2', { name: 'Bob' });
cache.set('user:3', { name: 'Charlie' });
cache.set('user:4', { name: 'David' }); // Removes user:1

console.log(cache.get('user:1')); // undefined
console.log(cache.get('user:2')); // { name: 'Bob' }
```

### Exercise 2: Event System
Create an event system using Map and Set:

**Solution:**
```javascript
class EventEmitter {
    constructor() {
        this.events = new Map();
    }
    
    on(event, callback) {
        if (!this.events.has(event)) {
            this.events.set(event, new Set());
        }
        this.events.get(event).add(callback);
    }
    
    off(event, callback) {
        if (this.events.has(event)) {
            this.events.get(event).delete(callback);
        }
    }
    
    emit(event, ...args) {
        if (this.events.has(event)) {
            for (const callback of this.events.get(event)) {
                callback(...args);
            }
        }
    }
    
    once(event, callback) {
        const onceCallback = (...args) => {
            callback(...args);
            this.off(event, onceCallback);
        };
        this.on(event, onceCallback);
    }
}

// Usage
const emitter = new EventEmitter();

emitter.on('user:login', (user) => {
    console.log(`User ${user.name} logged in`);
});

emitter.once('user:logout', (user) => {
    console.log(`User ${user.name} logged out`);
});

emitter.emit('user:login', { name: 'Alice' });
emitter.emit('user:logout', { name: 'Alice' });
emitter.emit('user:logout', { name: 'Bob' }); // Won't trigger
```

## 🎯 Key Takeaways

1. **Map** allows any key type, not just strings
2. **Set** stores unique values efficiently
3. **WeakMap** enables private data without memory leaks
4. **WeakSet** tracks objects without preventing garbage collection
5. **Choose the right collection** for your use case

## 🚀 Next Steps

Great! You now understand modern collections. In the next lesson, we'll learn about:

- **Symbols** - unique identifiers
- **Symbol properties** - well-known symbols
- **Metadata** - using symbols for object metadata

---

**Next Lesson**: [Lesson 6: Symbols and Metadata](./lesson6-symbols.md)
