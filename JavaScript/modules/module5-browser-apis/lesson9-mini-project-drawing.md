# Lesson 9: Mini Project - Drawing Pad App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete drawing pad application
- Integrate Canvas API with touch and mouse events
- Implement multiple drawing tools and brushes
- Add color picker and brush size controls
- Save and load drawings
- Create a responsive drawing interface

## 📚 Project Overview

We'll build a comprehensive drawing pad that includes:
- Multiple drawing tools (pen, brush, eraser)
- Color picker and brush size controls
- Undo/redo functionality
- Save and load drawings
- Touch and mouse support
- Responsive design

## 🏗️ Project Structure

```
drawing-pad/
├── index.html
├── style.css
└── script.js
```

## 📝 HTML Structure

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Drawing Pad</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>Drawing Pad</h1>
            <div class="toolbar">
                <div class="tool-group">
                    <button id="penTool" class="tool-btn active">Pen</button>
                    <button id="brushTool" class="tool-btn">Brush</button>
                    <button id="eraserTool" class="tool-btn">Eraser</button>
                </div>
                
                <div class="tool-group">
                    <input type="color" id="colorPicker" value="#000000">
                    <input type="range" id="brushSize" min="1" max="50" value="2">
                    <span id="brushSizeValue">2px</span>
                </div>
                
                <div class="tool-group">
                    <button id="undoBtn">Undo</button>
                    <button id="redoBtn">Redo</button>
                    <button id="clearBtn">Clear</button>
                </div>
                
                <div class="tool-group">
                    <button id="saveBtn">Save</button>
                    <button id="loadBtn">Load</button>
                    <input type="file" id="fileInput" accept=".json" style="display: none;">
                </div>
            </div>
        </header>
        
        <main>
            <canvas id="drawingCanvas"></canvas>
        </main>
    </div>
    
    <script src="script.js"></script>
</body>
</html>
```

## 💻 JavaScript Implementation

```javascript
class DrawingPad {
    constructor() {
        this.canvas = document.getElementById('drawingCanvas');
        this.ctx = this.canvas.getContext('2d');
        this.isDrawing = false;
        this.currentTool = 'pen';
        this.currentColor = '#000000';
        this.currentSize = 2;
        this.history = [];
        this.historyIndex = -1;
        
        this.setupCanvas();
        this.setupEventListeners();
        this.setupTools();
        this.saveState();
    }
    
    setupCanvas() {
        const rect = this.canvas.getBoundingClientRect();
        this.canvas.width = rect.width * window.devicePixelRatio;
        this.canvas.height = rect.height * window.devicePixelRatio;
        this.ctx.scale(window.devicePixelRatio, window.devicePixelRatio);
        
        this.canvas.style.width = rect.width + 'px';
        this.canvas.style.height = rect.height + 'px';
        
        this.ctx.lineCap = 'round';
        this.ctx.lineJoin = 'round';
    }
    
    setupEventListeners() {
        // Mouse events
        this.canvas.addEventListener('mousedown', (e) => this.startDrawing(e));
        this.canvas.addEventListener('mousemove', (e) => this.draw(e));
        this.canvas.addEventListener('mouseup', () => this.stopDrawing());
        this.canvas.addEventListener('mouseout', () => this.stopDrawing());
        
        // Touch events
        this.canvas.addEventListener('touchstart', (e) => {
            e.preventDefault();
            this.startDrawing(e.touches[0]);
        });
        this.canvas.addEventListener('touchmove', (e) => {
            e.preventDefault();
            this.draw(e.touches[0]);
        });
        this.canvas.addEventListener('touchend', (e) => {
            e.preventDefault();
            this.stopDrawing();
        });
        
        // Window resize
        window.addEventListener('resize', () => this.setupCanvas());
    }
    
    setupTools() {
        // Tool buttons
        document.getElementById('penTool').addEventListener('click', () => this.setTool('pen'));
        document.getElementById('brushTool').addEventListener('click', () => this.setTool('brush'));
        document.getElementById('eraserTool').addEventListener('click', () => this.setTool('eraser'));
        
        // Color picker
        document.getElementById('colorPicker').addEventListener('change', (e) => {
            this.currentColor = e.target.value;
        });
        
        // Brush size
        const brushSizeSlider = document.getElementById('brushSize');
        const brushSizeValue = document.getElementById('brushSizeValue');
        
        brushSizeSlider.addEventListener('input', (e) => {
            this.currentSize = parseInt(e.target.value);
            brushSizeValue.textContent = e.target.value + 'px';
        });
        
        // Action buttons
        document.getElementById('undoBtn').addEventListener('click', () => this.undo());
        document.getElementById('redoBtn').addEventListener('click', () => this.redo());
        document.getElementById('clearBtn').addEventListener('click', () => this.clear());
        document.getElementById('saveBtn').addEventListener('click', () => this.save());
        document.getElementById('loadBtn').addEventListener('click', () => this.load());
        
        // File input
        document.getElementById('fileInput').addEventListener('change', (e) => {
            this.loadFromFile(e.target.files[0]);
        });
    }
    
    setTool(tool) {
        this.currentTool = tool;
        
        // Update active tool button
        document.querySelectorAll('.tool-btn').forEach(btn => {
            btn.classList.remove('active');
        });
        document.getElementById(tool + 'Tool').classList.add('active');
    }
    
    startDrawing(e) {
        this.isDrawing = true;
        const rect = this.canvas.getBoundingClientRect();
        this.lastX = e.clientX - rect.left;
        this.lastY = e.clientY - rect.top;
        
        this.ctx.beginPath();
        this.ctx.moveTo(this.lastX, this.lastY);
    }
    
    draw(e) {
        if (!this.isDrawing) return;
        
        const rect = this.canvas.getBoundingClientRect();
        const currentX = e.clientX - rect.left;
        const currentY = e.clientY - rect.top;
        
        this.ctx.lineWidth = this.currentSize;
        
        switch(this.currentTool) {
            case 'pen':
                this.ctx.globalCompositeOperation = 'source-over';
                this.ctx.strokeStyle = this.currentColor;
                break;
            case 'brush':
                this.ctx.globalCompositeOperation = 'source-over';
                this.ctx.strokeStyle = this.currentColor;
                this.ctx.lineWidth = this.currentSize * 2;
                break;
            case 'eraser':
                this.ctx.globalCompositeOperation = 'destination-out';
                this.ctx.lineWidth = this.currentSize * 3;
                break;
        }
        
        this.ctx.lineTo(currentX, currentY);
        this.ctx.stroke();
        
        this.lastX = currentX;
        this.lastY = currentY;
    }
    
    stopDrawing() {
        if (this.isDrawing) {
            this.isDrawing = false;
            this.saveState();
        }
    }
    
    saveState() {
        this.historyIndex++;
        if (this.historyIndex < this.history.length) {
            this.history.length = this.historyIndex;
        }
        
        this.history.push(this.canvas.toDataURL());
        
        if (this.history.length > 20) {
            this.history.shift();
            this.historyIndex--;
        }
    }
    
    undo() {
        if (this.historyIndex > 0) {
            this.historyIndex--;
            this.restoreState();
        }
    }
    
    redo() {
        if (this.historyIndex < this.history.length - 1) {
            this.historyIndex++;
            this.restoreState();
        }
    }
    
    restoreState() {
        const img = new Image();
        img.onload = () => {
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            this.ctx.drawImage(img, 0, 0);
        };
        img.src = this.history[this.historyIndex];
    }
    
    clear() {
        if (confirm('Are you sure you want to clear the canvas?')) {
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            this.saveState();
        }
    }
    
    save() {
        const dataURL = this.canvas.toDataURL('image/png');
        const link = document.createElement('a');
        link.download = 'drawing.png';
        link.href = dataURL;
        link.click();
    }
    
    load() {
        document.getElementById('fileInput').click();
    }
    
    loadFromFile(file) {
        if (file && file.type === 'application/json') {
            const reader = new FileReader();
            reader.onload = (e) => {
                try {
                    const data = JSON.parse(e.target.result);
                    this.loadDrawing(data);
                } catch (error) {
                    console.error('Error loading file:', error);
                }
            };
            reader.readAsText(file);
        }
    }
    
    loadDrawing(data) {
        const img = new Image();
        img.onload = () => {
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            this.ctx.drawImage(img, 0, 0);
            this.saveState();
        };
        img.src = data.imageData;
    }
}

// Initialize the drawing pad
const drawingPad = new DrawingPad();
```

## 🎯 Key Features Implemented

1. **Multiple Drawing Tools** - Pen, brush, and eraser
2. **Color and Size Controls** - Color picker and brush size slider
3. **Undo/Redo** - History management with 20 levels
4. **Save/Load** - Export as PNG and load JSON files
5. **Touch Support** - Works on mobile devices
6. **Responsive Design** - Adapts to different screen sizes

## 🎯 Key Takeaways

1. **Canvas API** enables powerful drawing applications
2. **Event handling** for mouse and touch interactions
3. **State management** for undo/redo functionality
4. **File operations** for saving and loading drawings
5. **Responsive design** ensures cross-device compatibility

## 🚀 Next Steps

Congratulations! You've built a complete drawing pad application. In the next lesson, we'll create:

- **Voice Note App** - Speech recognition and text-to-speech
- **Voice input** - Converting speech to text
- **Audio playback** - Text-to-speech functionality
- **Note management** - Save and organize voice notes

---

**Next Lesson**: [Lesson 10: Mini Project - Voice Note App](./lesson10-mini-project-voice.md)
