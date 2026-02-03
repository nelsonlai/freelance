# Lesson 6: Timers and Intervals

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use setTimeout for delayed execution
- Use setInterval for repeated execution
- Clear timers with clearTimeout and clearInterval
- Build countdown timers
- Create animation loops
- Implement polling mechanisms

## 📚 Timer Functions

### setTimeout
```javascript
// Execute code after delay
setTimeout(() => {
    console.log('This runs after 2 seconds');
}, 2000);

// Store timer ID for clearing
const timerId = setTimeout(() => {
    console.log('Delayed execution');
}, 1000);

clearTimeout(timerId); // Cancel the timer
```

### setInterval
```javascript
// Execute code repeatedly
setInterval(() => {
    console.log('This runs every second');
}, 1000);

// Store interval ID for clearing
const intervalId = setInterval(() => {
    console.log('Repeated execution');
}, 500);

clearInterval(intervalId); // Stop the interval
```

## 🎯 Practice Exercises

### Exercise 1: Countdown Timer
Create a countdown timer:

**Solution:**
```javascript
class CountdownTimer {
    constructor(duration, displayElement) {
        this.duration = duration;
        this.displayElement = displayElement;
        this.timeLeft = duration;
        this.intervalId = null;
    }
    
    start() {
        this.intervalId = setInterval(() => {
            this.timeLeft--;
            this.updateDisplay();
            
            if (this.timeLeft <= 0) {
                this.stop();
                this.onComplete();
            }
        }, 1000);
    }
    
    stop() {
        if (this.intervalId) {
            clearInterval(this.intervalId);
            this.intervalId = null;
        }
    }
    
    updateDisplay() {
        const minutes = Math.floor(this.timeLeft / 60);
        const seconds = this.timeLeft % 60;
        this.displayElement.textContent = `${minutes}:${seconds.toString().padStart(2, '0')}`;
    }
    
    onComplete() {
        this.displayElement.textContent = 'Time\'s up!';
        this.displayElement.style.color = 'red';
    }
}

// Usage
const display = document.getElementById('countdown');
const timer = new CountdownTimer(60, display); // 60 seconds
timer.start();
```

## 🎯 Key Takeaways

1. **setTimeout** delays execution
2. **setInterval** repeats execution
3. **clearTimeout/clearInterval** stop timers
4. **Timer IDs** allow control over timers
5. **Timers** enable animations and polling

---

**Next Lesson**: [Lesson 7: Date and Time](./lesson7-date-time.md)
