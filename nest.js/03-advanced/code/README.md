# Advanced Level - Complete Code Examples

This directory contains complete, runnable code examples demonstrating advanced NestJS concepts.

## 📁 File Structure

```
code/
├── main.ts
├── app.module.ts
├── app.controller.ts
├── app.service.ts
├── config/
│   └── configuration.ts
├── common/
│   ├── decorators/
│   │   └── current-user.decorator.ts
│   ├── filters/
│   │   └── all-exceptions.filter.ts
│   └── interceptors/
│       ├── transform.interceptor.ts
│       └── logging.interceptor.ts
├── products/
│   ├── products.module.ts
│   ├── products.controller.ts
│   ├── products.service.ts
│   ├── products.service.spec.ts
│   └── dto/
│       └── create-product.dto.ts
├── cache/
│   ├── cache.module.ts
│   └── cache.service.ts
└── database/
    └── database.module.ts
```

## 🚀 How to Run

1. Copy these files to your NestJS project
2. Install dependencies:
   ```bash
   npm install @nestjs/config @nestjs/swagger
   ```
3. Run: `npm run start:dev`
4. Test the API at `http://localhost:3000`
5. View Swagger docs at `http://localhost:3000/api` (if Swagger is configured)

## 📝 API Endpoints

- `GET /products` - Get all products (cached, supports ?category=electronics)
- `GET /products/:id` - Get a specific product (cached)
- `POST /products` - Create a new product
- `PUT /products/:id` - Update a product
- `DELETE /products/:id` - Delete a product

## 🧪 Test with cURL

```bash
# Get all products
curl http://localhost:3000/products

# Get products by category
curl "http://localhost:3000/products?category=electronics"

# Get a specific product
curl http://localhost:3000/products/1

# Create a product
curl -X POST http://localhost:3000/products \
  -H "Content-Type: application/json" \
  -d '{
    "name": "Tablet",
    "description": "High-end tablet",
    "price": 499.99,
    "stock": 15,
    "category": "electronics"
  }'

# Update a product
curl -X PUT http://localhost:3000/products/1 \
  -H "Content-Type: application/json" \
  -d '{
    "price": 899.99,
    "stock": 8
  }'

# Delete a product
curl -X DELETE http://localhost:3000/products/1
```

## 📚 Learning Points

1. **Dynamic Modules**: CacheModule.forRoot() pattern
2. **Custom Providers**: Factory providers for database connection
3. **Configuration Management**: @nestjs/config with environment variables
4. **Custom Decorators**: @CurrentUser() parameter decorator
5. **Advanced Interceptors**: Logging and transformation
6. **Exception Filters**: Global error handling with logging
7. **Caching**: In-memory cache implementation
8. **Testing**: Unit tests with mocking
9. **Swagger/OpenAPI**: API documentation (if configured)

## 🔧 Advanced Features

### Dynamic Module Pattern
```typescript
CacheModule.forRoot({
  host: 'localhost',
  port: 6379,
  ttl: 300,
})
```

### Custom Parameter Decorator
```typescript
@Get('profile')
getProfile(@CurrentUser() user: any) {
  return user;
}
```

### Factory Provider
```typescript
{
  provide: 'DATABASE_CONNECTION',
  useFactory: async () => {
    // Create connection
  },
}
```

### Configuration Service
```typescript
constructor(private configService: ConfigService) {
  const port = this.configService.get<number>('app.port');
}
```

## 🧪 Running Tests

```bash
npm run test
npm run test:watch
npm run test:cov
```

## 📖 Additional Notes

- The cache service uses in-memory storage for tutorial purposes
- In production, use Redis or similar caching solution
- Database module simulates connection (replace with real DB in production)
- All endpoints are documented with Swagger decorators
- Global interceptors and filters are applied automatically

