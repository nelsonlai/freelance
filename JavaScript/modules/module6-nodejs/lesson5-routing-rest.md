# Lesson 5: Routing and REST API Design

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Design RESTful API endpoints
- Implement CRUD operations
- Use route parameters and query strings
- Organize routes with Express Router
- Handle different HTTP methods
- Create API documentation

## 📚 REST API Design

### CRUD Operations
```javascript
const express = require('express');
const router = express.Router();

// GET /api/posts - Read all
router.get('/', (req, res) => {
    res.json(posts);
});

// GET /api/posts/:id - Read one
router.get('/:id', (req, res) => {
    const post = posts.find(p => p.id === parseInt(req.params.id));
    res.json(post);
});

// POST /api/posts - Create
router.post('/', (req, res) => {
    const post = { id: Date.now(), ...req.body };
    posts.push(post);
    res.status(201).json(post);
});

// PUT /api/posts/:id - Update
router.put('/:id', (req, res) => {
    const index = posts.findIndex(p => p.id === parseInt(req.params.id));
    posts[index] = { ...posts[index], ...req.body };
    res.json(posts[index]);
});

// DELETE /api/posts/:id - Delete
router.delete('/:id', (req, res) => {
    const index = posts.findIndex(p => p.id === parseInt(req.params.id));
    posts.splice(index, 1);
    res.status(204).send();
});
```

## 🎯 Practice Exercises

### Exercise 1: Blog API
Create a complete blog API with CRUD operations:

**Solution:**
```javascript
const express = require('express');
const app = express();

app.use(express.json());

let posts = [
    { id: 1, title: 'First Post', content: 'Hello World', author: 'Alice' },
    { id: 2, title: 'Second Post', content: 'Node.js is awesome', author: 'Bob' }
];

// GET /api/posts
app.get('/api/posts', (req, res) => {
    const { author, limit } = req.query;
    let filteredPosts = posts;
    
    if (author) {
        filteredPosts = posts.filter(p => p.author === author);
    }
    
    if (limit) {
        filteredPosts = filteredPosts.slice(0, parseInt(limit));
    }
    
    res.json(filteredPosts);
});

// POST /api/posts
app.post('/api/posts', (req, res) => {
    const { title, content, author } = req.body;
    
    if (!title || !content || !author) {
        return res.status(400).json({ error: 'Missing required fields' });
    }
    
    const post = {
        id: Date.now(),
        title,
        content,
        author,
        createdAt: new Date()
    };
    
    posts.push(post);
    res.status(201).json(post);
});

app.listen(3000, () => {
    console.log('Blog API running on http://localhost:3000');
});
```

## 🎯 Key Takeaways

1. **REST principles** guide API design
2. **HTTP methods** map to CRUD operations
3. **Route parameters** access dynamic values
4. **Query strings** filter and paginate data
5. **Status codes** communicate results

---

**Next Lesson**: [Lesson 6: Working with Files](./lesson6-working-files.md)
