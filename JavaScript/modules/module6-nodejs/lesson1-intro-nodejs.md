# Lesson 1: Intro to Node.js

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand what Node.js is and how it works
- Set up Node.js development environment
- Use Node.js modules and require statements
- Work with built-in modules (fs, path, os)
- Run JavaScript files from the terminal
- Understand the Node.js event loop

## 📚 What is Node.js?

**Node.js** is a JavaScript runtime built on Chrome's V8 JavaScript engine. It allows you to run JavaScript on the server side, outside of web browsers.

### Key Features
- **Single-threaded** - Uses event loop for non-blocking operations
- **Event-driven** - Asynchronous programming model
- **Cross-platform** - Runs on Windows, macOS, Linux
- **NPM ecosystem** - Largest package registry in the world

## 🛠️ Setting Up Node.js

### Installation
1. Go to [nodejs.org](https://nodejs.org)
2. Download the LTS (Long Term Support) version
3. Install following the installer instructions
4. Verify installation: `node --version` and `npm --version`

### First Node.js Program
```javascript
// hello.js
console.log('Hello from Node.js!');
console.log('Node.js version:', process.version);
console.log('Platform:', process.platform);
console.log('Architecture:', process.arch);
```

Run with: `node hello.js`

## 📦 Node.js Modules

### Built-in Modules
```javascript
// File System module
const fs = require('fs');

// Read a file
fs.readFile('data.txt', 'utf8', (err, data) => {
    if (err) {
        console.error('Error reading file:', err);
        return;
    }
    console.log('File content:', data);
});

// Write a file
fs.writeFile('output.txt', 'Hello Node.js!', (err) => {
    if (err) {
        console.error('Error writing file:', err);
        return;
    }
    console.log('File written successfully');
});
```

### Path Module
```javascript
const path = require('path');

console.log('Current directory:', __dirname);
console.log('Current file:', __filename);
console.log('Path separator:', path.sep);
console.log('Join paths:', path.join(__dirname, 'data', 'file.txt'));
console.log('Resolve path:', path.resolve('data', 'file.txt'));
console.log('File extension:', path.extname('file.txt'));
console.log('Base name:', path.basename('/path/to/file.txt'));
console.log('Directory name:', path.dirname('/path/to/file.txt'));
```

### OS Module
```javascript
const os = require('os');

console.log('Operating system:', os.platform());
console.log('Architecture:', os.arch());
console.log('CPU info:', os.cpus());
console.log('Total memory:', os.totalmem());
console.log('Free memory:', os.freemem());
console.log('Home directory:', os.homedir());
console.log('Temporary directory:', os.tmpdir());
console.log('Hostname:', os.hostname());
console.log('Network interfaces:', os.networkInterfaces());
```

## 🔄 Event Loop and Asynchronous Programming

### Understanding the Event Loop
```javascript
console.log('1. Start');

setTimeout(() => {
    console.log('2. Timeout callback');
}, 0);

setImmediate(() => {
    console.log('3. Immediate callback');
});

process.nextTick(() => {
    console.log('4. Next tick callback');
});

console.log('5. End');

// Output order:
// 1. Start
// 5. End
// 4. Next tick callback
// 2. Timeout callback
// 3. Immediate callback
```

### Asynchronous File Operations
```javascript
const fs = require('fs');

console.log('Reading files...');

// Read multiple files asynchronously
fs.readFile('file1.txt', 'utf8', (err1, data1) => {
    if (err1) {
        console.error('Error reading file1:', err1);
        return;
    }
    console.log('File1 content:', data1);
});

fs.readFile('file2.txt', 'utf8', (err2, data2) => {
    if (err2) {
        console.error('Error reading file2:', err2);
        return;
    }
    console.log('File2 content:', data2);
});

console.log('Files are being read...');
```

## 🎯 Practice Exercises

### Exercise 1: File System Utility
Create a utility that provides file system information:

**Solution:**
```javascript
const fs = require('fs');
const path = require('path');
const os = require('os');

class FileSystemUtility {
    constructor() {
        this.currentDir = process.cwd();
    }
    
    getDirectoryInfo(dirPath = this.currentDir) {
        try {
            const stats = fs.statSync(dirPath);
            
            if (!stats.isDirectory()) {
                throw new Error('Path is not a directory');
            }
            
            const files = fs.readdirSync(dirPath);
            const fileInfo = files.map(file => {
                const filePath = path.join(dirPath, file);
                const fileStats = fs.statSync(filePath);
                
                return {
                    name: file,
                    type: fileStats.isDirectory() ? 'directory' : 'file',
                    size: fileStats.size,
                    modified: fileStats.mtime,
                    created: fileStats.birthtime
                };
            });
            
            return {
                path: dirPath,
                totalFiles: fileInfo.filter(f => f.type === 'file').length,
                totalDirectories: fileInfo.filter(f => f.type === 'directory').length,
                files: fileInfo
            };
        } catch (error) {
            console.error('Error reading directory:', error.message);
            return null;
        }
    }
    
    createFile(filePath, content) {
        try {
            fs.writeFileSync(filePath, content);
            console.log(`File created: ${filePath}`);
            return true;
        } catch (error) {
            console.error('Error creating file:', error.message);
            return false;
        }
    }
    
    readFile(filePath) {
        try {
            const content = fs.readFileSync(filePath, 'utf8');
            return content;
        } catch (error) {
            console.error('Error reading file:', error.message);
            return null;
        }
    }
    
    deleteFile(filePath) {
        try {
            fs.unlinkSync(filePath);
            console.log(`File deleted: ${filePath}`);
            return true;
        } catch (error) {
            console.error('Error deleting file:', error.message);
            return false;
        }
    }
    
    getSystemInfo() {
        return {
            platform: os.platform(),
            architecture: os.arch(),
            totalMemory: this.formatBytes(os.totalmem()),
            freeMemory: this.formatBytes(os.freemem()),
            cpuCount: os.cpus().length,
            uptime: this.formatUptime(os.uptime()),
            homeDir: os.homedir(),
            tempDir: os.tmpdir()
        };
    }
    
    formatBytes(bytes) {
        const sizes = ['Bytes', 'KB', 'MB', 'GB', 'TB'];
        if (bytes === 0) return '0 Bytes';
        const i = Math.floor(Math.log(bytes) / Math.log(1024));
        return Math.round(bytes / Math.pow(1024, i) * 100) / 100 + ' ' + sizes[i];
    }
    
    formatUptime(seconds) {
        const days = Math.floor(seconds / 86400);
        const hours = Math.floor((seconds % 86400) / 3600);
        const minutes = Math.floor((seconds % 3600) / 60);
        const secs = Math.floor(seconds % 60);
        
        return `${days}d ${hours}h ${minutes}m ${secs}s`;
    }
}

// Usage
const fsUtil = new FileSystemUtility();

console.log('Current directory info:');
console.log(fsUtil.getDirectoryInfo());

console.log('\nSystem info:');
console.log(fsUtil.getSystemInfo());

// Create a test file
fsUtil.createFile('test.txt', 'Hello Node.js!');

// Read the test file
const content = fsUtil.readFile('test.txt');
console.log('\nTest file content:', content);

// Clean up
fsUtil.deleteFile('test.txt');
```

### Exercise 2: Process Monitor
Create a simple process monitor:

**Solution:**
```javascript
const os = require('os');

class ProcessMonitor {
    constructor() {
        this.startTime = Date.now();
        this.memoryUsage = process.memoryUsage();
    }
    
    getProcessInfo() {
        const uptime = Date.now() - this.startTime;
        const currentMemory = process.memoryUsage();
        
        return {
            pid: process.pid,
            platform: process.platform,
            nodeVersion: process.version,
            uptime: this.formatUptime(uptime),
            memory: {
                rss: this.formatBytes(currentMemory.rss),
                heapTotal: this.formatBytes(currentMemory.heapTotal),
                heapUsed: this.formatBytes(currentMemory.heapUsed),
                external: this.formatBytes(currentMemory.external)
            },
            cpu: {
                count: os.cpus().length,
                model: os.cpus()[0].model,
                speed: os.cpus()[0].speed + ' MHz'
            },
            system: {
                totalMemory: this.formatBytes(os.totalmem()),
                freeMemory: this.formatBytes(os.freemem()),
                loadAverage: os.loadavg()
            }
        };
    }
    
    formatBytes(bytes) {
        const sizes = ['Bytes', 'KB', 'MB', 'GB'];
        if (bytes === 0) return '0 Bytes';
        const i = Math.floor(Math.log(bytes) / Math.log(1024));
        return Math.round(bytes / Math.pow(1024, i) * 100) / 100 + ' ' + sizes[i];
    }
    
    formatUptime(milliseconds) {
        const seconds = Math.floor(milliseconds / 1000);
        const minutes = Math.floor(seconds / 60);
        const hours = Math.floor(minutes / 60);
        const days = Math.floor(hours / 24);
        
        return `${days}d ${hours % 24}h ${minutes % 60}m ${seconds % 60}s`;
    }
    
    startMonitoring(interval = 5000) {
        console.log('Starting process monitoring...');
        
        const monitor = setInterval(() => {
            const info = this.getProcessInfo();
            console.log('\n=== Process Monitor ===');
            console.log('PID:', info.pid);
            console.log('Uptime:', info.uptime);
            console.log('Memory Usage:', info.memory.heapUsed);
            console.log('System Load:', info.system.loadAverage[0].toFixed(2));
        }, interval);
        
        // Stop monitoring after 30 seconds
        setTimeout(() => {
            clearInterval(monitor);
            console.log('\nMonitoring stopped.');
        }, 30000);
    }
}

// Usage
const monitor = new ProcessMonitor();
console.log('Process Info:', monitor.getProcessInfo());

// Start monitoring
monitor.startMonitoring(2000);
```

## 🚨 Common Mistakes to Avoid

### 1. Blocking the Event Loop
```javascript
// Wrong - blocking operation
const fs = require('fs');
const data = fs.readFileSync('large-file.txt', 'utf8'); // Blocks!

// Right - non-blocking operation
fs.readFile('large-file.txt', 'utf8', (err, data) => {
    if (err) throw err;
    console.log(data);
});
```

### 2. Not Handling Errors
```javascript
// Wrong - no error handling
fs.readFile('file.txt', 'utf8', (err, data) => {
    console.log(data); // Error if file doesn't exist
});

// Right - proper error handling
fs.readFile('file.txt', 'utf8', (err, data) => {
    if (err) {
        console.error('Error reading file:', err.message);
        return;
    }
    console.log(data);
});
```

### 3. Using Synchronous Methods in Production
```javascript
// Wrong - synchronous in production
const data = fs.readFileSync('file.txt', 'utf8');

// Right - asynchronous for production
fs.readFile('file.txt', 'utf8', (err, data) => {
    // Handle result
});
```

## 🎯 Key Takeaways

1. **Node.js** runs JavaScript on the server
2. **Modules** provide built-in functionality
3. **Event loop** enables non-blocking operations
4. **Asynchronous programming** is fundamental
5. **Error handling** is crucial for robust applications
6. **File system** operations are common in Node.js

## 🚀 Next Steps

Great! You now understand Node.js basics. In the next lesson, we'll learn about:

- **Package management** with npm
- **package.json** configuration
- **Installing dependencies** and managing packages
- **Scripts** and automation

## 📚 Additional Resources

- [Node.js Official Documentation](https://nodejs.org/docs/)
- [Node.js API Documentation](https://nodejs.org/api/)
- [npm Documentation](https://docs.npmjs.com/)

## 🎉 Congratulations!

You've mastered Node.js basics! You now understand:

- How Node.js works and its event loop
- Built-in modules and their usage
- Asynchronous programming patterns
- File system operations
- Process monitoring and system information

Practice with the exercises, and get ready for Lesson 2 where we'll learn about package management!

---

**Next Lesson**: [Lesson 2: Package Management](./lesson2-package-management.md)
