// Lesson 5: Forms and Validation Examples
// Note: These examples simulate form behavior for Node.js
// In a real browser, you would use actual DOM form elements

console.log("=== Forms and Validation Examples ===");
console.log("Note: These examples simulate form behavior for Node.js");
console.log("In a real browser, you would use actual DOM form elements");

// Mock form element for Node.js
class MockFormElement {
    constructor(tagName, type = null) {
        this.tagName = tagName.toLowerCase();
        this.type = type;
        this.value = '';
        this.name = '';
        this.id = '';
        this.className = '';
        this.required = false;
        this.disabled = false;
        this.readOnly = false;
        this.placeholder = '';
        this.pattern = '';
        this.minLength = 0;
        this.maxLength = Infinity;
        this.min = '';
        this.max = '';
        this.step = '';
        this.checked = false;
        this.selected = false;
        this.options = [];
        this.selectedIndex = -1;
        this.style = {};
        this.dataset = {};
        this.attributes = {};
        this.eventListeners = {};
        this.validationMessage = '';
        this.validity = {
            valid: true,
            valueMissing: false,
            typeMismatch: false,
            patternMismatch: false,
            tooLong: false,
            tooShort: false,
            rangeUnderflow: false,
            rangeOverflow: false,
            stepMismatch: false,
            badInput: false,
            customError: false
        };
    }
    
    setAttribute(name, value) {
        this.attributes[name] = value;
        if (name.startsWith('data-')) {
            this.dataset[name.substring(5)] = value;
        }
        
        // Handle form-specific attributes
        switch (name) {
            case 'required':
                this.required = true;
                break;
            case 'disabled':
                this.disabled = true;
                break;
            case 'readonly':
                this.readOnly = true;
                break;
            case 'placeholder':
                this.placeholder = value;
                break;
            case 'pattern':
                this.pattern = value;
                break;
            case 'minlength':
                this.minLength = parseInt(value);
                break;
            case 'maxlength':
                this.maxLength = parseInt(value);
                break;
            case 'min':
                this.min = value;
                break;
            case 'max':
                this.max = value;
                break;
            case 'step':
                this.step = value;
                break;
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
                const eventObj = {
                    target: this,
                    preventDefault: () => console.log('preventDefault called'),
                    stopPropagation: () => console.log('stopPropagation called'),
                    ...data
                };
                handler(eventObj);
            });
        }
    }
    
    setCustomValidity(message) {
        this.validationMessage = message;
        this.validity.customError = message !== '';
        this.validity.valid = this.checkValidity();
    }
    
    checkValidity() {
        this.validity.valueMissing = this.required && this.value.trim() === '';
        this.validity.tooShort = this.value.length < this.minLength;
        this.validity.tooLong = this.value.length > this.maxLength;
        this.validity.patternMismatch = this.pattern && !new RegExp(this.pattern).test(this.value);
        
        // Type-specific validation
        if (this.type === 'email') {
            this.validity.typeMismatch = !this.isValidEmail(this.value);
        }
        if (this.type === 'url') {
            this.validity.typeMismatch = !this.isValidUrl(this.value);
        }
        if (this.type === 'number') {
            const num = parseFloat(this.value);
            this.validity.badInput = isNaN(num);
            if (!isNaN(num)) {
                this.validity.rangeUnderflow = this.min && num < parseFloat(this.min);
                this.validity.rangeOverflow = this.max && num > parseFloat(this.max);
            }
        }
        
        this.validity.valid = !Object.values(this.validity).some(error => error === true);
        return this.validity.valid;
    }
    
    isValidEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
    }
    
    isValidUrl(url) {
        try {
            new URL(url);
            return true;
        } catch {
            return false;
        }
    }
    
    reportValidity() {
        if (!this.checkValidity()) {
            console.log(`Validation failed for ${this.name || this.id}: ${this.validationMessage || 'Invalid input'}`);
            return false;
        }
        return true;
    }
    
    reset() {
        this.value = '';
        this.checked = false;
        this.selected = false;
        this.selectedIndex = -1;
        this.validationMessage = '';
        this.validity.valid = true;
        Object.keys(this.validity).forEach(key => {
            if (key !== 'valid') this.validity[key] = false;
        });
    }
}

// Mock form for Node.js
class MockForm {
    constructor(id) {
        this.id = id;
        this.elements = [];
        this.eventListeners = {};
        this.method = 'GET';
        this.action = '';
        this.enctype = 'application/x-www-form-urlencoded';
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
                const eventObj = {
                    target: this,
                    preventDefault: () => console.log('preventDefault called'),
                    stopPropagation: () => console.log('stopPropagation called'),
                    ...data
                };
                handler(eventObj);
            });
        }
    }
    
    appendChild(element) {
        this.elements.push(element);
    }
    
    getFormData() {
        const formData = {};
        this.elements.forEach(element => {
            if (element.name && element.value) {
                if (element.type === 'checkbox' || element.type === 'radio') {
                    if (element.checked) {
                        formData[element.name] = element.value;
                    }
                } else if (element.tagName === 'select') {
                    if (element.selectedIndex >= 0) {
                        formData[element.name] = element.options[element.selectedIndex].value;
                    }
                } else {
                    formData[element.name] = element.value;
                }
            }
        });
        return formData;
    }
    
    validate() {
        let isValid = true;
        this.elements.forEach(element => {
            if (!element.reportValidity()) {
                isValid = false;
            }
        });
        return isValid;
    }
    
    reset() {
        this.elements.forEach(element => {
            element.reset();
        });
    }
}

// Example 1: Basic Form Handling
console.log("\n=== Example 1: Basic Form Handling ===");

function createBasicForm() {
    const form = new MockForm('contactForm');
    
    // Create form elements
    const nameInput = new MockFormElement('input', 'text');
    nameInput.name = 'name';
    nameInput.id = 'name';
    nameInput.placeholder = 'Enter your name';
    nameInput.setAttribute('required', '');
    
    const emailInput = new MockFormElement('input', 'email');
    emailInput.name = 'email';
    emailInput.id = 'email';
    emailInput.placeholder = 'Enter your email';
    emailInput.setAttribute('required', '');
    
    const messageTextarea = new MockFormElement('textarea');
    messageTextarea.name = 'message';
    messageTextarea.id = 'message';
    messageTextarea.placeholder = 'Enter your message';
    messageTextarea.setAttribute('required', '');
    
    const submitButton = new MockFormElement('button', 'submit');
    submitButton.innerText = 'Submit';
    
    // Add elements to form
    form.appendChild(nameInput);
    form.appendChild(emailInput);
    form.appendChild(messageTextarea);
    form.appendChild(submitButton);
    
    // Add form submission handler
    form.addEventListener('submit', function(event) {
        event.preventDefault();
        
        console.log('Form submitted!');
        const formData = form.getFormData();
        console.log('Form data:', formData);
        
        if (form.validate()) {
            console.log('Form is valid, processing...');
            // Process form data
        } else {
            console.log('Form validation failed');
        }
    });
    
    return form;
}

const basicForm = createBasicForm();

// Simulate form submission
console.log('Simulating form submission...');
basicForm.dispatchEvent('submit');

// Example 2: Real-time Validation
console.log("\n=== Example 2: Real-time Validation ===");

function createValidatedForm() {
    const form = new MockForm('validatedForm');
    
    // Email input with real-time validation
    const emailInput = new MockFormElement('input', 'email');
    emailInput.name = 'email';
    emailInput.id = 'email';
    emailInput.placeholder = 'Enter your email';
    emailInput.setAttribute('required', '');
    
    // Real-time validation
    emailInput.addEventListener('input', function(event) {
        const email = event.target.value;
        const isValid = emailInput.isValidEmail(email);
        
        if (email === '') {
            event.target.style.borderColor = '';
            event.target.setCustomValidity('');
        } else if (isValid) {
            event.target.style.borderColor = 'green';
            event.target.setCustomValidity('');
            console.log(`✓ Valid email: ${email}`);
        } else {
            event.target.style.borderColor = 'red';
            event.target.setCustomValidity('Please enter a valid email address');
            console.log(`✗ Invalid email: ${email}`);
        }
    });
    
    // Password input with strength validation
    const passwordInput = new MockFormElement('input', 'password');
    passwordInput.name = 'password';
    passwordInput.id = 'password';
    passwordInput.placeholder = 'Enter password';
    passwordInput.setAttribute('required', '');
    passwordInput.setAttribute('minlength', '8');
    
    passwordInput.addEventListener('input', function(event) {
        const password = event.target.value;
        const strength = getPasswordStrength(password);
        
        event.target.style.borderColor = strength.color;
        console.log(`Password strength: ${strength.level} (${strength.score}/4)`);
    });
    
    // Phone input with pattern validation
    const phoneInput = new MockFormElement('input', 'tel');
    phoneInput.name = 'phone';
    phoneInput.id = 'phone';
    phoneInput.placeholder = 'Enter phone number';
    phoneInput.setAttribute('pattern', '^[\\d\\s\\-\\+\\(\\)]+$');
    
    phoneInput.addEventListener('input', function(event) {
        const phone = event.target.value;
        const isValid = /^[\d\s\-\+\(\)]+$/.test(phone);
        
        if (phone === '') {
            event.target.style.borderColor = '';
        } else if (isValid) {
            event.target.style.borderColor = 'green';
            console.log(`✓ Valid phone: ${phone}`);
        } else {
            event.target.style.borderColor = 'red';
            console.log(`✗ Invalid phone: ${phone}`);
        }
    });
    
    form.appendChild(emailInput);
    form.appendChild(passwordInput);
    form.appendChild(phoneInput);
    
    return form;
}

function getPasswordStrength(password) {
    let score = 0;
    
    if (password.length >= 8) score++;
    if (/[a-z]/.test(password)) score++;
    if (/[A-Z]/.test(password)) score++;
    if (/\d/.test(password)) score++;
    if (/[^a-zA-Z\d]/.test(password)) score++;
    
    const levels = ['Very Weak', 'Weak', 'Fair', 'Good', 'Strong'];
    const colors = ['red', 'orange', 'yellow', 'lightgreen', 'green'];
    
    return {
        level: levels[Math.min(score, 4)],
        score: Math.min(score, 4),
        color: colors[Math.min(score, 4)]
    };
}

const validatedForm = createValidatedForm();

// Test real-time validation
console.log('Testing real-time validation...');
validatedForm.elements[0].value = 'test@example.com';
validatedForm.elements[0].dispatchEvent('input');

validatedForm.elements[1].value = 'MyPassword123!';
validatedForm.elements[1].dispatchEvent('input');

validatedForm.elements[2].value = '+1 (555) 123-4567';
validatedForm.elements[2].dispatchEvent('input');

// Example 3: Advanced Form Validation
console.log("\n=== Example 3: Advanced Form Validation ===");

class AdvancedFormValidator {
    constructor() {
        this.rules = new Map();
        this.customValidators = new Map();
    }
    
    addRule(fieldName, rule) {
        if (!this.rules.has(fieldName)) {
            this.rules.set(fieldName, []);
        }
        this.rules.get(fieldName).push(rule);
    }
    
    addCustomValidator(name, validatorFunction) {
        this.customValidators.set(name, validatorFunction);
    }
    
    validateField(field) {
        const fieldRules = this.rules.get(field.name) || [];
        const errors = [];
        
        fieldRules.forEach(rule => {
            if (!rule.validate(field.value)) {
                errors.push(rule.message);
            }
        });
        
        return errors;
    }
    
    validateForm(form) {
        const errors = {};
        let isValid = true;
        
        form.elements.forEach(element => {
            if (element.name) {
                const fieldErrors = this.validateField(element);
                if (fieldErrors.length > 0) {
                    errors[element.name] = fieldErrors;
                    isValid = false;
                }
            }
        });
        
        return { isValid, errors };
    }
}

// Validation rules
class ValidationRule {
    constructor(validateFunction, message) {
        this.validate = validateFunction;
        this.message = message;
    }
}

// Create validation rules
const requiredRule = new ValidationRule(
    value => value.trim() !== '',
    'This field is required'
);

const emailRule = new ValidationRule(
    value => /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value),
    'Please enter a valid email address'
);

const minLengthRule = (min) => new ValidationRule(
    value => value.length >= min,
    `Must be at least ${min} characters long`
);

const maxLengthRule = (max) => new ValidationRule(
    value => value.length <= max,
    `Must be no more than ${max} characters long`
);

const patternRule = (pattern, message) => new ValidationRule(
    value => new RegExp(pattern).test(value),
    message
);

// Test advanced validation
const validator = new AdvancedFormValidator();

// Add rules for different fields
validator.addRule('name', requiredRule);
validator.addRule('name', minLengthRule(2));
validator.addRule('name', maxLengthRule(50));

validator.addRule('email', requiredRule);
validator.addRule('email', emailRule);

validator.addRule('password', requiredRule);
validator.addRule('password', minLengthRule(8));
validator.addRule('password', patternRule('^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)', 'Password must contain at least one lowercase letter, one uppercase letter, and one number'));

// Create test form
const testForm = new MockForm('testForm');

const nameField = new MockFormElement('input', 'text');
nameField.name = 'name';
nameField.value = 'A'; // Too short

const emailField = new MockFormElement('input', 'email');
emailField.name = 'email';
emailField.value = 'invalid-email'; // Invalid email

const passwordField = new MockFormElement('input', 'password');
passwordField.name = 'password';
passwordField.value = 'weak'; // Weak password

testForm.appendChild(nameField);
testForm.appendChild(emailField);
testForm.appendChild(passwordField);

// Validate form
const validationResult = validator.validateForm(testForm);
console.log('Validation result:', validationResult);

// Example 4: Form Data Collection and Processing
console.log("\n=== Example 4: Form Data Collection and Processing ===");

class FormDataProcessor {
    constructor() {
        this.processors = new Map();
    }
    
    addProcessor(fieldName, processorFunction) {
        this.processors.set(fieldName, processorFunction);
    }
    
    processFormData(formData) {
        const processedData = {};
        
        Object.keys(formData).forEach(key => {
            const processor = this.processors.get(key);
            if (processor) {
                processedData[key] = processor(formData[key]);
            } else {
                processedData[key] = formData[key];
            }
        });
        
        return processedData;
    }
}

// Create form data processor
const processor = new FormDataProcessor();

// Add processors
processor.addProcessor('name', value => value.trim().toLowerCase().replace(/\b\w/g, l => l.toUpperCase()));
processor.addProcessor('email', value => value.trim().toLowerCase());
processor.addProcessor('phone', value => value.replace(/\D/g, ''));
processor.addProcessor('age', value => parseInt(value));

// Test form data processing
const sampleFormData = {
    name: '  john doe  ',
    email: '  JOHN@EXAMPLE.COM  ',
    phone: '+1 (555) 123-4567',
    age: '25'
};

const processedData = processor.processFormData(sampleFormData);
console.log('Original data:', sampleFormData);
console.log('Processed data:', processedData);

// Example 5: Form State Management
console.log("\n=== Example 5: Form State Management ===");

class FormStateManager {
    constructor(form) {
        this.form = form;
        this.originalData = {};
        this.isDirty = false;
        this.isSubmitting = false;
        this.autoSaveInterval = null;
    }
    
    initialize() {
        // Store original form data
        this.originalData = this.form.getFormData();
        
        // Add change listeners
        this.form.elements.forEach(element => {
            element.addEventListener('input', () => {
                this.markDirty();
            });
        });
        
        // Auto-save functionality
        this.startAutoSave();
    }
    
    markDirty() {
        this.isDirty = true;
        console.log('Form marked as dirty');
    }
    
    markClean() {
        this.isDirty = false;
        this.originalData = this.form.getFormData();
        console.log('Form marked as clean');
    }
    
    startAutoSave() {
        this.autoSaveInterval = setInterval(() => {
            if (this.isDirty && !this.isSubmitting) {
                this.autoSave();
            }
        }, 30000); // Auto-save every 30 seconds
    }
    
    stopAutoSave() {
        if (this.autoSaveInterval) {
            clearInterval(this.autoSaveInterval);
            this.autoSaveInterval = null;
        }
    }
    
    autoSave() {
        console.log('Auto-saving form data...');
        const currentData = this.form.getFormData();
        // In a real application, you would save to localStorage or send to server
        console.log('Auto-saved:', currentData);
        this.markClean();
    }
    
    reset() {
        this.form.reset();
        this.markClean();
        console.log('Form reset to original state');
    }
    
    hasUnsavedChanges() {
        const currentData = this.form.getFormData();
        return JSON.stringify(currentData) !== JSON.stringify(this.originalData);
    }
}

// Test form state management
const stateForm = new MockForm('stateForm');
const nameField2 = new MockFormElement('input', 'text');
nameField2.name = 'name';
nameField2.value = 'John Doe';

const emailField2 = new MockFormElement('input', 'email');
emailField2.name = 'email';
emailField2.value = 'john@example.com';

stateForm.appendChild(nameField2);
stateForm.appendChild(emailField2);

const stateManager = new FormStateManager(stateForm);
stateManager.initialize();

// Simulate changes
nameField2.value = 'Jane Smith';
nameField2.dispatchEvent('input');

console.log('Has unsaved changes:', stateManager.hasUnsavedChanges());

console.log("\n=== Forms and Validation Summary ===");
console.log("✓ Basic form handling and submission");
console.log("✓ Real-time input validation");
console.log("✓ Advanced validation rules and custom validators");
console.log("✓ Form data collection and processing");
console.log("✓ Form state management and auto-save");
console.log("✓ Password strength validation");
console.log("✓ Pattern-based validation");
console.log("✓ Form reset and cleanup");
console.log("✓ Error handling and user feedback");
console.log("✓ Accessibility and user experience features");
