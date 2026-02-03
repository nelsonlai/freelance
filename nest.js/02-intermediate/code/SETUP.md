# Setup Instructions for Intermediate Code

## Quick Start

1. **Navigate to the code directory:**
   ```bash
   cd 02-intermediate/code
   ```

2. **Install dependencies:**
   ```bash
   npm install
   ```

3. **Start the development server:**
   ```bash
   npm run start:dev
   ```

4. **Test the API:**
   ```bash
   curl http://localhost:3000/
   ```

## Troubleshooting

### Error: Module not found

If you see errors like "Cannot find module '@nestjs/common'", it means dependencies are not installed.

**Solution:**
```bash
cd 02-intermediate/code
npm install
```

### Error: Can't resolve 'ts-loader'

This means dev dependencies are missing.

**Solution:**
```bash
cd 02-intermediate/code
npm install
```

### Error: Cannot find name 'process' or '__dirname'

This means `@types/node` is not installed.

**Solution:**
```bash
cd 02-intermediate/code
npm install --save-dev @types/node
```

## Directory Structure

The code files are in the root of `02-intermediate/code/` directory:
- `main.ts` - Entry point
- `app.module.ts` - Root module
- All other files in their respective folders

This is different from a standard NestJS project (which uses `src/`), but it's set up this way for easy learning.

## Running from Root Directory

If you want to run from the project root, you need to:

1. Install dependencies in the root:
   ```bash
   npm install
   ```

2. Then the scripts in root `package.json` will work, but they point to `examples/backend`, not `02-intermediate/code`.

## Recommended Approach

**For learning purposes, run each level's code independently:**

```bash
# Beginner level
cd 01-beginner/demo-beginner
npm install
npm run start:dev

# Intermediate level
cd 02-intermediate/code
npm install
npm run start:dev

# Advanced level
cd 03-advanced/code
npm install
npm run start:dev
```

Each level is self-contained and should be run from its own directory.

