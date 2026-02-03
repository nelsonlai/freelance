// Jest setup file for backend tests
import { PrismaClient } from '@prisma/client';

// Mock Prisma client for tests
jest.mock('@prisma/client', () => ({
  PrismaClient: jest.fn().mockImplementation(() => ({
    record: {
      create: jest.fn(),
      findMany: jest.fn(),
      findUnique: jest.fn(),
      update: jest.fn(),
      delete: jest.fn(),
      findFirst: jest.fn(),
    },
    $disconnect: jest.fn(),
  })),
}));

// Global test setup
beforeAll(() => {
  // Setup any global test configuration
});

afterAll(() => {
  // Cleanup after all tests
});

afterEach(() => {
  // Cleanup after each test
  jest.clearAllMocks();
});
