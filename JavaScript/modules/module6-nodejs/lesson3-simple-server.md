# Lesson 3: Creating a Simple Server

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Create HTTP servers with Node.js
- Handle GET and POST requests
- Parse request data and send responses
- Implement basic routing
- Handle different content types
- Create a simple web server

## 📚 HTTP Server Basics

### Basic Server
```javascript
const http = require('http');

const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end('<h1>Hello World!</h1>');
});

server.listen(3000, () => {
    console.log('Server running on http://localhost:3000');
});
```

### Handling Different Routes
```javascript
const http = require('http');
const url = require('url');

const server = http.createServer((req, res) => {
    const parsedUrl = url.parse(req.url, true);
    const path = parsedUrl.pathname;
    
    if (path === '/') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<h1>Home Page</h1>');
    } else if (path === '/about') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<h1>About Page</h1>');
    } else if (path === '/api/data') {
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ message: 'API Data' }));
    } else {
        res.writeHead(404, { 'Content-Type': 'text/html' });
        res.end('<h1>404 Not Found</h1>');
    }
});

server.listen(3000);
```

## 🎯 Practice Exercises

### Exercise 1: Simple Web Server
Create a basic web server with multiple routes:

**Solution:**
```javascript
const http = require('http');
const url = require('url');
const fs = require('fs');
const path = require('path');

class SimpleServer {
    constructor(port = 3000) {
        this.port = port;
        this.routes = new Map();
        this.setupDefaultRoutes();
    }
    
    setupDefaultRoutes() {
        this.routes.set('GET /', this.handleHome.bind(this));
        this.routes.set('GET /about', this.handleAbout.bind(this));
        this.routes.set('GET /api/time', this.handleApiTime.bind(this));
        this.routes.set('POST /api/echo', this.handleApiEcho.bind(this));
    }
    
    handleHome(req, res) {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(`
            <html>
                <head><title>Home</title></head>
                <body>
                    <h1>Welcome to Simple Server</h1>
                    <nav>
                        <a href="/">Home</a> | 
                        <a href="/about">About</a> | 
                        <a href="/api/time">API Time</a>
                    </nav>
                </body>
            </html>
        `);
    }
    
    handleAbout(req, res) {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(`
            <html>
                <head><title>About</title></head>
                <body>
                    <h1>About This Server</h1>
                    <p>This is a simple Node.js HTTP server.</p>
                    <a href="/">Back to Home</a>
                </body>
            </html>
        `);
    }
    
    handleApiTime(req, res) {
        const data = {
            timestamp: new Date().toISOString(),
            unix: Date.now()
        };
        
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(data));
    }
    
    handleApiEcho(req, res) {
        let body = '';
        
        req.on('data', chunk => {
            body += chunk.toString();
        });
        
        req.on('end', () => {
            try {
                const data = JSON.parse(body);
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ echo: data }));
            } catch (error) {
                res.writeHead(400, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ error: 'Invalid JSON' }));
            }
        });
    }
    
    handleRequest(req, res) {
        const method = req.method;
        const parsedUrl = url.parse(req.url, true);
        const path = parsedUrl.pathname;
        const routeKey = `${method} ${path}`;
        
        const handler = this.routes.get(routeKey);
        
        if (handler) {
            handler(req, res);
        } else {
            res.writeHead(404, { 'Content-Type': 'text/html' });
            res.end('<h1>404 Not Found</h1>');
        }
    }
    
    start() {
        const server = http.createServer((req, res) => {
            this.handleRequest(req, res);
        });
        
        server.listen(this.port, () => {
            console.log(`Server running on http://localhost:${this.port}`);
        });
        
        return server;
    }
}

// Usage
const server = new SimpleServer(3000);
server.start();
```

## 🎯 Key Takeaways

1. **HTTP module** creates web servers
2. **Request handling** processes different routes
3. **Response formatting** sends appropriate content
4. **Error handling** manages 404s and errors
5. **Content types** specify response format

---

**Next Lesson**: [Lesson 4: Express.js Basics](./lesson4-express-basics.md)
