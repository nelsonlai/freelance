// Exercise 3: Advanced DOM Performance Optimizer
// Create a system for optimizing DOM operations and performance

console.log("=== Exercise 3: Advanced DOM Performance Optimizer ===");

// Performance-optimized mock element
class PerformanceMockElement {
    constructor(tagName) {
        this.tagName = tagName.toLowerCase();
        this.id = '';
        this.className = '';
        this.innerText = '';
        this.innerHTML = '';
        this.style = {};
        this.children = [];
        this.parentNode = null;
        this.attributes = {};
        this.dataset = {};
        this.eventListeners = {};
        this.isDirty = false; // For change tracking
        this.measurements = {
            creationTime: Date.now(),
            modificationCount: 0,
            renderTime: 0
        };
    }
    
    setAttribute(name, value) {
        this.attributes[name] = value;
        if (name.startsWith('data-')) {
            this.dataset[name.substring(5)] = value;
        }
        this.markDirty();
    }
    
    getAttribute(name) {
        return this.attributes[name];
    }
    
    addClass(className) {
        if (!this.className.includes(className)) {
            this.className += (this.className ? ' ' : '') + className;
            this.markDirty();
        }
    }
    
    removeClass(className) {
        const newClassName = this.className.replace(new RegExp(`\\b${className}\\b`, 'g'), '').trim();
        if (newClassName !== this.className) {
            this.className = newClassName;
            this.markDirty();
        }
    }
    
    hasClass(className) {
        return this.className.includes(className);
    }
    
    appendChild(child) {
        this.children.push(child);
        child.parentNode = this;
        this.markDirty();
    }
    
    removeChild(child) {
        const index = this.children.indexOf(child);
        if (index > -1) {
            this.children.splice(index, 1);
            child.parentNode = null;
            this.markDirty();
        }
    }
    
    markDirty() {
        this.isDirty = true;
        this.measurements.modificationCount++;
    }
    
    markClean() {
        this.isDirty = false;
    }
    
    cloneNode(deep = false) {
        const startTime = Date.now();
        const clone = new PerformanceMockElement(this.tagName);
        clone.id = this.id;
        clone.className = this.className;
        clone.innerText = this.innerText;
        clone.innerHTML = this.innerHTML;
        clone.dataset = { ...this.dataset };
        clone.attributes = { ...this.attributes };
        
        if (deep) {
            this.children.forEach(child => {
                clone.appendChild(child.cloneNode(true));
            });
        }
        
        clone.measurements.renderTime = Date.now() - startTime;
        return clone;
    }
}

class DocumentFragment {
    constructor() {
        this.children = [];
        this.isDirty = false;
    }
    
    appendChild(child) {
        this.children.push(child);
        this.isDirty = true;
    }
    
    get length() {
        return this.children.length;
    }
    
    markClean() {
        this.isDirty = false;
        this.children.forEach(child => child.markClean());
    }
}

const mockDocument = {
    createElement: (tagName) => new PerformanceMockElement(tagName),
    createDocumentFragment: () => new DocumentFragment()
};

// DOM Performance Optimizer
class DOMPerformanceOptimizer {
    constructor() {
        this.batchOperations = [];
        this.isBatching = false;
        this.performanceMetrics = {
            totalOperations: 0,
            batchOperations: 0,
            individualOperations: 0,
            averageOperationTime: 0,
            totalTime: 0
        };
        this.optimizationStrategies = new Map();
    }
    
    // Start batching operations
    startBatch() {
        this.isBatching = true;
        this.batchOperations = [];
        console.log('Started batch operations');
    }
    
    // End batching and execute all operations
    endBatch() {
        if (!this.isBatching) return;
        
        const startTime = Date.now();
        this.isBatching = false;
        
        // Execute all batched operations
        this.batchOperations.forEach(operation => {
            operation.execute();
        });
        
        const endTime = Date.now();
        const batchTime = endTime - startTime;
        
        this.performanceMetrics.batchOperations++;
        this.performanceMetrics.totalTime += batchTime;
        
        console.log(`Executed ${this.batchOperations.length} operations in batch (${batchTime}ms)`);
        this.batchOperations = [];
    }
    
    // Add operation to batch
    addToBatch(operation) {
        if (this.isBatching) {
            this.batchOperations.push(operation);
        } else {
            const startTime = Date.now();
            operation.execute();
            const endTime = Date.now();
            
            this.performanceMetrics.individualOperations++;
            this.performanceMetrics.totalTime += (endTime - startTime);
        }
    }
    
    // Register optimization strategy
    registerStrategy(name, strategyFunction) {
        this.optimizationStrategies.set(name, strategyFunction);
        console.log(`Registered optimization strategy: ${name}`);
    }
    
    // Apply optimization strategy
    applyStrategy(strategyName, elements, options = {}) {
        const strategy = this.optimizationStrategies.get(strategyName);
        if (!strategy) {
            throw new Error(`Strategy '${strategyName}' not found`);
        }
        
        const startTime = Date.now();
        const result = strategy(elements, options);
        const endTime = Date.now();
        
        console.log(`Applied strategy '${strategyName}' in ${endTime - startTime}ms`);
        return result;
    }
    
    // Create optimized element factory
    createOptimizedFactory(elementType, options = {}) {
        return (config) => {
            const operation = {
                execute: () => {
                    const element = mockDocument.createElement(elementType);
                    
                    // Apply configuration
                    if (config.id) element.id = config.id;
                    if (config.className) element.className = config.className;
                    if (config.innerText) element.innerText = config.innerText;
                    if (config.innerHTML) element.innerHTML = config.innerHTML;
                    if (config.attributes) {
                        Object.keys(config.attributes).forEach(key => {
                            element.setAttribute(key, config.attributes[key]);
                        });
                    }
                    
                    return element;
                }
            };
            
            this.addToBatch(operation);
            return operation;
        };
    }
    
    // Virtual DOM-like diffing
    diffElements(oldElement, newElement) {
        const changes = [];
        
        // Compare attributes
        const oldAttrs = oldElement.attributes;
        const newAttrs = newElement.attributes;
        
        // Find added/modified attributes
        Object.keys(newAttrs).forEach(key => {
            if (oldAttrs[key] !== newAttrs[key]) {
                changes.push({
                    type: 'attribute',
                    key,
                    oldValue: oldAttrs[key],
                    newValue: newAttrs[key]
                });
            }
        });
        
        // Find removed attributes
        Object.keys(oldAttrs).forEach(key => {
            if (!(key in newAttrs)) {
                changes.push({
                    type: 'removeAttribute',
                    key,
                    oldValue: oldAttrs[key]
                });
            }
        });
        
        // Compare children
        const oldChildren = oldElement.children;
        const newChildren = newElement.children;
        
        if (oldChildren.length !== newChildren.length) {
            changes.push({
                type: 'childrenCount',
                oldCount: oldChildren.length,
                newCount: newChildren.length
            });
        }
        
        return changes;
    }
    
    // Apply changes efficiently
    applyChanges(element, changes) {
        changes.forEach(change => {
            switch (change.type) {
                case 'attribute':
                    element.setAttribute(change.key, change.newValue);
                    break;
                case 'removeAttribute':
                    element.removeAttribute(change.key);
                    break;
                case 'childrenCount':
                    // Handle children changes
                    console.log(`Children count changed from ${change.oldCount} to ${change.newCount}`);
                    break;
            }
        });
    }
    
    // Get performance metrics
    getMetrics() {
        const totalOps = this.performanceMetrics.batchOperations + this.performanceMetrics.individualOperations;
        const avgTime = totalOps > 0 ? this.performanceMetrics.totalTime / totalOps : 0;
        
        return {
            ...this.performanceMetrics,
            averageOperationTime: avgTime,
            totalOperations: totalOps
        };
    }
    
    // Reset metrics
    resetMetrics() {
        this.performanceMetrics = {
            totalOperations: 0,
            batchOperations: 0,
            individualOperations: 0,
            averageOperationTime: 0,
            totalTime: 0
        };
        console.log('Performance metrics reset');
    }
}

// Test the DOM Performance Optimizer
console.log("\n--- Testing DOM Performance Optimizer ---");

const optimizer = new DOMPerformanceOptimizer();

// Register optimization strategies
optimizer.registerStrategy('batch-create', (elements, options) => {
    const fragment = mockDocument.createDocumentFragment();
    elements.forEach(element => {
        fragment.appendChild(element);
    });
    return fragment;
});

optimizer.registerStrategy('lazy-load', (elements, options) => {
    return elements.map(element => {
        element.style.display = 'none';
        element.dataset.lazy = 'true';
        return element;
    });
});

optimizer.registerStrategy('virtual-scroll', (elements, options) => {
    const visibleCount = options.visibleCount || 10;
    return elements.slice(0, visibleCount).map(element => {
        element.dataset.virtual = 'true';
        return element;
    });
});

// Create optimized factories
const buttonFactory = optimizer.createOptimizedFactory('button');
const divFactory = optimizer.createOptimizedFactory('div');
const listItemFactory = optimizer.createOptimizedFactory('li');

// Test batch operations
console.log("\n--- Testing Batch Operations ---");

optimizer.startBatch();

// Create multiple elements in batch
const buttons = [];
for (let i = 0; i < 5; i++) {
    const buttonOp = buttonFactory({
        id: `btn-${i}`,
        className: 'btn btn-primary',
        innerText: `Button ${i}`,
        attributes: { 'data-index': i }
    });
    buttons.push(buttonOp);
}

const divs = [];
for (let i = 0; i < 3; i++) {
    const divOp = divFactory({
        id: `div-${i}`,
        className: 'container',
        innerText: `Container ${i}`
    });
    divs.push(divOp);
}

optimizer.endBatch();

// Test individual operations
console.log("\n--- Testing Individual Operations ---");

const singleButton = buttonFactory({
    id: 'single-btn',
    className: 'btn btn-secondary',
    innerText: 'Single Button'
});

// Test optimization strategies
console.log("\n--- Testing Optimization Strategies ---");

const testElements = buttons.map(op => op.execute());
const batchedElements = optimizer.applyStrategy('batch-create', testElements);
console.log(`Batched ${testElements.length} elements`);

const lazyElements = optimizer.applyStrategy('lazy-load', testElements, {});
console.log(`Applied lazy loading to ${lazyElements.length} elements`);

const virtualElements = optimizer.applyStrategy('virtual-scroll', testElements, { visibleCount: 3 });
console.log(`Applied virtual scrolling to ${virtualElements.length} elements`);

// Test diffing
console.log("\n--- Testing Element Diffing ---");

const oldElement = mockDocument.createElement('div');
oldElement.id = 'test';
oldElement.className = 'old-class';
oldElement.setAttribute('data-value', 'old');

const newElement = mockDocument.createElement('div');
newElement.id = 'test';
newElement.className = 'new-class';
newElement.setAttribute('data-value', 'new');
newElement.setAttribute('data-new', 'added');

const changes = optimizer.diffElements(oldElement, newElement);
console.log('Detected changes:', changes);

optimizer.applyChanges(oldElement, changes);
console.log('Applied changes to element');

// Display performance metrics
console.log("\n--- Performance Metrics ---");
const metrics = optimizer.getMetrics();
console.log('Performance Metrics:', metrics);

console.log("\n=== Exercise 3 Complete ===");
console.log("✓ Batch operation optimization");
console.log("✓ Performance metrics tracking");
console.log("✓ Optimization strategy system");
console.log("✓ Virtual DOM-like diffing");
console.log("✓ Efficient change application");
console.log("✓ Lazy loading implementation");
console.log("✓ Virtual scrolling optimization");
console.log("✓ Factory pattern for element creation");
console.log("✓ Performance monitoring and analysis");
