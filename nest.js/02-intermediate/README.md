# Intermediate Level: Core NestJS Concepts

## 📚 Table of Contents

1. [Services and Dependency Injection](#services-and-dependency-injection)
2. [Middleware](#middleware)
3. [Pipes - Validation & Transformation](#pipes---validation--transformation)
4. [Guards - Authentication & Authorization](#guards---authentication--authorization)
5. [Exception Filters](#exception-filters)
6. [Interceptors](#interceptors)
7. [Custom Decorators](#custom-decorators)
8. [Configuration Management](#configuration-management)

---

## Services and Dependency Injection

### Understanding Dependency Injection

Dependency Injection (DI) is a design pattern where objects receive their dependencies from an external source rather than creating them internally.

### Service Lifecycle

```typescript
import { Injectable, Scope } from '@nestjs/common';

// Default: Singleton (shared instance)
@Injectable()
export class UsersService {
  // ...
}

// Request-scoped (new instance per request)
@Injectable({ scope: Scope.REQUEST })
export class RequestScopedService {
  // ...
}

// Transient (new instance every time)
@Injectable({ scope: Scope.TRANSIENT })
export class TransientService {
  // ...
}
```

### Custom Providers

```typescript
// Custom factory provider
const customProvider = {
  provide: 'CONFIG',
  useFactory: () => {
    return {
      apiKey: process.env.API_KEY,
      timeout: 5000,
    };
  },
};

@Module({
  providers: [customProvider],
})
export class AppModule {}
```

### Using Custom Providers

```typescript
@Injectable()
export class ApiService {
  constructor(@Inject('CONFIG') private config: any) {}
}
```

### Optional Dependencies

```typescript
import { Injectable, Optional, Inject } from '@nestjs/common';

@Injectable()
export class MyService {
  constructor(
    @Optional() @Inject('OPTIONAL_SERVICE') private optionalService?: any,
  ) {}
}
```

---

## Middleware

### What is Middleware?

Middleware functions have access to the request object, response object, and the next middleware function. They can execute code, modify requests/responses, and end the request-response cycle.

### Creating Middleware

```typescript
// logger.middleware.ts
import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';

@Injectable()
export class LoggerMiddleware implements NestMiddleware {
  use(req: Request, res: Response, next: NextFunction) {
    console.log(`[${new Date().toISOString()}] ${req.method} ${req.url}`);
    next();
  }
}
```

### Applying Middleware

```typescript
// app.module.ts
import { Module, NestModule, MiddlewareConsumer } from '@nestjs/common';
import { LoggerMiddleware } from './common/middleware/logger.middleware';

@Module({
  // ...
})
export class AppModule implements NestModule {
  configure(consumer: MiddlewareConsumer) {
    consumer
      .apply(LoggerMiddleware)
      .forRoutes('*'); // Apply to all routes
      
    // Or apply to specific routes
    consumer
      .apply(LoggerMiddleware)
      .forRoutes({ path: 'users', method: RequestMethod.GET });
      
    // Or apply to controllers
    consumer
      .apply(LoggerMiddleware)
      .forRoutes(UsersController);
  }
}
```

### Functional Middleware

```typescript
// logger.middleware.ts
import { Request, Response, NextFunction } from 'express';

export function logger(req: Request, res: Response, next: NextFunction) {
  console.log(`Request: ${req.method} ${req.url}`);
  next();
}

// app.module.ts
consumer.apply(logger).forRoutes('*');
```

### CORS Middleware

```typescript
// main.ts
app.enableCors({
  origin: ['http://localhost:3000', 'http://localhost:4200'],
  methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',
  credentials: true,
});
```

---

## Pipes - Validation & Transformation

### What are Pipes?

Pipes transform input data and validate it. They run before the route handler receives the request.

### Built-in Pipes

```typescript
import { ParseIntPipe, ParseBoolPipe, DefaultValuePipe } from '@nestjs/common';

@Get(':id')
findOne(@Param('id', ParseIntPipe) id: number) {
  // id is automatically converted to number
}

@Get()
findAll(
  @Query('active', new DefaultValuePipe(false), ParseBoolPipe) active: boolean,
) {
  // active defaults to false if not provided
}
```

### Validation Pipe

```typescript
// main.ts
import { ValidationPipe } from '@nestjs/common';

app.useGlobalPipes(
  new ValidationPipe({
    whitelist: true, // Strip properties that don't have decorators
    forbidNonWhitelisted: true, // Throw error if non-whitelisted properties exist
    transform: true, // Automatically transform payloads to DTO instances
    transformOptions: {
      enableImplicitConversion: true,
    },
  }),
);
```

### Creating DTOs with Validation

```bash
npm install class-validator class-transformer
```

```typescript
// dto/create-user.dto.ts
import {
  IsString,
  IsEmail,
  IsOptional,
  MinLength,
  MaxLength,
  IsInt,
  Min,
  Max,
} from 'class-validator';

export class CreateUserDto {
  @IsString()
  @MinLength(3)
  @MaxLength(50)
  name: string;

  @IsEmail()
  email: string;

  @IsOptional()
  @IsInt()
  @Min(18)
  @Max(100)
  age?: number;
}
```

### Custom Validation Pipe

```typescript
import {
  PipeTransform,
  Injectable,
  ArgumentMetadata,
  BadRequestException,
} from '@nestjs/common';

@Injectable()
export class ParseIntPipe implements PipeTransform<string, number> {
  transform(value: string, metadata: ArgumentMetadata): number {
    const val = parseInt(value, 10);
    if (isNaN(val)) {
      throw new BadRequestException('Validation failed');
    }
    return val;
  }
}
```

### Using Custom Pipes

```typescript
@Get(':id')
findOne(@Param('id', ParseIntPipe) id: number) {
  return this.usersService.findOne(id);
}
```

---

## Guards - Authentication & Authorization

### What are Guards?

Guards determine whether a request should be handled by the route handler. They run after middleware but before interceptors and pipes.

### Creating a Guard

```typescript
// auth.guard.ts
import {
  Injectable,
  CanActivate,
  ExecutionContext,
  UnauthorizedException,
} from '@nestjs/common';

@Injectable()
export class AuthGuard implements CanActivate {
  canActivate(context: ExecutionContext): boolean {
    const request = context.switchToHttp().getRequest();
    const token = request.headers.authorization;

    if (!token) {
      throw new UnauthorizedException('No token provided');
    }

    // Validate token here
    // For demo purposes, we'll just check if it exists
    return true;
  }
}
```

### Using Guards

```typescript
// Apply to a single route
@UseGuards(AuthGuard)
@Get('profile')
getProfile() {
  return { message: 'Protected route' };
}

// Apply to a controller
@Controller('users')
@UseGuards(AuthGuard)
export class UsersController {
  // All routes in this controller are protected
}

// Apply globally
// app.module.ts or main.ts
app.useGlobalGuards(new AuthGuard());
```

### Role-Based Authorization Guard

```typescript
// roles.guard.ts
import { Injectable, CanActivate, ExecutionContext } from '@nestjs/common';
import { Reflector } from '@nestjs/core';

@Injectable()
export class RolesGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate(context: ExecutionContext): boolean {
    const requiredRoles = this.reflector.get<string[]>(
      'roles',
      context.getHandler(),
    );
    if (!requiredRoles) {
      return true;
    }

    const request = context.switchToHttp().getRequest();
    const user = request.user;

    return requiredRoles.some((role) => user.roles?.includes(role));
  }
}
```

### Custom Decorator for Roles

```typescript
// roles.decorator.ts
import { SetMetadata } from '@nestjs/common';

export const Roles = (...roles: string[]) => SetMetadata('roles', roles);
```

### Using Role Guard

```typescript
@Controller('admin')
@UseGuards(AuthGuard, RolesGuard)
export class AdminController {
  @Get('users')
  @Roles('admin')
  getAllUsers() {
    return { message: 'Admin only' };
  }

  @Get('settings')
  @Roles('admin', 'moderator')
  getSettings() {
    return { message: 'Admin or moderator' };
  }
}
```

---

## Exception Filters

### What are Exception Filters?

Exception filters catch exceptions thrown by route handlers and return appropriate responses.

### Built-in Exceptions

```typescript
import {
  BadRequestException,
  UnauthorizedException,
  NotFoundException,
  ForbiddenException,
  ConflictException,
  InternalServerErrorException,
} from '@nestjs/common';

@Get(':id')
findOne(@Param('id') id: string) {
  const user = this.usersService.findOne(id);
  if (!user) {
    throw new NotFoundException(`User with ID ${id} not found`);
  }
  return user;
}
```

### Custom Exception Filter

```typescript
// http-exception.filter.ts
import {
  ExceptionFilter,
  Catch,
  ArgumentsHost,
  HttpException,
  HttpStatus,
} from '@nestjs/common';
import { Request, Response } from 'express';

@Catch()
export class AllExceptionsFilter implements ExceptionFilter {
  catch(exception: unknown, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const response = ctx.getResponse<Response>();
    const request = ctx.getRequest<Request>();

    const status =
      exception instanceof HttpException
        ? exception.getStatus()
        : HttpStatus.INTERNAL_SERVER_ERROR;

    const message =
      exception instanceof HttpException
        ? exception.getResponse()
        : 'Internal server error';

    response.status(status).json({
      statusCode: status,
      timestamp: new Date().toISOString(),
      path: request.url,
      message,
    });
  }
}
```

### Using Exception Filters

```typescript
// Apply to a route
@UseFilters(HttpExceptionFilter)
@Get(':id')
findOne(@Param('id') id: string) {
  // ...
}

// Apply globally
// main.ts
app.useGlobalFilters(new AllExceptionsFilter());
```

---

## Interceptors

### What are Interceptors?

Interceptors can transform the response, add extra logic before/after method execution, and handle exceptions.

### Response Transformation Interceptor

```typescript
// transform.interceptor.ts
import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

export interface Response<T> {
  data: T;
}

@Injectable()
export class TransformInterceptor<T>
  implements NestInterceptor<T, Response<T>>
{
  intercept(
    context: ExecutionContext,
    next: CallHandler,
  ): Observable<Response<T>> {
    return next.handle().pipe(
      map((data) => ({
        success: true,
        data,
        timestamp: new Date().toISOString(),
      })),
    );
  }
}
```

### Logging Interceptor

```typescript
// logging.interceptor.ts
import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';

@Injectable()
export class LoggingInterceptor implements NestInterceptor {
  intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
    const now = Date.now();
    const request = context.switchToHttp().getRequest();

    console.log(`Before: ${request.method} ${request.url}`);

    return next.handle().pipe(
      tap(() =>
        console.log(`After: ${Date.now() - now}ms`),
      ),
    );
  }
}
```

### Using Interceptors

```typescript
// Apply to a route
@UseInterceptors(TransformInterceptor)
@Get()
findAll() {
  return this.usersService.findAll();
}

// Apply globally
// main.ts
app.useGlobalInterceptors(new TransformInterceptor());
```

---

## Custom Decorators

### Creating Custom Decorators

```typescript
// user.decorator.ts
import { createParamDecorator, ExecutionContext } from '@nestjs/common';

export const User = createParamDecorator(
  (data: string, ctx: ExecutionContext) => {
    const request = ctx.switchToHttp().getRequest();
    const user = request.user;

    return data ? user?.[data] : user;
  },
);
```

### Using Custom Decorators

```typescript
@Get('profile')
getProfile(@User() user: any) {
  return user;
}

@Get('email')
getEmail(@User('email') email: string) {
  return { email };
}
```

### Combining Decorators

```typescript
// public.decorator.ts
import { SetMetadata } from '@nestjs/common';

export const IS_PUBLIC_KEY = 'isPublic';
export const Public = () => SetMetadata(IS_PUBLIC_KEY, true);
```

```typescript
// auth.guard.ts (updated)
import { Injectable, ExecutionContext } from '@nestjs/common';
import { Reflector } from '@nestjs/core';
import { IS_PUBLIC_KEY } from './public.decorator';

@Injectable()
export class AuthGuard {
  constructor(private reflector: Reflector) {}

  canActivate(context: ExecutionContext): boolean {
    const isPublic = this.reflector.getAllAndOverride<boolean>(IS_PUBLIC_KEY, [
      context.getHandler(),
      context.getClass(),
    ]);

    if (isPublic) {
      return true;
    }

    // Check authentication
    return true;
  }
}
```

---

## Configuration Management

### Environment Variables

```bash
npm install @nestjs/config
```

```typescript
// app.module.ts
import { ConfigModule } from '@nestjs/config';

@Module({
  imports: [
    ConfigModule.forRoot({
      isGlobal: true,
      envFilePath: '.env',
    }),
  ],
})
export class AppModule {}
```

### Using Configuration

```typescript
import { ConfigService } from '@nestjs/config';

@Injectable()
export class AppService {
  constructor(private configService: ConfigService) {}

  getDatabaseUrl() {
    return this.configService.get<string>('DATABASE_URL');
  }
}
```

### Configuration Schema

```typescript
// config/configuration.ts
export default () => ({
  port: parseInt(process.env.PORT, 10) || 3000,
  database: {
    host: process.env.DATABASE_HOST,
    port: parseInt(process.env.DATABASE_PORT, 10) || 5432,
  },
});
```

---

## Exercises

1. Create a logging middleware that logs all requests to a file
2. Implement a validation pipe that validates email format
3. Create an authentication guard using JWT tokens
4. Build a response interceptor that adds pagination metadata
5. Create a custom decorator that extracts the client IP address

---

## Next Steps

Ready for advanced topics? Continue to:
- [Advanced Level](../03-advanced/README.md) - Advanced patterns, microservices, testing

