# Lesson 8: Events

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Add event listeners to elements
- Handle different types of events (click, input, submit)
- Understand event bubbling and delegation
- Prevent default browser behavior
- Create interactive web applications

## 📚 What are Events?

**Events** are actions that happen in the browser, like clicks, key presses, or form submissions.

### Adding Event Listeners
```javascript
let button = document.querySelector('#myButton');

// Method 1: addEventListener (recommended)
button.addEventListener('click', function() {
    console.log('Button clicked!');
});

// Method 2: onclick (older method)
button.onclick = function() {
    console.log('Button clicked!');
};
```

### Common Event Types
```javascript
// Click events
button.addEventListener('click', handleClick);

// Input events
let input = document.querySelector('#myInput');
input.addEventListener('input', function(event) {
    console.log('Input changed:', event.target.value);
});

// Form submission
let form = document.querySelector('#myForm');
form.addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent form submission
    console.log('Form submitted!');
});
```

## 🎯 Practice Exercises

### Exercise 1: Interactive Counter
Create a counter that increments when clicked:

**Solution:**
```javascript
// HTML needed: <button id="counter">Count: 0</button>

let counter = 0;
let button = document.querySelector('#counter');

button.addEventListener('click', function() {
    counter++;
    button.innerText = `Count: ${counter}`;
});
```

### Exercise 2: Form Validation
Create a form that validates input:

**Solution:**
```javascript
// HTML needed: <input id="email" type="email"> <span id="error"></span>

let emailInput = document.querySelector('#email');
let errorSpan = document.querySelector('#error');

emailInput.addEventListener('input', function() {
    let email = this.value;
    if (email.includes('@')) {
        errorSpan.innerText = '';
        this.style.borderColor = 'green';
    } else {
        errorSpan.innerText = 'Please enter a valid email';
        this.style.borderColor = 'red';
    }
});
```

## 🎯 Key Takeaways

1. **addEventListener** is the modern way to handle events
2. **Event types** include click, input, submit, etc.
3. **preventDefault()** stops default browser behavior
4. **Event delegation** handles events efficiently

---

**Next Lesson**: [Lesson 9: JSON & LocalStorage](./lesson9-json-localstorage.md)
