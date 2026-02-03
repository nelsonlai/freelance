# Lesson 4: Props and State

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand the difference between props and state
- Pass data through props
- Manage component state
- Use useState hook for state management
- Handle state updates and re-rendering
- Build interactive components

## 📚 Props vs State

### Props (Properties)
```javascript
// Props are passed down from parent components
function UserCard({ name, email, age }) {
    return (
        <div className="user-card">
            <h3>{name}</h3>
            <p>{email}</p>
            <p>Age: {age}</p>
        </div>
    );
}

// Usage
<UserCard name="John Doe" email="john@example.com" age={25} />
```

### State
```javascript
// State is managed within the component
function Counter() {
    const [count, setCount] = useState(0);
    
    return (
        <div>
            <p>Count: {count}</p>
            <button onClick={() => setCount(count + 1)}>
                Increment
            </button>
        </div>
    );
}
```

## 🎯 Practice Exercises

### Exercise 1: Interactive Form
Create a form with state management:

**Solution:**
```javascript
function ContactForm() {
    const [formData, setFormData] = useState({
        name: '',
        email: '',
        message: ''
    });
    
    const [isSubmitted, setIsSubmitted] = useState(false);
    
    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData(prev => ({
            ...prev,
            [name]: value
        }));
    };
    
    const handleSubmit = (e) => {
        e.preventDefault();
        console.log('Form submitted:', formData);
        setIsSubmitted(true);
    };
    
    if (isSubmitted) {
        return <div>Thank you for your message!</div>;
    }
    
    return (
        <form onSubmit={handleSubmit}>
            <input
                type="text"
                name="name"
                value={formData.name}
                onChange={handleChange}
                placeholder="Your Name"
            />
            <input
                type="email"
                name="email"
                value={formData.email}
                onChange={handleChange}
                placeholder="Your Email"
            />
            <textarea
                name="message"
                value={formData.message}
                onChange={handleChange}
                placeholder="Your Message"
            />
            <button type="submit">Send Message</button>
        </form>
    );
}
```

## 🎯 Key Takeaways

1. **Props** are passed down from parent components
2. **State** is managed within the component
3. **useState** hook manages component state
4. **State updates** trigger re-rendering
5. **Immutable updates** prevent bugs

---

**Next Lesson**: [Lesson 5: Handling Events in React](./lesson5-events.md)
