# Lesson 2: Intro to React.js

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Set up a React development environment
- Create your first React application
- Understand React elements and components
- Use Create React App for project setup
- Understand the React development workflow
- Write basic React code

## 📚 React Setup

### Create React App
```bash
# Install Create React App globally
npm install -g create-react-app

# Create new React app
npx create-react-app my-react-app

# Navigate to project
cd my-react-app

# Start development server
npm start
```

### Basic React Element
```javascript
// React element (not HTML)
const element = <h1>Hello, React!</h1>;

// Rendering to DOM
ReactDOM.render(element, document.getElementById('root'));
```

## 🎯 Practice Exercises

### Exercise 1: First React App
Create a simple React application:

**Solution:**
```javascript
// App.js
import React from 'react';

function App() {
    return (
        <div className="App">
            <header className="App-header">
                <h1>Welcome to React!</h1>
                <p>This is my first React application.</p>
            </header>
        </div>
    );
}

export default App;
```

## 🎯 Key Takeaways

1. **Create React App** sets up development environment
2. **React elements** are JavaScript objects
3. **JSX** combines JavaScript and HTML
4. **Components** are reusable UI pieces
5. **Development server** provides hot reloading

---

**Next Lesson**: [Lesson 3: JSX and Components](./lesson3-jsx-components.md)
