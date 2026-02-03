# Lesson 2: Package Management

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use npm for package management
- Create and configure package.json
- Install and manage dependencies
- Use npm scripts for automation
- Understand semantic versioning
- Publish packages to npm registry

## 📚 Package.json Basics

### Creating package.json
```bash
npm init
# or
npm init -y  # Use defaults
```

### Basic package.json
```json
{
  "name": "my-node-app",
  "version": "1.0.0",
  "description": "A simple Node.js application",
  "main": "index.js",
  "scripts": {
    "start": "node index.js",
    "dev": "nodemon index.js",
    "test": "jest"
  },
  "keywords": ["node", "javascript"],
  "author": "Your Name",
  "license": "MIT",
  "dependencies": {
    "express": "^4.18.0"
  },
  "devDependencies": {
    "nodemon": "^2.0.0"
  }
}
```

## 📦 Installing Packages

### Install Commands
```bash
# Install production dependency
npm install express

# Install development dependency
npm install --save-dev nodemon

# Install specific version
npm install express@4.17.1

# Install globally
npm install -g nodemon

# Install all dependencies
npm install
```

## 🎯 Practice Exercises

### Exercise 1: Project Setup
Create a complete Node.js project setup:

**Solution:**
```bash
# Create project directory
mkdir my-node-project
cd my-node-project

# Initialize package.json
npm init -y

# Install dependencies
npm install express cors helmet morgan
npm install --save-dev nodemon jest

# Create basic file structure
mkdir src
mkdir tests
touch src/index.js
touch README.md
```

### Exercise 2: Package.json Configuration
Create a comprehensive package.json:

**Solution:**
```json
{
  "name": "my-node-project",
  "version": "1.0.0",
  "description": "A comprehensive Node.js project",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/index.js",
    "dev": "nodemon src/index.js",
    "test": "jest",
    "test:watch": "jest --watch",
    "lint": "eslint src/",
    "build": "echo 'Build process'",
    "clean": "rm -rf dist/"
  },
  "keywords": ["node", "express", "api"],
  "author": "Developer",
  "license": "MIT",
  "dependencies": {
    "express": "^4.18.0",
    "cors": "^2.8.5",
    "helmet": "^6.0.0",
    "morgan": "^1.10.0"
  },
  "devDependencies": {
    "nodemon": "^2.0.0",
    "jest": "^29.0.0",
    "eslint": "^8.0.0"
  },
  "engines": {
    "node": ">=14.0.0",
    "npm": ">=6.0.0"
  }
}
```

## 🎯 Key Takeaways

1. **npm** is the package manager for Node.js
2. **package.json** defines project metadata and dependencies
3. **Semantic versioning** controls package updates
4. **Scripts** automate common tasks
5. **Dependencies** vs **devDependencies**

---

**Next Lesson**: [Lesson 3: Creating a Simple Server](./lesson3-simple-server.md)
