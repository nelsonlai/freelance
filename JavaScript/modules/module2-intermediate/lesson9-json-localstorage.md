# Lesson 9: JSON & LocalStorage

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Convert JavaScript objects to JSON strings
- Parse JSON strings back to JavaScript objects
- Store data in browser localStorage
- Retrieve data from localStorage
- Persist data between browser sessions

## 📚 What is JSON?

**JSON (JavaScript Object Notation)** is a text format for storing and exchanging data.

### Converting to JSON
```javascript
let person = {
    name: "Alice",
    age: 30,
    city: "New York"
};

let jsonString = JSON.stringify(person);
console.log(jsonString); // '{"name":"Alice","age":30,"city":"New York"}'
```

### Parsing JSON
```javascript
let jsonString = '{"name":"Alice","age":30,"city":"New York"}';
let person = JSON.parse(jsonString);
console.log(person.name); // "Alice"
```

## 💾 LocalStorage

**localStorage** allows you to store data in the browser that persists between sessions.

### Storing Data
```javascript
// Store simple data
localStorage.setItem('username', 'Alice');
localStorage.setItem('score', '100');

// Store complex data (convert to JSON first)
let user = { name: "Alice", age: 30 };
localStorage.setItem('user', JSON.stringify(user));
```

### Retrieving Data
```javascript
// Get simple data
let username = localStorage.getItem('username');
let score = localStorage.getItem('score');

// Get complex data (parse JSON)
let userJson = localStorage.getItem('user');
let user = JSON.parse(userJson);
```

### Removing Data
```javascript
localStorage.removeItem('username'); // Remove specific item
localStorage.clear(); // Remove all items
```

## 🎯 Practice Exercises

### Exercise 1: User Preferences
Create a system to save and load user preferences:

**Solution:**
```javascript
// Save preferences
function savePreferences(theme, language) {
    let preferences = {
        theme: theme,
        language: language,
        lastUpdated: new Date().toISOString()
    };
    localStorage.setItem('preferences', JSON.stringify(preferences));
}

// Load preferences
function loadPreferences() {
    let preferencesJson = localStorage.getItem('preferences');
    if (preferencesJson) {
        return JSON.parse(preferencesJson);
    }
    return { theme: 'light', language: 'en' };
}

// Usage
savePreferences('dark', 'es');
let prefs = loadPreferences();
console.log(prefs); // { theme: 'dark', language: 'es', lastUpdated: '...' }
```

### Exercise 2: Todo List Storage
Create functions to save and load a todo list:

**Solution:**
```javascript
let todos = [
    { id: 1, text: "Learn JavaScript", completed: false },
    { id: 2, text: "Build a project", completed: true }
];

// Save todos
function saveTodos() {
    localStorage.setItem('todos', JSON.stringify(todos));
}

// Load todos
function loadTodos() {
    let todosJson = localStorage.getItem('todos');
    if (todosJson) {
        todos = JSON.parse(todosJson);
    }
    return todos;
}

// Usage
saveTodos();
let loadedTodos = loadTodos();
console.log(loadedTodos);
```

## 🎯 Key Takeaways

1. **JSON.stringify()** converts objects to strings
2. **JSON.parse()** converts strings to objects
3. **localStorage.setItem()** stores data
4. **localStorage.getItem()** retrieves data
5. **Data persists** between browser sessions

---

**Next Lesson**: [Lesson 10: Mini Project - To-Do List App](./lesson10-mini-project.md)
