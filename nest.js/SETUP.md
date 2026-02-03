# Setup Instructions

## Prerequisites

Before you begin, ensure you have the following installed:

- **Node.js** (v18 or higher) - [Download](https://nodejs.org/)
- **npm** (comes with Node.js) or **yarn**
- **Git** (optional, for version control)

## Installation Steps

### 1. Install Dependencies

```bash
# Navigate to the project directory
cd nest.js

# Install all dependencies
npm install
```

### 2. Start the Development Server

```bash
# Start the NestJS backend in development mode
npm run start:dev
```

The server will start on `http://localhost:3000`

### 3. Access the Frontend

Once the server is running, open your browser and navigate to:

```
http://localhost:3000/public/index.html
```

## Project Structure

```
nest.js/
├── 01-beginner/              # Beginner tutorials
├── 02-intermediate/          # Intermediate concepts
├── 03-advanced/              # Advanced topics
├── examples/
│   ├── backend/              # Complete NestJS backend
│   │   └── src/
│   │       ├── main.ts      # Application entry point
│   │       ├── app.module.ts
│   │       ├── tasks/        # Tasks module
│   │       └── users/        # Users module
│   └── frontend/             # HTML/CSS/JavaScript frontend
│       ├── index.html
│       ├── styles.css
│       └── app.js
├── package.json
└── README.md
```

## Available Scripts

- `npm run start` - Start the application
- `npm run start:dev` - Start in development mode with hot reload
- `npm run start:debug` - Start in debug mode
- `npm run start:prod` - Start in production mode
- `npm run build` - Build the application
- `npm run test` - Run unit tests
- `npm run test:e2e` - Run end-to-end tests
- `npm run lint` - Run ESLint

## API Endpoints

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

## Testing the API

### Using the Frontend

The easiest way to test the API is through the provided frontend interface at `http://localhost:3000/public/index.html`.

### Using cURL

```bash
# Get all tasks
curl http://localhost:3000/api/tasks

# Get a specific task
curl http://localhost:3000/api/tasks/1

# Create a task
curl -X POST http://localhost:3000/api/tasks \
  -H "Content-Type: application/json" \
  -d '{"title":"New Task","description":"Task description","completed":false}'

# Update a task
curl -X PUT http://localhost:3000/api/tasks/1 \
  -H "Content-Type: application/json" \
  -d '{"title":"Updated Task","completed":true}'

# Delete a task
curl -X DELETE http://localhost:3000/api/tasks/1

# Test OPTIONS (CORS preflight)
curl -X OPTIONS http://localhost:3000/api/tasks \
  -H "Origin: http://localhost:3000" \
  -H "Access-Control-Request-Method: POST"
```

### Using Postman

1. Import the collection (if available)
2. Set the base URL to `http://localhost:3000/api`
3. Test each endpoint

## Troubleshooting

### Port Already in Use

If port 3000 is already in use, you can change it:

1. Set an environment variable:
   ```bash
   PORT=3001 npm run start:dev
   ```

2. Or modify `examples/backend/src/main.ts`:
   ```typescript
   const port = process.env.PORT || 3001;
   ```

### CORS Issues

If you encounter CORS errors, ensure:

1. The CORS configuration in `main.ts` includes your frontend origin
2. The frontend is accessing the correct API URL
3. OPTIONS requests are properly handled

### Module Not Found Errors

If you see module not found errors:

```bash
# Clear node_modules and reinstall
rm -rf node_modules package-lock.json
npm install
```

## Learning Path

1. **Start Here**: Read `01-beginner/README.md`
2. **Practice**: Work through the examples in `examples/`
3. **Progress**: Move to `02-intermediate/README.md`
4. **Master**: Complete `03-advanced/README.md`
5. **Build**: Create your own NestJS application

## Next Steps

- Read the [Beginner Guide](./01-beginner/README.md)
- Explore the [Complete Examples](./examples/README.md)
- Check out the [NestJS Official Documentation](https://docs.nestjs.com/)

## Support

For issues or questions:
- Check the [NestJS Documentation](https://docs.nestjs.com/)
- Review the tutorial materials in this repository
- Check the examples for working code

Happy Learning! 🚀

