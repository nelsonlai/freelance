# Beginner Level - Complete Code Examples

This directory contains complete, runnable code examples for the beginner level.

## 📁 File Structure

```
code/
├── main.ts                 # Application entry point
├── app.module.ts          # Root module
├── app.controller.ts      # Root controller
├── app.service.ts         # Root service
└── todos/                 # Todos feature module
    ├── todos.module.ts
    ├── todos.controller.ts
    ├── todos.service.ts
    └── dto/
        └── create-todo.dto.ts
```

## 🚀 How to Run

1. Copy these files to your NestJS project
2. Install dependencies: `npm install`
3. Run: `npm run start:dev`
4. Test the API at `http://localhost:3000`

## 📝 API Endpoints

- `GET /todos` - Get all todos
- `GET /todos/:id` - Get a specific todo
- `POST /todos` - Create a new todo
- `PUT /todos/:id` - Update a todo
- `DELETE /todos/:id` - Delete a todo

## 🧪 Test with cURL

```bash
# Get all todos
curl http://localhost:3000/todos

# Get a specific todo
curl http://localhost:3000/todos/1

# Create a todo
curl -X POST http://localhost:3000/todos \
  -H "Content-Type: application/json" \
  -d '{"title":"New Todo","description":"Learn NestJS","completed":false}'

# Update a todo
curl -X PUT http://localhost:3000/todos/1 \
  -H "Content-Type: application/json" \
  -d '{"title":"Updated Todo","completed":true}'

# Delete a todo
curl -X DELETE http://localhost:3000/todos/1
```

## 📚 Learning Points

1. **Module Structure**: How to organize code into modules
2. **Controllers**: How to handle HTTP requests
3. **Services**: How to implement business logic
4. **Dependency Injection**: How services are injected into controllers
5. **DTOs**: Data Transfer Objects for type safety
6. **HTTP Methods**: GET, POST, PUT, DELETE implementation

