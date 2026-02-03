// Exercise 2: Single Page Application Router
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
