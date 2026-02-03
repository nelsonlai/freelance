# Backend Server for Angular Comprehensive Demo

This is a Node.js/Express backend server that provides REST API endpoints for the Angular Comprehensive Demo application.

## Features

- ✅ RESTful API endpoints
- ✅ JWT authentication
- ✅ CORS support
- ✅ Password hashing with bcrypt
- ✅ Role-based access control (Admin/User)
- ✅ In-memory data storage
- ✅ Error handling

## Installation

1. Navigate to the server directory:
   ```bash
   cd server
   ```

2. Install dependencies:
   ```bash
   npm install
   ```

## Running the Server

### Development Mode (with auto-reload):
```bash
npm run dev
```

### Production Mode:
```bash
npm start
```

The server will start on `http://localhost:3000`

## API Endpoints

### Authentication

- **POST** `/api/auth/register` - Register a new user
- **POST** `/api/auth/login` - Login user
- **POST** `/api/auth/refresh` - Refresh access token

### Users (Authentication Required)

- **GET** `/api/users` - Get all users
- **GET** `/api/users/:id` - Get user by ID
- **POST** `/api/users` - Create user (Admin only)
- **PUT** `/api/users/:id` - Update user
- **DELETE** `/api/users/:id` - Delete user (Admin only)

### Products (Authentication Required)

- **GET** `/api/products` - Get all products
- **GET** `/api/products/:id` - Get product by ID
- **POST** `/api/products` - Create product (Admin only)
- **PUT** `/api/products/:id` - Update product (Admin only)
- **DELETE** `/api/products/:id` - Delete product (Admin only)

## Default Users

The server comes with two default users:

**Admin User:**
- Email: `jane@example.com`
- Password: `password123`
- Role: `admin`

**Regular User:**
- Email: `john@example.com`
- Password: `password123`
- Role: `user`

## Authentication

All protected endpoints require a JWT token in the Authorization header:

```
Authorization: Bearer <token>
```

Tokens are obtained by logging in via `/api/auth/login` or registering via `/api/auth/register`.

## Request/Response Examples

### Register User
```bash
POST /api/auth/register
Content-Type: application/json

{
  "firstName": "John",
  "lastName": "Doe",
  "email": "john@example.com",
  "password": "password123",
  "role": "user"
}
```

### Login
```bash
POST /api/auth/login
Content-Type: application/json

{
  "email": "john@example.com",
  "password": "password123"
}
```

Response:
```json
{
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
  "refreshToken": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
  "user": {
    "id": 1,
    "firstName": "John",
    "lastName": "Doe",
    "email": "john@example.com",
    "role": "user",
    "isActive": true
  },
  "expiresIn": 3600
}
```

### Get Users (with authentication)
```bash
GET /api/users
Authorization: Bearer <token>
```

## Data Storage

Currently, the server uses in-memory storage. This means:
- Data persists only while the server is running
- Data is reset when the server restarts
- Suitable for development and demo purposes

For production, you would replace this with a database (MongoDB, PostgreSQL, etc.).

## Security Notes

⚠️ **Important for Production:**

1. Change the `JWT_SECRET` in `server.js` to a secure random string
2. Use environment variables for sensitive configuration
3. Implement rate limiting
4. Add input validation and sanitization
5. Use HTTPS in production
6. Implement proper database instead of in-memory storage
7. Add logging and monitoring
8. Implement proper error handling

## Development

The server uses `nodemon` for development, which automatically restarts the server when files change.

## Troubleshooting

**Port already in use:**
- Change the `PORT` constant in `server.js`
- Or kill the process using port 3000: `lsof -ti:3000 | xargs kill`

**CORS errors:**
- The server has CORS enabled for all origins
- If you still see CORS errors, check the Angular app's API URL configuration

**Authentication errors:**
- Make sure you're including the `Authorization: Bearer <token>` header
- Check that the token hasn't expired (default: 1 hour)
- Use the refresh token endpoint to get a new access token

