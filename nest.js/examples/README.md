# Complete Working Examples

This directory contains a fully functional NestJS backend application with a frontend that demonstrates all RESTful API interactions.

## 🚀 Quick Start

```bash
# Install dependencies
npm install

# Start the backend server
npm run start:dev

# Open your browser to http://localhost:3000/public/index.html
```

## 📁 Structure

```
examples/
├── backend/              # NestJS backend application
│   ├── src/
│   │   ├── main.ts
│   │   ├── app.module.ts
│   │   ├── tasks/        # Tasks module (CRUD example)
│   │   └── users/        # Users module (CRUD example)
│   └── ...
├── frontend/            # HTML/CSS/JavaScript frontend
│   ├── index.html
│   ├── styles.css
│   └── app.js
└── README.md
```

## 🎯 Features Demonstrated

- ✅ Complete RESTful API (GET, POST, PUT, DELETE, OPTIONS)
- ✅ CORS configuration
- ✅ Request validation
- ✅ Error handling
- ✅ Frontend-backend integration
- ✅ Modern UI with vanilla JavaScript

## 📝 API Endpoints

### Tasks API
- `GET /api/tasks` - Get all tasks
- `GET /api/tasks/:id` - Get a specific task
- `POST /api/tasks` - Create a new task
- `PUT /api/tasks/:id` - Update a task
- `DELETE /api/tasks/:id` - Delete a task
- `OPTIONS /api/tasks` - CORS preflight

### Users API
- `GET /api/users` - Get all users
- `GET /api/users/:id` - Get a specific user
- `POST /api/users` - Create a new user
- `PUT /api/users/:id` - Update a user
- `DELETE /api/users/:id` - Delete a user
- `OPTIONS /api/users` - CORS preflight

