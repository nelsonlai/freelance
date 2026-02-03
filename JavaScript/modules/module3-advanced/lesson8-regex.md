# Lesson 8: Regular Expressions

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand regex syntax and patterns
- Use regex for pattern matching
- Validate input with regex
- Replace text using regex
- Extract data from strings
- Create common regex patterns

## 📚 Regular Expression Basics

### Creating Regex
```javascript
// Literal syntax
const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

// Constructor syntax
const phoneRegex = new RegExp('^\\d{3}-\\d{3}-\\d{4}$');
```

### Common Patterns
```javascript
// Email validation
const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

// Phone number (US format)
const phonePattern = /^\(\d{3}\) \d{3}-\d{4}$/;

// Password (8+ chars, 1 uppercase, 1 lowercase, 1 number)
const passwordPattern = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d@$!%*?&]{8,}$/;

// URL validation
const urlPattern = /^https?:\/\/.+\..+/;
```

### Regex Methods
```javascript
const text = "Contact us at support@example.com or call (555) 123-4567";

// Test method
console.log(emailPattern.test(text)); // true

// Match method
const matches = text.match(/\d{3}-\d{3}-\d{4}/);
console.log(matches); // ["123-4567"]

// Replace method
const masked = text.replace(/\d{3}-\d{3}-\d{4}/, 'XXX-XXX-XXXX');
console.log(masked); // "Contact us at support@example.com or call XXX-XXX-XXXX"
```

## 🎯 Practice Exercises

### Exercise 1: Input Validator
Create a comprehensive input validator:

**Solution:**
```javascript
class InputValidator {
    static patterns = {
        email: /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
        phone: /^\(\d{3}\) \d{3}-\d{4}$/,
        password: /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d@$!%*?&]{8,}$/,
        username: /^[a-zA-Z0-9_]{3,20}$/,
        url: /^https?:\/\/.+\..+/
    };
    
    static validate(type, value) {
        const pattern = this.patterns[type];
        if (!pattern) {
            throw new Error(`Unknown validation type: ${type}`);
        }
        
        return {
            isValid: pattern.test(value),
            message: this.getErrorMessage(type, value)
        };
    }
    
    static getErrorMessage(type, value) {
        const messages = {
            email: 'Please enter a valid email address',
            phone: 'Please enter a valid phone number (555) 123-4567',
            password: 'Password must be 8+ characters with uppercase, lowercase, and number',
            username: 'Username must be 3-20 characters (letters, numbers, underscore only)',
            url: 'Please enter a valid URL starting with http:// or https://'
        };
        
        return messages[type] || 'Invalid input';
    }
    
    static extractEmails(text) {
        const emailPattern = /[^\s@]+@[^\s@]+\.[^\s@]+/g;
        return text.match(emailPattern) || [];
    }
    
    static extractPhoneNumbers(text) {
        const phonePattern = /\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{4}/g;
        return text.match(phonePattern) || [];
    }
}

// Usage
console.log(InputValidator.validate('email', 'user@example.com'));
console.log(InputValidator.extractEmails('Contact us at support@example.com or info@company.com'));
```

## 🎯 Key Takeaways

1. **Regex patterns** match specific text patterns
2. **test()** checks if pattern matches
3. **match()** finds pattern matches
4. **replace()** substitutes matched text
5. **Common patterns** validate common input types

---

**Next Lesson**: [Lesson 9: Debugging Tools](./lesson9-debugging.md)
