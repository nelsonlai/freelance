/**
 * API Service
 * 
 * This service provides a centralized HTTP client for making API requests.
 * 
 * Key Features:
 * - Type-safe HTTP requests
 * - Centralized error handling
 * - Request/response interceptors (configured in app.config.ts)
 * - Observable-based (RxJS)
 * - Support for all HTTP methods (GET, POST, PUT, DELETE, PATCH)
 * 
 * Angular HttpClient:
 * - Built on top of XMLHttpRequest and Fetch API
 * - Returns Observables (not Promises)
 * - Automatic JSON parsing
 * - Request/response interceptors
 * - Progress events for file uploads
 * - Type-safe with TypeScript generics
 */

import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams, HttpErrorResponse } from '@angular/common/http';
import { Observable, throwError } from 'rxjs';
import { catchError, retryWhen, concatMap } from 'rxjs/operators';
import { timer, throwError as rxThrowError } from 'rxjs';
import { environment } from '../../../../environments/environment';

/**
 * HTTP Request Options
 */
export interface HttpOptions {
  headers?: HttpHeaders | { [header: string]: string | string[] };
  params?: HttpParams | { [param: string]: any };
  observe?: 'body' | 'events' | 'response';
  reportProgress?: boolean;
  responseType?: 'json' | 'text' | 'blob' | 'arraybuffer';
}

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  /**
   * Base URL for all API requests
   * Configured from environment file
   */
  private readonly apiUrl: string = environment.apiUrl;

  /**
   * Default HTTP headers
   * Can be overridden per request
   */
  private readonly defaultHeaders: HttpHeaders = new HttpHeaders({
    'Content-Type': 'application/json',
    'Accept': 'application/json'
  });

  /**
   * Constructor with Dependency Injection
   * 
   * Angular's Dependency Injection (DI) system automatically provides
   * the HttpClient instance. This is one of Angular's core features.
   * 
   * Benefits of DI:
   * - Loose coupling: Components don't need to know how to create dependencies
   * - Testability: Easy to mock dependencies in tests
   * - Singleton pattern: Same instance shared across the app
   * - Tree-shaking: Unused services can be removed from bundle
   */
  constructor(private http: HttpClient) {}

  /**
   * GET Request
   * 
   * Used for retrieving data from the server.
   * GET requests should be idempotent (no side effects).
   * 
   * @param endpoint - API endpoint (relative to base URL)
   * @param options - Optional HTTP options
   * @returns Observable that emits the response data
   * 
   * @example
   * // Get all users
   * this.apiService.get<User[]>('/users')
   *   .subscribe(users => console.log(users));
   * 
   * @example
   * // Get user with query parameters
   * this.apiService.get<User>('/users/1')
   *   .subscribe(user => console.log(user));
   */
  get<T>(endpoint: string, options?: HttpOptions): Observable<T> {
    const url = `${this.apiUrl}${endpoint}`;
    const httpOptions: any = { ...this.buildHttpOptions(options), observe: 'body' as const };

    return this.http.get<T>(url, httpOptions).pipe(
      // Retry failed requests, but skip retries for connection errors (status 0)
      retryWhen(errors =>
        errors.pipe(
          concatMap((error: HttpErrorResponse, index) => {
            // Don't retry connection errors (status 0) - backend is down, fail immediately
            if (error.status === 0) {
              return rxThrowError(() => error);
            }
            // Retry other errors up to 2 times with 1 second delay
            if (index < 2) {
              return timer(1000);
            }
            // After 2 retries, give up
            return rxThrowError(() => error);
          })
        )
      ),
      // Handle errors
      catchError(this.handleError<T>('GET', endpoint))
    ) as Observable<T>;
  }

  /**
   * POST Request
   * 
   * Used for creating new resources or submitting data.
   * POST requests can have side effects.
   * 
   * @param endpoint - API endpoint
   * @param body - Request body data
   * @param options - Optional HTTP options
   * @returns Observable that emits the response data
   * 
   * @example
   * // Create a new user
   * this.apiService.post<User>('/users', { name: 'John', email: 'john@example.com' })
   *   .subscribe(user => console.log('Created:', user));
   */
  post<T>(endpoint: string, body: any, options?: HttpOptions): Observable<T> {
    const url = `${this.apiUrl}${endpoint}`;
    const httpOptions: any = { ...this.buildHttpOptions(options), observe: 'body' as const };

    return this.http.post<T>(url, body, httpOptions).pipe(
      catchError(this.handleError<T>('POST', endpoint))
    ) as Observable<T>;
  }

  /**
   * PUT Request
   * 
   * Used for updating/replacing entire resources.
   * PUT is idempotent (same request can be sent multiple times).
   * 
   * @param endpoint - API endpoint (usually includes resource ID)
   * @param body - Complete resource data
   * @param options - Optional HTTP options
   * @returns Observable that emits the response data
   * 
   * @example
   * // Update entire user
   * this.apiService.put<User>('/users/1', { id: 1, name: 'John Updated', email: 'john@example.com' })
   *   .subscribe(user => console.log('Updated:', user));
   */
  put<T>(endpoint: string, body: any, options?: HttpOptions): Observable<T> {
    const url = `${this.apiUrl}${endpoint}`;
    const httpOptions: any = { ...this.buildHttpOptions(options), observe: 'body' as const };

    return this.http.put<T>(url, body, httpOptions).pipe(
      catchError(this.handleError<T>('PUT', endpoint))
    ) as Observable<T>;
  }

  /**
   * PATCH Request
   * 
   * Used for partial updates to resources.
   * Only send the fields that need to be updated.
   * 
   * @param endpoint - API endpoint
   * @param body - Partial resource data
   * @param options - Optional HTTP options
   * @returns Observable that emits the response data
   * 
   * @example
   * // Update only user's email
   * this.apiService.patch<User>('/users/1', { email: 'newemail@example.com' })
   *   .subscribe(user => console.log('Patched:', user));
   */
  patch<T>(endpoint: string, body: any, options?: HttpOptions): Observable<T> {
    const url = `${this.apiUrl}${endpoint}`;
    const httpOptions: any = { ...this.buildHttpOptions(options), observe: 'body' as const };

    return this.http.patch<T>(url, body, httpOptions).pipe(
      catchError(this.handleError<T>('PATCH', endpoint))
    ) as Observable<T>;
  }

  /**
   * DELETE Request
   * 
   * Used for deleting resources.
   * DELETE is idempotent.
   * 
   * @param endpoint - API endpoint (usually includes resource ID)
   * @param options - Optional HTTP options
   * @returns Observable that completes when deletion is done
   * 
   * @example
   * // Delete a user
   * this.apiService.delete('/users/1')
   *   .subscribe(() => console.log('Deleted'));
   */
  delete<T>(endpoint: string, options?: HttpOptions): Observable<T> {
    const url = `${this.apiUrl}${endpoint}`;
    const httpOptions: any = { ...this.buildHttpOptions(options), observe: 'body' as const };

    return this.http.delete<T>(url, httpOptions).pipe(
      catchError(this.handleError<T>('DELETE', endpoint))
    ) as Observable<T>;
  }

  /**
   * Build HTTP options with defaults
   * 
   * Merges provided options with default headers and settings.
   * 
   * @param options - User-provided options
   * @returns Merged HTTP options
   */
  private buildHttpOptions(options?: HttpOptions): any {
    let headers = this.defaultHeaders;

    // Merge custom headers if provided
    if (options?.headers) {
      if (options.headers instanceof HttpHeaders) {
        headers = options.headers;
      } else {
        // Convert object to HttpHeaders
        const headersObj = options.headers as { [header: string]: string | string[] };
        Object.keys(headersObj).forEach(key => {
          const value = headersObj[key];
          if (Array.isArray(value)) {
            headers = headers.set(key, value.join(', '));
          } else {
            headers = headers.set(key, value);
          }
        });
      }
    }

    return {
      ...options,
      headers
    };
  }

  /**
   * Handle HTTP errors
   * 
   * Centralized error handling for all HTTP requests.
   * This provides consistent error handling across the application.
   * 
   * @param operation - Name of the operation that failed
   * @param endpoint - API endpoint that failed
   * @returns Error observable
   */
  private handleError<T>(operation: string, endpoint: string) {
    return (error: HttpErrorResponse): Observable<T> => {
      // Log error details (only if not status 0 in development)
      if (error.status !== 0 || environment.production) {
        console.error(`${operation} ${endpoint} failed:`, error);
      }

      let errorMessage = 'An unknown error occurred';

      if (error.error instanceof ErrorEvent) {
        // Client-side error (network, CORS, etc.)
        errorMessage = `Client Error: ${error.error.message}`;
      } else {
        // Handle specific status codes first
        switch (error.status) {
          case 0:
            // Network error - in development, use empty message (demo mode)
            if (environment.production) {
              errorMessage = 'Unable to connect to the server. Please check your internet connection.';
            } else {
              errorMessage = ''; // Empty message for demo mode
            }
            break;
          case 400:
            errorMessage = 'Bad Request: Invalid data provided';
            break;
          case 401:
            errorMessage = 'Unauthorized: Please log in';
            break;
          case 403:
            errorMessage = 'Forbidden: You do not have permission';
            break;
          case 404:
            errorMessage = 'Not Found: Resource does not exist';
            break;
          case 500:
            errorMessage = 'Server Error: Please try again later';
            break;
          default:
            // Server-side error (for other status codes)
            errorMessage = `Server Error: ${error.status} - ${error.message}`;
        }
      }

      // Return error observable
      // This allows components to handle errors as needed
      return throwError(() => ({
        message: errorMessage,
        status: error.status,
        error: error.error
      }));
    };
  }
}

