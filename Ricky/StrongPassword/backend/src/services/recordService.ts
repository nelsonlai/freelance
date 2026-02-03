import { PrismaClient, Record } from '@prisma/client';
import { CreateRecordInput, UpdateRecordInput } from '../validation/schemas';
import logger from '../utils/logger';

export class RecordService {
  private prisma: PrismaClient;

  constructor() {
    this.prisma = new PrismaClient();
  }

  async createRecord(data: CreateRecordInput): Promise<Record> {
    logger.db('CREATE', 'record', { username: data.username, email: data.email });
    
    // Check for existing username (case-insensitive)
    // Use a simple equality check here to be compatible with the installed Prisma client.
    // If case-insensitive checks are required, normalize values before comparing or enable
    // appropriate database/collation settings.
    const existingUsername = await this.prisma.record.findFirst({
      where: {
        username: data.username
      }
    });

    if (existingUsername) {
      logger.warn('⚠️ Username already exists', { username: data.username });
      throw new Error('Username already exists');
    }

    // Check for existing email (case-insensitive)
    const existingEmail = await this.prisma.record.findFirst({
      where: {
        email: data.email
      }
    });

    if (existingEmail) {
      logger.warn('⚠️ Email already exists', { email: data.email });
      throw new Error('Email already exists');
    }

    const record = await this.prisma.record.create({
      data: {
        username: data.username,
        email: data.email,
        password: data.password // Store as plain text for demo
      }
    });

    logger.db('CREATED', 'record', { id: record.id, username: record.username });
    return record;
  }

  async getAllRecords(includePassword: boolean = false): Promise<{ items: any[], total: number }> {
    const records = await this.prisma.record.findMany({
      orderBy: { createdAt: 'desc' }
    });

    const items = records.map(record => {
      const baseRecord = {
        id: record.id,
        username: record.username,
        email: record.email,
        createdAt: record.createdAt.toISOString(),
        updatedAt: record.updatedAt.toISOString()
      };

      if (includePassword) {
        return { ...baseRecord, password: record.password };
      }

      return baseRecord;
    });

    return { items, total: records.length };
  }

  async getRecordById(id: string, includePassword: boolean = false): Promise<any> {
    const record = await this.prisma.record.findUnique({
      where: { id }
    });

    if (!record) {
      throw new Error('Record not found');
    }

    const baseRecord = {
      id: record.id,
      username: record.username,
      email: record.email,
      createdAt: record.createdAt.toISOString(),
      updatedAt: record.updatedAt.toISOString()
    };

    if (includePassword) {
      return { ...baseRecord, password: record.password };
    }

    return baseRecord;
  }

  async updateRecord(id: string, data: UpdateRecordInput): Promise<any> {
    // Check if record exists
    const existingRecord = await this.prisma.record.findUnique({
      where: { id }
    });

    if (!existingRecord) {
      throw new Error('Record not found');
    }

    // Check for username conflicts if updating username
    if (data.username && data.username !== existingRecord.username) {
      const existingUsername = await this.prisma.record.findFirst({
        where: {
          username: data.username,
          id: { not: id }
        }
      });

      if (existingUsername) {
        throw new Error('Username already exists');
      }
    }

    // Check for email conflicts if updating email
    if (data.email && data.email !== existingRecord.email) {
      const existingEmail = await this.prisma.record.findFirst({
        where: {
          email: data.email,
          id: { not: id }
        }
      });

      if (existingEmail) {
        throw new Error('Email already exists');
      }
    }

    const updatedRecord = await this.prisma.record.update({
      where: { id },
      data: {
        ...(data.username && { username: data.username }),
        ...(data.email && { email: data.email }),
        ...(data.password && { password: data.password }) // Store as plain text for demo
      }
    });

    return {
      id: updatedRecord.id,
      username: updatedRecord.username,
      email: updatedRecord.email,
      createdAt: updatedRecord.createdAt.toISOString(),
      updatedAt: updatedRecord.updatedAt.toISOString()
    };
  }

  async deleteRecord(id: string): Promise<void> {
    const existingRecord = await this.prisma.record.findUnique({
      where: { id }
    });

    if (!existingRecord) {
      throw new Error('Record not found');
    }

    await this.prisma.record.delete({
      where: { id }
    });
  }

  async disconnect(): Promise<void> {
    await this.prisma.$disconnect();
  }
}
