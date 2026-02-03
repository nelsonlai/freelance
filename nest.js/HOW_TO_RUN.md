# How to Run Each Level

This guide explains how to run the code examples for each level.

## ⚠️ Important

Each level's code is **self-contained** and should be run from its own directory. Do NOT try to run them from the root directory unless you understand the project structure.

---

## 🟢 Beginner Level

### Location
`01-beginner/demo-beginner/`

### Setup
```bash
cd 01-beginner/demo-beginner
npm install
```

### Run
```bash
npm run start:dev
```

### Access
- Backend API: `http://localhost:3000`
- Frontend UI: `http://localhost:3000/`

---

## 🟡 Intermediate Level

### Location
`02-intermediate/code/`

### Setup
```bash
cd 02-intermediate/code
npm install
```

### Run
```bash
npm run start:dev
```

### Access
- Backend API: `http://localhost:3000`
- Test with: `curl http://localhost:3000/`

### Authentication
Use any token for testing:
```bash
curl http://localhost:3000/users \
  -H "Authorization: Bearer valid-token"
```

---

## 🔴 Advanced Level

### Location
`03-advanced/code/`

### Setup
```bash
cd 03-advanced/code
npm install
```

### Run
```bash
npm run start:dev
```

### Access
- Backend API: `http://localhost:3000`

---

## 📦 Examples (Complete Working Demo)

### Location
`examples/backend/` and `examples/frontend/`

### Setup
From project root:
```bash
npm install
```

### Run
From project root:
```bash
npm run start:dev
```

This runs the examples backend which serves the frontend.

### Access
- Backend API: `http://localhost:3000/api`
- Frontend UI: `http://localhost:3000/public/index.html`

---

## 🔧 Troubleshooting

### Error: Module not found

**Problem:** Dependencies not installed

**Solution:**
```bash
cd [level-directory]
npm install
```

### Error: Cannot find module '@nestjs/common'

**Problem:** Running from wrong directory or dependencies not installed

**Solution:**
1. Make sure you're in the correct directory
2. Run `npm install` in that directory
3. Try again

### Error: Port already in use

**Problem:** Another server is running on port 3000

**Solution:**
```bash
# Kill the process using port 3000
lsof -ti:3000 | xargs kill

# Or use a different port
PORT=3001 npm run start:dev
```

### Error: Can't resolve 'ts-loader'

**Problem:** Dev dependencies not installed

**Solution:**
```bash
npm install
```

This installs both dependencies and devDependencies.

---

## 📝 Quick Reference

| Level | Directory | Command |
|-------|-----------|---------|
| Beginner | `01-beginner/demo-beginner/` | `npm install && npm run start:dev` |
| Intermediate | `02-intermediate/code/` | `npm install && npm run start:dev` |
| Advanced | `03-advanced/code/` | `npm install && npm run start:dev` |
| Examples | Root (run from root) | `npm install && npm run start:dev` |

---

## 💡 Tips

1. **One at a time**: Only run one level at a time (they all use port 3000)
2. **Install first**: Always run `npm install` before `npm run start:dev`
3. **Check directory**: Make sure you're in the correct directory before running commands
4. **Read README**: Each level has a README with specific instructions

---

## 🎯 Recommended Learning Path

1. Start with **Beginner** level
2. Once comfortable, move to **Intermediate**
3. Then try **Advanced**
4. Finally, explore the **Examples** for a complete working application

Each level builds on the previous one, so follow them in order!

