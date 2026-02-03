export default () => ({
  app: {
    name: process.env.APP_NAME || 'NestJS Advanced',
    port: parseInt(process.env.PORT, 10) || 3000,
    env: process.env.NODE_ENV || 'development',
  },
  database: {
    host: process.env.DATABASE_HOST || 'localhost',
    port: parseInt(process.env.DATABASE_PORT, 10) || 5432,
    name: process.env.DATABASE_NAME || 'nestjs_db',
  },
  cache: {
    host: process.env.CACHE_HOST || 'localhost',
    port: parseInt(process.env.CACHE_PORT, 10) || 6379,
    ttl: parseInt(process.env.CACHE_TTL, 10) || 300,
  },
});

