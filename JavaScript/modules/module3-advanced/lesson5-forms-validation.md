# Lesson 5: Forms and Validation

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Handle form submission events
- Validate form inputs in real-time
- Prevent empty field submissions
- Create custom validation messages
- Implement form data collection
- Build user-friendly form experiences

## 📚 Form Handling

### Basic Form Submission
```javascript
const form = document.getElementById('myForm');

form.addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent default form submission
    
    const formData = new FormData(form);
    const data = Object.fromEntries(formData);
    
    console.log('Form data:', data);
    // Process the data
});
```

### Real-time Validation
```javascript
const emailInput = document.getElementById('email');

emailInput.addEventListener('input', function() {
    const email = this.value;
    const isValid = email.includes('@') && email.includes('.');
    
    if (isValid) {
        this.style.borderColor = 'green';
        this.setCustomValidity('');
    } else {
        this.style.borderColor = 'red';
        this.setCustomValidity('Please enter a valid email address');
    }
});
```

## 🎯 Practice Exercises

### Exercise 1: Contact Form Validator
Create a complete contact form with validation:

**Solution:**
```javascript
class ContactForm {
    constructor(formId) {
        this.form = document.getElementById(formId);
        this.init();
    }
    
    init() {
        this.form.addEventListener('submit', (e) => this.handleSubmit(e));
        this.setupValidation();
    }
    
    setupValidation() {
        const inputs = this.form.querySelectorAll('input, textarea');
        
        inputs.forEach(input => {
            input.addEventListener('blur', () => this.validateField(input));
            input.addEventListener('input', () => this.clearError(input));
        });
    }
    
    validateField(field) {
        const value = field.value.trim();
        let isValid = true;
        let message = '';
        
        if (field.hasAttribute('required') && !value) {
            isValid = false;
            message = 'This field is required';
        } else if (field.type === 'email' && value) {
            const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
            if (!emailRegex.test(value)) {
                isValid = false;
                message = 'Please enter a valid email address';
            }
        }
        
        this.showFieldError(field, isValid, message);
        return isValid;
    }
    
    showFieldError(field, isValid, message) {
        const errorElement = field.parentNode.querySelector('.error-message');
        
        if (isValid) {
            field.style.borderColor = 'green';
            if (errorElement) errorElement.remove();
        } else {
            field.style.borderColor = 'red';
            if (!errorElement) {
                const error = document.createElement('div');
                error.className = 'error-message';
                error.style.color = 'red';
                error.style.fontSize = '12px';
                field.parentNode.appendChild(error);
            }
            field.parentNode.querySelector('.error-message').textContent = message;
        }
    }
    
    clearError(field) {
        field.style.borderColor = '';
        const errorElement = field.parentNode.querySelector('.error-message');
        if (errorElement) errorElement.remove();
    }
    
    handleSubmit(event) {
        event.preventDefault();
        
        const inputs = this.form.querySelectorAll('input, textarea');
        let isFormValid = true;
        
        inputs.forEach(input => {
            if (!this.validateField(input)) {
                isFormValid = false;
            }
        });
        
        if (isFormValid) {
            this.submitForm();
        } else {
            console.log('Form has validation errors');
        }
    }
    
    submitForm() {
        const formData = new FormData(this.form);
        const data = Object.fromEntries(formData);
        
        console.log('Submitting form:', data);
        // Here you would typically send data to a server
        alert('Form submitted successfully!');
    }
}

// Usage
const contactForm = new ContactForm('contactForm');
```

## 🎯 Key Takeaways

1. **preventDefault()** stops default form submission
2. **FormData** collects form input values
3. **Real-time validation** improves user experience
4. **Custom validation** provides specific error messages
5. **Form classes** organize validation logic

---

**Next Lesson**: [Lesson 6: Timers and Intervals](./lesson6-timers-intervals.md)
