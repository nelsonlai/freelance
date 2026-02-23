# Frontend Design: HTML5, CSS & JavaScript
## Comprehensive Teaching Materials

---

## Table of Contents
1. [Introduction to Frontend Development](#1-introduction-to-frontend-development)
2. [HTML5 Fundamentals](#2-html5-fundamentals)
3. [HTML5 Semantic Elements](#3-html5-semantic-elements)
4. [HTML5 Forms & Input Types](#4-html5-forms--input-types)
5. [HTML5 Multimedia & APIs](#5-html5-multimedia--apis)
6. [CSS Fundamentals](#6-css-fundamentals)
7. [CSS Layout: Flexbox & Grid](#7-css-layout-flexbox--grid)
8. [Responsive Design](#8-responsive-design)
9. [JavaScript Fundamentals](#9-javascript-fundamentals)
10. [DOM Manipulation & Events](#10-dom-manipulation--events)
11. [Fetch API & Async JavaScript](#11-fetch-api--async-javascript)
12. [Frontend Best Practices](#12-frontend-best-practices)

---

## 1. Introduction to Frontend Development

### 1.1 What is the Frontend?

The **frontend** is everything users see and interact with in a web browser. It consists of three core technologies:

| Technology | Purpose | Role |
|------------|---------|------|
| **HTML** | Structure | Content, semantics, accessibility |
| **CSS** | Presentation | Styling, layout, visual design |
| **JavaScript** | Behavior | Interactivity, logic, API calls |

### 1.2 How They Work Together

```
HTML (Structure)     →  Defines WHAT is on the page (headings, paragraphs, forms)
CSS (Styling)        →  Defines HOW it looks (colors, fonts, layout)
JavaScript (Logic)   →  Defines WHAT it does (clicks, validation, data loading)
```

### 1.3 The Rendering Pipeline

1. Browser requests HTML
2. Browser parses HTML and builds DOM (Document Object Model)
3. CSS is applied to DOM → Render tree
4. Layout and paint → Visible page
5. JavaScript executes and can modify DOM, style, and behavior

---

## 2. HTML5 Fundamentals

### 2.1 The HTML5 Document Structure

Every HTML5 page starts with a document type declaration and a basic structure:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="Page description for SEO">
    <title>Page Title</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <!-- Page content goes here -->
    <script src="script.js"></script>
</body>
</html>
```

### 2.2 Key Head Elements

| Element | Purpose |
|---------|---------|
| `<!DOCTYPE html>` | Declares HTML5 (required) |
| `<meta charset="UTF-8">` | Character encoding (supports all languages) |
| `<meta name="viewport" ...>` | Responsive behavior on mobile |
| `<title>` | Page title (browser tab, search results) |
| `<link rel="stylesheet">` | External CSS |
| `<script>` | JavaScript (typically at end of body) |

### 2.3 Essential Block Elements

| Tag | Purpose | Example |
|-----|---------|---------|
| `<h1>` - `<h6>` | Headings (h1 = most important) | `<h1>Main Title</h1>` |
| `<p>` | Paragraph | `<p>Some text.</p>` |
| `<div>` | Generic container (block) | `<div class="wrapper">...</div>` |
| `<span>` | Generic inline container | `<span class="highlight">text</span>` |
| `<ul>`, `<ol>`, `<li>` | Lists (unordered, ordered, list item) | `<ul><li>Item</li></ul>` |
| `<a>` | Link | `<a href="https://...">Link</a>` |
| `<img>` | Image | `<img src="photo.jpg" alt="Description">` |

### 2.4 Inline vs Block

| Type | Behavior | Examples |
|------|----------|----------|
| **Block** | Takes full width, starts on new line | `div`, `p`, `h1`, `section` |
| **Inline** | Flows with text, no line break | `span`, `a`, `strong`, `em` |

---

## 3. HTML5 Semantic Elements

### 3.1 Why Semantics?

Semantic elements describe their **meaning**, not just appearance. Benefits:
- **Accessibility** — Screen readers understand structure
- **SEO** — Search engines better interpret content
- **Maintainability** — Clear, self-documenting markup

### 3.2 Main Semantic Elements

| Element | Purpose |
|---------|---------|
| `<header>` | Introductory content, nav, logo |
| `<nav>` | Navigation links |
| `<main>` | Primary content (one per page) |
| `<article>` | Self-contained content (blog post, news item) |
| `<section>` | Thematic grouping within content |
| `<aside>` | Tangentially related content (sidebar) |
| `<footer>` | Footer info (copyright, links) |

### 3.3 Typical Page Layout

```html
<body>
    <header>
        <nav>
            <a href="/">Home</a>
            <a href="/about">About</a>
            <a href="/contact">Contact</a>
        </nav>
    </header>

    <main>
        <article>
            <header>
                <h1>Article Title</h1>
            </header>
            <section>
                <h2>Section 1</h2>
                <p>Content...</p>
            </section>
            <section>
                <h2>Section 2</h2>
                <p>More content...</p>
            </section>
        </article>
        <aside>
            <h3>Related</h3>
            <ul>...</ul>
        </aside>
    </main>

    <footer>
        <p>© 2025 Company Name</p>
    </footer>
</body>
```

### 3.4 Visual Layout Reference

```
┌─────────────────────────────────────────┐
│              <header>                   │
│  Logo    <nav> Home | About | Contact   │
└─────────────────────────────────────────┘
┌──────────┬──────────────────┬──────────┐
│ <aside>  │     <main>        │ <aside>  │
│  Sidebar │  <article>        │  Widgets │
│          │  <section>...     │          │
│          │  <section>...     │          │
└──────────┴──────────────────┴──────────┘
┌─────────────────────────────────────────┐
│              <footer>                   │
│  © 2025 | Links | Social                │
└─────────────────────────────────────────┘
```

---

## 4. HTML5 Forms & Input Types

### 4.1 Basic Form Structure

```html
<form action="/submit" method="POST">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username" required>

    <label for="email">Email:</label>
    <input type="email" id="email" name="email" required>

    <label for="age">Age:</label>
    <input type="number" id="age" name="age" min="1" max="120">

    <button type="submit">Submit</button>
    <button type="reset">Reset</button>
</form>
```

### 4.2 HTML5 Input Types

| Type | Purpose | Browser Behavior |
|------|---------|------------------|
| `text` | Single-line text | — |
| `email` | Email address | Validation, mobile keyboard |
| `url` | URL | Validation |
| `number` | Numeric value | Spinner, min/max |
| `tel` | Phone number | Mobile numeric keyboard |
| `date` | Date picker | Native date picker |
| `time` | Time picker | Native time picker |
| `datetime-local` | Date and time | Native picker |
| `range` | Slider | Slider control |
| `color` | Color picker | Color picker |
| `password` | Password (masked) | Masked input |
| `search` | Search field | Search styling |
| `file` | File upload | File selector |

### 4.3 Form Attributes

| Attribute | Purpose | Example |
|-----------|---------|---------|
| `required` | Field is mandatory | `<input required>` |
| `placeholder` | Hint text | `<input placeholder="Enter name">` |
| `min`, `max` | Numeric/date range | `<input type="number" min="0" max="100">` |
| `pattern` | Regex validation | `<input pattern="[A-Za-z]+">` |
| `autofocus` | Focus on load | `<input autofocus>` |
| `disabled` | Disabled input | `<input disabled>` |
| `readonly` | Read-only (still submitted) | `<input readonly>` |

### 4.4 Other Form Elements

```html
<!-- Textarea -->
<textarea name="message" rows="4" cols="50" placeholder="Your message"></textarea>

<!-- Select dropdown -->
<select name="country">
    <option value="">Choose...</option>
    <option value="us">United States</option>
    <option value="uk">United Kingdom</option>
</select>

<!-- Checkbox -->
<input type="checkbox" id="agree" name="agree" value="yes">
<label for="agree">I agree to terms</label>

<!-- Radio buttons -->
<input type="radio" id="male" name="gender" value="male">
<label for="male">Male</label>
<input type="radio" id="female" name="gender" value="female">
<label for="female">Female</label>
```

---

## 5. HTML5 Multimedia & APIs

### 5.1 Audio

```html
<audio controls>
    <source src="audio.mp3" type="audio/mpeg">
    <source src="audio.ogg" type="audio/ogg">
    Your browser does not support the audio element.
</audio>
```

### 5.2 Video

```html
<video controls width="640" height="360" poster="thumbnail.jpg">
    <source src="video.mp4" type="video/mp4">
    <source src="video.webm" type="video/webm">
    Your browser does not support the video element.
</video>
```

### 5.3 Canvas (Drawing)

```html
<canvas id="myCanvas" width="400" height="200"></canvas>
<script>
    const canvas = document.getElementById('myCanvas');
    const ctx = canvas.getContext('2d');
    ctx.fillStyle = 'blue';
    ctx.fillRect(10, 10, 100, 50);
</script>
```

### 5.4 SVG (Vector Graphics)

```html
<svg width="100" height="100" viewBox="0 0 100 100">
    <circle cx="50" cy="50" r="40" fill="red"/>
    <rect x="20" y="60" width="60" height="20" fill="blue"/>
</svg>
```

### 5.5 Data Attributes

Store custom data for JavaScript:

```html
<div data-user-id="42" data-role="admin">User Info</div>
```

```javascript
const el = document.querySelector('div');
console.log(el.dataset.userId);  // "42"
console.log(el.dataset.role);    // "admin"
```

---

## 6. CSS Fundamentals

### 6.1 Including CSS

```html
<!-- External stylesheet (preferred) -->
<link rel="stylesheet" href="styles.css">

<!-- Internal (in <head>) -->
<style>
    body { font-family: Arial, sans-serif; }
</style>

<!-- Inline (avoid when possible) -->
<p style="color: red;">Red text</p>
```

### 6.2 Selectors

| Selector | Example | Targets |
|----------|---------|---------|
| Element | `p { }` | All `<p>` elements |
| Class | `.highlight { }` | Elements with `class="highlight"` |
| ID | `#header { }` | Element with `id="header"` |
| Descendant | `div p { }` | `<p>` inside any `<div>` |
| Child | `div > p { }` | `<p>` direct child of `<div>` |
| Attribute | `[type="text"] { }` | Elements with `type="text"` |
| Pseudo-class | `a:hover { }` | Links when hovered |
| Pseudo-element | `p::first-line { }` | First line of `<p>` |

### 6.3 The Box Model

Every element is a box with:

```
┌─────────────────────────────────────┐
│              margin                 │
│  ┌───────────────────────────────┐  │
│  │           border              │  │
│  │  ┌─────────────────────────┐  │  │
│  │  │        padding          │  │  │
│  │  │  ┌───────────────────┐  │  │  │
│  │  │  │     content       │  │  │  │
│  │  │  └───────────────────┘  │  │  │
│  │  └─────────────────────────┘  │  │
│  └───────────────────────────────┘  │
└─────────────────────────────────────┘
```

```css
.box {
    width: 200px;
    height: 100px;
    padding: 20px;
    border: 2px solid black;
    margin: 10px;
    box-sizing: border-box;  /* Includes padding/border in width/height */
}
```

### 6.4 Common Properties

**Typography:**
```css
font-family: 'Helvetica Neue', Arial, sans-serif;
font-size: 16px;
font-weight: bold;
line-height: 1.5;
text-align: center;
```

**Colors:**
```css
color: #333;
color: rgb(51, 51, 51);
color: hsl(0, 0%, 20%);
background-color: #f0f0f0;
```

**Spacing:**
```css
margin: 10px;
margin: 10px 20px;        /* top/bottom, left/right */
margin: 10px 20px 15px;   /* top, left/right, bottom */
padding: 10px;
```

---

## 7. CSS Layout: Flexbox & Grid

### 7.1 Flexbox (One-Dimensional)

Flexbox lays out items along a **main axis** (row or column).

```css
.container {
    display: flex;
    flex-direction: row;      /* row | row-reverse | column | column-reverse */
    justify-content: center;  /* main axis: flex-start | center | flex-end | space-between | space-around */
    align-items: center;      /* cross axis: flex-start | center | flex-end | stretch */
    gap: 1rem;
    flex-wrap: wrap;         /* wrap items to new line */
}

.item {
    flex: 1;                 /* grow/shrink to fill space */
    flex-grow: 1;
    flex-shrink: 0;
    flex-basis: 200px;
}
```

**Common Flexbox Patterns:**
- Center content: `display: flex; justify-content: center; align-items: center;`
- Space between: `justify-content: space-between;`
- Equal columns: `flex: 1` on each child

### 7.2 CSS Grid (Two-Dimensional)

Grid defines **rows and columns** for layout.

```css
.container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr;   /* 3 equal columns */
    grid-template-rows: auto 1fr auto;
    gap: 20px;
}

/* Or use repeat() */
.container {
    grid-template-columns: repeat(3, 1fr);
}

/* Responsive grid */
.container {
    grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
}
```

### 7.3 Flexbox vs Grid

| Flexbox | Grid |
|---------|------|
| One dimension (row or column) | Two dimensions (rows and columns) |
| Content-driven | Layout-driven |
| Good for: nav, cards in a row | Good for: page layout, complex grids |

---

## 8. Responsive Design

### 8.1 Viewport Meta Tag

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

### 8.2 Media Queries

```css
/* Mobile first: base styles for mobile */
.card {
    width: 100%;
}

/* Tablet and up */
@media (min-width: 768px) {
    .card {
        width: 50%;
    }
}

/* Desktop */
@media (min-width: 1024px) {
    .card {
        width: 33.333%;
    }
}
```

### 8.3 Responsive Units

| Unit | Description | Use Case |
|------|-------------|----------|
| `rem` | Relative to root font size | Typography, spacing |
| `em` | Relative to parent font size | Component scaling |
| `%` | Percentage of parent | Widths, layout |
| `vw`, `vh` | Viewport width/height | Full-width sections |
| `ch` | Character width | Max-width for readability |

```css
html {
    font-size: 16px;  /* 1rem = 16px */
}

body {
    font-size: 1rem;
    max-width: 65ch;  /* ~65 characters per line */
}
```

### 8.4 Breakpoint Conventions

| Breakpoint | Width | Device |
|------------|-------|--------|
| xs | &lt; 576px | Mobile |
| sm | ≥ 576px | Large mobile |
| md | ≥ 768px | Tablet |
| lg | ≥ 992px | Laptop |
| xl | ≥ 1200px | Desktop |
| xxl | ≥ 1400px | Large desktop |

---

## 9. JavaScript Fundamentals

### 9.1 Variables

```javascript
let x = 10;           // Mutable
const PI = 3.14;      // Immutable (preferred for constants)
var old = 5;          // Avoid (function-scoped, legacy)
```

### 9.2 Data Types

| Type | Example |
|------|---------|
| Number | `42`, `3.14` |
| String | `'hello'`, `"world"`, `` `template ${x}` `` |
| Boolean | `true`, `false` |
| Undefined | `undefined` |
| Null | `null` |
| Object | `{ key: 'value' }` |
| Array | `[1, 2, 3]` |
| Function | `function() {}` |

### 9.3 Functions

```javascript
function greet(name) {
    return `Hello, ${name}!`;
}

const greet = function(name) {
    return `Hello, ${name}!`;
};

const greet = (name) => `Hello, ${name}!`;  // Arrow function
```

### 9.4 Arrays & Objects

```javascript
const arr = [1, 2, 3];
arr.push(4);
arr.pop();
arr.map(x => x * 2);
arr.filter(x => x > 1);
arr.find(x => x === 2);

const obj = { name: 'John', age: 30 };
obj.name;
obj['age'];
Object.keys(obj);
```

### 9.5 Control Flow

```javascript
if (condition) { }
else if (other) { }
else { }

for (let i = 0; i < 10; i++) { }
for (const item of array) { }

switch (value) {
    case 'a': break;
    case 'b': break;
    default: break;
}
```

---

## 10. DOM Manipulation & Events

### 10.1 Selecting Elements

```javascript
document.getElementById('id');
document.querySelector('.class');      // First match
document.querySelectorAll('.class');   // All matches
document.getElementsByClassName('class');
document.getElementsByTagName('div');
```

### 10.2 Modifying Content & Attributes

```javascript
element.textContent = 'New text';
element.innerHTML = '<strong>HTML</strong>';
element.setAttribute('href', 'https://...');
element.getAttribute('href');
element.classList.add('active');
element.classList.remove('active');
element.classList.toggle('active');
element.style.color = 'red';
```

### 10.3 Creating & Removing Elements

```javascript
const div = document.createElement('div');
div.textContent = 'Hello';
parent.appendChild(div);
parent.removeChild(child);
```

### 10.4 Events

```javascript
button.addEventListener('click', function(e) {
    console.log('Clicked');
    e.preventDefault();  // Prevent default (e.g., form submit)
});

// Common events: click, submit, focus, blur, keydown, keyup, input, change, load
```

### 10.5 Event Delegation

Listen on parent, use `e.target` for the clicked child:

```javascript
list.addEventListener('click', function(e) {
    if (e.target.matches('li')) {
        console.log('Clicked:', e.target.textContent);
    }
});
```

---

## 11. Fetch API & Async JavaScript

### 11.1 Fetch (GET)

```javascript
fetch('https://api.example.com/users')
    .then(response => response.json())
    .then(data => console.log(data))
    .catch(err => console.error(err));
```

### 11.2 Fetch (POST)

```javascript
fetch('https://api.example.com/users', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer <token>'
    },
    body: JSON.stringify({ name: 'John', email: 'john@example.com' })
})
    .then(res => res.json())
    .then(data => console.log(data));
```

### 11.3 Async/Await

```javascript
async function getUsers() {
    try {
        const response = await fetch('https://api.example.com/users');
        if (!response.ok) throw new Error('Network error');
        const users = await response.json();
        return users;
    } catch (error) {
        console.error('Failed:', error);
        throw error;
    }
}
```

### 11.4 Response Handling

```javascript
const response = await fetch(url);

response.ok           // true if 2xx
response.status       // 200, 404, etc.
response.json()       // Parse as JSON
response.text()       // Parse as text
response.headers.get('Content-Type')
```

---

## 12. Frontend Best Practices

### 12.1 Accessibility (a11y)

- Use semantic HTML
- Provide `alt` text for images
- Ensure sufficient color contrast
- Make interactive elements keyboard accessible
- Use `aria-*` attributes when needed

### 12.2 Performance

- Minify CSS/JS in production
- Optimize images (format, size, lazy loading)
- Defer non-critical JavaScript
- Use browser caching

### 12.3 Code Organization

- Separate HTML, CSS, and JS files
- Use consistent naming (BEM for CSS, camelCase for JS)
- Comment complex logic
- Use meaningful variable and function names

### 12.4 Cross-Browser Compatibility

- Test in Chrome, Firefox, Safari, Edge
- Use vendor prefixes when needed (`-webkit-`, `-moz-`)
- Check [caniuse.com](https://caniuse.com) for feature support

---

## Summary

| Topic | Key Takeaway |
|-------|--------------|
| **HTML5** | Structure with semantic elements, forms, multimedia |
| **CSS** | Selectors, box model, Flexbox, Grid, responsive design |
| **JavaScript** | Variables, functions, DOM, events, Fetch/async |
| **Frontend** | HTML + CSS + JS = structure, style, behavior |

---

## Further Reading

- [MDN Web Docs](https://developer.mozilla.org/) — Authoritative reference
- [HTML5 Doctor](http://html5doctor.com/) — Semantic HTML
- [CSS-Tricks](https://css-tricks.com/) — CSS guides and Flexbox/Grid
- [JavaScript.info](https://javascript.info/) — Modern JavaScript tutorial
