import { z } from 'zod';

export const createRecordSchema = z.object({
  username: z.string()
    .min(3, 'Username must be at least 3 characters')
    .max(50, 'Username must be at most 50 characters')
    .regex(/^[A-Za-z0-9_\-\.]+$/, 'Username can only contain letters, numbers, underscores, hyphens, and dots'),
  email: z.string()
    .email('Invalid email format'),
  password: z.string()
    .min(8, 'Password must be at least 8 characters')
    .max(128, 'Password must be at most 128 characters')
    .refine((password) => {
      const hasLower = /[a-z]/.test(password);
      const hasUpper = /[A-Z]/.test(password);
      const hasDigit = /\d/.test(password);
      const hasSymbol = /[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(password);
      
      const classes = [hasLower, hasUpper, hasDigit, hasSymbol].filter(Boolean);
      return classes.length >= 3;
    }, 'Password must contain at least 3 character classes (lowercase, uppercase, digits, symbols)')
});

export const updateRecordSchema = z.object({
  username: z.string()
    .min(3, 'Username must be at least 3 characters')
    .max(50, 'Username must be at most 50 characters')
    .regex(/^[A-Za-z0-9_\-\.]+$/, 'Username can only contain letters, numbers, underscores, hyphens, and dots')
    .optional(),
  email: z.string()
    .email('Invalid email format')
    .optional(),
  password: z.string()
    .min(8, 'Password must be at least 8 characters')
    .max(128, 'Password must be at most 128 characters')
    .refine((password) => {
      const hasLower = /[a-z]/.test(password);
      const hasUpper = /[A-Z]/.test(password);
      const hasDigit = /\d/.test(password);
      const hasSymbol = /[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(password);
      
      const classes = [hasLower, hasUpper, hasDigit, hasSymbol].filter(Boolean);
      return classes.length >= 3;
    }, 'Password must contain at least 3 character classes (lowercase, uppercase, digits, symbols)')
    .optional()
}).refine((data) => Object.keys(data).length > 0, {
  message: 'At least one field must be provided for update'
});

export type CreateRecordInput = z.infer<typeof createRecordSchema>;
export type UpdateRecordInput = z.infer<typeof updateRecordSchema>;
