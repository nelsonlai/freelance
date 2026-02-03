# Lesson 8: JWT Authentication

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Implement JWT authentication
- Create login and registration endpoints
- Protect routes with middleware
- Handle token expiration
- Implement password hashing
- Create secure authentication flow

## 📚 JWT Authentication

### Basic JWT Implementation
```javascript
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');

// Generate token
function generateToken(user) {
    return jwt.sign(
        { userId: user.id, email: user.email },
        process.env.JWT_SECRET,
        { expiresIn: '1h' }
    );
}

// Verify token middleware
function authenticateToken(req, res, next) {
    const token = req.headers['authorization']?.split(' ')[1];
    
    if (!token) {
        return res.status(401).json({ error: 'Access token required' });
    }
    
    jwt.verify(token, process.env.JWT_SECRET, (err, user) => {
        if (err) {
            return res.status(403).json({ error: 'Invalid token' });
        }
        req.user = user;
        next();
    });
}
```

## 🎯 Practice Exercises

### Exercise 1: Authentication System
Create a complete authentication system:

**Solution:**
```javascript
const express = require('express');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');
const mongoose = require('mongoose');

const app = express();
app.use(express.json());

// User Schema
const userSchema = new mongoose.Schema({
    email: { type: String, required: true, unique: true },
    password: { type: String, required: true },
    name: { type: String, required: true }
});

userSchema.pre('save', async function(next) {
    if (!this.isModified('password')) return next();
    this.password = await bcrypt.hash(this.password, 10);
    next();
});

const User = mongoose.model('User', userSchema);

// Auth middleware
const authenticateToken = (req, res, next) => {
    const token = req.headers['authorization']?.split(' ')[1];
    
    if (!token) {
        return res.status(401).json({ error: 'Access token required' });
    }
    
    jwt.verify(token, process.env.JWT_SECRET, (err, user) => {
        if (err) {
            return res.status(403).json({ error: 'Invalid token' });
        }
        req.user = user;
        next();
    });
};

// Register
app.post('/api/register', async (req, res) => {
    try {
        const { email, password, name } = req.body;
        const user = new User({ email, password, name });
        await user.save();
        
        const token = jwt.sign(
            { userId: user._id, email: user.email },
            process.env.JWT_SECRET,
            { expiresIn: '1h' }
        );
        
        res.status(201).json({ token, user: { id: user._id, email, name } });
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
});

// Login
app.post('/api/login', async (req, res) => {
    try {
        const { email, password } = req.body;
        const user = await User.findOne({ email });
        
        if (!user || !await bcrypt.compare(password, user.password)) {
            return res.status(401).json({ error: 'Invalid credentials' });
        }
        
        const token = jwt.sign(
            { userId: user._id, email: user.email },
            process.env.JWT_SECRET,
            { expiresIn: '1h' }
        );
        
        res.json({ token, user: { id: user._id, email: user.email, name: user.name } });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Protected route
app.get('/api/profile', authenticateToken, async (req, res) => {
    try {
        const user = await User.findById(req.user.userId).select('-password');
        res.json(user);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.listen(3000, () => {
    console.log('Auth API running on http://localhost:3000');
});
```

## 🎯 Key Takeaways

1. **JWT tokens** provide stateless authentication
2. **Password hashing** secures user data
3. **Middleware** protects routes
4. **Token expiration** enhances security
5. **Error handling** manages auth failures

---

**Next Lesson**: [Lesson 9: Error Handling in Express](./lesson9-error-handling.md)
