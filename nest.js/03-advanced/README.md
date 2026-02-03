# Advanced Level: Advanced NestJS Patterns

## 📚 Table of Contents

1. [Advanced Decorators](#advanced-decorators)
2. [Custom Providers & Factories](#custom-providers--factories)
3. [Dynamic Modules](#dynamic-modules)
4. [Microservices](#microservices)
5. [WebSockets](#websockets)
6. [Testing](#testing)
7. [Database Integration](#database-integration)
8. [Performance Optimization](#performance-optimization)
9. [Security Best Practices](#security-best-practices)

---

## Advanced Decorators

### Parameter Decorators

```typescript
// current-user.decorator.ts
import { createParamDecorator, ExecutionContext } from '@nestjs/common';

export const CurrentUser = createParamDecorator(
  (data: unknown, ctx: ExecutionContext) => {
    const request = ctx.switchToHttp().getRequest();
    return request.user;
  },
);
```

### Method Decorators

```typescript
// cache.decorator.ts
import { SetMetadata } from '@nestjs/common';

export const CacheTTL = (ttl: number) => SetMetadata('cacheTTL', ttl);
```

### Property Decorators

```typescript
// transform.decorator.ts
import { Transform } from 'class-transformer';

export function ToLowerCase() {
  return Transform(({ value }) => value?.toLowerCase());
}

// Usage
export class CreateUserDto {
  @ToLowerCase()
  email: string;
}
```

### Composing Decorators

```typescript
// api-response.decorator.ts
import { applyDecorators, Type } from '@nestjs/common';
import { ApiResponse, ApiOperation } from '@nestjs/swagger';

export function ApiStandardResponse<T>(model: Type<T>) {
  return applyDecorators(
    ApiOperation({ summary: 'Standard response' }),
    ApiResponse({
      status: 200,
      description: 'Success',
      type: model,
    }),
    ApiResponse({
      status: 400,
      description: 'Bad Request',
    }),
  );
}
```

---

## Custom Providers & Factories

### Factory Providers

```typescript
// database.provider.ts
import { Provider } from '@nestjs/common';

export const DATABASE_CONNECTION = 'DATABASE_CONNECTION';

export const databaseProvider: Provider = {
  provide: DATABASE_CONNECTION,
  useFactory: async () => {
    // Create database connection
    const connection = await createConnection({
      // config
    });
    return connection;
  },
};
```

### Async Providers

```typescript
// config.module.ts
import { Module } from '@nestjs/common';
import { ConfigService } from './config.service';

@Module({
  providers: [
    {
      provide: ConfigService,
      useFactory: async () => {
        const config = await loadConfig();
        return new ConfigService(config);
      },
    },
  ],
  exports: [ConfigService],
})
export class ConfigModule {}
```

### Value Providers

```typescript
const constants = {
  API_VERSION: 'v1',
  MAX_RETRIES: 3,
};

@Module({
  providers: [
    {
      provide: 'CONSTANTS',
      useValue: constants,
    },
  ],
})
export class AppModule {}
```

### Class Providers

```typescript
@Module({
  providers: [
    {
      provide: 'CONFIG_SERVICE',
      useClass: process.env.NODE_ENV === 'production'
        ? ProductionConfigService
        : DevelopmentConfigService,
    },
  ],
})
export class AppModule {}
```

---

## Dynamic Modules

### Creating Dynamic Modules

```typescript
// cache.module.ts
import { Module, DynamicModule } from '@nestjs/common';

export interface CacheModuleOptions {
  host: string;
  port: number;
  ttl?: number;
}

@Module({})
export class CacheModule {
  static forRoot(options: CacheModuleOptions): DynamicModule {
    return {
      module: CacheModule,
      providers: [
        {
          provide: 'CACHE_OPTIONS',
          useValue: options,
        },
        CacheService,
      ],
      exports: [CacheService],
      global: true,
    };
  }

  static forRootAsync(options: {
    imports?: any[];
    useFactory: (...args: any[]) => Promise<CacheModuleOptions> | CacheModuleOptions;
    inject?: any[];
  }): DynamicModule {
    return {
      module: CacheModule,
      imports: options.imports || [],
      providers: [
        {
          provide: 'CACHE_OPTIONS',
          useFactory: options.useFactory,
          inject: options.inject || [],
        },
        CacheService,
      ],
      exports: [CacheService],
      global: true,
    };
  }
}
```

### Using Dynamic Modules

```typescript
// Synchronous
CacheModule.forRoot({
  host: 'localhost',
  port: 6379,
  ttl: 3600,
});

// Asynchronous
CacheModule.forRootAsync({
  imports: [ConfigModule],
  useFactory: (configService: ConfigService) => ({
    host: configService.get('REDIS_HOST'),
    port: configService.get('REDIS_PORT'),
  }),
  inject: [ConfigService],
});
```

---

## Microservices

### Setting Up Microservices

```bash
npm install @nestjs/microservices
```

### Creating a Microservice

```typescript
// main.ts (microservice)
import { NestFactory } from '@nestjs/core';
import { MicroserviceOptions, Transport } from '@nestjs/microservices';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.createMicroservice<MicroserviceOptions>(
    AppModule,
    {
      transport: Transport.TCP,
      options: {
        host: 'localhost',
        port: 3001,
      },
    },
  );

  await app.listen();
}
bootstrap();
```

### Message Patterns

```typescript
// users.controller.ts
import { Controller } from '@nestjs/common';
import { MessagePattern, Payload } from '@nestjs/microservices';

@Controller()
export class UsersController {
  @MessagePattern({ cmd: 'get_user' })
  getUser(@Payload() data: { id: string }) {
    return { id: data.id, name: 'John Doe' };
  }

  @MessagePattern({ cmd: 'create_user' })
  createUser(@Payload() data: any) {
    return { id: Date.now(), ...data };
  }
}
```

### Client-Side

```typescript
// app.module.ts
import { ClientsModule, Transport } from '@nestjs/microservices';

@Module({
  imports: [
    ClientsModule.register([
      {
        name: 'USER_SERVICE',
        transport: Transport.TCP,
        options: {
          host: 'localhost',
          port: 3001,
        },
      },
    ]),
  ],
})
export class AppModule {}
```

```typescript
// app.controller.ts
import { Controller, Get, Inject } from '@nestjs/common';
import { ClientProxy } from '@nestjs/microservices';

@Controller()
export class AppController {
  constructor(
    @Inject('USER_SERVICE') private client: ClientProxy,
  ) {}

  @Get()
  async getUsers() {
    return this.client.send({ cmd: 'get_user' }, { id: '1' });
  }
}
```

### RabbitMQ Transport

```typescript
// RabbitMQ microservice
const app = await NestFactory.createMicroservice<MicroserviceOptions>(
  AppModule,
  {
    transport: Transport.RMQ,
    options: {
      urls: ['amqp://localhost:5672'],
      queue: 'users_queue',
      queueOptions: {
        durable: false,
      },
    },
  },
);
```

---

## WebSockets

### Setting Up WebSockets

```bash
npm install @nestjs/websockets @nestjs/platform-socket.io socket.io
```

### Gateway

```typescript
// chat.gateway.ts
import {
  WebSocketGateway,
  WebSocketServer,
  SubscribeMessage,
  OnGatewayConnection,
  OnGatewayDisconnect,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';

@WebSocketGateway({
  cors: {
    origin: '*',
  },
})
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer()
  server: Server;

  handleConnection(client: Socket) {
    console.log(`Client connected: ${client.id}`);
  }

  handleDisconnect(client: Socket) {
    console.log(`Client disconnected: ${client.id}`);
  }

  @SubscribeMessage('message')
  handleMessage(client: Socket, payload: any) {
    // Broadcast to all clients
    this.server.emit('message', {
      id: client.id,
      ...payload,
    });
  }

  @SubscribeMessage('join_room')
  handleJoinRoom(client: Socket, room: string) {
    client.join(room);
    this.server.to(room).emit('user_joined', client.id);
  }
}
```

### Using WebSockets in Frontend

```javascript
// Frontend example
const socket = io('http://localhost:3000');

socket.on('connect', () => {
  console.log('Connected to server');
});

socket.emit('message', { text: 'Hello!' });

socket.on('message', (data) => {
  console.log('Received:', data);
});
```

---

## Testing

### Unit Testing

```typescript
// users.service.spec.ts
import { Test, TestingModule } from '@nestjs/testing';
import { UsersService } from './users.service';

describe('UsersService', () => {
  let service: UsersService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [UsersService],
    }).compile();

    service = module.get<UsersService>(UsersService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });

  it('should create a user', () => {
    const user = service.create({ name: 'John', email: 'john@example.com' });
    expect(user).toHaveProperty('id');
    expect(user.name).toBe('John');
  });
});
```

### E2E Testing

```typescript
// users.e2e-spec.ts
import { Test, TestingModule } from '@nestjs/testing';
import { INestApplication } from '@nestjs/common';
import * as request from 'supertest';
import { AppModule } from './../src/app.module';

describe('UsersController (e2e)', () => {
  let app: INestApplication;

  beforeEach(async () => {
    const moduleFixture: TestingModule = await Test.createTestingModule({
      imports: [AppModule],
    }).compile();

    app = moduleFixture.createNestApplication();
    await app.init();
  });

  it('/users (GET)', () => {
    return request(app.getHttpServer())
      .get('/users')
      .expect(200)
      .expect((res) => {
        expect(Array.isArray(res.body)).toBe(true);
      });
  });

  it('/users (POST)', () => {
    return request(app.getHttpServer())
      .post('/users')
      .send({ name: 'John', email: 'john@example.com' })
      .expect(201)
      .expect((res) => {
        expect(res.body).toHaveProperty('id');
      });
  });
});
```

### Mocking

```typescript
// users.controller.spec.ts
import { Test, TestingModule } from '@nestjs/testing';
import { UsersController } from './users.controller';
import { UsersService } from './users.service';

describe('UsersController', () => {
  let controller: UsersController;
  let service: UsersService;

  const mockUsersService = {
    findAll: jest.fn(() => []),
    findOne: jest.fn((id) => ({ id, name: 'John' })),
    create: jest.fn((dto) => ({ id: '1', ...dto })),
  };

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [UsersController],
      providers: [
        {
          provide: UsersService,
          useValue: mockUsersService,
        },
      ],
    }).compile();

    controller = module.get<UsersController>(UsersController);
    service = module.get<UsersService>(UsersService);
  });

  it('should return all users', () => {
    expect(controller.findAll()).toEqual([]);
    expect(mockUsersService.findAll).toHaveBeenCalled();
  });
});
```

---

## Database Integration

### TypeORM Setup

```bash
npm install @nestjs/typeorm typeorm mysql2
```

```typescript
// app.module.ts
import { TypeOrmModule } from '@nestjs/typeorm';

@Module({
  imports: [
    TypeOrmModule.forRoot({
      type: 'mysql',
      host: 'localhost',
      port: 3306,
      username: 'root',
      password: 'password',
      database: 'test',
      entities: [User],
      synchronize: true, // Only for development
    }),
    UsersModule,
  ],
})
export class AppModule {}
```

### Entity

```typescript
// user.entity.ts
import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity()
export class User {
  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  name: string;

  @Column({ unique: true })
  email: string;

  @Column({ default: true })
  isActive: boolean;
}
```

### Repository Pattern

```typescript
// users.service.ts
import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from './user.entity';

@Injectable()
export class UsersService {
  constructor(
    @InjectRepository(User)
    private usersRepository: Repository<User>,
  ) {}

  findAll(): Promise<User[]> {
    return this.usersRepository.find();
  }

  findOne(id: number): Promise<User> {
    return this.usersRepository.findOne({ where: { id } });
  }

  async create(createUserDto: CreateUserDto): Promise<User> {
    const user = this.usersRepository.create(createUserDto);
    return this.usersRepository.save(user);
  }

  async remove(id: number): Promise<void> {
    await this.usersRepository.delete(id);
  }
}
```

### Prisma Setup

```bash
npm install prisma @prisma/client
npx prisma init
```

```typescript
// prisma.service.ts
import { Injectable, OnModuleInit } from '@nestjs/common';
import { PrismaClient } from '@prisma/client';

@Injectable()
export class PrismaService extends PrismaClient implements OnModuleInit {
  async onModuleInit() {
    await this.$connect();
  }
}
```

---

## Performance Optimization

### Caching

```typescript
// app.module.ts
import { CacheModule } from '@nestjs/cache-manager';
import { redisStore } from 'cache-manager-redis-store';

@Module({
  imports: [
    CacheModule.register({
      store: redisStore,
      host: 'localhost',
      port: 6379,
      ttl: 300,
    }),
  ],
})
export class AppModule {}
```

```typescript
// users.controller.ts
import { CacheKey, CacheTTL } from '@nestjs/cache-manager';
import { UseInterceptors, CacheInterceptor } from '@nestjs/common';

@Controller('users')
@UseInterceptors(CacheInterceptor)
export class UsersController {
  @Get()
  @CacheKey('users')
  @CacheTTL(60)
  findAll() {
    return this.usersService.findAll();
  }
}
```

### Compression

```bash
npm install compression
```

```typescript
// main.ts
import * as compression from 'compression';

app.use(compression());
```

### Rate Limiting

```bash
npm install @nestjs/throttler
```

```typescript
// app.module.ts
import { ThrottlerModule } from '@nestjs/throttler';

@Module({
  imports: [
    ThrottlerModule.forRoot({
      ttl: 60,
      limit: 10,
    }),
  ],
})
export class AppModule {}
```

---

## Security Best Practices

### Helmet

```bash
npm install helmet
```

```typescript
// main.ts
import helmet from 'helmet';

app.use(helmet());
```

### CSRF Protection

```bash
npm install csurf
```

```typescript
// main.ts
import * as csurf from 'csurf';

app.use(csurf());
```

### Input Sanitization

```typescript
// sanitize.pipe.ts
import { PipeTransform, Injectable, BadRequestException } from '@nestjs/common';

@Injectable()
export class SanitizePipe implements PipeTransform {
  transform(value: any) {
    if (typeof value === 'string') {
      return value.trim().replace(/<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi, '');
    }
    return value;
  }
}
```

### Password Hashing

```bash
npm install bcrypt
npm install --save-dev @types/bcrypt
```

```typescript
import * as bcrypt from 'bcrypt';

async hashPassword(password: string): Promise<string> {
  const salt = await bcrypt.genSalt(10);
  return bcrypt.hash(password, salt);
}

async comparePassword(password: string, hash: string): Promise<boolean> {
  return bcrypt.compare(password, hash);
}
```

---

## Exercises

1. Create a dynamic module for email service configuration
2. Implement a microservice for handling notifications
3. Build a WebSocket gateway for real-time chat
4. Write comprehensive unit and E2E tests
5. Integrate a database and implement full CRUD operations
6. Add caching and rate limiting to your API

---

## Next Steps

Now that you've mastered advanced concepts, practice by:
- Building a complete full-stack application
- Implementing authentication and authorization
- Deploying to production
- Monitoring and logging

