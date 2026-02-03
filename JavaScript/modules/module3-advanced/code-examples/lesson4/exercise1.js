// Exercise 1: Dynamic Content Manager
// Create a system for managing dynamic content with advanced DOM manipulation

console.log("=== Exercise 1: Dynamic Content Manager ===");

// Mock DOM elements for Node.js
class MockElement {
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
    
    cloneNode(deep = false) {
        const clone = new MockElement(this.tagName);
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
        return clone;
    }
}

class DocumentFragment {
    constructor() {
        this.children = [];
    }
    
    appendChild(child) {
        this.children.push(child);
    }
    
    get length() {
        return this.children.length;
    }
}

const mockDocument = {
    createElement: (tagName) => new MockElement(tagName),
    createDocumentFragment: () => new DocumentFragment()
};

// Dynamic Content Manager
class DynamicContentManager {
    constructor(containerId) {
        this.container = mockDocument.createElement('div');
        this.container.id = containerId;
        this.container.className = 'content-manager';
        this.sections = new Map();
        this.templates = new Map();
    }
    
    // Create a new content section
    createSection(sectionId, title, content = '') {
        const section = mockDocument.createElement('section');
        section.id = sectionId;
        section.className = 'content-section';
        
        const header = mockDocument.createElement('header');
        header.className = 'section-header';
        header.innerHTML = `<h2>${title}</h2>`;
        
        const body = mockDocument.createElement('div');
        body.className = 'section-body';
        body.innerHTML = content;
        
        section.appendChild(header);
        section.appendChild(body);
        
        this.container.appendChild(section);
        this.sections.set(sectionId, section);
        
        console.log(`Created section: ${sectionId} - ${title}`);
        return section;
    }
    
    // Update section content
    updateSection(sectionId, newContent) {
        const section = this.sections.get(sectionId);
        if (section) {
            const body = section.querySelector('.section-body');
            if (body) {
                body.innerHTML = newContent;
                console.log(`Updated section: ${sectionId}`);
            }
        } else {
            console.log(`Section ${sectionId} not found`);
        }
    }
    
    // Remove a section
    removeSection(sectionId) {
        const section = this.sections.get(sectionId);
        if (section) {
            this.container.removeChild(section);
            this.sections.delete(sectionId);
            console.log(`Removed section: ${sectionId}`);
        } else {
            console.log(`Section ${sectionId} not found`);
        }
    }
    
    // Register a template
    registerTemplate(name, templateFunction) {
        this.templates.set(name, templateFunction);
        console.log(`Registered template: ${name}`);
    }
    
    // Render content using template
    renderWithTemplate(templateName, data, sectionId) {
        const template = this.templates.get(templateName);
        if (!template) {
            throw new Error(`Template '${templateName}' not found`);
        }
        
        const content = template(data);
        this.updateSection(sectionId, content);
        console.log(`Rendered ${templateName} template in section ${sectionId}`);
    }
    
    // Create multiple sections from data
    createSectionsFromData(dataArray, templateName) {
        const fragment = mockDocument.createDocumentFragment();
        
        dataArray.forEach((data, index) => {
            const sectionId = `${templateName}-${index}`;
            const section = this.createSection(sectionId, data.title || `Section ${index + 1}`);
            
            if (this.templates.has(templateName)) {
                const template = this.templates.get(templateName);
                const content = template(data);
                const body = section.querySelector('.section-body');
                if (body) {
                    body.innerHTML = content;
                }
            }
            
            fragment.appendChild(section);
        });
        
        console.log(`Created ${dataArray.length} sections from template ${templateName}`);
        return fragment;
    }
    
    // Get section count
    getSectionCount() {
        return this.sections.size;
    }
    
    // Clear all sections
    clearAll() {
        this.sections.forEach((section, sectionId) => {
            this.container.removeChild(section);
        });
        this.sections.clear();
        console.log('Cleared all sections');
    }
    
    // Display current state
    displayState() {
        console.log(`Content Manager State:`);
        console.log(`  Container ID: ${this.container.id}`);
        console.log(`  Sections: ${this.sections.size}`);
        console.log(`  Templates: ${this.templates.size}`);
        
        this.sections.forEach((section, sectionId) => {
            console.log(`    - ${sectionId}: ${section.querySelector('h2')?.innerText || 'No title'}`);
        });
    }
}

// Test the Dynamic Content Manager
console.log("\n--- Testing Dynamic Content Manager ---");

const contentManager = new DynamicContentManager('main-content');

// Register templates
contentManager.registerTemplate('article', (data) => {
    return `
        <div class="article">
            <h3>${data.title}</h3>
            <p class="author">By ${data.author}</p>
            <p class="content">${data.content}</p>
            <div class="meta">
                <span class="date">${data.date}</span>
                <span class="category">${data.category}</span>
            </div>
        </div>
    `;
});

contentManager.registerTemplate('product', (data) => {
    return `
        <div class="product">
            <h3>${data.name}</h3>
            <p class="price">$${data.price}</p>
            <p class="description">${data.description}</p>
            <div class="actions">
                <button class="btn-primary" data-product-id="${data.id}">Add to Cart</button>
                <button class="btn-secondary" data-product-id="${data.id}">View Details</button>
            </div>
        </div>
    `;
});

// Create individual sections
contentManager.createSection('intro', 'Introduction', '<p>Welcome to our dynamic content system!</p>');
contentManager.createSection('features', 'Features', '<p>This system supports dynamic content management.</p>');

// Create sections from data
const articles = [
    {
        title: 'Getting Started with JavaScript',
        author: 'John Doe',
        content: 'JavaScript is a powerful programming language...',
        date: '2024-01-15',
        category: 'Programming'
    },
    {
        title: 'Advanced DOM Manipulation',
        author: 'Jane Smith',
        content: 'Learn how to manipulate the DOM efficiently...',
        date: '2024-01-20',
        category: 'Web Development'
    }
];

const products = [
    {
        id: 1,
        name: 'JavaScript Course',
        price: 99.99,
        description: 'Complete JavaScript course for beginners'
    },
    {
        id: 2,
        name: 'DOM Mastery Guide',
        price: 49.99,
        description: 'Advanced DOM manipulation techniques'
    }
];

// Create sections from data
contentManager.createSectionsFromData(articles, 'article');
contentManager.createSectionsFromData(products, 'product');

// Update a section
contentManager.updateSection('intro', '<p>Welcome to our <strong>enhanced</strong> dynamic content system!</p>');

// Display current state
contentManager.displayState();

// Remove a section
contentManager.removeSection('features');

console.log(`\nFinal section count: ${contentManager.getSectionCount()}`);

console.log("\n=== Exercise 1 Complete ===");
console.log("✓ Dynamic content section management");
console.log("✓ Template-based content rendering");
console.log("✓ CRUD operations for content sections");
console.log("✓ Batch content creation from data");
console.log("✓ Content state management and tracking");
