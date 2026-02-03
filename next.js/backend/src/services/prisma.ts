// Prisma client service for database operations
// This service provides a singleton instance of PrismaClient
// and handles database connections and disconnections

import { PrismaClient } from '@prisma/client';

// Create a global variable to store the PrismaClient instance
// This prevents multiple instances during hot reloads in development
declare global {
  var __prisma: PrismaClient | undefined;
}

// Initialize PrismaClient
// Use existing instance if available (for hot reloads), otherwise create new one
export const prisma = globalThis.__prisma || new PrismaClient({
  log: process.env.NODE_ENV === 'development' ? ['query', 'error', 'warn'] : ['error'],
});

// Store the instance globally in development
if (process.env.NODE_ENV === 'development') {
  globalThis.__prisma = prisma;
}

// Graceful shutdown handler
// Ensures database connections are properly closed when the application shuts down
process.on('beforeExit', async () => {
  await prisma.$disconnect();
});

// Export the PrismaClient instance for use in other parts of the application
export default prisma;
