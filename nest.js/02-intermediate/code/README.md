# Intermediate Level - Complete Code Examples

This directory contains complete, runnable code examples demonstrating intermediate NestJS concepts.

## 📁 File Structure

```
code/
├── main.ts
├── app.module.ts
├── app.controller.ts
├── app.service.ts
├── common/
│   ├── middleware/
│   │   └── logger.middleware.ts
│   ├── interceptors/
│   │   └── transform.interceptor.ts
│   ├── filters/
│   │   └── http-exception.filter.ts
│   └── pipes/
│       └── parse-int.pipe.ts
├── users/
│   ├── users.module.ts
│   ├── users.controller.ts
│   ├── users.service.ts
│   └── dto/
│       └── create-user.dto.ts
└── auth/
    ├── auth.module.ts
    ├── guards/
    │   ├── auth.guard.ts
    │   └── roles.guard.ts
    └── decorators/
        ├── public.decorator.ts
        └── roles.decorator.ts
```

## 🚀 Setup and Installation

### Step 1: Install Dependencies

```bash
cd 02-intermediate/code
npm install
```

### Step 2: Start the Server

```bash
npm run start:dev
```

The server will start on `http://localhost:3000`

## 📝 API Endpoints

### Public Endpoints
- `GET /` - Hello message
- `GET /health` - Health check
- `GET /protected` - Protected route (requires auth)

### User Endpoints (Requires Authentication)
- `GET /users` - Get all users (with optional query params: ?minAge=25&maxAge=50)
- `GET /users/:id` - Get a specific user
- `POST /users` - Create a new user (validated)
- `PUT /users/:id` - Update a user
- `DELETE /users/:id` - Delete a user (Admin only)

## 🧪 Test with cURL

```bash
# Public endpoint
curl http://localhost:3000/

# Protected endpoint (without auth - will fail)
curl http://localhost:3000/protected

# Protected endpoint (with auth)
curl http://localhost:3000/protected \
  -H "Authorization: Bearer valid-token"

# Get all users (with auth)
curl http://localhost:3000/users \
  -H "Authorization: Bearer valid-token"

# Get users with filters
curl "http://localhost:3000/users?minAge=25&maxAge=50" \
  -H "Authorization: Bearer valid-token"

# Create user (validated)
curl -X POST http://localhost:3000/users \
  -H "Authorization: Bearer valid-token" \
  -H "Content-Type: application/json" \
  -d '{
    "name": "Alice",
    "email": "alice@example.com",
    "age": 28
  }'

# Try invalid data (will fail validation)
curl -X POST http://localhost:3000/users \
  -H "Authorization: Bearer valid-token" \
  -H "Content-Type: application/json" \
  -d '{
    "name": "AB",
    "email": "invalid-email",
    "age": 15
  }'
```

## 📚 Learning Points

1. **Middleware**: Request logging middleware
2. **Validation Pipes**: Automatic validation with class-validator
3. **Guards**: Authentication and authorization guards
4. **Interceptors**: Response transformation
5. **Exception Filters**: Global error handling
6. **Custom Decorators**: Public and Roles decorators
7. **Custom Pipes**: ParseIntPipe for parameter validation
8. **Query Parameters**: Filtering with query params

## 🔐 Authentication

For this tutorial, use any token string:
- Valid token: `Bearer valid-token` or any non-empty token
- Invalid: No token or empty token

In production, implement proper JWT validation.

## ⚠️ Important Notes

- Make sure to run `npm install` in this directory first
- The code files are in the root of this directory (not in `src/`)
- All dependencies must be installed before running
