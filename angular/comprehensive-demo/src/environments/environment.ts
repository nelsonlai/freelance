/**
 * Environment Configuration - Development
 * 
 * This file contains environment-specific configuration for the development build.
 * In Angular, environment files allow you to configure different settings for
 * different build targets (development, staging, production).
 * 
 * Best Practices:
 * - Never commit sensitive data (API keys, secrets) to version control
 * - Use environment variables or secure configuration management in production
 * - Keep development and production configurations separate
 */

export const environment = {
  /**
   * Production flag - indicates if the app is running in production mode
   * Used to enable/disable features like logging, debugging, etc.
   */
  production: false,

  /**
   * API Configuration
   * Base URL for all HTTP requests to the backend API
   * In development, this typically points to a local server or mock API
   */
  apiUrl: 'http://localhost:3000/api',

  /**
   * Application Name
   * Used throughout the application for branding and display purposes
   */
  appName: 'Angular Comprehensive Demo',

  /**
   * Version Information
   * Useful for debugging and tracking which version is deployed
   */
  version: '1.0.0',

  /**
   * Feature Flags
   * Control which features are enabled/disabled in different environments
   */
  features: {
    enableLogging: true, // Enable logging when backend is available
    enableAnalytics: false,
    enableErrorReporting: false,
  },

  /**
   * Storage Configuration
   * Configuration for different storage mechanisms
   */
  storage: {
    localStoragePrefix: 'app_',
    sessionStoragePrefix: 'session_',
    cookiePrefix: 'app_',
    indexedDBName: 'AngularDemoDB',
    indexedDBVersion: 1,
  },

  /**
   * Authentication Configuration
   * Settings related to user authentication and authorization
   */
  auth: {
    tokenKey: 'auth_token',
    refreshTokenKey: 'refresh_token',
    tokenExpirationTime: 3600, // seconds
  },
};

