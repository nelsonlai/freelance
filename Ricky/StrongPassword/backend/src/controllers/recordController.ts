import { Request, Response } from 'express';
import { RecordService } from '../services/recordService';
import { createRecordSchema, updateRecordSchema } from '../validation/schemas';
import { ErrorResponse } from '../types';
import logger from '../utils/logger';

export class RecordController {
  private recordService: RecordService;

  constructor() {
    this.recordService = new RecordService();
  }

  private sendErrorResponse(res: Response, code: string, message: string, details?: any, statusCode: number = 400) {
    const errorResponse: ErrorResponse = {
      error: {
        code: code as any,
        message,
        details
      }
    };
    res.status(statusCode).json(errorResponse);
  }
  
  async createRecord(req: Request, res: Response) {
    try {
      logger.info('📝 Creating new record', { username: req.body.username, email: req.body.email });
      
      const validationResult = createRecordSchema.safeParse(req.body);
      
      if (!validationResult.success) {
        const errors = validationResult.error.errors.map(err => ({
          field: err.path.join('.'),
          message: err.message
        }));
        
        logger.warn('❌ Record creation validation failed', { errors });
        return this.sendErrorResponse(
          res, 
          'VALIDATION_ERROR', 
          'Validation failed', 
          { errors }, 
          400
        );
      }

      const record = await this.recordService.createRecord(validationResult.data);
      
      logger.info('✅ Record created successfully', { id: record.id, username: record.username });
      
      res.status(201).json({
        id: record.id,
        username: record.username,
        email: record.email,
        createdAt: record.createdAt.toISOString(),
        updatedAt: record.updatedAt.toISOString()
      });
    } catch (error: any) {
      if (error.message === 'Username already exists' || error.message === 'Email already exists') {
        logger.warn('⚠️ Record creation conflict', { error: error.message });
        return this.sendErrorResponse(res, 'CONFLICT', error.message, { field: error.message.includes('Username') ? 'username' : 'email' }, 409);
      }
      
      logger.error('💥 Create record error', { error: error.message, stack: error.stack });
      this.sendErrorResponse(res, 'INTERNAL_ERROR', 'Internal server error', {}, 500);
    }
  }

  async getAllRecords(req: Request, res: Response) {
    try {
      const includePassword = req.query.includePassword === 'true';
      logger.info('📋 Fetching all records', { includePassword });
      
      const result = await this.recordService.getAllRecords(includePassword);
      
      logger.info('✅ Records fetched successfully', { count: result.total });
      res.json(result);
    } catch (error: any) {
      logger.error('💥 Get all records error', { error: error.message, stack: error.stack });
      this.sendErrorResponse(res, 'INTERNAL_ERROR', 'Internal server error', {}, 500);
    }
  }

  async getRecordById(req: Request, res: Response) {
    try {
      const { id } = req.params;
      const includePassword = req.query.includePassword === 'true';
      
      logger.info('🔍 Fetching record by ID', { id, includePassword });
      
      const record = await this.recordService.getRecordById(id, includePassword);
      
      logger.info('✅ Record fetched successfully', { id: record.id, username: record.username });
      res.json(record);
    } catch (error: any) {
      if (error.message === 'Record not found') {
        logger.warn('⚠️ Record not found', { id: req.params.id });
        return this.sendErrorResponse(res, 'NOT_FOUND', 'Record not found', {}, 404);
      }
      
      logger.error('💥 Get record by ID error', { id: req.params.id, error: error.message, stack: error.stack });
      this.sendErrorResponse(res, 'INTERNAL_ERROR', 'Internal server error', {}, 500);
    }
  }

  async updateRecord(req: Request, res: Response) {
    try {
      const { id } = req.params;
      logger.info('✏️ Updating record', { id, updates: Object.keys(req.body) });
      
      const validationResult = updateRecordSchema.safeParse(req.body);
      
      if (!validationResult.success) {
        const errors = validationResult.error.errors.map(err => ({
          field: err.path.join('.'),
          message: err.message
        }));
        
        logger.warn('❌ Record update validation failed', { id, errors });
        return this.sendErrorResponse(
          res, 
          'VALIDATION_ERROR', 
          'Validation failed', 
          { errors }, 
          400
        );
      }

      const record = await this.recordService.updateRecord(id, validationResult.data);
      
      logger.info('✅ Record updated successfully', { id: record.id, username: record.username });
      res.json(record);
    } catch (error: any) {
      if (error.message === 'Record not found') {
        logger.warn('⚠️ Record not found for update', { id: req.params.id });
        return this.sendErrorResponse(res, 'NOT_FOUND', 'Record not found', {}, 404);
      }
      
      if (error.message === 'Username already exists' || error.message === 'Email already exists') {
        logger.warn('⚠️ Record update conflict', { id: req.params.id, error: error.message });
        return this.sendErrorResponse(res, 'CONFLICT', error.message, { field: error.message.includes('Username') ? 'username' : 'email' }, 409);
      }
      
      logger.error('💥 Update record error', { id: req.params.id, error: error.message, stack: error.stack });
      this.sendErrorResponse(res, 'INTERNAL_ERROR', 'Internal server error', {}, 500);
    }
  }

  async deleteRecord(req: Request, res: Response) {
    try {
      const { id } = req.params;
      logger.info('🗑️ Deleting record', { id });
      
      await this.recordService.deleteRecord(id);
      
      logger.info('✅ Record deleted successfully', { id });
      res.status(204).send();
    } catch (error: any) {
      if (error.message === 'Record not found') {
        logger.warn('⚠️ Record not found for deletion', { id: req.params.id });
        return this.sendErrorResponse(res, 'NOT_FOUND', 'Record not found', {}, 404);
      }
      
      logger.error('💥 Delete record error', { id: req.params.id, error: error.message, stack: error.stack });
      this.sendErrorResponse(res, 'INTERNAL_ERROR', 'Internal server error', {}, 500);
    }
  }
}
