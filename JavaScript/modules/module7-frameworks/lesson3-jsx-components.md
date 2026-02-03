# Lesson 3: JSX and Components

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand JSX syntax and rules
- Create functional and class components
- Use JSX expressions and attributes
- Handle events in JSX
- Understand component composition
- Build reusable UI components

## 📚 JSX Basics

### JSX Syntax
```javascript
// JSX expression
const name = 'React';
const element = <h1>Hello, {name}!</h1>;

// JSX attributes
const element = <div className="container" id="main">Content</div>;

// JSX with children
const element = (
    <div>
        <h1>Title</h1>
        <p>Paragraph</p>
    </div>
);
```

### Functional Components
```javascript
function Welcome(props) {
    return <h1>Hello, {props.name}!</h1>;
}

// Arrow function component
const Welcome = (props) => {
    return <h1>Hello, {props.name}!</h1>;
};
```

## 🎯 Practice Exercises

### Exercise 1: Component Library
Create a library of reusable components:

**Solution:**
```javascript
// Button Component
function Button({ children, onClick, variant = 'primary', size = 'medium' }) {
    const baseClasses = 'btn';
    const variantClasses = `btn-${variant}`;
    const sizeClasses = `btn-${size}`;
    
    return (
        <button 
            className={`${baseClasses} ${variantClasses} ${sizeClasses}`}
            onClick={onClick}
        >
            {children}
        </button>
    );
}

// Card Component
function Card({ title, content, footer }) {
    return (
        <div className="card">
            {title && <div className="card-header">{title}</div>}
            <div className="card-body">{content}</div>
            {footer && <div className="card-footer">{footer}</div>}
        </div>
    );
}

// Usage
function App() {
    return (
        <div>
            <Button onClick={() => alert('Clicked!')}>
                Click Me
            </Button>
            
            <Card 
                title="Welcome"
                content="This is a card component"
                footer={<Button variant="secondary">Learn More</Button>}
            />
        </div>
    );
}
```

## 🎯 Key Takeaways

1. **JSX** combines JavaScript and HTML
2. **Components** are reusable UI pieces
3. **Props** pass data to components
4. **Composition** builds complex UIs from simple parts
5. **Event handling** uses camelCase attributes

---

**Next Lesson**: [Lesson 4: Props and State](./lesson4-props-state.md)
