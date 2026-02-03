# Lesson 4: FileReader API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Read files from user input
- Handle different file types (text, images, JSON)
- Preview images before upload
- Process file content asynchronously
- Handle file upload errors
- Create file validation and processing

## 📚 FileReader Basics

### Reading Text Files
```javascript
function readTextFile(file) {
    const reader = new FileReader();
    
    reader.onload = (event) => {
        console.log('File content:', event.target.result);
    };
    
    reader.onerror = (error) => {
        console.error('Error reading file:', error);
    };
    
    reader.readAsText(file);
}
```

### Reading Images
```javascript
function previewImage(file) {
    const reader = new FileReader();
    
    reader.onload = (event) => {
        const img = document.createElement('img');
        img.src = event.target.result;
        img.style.maxWidth = '300px';
        document.body.appendChild(img);
    };
    
    reader.readAsDataURL(file);
}
```

## 🎯 Practice Exercises

### Exercise 1: File Upload Handler
Create a comprehensive file upload handler:

**Solution:**
```javascript
class FileUploadHandler {
    constructor(inputId, previewId) {
        this.input = document.getElementById(inputId);
        this.preview = document.getElementById(previewId);
        this.allowedTypes = {
            image: ['image/jpeg', 'image/png', 'image/gif'],
            text: ['text/plain', 'text/csv'],
            json: ['application/json']
        };
        
        this.setupInput();
    }
    
    setupInput() {
        this.input.addEventListener('change', (e) => {
            const files = Array.from(e.target.files);
            files.forEach(file => this.handleFile(file));
        });
    }
    
    handleFile(file) {
        if (!this.validateFile(file)) {
            console.error('Invalid file type or size');
            return;
        }
        
        const fileType = this.getFileType(file.type);
        
        switch(fileType) {
            case 'image':
                this.previewImage(file);
                break;
            case 'text':
                this.readTextFile(file);
                break;
            case 'json':
                this.readJsonFile(file);
                break;
            default:
                console.log('Unsupported file type');
        }
    }
    
    validateFile(file) {
        const maxSize = 10 * 1024 * 1024; // 10MB
        if (file.size > maxSize) {
            console.error('File too large');
            return false;
        }
        
        const allowedTypes = Object.values(this.allowedTypes).flat();
        if (!allowedTypes.includes(file.type)) {
            console.error('File type not allowed');
            return false;
        }
        
        return true;
    }
    
    getFileType(mimeType) {
        for (const [type, mimes] of Object.entries(this.allowedTypes)) {
            if (mimes.includes(mimeType)) {
                return type;
            }
        }
        return 'unknown';
    }
    
    previewImage(file) {
        const reader = new FileReader();
        
        reader.onload = (event) => {
            const img = document.createElement('img');
            img.src = event.target.result;
            img.style.maxWidth = '300px';
            img.style.margin = '10px';
            
            const container = document.createElement('div');
            container.innerHTML = `
                <p><strong>${file.name}</strong> (${this.formatFileSize(file.size)})</p>
            `;
            container.appendChild(img);
            
            this.preview.appendChild(container);
        };
        
        reader.readAsDataURL(file);
    }
    
    readTextFile(file) {
        const reader = new FileReader();
        
        reader.onload = (event) => {
            const content = event.target.result;
            const container = document.createElement('div');
            container.innerHTML = `
                <h4>${file.name}</h4>
                <pre style="background: #f5f5f5; padding: 10px; border-radius: 5px;">${content}</pre>
            `;
            this.preview.appendChild(container);
        };
        
        reader.readAsText(file);
    }
    
    readJsonFile(file) {
        const reader = new FileReader();
        
        reader.onload = (event) => {
            try {
                const jsonData = JSON.parse(event.target.result);
                const container = document.createElement('div');
                container.innerHTML = `
                    <h4>${file.name}</h4>
                    <pre style="background: #f5f5f5; padding: 10px; border-radius: 5px;">${JSON.stringify(jsonData, null, 2)}</pre>
                `;
                this.preview.appendChild(container);
            } catch (error) {
                console.error('Invalid JSON file:', error);
            }
        };
        
        reader.readAsText(file);
    }
    
    formatFileSize(bytes) {
        if (bytes === 0) return '0 Bytes';
        
        const k = 1024;
        const sizes = ['Bytes', 'KB', 'MB', 'GB'];
        const i = Math.floor(Math.log(bytes) / Math.log(k));
        
        return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
    }
}

// Usage
const fileHandler = new FileUploadHandler('fileInput', 'filePreview');
```

## 🎯 Key Takeaways

1. **FileReader API** enables file processing in browsers
2. **File validation** ensures security and performance
3. **Different methods** for different file types
4. **Error handling** is crucial for file operations
5. **Preview functionality** improves user experience

---

**Next Lesson**: [Lesson 5: Clipboard API](./lesson5-clipboard.md)
