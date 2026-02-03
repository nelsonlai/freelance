// Security utility functions for the questionnaire system
// Implements IP hashing and request ID generation as per SRS requirements

import crypto from 'crypto';

/**
 * Generates a SHA-256 hash of an IP address with a salt
 * This ensures privacy by not storing raw IP addresses
 * As per SRS: Store no PII; if IP captured, hash (SHA-256 + per-env salt)
 * 
 * @param ip - The IP address to hash
 * @param salt - Environment-specific salt for additional security
 * @returns SHA-256 hash of the IP + salt combination
 */
export function hashIP(ip: string, salt: string): string {
  return crypto.createHash('sha256').update(ip + salt).digest('hex');
}

/**
 * Generates a unique request ID for tracking requests
 * Used for logging and debugging purposes
 * 
 * @returns A unique request identifier
 */
export function generateRequestId(): string {
  return crypto.randomUUID();
}

/**
 * Sanitizes user input to prevent XSS and injection attacks
 * Strips HTML tags and potentially dangerous characters
 * 
 * @param input - The input string to sanitize
 * @returns Sanitized string safe for storage and display
 */
export function sanitizeInput(input: string): string {
  if (typeof input !== 'string') {
    return '';
  }
  
  // Remove HTML tags and potentially dangerous characters
  return input
    .replace(/<[^>]*>/g, '') // Remove HTML tags
    .replace(/[<>\"'&]/g, '') // Remove potentially dangerous characters
    .trim();
}

/**
 * Validates if a string is a valid IP address
 * 
 * @param ip - The string to validate as an IP address
 * @returns True if valid IP, false otherwise
 */
export function isValidIP(ip: string): boolean {
  const ipv4Regex = /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
  const ipv6Regex = /^(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$/;
  
  return ipv4Regex.test(ip) || ipv6Regex.test(ip);
}
