// API routes for questionnaire responses
// Implements the three main endpoints specified in the SRS:
// POST /api/v1/responses - Create a response
// GET /api/v1/responses/:id - Fetch one response
// GET /api/v1/metrics - Get aggregated metrics

import { Router, Request, Response } from 'express';
import { CreateResponseSchema, MetricsQuerySchema } from '../schemas/validation';
import { createResponse, getResponseById, getMetrics } from '../services/responseService';
import { generateRequestId } from '../utils/security';

const router = Router();

// Middleware to add request ID to all requests
router.use((req: Request, res: Response, next) => {
  const requestId = req.headers['x-request-id'] as string || generateRequestId();
  req.headers['x-request-id'] = requestId;
  res.setHeader('x-request-id', requestId);
  next();
});

/**
 * POST /api/v1/responses
 * Creates a new questionnaire response
 * As per SRS: Returns 201 Created with response ID
 */
router.post('/', async (req: Request, res: Response) => {
  try {
    // Validate the request body using Zod schema
    const validationResult = CreateResponseSchema.safeParse(req.body);
    
    if (!validationResult.success) {
      return res.status(422).json({
        error: {
          code: 'VALIDATION_ERROR',
          message: 'Invalid request data',
          details: validationResult.error.errors
        }
      });
    }

    // Extract user agent and IP address from request
    const userAgent = req.get('User-Agent');
    const ipAddress = req.ip || req.connection.remoteAddress || req.socket.remoteAddress;
    const ipSalt = process.env.IP_SALT;

    // Create the response in the database
    const response = await createResponse(
      validationResult.data,
      userAgent,
      ipAddress,
      ipSalt
    );

    // Return success response as per SRS specification
    return res.status(201).json({
      id: response.id,
      createdAt: response.createdAt
    });

  } catch (error) {
    console.error('Error creating response:', error);
    return res.status(500).json({
      error: {
        code: 'INTERNAL_SERVER_ERROR',
        message: 'An unexpected error occurred'
      }
    });
  }
});

/**
 * GET /api/v1/responses/:id
 * Retrieves a single response by ID
 * As per SRS: Returns the stored document (no PII)
 */
router.get('/:id', async (req: Request, res: Response) => {
  try {
    const { id } = req.params;

    // Validate ID parameter
    if (!id || typeof id !== 'string') {
      return res.status(400).json({
        error: {
          code: 'INVALID_ID',
          message: 'Invalid response ID'
        }
      });
    }

    // Retrieve the response from the database
    const response = await getResponseById(id);

    if (!response) {
      return res.status(404).json({
        error: {
          code: 'RESPONSE_NOT_FOUND',
          message: 'Response not found'
        }
      });
    }

    // Return the response data
    return res.status(200).json(response);

  } catch (error) {
    console.error('Error retrieving response:', error);
    return res.status(500).json({
      error: {
        code: 'INTERNAL_SERVER_ERROR',
        message: 'An unexpected error occurred'
      }
    });
  }
});

/**
 * GET /api/v1/metrics
 * Returns aggregated metrics for all responses
 * As per SRS: Returns simple counts per question option and total submissions
 */
router.get('/metrics', async (req: Request, res: Response) => {
  try {
    // Validate query parameters using Zod schema
    const validationResult = MetricsQuerySchema.safeParse(req.query);
    
    if (!validationResult.success) {
      return res.status(400).json({
        error: {
          code: 'INVALID_QUERY_PARAMS',
          message: 'Invalid query parameters',
          details: validationResult.error.errors
        }
      });
    }

    // Get metrics from the database
    const metrics = await getMetrics(validationResult.data);

    // Return the metrics data
    return res.status(200).json(metrics);

  } catch (error) {
    console.error('Error retrieving metrics:', error);
    return res.status(500).json({
      error: {
        code: 'INTERNAL_SERVER_ERROR',
        message: 'An unexpected error occurred'
      }
    });
  }
});

export default router;
