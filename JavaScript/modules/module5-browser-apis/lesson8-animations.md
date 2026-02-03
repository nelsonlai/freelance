# Lesson 8: Animations with requestAnimationFrame

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use requestAnimationFrame for smooth animations
- Create CSS and JavaScript animations
- Implement animation loops and timing
- Handle animation performance and optimization
- Create interactive animations
- Build animation libraries and utilities

## 📚 requestAnimationFrame Basics

### Basic Animation Loop
```javascript
function animate() {
    // Animation code here
    requestAnimationFrame(animate);
}

animate();
```

### Controlled Animation
```javascript
let animationId;
let startTime;

function animate(timestamp) {
    if (!startTime) startTime = timestamp;
    
    const elapsed = timestamp - startTime;
    
    // Animation logic based on elapsed time
    
    animationId = requestAnimationFrame(animate);
}

function startAnimation() {
    animationId = requestAnimationFrame(animate);
}

function stopAnimation() {
    cancelAnimationFrame(animationId);
}
```

## 🎯 Practice Exercises

### Exercise 1: Animation Controller
Create a comprehensive animation system:

**Solution:**
```javascript
class AnimationController {
    constructor() {
        this.animations = new Map();
        this.isRunning = false;
        this.lastTime = 0;
    }
    
    addAnimation(name, animationFunction) {
        this.animations.set(name, {
            function: animationFunction,
            active: false,
            startTime: 0
        });
    }
    
    startAnimation(name) {
        const animation = this.animations.get(name);
        if (animation) {
            animation.active = true;
            animation.startTime = performance.now();
            
            if (!this.isRunning) {
                this.isRunning = true;
                this.animate();
            }
        }
    }
    
    stopAnimation(name) {
        const animation = this.animations.get(name);
        if (animation) {
            animation.active = false;
        }
    }
    
    animate(timestamp = 0) {
        const deltaTime = timestamp - this.lastTime;
        this.lastTime = timestamp;
        
        let hasActiveAnimations = false;
        
        this.animations.forEach((animation, name) => {
            if (animation.active) {
                const elapsed = timestamp - animation.startTime;
                animation.function(elapsed, deltaTime);
                hasActiveAnimations = true;
            }
        });
        
        if (hasActiveAnimations) {
            requestAnimationFrame((time) => this.animate(time));
        } else {
            this.isRunning = false;
        }
    }
    
    stopAllAnimations() {
        this.animations.forEach(animation => {
            animation.active = false;
        });
        this.isRunning = false;
    }
}

// Usage
const animator = new AnimationController();

// Add a simple animation
animator.addAnimation('fadeIn', (elapsed, deltaTime) => {
    const element = document.getElementById('fadeElement');
    const opacity = Math.min(elapsed / 1000, 1); // 1 second fade
    element.style.opacity = opacity;
    
    if (opacity >= 1) {
        animator.stopAnimation('fadeIn');
    }
});

// Start the animation
animator.startAnimation('fadeIn');
```

## 🎯 Key Takeaways

1. **requestAnimationFrame** provides smooth animations
2. **Performance optimization** with proper timing
3. **Animation control** for start/stop functionality
4. **Delta time** for frame-rate independent animations
5. **Memory management** for animation cleanup

---

**Next Lesson**: [Lesson 9: Mini Project - Drawing Pad App](./lesson9-mini-project-drawing.md)
