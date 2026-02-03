# Lesson 5: Clipboard API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Copy text to clipboard programmatically
- Read text from clipboard
- Handle clipboard permissions
- Copy images and other data types
- Implement copy/paste functionality
- Create clipboard-based features

## 📚 Clipboard API Basics

### Copying Text
```javascript
async function copyToClipboard(text) {
    try {
        await navigator.clipboard.writeText(text);
        console.log('Text copied to clipboard');
    } catch (error) {
        console.error('Failed to copy text:', error);
    }
}
```

### Reading Text
```javascript
async function readFromClipboard() {
    try {
        const text = await navigator.clipboard.readText();
        console.log('Clipboard text:', text);
        return text;
    } catch (error) {
        console.error('Failed to read clipboard:', error);
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: Clipboard Manager
Create a clipboard management utility:

**Solution:**
```javascript
class ClipboardManager {
    constructor() {
        this.clipboardHistory = [];
        this.maxHistorySize = 10;
    }
    
    async copyText(text) {
        try {
            await navigator.clipboard.writeText(text);
            this.addToHistory(text);
            return true;
        } catch (error) {
            console.error('Copy failed:', error);
            return false;
        }
    }
    
    async pasteText() {
        try {
            const text = await navigator.clipboard.readText();
            return text;
        } catch (error) {
            console.error('Paste failed:', error);
            return null;
        }
    }
    
    addToHistory(text) {
        if (text && !this.clipboardHistory.includes(text)) {
            this.clipboardHistory.unshift(text);
            if (this.clipboardHistory.length > this.maxHistorySize) {
                this.clipboardHistory.pop();
            }
        }
    }
    
    getHistory() {
        return this.clipboardHistory;
    }
    
    clearHistory() {
        this.clipboardHistory = [];
    }
}

// Usage
const clipboard = new ClipboardManager();
```

## 🎯 Key Takeaways

1. **Clipboard API** enables programmatic clipboard access
2. **Permissions** may be required for clipboard access
3. **Error handling** is important for clipboard operations
4. **Security** considerations for clipboard data
5. **User experience** improvements with clipboard features

---

**Next Lesson**: [Lesson 6: Speech Recognition API](./lesson6-speech-recognition.md)
