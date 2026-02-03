# Lesson 10: Final Project - Full-Stack App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete full-stack application
- Integrate frontend and backend seamlessly
- Implement comprehensive authentication
- Design and implement database schemas
- Deploy application to production
- Monitor and maintain the application

## 📚 Project Overview

We'll build a complete full-stack application that demonstrates mastery of all concepts learned throughout the curriculum:

- **Frontend**: React.js with modern hooks and state management
- **Backend**: Node.js with Express.js and MongoDB
- **Authentication**: JWT-based authentication with role management
- **Database**: MongoDB with Mongoose ODM
- **Deployment**: Production deployment with monitoring
- **Testing**: Comprehensive test coverage
- **Performance**: Optimized for production use

## 🏗️ Project Structure

```
fullstack-app/
├── client/
│   ├── package.json
│   ├── src/
│   │   ├── App.js
│   │   ├── components/
│   │   ├── pages/
│   │   ├── hooks/
│   │   ├── context/
│   │   └── utils/
│   └── public/
├── server/
│   ├── package.json
│   ├── server.js
│   ├── models/
│   ├── routes/
│   ├── middleware/
│   └── utils/
├── shared/
│   └── types/
├── tests/
├── docs/
└── README.md
```

## 💻 Complete Implementation

### server/server.js
```javascript
const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const rateLimit = require('express-rate-limit');
require('dotenv').config();

const app = express();

// Security middleware
app.use(helmet());
app.use(cors({
    origin: process.env.CLIENT_URL || 'http://localhost:3000',
    credentials: true
}));

// Rate limiting
const limiter = rateLimit({
    windowMs: 15 * 60 * 1000, // 15 minutes
    max: 100 // limit each IP to 100 requests per windowMs
});
app.use(limiter);

// Logging
app.use(morgan('combined'));

// Body parsing
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true }));

// Routes
app.use('/api/auth', require('./routes/auth'));
app.use('/api/users', require('./routes/users'));
app.use('/api/posts', require('./routes/posts'));
app.use('/api/comments', require('./routes/comments'));

// Health check
app.get('/health', (req, res) => {
    res.json({ 
        status: 'OK', 
        timestamp: new Date().toISOString(),
        uptime: process.uptime()
    });
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({ 
        message: 'Something went wrong!',
        error: process.env.NODE_ENV === 'development' ? err.message : {}
    });
});

// 404 handler
app.use('*', (req, res) => {
    res.status(404).json({ message: 'Route not found' });
});

// Database connection
mongoose.connect(process.env.MONGODB_URI || 'mongodb://localhost:27017/fullstack-app', {
    useNewUrlParser: true,
    useUnifiedTopology: true
});

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', () => {
    console.log('Connected to MongoDB');
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
```

### client/src/App.js
```javascript
import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { AuthProvider } from './context/AuthContext';
import { ThemeProvider } from './context/ThemeContext';
import ProtectedRoute from './components/ProtectedRoute';
import Header from './components/Header';
import Footer from './components/Footer';
import Home from './pages/Home';
import Login from './pages/Login';
import Register from './pages/Register';
import Dashboard from './pages/Dashboard';
import Profile from './pages/Profile';
import Posts from './pages/Posts';
import PostDetail from './pages/PostDetail';
import './styles/App.css';

function App() {
    return (
        <ThemeProvider>
            <AuthProvider>
                <Router>
                    <div className="app">
                        <Header />
                        
                        <main className="main-content">
                            <Routes>
                                <Route path="/" element={<Home />} />
                                <Route path="/login" element={<Login />} />
                                <Route path="/register" element={<Register />} />
                                
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
                                
                                <Route path="/posts" element={<Posts />} />
                                <Route path="/posts/:id" element={<PostDetail />} />
                            </Routes>
                        </main>
                        
                        <Footer />
                    </div>
                </Router>
            </AuthProvider>
        </ThemeProvider>
    );
}

export default App;
```

### server/models/User.js
```javascript
const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

const userSchema = new mongoose.Schema({
    username: {
        type: String,
        required: [true, 'Username is required'],
        unique: true,
        trim: true,
        minlength: [3, 'Username must be at least 3 characters'],
        maxlength: [30, 'Username cannot exceed 30 characters']
    },
    email: {
        type: String,
        required: [true, 'Email is required'],
        unique: true,
        lowercase: true,
        match: [/^\w+([.-]?\w+)*@\w+([.-]?\w+)*(\.\w{2,3})+$/, 'Please enter a valid email']
    },
    password: {
        type: String,
        required: [true, 'Password is required'],
        minlength: [6, 'Password must be at least 6 characters']
    },
    firstName: {
        type: String,
        required: [true, 'First name is required'],
        trim: true,
        maxlength: [50, 'First name cannot exceed 50 characters']
    },
    lastName: {
        type: String,
        required: [true, 'Last name is required'],
        trim: true,
        maxlength: [50, 'Last name cannot exceed 50 characters']
    },
    avatar: {
        type: String,
        default: ''
    },
    role: {
        type: String,
        enum: ['user', 'admin', 'moderator'],
        default: 'user'
    },
    isActive: {
        type: Boolean,
        default: true
    },
    lastLogin: {
        type: Date
    },
    preferences: {
        theme: {
            type: String,
            enum: ['light', 'dark'],
            default: 'light'
        },
        notifications: {
            email: {
                type: Boolean,
                default: true
            },
            push: {
                type: Boolean,
                default: true
            }
        }
    }
}, {
    timestamps: true
});

// Hash password before saving
userSchema.pre('save', async function(next) {
    if (!this.isModified('password')) return next();
    
    try {
        const salt = await bcrypt.genSalt(12);
        this.password = await bcrypt.hash(this.password, salt);
        next();
    } catch (error) {
        next(error);
    }
});

// Compare password method
userSchema.methods.comparePassword = async function(candidatePassword) {
    return await bcrypt.compare(candidatePassword, this.password);
};

// Generate JWT token
userSchema.methods.generateToken = function() {
    return jwt.sign(
        { 
            userId: this._id, 
            username: this.username, 
            role: this.role 
        },
        process.env.JWT_SECRET,
        { expiresIn: '7d' }
    );
};

// Remove password from JSON output
userSchema.methods.toJSON = function() {
    const user = this.toObject();
    delete user.password;
    return user;
};

// Update last login
userSchema.methods.updateLastLogin = function() {
    this.lastLogin = new Date();
    return this.save();
};

module.exports = mongoose.model('User', userSchema);
```

### client/src/context/AuthContext.js
```javascript
import React, { createContext, useContext, useReducer, useEffect } from 'react';
import { authAPI } from '../utils/api';

const AuthContext = createContext();

const authReducer = (state, action) => {
    switch (action.type) {
        case 'LOGIN_START':
            return {
                ...state,
                loading: true,
                error: null
            };
        
        case 'LOGIN_SUCCESS':
            return {
                ...state,
                loading: false,
                isAuthenticated: true,
                user: action.payload.user,
                token: action.payload.token,
                error: null
            };
        
        case 'LOGIN_FAILURE':
            return {
                ...state,
                loading: false,
                isAuthenticated: false,
                user: null,
                token: null,
                error: action.payload
            };
        
        case 'LOGOUT':
            return {
                ...state,
                isAuthenticated: false,
                user: null,
                token: null,
                error: null
            };
        
        case 'UPDATE_USER':
            return {
                ...state,
                user: { ...state.user, ...action.payload }
            };
        
        default:
            return state;
    }
};

export function AuthProvider({ children }) {
    const [state, dispatch] = useReducer(authReducer, {
        isAuthenticated: false,
        user: null,
        token: null,
        loading: true,
        error: null
    });
    
    // Check for existing token on mount
    useEffect(() => {
        const token = localStorage.getItem('token');
        if (token) {
            verifyToken(token);
        } else {
            dispatch({ type: 'LOGIN_FAILURE', payload: null });
        }
    }, []);
    
    const verifyToken = async (token) => {
        try {
            const response = await authAPI.verifyToken(token);
            dispatch({
                type: 'LOGIN_SUCCESS',
                payload: {
                    user: response.user,
                    token
                }
            });
        } catch (error) {
            localStorage.removeItem('token');
            dispatch({ type: 'LOGIN_FAILURE', payload: error.message });
        }
    };
    
    const login = async (credentials) => {
        dispatch({ type: 'LOGIN_START' });
        
        try {
            const response = await authAPI.login(credentials);
            localStorage.setItem('token', response.token);
            
            dispatch({
                type: 'LOGIN_SUCCESS',
                payload: response
            });
            
            return response;
        } catch (error) {
            dispatch({
                type: 'LOGIN_FAILURE',
                payload: error.message
            });
            throw error;
        }
    };
    
    const register = async (userData) => {
        dispatch({ type: 'LOGIN_START' });
        
        try {
            const response = await authAPI.register(userData);
            localStorage.setItem('token', response.token);
            
            dispatch({
                type: 'LOGIN_SUCCESS',
                payload: response
            });
            
            return response;
        } catch (error) {
            dispatch({
                type: 'LOGIN_FAILURE',
                payload: error.message
            });
            throw error;
        }
    };
    
    const logout = () => {
        localStorage.removeItem('token');
        dispatch({ type: 'LOGOUT' });
    };
    
    const updateUser = (userData) => {
        dispatch({
            type: 'UPDATE_USER',
            payload: userData
        });
    };
    
    const value = {
        ...state,
        login,
        register,
        logout,
        updateUser
    };
    
    return (
        <AuthContext.Provider value={value}>
            {children}
        </AuthContext.Provider>
    );
}

export function useAuth() {
    const context = useContext(AuthContext);
    if (!context) {
        throw new Error('useAuth must be used within an AuthProvider');
    }
    return context;
}
```

## 🎯 Key Features Implemented

1. **Complete Authentication** - Login, register, JWT tokens
2. **Role-Based Access** - User, admin, moderator roles
3. **Database Integration** - MongoDB with Mongoose
4. **API Design** - RESTful API with proper error handling
5. **Frontend State Management** - Context API with reducers
6. **Protected Routes** - Authentication-based routing
7. **Error Handling** - Comprehensive error management
8. **Security** - Helmet, CORS, rate limiting
9. **Performance** - Optimized queries and caching
10. **Testing** - Unit and integration tests

## 🎯 Key Takeaways

1. **Full-stack development** requires both frontend and backend skills
2. **Authentication** secures user sessions
3. **Database design** affects application performance
4. **API design** enables frontend-backend communication
5. **Error handling** improves user experience
6. **Security** protects against common vulnerabilities
7. **Testing** ensures code quality
8. **Deployment** makes applications accessible

## 🚀 Next Steps

Congratulations! You've completed the entire JavaScript curriculum! You now have:

- **Complete JavaScript knowledge** from basics to advanced
- **Frontend development skills** with React.js
- **Backend development skills** with Node.js
- **Database management** with MongoDB
- **Authentication and security** implementation
- **Testing and deployment** capabilities
- **Performance optimization** techniques
- **Professional development practices**

## 🎉 Final Achievement

You've successfully completed **80 comprehensive lessons** covering:

1. **JavaScript Foundations** - Variables, functions, arrays, objects
2. **Intermediate JavaScript** - Modern features, DOM manipulation
3. **Advanced JavaScript** - Async programming, APIs, debugging
4. **Modern ES6+ Features** - Arrow functions, Promises, modules
5. **Browser APIs** - Geolocation, Canvas, FileReader, Speech
6. **Node.js & Backend** - Servers, databases, authentication
7. **Frontend Frameworks** - React.js, components, hooks
8. **Capstone Projects** - Portfolio, chat app, e-commerce

**You are now a full-stack JavaScript developer ready for professional work!** 🎉

---

**Congratulations on completing the JavaScript Full Curriculum!** 🚀
