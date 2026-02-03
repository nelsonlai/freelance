// Lesson 8: Events Examples
// Note: These examples simulate event handling for Node.js
// In a real browser, you would use actual DOM events

console.log("=== Events Examples ===");
console.log("Note: These examples simulate event handling for Node.js");
console.log("In a real browser, you would use actual DOM events");

// Event system simulation
class EventEmitter {
    constructor() {
        this.events = {};
    }
    
    addEventListener(event, handler) {
        if (!this.events[event]) {
            this.events[event] = [];
        }
        this.events[event].push(handler);
        console.log(`Event listener added for '${event}'`);
    }
    
    removeEventListener(event, handler) {
        if (this.events[event]) {
            const index = this.events[event].indexOf(handler);
            if (index > -1) {
                this.events[event].splice(index, 1);
                console.log(`Event listener removed for '${event}'`);
            }
        }
    }
    
    dispatchEvent(event, data = {}) {
        console.log(`Event '${event}' dispatched`);
        if (this.events[event]) {
            this.events[event].forEach(handler => {
                handler(data);
            });
        }
    }
}

// Mock element with event capabilities
class MockElementWithEvents extends EventEmitter {
    constructor(tagName, id = null) {
        super();
        this.tagName = tagName.toLowerCase();
        this.id = id;
        this.innerText = '';
        this.style = {};
        this.disabled = false;
    }
    
    click() {
        if (!this.disabled) {
            this.dispatchEvent('click', { target: this });
        }
    }
    
    focus() {
        this.dispatchEvent('focus', { target: this });
    }
    
    blur() {
        this.dispatchEvent('blur', { target: this });
    }
    
    keydown(key) {
        this.dispatchEvent('keydown', { target: this, key: key });
    }
    
    change(value) {
        this.value = value;
        this.dispatchEvent('change', { target: this, value: value });
    }
}

// Example 1: Basic Event Handling
console.log("\n=== Example 1: Basic Event Handling ===");

let button = new MockElementWithEvents('button', 'myButton');
button.innerText = "Click me";

// Add click event listener
button.addEventListener('click', function(event) {
    console.log("Button clicked! Event data:", event);
});

// Simulate click
console.log("Simulating button click:");
button.click();

// Example 2: Multiple Event Listeners
console.log("\n=== Example 2: Multiple Event Listeners ===");

let multiButton = new MockElementWithEvents('button', 'multiButton');

// Add multiple listeners for the same event
multiButton.addEventListener('click', function(event) {
    console.log("First click handler");
});

multiButton.addEventListener('click', function(event) {
    console.log("Second click handler");
});

multiButton.addEventListener('click', function(event) {
    console.log("Third click handler");
});

console.log("Simulating click with multiple handlers:");
multiButton.click();

// Example 3: Event Object Properties
console.log("\n=== Example 3: Event Object Properties ===");

let eventButton = new MockElementWithEvents('button', 'eventButton');

eventButton.addEventListener('click', function(event) {
    console.log("Event properties:");
    console.log("- Target:", event.target.tagName, event.target.id);
    console.log("- Type:", event.type || 'click');
    console.log("- Timestamp:", new Date().toISOString());
});

console.log("Simulating click with event properties:");
eventButton.click();

// Example 4: Form Events
console.log("\n=== Example 4: Form Events ===");

let input = new MockElementWithEvents('input', 'myInput');
input.type = 'text';

// Input change event
input.addEventListener('change', function(event) {
    console.log("Input changed to:", event.value);
});

input.addEventListener('focus', function(event) {
    console.log("Input focused");
});

input.addEventListener('blur', function(event) {
    console.log("Input blurred");
});

console.log("Simulating form events:");
input.focus();
input.change("Hello World");
input.blur();

// Example 5: Keyboard Events
console.log("\n=== Example 5: Keyboard Events ===");

let textArea = new MockElementWithEvents('textarea', 'myTextArea');

textArea.addEventListener('keydown', function(event) {
    console.log("Key pressed:", event.key);
    
    if (event.key === 'Enter') {
        console.log("Enter key pressed - submitting form");
    } else if (event.key === 'Escape') {
        console.log("Escape key pressed - canceling");
    }
});

console.log("Simulating keyboard events:");
textArea.keydown('a');
textArea.keydown('Enter');
textArea.keydown('Escape');

// Example 6: Event Delegation
console.log("\n=== Example 6: Event Delegation ===");

let list = new MockElementWithEvents('ul', 'myList');

// Add event delegation
list.addEventListener('click', function(event) {
    if (event.target.tagName === 'li') {
        console.log("List item clicked:", event.target.innerText);
    }
});

// Create list items
let items = ['Item 1', 'Item 2', 'Item 3'];
items.forEach((itemText, index) => {
    let li = new MockElementWithEvents('li');
    li.innerText = itemText;
    li.id = `item-${index}`;
    list.children = list.children || [];
    list.children.push(li);
});

console.log("Simulating clicks on list items:");
list.children.forEach(item => {
    console.log(`Clicking ${item.innerText}:`);
    item.click();
});

// Example 7: Event Bubbling and Capturing
console.log("\n=== Example 7: Event Bubbling and Capturing ===");

let parent = new MockElementWithEvents('div', 'parent');
let child = new MockElementWithEvents('div', 'child');

// Add event listeners
parent.addEventListener('click', function(event) {
    console.log("Parent clicked (bubbling phase)");
});

child.addEventListener('click', function(event) {
    console.log("Child clicked (bubbling phase)");
});

// Simulate event bubbling
console.log("Simulating event bubbling:");
child.click();

// Example 8: Preventing Default Behavior
console.log("\n=== Example 8: Preventing Default Behavior ===");

let link = new MockElementWithEvents('a', 'myLink');
link.href = 'https://example.com';
link.innerText = 'Click me';

link.addEventListener('click', function(event) {
    console.log("Link clicked, preventing default behavior");
    // In a real browser: event.preventDefault();
    console.log("Default behavior prevented");
});

console.log("Simulating link click with preventDefault:");
link.click();

// Example 9: Event Removal
console.log("\n=== Example 9: Event Removal ===");

let removableButton = new MockElementWithEvents('button', 'removableButton');

// Define handler function
let clickHandler = function(event) {
    console.log("Button clicked!");
};

// Add event listener
removableButton.addEventListener('click', clickHandler);

console.log("Button with event listener:");
removableButton.click();

// Remove event listener
removableButton.removeEventListener('click', clickHandler);

console.log("Button after removing event listener:");
removableButton.click();

// Example 10: Custom Events
console.log("\n=== Example 10: Custom Events ===");

let customElement = new MockElementWithEvents('div', 'customElement');

// Add custom event listener
customElement.addEventListener('customEvent', function(event) {
    console.log("Custom event received:", event.data);
});

// Dispatch custom event
console.log("Dispatching custom event:");
customElement.dispatchEvent('customEvent', { data: 'Custom event data' });

// Example 11: Event Timing
console.log("\n=== Example 11: Event Timing ===");

let timingButton = new MockElementWithEvents('button', 'timingButton');

timingButton.addEventListener('click', function(event) {
    console.log("Immediate click handler");
});

timingButton.addEventListener('click', function(event) {
    setTimeout(() => {
        console.log("Delayed click handler (100ms)");
    }, 100);
});

timingButton.addEventListener('click', function(event) {
    setTimeout(() => {
        console.log("Delayed click handler (200ms)");
    }, 200);
});

console.log("Simulating click with timing:");
timingButton.click();

// Wait a bit to see delayed handlers
setTimeout(() => {
    console.log("Timing example completed");
}, 300);

console.log("\n=== Events Summary ===");
console.log("✓ Basic event handling with addEventListener");
console.log("✓ Multiple event listeners for same event");
console.log("✓ Event object properties and data");
console.log("✓ Form events (change, focus, blur)");
console.log("✓ Keyboard events");
console.log("✓ Event delegation");
console.log("✓ Event bubbling and capturing");
console.log("✓ Preventing default behavior");
console.log("✓ Event listener removal");
console.log("✓ Custom events");
console.log("✓ Event timing and asynchronous handlers");
