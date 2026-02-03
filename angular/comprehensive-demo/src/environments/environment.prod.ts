/**
 * Environment Configuration - Production
 * 
 * Production environment configuration with optimized settings.
 * This file is used when building for production (ng build --configuration production).
 */

export const environment = {
  production: true,
  apiUrl: 'https://api.example.com/api',
  appName: 'Angular Comprehensive Demo',
  version: '1.0.0',
  features: {
    enableLogging: false,
    enableAnalytics: true,
    enableErrorReporting: true,
  },
  storage: {
    localStoragePrefix: 'app_',
    sessionStoragePrefix: 'session_',
    cookiePrefix: 'app_',
    indexedDBName: 'AngularDemoDB',
    indexedDBVersion: 1,
  },
  auth: {
    tokenKey: 'auth_token',
    refreshTokenKey: 'refresh_token',
    tokenExpirationTime: 3600,
  },
};

