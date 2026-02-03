/**
 * Application Configuration
 * 
 * This file configures the Angular application.
 * In Angular 17+, this replaces the old app.module.ts approach.
 * 
 * Key Configurations:
 * - HTTP Client with interceptors
 * - Router configuration
 * - Providers (services, guards, etc.)
 * - Application-wide settings
 */

import { ApplicationConfig, provideZoneChangeDetection } from '@angular/core';
import { provideRouter, withComponentInputBinding, withViewTransitions } from '@angular/router';
import { provideHttpClient, withInterceptors, HTTP_INTERCEPTORS } from '@angular/common/http';
import { routes } from './app.routes';

// Import interceptors
import { authInterceptor } from './core/interceptors/auth.interceptor';
import { errorInterceptor } from './core/interceptors/error.interceptor';
import { loadingInterceptor } from './core/interceptors/loading.interceptor';

export const appConfig: ApplicationConfig = {
  providers: [
    /**
     * Zone.js Change Detection
     * 
     * Zone.js patches async operations to trigger change detection.
     * This is the default in Angular but can be configured.
     */
    provideZoneChangeDetection({ eventCoalescing: true }),

    /**
     * Router Configuration
     * 
     * provideRouter: Configures the Angular router
     * - routes: Route configuration
     * - withComponentInputBinding: Allows route params to be inputs
     * - withViewTransitions: Enables smooth page transitions
     */
    provideRouter(
      routes,
      withComponentInputBinding(), // Route params become component inputs
      withViewTransitions() // Smooth transitions between routes
    ),

    /**
     * HTTP Client Configuration
     * 
     * provideHttpClient: Configures Angular's HTTP client
     * - withInterceptors: Adds interceptors to the request/response chain
     * 
     * Interceptor Order:
     * Interceptors are executed in the order they're provided.
     * 1. authInterceptor: Adds auth token
     * 2. loadingInterceptor: Tracks loading state
     * 3. errorInterceptor: Handles errors
     */
    provideHttpClient(
      withInterceptors([
        authInterceptor,      // Add authentication token
        loadingInterceptor,  // Track loading state
        errorInterceptor     // Handle errors globally
      ])
    )
  ]
};

