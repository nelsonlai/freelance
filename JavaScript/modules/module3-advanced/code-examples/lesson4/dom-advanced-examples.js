// Lesson 4: Advanced DOM Manipulation Examples
// Note: These examples simulate DOM behavior for Node.js
// In a real browser, you would use actual DOM methods

console.log("=== Advanced DOM Manipulation Examples ===");
console.log("Note: These examples simulate DOM behavior for Node.js");
console.log("In a real browser, you would use actual DOM methods");

// Enhanced mock element with advanced capabilities
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
    
    removeAttribute(name) {
        delete this.attributes[name];
        if (name.startsWith('data-')) {
            delete this.dataset[name.substring(5)];
        }
    }
    
    hasAttribute(name) {
        return name in this.attributes;
    }
    
    addEventListener(event, handler) {
        if (!this.eventListeners[event]) {
            this.eventListeners[event] = [];
        }
        this.eventListeners[event].push(handler);
    }
    
    removeEventListener(event, handler) {
        if (this.eventListeners[event]) {
            const index = this.eventListeners[event].indexOf(handler);
            if (index > -1) {
                this.eventListeners[event].splice(index, 1);
            }
        }
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
    
    replaceChild(newChild, oldChild) {
        const index = this.children.indexOf(oldChild);
        if (index > -1) {
            this.children[index] = newChild;
            newChild.parentNode = this;
            oldChild.parentNode = null;
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
    
    querySelector(selector) {
        // Simple selector matching
        if (selector.startsWith('#')) {
            return this.children.find(child => child.id === selector.substring(1));
        }
        if (selector.startsWith('.')) {
            return this.children.find(child => child.hasClass(selector.substring(1)));
        }
        return this.children.find(child => child.tagName === selector);
    }
    
    querySelectorAll(selector) {
        // Simple selector matching
        if (selector.startsWith('#')) {
            return this.children.filter(child => child.id === selector.substring(1));
        }
        if (selector.startsWith('.')) {
            return this.children.filter(child => child.hasClass(selector.substring(1)));
        }
        return this.children.filter(child => child.tagName === selector);
    }
}

// Mock document with advanced features
const mockDocument = {
    createElement: (tagName) => new AdvancedMockElement(tagName),
    createDocumentFragment: () => new DocumentFragment(),
    getElementById: (id) => new AdvancedMockElement('div', id),
    querySelector: (selector) => new AdvancedMockElement('div'),
    querySelectorAll: (selector) => [new AdvancedMockElement('div'), new AdvancedMockElement('div')]
};

// Document Fragment class
class DocumentFragment {
    constructor() {
        this.children = [];
    }
    
    appendChild(child) {
        this.children.push(child);
    }
    
    removeChild(child) {
        const index = this.children.indexOf(child);
        if (index > -1) {
            this.children.splice(index, 1);
        }
    }
    
    get length() {
        return this.children.length;
    }
}

// Example 1: Dynamic Element Creation
console.log("\n=== Example 1: Dynamic Element Creation ===");

function createDynamicElement(tagName, options = {}) {
    const element = mockDocument.createElement(tagName);
    
    if (options.id) element.id = options.id;
    if (options.className) element.className = options.className;
    if (options.innerText) element.innerText = options.innerText;
    if (options.innerHTML) element.innerHTML = options.innerHTML;
    if (options.attributes) {
        Object.keys(options.attributes).forEach(key => {
            element.setAttribute(key, options.attributes[key]);
        });
    }
    if (options.style) {
        Object.assign(element.style, options.style);
    }
    
    return element;
}

// Create various elements
const button = createDynamicElement('button', {
    id: 'my-button',
    className: 'btn btn-primary',
    innerText: 'Click me',
    attributes: { 'data-action': 'submit' },
    style: { backgroundColor: 'blue', color: 'white' }
});

const input = createDynamicElement('input', {
    id: 'my-input',
    className: 'form-control',
    attributes: { type: 'text', placeholder: 'Enter text' }
});

const div = createDynamicElement('div', {
    id: 'my-div',
    className: 'container',
    innerText: 'Dynamic content'
});

console.log('Created button:', button);
console.log('Created input:', input);
console.log('Created div:', div);

// Example 2: Document Fragments for Performance
console.log("\n=== Example 2: Document Fragments ===");

function createListWithFragment(itemCount) {
    const fragment = mockDocument.createDocumentFragment();
    
    for (let i = 0; i < itemCount; i++) {
        const li = createDynamicElement('li', {
            className: 'list-item',
            innerText: `Item ${i + 1}`,
            attributes: { 'data-index': i }
        });
        fragment.appendChild(li);
    }
    
    console.log(`Created fragment with ${fragment.length} items`);
    return fragment;
}

const listFragment = createListWithFragment(5);
console.log('Fragment children:', listFragment.children.length);

// Example 3: Advanced Element Manipulation
console.log("\n=== Example 3: Advanced Element Manipulation ===");

function manipulateElement(element) {
    // Add multiple classes
    element.addClass('active');
    element.addClass('highlighted');
    console.log('Added classes:', element.className);
    
    // Toggle class
    element.toggleClass('active');
    console.log('After toggle:', element.className);
    
    // Set multiple attributes
    element.setAttribute('data-id', '123');
    element.setAttribute('data-type', 'button');
    element.setAttribute('aria-label', 'Submit button');
    
    // Set dataset properties
    element.dataset.userId = '456';
    element.dataset.action = 'submit';
    
    console.log('Attributes:', element.attributes);
    console.log('Dataset:', element.dataset);
    
    // Style manipulation
    element.style.padding = '10px';
    element.style.margin = '5px';
    element.style.borderRadius = '4px';
    
    console.log('Styles:', element.style);
    
    return element;
}

const manipulatedButton = manipulateElement(button);

// Example 4: Element Cloning and Replacement
console.log("\n=== Example 4: Element Cloning and Replacement ===");

function cloneAndReplaceElement(originalElement) {
    // Shallow clone
    const shallowClone = originalElement.cloneNode(false);
    console.log('Shallow clone:', shallowClone);
    
    // Deep clone
    const deepClone = originalElement.cloneNode(true);
    console.log('Deep clone:', deepClone);
    
    // Replace element
    const newElement = createDynamicElement('span', {
        innerText: 'Replaced element',
        className: 'replaced'
    });
    
    if (originalElement.parentNode) {
        originalElement.parentNode.replaceChild(newElement, originalElement);
        console.log('Element replaced');
    }
    
    return { shallowClone, deepClone, newElement };
}

const cloneResults = cloneAndReplaceElement(manipulatedButton);

// Example 5: Dynamic List Management
console.log("\n=== Example 5: Dynamic List Management ===");

class DynamicList {
    constructor(containerId) {
        this.container = createDynamicElement('ul', { id: containerId, className: 'dynamic-list' });
        this.items = [];
    }
    
    addItem(text, options = {}) {
        const item = createDynamicElement('li', {
            className: 'list-item',
            innerText: text,
            attributes: { 'data-id': Date.now() }
        });
        
        if (options.className) item.addClass(options.className);
        if (options.attributes) {
            Object.keys(options.attributes).forEach(key => {
                item.setAttribute(key, options.attributes[key]);
            });
        }
        
        this.container.appendChild(item);
        this.items.push(item);
        
        console.log(`Added item: ${text}`);
        return item;
    }
    
    removeItem(index) {
        if (index >= 0 && index < this.items.length) {
            const item = this.items[index];
            this.container.removeChild(item);
            this.items.splice(index, 1);
            console.log(`Removed item at index ${index}`);
            return true;
        }
        return false;
    }
    
    updateItem(index, newText) {
        if (index >= 0 && index < this.items.length) {
            this.items[index].innerText = newText;
            console.log(`Updated item at index ${index}: ${newText}`);
            return true;
        }
        return false;
    }
    
    clear() {
        this.items.forEach(item => this.container.removeChild(item));
        this.items = [];
        console.log('List cleared');
    }
    
    getItemCount() {
        return this.items.length;
    }
    
    render() {
        console.log(`List with ${this.items.length} items:`);
        this.items.forEach((item, index) => {
            console.log(`  ${index}: ${item.innerText}`);
        });
    }
}

const dynamicList = new DynamicList('my-list');
dynamicList.addItem('First item');
dynamicList.addItem('Second item', { className: 'highlighted' });
dynamicList.addItem('Third item', { attributes: { 'data-priority': 'high' } });
dynamicList.render();

dynamicList.updateItem(1, 'Updated second item');
dynamicList.removeItem(0);
dynamicList.render();

// Example 6: Template System
console.log("\n=== Example 6: Template System ===");

class TemplateRenderer {
    constructor() {
        this.templates = new Map();
    }
    
    registerTemplate(name, templateFunction) {
        this.templates.set(name, templateFunction);
        console.log(`Template '${name}' registered`);
    }
    
    render(templateName, data) {
        const template = this.templates.get(templateName);
        if (!template) {
            throw new Error(`Template '${templateName}' not found`);
        }
        
        return template(data);
    }
    
    renderList(templateName, dataArray) {
        const fragment = mockDocument.createDocumentFragment();
        
        dataArray.forEach(data => {
            const element = this.render(templateName, data);
            fragment.appendChild(element);
        });
        
        console.log(`Rendered ${dataArray.length} items with template '${templateName}'`);
        return fragment;
    }
}

const templateRenderer = new TemplateRenderer();

// Register templates
templateRenderer.registerTemplate('user-card', (user) => {
    return createDynamicElement('div', {
        className: 'user-card',
        innerHTML: `
            <h3>${user.name}</h3>
            <p>Email: ${user.email}</p>
            <p>Age: ${user.age}</p>
        `,
        attributes: { 'data-user-id': user.id }
    });
});

templateRenderer.registerTemplate('product-item', (product) => {
    return createDynamicElement('div', {
        className: 'product-item',
        innerHTML: `
            <h4>${product.name}</h4>
            <p>Price: $${product.price}</p>
            <p>Stock: ${product.stock}</p>
        `,
        attributes: { 'data-product-id': product.id }
    });
});

// Test template rendering
const users = [
    { id: 1, name: 'Alice', email: 'alice@example.com', age: 30 },
    { id: 2, name: 'Bob', email: 'bob@example.com', age: 25 }
];

const products = [
    { id: 1, name: 'Laptop', price: 999.99, stock: 10 },
    { id: 2, name: 'Phone', price: 699.99, stock: 25 }
];

const userCards = templateRenderer.renderList('user-card', users);
const productItems = templateRenderer.renderList('product-item', products);

console.log('User cards fragment:', userCards.length);
console.log('Product items fragment:', productItems.length);

// Example 7: Event Delegation
console.log("\n=== Example 7: Event Delegation ===");

class EventDelegator {
    constructor(container) {
        this.container = container;
        this.delegatedEvents = new Map();
    }
    
    delegate(eventType, selector, handler) {
        if (!this.delegatedEvents.has(eventType)) {
            this.delegatedEvents.set(eventType, []);
        }
        
        this.delegatedEvents.get(eventType).push({ selector, handler });
        
        // Add event listener to container
        this.container.addEventListener(eventType, (event) => {
            const target = event.target;
            
            // Check if target matches any delegated selectors
            for (const { selector: sel, handler: h } of this.delegatedEvents.get(eventType)) {
                if (this.matchesSelector(target, sel)) {
                    h(event);
                    break;
                }
            }
        });
        
        console.log(`Delegated ${eventType} event for selector '${selector}'`);
    }
    
    matchesSelector(element, selector) {
        if (selector.startsWith('.')) {
            return element.hasClass(selector.substring(1));
        }
        if (selector.startsWith('#')) {
            return element.id === selector.substring(1);
        }
        return element.tagName === selector;
    }
}

const container = createDynamicElement('div', { id: 'event-container' });
const delegator = new EventDelegator(container);

// Add some elements to container
const button1 = createDynamicElement('button', { className: 'btn', innerText: 'Button 1' });
const button2 = createDynamicElement('button', { className: 'btn', innerText: 'Button 2' });
const link = createDynamicElement('a', { innerText: 'Link', attributes: { href: '#' } });

container.appendChild(button1);
container.appendChild(button2);
container.appendChild(link);

// Delegate events
delegator.delegate('click', '.btn', (event) => {
    console.log(`Button clicked: ${event.target.innerText}`);
});

delegator.delegate('click', 'a', (event) => {
    console.log(`Link clicked: ${event.target.innerText}`);
});

// Test event delegation
button1.dispatchEvent('click');
button2.dispatchEvent('click');
link.dispatchEvent('click');

console.log("\n=== Advanced DOM Manipulation Summary ===");
console.log("✓ Dynamic element creation and configuration");
console.log("✓ Document fragments for performance optimization");
console.log("✓ Advanced element manipulation (classes, attributes, styles)");
console.log("✓ Element cloning and replacement");
console.log("✓ Dynamic list management with CRUD operations");
console.log("✓ Template system for reusable components");
console.log("✓ Event delegation for efficient event handling");
console.log("✓ Advanced DOM traversal and manipulation");
console.log("✓ Performance optimization techniques");
console.log("✓ Real-world DOM manipulation patterns");
