// Exercise 1: File System Utility
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
