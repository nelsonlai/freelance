# Module 5: Nest.js Backend Development

Nest.js is a **TypeScript-first** backend framework built on Node.js. It uses **modules**, **dependency injection**, and **decorators** similar to Angular, and is well-suited for scalable REST APIs and microservices.

---

## 1. Why Nest.js?

- **Structure**: Modules, controllers, services, and clear separation of concerns.
- **TypeScript**: First-class support and strong typing.
- **Dependency injection**: Built-in IoC container for testability and modularity.
- **Decorators**: `@Controller()`, `@Get()`, `@Post()`, `@Body()`, etc. for routing and validation.
- **Ecosystem**: OpenAPI (Swagger), TypeORM/Prisma, Passport (auth), etc.
- **Testing**: Unit and e2e testing built into the CLI.

---

## 2. Prerequisites

- **Node.js** 18+
- **npm** or **pnpm** / **yarn**

---

## 3. Project Setup

```bash
npm i -g @nestjs/cli
nest new my-api
cd my-api
```

Options: npm/yarn/pnpm, strict TypeScript. This creates `src/` with `main.ts`, `app.module.ts`, `app.controller.ts`, `app.service.ts`.

---

## 4. Project Structure (Default)

```
my-api/
  src/
    main.ts              # Bootstrap app
    app.module.ts        # Root module
    app.controller.ts    # Root controller
    app.service.ts       # Root service
  test/
  package.json
  tsconfig.json
```

---

## 5. Main Entry (Bootstrap)

```typescript
// src/main.ts
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.setGlobalPrefix('api/v1');  // optional: all routes under /api/v1
  app.enableCors();
  await app.listen(process.env.PORT || 3000);
}
bootstrap();
```

---

## 6. Module, Controller, Service

**Module** — groups related pieces (controllers, services, imports):

```typescript
// src/app.module.ts
import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { UsersModule } from './users/users.module';

@Module({
  imports: [UsersModule],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
```

**Controller** — handles HTTP and delegates to services:

```typescript
// src/users/users.controller.ts
import { Controller, Get, Post, Body, Param, ParseIntPipe } from '@nestjs/common';
import { UsersService } from './users.service';

@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  @Get()
  findAll() {
    return this.usersService.findAll();
  }

  @Get(':id')
  findOne(@Param('id', ParseIntPipe) id: number) {
    return this.usersService.findOne(id);
  }

  @Post()
  create(@Body() body: { email: string; name?: string }) {
    return this.usersService.create(body);
  }
}
```

**Service** — business logic and data access:

```typescript
// src/users/users.service.ts
import { Injectable, NotFoundException } from '@nestjs/common';

@Injectable()
export class UsersService {
  async findAll() {
    return [];  // or prisma.user.findMany()
  }

  async findOne(id: number) {
    const user = await this.findUserById(id);  // your logic
    if (!user) throw new NotFoundException('User not found');
    return user;
  }

  async create(data: { email: string; name?: string }) {
    return {};  // or prisma.user.create({ data })
  }
}
```

**Feature module** — wires controller and service:

```typescript
// src/users/users.module.ts
import { Module } from '@nestjs/common';
import { UsersController } from './users.controller';
import { UsersService } from './users.service';

@Module({
  controllers: [UsersController],
  providers: [UsersService],
  exports: [UsersService],  // if other modules need UsersService
})
export class UsersModule {}
```

---

## 7. Routing and Parameters

- **Path params**: `@Param('id', ParseIntPipe) id: number`
- **Query**: `@Query('page') page: string`, `@Query() query: { page?: string; limit?: string }`
- **Body**: `@Body() body: CreateUserDto` (use DTOs with `class-validator` for validation)
- **Headers**: `@Headers('authorization') auth: string`

---

## 8. DTOs and Validation

```bash
npm install class-validator class-transformer
```

Enable global validation in `main.ts`:

```typescript
import { ValidationPipe } from '@nestjs/common';

const app = await NestFactory.create(AppModule);
app.useGlobalPipes(new ValidationPipe({ whitelist: true }));
```

DTO example:

```typescript
// src/users/dto/create-user.dto.ts
import { IsEmail, IsOptional, IsString } from 'class-validator';

export class CreateUserDto {
  @IsEmail()
  email: string;

  @IsOptional()
  @IsString()
  name?: string;
}
```

In controller: `@Body() body: CreateUserDto` — invalid body returns 400 automatically.

---

## 9. Exception Handling

- Use built-in **exceptions**: `NotFoundException`, `BadRequestException`, `UnauthorizedException`, etc.
- Throwing in a service or controller is caught by Nest and converted to HTTP response.

```typescript
import { NotFoundException } from '@nestjs/common';

throw new NotFoundException('User not found');
// -> 404 { "statusCode": 404, "message": "User not found" }
```

- Custom exception filter: implement `ExceptionFilter` and use `@Catch()` / `@UseFilters()` for global or per-route behavior.

---

## 10. Dependency Injection

- **Constructor injection**: `constructor(private readonly usersService: UsersService) {}`
- Services are **providers**; register in a module's `providers` (or use `@Injectable()` and register in a module).
- Other modules: import `UsersModule` and, if needed, export `UsersService` from it so it can be injected elsewhere.

---

## 11. OpenAPI (Swagger)

```bash
npm install @nestjs/swagger swagger-ui-express
```

```typescript
// main.ts
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';

const config = new DocumentBuilder()
  .setTitle('My API')
  .setVersion('1.0')
  .build();
const document = SwaggerModule.createDocument(app, config);
SwaggerModule.setup('docs', app, document);
```

Use `@ApiTags()`, `@ApiBody()`, `@ApiResponse()` on controllers and methods to enrich docs.

---

## 12. Database (Prisma)

```bash
npm install @prisma/client
npm install -D prisma
npx prisma init
```

- Define schema in `prisma/schema.prisma`, then `npx prisma generate` and migrations.
- Create a **PrismaService** that extends `PrismaClient` and is provided in a module (e.g. `PrismaModule`).
- Inject `PrismaService` in your services and call `this.prisma.user.findMany()`, etc.

---

## 13. Project Structure (Scalable)

```
src/
  main.ts
  app.module.ts
  users/
    users.module.ts
    users.controller.ts
    users.service.ts
    dto/
      create-user.dto.ts
      update-user.dto.ts
  prisma/
    prisma.module.ts
    prisma.service.ts
prisma/
  schema.prisma
```

---

## 14. Running and Building

```bash
npm run start        # dev
npm run start:dev    # watch mode
npm run start:prod   # production (after build)
npm run build        # compile to dist/
```

---

## Lesson Plan

1. Create project and understand module/controller/service.
2. Add a feature module (e.g. users) with CRUD.
3. DTOs and validation (class-validator).
4. Exception handling and status codes.
5. Prisma (or TypeORM) integration.
6. OpenAPI (Swagger).
7. Auth (e.g. JWT with Passport).

---

## Comparison: Express vs Nest.js

| Aspect       | Express (Node.js) | Nest.js              |
|-------------|-------------------|----------------------|
| Structure   | You define         | Modules, DI, layers  |
| TypeScript  | Optional           | First-class          |
| Validation  | Manual / Zod       | DTOs + class-validator |
| OpenAPI     | Manual / swagger-jsdoc | Built-in Swagger |
| Learning    | Easier, minimal   | More concepts        |

Use **Express** for small APIs or maximum flexibility; use **Nest.js** for larger, structured TypeScript backends.

---

## Next

- [01_restful_api](../01_restful_api/) — REST  
- [04_nodejs](../04_nodejs/) — Node.js with Express  
- [06_sql](../06_sql/) / [07_nosql](../07_nosql/) — Databases  
