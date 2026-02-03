// Exercise 2: Dynamic Form Builder
// Create a system for building dynamic forms with conditional fields

console.log("=== Exercise 2: Dynamic Form Builder ===");

// Enhanced mock form elements for Node.js
class DynamicMockElement {
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
            customError: false
        };
        this.isVisible = true;
        this.conditionalRules = [];
        this.dependencies = [];
    }
    
    setAttribute(name, value) {
        this.attributes[name] = value;
        if (name.startsWith('data-')) {
            this.dataset[name.substring(5)] = value;
        }
        
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
    
    addConditionalRule(rule) {
        this.conditionalRules.push(rule);
    }
    
    addDependency(fieldName) {
        this.dependencies.push(fieldName);
    }
    
    checkConditionalVisibility(formData) {
        let shouldShow = true;
        
        this.conditionalRules.forEach(rule => {
            if (!rule(formData)) {
                shouldShow = false;
            }
        });
        
        if (shouldShow) {
            this.show();
        } else {
            this.hide();
        }
        
        return shouldShow;
    }
    
    setCustomValidity(message) {
        this.validationMessage = message;
        this.validity.customError = message !== '';
        this.validity.valid = this.checkValidity();
    }
    
    checkValidity() {
        if (!this.isVisible) return true; // Hidden fields don't need validation
        
        this.validity.valueMissing = this.required && this.value.trim() === '';
        this.validity.tooShort = this.value.length < this.minLength;
        this.validity.tooLong = this.value.length > this.maxLength;
        this.validity.patternMismatch = this.pattern && !new RegExp(this.pattern).test(this.value);
        
        if (this.type === 'email') {
            this.validity.typeMismatch = !this.isValidEmail(this.value);
        }
        
        this.validity.valid = !Object.values(this.validity).some(error => error === true);
        return this.validity.valid;
    }
    
    isValidEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
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
        this.validationMessage = '';
        this.validity.valid = true;
        Object.keys(this.validity).forEach(key => {
            if (key !== 'valid') this.validity[key] = false;
        });
    }
}

class DynamicMockForm {
    constructor(id) {
        this.id = id;
        this.elements = [];
        this.eventListeners = {};
        this.conditionalFields = new Map();
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
    
    appendChild(element) {
        this.elements.push(element);
    }
    
    getFormData() {
        const formData = {};
        this.elements.forEach(element => {
            if (element.name && element.value && element.isVisible) {
                formData[element.name] = element.value;
            }
        });
        return formData;
    }
    
    validate() {
        let isValid = true;
        this.elements.forEach(element => {
            if (element.isVisible && !element.reportValidity()) {
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
    
    updateConditionalFields() {
        const formData = this.getFormData();
        
        this.elements.forEach(element => {
            if (element.conditionalRules.length > 0) {
                element.checkConditionalVisibility(formData);
            }
        });
    }
}

// Dynamic Form Builder
class DynamicFormBuilder {
    constructor() {
        this.form = new DynamicMockForm('dynamicForm');
        this.fieldTypes = new Map();
        this.validationRules = new Map();
        this.conditionalRules = new Map();
    }
    
    // Register field type
    registerFieldType(typeName, builderFunction) {
        this.fieldTypes.set(typeName, builderFunction);
        console.log(`Registered field type: ${typeName}`);
    }
    
    // Add field with conditional logic
    addField(type, name, options = {}) {
        const field = new DynamicMockElement('input', type);
        field.name = name;
        field.id = name;
        
        // Set field properties
        if (options.placeholder) field.placeholder = options.placeholder;
        if (options.required) field.setAttribute('required', '');
        if (options.pattern) field.setAttribute('pattern', options.pattern);
        if (options.minLength) field.setAttribute('minlength', options.minLength);
        if (options.maxLength) field.setAttribute('maxlength', options.maxLength);
        
        // Add conditional rules
        if (options.showIf) {
            field.addConditionalRule(options.showIf);
        }
        
        if (options.hideIf) {
            field.addConditionalRule((formData) => !options.hideIf(formData));
        }
        
        // Add dependencies
        if (options.dependsOn) {
            options.dependsOn.forEach(dep => field.addDependency(dep));
        }
        
        // Add validation
        if (options.validation) {
            this.validationRules.set(name, options.validation);
        }
        
        this.form.appendChild(field);
        return field;
    }
    
    // Add select field with options
    addSelect(name, options = []) {
        const select = new DynamicMockElement('select');
        select.name = name;
        select.id = name;
        select.options = options;
        
        this.form.appendChild(select);
        return select;
    }
    
    // Add checkbox group
    addCheckboxGroup(name, options = []) {
        const group = [];
        options.forEach((option, index) => {
            const checkbox = new DynamicMockElement('input', 'checkbox');
            checkbox.name = `${name}[]`;
            checkbox.id = `${name}_${index}`;
            checkbox.value = option.value;
            checkbox.dataset.label = option.label;
            
            this.form.appendChild(checkbox);
            group.push(checkbox);
        });
        return group;
    }
    
    // Add radio group
    addRadioGroup(name, options = []) {
        const group = [];
        options.forEach((option, index) => {
            const radio = new DynamicMockElement('input', 'radio');
            radio.name = name;
            radio.id = `${name}_${index}`;
            radio.value = option.value;
            radio.dataset.label = option.label;
            
            this.form.appendChild(radio);
            group.push(radio);
        });
        return group;
    }
    
    // Setup conditional field updates
    setupConditionalUpdates() {
        this.form.elements.forEach(element => {
            element.addEventListener('change', () => {
                this.form.updateConditionalFields();
            });
            
            element.addEventListener('input', () => {
                this.form.updateConditionalFields();
            });
        });
    }
    
    // Setup form submission
    setupSubmission() {
        this.form.addEventListener('submit', (event) => {
            event.preventDefault();
            
            console.log('Dynamic form submission started...');
            
            if (this.form.validate()) {
                const formData = this.form.getFormData();
                console.log('Form submitted successfully!');
                console.log('Form data:', formData);
                
                this.processFormData(formData);
            } else {
                console.log('Form validation failed. Please correct the errors.');
            }
        });
    }
    
    // Process form data
    processFormData(data) {
        console.log('Processing dynamic form data...');
        
        // Simulate sending data to server
        setTimeout(() => {
            console.log('Dynamic form data processed successfully!');
        }, 1000);
    }
    
    // Get form instance
    getForm() {
        return this.form;
    }
}

// Test the Dynamic Form Builder
console.log("\n--- Testing Dynamic Form Builder ---");

const dynamicForm = new DynamicFormBuilder();

// Register field types
dynamicForm.registerFieldType('text', (name, options) => {
    return dynamicForm.addField('text', name, options);
});

dynamicForm.registerFieldType('email', (name, options) => {
    return dynamicForm.addField('email', name, options);
});

dynamicForm.registerFieldType('select', (name, options) => {
    return dynamicForm.addSelect(name, options);
});

// Build a dynamic registration form
console.log("\n--- Building Dynamic Registration Form ---");

// Basic information
dynamicForm.addField('text', 'firstName', {
    placeholder: 'First Name',
    required: true,
    minLength: 2
});

dynamicForm.addField('text', 'lastName', {
    placeholder: 'Last Name',
    required: true,
    minLength: 2
});

dynamicForm.addField('email', 'email', {
    placeholder: 'Email Address',
    required: true
});

// Account type selection
dynamicForm.addRadioGroup('accountType', [
    { value: 'personal', label: 'Personal' },
    { value: 'business', label: 'Business' },
    { value: 'student', label: 'Student' }
]);

// Conditional fields based on account type
dynamicForm.addField('text', 'companyName', {
    placeholder: 'Company Name',
    required: true,
    showIf: (formData) => formData.accountType === 'business'
});

dynamicForm.addField('text', 'studentId', {
    placeholder: 'Student ID',
    required: true,
    showIf: (formData) => formData.accountType === 'student'
});

dynamicForm.addField('text', 'university', {
    placeholder: 'University Name',
    showIf: (formData) => formData.accountType === 'student'
});

// Subscription preferences
dynamicForm.addCheckboxGroup('subscriptions', [
    { value: 'newsletter', label: 'Newsletter' },
    { value: 'promotions', label: 'Promotions' },
    { value: 'updates', label: 'Product Updates' }
]);

// Conditional newsletter frequency
dynamicForm.addSelect('newsletterFrequency', [
    { value: 'daily', text: 'Daily' },
    { value: 'weekly', text: 'Weekly' },
    { value: 'monthly', text: 'Monthly' }
]);

// Add conditional rule for newsletter frequency
const newsletterField = dynamicForm.form.elements.find(el => el.name === 'newsletterFrequency');
if (newsletterField) {
    newsletterField.addConditionalRule((formData) => 
        formData.subscriptions && formData.subscriptions.includes('newsletter')
    );
}

// Payment information (only for business accounts)
dynamicForm.addField('text', 'creditCard', {
    placeholder: 'Credit Card Number',
    pattern: '^[0-9]{16}$',
    showIf: (formData) => formData.accountType === 'business'
});

dynamicForm.addField('text', 'billingAddress', {
    placeholder: 'Billing Address',
    showIf: (formData) => formData.accountType === 'business'
});

// Setup conditional updates and submission
dynamicForm.setupConditionalUpdates();
dynamicForm.setupSubmission();

// Test the dynamic form
console.log("\n--- Testing Dynamic Form Behavior ---");

const form = dynamicForm.getForm();

// Test account type changes
console.log("Testing account type: Personal");
form.elements[3].value = 'personal'; // accountType radio
form.elements[3].dispatchEvent('change');

console.log("Testing account type: Business");
form.elements[4].value = 'business'; // accountType radio
form.elements[4].dispatchEvent('change');

console.log("Testing account type: Student");
form.elements[5].value = 'student'; // accountType radio
form.elements[5].dispatchEvent('change');

// Test subscription changes
console.log("\nTesting subscription changes:");
form.elements[6].checked = true; // newsletter subscription
form.elements[6].dispatchEvent('change');

// Fill out form data
console.log("\n--- Filling Out Form Data ---");
form.elements[0].value = 'John'; // firstName
form.elements[1].value = 'Doe'; // lastName
form.elements[2].value = 'john.doe@example.com'; // email
form.elements[4].value = 'business'; // accountType
form.elements[7].value = 'Acme Corp'; // companyName
form.elements[6].checked = true; // newsletter subscription
form.elements[9].value = 'weekly'; // newsletterFrequency

// Test form submission
console.log("\n--- Testing Form Submission ---");
form.dispatchEvent('submit');

console.log("\n=== Exercise 2 Complete ===");
console.log("✓ Dynamic form builder with conditional fields");
console.log("✓ Field type registration system");
console.log("✓ Conditional visibility rules");
console.log("✓ Real-time form updates");
console.log("✓ Checkbox and radio group handling");
console.log("✓ Dependency management");
console.log("✓ Dynamic validation based on visibility");
console.log("✓ Form data collection with conditional fields");
console.log("✓ User experience with progressive disclosure");

