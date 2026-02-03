# Lesson 7: Database Connection

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Connect to MongoDB with Mongoose
- Define schemas and models
- Perform CRUD operations
- Handle database connections
- Implement data validation
- Use MongoDB queries and aggregation

## 📚 MongoDB with Mongoose

### Basic Connection
```javascript
const mongoose = require('mongoose');

mongoose.connect('mongodb://localhost:27017/myapp', {
    useNewUrlParser: true,
    useUnifiedTopology: true
});

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', () => {
    console.log('Connected to MongoDB');
});
```

### Schema and Model
```javascript
const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
    name: { type: String, required: true },
    email: { type: String, required: true, unique: true },
    age: { type: Number, min: 0, max: 120 }
});

const User = mongoose.model('User', userSchema);
```

## 🎯 Practice Exercises

### Exercise 1: User Management API
Create a complete user management system:

**Solution:**
```javascript
const express = require('express');
const mongoose = require('mongoose');

const app = express();
app.use(express.json());

// Connect to MongoDB
mongoose.connect('mongodb://localhost:27017/userapp');

// User Schema
const userSchema = new mongoose.Schema({
    name: { type: String, required: true },
    email: { type: String, required: true, unique: true },
    age: { type: Number, min: 0, max: 120 },
    createdAt: { type: Date, default: Date.now }
});

const User = mongoose.model('User', userSchema);

// Routes
app.get('/api/users', async (req, res) => {
    try {
        const users = await User.find();
        res.json(users);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.post('/api/users', async (req, res) => {
    try {
        const user = new User(req.body);
        await user.save();
        res.status(201).json(user);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
});

app.listen(3000, () => {
    console.log('User API running on http://localhost:3000');
});
```

## 🎯 Key Takeaways

1. **Mongoose** provides MongoDB object modeling
2. **Schemas** define data structure
3. **Models** create database collections
4. **CRUD operations** work with documents
5. **Validation** ensures data integrity

---

**Next Lesson**: [Lesson 8: JWT Authentication](./lesson8-jwt-auth.md)
