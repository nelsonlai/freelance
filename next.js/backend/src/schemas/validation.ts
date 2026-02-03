// Validation schemas using Zod for type-safe API validation
// These schemas ensure data integrity and match the SRS requirements

import { z } from 'zod';

// Schema for individual question answers
// As per SRS: q1 (single choice), q2 (multi select), q3 (short text)
export const QuestionAnswerSchema = z.object({
  q1: z.enum(['A', 'B', 'C'], {
    required_error: 'Question 1 is required',
    invalid_type_error: 'Question 1 must be A, B, or C'
  }),
  q2: z.array(z.enum(['X', 'Y', 'Z']))
    .max(3, 'Question 2 can have maximum 3 selections')
    .optional()
    .default([]),
  q3: z.string()
    .max(500, 'Question 3 text cannot exceed 500 characters')
    .optional()
    .default('')
});

// Schema for the complete response payload
export const CreateResponseSchema = z.object({
  answers: QuestionAnswerSchema
});

// Schema for response retrieval (what gets returned from GET endpoints)
export const ResponseSchema = z.object({
  id: z.string(),
  answers: QuestionAnswerSchema,
  createdAt: z.date(),
  userAgent: z.string().optional(),
  ipHash: z.string().optional()
});

// Schema for metrics query parameters
export const MetricsQuerySchema = z.object({
  from: z.string().datetime().optional(),
  to: z.string().datetime().optional()
});

// Schema for error responses
export const ErrorResponseSchema = z.object({
  error: z.object({
    code: z.string(),
    message: z.string(),
    details: z.any().optional()
  })
});

// Type exports for use in other parts of the application
export type CreateResponseRequest = z.infer<typeof CreateResponseSchema>;
export type ResponseData = z.infer<typeof ResponseSchema>;
export type MetricsQuery = z.infer<typeof MetricsQuerySchema>;
export type ErrorResponse = z.infer<typeof ErrorResponseSchema>;
