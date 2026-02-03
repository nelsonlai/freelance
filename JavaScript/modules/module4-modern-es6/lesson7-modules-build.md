# Lesson 7: Modules with Webpack / Vite

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Set up Webpack for modern JavaScript development
- Configure Vite for fast development
- Bundle modules for production
- Use modern build tools effectively
- Optimize bundle size and performance

## 📚 Webpack Setup

### Basic Webpack Configuration
```javascript
// webpack.config.js
const path = require('path');

module.exports = {
    entry: './src/index.js',
    output: {
        filename: 'bundle.js',
        path: path.resolve(__dirname, 'dist')
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader'
                }
            }
        ]
    }
};
```

## 📚 Vite Setup

### Vite Configuration
```javascript
// vite.config.js
import { defineConfig } from 'vite';

export default defineConfig({
    build: {
        outDir: 'dist',
        sourcemap: true
    },
    server: {
        port: 3000,
        open: true
    }
});
```

## 🎯 Key Takeaways

1. **Webpack** is a powerful module bundler
2. **Vite** provides fast development experience
3. **Build tools** optimize code for production
4. **Configuration** customizes build behavior

---

**Next Lesson**: [Lesson 8: Transpiling with Babel](./lesson8-babel.md)
