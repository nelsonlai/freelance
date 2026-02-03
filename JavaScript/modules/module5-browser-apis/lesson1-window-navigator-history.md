# Lesson 1: Window, Navigator, History APIs

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use Window API for browser window management
- Access device information with Navigator API
- Control browser history with History API
- Detect user agent and device capabilities
- Implement responsive design based on screen size
- Create navigation controls for single-page applications

## 📚 Window API

### Window Properties and Methods
```javascript
// Window dimensions
console.log('Window size:', window.innerWidth, 'x', window.innerHeight);
console.log('Screen size:', screen.width, 'x', screen.height);

// Window position
console.log('Window position:', window.screenX, window.screenY);

// Scroll position
console.log('Scroll position:', window.scrollX, window.scrollY);

// Window methods
window.scrollTo(0, 0); // Scroll to top
window.scrollBy(0, 100); // Scroll down 100px
window.resizeTo(800, 600); // Resize window (if allowed)
```

### Window Events
```javascript
// Resize event
window.addEventListener('resize', () => {
    console.log('Window resized:', window.innerWidth, 'x', window.innerHeight);
});

// Scroll event
window.addEventListener('scroll', () => {
    console.log('Scroll position:', window.scrollY);
});

// Before unload event
window.addEventListener('beforeunload', (event) => {
    event.preventDefault();
    event.returnValue = 'Are you sure you want to leave?';
});
```

## 🌐 Navigator API

### Device Information
```javascript
// User agent
console.log('User Agent:', navigator.userAgent);

// Platform
console.log('Platform:', navigator.platform);

// Language
console.log('Language:', navigator.language);
console.log('Languages:', navigator.languages);

// Online status
console.log('Online:', navigator.onLine);

// Cookie enabled
console.log('Cookies enabled:', navigator.cookieEnabled);

// Do not track
console.log('Do not track:', navigator.doNotTrack);
```

### Device Capabilities
```javascript
// Hardware concurrency
console.log('CPU cores:', navigator.hardwareConcurrency);

// Memory (if available)
if ('memory' in performance) {
    console.log('Device memory:', performance.memory);
}

// Connection information
if ('connection' in navigator) {
    const connection = navigator.connection;
    console.log('Connection type:', connection.effectiveType);
    console.log('Downlink:', connection.downlink);
    console.log('RTT:', connection.rtt);
}
```

## 📖 History API

### Basic History Operations
```javascript
// Get current history length
console.log('History length:', history.length);

// Navigate back
history.back();

// Navigate forward
history.forward();

// Navigate to specific position
history.go(-2); // Go back 2 pages
history.go(1);  // Go forward 1 page
```

### PushState and ReplaceState
```javascript
// Push new state
history.pushState({ page: 'home' }, 'Home', '/home');

// Replace current state
history.replaceState({ page: 'about' }, 'About', '/about');

// Listen for popstate events
window.addEventListener('popstate', (event) => {
    console.log('State:', event.state);
    console.log('URL:', window.location.href);
});
```

## 🎯 Practice Exercises

### Exercise 1: Responsive Design Helper
Create a utility that provides responsive design information:

**Solution:**
```javascript
class ResponsiveHelper {
    constructor() {
        this.breakpoints = {
            mobile: 768,
            tablet: 1024,
            desktop: 1200
        };
        
        this.currentBreakpoint = this.getCurrentBreakpoint();
        this.setupResizeListener();
    }
    
    getCurrentBreakpoint() {
        const width = window.innerWidth;
        
        if (width < this.breakpoints.mobile) return 'mobile';
        if (width < this.breakpoints.tablet) return 'tablet';
        if (width < this.breakpoints.desktop) return 'desktop';
        return 'large';
    }
    
    setupResizeListener() {
        window.addEventListener('resize', () => {
            const newBreakpoint = this.getCurrentBreakpoint();
            if (newBreakpoint !== this.currentBreakpoint) {
                const oldBreakpoint = this.currentBreakpoint;
                this.currentBreakpoint = newBreakpoint;
                this.onBreakpointChange(oldBreakpoint, newBreakpoint);
            }
        });
    }
    
    onBreakpointChange(oldBreakpoint, newBreakpoint) {
        console.log(`Breakpoint changed: ${oldBreakpoint} → ${newBreakpoint}`);
        
        // Dispatch custom event
        window.dispatchEvent(new CustomEvent('breakpointChange', {
            detail: { oldBreakpoint, newBreakpoint }
        }));
    }
    
    isMobile() {
        return this.currentBreakpoint === 'mobile';
    }
    
    isTablet() {
        return this.currentBreakpoint === 'tablet';
    }
    
    isDesktop() {
        return this.currentBreakpoint === 'desktop' || this.currentBreakpoint === 'large';
    }
}

// Usage
const responsive = new ResponsiveHelper();

window.addEventListener('breakpointChange', (event) => {
    const { oldBreakpoint, newBreakpoint } = event.detail;
    console.log(`Responsive change: ${oldBreakpoint} → ${newBreakpoint}`);
});
```

### Exercise 2: Single Page Application Router
Create a simple router using History API:

**Solution:**
```javascript
class SimpleRouter {
    constructor() {
        this.routes = new Map();
        this.currentRoute = null;
        this.setupRouter();
    }
    
    addRoute(path, handler) {
        this.routes.set(path, handler);
    }
    
    setupRouter() {
        // Handle initial route
        this.handleRoute(window.location.pathname);
        
        // Handle browser navigation
        window.addEventListener('popstate', (event) => {
            this.handleRoute(window.location.pathname);
        });
    }
    
    navigate(path, state = {}) {
        const handler = this.routes.get(path);
        
        if (handler) {
            history.pushState(state, '', path);
            this.handleRoute(path);
        } else {
            console.error(`Route not found: ${path}`);
        }
    }
    
    handleRoute(path) {
        const handler = this.routes.get(path);
        
        if (handler) {
            this.currentRoute = path;
            handler();
        } else {
            // Default route
            this.navigate('/');
        }
    }
    
    getCurrentRoute() {
        return this.currentRoute;
    }
}

// Usage
const router = new SimpleRouter();

router.addRoute('/', () => {
    document.getElementById('content').innerHTML = '<h1>Home Page</h1>';
});

router.addRoute('/about', () => {
    document.getElementById('content').innerHTML = '<h1>About Page</h1>';
});

router.addRoute('/contact', () => {
    document.getElementById('content').innerHTML = '<h1>Contact Page</h1>';
});

// Navigation buttons
document.getElementById('homeBtn').addEventListener('click', () => router.navigate('/'));
document.getElementById('aboutBtn').addEventListener('click', () => router.navigate('/about'));
document.getElementById('contactBtn').addEventListener('click', () => router.navigate('/contact'));
```

### Exercise 3: Device Information Display
Create a component that displays device information:

**Solution:**
```javascript
class DeviceInfo {
    constructor() {
        this.info = this.gatherDeviceInfo();
    }
    
    gatherDeviceInfo() {
        return {
            userAgent: navigator.userAgent,
            platform: navigator.platform,
            language: navigator.language,
            languages: navigator.languages,
            online: navigator.onLine,
            cookieEnabled: navigator.cookieEnabled,
            doNotTrack: navigator.doNotTrack,
            hardwareConcurrency: navigator.hardwareConcurrency,
            screenWidth: screen.width,
            screenHeight: screen.height,
            windowWidth: window.innerWidth,
            windowHeight: window.innerHeight,
            colorDepth: screen.colorDepth,
            pixelDepth: screen.pixelDepth,
            timezone: Intl.DateTimeFormat().resolvedOptions().timeZone
        };
    }
    
    displayInfo(containerId) {
        const container = document.getElementById(containerId);
        const infoHtml = Object.entries(this.info)
            .map(([key, value]) => `<div><strong>${key}:</strong> ${value}</div>`)
            .join('');
        
        container.innerHTML = `
            <h3>Device Information</h3>
            <div class="device-info">${infoHtml}</div>
        `;
    }
    
    isMobile() {
        return /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
    }
    
    isTouchDevice() {
        return 'ontouchstart' in window || navigator.maxTouchPoints > 0;
    }
    
    getConnectionInfo() {
        if ('connection' in navigator) {
            const connection = navigator.connection;
            return {
                effectiveType: connection.effectiveType,
                downlink: connection.downlink,
                rtt: connection.rtt,
                saveData: connection.saveData
            };
        }
        return null;
    }
}

// Usage
const deviceInfo = new DeviceInfo();
deviceInfo.displayInfo('deviceInfoContainer');

console.log('Is mobile:', deviceInfo.isMobile());
console.log('Is touch device:', deviceInfo.isTouchDevice());
console.log('Connection info:', deviceInfo.getConnectionInfo());
```

## 🚨 Common Mistakes to Avoid

### 1. Not Checking API Support
```javascript
// Wrong
const connection = navigator.connection;

// Right
if ('connection' in navigator) {
    const connection = navigator.connection;
    console.log(connection.effectiveType);
}
```

### 2. Not Handling Popstate Events
```javascript
// Wrong - only using pushState
history.pushState({ page: 'home' }, 'Home', '/home');

// Right - handling navigation
history.pushState({ page: 'home' }, 'Home', '/home');
window.addEventListener('popstate', (event) => {
    // Handle browser back/forward
});
```

### 3. Not Checking Online Status
```javascript
// Wrong - assuming always online
fetch('/api/data');

// Right - checking online status
if (navigator.onLine) {
    fetch('/api/data');
} else {
    console.log('Offline - using cached data');
}
```

## 🎯 Key Takeaways

1. **Window API** provides access to browser window properties
2. **Navigator API** gives device and browser information
3. **History API** enables programmatic navigation
4. **Always check** for API support before using
5. **Handle events** for responsive behavior
6. **Use responsibly** - respect user privacy

## 🚀 Next Steps

Great! You now understand browser APIs. In the next lesson, we'll learn about:

- **Geolocation API** - getting user location
- **Permission handling** - requesting location access
- **Location-based features** - maps and distance calculations

## 📚 Additional Resources

- [MDN Window API](https://developer.mozilla.org/en-US/docs/Web/API/Window)
- [MDN Navigator API](https://developer.mozilla.org/en-US/docs/Web/API/Navigator)
- [MDN History API](https://developer.mozilla.org/en-US/docs/Web/API/History)

## 🎉 Congratulations!

You've mastered browser APIs! You now understand:

- How to access window and device information
- How to control browser navigation
- How to create responsive applications
- How to build single-page applications

Practice with the exercises, and get ready for Lesson 2 where we'll learn about the Geolocation API!

---

**Next Lesson**: [Lesson 2: Geolocation API](./lesson2-geolocation.md)
