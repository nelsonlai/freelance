# Lesson 7: DOM Manipulation Basics

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Select elements using `querySelector` and `querySelectorAll`
- Change element content with `innerText` and `innerHTML`
- Modify element styles dynamically
- Add and remove CSS classes
- Create and append new elements

## 📚 What is the DOM?

The **Document Object Model (DOM)** is a representation of HTML elements that JavaScript can interact with.

### Selecting Elements
```javascript
// Select single element
let heading = document.querySelector('h1');
let button = document.querySelector('#myButton');
let paragraph = document.querySelector('.myClass');

// Select multiple elements
let allParagraphs = document.querySelectorAll('p');
let allButtons = document.querySelectorAll('button');
```

### Changing Content
```javascript
// Change text content
heading.innerText = "New Heading";

// Change HTML content
paragraph.innerHTML = "<strong>Bold text</strong>";
```

### Changing Styles
```javascript
// Change individual styles
heading.style.color = "red";
heading.style.fontSize = "24px";

// Add/remove classes
heading.classList.add("highlight");
heading.classList.remove("old-class");
heading.classList.toggle("active");
```

## 🎯 Practice Exercises

### Exercise 1: Interactive Page
Create a page that changes when buttons are clicked:

**Solution:**
```javascript
// HTML structure needed:
// <h1 id="title">Hello World</h1>
// <button id="changeTitle">Change Title</button>
// <button id="changeColor">Change Color</button>

let title = document.querySelector('#title');
let changeTitleBtn = document.querySelector('#changeTitle');
let changeColorBtn = document.querySelector('#changeColor');

changeTitleBtn.addEventListener('click', function() {
    title.innerText = "Title Changed!";
});

changeColorBtn.addEventListener('click', function() {
    title.style.color = title.style.color === 'red' ? 'blue' : 'red';
});
```

## 🎯 Key Takeaways

1. **querySelector** selects single elements
2. **querySelectorAll** selects multiple elements
3. **innerText** changes text content
4. **innerHTML** changes HTML content
5. **style** property changes CSS styles

---

**Next Lesson**: [Lesson 8: Events](./lesson8-events.md)
