/**
 * Loading Interceptor
 * 
 * This interceptor tracks HTTP request loading state.
 * It can be used to:
 * - Show/hide loading spinners
 * - Track active requests
 * - Prevent duplicate requests
 * - Show progress indicators
 * 
 * This is a simple example that logs loading state.
 * In a real application, you might use a LoadingService
 * to manage loading state across the application.
 */

import { HttpInterceptorFn, HttpRequest, HttpEvent, HttpErrorResponse } from '@angular/common/http';
import { Observable } from 'rxjs';
import { tap, finalize, catchError } from 'rxjs/operators';
import { environment } from '../../../environments/environment';

/**
 * Loading Interceptor
 * 
 * Logs request start and completion.
 * In a real app, you'd update a loading service here.
 */
export const loadingInterceptor: HttpInterceptorFn = (req, next) => {
  // Mark request as started
  const startTime = Date.now();
  
  // Suppress all logging for localhost:3000 requests in development (demo mode)
  const isDemoRequest = !environment.production && req.url.includes('localhost:3000');
  
  // Only log if not a demo request and logging is enabled
  if (!isDemoRequest && environment.features.enableLogging) {
    console.log(`[HTTP] Starting request: ${req.method} ${req.url}`);
  }

  // You could inject a LoadingService here to show loading indicators
  // const loadingService = inject(LoadingService);
  // loadingService.setLoading(true);

  return next(req).pipe(
    // Tap into the stream without modifying it
    tap((event: HttpEvent<any>) => {
      // Log successful responses (but not for demo requests)
      if (event.type === 4 && !isDemoRequest && environment.features.enableLogging) {
        const duration = Date.now() - startTime;
        console.log(`[HTTP] Request completed: ${req.method} ${req.url} (${duration}ms)`);
      }
    }),
    // Catch errors to check status before logging
    catchError((error: HttpErrorResponse) => {
      // Don't log for demo requests or connection errors in development
      if (!isDemoRequest && (error.status !== 0 || environment.production)) {
        if (environment.features.enableLogging) {
          const duration = Date.now() - startTime;
          console.log(`[HTTP] Request failed: ${req.method} ${req.url} (${duration}ms)`);
        }
      }
      // Re-throw the error
      throw error;
    }),
    // Always execute when request completes (success or error)
    finalize(() => {
      // Suppress logging for demo requests
      if (!isDemoRequest && environment.features.enableLogging) {
        const duration = Date.now() - startTime;
        console.log(`[HTTP] Request finalized: ${req.method} ${req.url} (${duration}ms)`);
      }
      
      // Hide loading indicator
      // loadingService.setLoading(false);
    })
  );
};

