import { Request, Response, NextFunction } from 'express';
import logger from '../utils/logger';

export const requestLogger = (req: Request, res: Response, next: NextFunction) => {
  const start = Date.now();
  
  // Log the incoming request
  logger.request(req.method, req.url, req.ip);

  // Override res.end to log the response
  const originalEnd = res.end;
  res.end = function(chunk?: any, encoding?: any) {
    const responseTime = Date.now() - start;
    logger.response(req.method, req.url, res.statusCode, responseTime);
    return originalEnd.call(this, chunk, encoding);
  };

  next();
};
