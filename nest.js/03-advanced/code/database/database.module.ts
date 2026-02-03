import { Module } from '@nestjs/common';

@Module({
  providers: [
    {
      provide: 'DATABASE_CONNECTION',
      useFactory: async () => {
        // In a real application, this would create a database connection
        // For this tutorial, we'll simulate it
        console.log('Database connection established');
        return {
          type: 'postgres',
          host: 'localhost',
          port: 5432,
          connected: true,
        };
      },
    },
  ],
  exports: ['DATABASE_CONNECTION'],
})
export class DatabaseModule {}

