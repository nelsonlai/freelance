import express from 'express';
import cors from 'cors';
import helmet from 'helmet';
import rateLimit from 'express-rate-limit';
import recordRoutes from './routes/recordRoutes';
import userRoutes from './routes/userRoutes';
import { errorHandler, notFoundHandler } from './middleware/errorHandler';
import { requestLogger } from './middleware/requestLogger';
import logger from './utils/logger';

const app = express();
const PORT = process.env.PORT || 4000;

// Request logging middleware
app.use(requestLogger);

// Security middleware
app.use(helmet());

// CORS configuration
// CORS configuration: when CORS_ORIGIN is set, use it; otherwise reflect origin (allow dev ports)
const corsOrigin = process.env.CORS_ORIGIN || undefined;
app.use(cors({
  origin: corsOrigin ?? true,
  credentials: true
}));

// Rate limiting
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  max: 100, // limit each IP to 100 requests per windowMs
  message: {
    error: {
      code: 'RATE_LIMIT_EXCEEDED',
      message: 'Too many requests from this IP, please try again later.'
    }
  }
});
app.use('/api/', limiter);

// Body parsing middleware
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true, limit: '10mb' }));

// Health check endpoint
app.get('/health', (req, res) => {
  logger.info('🏥 Health check requested');
  res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

// API routes for records
app.use('/api/v1/records', recordRoutes);

// API routes for users
app.use('/api/v1/users', userRoutes);

// API routes for authentication
app.use('/api/v1/auth', authRoutes);

// API routes for emails
app.use('/api/v1/emails', emailRoutes);

// API routes for google forms
app.use('/api/v1/googleforms', googleFormRoutes);

// API photos routes
app.use('/api/v1/photos', photoRoutes);

// API routes for catmatcher
app.use('/api/v1/catmatcher', catMatcherRoutes);

// API routes for opionions
app.use('/api/v1/opinions', opinionRoutes);

// 404 handler
app.use(notFoundHandler);

// Error handling middleware
app.use(errorHandler);

// Graceful shutdown
process.on('SIGTERM', () => {
  logger.info('🛑 SIGTERM received, shutting down gracefully');
  process.exit(0);
});

process.on('SIGINT', () => {
  logger.info('🛑 SIGINT received, shutting down gracefully');
  process.exit(0);
});

// Start server
app.listen(PORT, () => {
  logger.info('🚀 Backend server started', {
    port: PORT,
    environment: process.env.NODE_ENV || 'development',
    logLevel: process.env.LOG_LEVEL || 'INFO'
  });
  logger.info('📊 Health check available', { url: `http://localhost:${PORT}/health` });
  logger.info('🔗 API base available', { url: `http://localhost:${PORT}/api/v1` });
  logger.warn('⚠️  DEMO MODE: Passwords stored in plain text!');
});

export default app;
