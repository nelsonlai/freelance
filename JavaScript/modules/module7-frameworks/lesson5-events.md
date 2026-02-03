# Lesson 5: Handling Events in React

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Handle events in React components
- Understand event object and synthetic events
- Prevent default behavior and stop propagation
- Pass event handlers as props
- Handle form events and input changes
- Create interactive user interfaces

## 📚 Event Handling

### Basic Event Handling
```javascript
function Button() {
    const handleClick = () => {
        alert('Button clicked!');
    };
    
    return <button onClick={handleClick}>Click Me</button>;
}
```

### Event Object
```javascript
function Input() {
    const handleChange = (event) => {
        console.log('Value:', event.target.value);
    };
    
    return <input onChange={handleChange} />;
}
```

## 🎯 Practice Exercises

### Exercise 1: Interactive Dashboard
Create an interactive dashboard with multiple events:

**Solution:**
```javascript
function Dashboard() {
    const [selectedTab, setSelectedTab] = useState('home');
    const [notifications, setNotifications] = useState([]);
    
    const handleTabClick = (tabName) => {
        setSelectedTab(tabName);
    };
    
    const handleAddNotification = () => {
        const newNotification = {
            id: Date.now(),
            message: `Notification ${notifications.length + 1}`,
            timestamp: new Date()
        };
        setNotifications(prev => [...prev, newNotification]);
    };
    
    const handleRemoveNotification = (id) => {
        setNotifications(prev => prev.filter(n => n.id !== id));
    };
    
    return (
        <div className="dashboard">
            <nav>
                {['home', 'profile', 'settings'].map(tab => (
                    <button
                        key={tab}
                        className={selectedTab === tab ? 'active' : ''}
                        onClick={() => handleTabClick(tab)}
                    >
                        {tab.charAt(0).toUpperCase() + tab.slice(1)}
                    </button>
                ))}
            </nav>
            
            <main>
                <h2>{selectedTab.charAt(0).toUpperCase() + selectedTab.slice(1)}</h2>
                
                <div className="notifications">
                    <button onClick={handleAddNotification}>
                        Add Notification
                    </button>
                    
                    {notifications.map(notification => (
                        <div key={notification.id} className="notification">
                            <span>{notification.message}</span>
                            <button onClick={() => handleRemoveNotification(notification.id)}>
                                ×
                            </button>
                        </div>
                    ))}
                </div>
            </main>
        </div>
    );
}
```

## 🎯 Key Takeaways

1. **Event handlers** use camelCase naming
2. **Synthetic events** provide consistent API
3. **Event object** contains target and other properties
4. **State updates** trigger re-rendering
5. **Event propagation** can be controlled

---

**Next Lesson**: [Lesson 6: Conditional Rendering and Lists](./lesson6-conditional-lists.md)
