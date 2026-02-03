# Lesson 4: DOM Advanced

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Create and remove DOM elements dynamically
- Build dynamic lists and templates
- Manipulate element attributes and classes
- Use document fragments for performance
- Implement advanced DOM traversal
- Create reusable DOM manipulation functions

## 📚 Advanced DOM Manipulation

### Creating Elements
```javascript
// Create new element
const newDiv = document.createElement('div');
newDiv.textContent = 'Hello World';
newDiv.className = 'my-class';

// Append to parent
document.body.appendChild(newDiv);
```

### Removing Elements
```javascript
// Remove element
const element = document.querySelector('.to-remove');
element.remove();

// Remove from parent
const parent = element.parentNode;
parent.removeChild(element);
```

### Document Fragments
```javascript
// Efficient way to add multiple elements
const fragment = document.createDocumentFragment();

for (let i = 0; i < 100; i++) {
    const li = document.createElement('li');
    li.textContent = `Item ${i}`;
    fragment.appendChild(li);
}

document.getElementById('list').appendChild(fragment);
```

## 🎯 Practice Exercises

### Exercise 1: Dynamic List Builder
Create a function that builds a dynamic list:

**Solution:**
```javascript
function createDynamicList(items, containerId) {
    const container = document.getElementById(containerId);
    const fragment = document.createDocumentFragment();
    
    items.forEach(item => {
        const li = document.createElement('li');
        li.textContent = item;
        li.className = 'list-item';
        fragment.appendChild(li);
    });
    
    container.appendChild(fragment);
}

// Usage
const items = ['Apple', 'Banana', 'Orange'];
createDynamicList(items, 'myList');
```

## 🎯 Key Takeaways

1. **createElement** creates new DOM elements
2. **appendChild** adds elements to parents
3. **remove** removes elements efficiently
4. **Document fragments** improve performance
5. **Dynamic content** makes pages interactive

---

**Next Lesson**: [Lesson 5: Forms and Validation](./lesson5-forms-validation.md)
