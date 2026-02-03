/**
 * Application Bootstrap
 * 
 * This is the entry point of the Angular application.
 * 
 * Bootstrap Process:
 * 1. Angular bootstraps the root component (AppComponent)
 * 2. AppComponent renders and initializes
 * 3. Router takes over and displays the appropriate component
 * 
 * Standalone Bootstrap (Angular 14+):
 * - No NgModule needed
 * - Direct component bootstrap
 * - Simpler and more modern approach
 */

import { bootstrapApplication } from '@angular/platform-browser';
import { AppComponent } from './app/app.component';
import { appConfig } from './app/app.config';

/**
 * Bootstrap the application
 * 
 * bootstrapApplication is the modern way to start an Angular app.
 * It takes:
 * - Root component (AppComponent)
 * - Application configuration (appConfig)
 */
bootstrapApplication(AppComponent, appConfig)
  .catch((err) => console.error('Error bootstrapping application:', err));

