// Exercise 3: Dynamic Content Management
// This exercise demonstrates advanced DOM manipulation and content management

console.log("=== Exercise 3: Dynamic Content Management ===");

// Enhanced mock element with more capabilities
class AdvancedMockElement {
    constructor(tagName, id = null, className = null) {
        this.tagName = tagName.toLowerCase();
        this.id = id;
        this.className = className || '';
        this.innerText = '';
        this.innerHTML = '';
        this.style = {};
        this.children = [];
        this.parentNode = null;
        this.attributes = {};
        this.dataset = {};
        this.eventListeners = {};
    }
    
    setAttribute(name, value) {
        this.attributes[name] = value;
        if (name.startsWith('data-')) {
            this.dataset[name.substring(5)] = value;
        }
    }
    
    getAttribute(name) {
        return this.attributes[name];
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
                handler({ target: this, ...data });
            });
        }
    }
    
    appendChild(child) {
        this.children.push(child);
        child.parentNode = this;
    }
    
    removeChild(child) {
        const index = this.children.indexOf(child);
        if (index > -1) {
            this.children.splice(index, 1);
            child.parentNode = null;
        }
    }
    
    insertBefore(newChild, referenceChild) {
        const index = this.children.indexOf(referenceChild);
        if (index > -1) {
            this.children.splice(index, 0, newChild);
            newChild.parentNode = this;
        } else {
            this.appendChild(newChild);
        }
    }
    
    cloneNode(deep = false) {
        const clone = new AdvancedMockElement(this.tagName, this.id, this.className);
        clone.innerText = this.innerText;
        clone.innerHTML = this.innerHTML;
        clone.dataset = { ...this.dataset };
        clone.attributes = { ...this.attributes };
        
        if (deep) {
            this.children.forEach(child => {
                clone.appendChild(child.cloneNode(true));
            });
        }
        return clone;
    }
    
    addClass(className) {
        if (!this.className.includes(className)) {
            this.className += (this.className ? ' ' : '') + className;
        }
    }
    
    removeClass(className) {
        this.className = this.className.replace(new RegExp(`\\b${className}\\b`, 'g'), '').trim();
    }
    
    toggleClass(className) {
        if (this.className.includes(className)) {
            this.removeClass(className);
        } else {
            this.addClass(className);
        }
    }
    
    hasClass(className) {
        return this.className.includes(className);
    }
}

// Content Manager class
class ContentManager {
    constructor(container) {
        this.container = container;
        this.items = [];
        this.templates = {};
    }
    
    addTemplate(name, templateFunction) {
        this.templates[name] = templateFunction;
    }
    
    createItem(data, templateName = 'default') {
        const template = this.templates[templateName];
        if (!template) {
            throw new Error(`Template '${templateName}' not found`);
        }
        
        const element = template(data);
        element.setAttribute('data-item-id', data.id);
        this.items.push({ data, element });
        return element;
    }
    
    addItem(data, templateName = 'default') {
        const element = this.createItem(data, templateName);
        this.container.appendChild(element);
        return element;
    }
    
    removeItem(id) {
        const itemIndex = this.items.findIndex(item => item.data.id === id);
        if (itemIndex > -1) {
            const item = this.items[itemIndex];
            this.container.removeChild(item.element);
            this.items.splice(itemIndex, 1);
            return true;
        }
        return false;
    }
    
    updateItem(id, newData) {
        const item = this.items.find(item => item.data.id === id);
        if (item) {
            // Update data
            Object.assign(item.data, newData);
            
            // Re-render element
            const newElement = this.createItem(item.data, 'default');
            this.container.insertBefore(newElement, item.element);
            this.container.removeChild(item.element);
            
            // Update reference
            item.element = newElement;
            return true;
        }
        return false;
    }
    
    clearAll() {
        this.items.forEach(item => {
            this.container.removeChild(item.element);
        });
        this.items = [];
    }
    
    filterItems(filterFunction) {
        this.items.forEach(item => {
            const shouldShow = filterFunction(item.data);
            if (shouldShow) {
                item.element.style.display = 'block';
            } else {
                item.element.style.display = 'none';
            }
        });
    }
    
    sortItems(sortFunction) {
        this.items.sort((a, b) => sortFunction(a.data, b.data));
        
        // Reorder DOM elements
        this.items.forEach(item => {
            this.container.appendChild(item.element);
        });
    }
}

// Create a task management system
console.log("Creating task management system...");

const container = new AdvancedMockElement('div', 'task-container');
container.className = 'task-container';

const contentManager = new ContentManager(container);

// Define task template
contentManager.addTemplate('default', (taskData) => {
    const taskElement = new AdvancedMockElement('div', `task-${taskData.id}`);
    taskElement.className = 'task-item';
    taskElement.setAttribute('data-priority', taskData.priority);
    taskElement.setAttribute('data-status', taskData.status);
    
    taskElement.innerHTML = `
        <div class="task-header">
            <h3 class="task-title">${taskData.title}</h3>
            <span class="task-priority priority-${taskData.priority}">${taskData.priority}</span>
        </div>
        <div class="task-content">
            <p class="task-description">${taskData.description}</p>
            <div class="task-meta">
                <span class="task-date">${taskData.dueDate}</span>
                <span class="task-status status-${taskData.status}">${taskData.status}</span>
            </div>
        </div>
        <div class="task-actions">
            <button class="btn btn-edit" data-action="edit">Edit</button>
            <button class="btn btn-delete" data-action="delete">Delete</button>
            <button class="btn btn-toggle" data-action="toggle">Toggle Status</button>
        </div>
    `;
    
    // Add event listeners
    taskElement.addEventListener('click', (event) => {
        const action = event.target.getAttribute('data-action');
        if (action) {
            console.log(`Task ${taskData.id} - Action: ${action}`);
            handleTaskAction(taskData.id, action);
        }
    });
    
    return taskElement;
});

// Task action handler
function handleTaskAction(taskId, action) {
    switch (action) {
        case 'edit':
            console.log(`Editing task ${taskId}`);
            break;
        case 'delete':
            console.log(`Deleting task ${taskId}`);
            contentManager.removeItem(taskId);
            break;
        case 'toggle':
            const task = contentManager.items.find(item => item.data.id === taskId);
            if (task) {
                const newStatus = task.data.status === 'completed' ? 'pending' : 'completed';
                contentManager.updateItem(taskId, { status: newStatus });
                console.log(`Task ${taskId} status changed to ${newStatus}`);
            }
            break;
    }
}

// Add some initial tasks
const initialTasks = [
    {
        id: 1,
        title: 'Learn JavaScript',
        description: 'Complete the JavaScript course',
        priority: 'high',
        status: 'pending',
        dueDate: '2024-01-15'
    },
    {
        id: 2,
        title: 'Build a project',
        description: 'Create a todo application',
        priority: 'medium',
        status: 'in-progress',
        dueDate: '2024-01-20'
    },
    {
        id: 3,
        title: 'Deploy to production',
        description: 'Deploy the application to production',
        priority: 'low',
        status: 'pending',
        dueDate: '2024-01-25'
    }
];

console.log("Adding initial tasks...");
initialTasks.forEach(task => {
    contentManager.addItem(task);
});

console.log(`Added ${contentManager.items.length} tasks`);

// Test task operations
console.log("\n=== Testing Task Operations ===");

// Test 1: Add new task
console.log("\nTest 1: Adding new task");
const newTask = {
    id: 4,
    title: 'Write documentation',
    description: 'Document the API endpoints',
    priority: 'medium',
    status: 'pending',
    dueDate: '2024-01-30'
};
contentManager.addItem(newTask);
console.log(`Total tasks: ${contentManager.items.length}`);

// Test 2: Update task
console.log("\nTest 2: Updating task");
contentManager.updateItem(1, { 
    title: 'Learn Advanced JavaScript',
    description: 'Complete the advanced JavaScript course',
    priority: 'high'
});
console.log("Task 1 updated");

// Test 3: Filter tasks
console.log("\nTest 3: Filtering tasks by priority");
console.log("Filtering high priority tasks...");
contentManager.filterItems(task => task.priority === 'high');
console.log("High priority tasks shown");

// Reset filter
contentManager.filterItems(() => true);
console.log("Filter reset - all tasks shown");

// Test 4: Sort tasks
console.log("\nTest 4: Sorting tasks by due date");
contentManager.sortItems((a, b) => new Date(a.dueDate) - new Date(b.dueDate));
console.log("Tasks sorted by due date");

// Test 5: Task interactions
console.log("\nTest 5: Simulating task interactions");
const taskElement = contentManager.items[0].element;
taskElement.dispatchEvent('click', { target: { getAttribute: () => 'toggle' } });

// Test 6: Dynamic content updates
console.log("\n=== Dynamic Content Updates ===");

// Create a live counter
const counterElement = new AdvancedMockElement('div', 'counter');
counterElement.className = 'counter';
counterElement.innerHTML = '<span class="count">0</span> tasks remaining';

let taskCount = contentManager.items.filter(item => item.data.status !== 'completed').length;
counterElement.innerHTML = `<span class="count">${taskCount}</span> tasks remaining`;

container.appendChild(counterElement);

// Update counter when tasks change
function updateCounter() {
    taskCount = contentManager.items.filter(item => item.data.status !== 'completed').length;
    counterElement.innerHTML = `<span class="count">${taskCount}</span> tasks remaining`;
    console.log(`Counter updated: ${taskCount} tasks remaining`);
}

// Test counter updates
console.log("Testing counter updates...");
updateCounter();

// Mark a task as completed
contentManager.updateItem(2, { status: 'completed' });
updateCounter();

// Test 7: Batch operations
console.log("\n=== Batch Operations ===");

// Batch delete completed tasks
function deleteCompletedTasks() {
    const completedTasks = contentManager.items.filter(item => item.data.status === 'completed');
    console.log(`Deleting ${completedTasks.length} completed tasks`);
    
    completedTasks.forEach(task => {
        contentManager.removeItem(task.data.id);
    });
    
    updateCounter();
}

// Test batch delete
deleteCompletedTasks();

// Test 8: Search functionality
console.log("\n=== Search Functionality ===");

function searchTasks(query) {
    console.log(`Searching for: "${query}"`);
    
    contentManager.filterItems(task => {
        const searchText = `${task.title} ${task.description}`.toLowerCase();
        return searchText.includes(query.toLowerCase());
    });
}

// Test search
searchTasks('JavaScript');
console.log("Search results filtered");

// Reset search
contentManager.filterItems(() => true);
console.log("Search reset");

console.log("\n=== Dynamic Content Management Summary ===");
console.log("✓ Advanced DOM element manipulation");
console.log("✓ Content management system with templates");
console.log("✓ Dynamic item creation, updating, and deletion");
console.log("✓ Event handling and user interactions");
console.log("✓ Filtering and sorting capabilities");
console.log("✓ Live content updates and counters");
console.log("✓ Batch operations and search functionality");
console.log("✓ Template-based content rendering");
