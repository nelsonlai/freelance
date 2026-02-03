# Lesson 7: React Hooks

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand React Hooks and their purpose
- Use useState for state management
- Use useEffect for side effects
- Use useContext for context sharing
- Use custom hooks for reusable logic
- Build modern React applications

## 📚 React Hooks

### useState Hook
```javascript
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

### useEffect Hook
```javascript
function DataFetcher({ url }) {
    const [data, setData] = useState(null);
    const [loading, setLoading] = useState(true);
    
    useEffect(() => {
        fetch(url)
            .then(response => response.json())
            .then(data => {
                setData(data);
                setLoading(false);
            });
    }, [url]);
    
    if (loading) return <div>Loading...</div>;
    return <div>{JSON.stringify(data)}</div>;
}
```

## 🎯 Practice Exercises

### Exercise 1: Custom Hook Library
Create a library of custom hooks:

**Solution:**
```javascript
// Custom hook for local storage
function useLocalStorage(key, initialValue) {
    const [storedValue, setStoredValue] = useState(() => {
        try {
            const item = window.localStorage.getItem(key);
            return item ? JSON.parse(item) : initialValue;
        } catch (error) {
            return initialValue;
        }
    });
    
    const setValue = (value) => {
        try {
            setStoredValue(value);
            window.localStorage.setItem(key, JSON.stringify(value));
        } catch (error) {
            console.error(error);
        }
    };
    
    return [storedValue, setValue];
}

// Custom hook for API calls
function useApi(url) {
    const [data, setData] = useState(null);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);
    
    useEffect(() => {
        const fetchData = async () => {
            try {
                setLoading(true);
                const response = await fetch(url);
                const result = await response.json();
                setData(result);
            } catch (err) {
                setError(err);
            } finally {
                setLoading(false);
            }
        };
        
        fetchData();
    }, [url]);
    
    return { data, loading, error };
}

// Custom hook for form handling
function useForm(initialValues) {
    const [values, setValues] = useState(initialValues);
    const [errors, setErrors] = useState({});
    
    const handleChange = (e) => {
        const { name, value } = e.target;
        setValues(prev => ({
            ...prev,
            [name]: value
        }));
        
        // Clear error when user starts typing
        if (errors[name]) {
            setErrors(prev => ({
                ...prev,
                [name]: ''
            }));
        }
    };
    
    const handleSubmit = (onSubmit) => (e) => {
        e.preventDefault();
        onSubmit(values);
    };
    
    const reset = () => {
        setValues(initialValues);
        setErrors({});
    };
    
    return {
        values,
        errors,
        handleChange,
        handleSubmit,
        reset,
        setErrors
    };
}

// Usage example
function UserProfile() {
    const [user, setUser] = useLocalStorage('user', { name: '', email: '' });
    const { data: profile, loading } = useApi('/api/profile');
    const { values, handleChange, handleSubmit } = useForm(user);
    
    const onSubmit = (formData) => {
        setUser(formData);
        console.log('Profile updated:', formData);
    };
    
    if (loading) return <div>Loading profile...</div>;
    
    return (
        <form onSubmit={handleSubmit(onSubmit)}>
            <input
                name="name"
                value={values.name}
                onChange={handleChange}
                placeholder="Name"
            />
            <input
                name="email"
                value={values.email}
                onChange={handleChange}
                placeholder="Email"
            />
            <button type="submit">Update Profile</button>
        </form>
    );
}
```

## 🎯 Key Takeaways

1. **Hooks** enable stateful logic in functional components
2. **useState** manages component state
3. **useEffect** handles side effects
4. **Custom hooks** encapsulate reusable logic
5. **Hooks** follow naming conventions and rules

---

**Next Lesson**: [Lesson 8: Router and Navigation](./lesson8-routing.md)
