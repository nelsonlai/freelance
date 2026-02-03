/**
 * Error Interceptor
 * 
 * This interceptor handles HTTP errors globally.
 * It can:
 * - Log errors
 * - Show error notifications
 * - Redirect on specific errors (e.g., 401 to login)
 * - Transform error responses
 * - Retry failed requests
 * 
 * Error Handling Strategy:
 * - 401 Unauthorized: Redirect to login
 * - 403 Forbidden: Show access denied message
 * - 500 Server Error: Show generic error message
 * - Network errors: Show connection error message
 */

import { HttpInterceptorFn, HttpErrorResponse } from '@angular/common/http';
import { inject } from '@angular/core';
import { Router } from '@angular/router';
import { Observable, throwError } from 'rxjs';
import { catchError } from 'rxjs/operators';
import { AuthService } from '../services/auth/auth.service';
import { environment } from '../../../environments/environment';

/**
 * Error Interceptor Function
 * 
 * Catches HTTP errors and handles them appropriately.
 */
export const errorInterceptor: HttpInterceptorFn = (req, next) => {
  const router = inject(Router);
  const authService = inject(AuthService);

  return next(req).pipe(
    catchError((error: HttpErrorResponse) => {
      let errorMessage = 'An unknown error occurred';

      if (error.error instanceof ErrorEvent) {
        // Client-side error (network, CORS, etc.)
        errorMessage = `Client Error: ${error.error.message}`;
        // Only log in development mode
        if (environment.features.enableLogging) {
          console.error('Client-side error:', error.error);
        }
      } else {
        // Server-side error
        const status = error.status;

        // Handle specific HTTP status codes
        switch (status) {
          case 0:
            // Network error or CORS issue (usually means no backend server)
            // In development/demo mode, this is expected - components will use mock data
            if (environment.production) {
              errorMessage = 'Unable to connect to the server. Please check your internet connection.';
            } else {
              // In development, silently handle - components will use mock data
              // Don't show error message to users in demo mode
              errorMessage = ''; // Empty message - components will handle gracefully
              // Suppress all logging for connection errors in demo mode
              // (No console.log here - completely silent)
            }
            break;

          case 401:
            // Unauthorized - token expired or invalid
            console.warn('Unauthorized access - redirecting to login');
            authService.logout();
            // Use setTimeout to avoid navigation during interceptor execution
            setTimeout(() => {
              const currentUrl = router.url || '/';
              router.navigate(['/login'], {
                queryParams: { returnUrl: currentUrl }
              });
            }, 0);
            errorMessage = 'Your session has expired. Please log in again.';
            break;

          case 403:
            // Forbidden - user doesn't have permission
            console.warn('Forbidden access');
            errorMessage = 'You do not have permission to access this resource.';
            break;

          case 404:
            // Not Found
            errorMessage = 'The requested resource was not found.';
            break;

          case 500:
            // Internal Server Error
            errorMessage = 'A server error occurred. Please try again later.';
            break;

          default:
            errorMessage = `Server Error: ${status} - ${error.message}`;
        }

        // Only log errors in development mode if logging is enabled
        if (environment.features.enableLogging && status !== 0) {
          console.error('Server-side error:', {
            status,
            message: error.message,
            url: error.url,
            error: error.error
          });
        }
      }

      // You could inject a notification service here to show user-friendly messages
      // For example: this.notificationService.showError(errorMessage);

      // Return error observable
      return throwError(() => ({
        message: errorMessage,
        status: error.status,
        originalError: error
      }));
    })
  );
};

