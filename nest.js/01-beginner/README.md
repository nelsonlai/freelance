# Beginner Level: NestJS Fundamentals

## 📚 Table of Contents

1. [Introduction to NestJS](#introduction-to-nestjs)
2. [Project Setup](#project-setup)
3. [Understanding the Project Structure](#understanding-the-project-structure)
4. [Controllers and Routes](#controllers-and-routes)
5. [Basic RESTful API](#basic-restful-api)
6. [Modules](#modules)
7. [Providers and Services](#providers-and-services)
8. [Your First Complete API](#your-first-complete-api)

---

## Introduction to NestJS

### What is NestJS?

NestJS is a progressive Node.js framework for building efficient, reliable, and scalable server-side applications. It uses modern JavaScript, is built with TypeScript, and combines elements of OOP (Object-Oriented Programming), FP (Functional Programming), and FRP (Functional Reactive Programming).

### Key Features

- **Built with TypeScript** - Type safety out of the box
- **Modular Architecture** - Organized, testable, and maintainable code
- **Dependency Injection** - Built-in IoC container
- **Express Under the Hood** - Can use Express or Fastify
- **Decorators** - Clean, declarative syntax
- **Microservices Ready** - Built-in support for microservices

### Why NestJS?

- **Scalability** - Perfect for large-scale applications
- **Developer Experience** - Excellent tooling and documentation
- **Enterprise Ready** - Used by many large companies
- **Active Community** - Strong ecosystem and support

---

## Project Setup

### Step 1: Install NestJS CLI

```bash
npm i -g @nestjs/cli
```

### Step 2: Create a New Project

```bash
nest new project-name
cd project-name
```

### Step 3: Project Structure

After creation, you'll see:

```
project-name/
├── src/
│   ├── app.controller.ts    # Basic controller
│   ├── app.module.ts        # Root module
│   └── main.ts              # Application entry point
├── test/                    # Test files
├── package.json
└── tsconfig.json
```

### Step 4: Run the Application

```bash
# Development mode (with hot reload)
npm run start:dev

# Production mode
npm run start:prod

# Debug mode
npm run start:debug
```

The application will be available at `http://localhost:3000`

---

## Understanding the Project Structure

### main.ts - Application Entry Point

```typescript
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  
  // Enable CORS for frontend communication
  app.enableCors({
    origin: 'http://localhost:3000',
    credentials: true,
  });
  
  await app.listen(3000);
}
bootstrap();
```

**Key Points:**
- `NestFactory.create()` - Creates the NestJS application instance
- `app.listen()` - Starts the HTTP server
- This is where you configure global settings

### app.module.ts - Root Module

```typescript
import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';

@Module({
  imports: [],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
```

**Key Points:**
- `@Module()` - Decorator that defines a module
- `controllers` - Array of controllers in this module
- `providers` - Array of services/providers
- `imports` - Other modules to import

---

## Controllers and Routes

### What is a Controller?

Controllers handle incoming requests and return responses to the client. They define the routes and HTTP methods.

### Creating Your First Controller

```typescript
import { Controller, Get } from '@nestjs/common';

@Controller('users')
export class UsersController {
  @Get()
  findAll() {
    return 'This returns all users';
  }
}
```

### Understanding Decorators

- `@Controller('users')` - Defines the base route `/users`
- `@Get()` - Handles GET requests
- Method name `findAll()` - Can be anything, but should be descriptive

### Complete Controller Example

```typescript
import { Controller, Get, Post, Put, Delete, Param, Body } from '@nestjs/common';

@Controller('products')
export class ProductsController {
  // GET /products
  @Get()
  findAll() {
    return { message: 'Get all products' };
  }

  // GET /products/:id
  @Get(':id')
  findOne(@Param('id') id: string) {
    return { message: `Get product ${id}` };
  }

  // POST /products
  @Post()
  create(@Body() createProductDto: any) {
    return { message: 'Create a product', data: createProductDto };
  }

  // PUT /products/:id
  @Put(':id')
  update(@Param('id') id: string, @Body() updateProductDto: any) {
    return { message: `Update product ${id}`, data: updateProductDto };
  }

  // DELETE /products/:id
  @Delete(':id')
  remove(@Param('id') id: string) {
    return { message: `Delete product ${id}` };
  }
}
```

### Route Parameters

```typescript
@Get(':id')
findOne(@Param('id') id: string) {
  return { id };
}

// Multiple parameters
@Get(':category/:id')
findByCategory(
  @Param('category') category: string,
  @Param('id') id: string,
) {
  return { category, id };
}
```

### Query Parameters

```typescript
@Get()
findAll(@Query('page') page: number, @Query('limit') limit: number) {
  return { page, limit };
}
// Usage: GET /products?page=1&limit=10
```

### Request Body

```typescript
@Post()
create(@Body() createDto: any) {
  return createDto;
}
```

---

## Basic RESTful API

### REST Principles

REST (Representational State Transfer) is an architectural style for designing networked applications.

### HTTP Methods

| Method | Purpose | Example |
|--------|---------|---------|
| GET | Retrieve data | `GET /users` - Get all users |
| POST | Create new resource | `POST /users` - Create a user |
| PUT | Update entire resource | `PUT /users/1` - Update user 1 |
| PATCH | Partial update | `PATCH /users/1` - Partially update user 1 |
| DELETE | Remove resource | `DELETE /users/1` - Delete user 1 |
| OPTIONS | CORS preflight | `OPTIONS /users` - Check allowed methods |

### Status Codes

```typescript
import { HttpStatus } from '@nestjs/common';

@Get()
findAll() {
  return {
    statusCode: HttpStatus.OK,
    message: 'Success',
    data: []
  };
}
```

Common Status Codes:
- `200 OK` - Success
- `201 Created` - Resource created
- `400 Bad Request` - Invalid request
- `404 Not Found` - Resource not found
- `500 Internal Server Error` - Server error

---

## Modules

### What is a Module?

A module is a class annotated with the `@Module()` decorator. It organizes related functionality.

### Module Structure

```typescript
import { Module } from '@nestjs/common';
import { UsersController } from './users.controller';
import { UsersService } from './users.service';

@Module({
  controllers: [UsersController],
  providers: [UsersService],
  exports: [UsersService], // Make service available to other modules
})
export class UsersModule {}
```

### Feature Modules

Organize your application by features:

```
src/
├── users/
│   ├── users.controller.ts
│   ├── users.service.ts
│   ├── users.module.ts
│   └── dto/
│       └── create-user.dto.ts
├── products/
│   ├── products.controller.ts
│   ├── products.service.ts
│   └── products.module.ts
└── app.module.ts
```

### Importing Modules

```typescript
// app.module.ts
import { UsersModule } from './users/users.module';
import { ProductsModule } from './products/products.module';

@Module({
  imports: [UsersModule, ProductsModule],
})
export class AppModule {}
```

---

## Providers and Services

### What is a Service?

Services contain business logic and are injectable into controllers or other services.

### Creating a Service

```typescript
import { Injectable } from '@nestjs/common';

@Injectable()
export class UsersService {
  private users = [];

  findAll() {
    return this.users;
  }

  findOne(id: string) {
    return this.users.find(user => user.id === id);
  }

  create(createUserDto: any) {
    const user = {
      id: Date.now().toString(),
      ...createUserDto,
    };
    this.users.push(user);
    return user;
  }

  update(id: string, updateUserDto: any) {
    const index = this.users.findIndex(user => user.id === id);
    if (index >= 0) {
      this.users[index] = { ...this.users[index], ...updateUserDto };
      return this.users[index];
    }
    return null;
  }

  remove(id: string) {
    const index = this.users.findIndex(user => user.id === id);
    if (index >= 0) {
      return this.users.splice(index, 1)[0];
    }
    return null;
  }
}
```

### Injecting Services

```typescript
import { Controller, Get } from '@nestjs/common';
import { UsersService } from './users.service';

@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  @Get()
  findAll() {
    return this.usersService.findAll();
  }
}
```

**Key Points:**
- Use `constructor` injection
- TypeScript automatically resolves dependencies
- `private readonly` - Best practice for service injection

---

## Your First Complete API

### Complete Example: Todo API

#### 1. Create DTO (Data Transfer Object)

```typescript
// dto/create-todo.dto.ts
export class CreateTodoDto {
  title: string;
  description?: string;
  completed?: boolean;
}
```

#### 2. Create Service

```typescript
// todos.service.ts
import { Injectable } from '@nestjs/common';
import { CreateTodoDto } from './dto/create-todo.dto';

@Injectable()
export class TodosService {
  private todos = [];

  create(createTodoDto: CreateTodoDto) {
    const todo = {
      id: Date.now().toString(),
      ...createTodoDto,
      completed: createTodoDto.completed || false,
      createdAt: new Date(),
    };
    this.todos.push(todo);
    return todo;
  }

  findAll() {
    return this.todos;
  }

  findOne(id: string) {
    return this.todos.find(todo => todo.id === id);
  }

  update(id: string, updateTodoDto: Partial<CreateTodoDto>) {
    const todo = this.findOne(id);
    if (todo) {
      Object.assign(todo, updateTodoDto);
      return todo;
    }
    return null;
  }

  remove(id: string) {
    const index = this.todos.findIndex(todo => todo.id === id);
    if (index >= 0) {
      return this.todos.splice(index, 1)[0];
    }
    return null;
  }
}
```

#### 3. Create Controller

```typescript
// todos.controller.ts
import {
  Controller,
  Get,
  Post,
  Put,
  Delete,
  Body,
  Param,
  HttpStatus,
  HttpCode,
} from '@nestjs/common';
import { TodosService } from './todos.service';
import { CreateTodoDto } from './dto/create-todo.dto';

@Controller('todos')
export class TodosController {
  constructor(private readonly todosService: TodosService) {}

  @Post()
  @HttpCode(HttpStatus.CREATED)
  create(@Body() createTodoDto: CreateTodoDto) {
    return this.todosService.create(createTodoDto);
  }

  @Get()
  findAll() {
    return this.todosService.findAll();
  }

  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.todosService.findOne(id);
  }

  @Put(':id')
  update(
    @Param('id') id: string,
    @Body() updateTodoDto: Partial<CreateTodoDto>,
  ) {
    return this.todosService.update(id, updateTodoDto);
  }

  @Delete(':id')
  @HttpCode(HttpStatus.NO_CONTENT)
  remove(@Param('id') id: string) {
    return this.todosService.remove(id);
  }
}
```

#### 4. Create Module

```typescript
// todos.module.ts
import { Module } from '@nestjs/common';
import { TodosController } from './todos.controller';
import { TodosService } from './todos.service';

@Module({
  controllers: [TodosController],
  providers: [TodosService],
})
export class TodosModule {}
```

#### 5. Register in App Module

```typescript
// app.module.ts
import { Module } from '@nestjs/common';
import { TodosModule } from './todos/todos.module';

@Module({
  imports: [TodosModule],
})
export class AppModule {}
```

### Testing Your API

Use tools like:
- **Postman** - API testing tool
- **curl** - Command line tool
- **Thunder Client** - VS Code extension
- **Browser** - For GET requests

Example requests:

```bash
# Create a todo
curl -X POST http://localhost:3000/todos \
  -H "Content-Type: application/json" \
  -d '{"title":"Learn NestJS","description":"Complete the tutorial"}'

# Get all todos
curl http://localhost:3000/todos

# Get a specific todo
curl http://localhost:3000/todos/1

# Update a todo
curl -X PUT http://localhost:3000/todos/1 \
  -H "Content-Type: application/json" \
  -d '{"completed":true}'

# Delete a todo
curl -X DELETE http://localhost:3000/todos/1
```

---

## Exercises

1. Create a `Books` module with full CRUD operations
2. Add validation to ensure required fields are present
3. Implement search functionality using query parameters
4. Add pagination to the `findAll` method

---

## Additional Resources

- **[JSON Guide](./JSON_GUIDE.md)** - Comprehensive guide to JSON format, syntax, and usage in RESTful APIs
- **[Request Flow Explanation](./REQUEST_FLOW_EXPLANATION.md)** - Detailed explanation of how GET and POST requests work

---

## Next Steps

Once you've mastered these basics, move on to:
- [Intermediate Level](../02-intermediate/README.md) - Services, Middleware, Pipes, Guards

