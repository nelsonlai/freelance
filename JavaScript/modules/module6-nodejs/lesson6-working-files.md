# Lesson 6: Working with Files

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Read and write files synchronously and asynchronously
- Handle file uploads with multer
- Process different file types
- Implement file validation and security
- Create file management APIs
- Handle file errors gracefully

## 📚 File Operations

### Reading and Writing Files
```javascript
const fs = require('fs').promises;

// Async file operations
async function readFile(filePath) {
    try {
        const data = await fs.readFile(filePath, 'utf8');
        return data;
    } catch (error) {
        console.error('Error reading file:', error);
    }
}

async function writeFile(filePath, content) {
    try {
        await fs.writeFile(filePath, content, 'utf8');
        console.log('File written successfully');
    } catch (error) {
        console.error('Error writing file:', error);
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: File Management API
Create an API for file operations:

**Solution:**
```javascript
const express = require('express');
const multer = require('multer');
const fs = require('fs').promises;
const path = require('path');

const app = express();

// Configure multer for file uploads
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, 'uploads/');
    },
    filename: (req, file, cb) => {
        cb(null, Date.now() + '-' + file.originalname);
    }
});

const upload = multer({ 
    storage,
    limits: { fileSize: 5 * 1024 * 1024 }, // 5MB limit
    fileFilter: (req, file, cb) => {
        const allowedTypes = /jpeg|jpg|png|gif|pdf|txt/;
        const extname = allowedTypes.test(path.extname(file.originalname).toLowerCase());
        const mimetype = allowedTypes.test(file.mimetype);
        
        if (mimetype && extname) {
            return cb(null, true);
        } else {
            cb(new Error('Invalid file type'));
        }
    }
});

// Upload file
app.post('/api/upload', upload.single('file'), (req, res) => {
    if (!req.file) {
        return res.status(400).json({ error: 'No file uploaded' });
    }
    
    res.json({
        message: 'File uploaded successfully',
        file: {
            filename: req.file.filename,
            originalName: req.file.originalname,
            size: req.file.size,
            path: req.file.path
        }
    });
});

// List files
app.get('/api/files', async (req, res) => {
    try {
        const files = await fs.readdir('uploads/');
        res.json(files);
    } catch (error) {
        res.status(500).json({ error: 'Error reading files' });
    }
});

app.listen(3000, () => {
    console.log('File API running on http://localhost:3000');
});
```

## 🎯 Key Takeaways

1. **File operations** can be synchronous or asynchronous
2. **Multer** handles file uploads
3. **File validation** ensures security
4. **Error handling** prevents crashes
5. **File management** APIs provide file operations

---

**Next Lesson**: [Lesson 7: Database Connection](./lesson7-database.md)
