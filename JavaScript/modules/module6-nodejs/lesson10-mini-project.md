# Lesson 10: Mini Project - Simple Blog API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete blog API with Express.js
- Implement user authentication and authorization
- Create CRUD operations for posts and comments
- Handle file uploads for images
- Implement data validation and error handling
- Deploy the API to production

## 📚 Project Overview

We'll build a comprehensive blog API that includes:
- User registration and authentication
- Post creation, editing, and deletion
- Comment system
- Image uploads
- Data validation and error handling
- MongoDB integration

## 🏗️ Project Structure

```
blog-api/
├── package.json
├── .env
├── server.js
├── models/
│   ├── User.js
│   ├── Post.js
│   └── Comment.js
├── routes/
│   ├── auth.js
│   ├── posts.js
│   └── comments.js
├── middleware/
│   ├── auth.js
│   └── errorHandler.js
└── uploads/
```

## 📝 Package.json

```json
{
  "name": "blog-api",
  "version": "1.0.0",
  "description": "A simple blog API with authentication",
  "main": "server.js",
  "scripts": {
    "start": "node server.js",
    "dev": "nodemon server.js",
    "test": "jest"
  },
  "dependencies": {
    "express": "^4.18.0",
    "mongoose": "^6.0.0",
    "bcryptjs": "^2.4.3",
    "jsonwebtoken": "^9.0.0",
    "multer": "^1.4.5",
    "cors": "^2.8.5",
    "helmet": "^6.0.0",
    "morgan": "^1.10.0",
    "dotenv": "^16.0.0",
    "express-validator": "^6.14.0"
  },
  "devDependencies": {
    "nodemon": "^2.0.0",
    "jest": "^29.0.0"
  }
}
```

## 💻 Complete Implementation

### Server.js
```javascript
const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const path = require('path');
require('dotenv').config();

const app = express();

// Middleware
app.use(helmet());
app.use(cors());
app.use(morgan('combined'));
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true }));
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));

// Database connection
mongoose.connect(process.env.MONGODB_URI || 'mongodb://localhost:27017/blog-api', {
    useNewUrlParser: true,
    useUnifiedTopology: true
});

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', () => {
    console.log('Connected to MongoDB');
});

// Routes
app.use('/api/auth', require('./routes/auth'));
app.use('/api/posts', require('./routes/posts'));
app.use('/api/comments', require('./routes/comments'));

// Error handling middleware
app.use(require('./middleware/errorHandler'));

// 404 handler
app.use('*', (req, res) => {
    res.status(404).json({
        success: false,
        message: 'Route not found'
    });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
```

### Models/User.js
```javascript
const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');

const userSchema = new mongoose.Schema({
    name: {
        type: String,
        required: [true, 'Name is required'],
        trim: true,
        maxlength: [50, 'Name cannot exceed 50 characters']
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
    avatar: {
        type: String,
        default: ''
    },
    role: {
        type: String,
        enum: ['user', 'admin'],
        default: 'user'
    }
}, {
    timestamps: true
});

// Hash password before saving
userSchema.pre('save', async function(next) {
    if (!this.isModified('password')) return next();
    this.password = await bcrypt.hash(this.password, 12);
    next();
});

// Compare password method
userSchema.methods.comparePassword = async function(candidatePassword) {
    return await bcrypt.compare(candidatePassword, this.password);
};

// Remove password from JSON output
userSchema.methods.toJSON = function() {
    const user = this.toObject();
    delete user.password;
    return user;
};

module.exports = mongoose.model('User', userSchema);
```

### Models/Post.js
```javascript
const mongoose = require('mongoose');

const postSchema = new mongoose.Schema({
    title: {
        type: String,
        required: [true, 'Title is required'],
        trim: true,
        maxlength: [100, 'Title cannot exceed 100 characters']
    },
    content: {
        type: String,
        required: [true, 'Content is required'],
        minlength: [10, 'Content must be at least 10 characters']
    },
    excerpt: {
        type: String,
        maxlength: [200, 'Excerpt cannot exceed 200 characters']
    },
    image: {
        type: String,
        default: ''
    },
    author: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'User',
        required: true
    },
    tags: [{
        type: String,
        trim: true
    }],
    published: {
        type: Boolean,
        default: false
    },
    publishedAt: {
        type: Date
    },
    views: {
        type: Number,
        default: 0
    }
}, {
    timestamps: true
});

// Generate excerpt from content
postSchema.pre('save', function(next) {
    if (this.isModified('content') && !this.excerpt) {
        this.excerpt = this.content.substring(0, 200) + '...';
    }
    next();
});

// Increment views
postSchema.methods.incrementViews = function() {
    this.views += 1;
    return this.save();
};

module.exports = mongoose.model('Post', postSchema);
```

### Routes/auth.js
```javascript
const express = require('express');
const jwt = require('jsonwebtoken');
const { body, validationResult } = require('express-validator');
const User = require('../models/User');
const auth = require('../middleware/auth');

const router = express.Router();

// Generate JWT token
const generateToken = (userId) => {
    return jwt.sign({ userId }, process.env.JWT_SECRET, { expiresIn: '7d' });
};

// Register
router.post('/register', [
    body('name').trim().isLength({ min: 2, max: 50 }).withMessage('Name must be 2-50 characters'),
    body('email').isEmail().normalizeEmail().withMessage('Please provide a valid email'),
    body('password').isLength({ min: 6 }).withMessage('Password must be at least 6 characters')
], async (req, res) => {
    try {
        const errors = validationResult(req);
        if (!errors.isEmpty()) {
            return res.status(400).json({
                success: false,
                errors: errors.array()
            });
        }

        const { name, email, password } = req.body;

        // Check if user exists
        const existingUser = await User.findOne({ email });
        if (existingUser) {
            return res.status(400).json({
                success: false,
                message: 'User already exists'
            });
        }

        // Create user
        const user = new User({ name, email, password });
        await user.save();

        const token = generateToken(user._id);

        res.status(201).json({
            success: true,
            message: 'User registered successfully',
            token,
            user
        });
    } catch (error) {
        res.status(500).json({
            success: false,
            message: 'Server error',
            error: error.message
        });
    }
});

// Login
router.post('/login', [
    body('email').isEmail().normalizeEmail().withMessage('Please provide a valid email'),
    body('password').notEmpty().withMessage('Password is required')
], async (req, res) => {
    try {
        const errors = validationResult(req);
        if (!errors.isEmpty()) {
            return res.status(400).json({
                success: false,
                errors: errors.array()
            });
        }

        const { email, password } = req.body;

        // Find user
        const user = await User.findOne({ email });
        if (!user) {
            return res.status(401).json({
                success: false,
                message: 'Invalid credentials'
            });
        }

        // Check password
        const isMatch = await user.comparePassword(password);
        if (!isMatch) {
            return res.status(401).json({
                success: false,
                message: 'Invalid credentials'
            });
        }

        const token = generateToken(user._id);

        res.json({
            success: true,
            message: 'Login successful',
            token,
            user
        });
    } catch (error) {
        res.status(500).json({
            success: false,
            message: 'Server error',
            error: error.message
        });
    }
});

// Get current user
router.get('/me', auth, async (req, res) => {
    try {
        const user = await User.findById(req.user.userId);
        res.json({
            success: true,
            user
        });
    } catch (error) {
        res.status(500).json({
            success: false,
            message: 'Server error',
            error: error.message
        });
    }
});

module.exports = router;
```

## 🎯 Key Features Implemented

1. **User Authentication** - Registration, login, JWT tokens
2. **Post Management** - CRUD operations for blog posts
3. **Comment System** - Nested comments on posts
4. **Image Uploads** - Multer for handling file uploads
5. **Data Validation** - Express-validator for input validation
6. **Error Handling** - Comprehensive error management
7. **Security** - Helmet, CORS, password hashing
8. **Database** - MongoDB with Mongoose ODM

## 🎯 Key Takeaways

1. **Full-stack development** with Node.js and Express
2. **Authentication** with JWT and bcrypt
3. **Database design** with Mongoose schemas
4. **API design** following REST principles
5. **Security best practices** for production
6. **Error handling** for robust applications

## 🚀 Next Steps

Congratulations! You've completed Module 6. You now understand:

- Node.js fundamentals and server creation
- Package management with npm
- Express.js framework and middleware
- REST API design and routing
- File handling and uploads
- Database integration with MongoDB
- JWT authentication and security
- Error handling and validation
- Building complete backend applications

**Ready for Module 7: Frontend Frameworks!** 🎉

---

**Next Module**: [Module 7: Frontend Frameworks](../module7-frameworks/README.md)
