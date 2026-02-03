# Lesson 1: Introduction to Programming & JavaScript

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand what JavaScript is and why it matters
- Know where JavaScript runs (browser + Node.js)
- Set up your development environment
- Write your first "Hello World" program
- Use console.log() to display output
- Understand basic programming concepts

## 📚 What is JavaScript?

JavaScript is a **programming language** that makes websites interactive and dynamic. Think of it as the "brain" that tells web pages how to behave.

### Why JavaScript Matters

- **Everywhere**: Runs in every web browser
- **Versatile**: Can build websites, mobile apps, desktop apps, and servers
- **Popular**: One of the most used programming languages in the world
- **Job Market**: High demand for JavaScript developers

### Where JavaScript Runs

1. **In Web Browsers** (Frontend)
   - Makes websites interactive
   - Handles user clicks, form submissions, animations
   - Examples: Google, Facebook, Netflix websites

2. **On Servers** (Backend) - Node.js
   - Handles data processing
   - Manages databases
   - Serves web pages
   - Examples: Netflix backend, Uber server

## 🛠️ Setting Up Your Development Environment

### Step 1: Install VS Code

1. Go to [code.visualstudio.com](https://code.visualstudio.com)
2. Download and install VS Code
3. Open VS Code

### Step 2: Install Chrome Browser

1. Download Chrome if you don't have it
2. We'll use Chrome's Developer Tools to test our code

### Step 3: Install Node.js

1. Go to [nodejs.org](https://nodejs.org)
2. Download the LTS (Long Term Support) version
3. Install it
4. Open terminal/command prompt and type: `node --version`
5. You should see a version number (like v18.17.0)

### Step 4: Create Your First Project

1. Create a new folder called `my-first-js-project`
2. Open VS Code
3. Open the folder in VS Code (File → Open Folder)

## 🚀 Your First JavaScript Program

### Method 1: Running JavaScript in the Browser

Create a file called `index.html`:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My First JavaScript</title>
</head>
<body>
    <h1>Welcome to JavaScript!</h1>
    
    <script>
        // This is where we write JavaScript code
        console.log("Hello, World!");
        console.log("I'm learning JavaScript!");
    </script>
</body>
</html>
```

**How to run:**
1. Save the file
2. Right-click on `index.html` → "Open with Chrome"
3. Press F12 to open Developer Tools
4. Click on the "Console" tab
5. You should see your messages!

### Method 2: Running JavaScript with Node.js

Create a file called `hello.js`:

```javascript
// This is a comment - it doesn't run as code
console.log("Hello, World!");
console.log("I'm learning JavaScript!");
console.log("This is running with Node.js!");
```

**How to run:**
1. Open terminal/command prompt
2. Navigate to your project folder: `cd my-first-js-project`
3. Type: `node hello.js`
4. Press Enter
5. You should see your messages!

## 📝 Understanding console.log()

`console.log()` is a function that displays information in the console. It's like printing something on paper, but for programmers.

### Examples:

```javascript
// Display text
console.log("Hello, World!");

// Display numbers
console.log(42);
console.log(3.14);

// Display calculations
console.log(2 + 2);
console.log(10 * 5);

// Display multiple things
console.log("The answer is:", 42);
console.log("2 + 2 =", 2 + 2);
```

## 🎯 Practice Exercises

### Exercise 1: Basic Output
Create a file called `exercise1.js` and write code that displays:
- Your name
- Your age
- Your favorite color
- A simple math calculation (like 5 + 3)

**Solution:**
```javascript
console.log("My name is: John Doe");
console.log("My age is: 25");
console.log("My favorite color is: blue");
console.log("5 + 3 =", 5 + 3);
```

### Exercise 2: Multiple Calculations
Create a file called `exercise2.js` and calculate:
- The area of a rectangle (length × width)
- The circumference of a circle (2 × π × radius)
- The result of 100 divided by 7

**Solution:**
```javascript
// Rectangle area
let length = 10;
let width = 5;
console.log("Rectangle area:", length * width);

// Circle circumference
let radius = 3;
let pi = 3.14159;
console.log("Circle circumference:", 2 * pi * radius);

// Division
console.log("100 ÷ 7 =", 100 / 7);
```

### Exercise 3: Personal Information
Create a file called `exercise3.js` and display:
- Your name and age in one line
- Your city and country in another line
- A fun fact about yourself

**Solution:**
```javascript
console.log("Name: Alice, Age: 28");
console.log("City: New York, Country: USA");
console.log("Fun fact: I can solve a Rubik's cube in under 2 minutes!");
```

## 🔍 Understanding Code Structure

### Comments
Comments are notes for humans, not for the computer:

```javascript
// This is a single-line comment

/*
This is a multi-line comment
You can write multiple lines here
The computer will ignore all of this
*/
```

### Statements
Each line of code is called a **statement**:

```javascript
console.log("Hello");  // Statement 1
console.log("World");  // Statement 2
```

### Semicolons
JavaScript statements often end with semicolons (`;`):

```javascript
console.log("Hello");  // Good
console.log("World")   // Also works, but semicolons are recommended
```

## 🎯 Key Takeaways

1. **JavaScript** is a programming language that makes websites interactive
2. **JavaScript runs** in browsers (frontend) and on servers (Node.js)
3. **console.log()** displays information in the console
4. **Comments** help explain code to humans
5. **Statements** are individual lines of code
6. **Semicolons** end statements (recommended but not always required)

## 🚀 Next Steps

Congratulations! You've written your first JavaScript programs. In the next lesson, we'll learn about:

- **Variables** - storing information
- **Data Types** - different kinds of information
- **Type conversion** - changing one type to another

## 📚 Additional Resources

- [MDN JavaScript Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide)
- [JavaScript.info](https://javascript.info/)
- [Chrome DevTools Documentation](https://developers.google.com/web/tools/chrome-devtools)

## 🎉 Congratulations!

You've taken your first step into the world of JavaScript programming! You now know:

- What JavaScript is and why it's important
- How to set up your development environment
- How to write and run your first programs
- How to use console.log() to display output

Keep practicing with the exercises, and get ready for Lesson 2 where we'll learn about variables and data types!

---

**Next Lesson**: [Lesson 2: Variables and Data Types](./lesson2-variables-data-types.md)
