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
