// Exercise 1: DOM Element Manipulation
// This exercise demonstrates basic DOM manipulation techniques

console.log("=== Exercise 1: DOM Element Manipulation ===");

// Mock DOM elements for Node.js environment
class MockElement {
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
    }
    
    setAttribute(name, value) {
        this.attributes[name] = value;
    }
    
    getAttribute(name) {
        return this.attributes[name];
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
    
    addClass(className) {
        if (!this.className.includes(className)) {
            this.className += (this.className ? ' ' : '') + className;
        }
    }
    
    removeClass(className) {
        this.className = this.className.replace(new RegExp(`\\b${className}\\b`, 'g'), '').trim();
    }
    
    hasClass(className) {
        return this.className.includes(className);
    }
}

// Mock document
const mockDocument = {
    createElement: (tagName) => new MockElement(tagName),
    getElementById: (id) => new MockElement('div', id),
    querySelector: (selector) => {
        if (selector.startsWith('#')) {
            return new MockElement('div', selector.substring(1));
        }
        if (selector.startsWith('.')) {
            return new MockElement('div', null, selector.substring(1));
        }
        return new MockElement(selector);
    }
};

// Exercise: Create a dynamic list
console.log("Creating a dynamic list...");

// Create container
let container = mockDocument.createElement('div');
container.id = 'list-container';
container.className = 'container';

// Create heading
let heading = mockDocument.createElement('h2');
heading.innerText = 'My Dynamic List';
heading.setAttribute('data-list-title', 'dynamic');

// Create list
let list = mockDocument.createElement('ul');
list.id = 'my-list';
list.className = 'list';

// Create input and button
let input = mockDocument.createElement('input');
input.type = 'text';
input.placeholder = 'Enter item text';
input.id = 'item-input';

let addButton = mockDocument.createElement('button');
addButton.innerText = 'Add Item';
addButton.id = 'add-button';
addButton.className = 'btn btn-primary';

// Assemble the structure
container.appendChild(heading);
container.appendChild(input);
container.appendChild(addButton);
container.appendChild(list);

console.log("Container structure created:");
console.log("- Container ID:", container.id);
console.log("- Container class:", container.className);
console.log("- Children count:", container.children.length);

// Add some initial items
let initialItems = ['Learn JavaScript', 'Build a project', 'Deploy to production'];

initialItems.forEach((itemText, index) => {
    let li = mockDocument.createElement('li');
    li.innerText = itemText;
    li.setAttribute('data-index', index);
    li.className = 'list-item';
    
    // Add delete button
    let deleteBtn = mockDocument.createElement('button');
    deleteBtn.innerText = 'Delete';
    deleteBtn.className = 'btn btn-danger btn-sm';
    deleteBtn.setAttribute('data-action', 'delete');
    
    li.appendChild(deleteBtn);
    list.appendChild(li);
});

console.log("\nInitial list items:");
list.children.forEach((item, index) => {
    console.log(`Item ${index + 1}: ${item.innerText} (class: ${item.className})`);
});

// Simulate adding new items
function addListItem(text) {
    let li = mockDocument.createElement('li');
    li.innerText = text;
    li.className = 'list-item';
    li.setAttribute('data-index', list.children.length);
    
    // Add delete button
    let deleteBtn = mockDocument.createElement('button');
    deleteBtn.innerText = 'Delete';
    deleteBtn.className = 'btn btn-danger btn-sm';
    deleteBtn.setAttribute('data-action', 'delete');
    
    li.appendChild(deleteBtn);
    list.appendChild(li);
    
    console.log(`Added item: "${text}"`);
}

// Simulate removing items
function removeListItem(index) {
    if (index >= 0 && index < list.children.length) {
        let item = list.children[index];
        console.log(`Removing item: "${item.innerText}"`);
        list.removeChild(item);
        
        // Update data-index attributes
        list.children.forEach((item, i) => {
            item.setAttribute('data-index', i);
        });
    }
}

// Test adding items
console.log("\nTesting add functionality:");
addListItem('New item 1');
addListItem('New item 2');

console.log("\nUpdated list items:");
list.children.forEach((item, index) => {
    console.log(`Item ${index + 1}: ${item.innerText}`);
});

// Test removing items
console.log("\nTesting remove functionality:");
removeListItem(1); // Remove second item

console.log("\nAfter removal:");
list.children.forEach((item, index) => {
    console.log(`Item ${index + 1}: ${item.innerText}`);
});

// Test class manipulation
console.log("\nTesting class manipulation:");
let testElement = mockDocument.createElement('div');
testElement.className = 'initial-class';

console.log("Initial class:", testElement.className);
console.log("Has 'initial-class':", testElement.hasClass('initial-class'));

testElement.addClass('new-class');
console.log("After adding 'new-class':", testElement.className);

testElement.addClass('active');
console.log("After adding 'active':", testElement.className);

testElement.removeClass('initial-class');
console.log("After removing 'initial-class':", testElement.className);

console.log("Has 'new-class':", testElement.hasClass('new-class'));
console.log("Has 'initial-class':", testElement.hasClass('initial-class'));

// Test style manipulation
console.log("\nTesting style manipulation:");
let styledElement = mockDocument.createElement('div');
styledElement.style.color = 'blue';
styledElement.style.backgroundColor = 'yellow';
styledElement.style.padding = '10px';
styledElement.style.border = '1px solid black';

console.log("Element styles:");
console.log("- Color:", styledElement.style.color);
console.log("- Background:", styledElement.style.backgroundColor);
console.log("- Padding:", styledElement.style.padding);
console.log("- Border:", styledElement.style.border);

// Test attribute manipulation
console.log("\nTesting attribute manipulation:");
let attrElement = mockDocument.createElement('div');
attrElement.setAttribute('data-id', '123');
attrElement.setAttribute('data-type', 'container');
attrElement.setAttribute('title', 'Tooltip text');

console.log("Element attributes:");
console.log("- data-id:", attrElement.getAttribute('data-id'));
console.log("- data-type:", attrElement.getAttribute('data-type'));
console.log("- title:", attrElement.getAttribute('title'));

console.log("\n=== DOM Element Manipulation Summary ===");
console.log("✓ Element creation and structure building");
console.log("✓ Adding and removing child elements");
console.log("✓ Class manipulation (add, remove, has)");
console.log("✓ Style property modification");
console.log("✓ Attribute setting and getting");
console.log("✓ Dynamic list management");
console.log("✓ Element traversal and manipulation");
