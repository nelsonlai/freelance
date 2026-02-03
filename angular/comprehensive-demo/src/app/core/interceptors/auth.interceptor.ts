/**
 * Authentication Interceptor
 * 
 * HTTP Interceptors in Angular allow you to:
 * - Modify HTTP requests before they're sent
 * - Modify HTTP responses before they reach your code
 * - Handle errors globally
 * - Add headers automatically
 * - Log requests/responses
 * 
 * This interceptor automatically adds the authentication token
 * to all HTTP requests.
 * 
 * Interceptor Chain:
 * - Interceptors are executed in the order they're provided
 * - Each interceptor can modify the request/response
 * - The chain can be short-circuited if needed
 * 
 * Registration:
 * Interceptors are registered in app.config.ts using the
 * provideHttpClient() function with interceptors array.
 */

import { HttpInterceptorFn, HttpRequest, HttpHandlerFn } from '@angular/common/http';
import { inject } from '@angular/core';
import { AuthService } from '../services/auth/auth.service';

/**
 * Functional Interceptor (Angular 15+)
 * 
 * Functional interceptors are the modern approach.
 * They're easier to test and more functional in style.
 * 
 * @param req - HTTP request
 * @param next - Next handler function in the interceptor chain
 * @returns Observable of HTTP event
 */
export const authInterceptor: HttpInterceptorFn = (
  req: HttpRequest<unknown>,
  next: HttpHandlerFn
) => {
  const authService = inject(AuthService);

  // Get authentication token
  const token = authService.getToken();

  // If token exists, add it to the request headers
  if (token) {
    // Clone the request and add the Authorization header
    // Requests are immutable, so we must clone to modify them
    const clonedRequest = req.clone({
      setHeaders: {
        Authorization: `Bearer ${token}`
      }
    });

    // Pass the cloned request to the next handler
    return next(clonedRequest);
  }

  // No token, pass the original request unchanged
  return next(req);
};

