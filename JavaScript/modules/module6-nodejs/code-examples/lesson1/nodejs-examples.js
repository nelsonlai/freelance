// Lesson 1: Intro to Node.js Examples

console.log('Hello from Node.js!');
console.log('Node.js version:', process.version);
console.log('Platform:', process.platform);
console.log('Architecture:', process.arch);

console.log('\n=== File System Module ===');
const fs = require('fs');

// Create a test file
fs.writeFileSync('test.txt', 'Hello Node.js!');

// Read the file
const content = fs.readFileSync('test.txt', 'utf8');
console.log('File content:', content);

// Clean up
fs.unlinkSync('test.txt');

console.log('\n=== Path Module ===');
const path = require('path');

console.log('Current directory:', __dirname);
console.log('Current file:', __filename);
console.log('Path separator:', path.sep);
console.log('Join paths:', path.join(__dirname, 'data', 'file.txt'));
console.log('Resolve path:', path.resolve('data', 'file.txt'));
console.log('File extension:', path.extname('file.txt'));
console.log('Base name:', path.basename('/path/to/file.txt'));
console.log('Directory name:', path.dirname('/path/to/file.txt'));

console.log('\n=== OS Module ===');
const os = require('os');

console.log('Operating system:', os.platform());
console.log('Architecture:', os.arch());
console.log('CPU count:', os.cpus().length);
console.log('Total memory:', Math.round(os.totalmem() / 1024 / 1024 / 1024) + ' GB');
console.log('Free memory:', Math.round(os.freemem() / 1024 / 1024 / 1024) + ' GB');
console.log('Home directory:', os.homedir());
console.log('Temporary directory:', os.tmpdir());
console.log('Hostname:', os.hostname());

console.log('\n=== Event Loop Example ===');
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
