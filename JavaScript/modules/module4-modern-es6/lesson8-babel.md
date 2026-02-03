# Lesson 8: Transpiling with Babel

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Configure Babel for JavaScript transpilation
- Use Babel presets and plugins
- Transpile modern JavaScript to older versions
- Set up Babel with different environments
- Understand polyfills and their usage

## 📚 Babel Configuration

### Basic Babel Setup
```javascript
// babel.config.js
module.exports = {
    presets: [
        ['@babel/preset-env', {
            targets: {
                browsers: ['> 1%', 'last 2 versions']
            }
        }]
    ],
    plugins: [
        '@babel/plugin-proposal-class-properties',
        '@babel/plugin-proposal-optional-chaining'
    ]
};
```

### Package.json Scripts
```json
{
    "scripts": {
        "build": "babel src -d dist",
        "watch": "babel src -d dist --watch"
    }
}
```

## 🎯 Key Takeaways

1. **Babel** transpiles modern JavaScript
2. **Presets** provide common configurations
3. **Plugins** add specific transformations
4. **Targets** specify browser compatibility

---

**Next Lesson**: [Lesson 9: Error Handling Patterns](./lesson9-error-patterns.md)
