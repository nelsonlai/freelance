# 🚀 Quick Start Guide

Get up and running with the NestJS tutorial in 5 minutes!

## Step 1: Install Dependencies

```bash
npm install
```

## Step 2: Start the Server

```bash
npm run start:dev
```

You should see:
```
🚀 Application is running on: http://localhost:3000
📱 Frontend available at: http://localhost:3000/public/index.html
```

## Step 3: Open the Frontend

Open your browser and go to:
```
http://localhost:3000/public/index.html
```

## Step 4: Try It Out!

### Test GET Request
1. Click the "Refresh (GET)" button
2. See the list of tasks/users loaded from the API

### Test POST Request
1. Fill in the form (Title for tasks, Name/Email for users)
2. Click "Create Task (POST)" or "Create User (POST)"
3. See the new item appear in the list

### Test PUT Request
1. Click "Edit (PUT)" on any item
2. Enter new values when prompted
3. See the item update

### Test DELETE Request
1. Click "Delete (DELETE)" on any item
2. Confirm the deletion
3. See the item removed

### Test OPTIONS Request
1. Click "Test OPTIONS" button
2. See the CORS preflight response in the API Response section

## What You'll See

- **Modern UI**: Beautiful, responsive interface
- **Real-time Updates**: Changes reflect immediately
- **API Responses**: See the actual API responses below
- **All HTTP Methods**: GET, POST, PUT, DELETE, OPTIONS

## Next Steps

1. **Learn the Basics**: Read [01-beginner/README.md](./01-beginner/README.md)
2. **Explore the Code**: Check out `examples/backend/src/` and `examples/frontend/`
3. **Progress**: Move to [02-intermediate/README.md](./02-intermediate/README.md)
4. **Master**: Complete [03-advanced/README.md](./03-advanced/README.md)

## Troubleshooting

**Port 3000 already in use?**
```bash
PORT=3001 npm run start:dev
```

**Module not found?**
```bash
rm -rf node_modules package-lock.json
npm install
```

**Need help?** Check [SETUP.md](./SETUP.md) for detailed instructions.

Happy coding! 🎉

