// Exercise 2: Interactive Element Builder
// Create a system for building interactive elements with advanced DOM manipulation

console.log("=== Exercise 2: Interactive Element Builder ===");

// Enhanced mock element for Node.js
class InteractiveMockElement {
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
        this.isVisible = true;
        this.isEnabled = true;
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
    
    toggleClass(className) {
        if (this.hasClass(className)) {
            this.removeClass(className);
        } else {
            this.addClass(className);
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
    
    show() {
        this.isVisible = true;
        this.style.display = 'block';
    }
    
    hide() {
        this.isVisible = false;
        this.style.display = 'none';
    }
    
    enable() {
        this.isEnabled = true;
        this.removeClass('disabled');
    }
    
    disable() {
        this.isEnabled = false;
        this.addClass('disabled');
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
        // For complex selectors like 'button, input, select, textarea, a[href]'
        if (selector.includes(',')) {
            const selectors = selector.split(',').map(s => s.trim());
            const results = [];
            selectors.forEach(sel => {
                results.push(...this.querySelectorAll(sel));
            });
            return results;
        }
        return this.children.filter(child => child.tagName === selector);
    }
    
    cloneNode(deep = false) {
        const clone = new InteractiveMockElement(this.tagName);
        clone.id = this.id;
        clone.className = this.className;
        clone.innerText = this.innerText;
        clone.innerHTML = this.innerHTML;
        clone.dataset = { ...this.dataset };
        clone.attributes = { ...this.attributes };
        clone.isVisible = this.isVisible;
        clone.isEnabled = this.isEnabled;
        
        if (deep) {
            this.children.forEach(child => {
                clone.appendChild(child.cloneNode(true));
            });
        }
        return clone;
    }
}

const mockDocument = {
    createElement: (tagName) => new InteractiveMockElement(tagName)
};

// Interactive Element Builder
class InteractiveElementBuilder {
    constructor() {
        this.elementTypes = new Map();
        this.interactions = new Map();
        this.animations = new Map();
    }
    
    // Register element type
    registerElementType(typeName, builderFunction) {
        this.elementTypes.set(typeName, builderFunction);
        console.log(`Registered element type: ${typeName}`);
    }
    
    // Register interaction pattern
    registerInteraction(name, interactionFunction) {
        this.interactions.set(name, interactionFunction);
        console.log(`Registered interaction: ${name}`);
    }
    
    // Register animation
    registerAnimation(name, animationFunction) {
        this.animations.set(name, animationFunction);
        console.log(`Registered animation: ${name}`);
    }
    
    // Build element with type
    buildElement(typeName, options = {}) {
        const builder = this.elementTypes.get(typeName);
        if (!builder) {
            throw new Error(`Element type '${typeName}' not found`);
        }
        
        const element = builder(options);
        console.log(`Built ${typeName} element`);
        return element;
    }
    
    // Apply interaction to element
    applyInteraction(element, interactionName, options = {}) {
        const interaction = this.interactions.get(interactionName);
        if (!interaction) {
            throw new Error(`Interaction '${interactionName}' not found`);
        }
        
        interaction(element, options);
        console.log(`Applied ${interactionName} interaction`);
    }
    
    // Apply animation to element
    applyAnimation(element, animationName, options = {}) {
        const animation = this.animations.get(animationName);
        if (!animation) {
            throw new Error(`Animation '${animationName}' not found`);
        }
        
        animation(element, options);
        console.log(`Applied ${animationName} animation`);
    }
    
    // Create complex interactive element
    createInteractiveElement(typeName, interactions = [], animations = [], options = {}) {
        const element = this.buildElement(typeName, options);
        
        // Apply interactions
        interactions.forEach(({ name, options: interactionOptions }) => {
            this.applyInteraction(element, name, interactionOptions);
        });
        
        // Apply animations
        animations.forEach(({ name, options: animationOptions }) => {
            this.applyAnimation(element, name, animationOptions);
        });
        
        console.log(`Created interactive ${typeName} with ${interactions.length} interactions and ${animations.length} animations`);
        return element;
    }
}

// Test the Interactive Element Builder
console.log("\n--- Testing Interactive Element Builder ---");

const builder = new InteractiveElementBuilder();

// Register element types
builder.registerElementType('button', (options) => {
    const button = mockDocument.createElement('button');
    button.className = options.className || 'btn';
    button.innerText = options.text || 'Button';
    button.setAttribute('type', options.type || 'button');
    
    if (options.disabled) button.disable();
    if (options.variant) button.addClass(`btn-${options.variant}`);
    
    return button;
});

builder.registerElementType('card', (options) => {
    const card = mockDocument.createElement('div');
    card.className = 'card';
    
    const header = mockDocument.createElement('div');
    header.className = 'card-header';
    header.innerHTML = `<h3>${options.title || 'Card Title'}</h3>`;
    
    const body = mockDocument.createElement('div');
    body.className = 'card-body';
    body.innerHTML = options.content || '<p>Card content</p>';
    
    const footer = mockDocument.createElement('div');
    footer.className = 'card-footer';
    footer.innerHTML = options.footer || '';
    
    card.appendChild(header);
    card.appendChild(body);
    card.appendChild(footer);
    
    return card;
});

builder.registerElementType('modal', (options) => {
    const modal = mockDocument.createElement('div');
    modal.className = 'modal';
    modal.setAttribute('role', 'dialog');
    modal.setAttribute('aria-modal', 'true');
    
    const overlay = mockDocument.createElement('div');
    overlay.className = 'modal-overlay';
    
    const content = mockDocument.createElement('div');
    content.className = 'modal-content';
    
    const header = mockDocument.createElement('div');
    header.className = 'modal-header';
    header.innerHTML = `
        <h2>${options.title || 'Modal Title'}</h2>
        <button class="modal-close" aria-label="Close">&times;</button>
    `;
    
    const body = mockDocument.createElement('div');
    body.className = 'modal-body';
    body.innerHTML = options.content || '<p>Modal content</p>';
    
    const footer = mockDocument.createElement('div');
    body.className = 'modal-footer';
    footer.innerHTML = options.footer || '<button class="btn btn-primary">OK</button>';
    
    content.appendChild(header);
    content.appendChild(body);
    content.appendChild(footer);
    modal.appendChild(overlay);
    modal.appendChild(content);
    
    return modal;
});

// Register interactions
builder.registerInteraction('click-toggle', (element, options) => {
    element.addEventListener('click', () => {
        element.toggleClass(options.className || 'active');
        console.log(`Toggled class ${options.className || 'active'} on ${element.tagName}`);
    });
});

builder.registerInteraction('hover-effect', (element, options) => {
    element.addEventListener('mouseenter', () => {
        element.addClass(options.hoverClass || 'hover');
        console.log(`Added hover effect to ${element.tagName}`);
    });
    
    element.addEventListener('mouseleave', () => {
        element.removeClass(options.hoverClass || 'hover');
        console.log(`Removed hover effect from ${element.tagName}`);
    });
});

builder.registerInteraction('focus-trap', (element, options) => {
    element.addEventListener('keydown', (event) => {
        if (event.key === 'Tab') {
            const focusableElements = element.querySelectorAll('button, input, select, textarea, a[href]');
            const firstElement = focusableElements[0];
            const lastElement = focusableElements[focusableElements.length - 1];
            
            if (event.shiftKey) {
                if (event.target === firstElement) {
                    lastElement.focus();
                    event.preventDefault();
                }
            } else {
                if (event.target === lastElement) {
                    firstElement.focus();
                    event.preventDefault();
                }
            }
        }
    });
});

// Register animations
builder.registerAnimation('fade-in', (element, options) => {
    element.style.opacity = '0';
    element.style.transition = `opacity ${options.duration || '0.3s'} ease-in-out`;
    
    setTimeout(() => {
        element.style.opacity = '1';
        console.log(`Fade-in animation applied to ${element.tagName}`);
    }, options.delay || 0);
});

builder.registerAnimation('slide-down', (element, options) => {
    element.style.maxHeight = '0';
    element.style.overflow = 'hidden';
    element.style.transition = `max-height ${options.duration || '0.3s'} ease-in-out`;
    
    setTimeout(() => {
        element.style.maxHeight = options.maxHeight || '200px';
        console.log(`Slide-down animation applied to ${element.tagName}`);
    }, options.delay || 0);
});

builder.registerAnimation('pulse', (element, options) => {
    element.style.animation = `pulse ${options.duration || '1s'} infinite`;
    console.log(`Pulse animation applied to ${element.tagName}`);
});

// Test building elements
console.log("\n--- Building Elements ---");

// Simple button
const simpleButton = builder.buildElement('button', {
    text: 'Click Me',
    variant: 'primary'
});

// Interactive button with effects
const interactiveButton = builder.createInteractiveElement('button', 
    [
        { name: 'click-toggle', options: { className: 'active' } },
        { name: 'hover-effect', options: { hoverClass: 'btn-hover' } }
    ],
    [
        { name: 'pulse', options: { duration: '2s' } }
    ],
    {
        text: 'Interactive Button',
        variant: 'success'
    }
);

// Card with interactions
const interactiveCard = builder.createInteractiveElement('card',
    [
        { name: 'hover-effect', options: { hoverClass: 'card-hover' } }
    ],
    [
        { name: 'fade-in', options: { duration: '0.5s' } }
    ],
    {
        title: 'Interactive Card',
        content: '<p>This card has hover effects and animations!</p>',
        footer: '<button class="btn btn-primary">Action</button>'
    }
);

// Modal with focus trap
const modal = builder.createInteractiveElement('modal',
    [
        { name: 'focus-trap', options: {} }
    ],
    [
        { name: 'fade-in', options: { duration: '0.3s' } }
    ],
    {
        title: 'Interactive Modal',
        content: '<p>This modal has focus trapping!</p>',
        footer: '<button class="btn btn-primary">OK</button><button class="btn btn-secondary">Cancel</button>'
    }
);

// Test interactions
console.log("\n--- Testing Interactions ---");

// Simulate button clicks
simpleButton.dispatchEvent('click');
interactiveButton.dispatchEvent('click');
interactiveButton.dispatchEvent('click'); // Toggle back

// Simulate hover effects
interactiveCard.dispatchEvent('mouseenter');
interactiveCard.dispatchEvent('mouseleave');

// Test modal interactions
modal.dispatchEvent('keydown', { key: 'Tab', shiftKey: false });

console.log("\n=== Exercise 2 Complete ===");
console.log("✓ Interactive element type registration");
console.log("✓ Interaction pattern system");
console.log("✓ Animation system integration");
console.log("✓ Complex element composition");
console.log("✓ Event handling and delegation");
console.log("✓ Accessibility features (focus trap)");
console.log("✓ Reusable interaction patterns");
console.log("✓ Animation and transition effects");
