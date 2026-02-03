// Exercise 3: Advanced Form Validation System
// Create a comprehensive form validation system with custom rules and error handling

console.log("=== Exercise 3: Advanced Form Validation System ===");

// Advanced mock form elements for Node.js
class AdvancedMockElement {
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
        this.validationRules = [];
        this.errorMessages = [];
        this.validationHistory = [];
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
    
    addValidationRule(rule) {
        this.validationRules.push(rule);
    }
    
    setCustomValidity(message) {
        this.validationMessage = message;
        this.validity.customError = message !== '';
        this.validity.valid = this.checkValidity();
    }
    
    checkValidity() {
        // Reset validity
        Object.keys(this.validity).forEach(key => {
            if (key !== 'valid') this.validity[key] = false;
        });
        
        // Check built-in validation
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
        
        // Check custom validation rules
        this.validationRules.forEach(rule => {
            if (!rule.validate(this.value)) {
                this.validity.customError = true;
                this.validationMessage = rule.message;
            }
        });
        
        this.validity.valid = !Object.values(this.validity).some(error => error === true);
        
        // Record validation history
        this.validationHistory.push({
            timestamp: Date.now(),
            value: this.value,
            valid: this.validity.valid,
            errors: Object.keys(this.validity).filter(key => this.validity[key] === true)
        });
        
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
    
    getValidationSummary() {
        return {
            field: this.name || this.id,
            valid: this.validity.valid,
            errors: Object.keys(this.validity).filter(key => this.validity[key] === true),
            message: this.validationMessage,
            history: this.validationHistory.slice(-5) // Last 5 validations
        };
    }
    
    reset() {
        this.value = '';
        this.validationMessage = '';
        this.validity.valid = true;
        this.validationHistory = [];
        Object.keys(this.validity).forEach(key => {
            if (key !== 'valid') this.validity[key] = false;
        });
    }
}

class AdvancedMockForm {
    constructor(id) {
        this.id = id;
        this.elements = [];
        this.eventListeners = {};
        this.validationRules = new Map();
        this.crossFieldValidators = [];
        this.validationHistory = [];
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
    
    addCrossFieldValidator(validator) {
        this.crossFieldValidators.push(validator);
    }
    
    validate() {
        let isValid = true;
        const errors = {};
        
        // Validate individual fields
        this.elements.forEach(element => {
            if (!element.reportValidity()) {
                isValid = false;
                errors[element.name] = element.getValidationSummary();
            }
        });
        
        // Validate cross-field rules
        this.crossFieldValidators.forEach(validator => {
            const result = validator(this.getFormData());
            if (!result.valid) {
                isValid = false;
                errors[result.field] = result;
            }
        });
        
        // Record validation history
        this.validationHistory.push({
            timestamp: Date.now(),
            valid: isValid,
            errors: errors
        });
        
        return { isValid, errors };
    }
    
    getValidationReport() {
        const report = {
            formId: this.id,
            timestamp: Date.now(),
            fields: {},
            crossFieldErrors: [],
            summary: {
                totalFields: this.elements.length,
                validFields: 0,
                invalidFields: 0,
                totalErrors: 0
            }
        };
        
        this.elements.forEach(element => {
            const fieldReport = element.getValidationSummary();
            report.fields[element.name] = fieldReport;
            
            if (fieldReport.valid) {
                report.summary.validFields++;
            } else {
                report.summary.invalidFields++;
                report.summary.totalErrors += fieldReport.errors.length;
            }
        });
        
        return report;
    }
    
    reset() {
        this.elements.forEach(element => {
            element.reset();
        });
        this.validationHistory = [];
    }
}

// Advanced Form Validation System
class AdvancedFormValidator {
    constructor() {
        this.validators = new Map();
        this.errorMessages = new Map();
        this.validationStrategies = new Map();
    }
    
    // Register validation rule
    registerRule(name, rule) {
        this.validators.set(name, rule);
        console.log(`Registered validation rule: ${name}`);
    }
    
    // Register error message template
    registerErrorMessage(ruleName, messageTemplate) {
        this.errorMessages.set(ruleName, messageTemplate);
    }
    
    // Register validation strategy
    registerStrategy(name, strategy) {
        this.validationStrategies.set(name, strategy);
        console.log(`Registered validation strategy: ${name}`);
    }
    
    // Create validation rule
    createRule(name, validateFunction, message) {
        return {
            name: name,
            validate: validateFunction,
            message: message
        };
    }
    
    // Apply validation to field
    validateField(field, rules = []) {
        const errors = [];
        
        rules.forEach(rule => {
            if (!rule.validate(field.value)) {
                errors.push({
                    rule: rule.name,
                    message: rule.message,
                    field: field.name
                });
            }
        });
        
        return errors;
    }
    
    // Apply validation strategy
    applyStrategy(strategyName, form, options = {}) {
        const strategy = this.validationStrategies.get(strategyName);
        if (!strategy) {
            throw new Error(`Strategy '${strategyName}' not found`);
        }
        
        return strategy(form, options);
    }
}

// Test the Advanced Form Validation System
console.log("\n--- Testing Advanced Form Validation System ---");

const validator = new AdvancedFormValidator();

// Register validation rules
validator.registerRule('required', {
    validate: (value) => value.trim() !== '',
    message: 'This field is required'
});

validator.registerRule('email', {
    validate: (value) => /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value),
    message: 'Please enter a valid email address'
});

validator.registerRule('minLength', (min) => ({
    validate: (value) => value.length >= min,
    message: `Must be at least ${min} characters long`
}));

validator.registerRule('maxLength', (max) => ({
    validate: (value) => value.length <= max,
    message: `Must be no more than ${max} characters long`
}));

validator.registerRule('pattern', (pattern, message) => ({
    validate: (value) => new RegExp(pattern).test(value),
    message: message
}));

validator.registerRule('passwordStrength', {
    validate: (value) => {
        const hasLower = /[a-z]/.test(value);
        const hasUpper = /[A-Z]/.test(value);
        const hasNumber = /\d/.test(value);
        const hasSpecial = /[^a-zA-Z\d]/.test(value);
        return hasLower && hasUpper && hasNumber && hasSpecial;
    },
    message: 'Password must contain at least one lowercase letter, one uppercase letter, one number, and one special character'
});

validator.registerRule('phoneNumber', {
    validate: (value) => /^[\d\s\-\+\(\)]+$/.test(value) && value.replace(/\D/g, '').length >= 10,
    message: 'Please enter a valid phone number'
});

validator.registerRule('age', {
    validate: (value) => {
        const age = parseInt(value);
        return !isNaN(age) && age >= 13 && age <= 120;
    },
    message: 'Age must be between 13 and 120'
});

// Register validation strategies
validator.registerStrategy('realTime', (form, options) => {
    form.elements.forEach(element => {
        element.addEventListener('input', () => {
            const rules = options.rules || [];
            const errors = validator.validateField(element, rules);
            
            if (errors.length > 0) {
                element.style.borderColor = 'red';
                element.setCustomValidity(errors[0].message);
                console.log(`✗ ${element.name}: ${errors[0].message}`);
            } else {
                element.style.borderColor = 'green';
                element.setCustomValidity('');
                console.log(`✓ ${element.name}: Valid`);
            }
        });
    });
});

validator.registerStrategy('onSubmit', (form, options) => {
    form.addEventListener('submit', (event) => {
        event.preventDefault();
        
        const validationResult = form.validate();
        
        if (validationResult.isValid) {
            console.log('Form submitted successfully!');
            const formData = form.getFormData();
            console.log('Form data:', formData);
        } else {
            console.log('Form validation failed:');
            Object.keys(validationResult.errors).forEach(fieldName => {
                const error = validationResult.errors[fieldName];
                console.log(`  ${fieldName}: ${error.message}`);
            });
        }
    });
});

validator.registerStrategy('crossField', (form, options) => {
    const crossFieldRules = options.rules || [];
    
    crossFieldRules.forEach(rule => {
        form.addCrossFieldValidator(rule);
    });
});

// Create advanced form
const advancedForm = new AdvancedMockForm('advancedForm');

// Add form fields
const firstNameField = new AdvancedMockElement('input', 'text');
firstNameField.name = 'firstName';
firstNameField.id = 'firstName';
firstNameField.placeholder = 'First Name';
firstNameField.setAttribute('required', '');
advancedForm.appendChild(firstNameField);

const lastNameField = new AdvancedMockElement('input', 'text');
lastNameField.name = 'lastName';
lastNameField.id = 'lastName';
lastNameField.placeholder = 'Last Name';
lastNameField.setAttribute('required', '');
advancedForm.appendChild(lastNameField);

const emailField = new AdvancedMockElement('input', 'email');
emailField.name = 'email';
emailField.id = 'email';
emailField.placeholder = 'Email Address';
emailField.setAttribute('required', '');
advancedForm.appendChild(emailField);

const passwordField = new AdvancedMockElement('input', 'password');
passwordField.name = 'password';
passwordField.id = 'password';
passwordField.placeholder = 'Password';
passwordField.setAttribute('required', '');
advancedForm.appendChild(passwordField);

const confirmPasswordField = new AdvancedMockElement('input', 'password');
confirmPasswordField.name = 'confirmPassword';
confirmPasswordField.id = 'confirmPassword';
confirmPasswordField.placeholder = 'Confirm Password';
confirmPasswordField.setAttribute('required', '');
advancedForm.appendChild(confirmPasswordField);

const phoneField = new AdvancedMockElement('input', 'tel');
phoneField.name = 'phone';
phoneField.id = 'phone';
phoneField.placeholder = 'Phone Number';
advancedForm.appendChild(phoneField);

const ageField = new AdvancedMockElement('input', 'number');
ageField.name = 'age';
ageField.id = 'age';
ageField.placeholder = 'Age';
ageField.setAttribute('min', '13');
ageField.setAttribute('max', '120');
advancedForm.appendChild(ageField);

// Add validation rules to fields
firstNameField.addValidationRule(validator.validators.get('required'));
firstNameField.addValidationRule(validator.validators.get('minLength')(2));
firstNameField.addValidationRule(validator.validators.get('maxLength')(50));

lastNameField.addValidationRule(validator.validators.get('required'));
lastNameField.addValidationRule(validator.validators.get('minLength')(2));
lastNameField.addValidationRule(validator.validators.get('maxLength')(50));

emailField.addValidationRule(validator.validators.get('required'));
emailField.addValidationRule(validator.validators.get('email'));

passwordField.addValidationRule(validator.validators.get('required'));
passwordField.addValidationRule(validator.validators.get('minLength')(8));
passwordField.addValidationRule(validator.validators.get('passwordStrength'));

confirmPasswordField.addValidationRule(validator.validators.get('required'));

phoneField.addValidationRule(validator.validators.get('phoneNumber'));

ageField.addValidationRule(validator.validators.get('age'));

// Add cross-field validation
advancedForm.addCrossFieldValidator((formData) => {
    if (formData.password !== formData.confirmPassword) {
        return {
            valid: false,
            field: 'confirmPassword',
            message: 'Passwords do not match'
        };
    }
    return { valid: true };
});

// Apply validation strategies
validator.applyStrategy('realTime', advancedForm, {
    rules: [
        validator.validators.get('required'),
        validator.validators.get('email'),
        validator.validators.get('minLength')(2)
    ]
});

validator.applyStrategy('onSubmit', advancedForm);

validator.applyStrategy('crossField', advancedForm, {
    rules: [
        (formData) => {
            if (formData.password !== formData.confirmPassword) {
                return {
                    valid: false,
                    field: 'confirmPassword',
                    message: 'Passwords do not match'
                };
            }
            return { valid: true };
        }
    ]
});

// Test the advanced validation system
console.log("\n--- Testing Advanced Validation ---");

// Test with valid data
console.log("Testing with valid data:");
advancedForm.elements[0].value = 'John'; // firstName
advancedForm.elements[1].value = 'Doe'; // lastName
advancedForm.elements[2].value = 'john.doe@example.com'; // email
advancedForm.elements[3].value = 'MyPassword123!'; // password
advancedForm.elements[4].value = 'MyPassword123!'; // confirmPassword
advancedForm.elements[5].value = '+1 (555) 123-4567'; // phone
advancedForm.elements[6].value = '25'; // age

// Trigger validation
advancedForm.elements.forEach(element => {
    element.dispatchEvent('input');
});

// Test form submission
console.log("\n--- Testing Form Submission ---");
advancedForm.dispatchEvent('submit');

// Test with invalid data
console.log("\n--- Testing with Invalid Data ---");
advancedForm.elements[0].value = 'A'; // Too short firstName
advancedForm.elements[2].value = 'invalid-email'; // Invalid email
advancedForm.elements[3].value = 'weak'; // Weak password
advancedForm.elements[4].value = 'different'; // Mismatched password
advancedForm.elements[5].value = '123'; // Invalid phone
advancedForm.elements[6].value = '5'; // Too young

// Trigger validation
advancedForm.elements.forEach(element => {
    element.dispatchEvent('input');
});

// Test form submission with errors
advancedForm.dispatchEvent('submit');

// Get validation report
console.log("\n--- Validation Report ---");
const report = advancedForm.getValidationReport();
console.log('Validation Report:', report);

console.log("\n=== Exercise 3 Complete ===");
console.log("✓ Advanced form validation system");
console.log("✓ Custom validation rules and strategies");
console.log("✓ Real-time validation with visual feedback");
console.log("✓ Cross-field validation rules");
console.log("✓ Validation history tracking");
console.log("✓ Comprehensive error reporting");
console.log("✓ Password strength validation");
console.log("✓ Phone number and age validation");
console.log("✓ Form submission validation");
console.log("✓ Validation report generation");

