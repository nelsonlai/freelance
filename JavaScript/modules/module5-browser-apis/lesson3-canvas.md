# Lesson 3: Canvas API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Create and configure HTML5 Canvas elements
- Draw basic shapes (lines, rectangles, circles)
- Apply colors, gradients, and patterns
- Handle mouse and touch events for drawing
- Create animations with requestAnimationFrame
- Implement drawing tools and brushes

## 📚 Canvas Basics

### Setting Up Canvas
```javascript
// Get canvas element and context
const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');

// Set canvas size
canvas.width = 800;
canvas.height = 600;
```

### Basic Drawing
```javascript
// Draw a line
ctx.beginPath();
ctx.moveTo(10, 10);
ctx.lineTo(100, 100);
ctx.stroke();

// Draw a rectangle
ctx.fillStyle = 'red';
ctx.fillRect(50, 50, 100, 100);

// Draw a circle
ctx.beginPath();
ctx.arc(200, 200, 50, 0, 2 * Math.PI);
ctx.fillStyle = 'blue';
ctx.fill();
```

## 🎯 Practice Exercises

### Exercise 1: Simple Drawing App
Create a basic drawing application:

**Solution:**
```javascript
class DrawingApp {
    constructor(canvasId) {
        this.canvas = document.getElementById(canvasId);
        this.ctx = this.canvas.getContext('2d');
        this.isDrawing = false;
        this.currentTool = 'pen';
        this.currentColor = '#000000';
        this.lineWidth = 2;
        
        this.setupCanvas();
        this.setupEventListeners();
    }
    
    setupCanvas() {
        this.canvas.width = 800;
        this.canvas.height = 600;
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
        this.canvas.addEventListener('touchstart', (e) => this.startDrawing(e.touches[0]));
        this.canvas.addEventListener('touchmove', (e) => {
            e.preventDefault();
            this.draw(e.touches[0]);
        });
        this.canvas.addEventListener('touchend', () => this.stopDrawing());
    }
    
    startDrawing(e) {
        this.isDrawing = true;
        const rect = this.canvas.getBoundingClientRect();
        this.lastX = e.clientX - rect.left;
        this.lastY = e.clientY - rect.top;
    }
    
    draw(e) {
        if (!this.isDrawing) return;
        
        const rect = this.canvas.getBoundingClientRect();
        const currentX = e.clientX - rect.left;
        const currentY = e.clientY - rect.top;
        
        this.ctx.strokeStyle = this.currentColor;
        this.ctx.lineWidth = this.lineWidth;
        
        this.ctx.beginPath();
        this.ctx.moveTo(this.lastX, this.lastY);
        this.ctx.lineTo(currentX, currentY);
        this.ctx.stroke();
        
        this.lastX = currentX;
        this.lastY = currentY;
    }
    
    stopDrawing() {
        this.isDrawing = false;
    }
    
    clearCanvas() {
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }
    
    setColor(color) {
        this.currentColor = color;
    }
    
    setLineWidth(width) {
        this.lineWidth = width;
    }
}

// Usage
const drawingApp = new DrawingApp('drawingCanvas');
```

## 🎯 Key Takeaways

1. **Canvas API** enables 2D graphics and animations
2. **Context** provides drawing methods and properties
3. **Event handling** enables interactive drawing
4. **Touch support** makes apps mobile-friendly
5. **Performance** considerations for smooth drawing

---

**Next Lesson**: [Lesson 4: FileReader API](./lesson4-filereader.md)
