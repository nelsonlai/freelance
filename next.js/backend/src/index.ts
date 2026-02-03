// Main Express server entry point
// Configures all middleware, routes, and starts the server
// Implements security features and logging as specified in the SRS

import express from 'express';
import cors from 'cors';
import helmet from 'helmet';
import compression from 'compression';
import morgan from 'morgan';
import rateLimit from 'express-rate-limit';
import dotenv from 'dotenv';

// Import routes
import responsesRouter from './routes/responses';

// Load environment variables
dotenv.config();

// Create Express application
const app = express();
const PORT = process.env.PORT || 4000;

// Security middleware
// Helmet helps secure Express apps by setting various HTTP headers
app.use(helmet());

// CORS configuration
// Allow only the specified origin (Next.js frontend) as per SRS
const corsOrigin = process.env.CORS_ORIGIN || 'http://localhost:3000';
app.use(cors({
  origin: corsOrigin,
  credentials: true,
  methods: ['GET', 'POST', 'OPTIONS'],
  allowedHeaders: ['Content-Type', 'Authorization', 'x-request-id']
}));

// Rate limiting middleware
// As per SRS: basic rate limiting (e.g., 60 req/min IP)
const rateLimitWindow = parseInt(process.env.RATE_LIMIT_WINDOW_MS || '60000');
const rateLimitMax = parseInt(process.env.RATE_LIMIT_MAX_REQUESTS || '60');

const limiter = rateLimit({
  windowMs: rateLimitWindow,
  max: rateLimitMax,
  message: {
    error: {
      code: 'RATE_LIMIT_EXCEEDED',
      message: 'Too many requests from this IP, please try again later'
    }
  },
  standardHeaders: true,
  legacyHeaders: false,
  // Trust proxy for accurate IP detection
  trustProxy: true
});

app.use(limiter);

// Compression middleware for better performance
app.use(compression());

// Body parsing middleware
// Limit JSON payload size to 100kb as per SRS
app.use(express.json({ limit: '100kb' }));
app.use(express.urlencoded({ extended: true, limit: '100kb' }));

// Logging middleware
// As per SRS: Console logs + request IDs; lightweight error logs
const morganFormat = process.env.NODE_ENV === 'production' 
  ? 'combined' 
  : 'dev';

app.use(morgan(morganFormat, {
  // Add request ID to logs
  stream: {
    write: (message: string) => {
      console.log(message.trim());
    }
  }
}));

// Request ID middleware for all routes
app.use((req, res, next) => {
  const requestId = req.headers['x-request-id'] || `req_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
  req.headers['x-request-id'] = requestId as string;
  res.setHeader('x-request-id', requestId as string);
  next();
});

// Health check endpoint
app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'healthy',
    timestamp: new Date().toISOString(),
    requestId: req.headers['x-request-id']
  });
});

// API routes
// Mount the responses router under /api/v1/responses
app.use('/api/v1/responses', responsesRouter);

// 404 handler for unmatched routes
app.use('*', (req, res) => {
  res.status(404).json({
    error: {
      code: 'NOT_FOUND',
      message: 'Route not found',
      requestId: req.headers['x-request-id']
    }
  });
});

// Global error handler
app.use((error: any, req: express.Request, res: express.Response, next: express.NextFunction) => {
  console.error('Unhandled error:', error);
  
  res.status(500).json({
    error: {
      code: 'INTERNAL_SERVER_ERROR',
      message: 'An unexpected error occurred',
      requestId: req.headers['x-request-id']
    }
  });
});

// Start the server
app.listen(PORT, () => {
  console.log(`🚀 Questionnaire API server running on port ${PORT}`);
  console.log(`📊 Environment: ${process.env.NODE_ENV || 'development'}`);
  console.log(`🔒 CORS Origin: ${corsOrigin}`);
  console.log(`⏱️  Rate Limit: ${rateLimitMax} requests per ${rateLimitWindow / 1000} seconds`);
  console.log(`📝 Request ID Header: x-request-id`);
});

// Graceful shutdown handling
process.on('SIGTERM', () => {
  console.log('SIGTERM received, shutting down gracefully');
  process.exit(0);
});

process.on('SIGINT', () => {
  console.log('SIGINT received, shutting down gracefully');
  process.exit(0);
});

export default app;
