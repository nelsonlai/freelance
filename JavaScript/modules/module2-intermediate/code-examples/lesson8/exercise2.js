// Exercise 2: Interactive Todo Application
// This exercise demonstrates comprehensive event handling in a todo app

console.log("=== Exercise 2: Interactive Todo Application ===");

// Todo item class
class TodoItem {
    constructor(id, text, completed = false, priority = 'medium') {
        this.id = id;
        this.text = text;
        this.completed = completed;
        this.priority = priority;
        this.createdAt = new Date().toISOString();
        this.updatedAt = new Date().toISOString();
    }
    
    toggle() {
        this.completed = !this.completed;
        this.updatedAt = new Date().toISOString();
    }
    
    updateText(newText) {
        this.text = newText;
        this.updatedAt = new Date().toISOString();
    }
    
    setPriority(priority) {
        this.priority = priority;
        this.updatedAt = new Date().toISOString();
    }
}

// Todo application class
class TodoApp {
    constructor() {
        this.todos = [];
        this.nextId = 1;
        this.filter = 'all'; // all, active, completed
        this.sortBy = 'created'; // created, priority, text
        this.eventListeners = {};
    }
    
    addEventListener(event, handler) {
        if (!this.eventListeners[event]) {
            this.eventListeners[event] = [];
        }
        this.eventListeners[event].push(handler);
    }
    
    dispatchEvent(event, data = {}) {
        if (this.eventListeners[event]) {
            this.eventListeners[event].forEach(handler => {
                handler({ ...data, app: this });
            });
        }
    }
    
    addTodo(text, priority = 'medium') {
        const todo = new TodoItem(this.nextId++, text, false, priority);
        this.todos.push(todo);
        
        this.dispatchEvent('todoAdded', { todo });
        this.dispatchEvent('todosChanged', { todos: this.todos });
        
        return todo;
    }
    
    removeTodo(id) {
        const index = this.todos.findIndex(todo => todo.id === id);
        if (index > -1) {
            const todo = this.todos[index];
            this.todos.splice(index, 1);
            
            this.dispatchEvent('todoRemoved', { todo });
            this.dispatchEvent('todosChanged', { todos: this.todos });
            
            return true;
        }
        return false;
    }
    
    toggleTodo(id) {
        const todo = this.todos.find(todo => todo.id === id);
        if (todo) {
            todo.toggle();
            
            this.dispatchEvent('todoToggled', { todo });
            this.dispatchEvent('todosChanged', { todos: this.todos });
            
            return true;
        }
        return false;
    }
    
    updateTodo(id, updates) {
        const todo = this.todos.find(todo => todo.id === id);
        if (todo) {
            Object.assign(todo, updates);
            todo.updatedAt = new Date().toISOString();
            
            this.dispatchEvent('todoUpdated', { todo });
            this.dispatchEvent('todosChanged', { todos: this.todos });
            
            return true;
        }
        return false;
    }
    
    setFilter(filter) {
        this.filter = filter;
        this.dispatchEvent('filterChanged', { filter });
        this.dispatchEvent('todosChanged', { todos: this.todos });
    }
    
    setSortBy(sortBy) {
        this.sortBy = sortBy;
        this.dispatchEvent('sortChanged', { sortBy });
        this.dispatchEvent('todosChanged', { todos: this.todos });
    }
    
    getFilteredTodos() {
        let filtered = this.todos;
        
        // Apply filter
        switch (this.filter) {
            case 'active':
                filtered = filtered.filter(todo => !todo.completed);
                break;
            case 'completed':
                filtered = filtered.filter(todo => todo.completed);
                break;
        }
        
        // Apply sorting
        switch (this.sortBy) {
            case 'priority':
                const priorityOrder = { high: 3, medium: 2, low: 1 };
                filtered.sort((a, b) => priorityOrder[b.priority] - priorityOrder[a.priority]);
                break;
            case 'text':
                filtered.sort((a, b) => a.text.localeCompare(b.text));
                break;
            case 'created':
            default:
                filtered.sort((a, b) => new Date(a.createdAt) - new Date(b.createdAt));
                break;
        }
        
        return filtered;
    }
    
    clearCompleted() {
        const completedTodos = this.todos.filter(todo => todo.completed);
        this.todos = this.todos.filter(todo => !todo.completed);
        
        this.dispatchEvent('completedCleared', { clearedTodos: completedTodos });
        this.dispatchEvent('todosChanged', { todos: this.todos });
        
        return completedTodos.length;
    }
    
    getStats() {
        const total = this.todos.length;
        const completed = this.todos.filter(todo => todo.completed).length;
        const active = total - completed;
        
        return { total, completed, active };
    }
}

// Todo UI class
class TodoUI {
    constructor(app) {
        this.app = app;
        this.setupEventListeners();
    }
    
    setupEventListeners() {
        // Todo events
        this.app.addEventListener('todoAdded', (event) => {
            console.log(`✓ Todo added: "${event.todo.text}" (${event.todo.priority})`);
        });
        
        this.app.addEventListener('todoRemoved', (event) => {
            console.log(`✗ Todo removed: "${event.todo.text}"`);
        });
        
        this.app.addEventListener('todoToggled', (event) => {
            const status = event.todo.completed ? 'completed' : 'active';
            console.log(`↔ Todo toggled: "${event.todo.text}" → ${status}`);
        });
        
        this.app.addEventListener('todoUpdated', (event) => {
            console.log(`✏ Todo updated: "${event.todo.text}"`);
        });
        
        // App events
        this.app.addEventListener('todosChanged', (event) => {
            const stats = this.app.getStats();
            console.log(`📊 Stats: ${stats.total} total, ${stats.active} active, ${stats.completed} completed`);
        });
        
        this.app.addEventListener('filterChanged', (event) => {
            console.log(`🔍 Filter changed to: ${event.filter}`);
        });
        
        this.app.addEventListener('sortChanged', (event) => {
            console.log(`📋 Sort changed to: ${event.sortBy}`);
        });
        
        this.app.addEventListener('completedCleared', (event) => {
            console.log(`🗑 Cleared ${event.clearedTodos.length} completed todos`);
        });
    }
    
    simulateUserActions() {
        console.log("\n=== Simulating User Actions ===");
        
        // Add todos
        console.log("\n1. Adding todos...");
        this.app.addTodo("Learn JavaScript", "high");
        this.app.addTodo("Build a project", "medium");
        this.app.addTodo("Write documentation", "low");
        this.app.addTodo("Deploy to production", "high");
        this.app.addTodo("Review code", "medium");
        
        // Toggle some todos
        console.log("\n2. Completing some todos...");
        this.app.toggleTodo(1); // Complete "Learn JavaScript"
        this.app.toggleTodo(3); // Complete "Write documentation"
        
        // Update a todo
        console.log("\n3. Updating a todo...");
        this.app.updateTodo(2, { text: "Build a React project", priority: "high" });
        
        // Change filter
        console.log("\n4. Filtering todos...");
        this.app.setFilter('active');
        console.log("Active todos:", this.app.getFilteredTodos().map(t => t.text));
        
        this.app.setFilter('completed');
        console.log("Completed todos:", this.app.getFilteredTodos().map(t => t.text));
        
        this.app.setFilter('all');
        
        // Change sorting
        console.log("\n5. Sorting todos...");
        this.app.setSortBy('priority');
        console.log("Todos sorted by priority:", this.app.getFilteredTodos().map(t => `${t.text} (${t.priority})`));
        
        this.app.setSortBy('text');
        console.log("Todos sorted by text:", this.app.getFilteredTodos().map(t => t.text));
        
        this.app.setSortBy('created');
        
        // Clear completed
        console.log("\n6. Clearing completed todos...");
        this.app.clearCompleted();
        
        // Final state
        console.log("\n7. Final state:");
        this.app.getFilteredTodos().forEach(todo => {
            const status = todo.completed ? '✓' : '○';
            console.log(`${status} [${todo.priority}] ${todo.text}`);
        });
    }
}

// Test the todo application
console.log("Testing todo application...");

const todoApp = new TodoApp();
const todoUI = new TodoUI(todoApp);

// Run simulation
todoUI.simulateUserActions();

// Advanced features
console.log("\n=== Advanced Features ===");

// Bulk operations
console.log("\nBulk operations:");
const bulkTodos = [
    "Review pull requests",
    "Update dependencies",
    "Fix bugs",
    "Write tests",
    "Optimize performance"
];

bulkTodos.forEach((text, index) => {
    const priority = index % 3 === 0 ? 'high' : index % 3 === 1 ? 'medium' : 'low';
    todoApp.addTodo(text, priority);
});

console.log(`Added ${bulkTodos.length} todos in bulk`);

// Search functionality
class TodoSearch {
    constructor(app) {
        this.app = app;
        this.searchTerm = '';
    }
    
    search(term) {
        this.searchTerm = term.toLowerCase();
        const results = this.app.todos.filter(todo => 
            todo.text.toLowerCase().includes(this.searchTerm)
        );
        
        console.log(`Search results for "${term}":`, results.map(t => t.text));
        return results;
    }
    
    clearSearch() {
        this.searchTerm = '';
        console.log("Search cleared");
    }
}

// Test search
const search = new TodoSearch(todoApp);
search.search("test");
search.search("bug");
search.clearSearch();

// Export functionality
class TodoExporter {
    constructor(app) {
        this.app = app;
    }
    
    exportToJSON() {
        const data = {
            todos: this.app.todos,
            stats: this.app.getStats(),
            exportDate: new Date().toISOString()
        };
        
        console.log("Exported todos to JSON:");
        console.log(JSON.stringify(data, null, 2));
        return data;
    }
    
    exportToCSV() {
        const csv = [
            'ID,Text,Completed,Priority,Created,Updated',
            ...this.app.todos.map(todo => 
                `${todo.id},"${todo.text}",${todo.completed},${todo.priority},"${todo.createdAt}","${todo.updatedAt}"`
            )
        ].join('\n');
        
        console.log("Exported todos to CSV:");
        console.log(csv);
        return csv;
    }
}

// Test export
const exporter = new TodoExporter(todoApp);
exporter.exportToJSON();
exporter.exportToCSV();

console.log("\n=== Interactive Todo Application Summary ===");
console.log("✓ Todo item management with events");
console.log("✓ Event-driven architecture for UI updates");
console.log("✓ Filtering and sorting capabilities");
console.log("✓ Bulk operations and search functionality");
console.log("✓ Export functionality (JSON and CSV)");
console.log("✓ Real-time statistics and updates");
console.log("✓ Comprehensive event handling system");
