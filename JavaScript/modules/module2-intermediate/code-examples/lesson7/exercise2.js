// Exercise 2: Interactive Form Handling
// This exercise demonstrates form manipulation and validation

console.log("=== Exercise 2: Interactive Form Handling ===");

// Mock form elements
class MockFormElement {
    constructor(type, name, id = null) {
        this.type = type;
        this.name = name;
        this.id = id || name;
        this.value = '';
        this.checked = false;
        this.disabled = false;
        this.required = false;
        this.className = '';
        this.style = {};
        this.attributes = {};
    }
    
    setAttribute(name, value) {
        this.attributes[name] = value;
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
}

// Form validation functions
class FormValidator {
    static validateEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
    }
    
    static validatePassword(password) {
        return password.length >= 8;
    }
    
    static validateRequired(value) {
        return value.trim().length > 0;
    }
    
    static validateMinLength(value, minLength) {
        return value.length >= minLength;
    }
    
    static validateMaxLength(value, maxLength) {
        return value.length <= maxLength;
    }
    
    static validateNumber(value, min = null, max = null) {
        const num = parseFloat(value);
        if (isNaN(num)) return false;
        if (min !== null && num < min) return false;
        if (max !== null && num > max) return false;
        return true;
    }
}

// Form handler class
class FormHandler {
    constructor() {
        this.formData = {};
        this.errors = {};
        this.elements = {};
    }
    
    addElement(element) {
        this.elements[element.name] = element;
    }
    
    validateForm() {
        this.errors = {};
        let isValid = true;
        
        // Validate each element
        for (const [name, element] of Object.entries(this.elements)) {
            const value = element.value;
            const elementErrors = [];
            
            // Required validation
            if (element.required && !FormValidator.validateRequired(value)) {
                elementErrors.push(`${name} is required`);
            }
            
            // Type-specific validation
            if (value && element.type === 'email' && !FormValidator.validateEmail(value)) {
                elementErrors.push(`${name} must be a valid email`);
            }
            
            if (value && element.type === 'password' && !FormValidator.validatePassword(value)) {
                elementErrors.push(`${name} must be at least 8 characters`);
            }
            
            if (value && element.type === 'number') {
                const min = parseFloat(element.getAttribute('min'));
                const max = parseFloat(element.getAttribute('max'));
                if (!FormValidator.validateNumber(value, min, max)) {
                    elementErrors.push(`${name} must be a valid number`);
                }
            }
            
            if (elementErrors.length > 0) {
                this.errors[name] = elementErrors;
                isValid = false;
            }
        }
        
        return isValid;
    }
    
    getFormData() {
        const data = {};
        for (const [name, element] of Object.entries(this.elements)) {
            if (element.type === 'checkbox') {
                data[name] = element.checked;
            } else {
                data[name] = element.value;
            }
        }
        return data;
    }
    
    clearForm() {
        for (const element of Object.values(this.elements)) {
            element.value = '';
            element.checked = false;
            element.removeClass('error');
        }
        this.errors = {};
    }
    
    showErrors() {
        for (const [name, errors] of Object.entries(this.errors)) {
            const element = this.elements[name];
            if (element) {
                element.addClass('error');
                console.log(`${name} errors:`, errors);
            }
        }
    }
    
    clearErrors() {
        for (const element of Object.values(this.elements)) {
            element.removeClass('error');
        }
        this.errors = {};
    }
}

// Create a registration form
console.log("Creating registration form...");

const formHandler = new FormHandler();

// Create form elements
const username = new MockFormElement('text', 'username');
username.required = true;
username.setAttribute('minlength', '3');
username.setAttribute('maxlength', '20');

const email = new MockFormElement('email', 'email');
email.required = true;

const password = new MockFormElement('password', 'password');
password.required = true;

const confirmPassword = new MockFormElement('password', 'confirmPassword');
confirmPassword.required = true;

const age = new MockFormElement('number', 'age');
age.setAttribute('min', '13');
age.setAttribute('max', '120');

const newsletter = new MockFormElement('checkbox', 'newsletter');

const submitButton = new MockFormElement('submit', 'submit');
submitButton.value = 'Register';

// Add elements to form handler
formHandler.addElement(username);
formHandler.addElement(email);
formHandler.addElement(password);
formHandler.addElement(confirmPassword);
formHandler.addElement(age);
formHandler.addElement(newsletter);
formHandler.addElement(submitButton);

console.log("Form elements created:", Object.keys(formHandler.elements));

// Test form validation
console.log("\n=== Testing Form Validation ===");

// Test 1: Empty form
console.log("\nTest 1: Empty form");
formHandler.clearForm();
let isValid = formHandler.validateForm();
console.log("Form valid:", isValid);
if (!isValid) {
    formHandler.showErrors();
}

// Test 2: Invalid data
console.log("\nTest 2: Invalid data");
username.value = "ab"; // Too short
email.value = "invalid-email"; // Invalid email
password.value = "123"; // Too short
confirmPassword.value = "456"; // Different password
age.value = "5"; // Too young

isValid = formHandler.validateForm();
console.log("Form valid:", isValid);
if (!isValid) {
    formHandler.showErrors();
}

// Test 3: Valid data
console.log("\nTest 3: Valid data");
username.value = "john_doe";
email.value = "john@example.com";
password.value = "password123";
confirmPassword.value = "password123";
age.value = "25";
newsletter.checked = true;

isValid = formHandler.validateForm();
console.log("Form valid:", isValid);
if (!isValid) {
    formHandler.showErrors();
} else {
    console.log("Form data:", formHandler.getFormData());
}

// Test 4: Password confirmation
console.log("\nTest 4: Password confirmation validation");
password.value = "password123";
confirmPassword.value = "different123";

// Add custom validation for password confirmation
if (password.value !== confirmPassword.value) {
    formHandler.errors.confirmPassword = ["Passwords do not match"];
    isValid = false;
}

console.log("Password confirmation valid:", isValid);
if (!isValid) {
    console.log("Password confirmation errors:", formHandler.errors.confirmPassword);
}

// Test 5: Form submission simulation
console.log("\n=== Form Submission Simulation ===");

function simulateFormSubmission(formData) {
    console.log("Submitting form with data:", formData);
    
    // Simulate API call
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            // Simulate success/failure
            if (Math.random() > 0.3) {
                resolve({ success: true, message: "Registration successful!" });
            } else {
                reject({ success: false, message: "Registration failed. Please try again." });
            }
        }, 1000);
    });
}

// Test form submission
async function testFormSubmission() {
    // Set valid data
    username.value = "jane_doe";
    email.value = "jane@example.com";
    password.value = "securepassword123";
    confirmPassword.value = "securepassword123";
    age.value = "28";
    newsletter.checked = false;
    
    const formData = formHandler.getFormData();
    
    try {
        const result = await simulateFormSubmission(formData);
        console.log("Submission result:", result);
        
        if (result.success) {
            formHandler.clearForm();
            console.log("Form cleared after successful submission");
        }
    } catch (error) {
        console.log("Submission error:", error);
    }
}

// Run form submission test
testFormSubmission();

// Test 6: Dynamic form manipulation
console.log("\n=== Dynamic Form Manipulation ===");

// Add conditional field
const country = new MockFormElement('text', 'country');
const state = new MockFormElement('text', 'state');

formHandler.addElement(country);
formHandler.addElement(state);

// Simulate country selection affecting state field
function onCountryChange(countryValue) {
    console.log(`Country changed to: ${countryValue}`);
    
    if (countryValue === 'USA') {
        state.required = true;
        state.setAttribute('placeholder', 'Enter state (required for USA)');
        console.log("State field is now required");
    } else {
        state.required = false;
        state.setAttribute('placeholder', 'Enter state (optional)');
        console.log("State field is now optional");
    }
}

// Test country change
onCountryChange('USA');
onCountryChange('Canada');

console.log("\n=== Interactive Form Handling Summary ===");
console.log("✓ Form element creation and management");
console.log("✓ Form validation with multiple rules");
console.log("✓ Error handling and display");
console.log("✓ Form data collection and processing");
console.log("✓ Form submission simulation");
console.log("✓ Dynamic form behavior");
console.log("✓ Conditional field requirements");
