# Backend Server Setup

This document explains how to set up and run the backend server for the Angular Comprehensive Demo.

## Quick Start

1. **Navigate to server directory:**
   ```bash
   cd server
   ```

2. **Install dependencies:**
   ```bash
   npm install
   ```

3. **Start the server:**
   ```bash
   npm start
   ```

4. **Verify server is running:**
   - Open `http://localhost:3000/api/health` in your browser
   - You should see: `{"status":"ok","message":"Server is running"}`

## Server Features

### Authentication
- JWT-based authentication
- Password hashing with bcrypt
- Token refresh mechanism
- Role-based access control

### API Endpoints

**Authentication:**
- `POST /api/auth/register` - Register new user
- `POST /api/auth/login` - Login user
- `POST /api/auth/refresh` - Refresh access token

**Users (Protected):**
- `GET /api/users` - Get all users
- `GET /api/users/:id` - Get user by ID
- `POST /api/users` - Create user (Admin only)
- `PUT /api/users/:id` - Update user
- `DELETE /api/users/:id` - Delete user (Admin only)

**Products (Protected):**
- `GET /api/products` - Get all products
- `GET /api/products/:id` - Get product by ID
- `POST /api/products` - Create product (Admin only)
- `PUT /api/products/:id` - Update product (Admin only)
- `DELETE /api/products/:id` - Delete product (Admin only)

## Default Users

The server comes with pre-configured users:

**Admin:**
- Email: `jane@example.com`
- Password: `password123`

**User:**
- Email: `john@example.com`
- Password: `password123`

## Testing the API

You can test the API using curl, Postman, or any HTTP client:

### Register a new user:
```bash
curl -X POST http://localhost:3000/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{
    "firstName": "Test",
    "lastName": "User",
    "email": "test@example.com",
    "password": "password123"
  }'
```

### Login:
```bash
curl -X POST http://localhost:3000/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{
    "email": "john@example.com",
    "password": "password123"
  }'
```

### Get users (with token):
```bash
curl -X GET http://localhost:3000/api/users \
  -H "Authorization: Bearer YOUR_TOKEN_HERE"
```

## Data Storage

The server uses in-memory storage, which means:
- ✅ Fast and simple for development
- ✅ No database setup required
- ⚠️ Data resets when server restarts
- ⚠️ Not suitable for production

For production, replace with a real database (MongoDB, PostgreSQL, etc.).

## Development Mode

Use `nodemon` for auto-reload during development:

```bash
npm run dev
```

The server will automatically restart when you make changes to `server.js`.

## Troubleshooting

**Port 3000 already in use:**
- Change the `PORT` constant in `server.js`
- Or find and kill the process: `lsof -ti:3000 | xargs kill`

**Module not found errors:**
- Make sure you ran `npm install` in the `server` directory
- Check that `node_modules` exists in the server folder

**CORS errors:**
- The server has CORS enabled for all origins
- If issues persist, check the Angular app's API URL

## Production Considerations

Before deploying to production:

1. **Change JWT Secret:**
   - Use a strong, random secret key
   - Store in environment variables, not in code

2. **Use Environment Variables:**
   ```javascript
   const JWT_SECRET = process.env.JWT_SECRET || 'fallback-secret';
   const PORT = process.env.PORT || 3000;
   ```

3. **Add Database:**
   - Replace in-memory storage with a real database
   - Consider MongoDB, PostgreSQL, or MySQL

4. **Add Security:**
   - Implement rate limiting
   - Add input validation and sanitization
   - Use HTTPS
   - Add proper error logging

5. **Add Monitoring:**
   - Log all requests
   - Monitor server health
   - Set up alerts

## Integration with Angular App

Once the backend is running:

1. The Angular app will automatically connect to `http://localhost:3000/api`
2. Authentication will work with real JWT tokens
3. All API calls will use real data instead of mocks
4. Console errors will disappear (backend is available)

The Angular app is designed to work seamlessly with or without the backend server.

