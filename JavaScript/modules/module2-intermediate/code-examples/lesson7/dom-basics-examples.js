// Lesson 7: DOM Manipulation Basics Examples
// Note: These examples are designed to run in a browser environment
// For Node.js testing, we'll simulate DOM behavior

console.log("=== DOM Manipulation Basics Examples ===");
console.log("Note: These examples simulate DOM behavior for Node.js");
console.log("In a real browser, you would use document.querySelector(), etc.");

// Simulate DOM elements for Node.js environment
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
    }
    
    setAttribute(name, value) {
        this[name] = value;
    }
    
    getAttribute(name) {
        return this[name];
    }
    
    addEventListener(event, handler) {
        console.log(`Event listener added for ${event} on ${this.tagName}`);
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
    
    cloneNode(deep = false) {
        const clone = new MockElement(this.tagName, this.id, this.className);
        clone.innerText = this.innerText;
        clone.innerHTML = this.innerHTML;
        if (deep) {
            this.children.forEach(child => {
                clone.appendChild(child.cloneNode(true));
            });
        }
        return clone;
    }
}

// Mock document object
const mockDocument = {
    querySelector: (selector) => {
        console.log(`querySelector('${selector}') called`);
        // Simulate finding elements
        if (selector === 'h1') return new MockElement('h1');
        if (selector === '#myButton') return new MockElement('button', 'myButton');
        if (selector === '.myClass') return new MockElement('div', null, 'myClass');
        return null;
    },
    
    querySelectorAll: (selector) => {
        console.log(`querySelectorAll('${selector}') called`);
        // Simulate finding multiple elements
        if (selector === 'p') return [new MockElement('p'), new MockElement('p')];
        if (selector === 'button') return [new MockElement('button'), new MockElement('button')];
        return [];
    },
    
    createElement: (tagName) => {
        console.log(`createElement('${tagName}') called`);
        return new MockElement(tagName);
    },
    
    getElementById: (id) => {
        console.log(`getElementById('${id}') called`);
        return new MockElement('div', id);
    }
};

// Example 1: Selecting Elements
console.log("\n=== Example 1: Selecting Elements ===");

// Simulate selecting elements
let heading = mockDocument.querySelector('h1');
let button = mockDocument.querySelector('#myButton');
let paragraph = mockDocument.querySelector('.myClass');

console.log("Selected elements:");
console.log("Heading:", heading ? heading.tagName : 'null');
console.log("Button:", button ? button.tagName + ' (id: ' + button.id + ')' : 'null');
console.log("Paragraph:", paragraph ? paragraph.tagName + ' (class: ' + paragraph.className + ')' : 'null');

// Select multiple elements
let allParagraphs = mockDocument.querySelectorAll('p');
let allButtons = mockDocument.querySelectorAll('button');

console.log("Multiple elements:");
console.log("All paragraphs:", allParagraphs.length);
console.log("All buttons:", allButtons.length);

// Example 2: Changing Content
console.log("\n=== Example 2: Changing Content ===");

let contentElement = new MockElement('div');
contentElement.innerText = "Original text";
contentElement.innerHTML = "<strong>Original HTML</strong>";

console.log("Original content:");
console.log("innerText:", contentElement.innerText);
console.log("innerHTML:", contentElement.innerHTML);

// Change content
contentElement.innerText = "Updated text content";
contentElement.innerHTML = "<em>Updated HTML content</em>";

console.log("Updated content:");
console.log("innerText:", contentElement.innerText);
console.log("innerHTML:", contentElement.innerHTML);

// Example 3: Modifying Styles
console.log("\n=== Example 3: Modifying Styles ===");

let styledElement = new MockElement('div');
styledElement.style.color = 'blue';
styledElement.style.backgroundColor = 'yellow';
styledElement.style.fontSize = '16px';
styledElement.style.padding = '10px';

console.log("Element styles:");
console.log("Color:", styledElement.style.color);
console.log("Background:", styledElement.style.backgroundColor);
console.log("Font size:", styledElement.style.fontSize);
console.log("Padding:", styledElement.style.padding);

// Example 4: Adding and Removing Classes
console.log("\n=== Example 4: Adding and Removing Classes ===");

let classElement = new MockElement('div', null, 'initial-class');
console.log("Initial className:", classElement.className);

// Add classes
classElement.className += ' new-class active';
console.log("After adding classes:", classElement.className);

// Remove classes (simulate)
classElement.className = classElement.className.replace('initial-class', '').trim();
console.log("After removing 'initial-class':", classElement.className);

// Example 5: Creating and Appending Elements
console.log("\n=== Example 5: Creating and Appending Elements ===");

let container = new MockElement('div', 'container');
let newElement = mockDocument.createElement('p');
newElement.innerText = "This is a new paragraph";

console.log("Before appending:");
console.log("Container children:", container.children.length);

container.appendChild(newElement);

console.log("After appending:");
console.log("Container children:", container.children.length);
console.log("New element parent:", newElement.parentNode ? newElement.parentNode.tagName : 'null');

// Example 6: Event Handling
console.log("\n=== Example 6: Event Handling ===");

let clickableElement = new MockElement('button', 'clickButton');
clickableElement.innerText = "Click me";

// Add event listener
clickableElement.addEventListener('click', function() {
    console.log("Button clicked!");
});

// Simulate click event
console.log("Simulating click event...");
// In a real browser: clickableElement.click();

// Example 7: Element Manipulation
console.log("\n=== Example 7: Element Manipulation ===");

let listContainer = new MockElement('ul', 'myList');

// Create list items
let items = ['Item 1', 'Item 2', 'Item 3'];
items.forEach((itemText, index) => {
    let li = mockDocument.createElement('li');
    li.innerText = itemText;
    li.setAttribute('data-index', index);
    listContainer.appendChild(li);
});

console.log("List container:");
console.log("Tag:", listContainer.tagName);
console.log("ID:", listContainer.id);
console.log("Children count:", listContainer.children.length);

listContainer.children.forEach((child, index) => {
    console.log(`Child ${index}: ${child.innerText} (data-index: ${child.getAttribute('data-index')})`);
});

// Example 8: Cloning Elements
console.log("\n=== Example 8: Cloning Elements ===");

let originalElement = new MockElement('div', 'original');
originalElement.innerText = "Original content";
originalElement.className = "original-class";

let clonedElement = originalElement.cloneNode(true);

console.log("Original element:");
console.log("ID:", originalElement.id);
console.log("Text:", originalElement.innerText);
console.log("Class:", originalElement.className);

console.log("Cloned element:");
console.log("ID:", clonedElement.id);
console.log("Text:", clonedElement.innerText);
console.log("Class:", clonedElement.className);

console.log("\n=== DOM Manipulation Summary ===");
console.log("✓ Element selection with querySelector and querySelectorAll");
console.log("✓ Content modification with innerText and innerHTML");
console.log("✓ Dynamic style changes");
console.log("✓ Class manipulation");
console.log("✓ Element creation and appending");
console.log("✓ Event handling");
console.log("✓ Element cloning and manipulation");
