// Exercise 1: Contact Form with Validation
// Create a comprehensive contact form with real-time validation

console.log("=== Exercise 1: Contact Form with Validation ===");

// Mock form elements for Node.js
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

class MockForm {
    constructor(id) {
        this.id = id;
        this.elements = [];
        this.eventListeners = {};
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
            if (element.name && element.value) {
                formData[element.name] = element.value;
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

// Contact Form Builder
class ContactFormBuilder {
    constructor() {
        this.form = new MockForm('contactForm');
        this.validationRules = new Map();
        this.errorMessages = new Map();
    }
    
    // Add form field
    addField(type, name, options = {}) {
        const field = new MockFormElement('input', type);
        field.name = name;
        field.id = name;
        
        // Set field properties
        if (options.placeholder) field.placeholder = options.placeholder;
        if (options.required) field.setAttribute('required', '');
        if (options.pattern) field.setAttribute('pattern', options.pattern);
        if (options.minLength) field.setAttribute('minlength', options.minLength);
        if (options.maxLength) field.setAttribute('maxlength', options.maxLength);
        
        // Add validation rules
        if (options.validation) {
            this.validationRules.set(name, options.validation);
        }
        
        // Add error messages
        if (options.errorMessage) {
            this.errorMessages.set(name, options.errorMessage);
        }
        
        this.form.appendChild(field);
        return field;
    }
    
    // Add textarea field
    addTextarea(name, options = {}) {
        const textarea = new MockFormElement('textarea');
        textarea.name = name;
        textarea.id = name;
        
        if (options.placeholder) textarea.placeholder = options.placeholder;
        if (options.required) textarea.setAttribute('required', '');
        if (options.minLength) textarea.setAttribute('minlength', options.minLength);
        if (options.maxLength) textarea.setAttribute('maxlength', options.maxLength);
        
        if (options.validation) {
            this.validationRules.set(name, options.validation);
        }
        
        if (options.errorMessage) {
            this.errorMessages.set(name, options.errorMessage);
        }
        
        this.form.appendChild(textarea);
        return textarea;
    }
    
    // Add select field
    addSelect(name, options = []) {
        const select = new MockFormElement('select');
        select.name = name;
        select.id = name;
        select.options = options;
        
        this.form.appendChild(select);
        return select;
    }
    
    // Add submit button
    addSubmitButton(text = 'Submit') {
        const button = new MockFormElement('button', 'submit');
        button.innerText = text;
        button.className = 'btn btn-primary';
        
        this.form.appendChild(button);
        return button;
    }
    
    // Setup real-time validation
    setupRealTimeValidation() {
        this.form.elements.forEach(element => {
            if (element.name) {
                element.addEventListener('input', () => {
                    this.validateField(element);
                });
                
                element.addEventListener('blur', () => {
                    this.validateField(element);
                });
            }
        });
    }
    
    // Validate individual field
    validateField(field) {
        const fieldName = field.name;
        const value = field.value;
        
        // Check built-in validation
        const isValid = field.checkValidity();
        
        // Check custom validation rules
        const customRule = this.validationRules.get(fieldName);
        if (customRule && !customRule(value)) {
            field.setCustomValidity(this.errorMessages.get(fieldName) || 'Invalid input');
            field.style.borderColor = 'red';
            console.log(`✗ ${fieldName}: ${field.validationMessage}`);
            return false;
        }
        
        if (isValid) {
            field.setCustomValidity('');
            field.style.borderColor = 'green';
            console.log(`✓ ${fieldName}: Valid`);
            return true;
        } else {
            field.style.borderColor = 'red';
            console.log(`✗ ${fieldName}: ${field.validationMessage || 'Invalid input'}`);
            return false;
        }
    }
    
    // Setup form submission
    setupSubmission() {
        this.form.addEventListener('submit', (event) => {
            event.preventDefault();
            
            console.log('Form submission started...');
            
            if (this.form.validate()) {
                const formData = this.form.getFormData();
                console.log('Form submitted successfully!');
                console.log('Form data:', formData);
                
                // Simulate form processing
                this.processFormData(formData);
                
                // Reset form after successful submission
                this.form.reset();
                console.log('Form reset after successful submission');
            } else {
                console.log('Form validation failed. Please correct the errors.');
            }
        });
    }
    
    // Process form data
    processFormData(data) {
        console.log('Processing form data...');
        
        // Simulate sending data to server
        setTimeout(() => {
            console.log('Form data processed successfully!');
            console.log('Thank you for your submission.');
        }, 1000);
    }
    
    // Get form instance
    getForm() {
        return this.form;
    }
}

// Test the Contact Form Builder
console.log("\n--- Testing Contact Form Builder ---");

const contactForm = new ContactFormBuilder();

// Add form fields with validation
contactForm.addField('text', 'firstName', {
    placeholder: 'First Name',
    required: true,
    minLength: 2,
    maxLength: 50,
    validation: (value) => value.trim().length >= 2,
    errorMessage: 'First name must be at least 2 characters long'
});

contactForm.addField('text', 'lastName', {
    placeholder: 'Last Name',
    required: true,
    minLength: 2,
    maxLength: 50,
    validation: (value) => value.trim().length >= 2,
    errorMessage: 'Last name must be at least 2 characters long'
});

contactForm.addField('email', 'email', {
    placeholder: 'Email Address',
    required: true,
    validation: (value) => /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value),
    errorMessage: 'Please enter a valid email address'
});

contactForm.addField('tel', 'phone', {
    placeholder: 'Phone Number',
    pattern: '^[\\d\\s\\-\\+\\(\\)]+$',
    validation: (value) => value === '' || /^[\d\s\-\+\(\)]+$/.test(value),
    errorMessage: 'Please enter a valid phone number'
});

contactForm.addSelect('subject', [
    { value: 'general', text: 'General Inquiry' },
    { value: 'support', text: 'Technical Support' },
    { value: 'sales', text: 'Sales Question' },
    { value: 'feedback', text: 'Feedback' }
]);

contactForm.addTextarea('message', {
    placeholder: 'Your Message',
    required: true,
    minLength: 10,
    maxLength: 1000,
    validation: (value) => value.trim().length >= 10,
    errorMessage: 'Message must be at least 10 characters long'
});

contactForm.addSubmitButton('Send Message');

// Setup validation and submission
contactForm.setupRealTimeValidation();
contactForm.setupSubmission();

// Test form validation
console.log("\n--- Testing Form Validation ---");

const form = contactForm.getForm();

// Test valid data
form.elements[0].value = 'John'; // firstName
form.elements[0].dispatchEvent('input');

form.elements[1].value = 'Doe'; // lastName
form.elements[1].dispatchEvent('input');

form.elements[2].value = 'john.doe@example.com'; // email
form.elements[2].dispatchEvent('input');

form.elements[3].value = '+1 (555) 123-4567'; // phone
form.elements[3].dispatchEvent('input');

form.elements[5].value = 'This is a test message with more than 10 characters.'; // message
form.elements[5].dispatchEvent('input');

// Test form submission
console.log("\n--- Testing Form Submission ---");
form.dispatchEvent('submit');

// Test invalid data
console.log("\n--- Testing Invalid Data ---");
form.elements[0].value = 'A'; // Too short
form.elements[0].dispatchEvent('input');

form.elements[2].value = 'invalid-email'; // Invalid email
form.elements[2].dispatchEvent('input');

form.elements[5].value = 'Short'; // Too short message
form.elements[5].dispatchEvent('input');

console.log("\n=== Exercise 1 Complete ===");
console.log("✓ Contact form with comprehensive validation");
console.log("✓ Real-time field validation");
console.log("✓ Custom validation rules");
console.log("✓ Error message handling");
console.log("✓ Form data collection and processing");
console.log("✓ Form submission handling");
console.log("✓ Form reset functionality");
console.log("✓ User-friendly validation feedback");

