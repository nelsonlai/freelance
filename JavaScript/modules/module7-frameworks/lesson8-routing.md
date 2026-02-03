# Lesson 8: Router and Navigation

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Set up React Router for navigation
- Create routes and route components
- Handle navigation between pages
- Use route parameters and query strings
- Implement protected routes
- Build single-page applications

## 📚 React Router

### Basic Setup
```javascript
import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';

function App() {
    return (
        <BrowserRouter>
            <nav>
                <Link to="/">Home</Link>
                <Link to="/about">About</Link>
                <Link to="/contact">Contact</Link>
            </nav>
            
            <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/about" element={<About />} />
                <Route path="/contact" element={<Contact />} />
            </Routes>
        </BrowserRouter>
    );
}
```

### Route Parameters
```javascript
function UserProfile() {
    const { id } = useParams();
    const [user, setUser] = useState(null);
    
    useEffect(() => {
        fetch(`/api/users/${id}`)
            .then(response => response.json())
            .then(setUser);
    }, [id]);
    
    if (!user) return <div>Loading...</div>;
    
    return <div>User: {user.name}</div>;
}

// Route definition
<Route path="/user/:id" element={<UserProfile />} />
```

## 🎯 Practice Exercises

### Exercise 1: Complete Navigation System
Create a complete navigation system with protected routes:

**Solution:**
```javascript
import { BrowserRouter, Routes, Route, Link, Navigate } from 'react-router-dom';

// Context for authentication
const AuthContext = createContext();

function AuthProvider({ children }) {
    const [user, setUser] = useState(null);
    
    const login = (userData) => {
        setUser(userData);
        localStorage.setItem('user', JSON.stringify(userData));
    };
    
    const logout = () => {
        setUser(null);
        localStorage.removeItem('user');
    };
    
    useEffect(() => {
        const savedUser = localStorage.getItem('user');
        if (savedUser) {
            setUser(JSON.parse(savedUser));
        }
    }, []);
    
    return (
        <AuthContext.Provider value={{ user, login, logout }}>
            {children}
        </AuthContext.Provider>
    );
}

// Protected route component
function ProtectedRoute({ children }) {
    const { user } = useContext(AuthContext);
    return user ? children : <Navigate to="/login" />;
}

// Login component
function Login() {
    const { login } = useContext(AuthContext);
    const [formData, setFormData] = useState({ email: '', password: '' });
    
    const handleSubmit = (e) => {
        e.preventDefault();
        // Simulate login
        login({ email: formData.email, name: 'User' });
    };
    
    return (
        <form onSubmit={handleSubmit}>
            <input
                type="email"
                value={formData.email}
                onChange={(e) => setFormData({ ...formData, email: e.target.value })}
                placeholder="Email"
            />
            <input
                type="password"
                value={formData.password}
                onChange={(e) => setFormData({ ...formData, password: e.target.value })}
                placeholder="Password"
            />
            <button type="submit">Login</button>
        </form>
    );
}

// Dashboard component
function Dashboard() {
    const { user, logout } = useContext(AuthContext);
    
    return (
        <div>
            <h1>Welcome, {user.name}!</h1>
            <button onClick={logout}>Logout</button>
        </div>
    );
}

// Main App component
function App() {
    return (
        <AuthProvider>
            <BrowserRouter>
                <nav>
                    <Link to="/">Home</Link>
                    <Link to="/dashboard">Dashboard</Link>
                    <Link to="/profile">Profile</Link>
                </nav>
                
                <Routes>
                    <Route path="/" element={<Home />} />
                    <Route path="/login" element={<Login />} />
                    <Route path="/dashboard" element={
                        <ProtectedRoute>
                            <Dashboard />
                        </ProtectedRoute>
                    } />
                    <Route path="/profile" element={
                        <ProtectedRoute>
                            <Profile />
                        </ProtectedRoute>
                    } />
                </Routes>
            </BrowserRouter>
        </AuthProvider>
    );
}
```

## 🎯 Key Takeaways

1. **React Router** enables client-side routing
2. **Routes** define URL patterns and components
3. **Navigation** uses Link components
4. **Protected routes** require authentication
5. **Route parameters** pass dynamic data

---

**Next Lesson**: [Lesson 9: Mini Project - Movie Search App](./lesson9-mini-project-movie.md)
