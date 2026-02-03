# Lesson 6: Conditional Rendering and Lists

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Render components conditionally
- Use conditional operators in JSX
- Render lists of components
- Use keys for list items
- Handle empty states and loading states
- Create dynamic user interfaces

## 📚 Conditional Rendering

### Conditional Operators
```javascript
function UserProfile({ user, isLoggedIn }) {
    return (
        <div>
            {isLoggedIn ? (
                <div>
                    <h2>Welcome, {user.name}!</h2>
                    <p>Email: {user.email}</p>
                </div>
            ) : (
                <div>Please log in to view your profile.</div>
            )}
        </div>
    );
}
```

### List Rendering
```javascript
function TodoList({ todos }) {
    return (
        <ul>
            {todos.map(todo => (
                <li key={todo.id}>
                    {todo.text}
                </li>
            ))}
        </ul>
    );
}
```

## 🎯 Practice Exercises

### Exercise 1: Dynamic Content Manager
Create a component that manages dynamic content:

**Solution:**
```javascript
function ContentManager() {
    const [content, setContent] = useState([]);
    const [filter, setFilter] = useState('all');
    const [isLoading, setIsLoading] = useState(false);
    
    const addContent = (type, text) => {
        const newItem = {
            id: Date.now(),
            type,
            text,
            timestamp: new Date()
        };
        setContent(prev => [...prev, newItem]);
    };
    
    const removeContent = (id) => {
        setContent(prev => prev.filter(item => item.id !== id));
    };
    
    const filteredContent = content.filter(item => 
        filter === 'all' || item.type === filter
    );
    
    const handleLoadMore = () => {
        setIsLoading(true);
        setTimeout(() => {
            addContent('text', 'Loaded content');
            setIsLoading(false);
        }, 1000);
    };
    
    return (
        <div className="content-manager">
            <div className="controls">
                <button onClick={() => addContent('text', 'New text content')}>
                    Add Text
                </button>
                <button onClick={() => addContent('image', 'New image content')}>
                    Add Image
                </button>
                <button onClick={() => addContent('video', 'New video content')}>
                    Add Video
                </button>
            </div>
            
            <div className="filters">
                <select value={filter} onChange={(e) => setFilter(e.target.value)}>
                    <option value="all">All Content</option>
                    <option value="text">Text Only</option>
                    <option value="image">Images Only</option>
                    <option value="video">Videos Only</option>
                </select>
            </div>
            
            <div className="content-list">
                {filteredContent.length === 0 ? (
                    <div className="empty-state">
                        No content to display
                    </div>
                ) : (
                    filteredContent.map(item => (
                        <div key={item.id} className={`content-item ${item.type}`}>
                            <span>{item.text}</span>
                            <button onClick={() => removeContent(item.id)}>
                                Remove
                            </button>
                        </div>
                    ))
                )}
            </div>
            
            <div className="load-more">
                {isLoading ? (
                    <div>Loading...</div>
                ) : (
                    <button onClick={handleLoadMore}>
                        Load More
                    </button>
                )}
            </div>
        </div>
    );
}
```

## 🎯 Key Takeaways

1. **Conditional rendering** uses JavaScript expressions
2. **Lists** require unique keys for performance
3. **Empty states** improve user experience
4. **Loading states** provide feedback
5. **Dynamic content** creates interactive UIs

---

**Next Lesson**: [Lesson 7: React Hooks](./lesson7-hooks.md)
