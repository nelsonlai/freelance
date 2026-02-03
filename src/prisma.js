/**
 * Prisma Client singleton to avoid multiple instances in dev (nodemon).
 */
const { PrismaClient } = require('@prisma/client');
const globalForPrisma = globalThis;
const prisma = globalForPrisma._prisma || new PrismaClient();
if (process.env.NODE_ENV !== 'production') globalForPrisma._prisma = prisma;
module.exports = { prisma };
