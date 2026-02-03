import { Request, Response, NextFunction } from 'express';
import { ErrorResponse } from '../types';

export interface AppError extends Error {
  statusCode?: number;
  code?: string;
  details?: any;
}

export const errorHandler = (
  error: AppError,
  req: Request,
  res: Response,
  next: NextFunction
) => {
  console.error('Error:', error);

  let statusCode = error.statusCode || 500;
  let code = error.code || 'INTERNAL_ERROR';
  let message = error.message || 'Internal server error';
  let details = error.details;

  // Handle Prisma errors
  if (error.name === 'PrismaClientKnownRequestError') {
    statusCode = 400;
    code = 'BAD_REQUEST';
    message = 'Database operation failed';
  }

  // Handle validation errors
  if (error.name === 'ZodError') {
    statusCode = 400;
    code = 'VALIDATION_ERROR';
    message = 'Validation failed';
  }

  const errorResponse: ErrorResponse = {
    error: {
      code: code as any,
      message,
      details
    }
  };

  res.status(statusCode).json(errorResponse);
};

export const notFoundHandler = (req: Request, res: Response) => {
  const errorResponse: ErrorResponse = {
    error: {
      code: 'NOT_FOUND',
      message: `Route ${req.method} ${req.path} not found`
    }
  };
  
  res.status(404).json(errorResponse);
};
