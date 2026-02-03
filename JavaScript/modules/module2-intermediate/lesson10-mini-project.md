# Lesson 10: Mini Project - To-Do List App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete interactive web application
- Combine all concepts from Module 2
- Use DOM manipulation, events, and localStorage
- Create a functional to-do list with add/remove/complete features
- Apply modern JavaScript practices

## 📚 Project Overview

We'll build a complete to-do list application that allows users to:
- Add new tasks
- Mark tasks as complete
- Remove tasks
- Persist data in localStorage
- Have a clean, interactive interface

## 🏗️ Project Structure

```
todo-app/
├── index.html
├── style.css
└── script.js
```

## 📝 HTML Structure

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>To-Do List App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <h1>My To-Do List</h1>
        
        <form id="todoForm">
            <input type="text" id="todoInput" placeholder="Add a new task..." required>
            <button type="submit">Add Task</button>
        </form>
        
        <ul id="todoList"></ul>
        
        <div class="stats">
            <p>Total: <span id="totalCount">0</span></p>
            <p>Completed: <span id="completedCount">0</span></p>
        </div>
    </div>
    
    <script src="script.js"></script>
</body>
</html>
```

## 🎨 CSS Styling

```css
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: Arial, sans-serif;
    background-color: #f5f5f5;
    padding: 20px;
}

.container {
    max-width: 600px;
    margin: 0 auto;
    background: white;
    padding: 30px;
    border-radius: 10px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}

h1 {
    text-align: center;
    color: #333;
    margin-bottom: 30px;
}

#todoForm {
    display: flex;
    gap: 10px;
    margin-bottom: 30px;
}

#todoInput {
    flex: 1;
    padding: 12px;
    border: 2px solid #ddd;
    border-radius: 5px;
    font-size: 16px;
}

#todoInput:focus {
    outline: none;
    border-color: #007bff;
}

button {
    padding: 12px 20px;
    background-color: #007bff;
    color: white;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    font-size: 16px;
}

button:hover {
    background-color: #0056b3;
}

#todoList {
    list-style: none;
}

.todo-item {
    display: flex;
    align-items: center;
    padding: 15px;
    margin-bottom: 10px;
    background-color: #f8f9fa;
    border-radius: 5px;
    border-left: 4px solid #007bff;
}

.todo-item.completed {
    opacity: 0.6;
    border-left-color: #28a745;
}

.todo-item.completed .todo-text {
    text-decoration: line-through;
}

.todo-text {
    flex: 1;
    margin-left: 10px;
}

.todo-actions {
    display: flex;
    gap: 10px;
}

.toggle-btn, .delete-btn {
    padding: 8px 12px;
    border: none;
    border-radius: 3px;
    cursor: pointer;
    font-size: 14px;
}

.toggle-btn {
    background-color: #28a745;
    color: white;
}

.toggle-btn:hover {
    background-color: #218838;
}

.delete-btn {
    background-color: #dc3545;
    color: white;
}

.delete-btn:hover {
    background-color: #c82333;
}

.stats {
    display: flex;
    justify-content: space-between;
    margin-top: 20px;
    padding-top: 20px;
    border-top: 1px solid #ddd;
}

.stats p {
    font-weight: bold;
    color: #666;
}
```

## 💻 JavaScript Functionality

```javascript
class TodoApp {
    constructor() {
        this.todos = this.loadTodos();
        this.todoForm = document.getElementById('todoForm');
        this.todoInput = document.getElementById('todoInput');
        this.todoList = document.getElementById('todoList');
        this.totalCount = document.getElementById('totalCount');
        this.completedCount = document.getElementById('completedCount');
        
        this.init();
    }
    
    init() {
        this.todoForm.addEventListener('submit', (e) => this.addTodo(e));
        this.renderTodos();
        this.updateStats();
    }
    
    addTodo(e) {
        e.preventDefault();
        
        const text = this.todoInput.value.trim();
        if (!text) return;
        
        const todo = {
            id: Date.now(),
            text: text,
            completed: false,
            createdAt: new Date().toISOString()
        };
        
        this.todos.push(todo);
        this.todoInput.value = '';
        this.saveTodos();
        this.renderTodos();
        this.updateStats();
    }
    
    toggleTodo(id) {
        const todo = this.todos.find(t => t.id === id);
        if (todo) {
            todo.completed = !todo.completed;
            this.saveTodos();
            this.renderTodos();
            this.updateStats();
        }
    }
    
    deleteTodo(id) {
        this.todos = this.todos.filter(t => t.id !== id);
        this.saveTodos();
        this.renderTodos();
        this.updateStats();
    }
    
    renderTodos() {
        this.todoList.innerHTML = '';
        
        this.todos.forEach(todo => {
            const li = document.createElement('li');
            li.className = `todo-item ${todo.completed ? 'completed' : ''}`;
            
            li.innerHTML = `
                <input type="checkbox" ${todo.completed ? 'checked' : ''} 
                       onchange="app.toggleTodo(${todo.id})">
                <span class="todo-text">${todo.text}</span>
                <div class="todo-actions">
                    <button class="toggle-btn" onclick="app.toggleTodo(${todo.id})">
                        ${todo.completed ? 'Undo' : 'Complete'}
                    </button>
                    <button class="delete-btn" onclick="app.deleteTodo(${todo.id})">
                        Delete
                    </button>
                </div>
            `;
            
            this.todoList.appendChild(li);
        });
    }
    
    updateStats() {
        this.totalCount.textContent = this.todos.length;
        this.completedCount.textContent = this.todos.filter(t => t.completed).length;
    }
    
    saveTodos() {
        localStorage.setItem('todos', JSON.stringify(this.todos));
    }
    
    loadTodos() {
        const todosJson = localStorage.getItem('todos');
        return todosJson ? JSON.parse(todosJson) : [];
    }
}

// Initialize the app
const app = new TodoApp();
```

## 🎯 Key Features Implemented

1. **Add Tasks** - Form submission with validation
2. **Toggle Completion** - Checkbox and button functionality
3. **Delete Tasks** - Remove tasks from the list
4. **Persistent Storage** - Data saved in localStorage
5. **Statistics** - Total and completed task counts
6. **Responsive Design** - Clean, modern interface

## 🎯 Key Takeaways

1. **Classes** organize complex application logic
2. **Event listeners** handle user interactions
3. **DOM manipulation** updates the interface
4. **localStorage** persists data between sessions
5. **Modern JavaScript** features make code cleaner

## 🚀 Next Steps

Congratulations! You've completed Module 2. You now understand:

- Scope and hoisting
- Destructuring and spread/rest operators
- Template literals
- Modules and imports/exports
- Classes and object-oriented programming
- Error handling
- DOM manipulation
- Event handling
- JSON and localStorage
- Building complete applications

**Ready for Module 3: Advanced JavaScript!** 🎉

---

**Next Module**: [Module 3: Advanced JavaScript](../module3-advanced/README.md)
