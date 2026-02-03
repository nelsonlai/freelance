// Response service for handling questionnaire response business logic
// This service contains all the business logic for creating, retrieving, and analyzing responses
// It acts as an intermediary between the API routes and the database layer

import { prisma } from './prisma';
import { CreateResponseRequest, ResponseData, MetricsQuery } from '../schemas/validation';
import { hashIP } from '../utils/security';

/**
 * Creates a new questionnaire response in the database
 * As per SRS: POST /api/v1/responses creates a response record
 * 
 * @param data - The validated response data from the request
 * @param userAgent - Optional user agent string for analytics
 * @param ipAddress - Optional IP address to hash and store
 * @param ipSalt - Salt for hashing the IP address
 * @returns The created response with ID and timestamp
 */
export async function createResponse(
  data: CreateResponseRequest,
  userAgent?: string,
  ipAddress?: string,
  ipSalt?: string
): Promise<{ id: string; createdAt: Date }> {
  // Hash the IP address if provided and salt is available
  let ipHash: string | undefined;
  if (ipAddress && ipSalt) {
    ipHash = hashIP(ipAddress, ipSalt);
  }

  // Create the response record in the database
  const response = await prisma.response.create({
    data: {
      answers: data.answers,
      userAgent: userAgent || null,
      ipHash: ipHash || null,
    },
    select: {
      id: true,
      createdAt: true,
    },
  });

  return response;
}

/**
 * Retrieves a single response by its ID
 * As per SRS: GET /api/v1/responses/:id returns the stored document
 * 
 * @param id - The unique identifier of the response
 * @returns The response data or null if not found
 */
export async function getResponseById(id: string): Promise<ResponseData | null> {
  const response = await prisma.response.findUnique({
    where: { id },
    select: {
      id: true,
      answers: true,
      createdAt: true,
      userAgent: true,
      ipHash: true,
    },
  });

  return response;
}

/**
 * Retrieves aggregated metrics for all responses
 * As per SRS: GET /api/v1/metrics returns simple counts per question option
 * 
 * @param query - Optional date range parameters
 * @returns Aggregated metrics including total submissions and counts per question
 */
export async function getMetrics(query?: MetricsQuery) {
  // Build date filter if date range is provided
  const dateFilter: any = {};
  if (query?.from || query?.to) {
    dateFilter.createdAt = {};
    if (query.from) {
      dateFilter.createdAt.gte = new Date(query.from);
    }
    if (query.to) {
      dateFilter.createdAt.lte = new Date(query.to);
    }
  }

  // Get total submissions count
  const totalSubmissions = await prisma.response.count({
    where: dateFilter,
  });

  // Get all responses for analysis
  const responses = await prisma.response.findMany({
    where: dateFilter,
    select: {
      answers: true,
    },
  });

  // Initialize counters for each question
  const counts: any = {
    q1: { A: 0, B: 0, C: 0 },
    q2: { X: 0, Y: 0, Z: 0 },
  };

  // Count responses for each question option
  responses.forEach((response) => {
    const answers = response.answers as any;
    
    // Count q1 (single choice)
    if (answers.q1 && counts.q1[answers.q1] !== undefined) {
      counts.q1[answers.q1]++;
    }
    
    // Count q2 (multi select)
    if (answers.q2 && Array.isArray(answers.q2)) {
      answers.q2.forEach((option: string) => {
        if (counts.q2[option] !== undefined) {
          counts.q2[option]++;
        }
      });
    }
  });

  return {
    totalSubmissions,
    counts,
  };
}

/**
 * Deletes a response by its ID (for testing/cleanup purposes)
 * 
 * @param id - The unique identifier of the response to delete
 * @returns True if deleted, false if not found
 */
export async function deleteResponse(id: string): Promise<boolean> {
  try {
    await prisma.response.delete({
      where: { id },
    });
    return true;
  } catch (error) {
    return false;
  }
}
