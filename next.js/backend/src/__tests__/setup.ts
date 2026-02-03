// Test setup file for Jest
// Configures the testing environment and global test utilities

import { PrismaClient } from '@prisma/client';

// Mock Prisma client for testing
jest.mock('@prisma/client', () => ({
  PrismaClient: jest.fn().mockImplementation(() => ({
    response: {
      create: jest.fn(),
      findUnique: jest.fn(),
      findMany: jest.fn(),
      count: jest.fn(),
      delete: jest.fn(),
    },
    $disconnect: jest.fn(),
  })),
}));

// Global test timeout
jest.setTimeout(10000);

// Clean up after each test
afterEach(() => {
  jest.clearAllMocks();
});

// Global test utilities
global.testUtils = {
  // Helper to create mock response data
  createMockResponse: (overrides = {}) => ({
    id: 'test-id-123',
    answers: {
      q1: 'A',
      q2: ['X', 'Y'],
      q3: 'Test comment'
    },
    userAgent: 'Test User Agent',
    ipHash: 'test-hash',
    createdAt: new Date('2025-01-23T10:00:00Z'),
    ...overrides
  }),

  // Helper to create mock request data
  createMockRequest: (overrides = {}) => ({
    answers: {
      q1: 'A',
      q2: ['X', 'Y'],
      q3: 'Test comment'
    },
    ...overrides
  })
};

// Type declarations for global test utilities
declare global {
  var testUtils: {
    createMockResponse: (overrides?: any) => any;
    createMockRequest: (overrides?: any) => any;
  };
}
