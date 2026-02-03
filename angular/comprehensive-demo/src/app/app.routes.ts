/**
 * Application Routes Configuration
 * 
 * This file defines all routes in the application.
 * 
 * Routing Concepts:
 * - Routes map URLs to components
 * - Lazy loading improves initial load time
 * - Guards protect routes
 * - Resolvers pre-fetch data
 * - Child routes create nested navigation
 * 
 * Lazy Loading:
 * - loadComponent: Loads a standalone component
 * - loadChildren: Loads a feature module
 * - Reduces initial bundle size
 * - Code is split into separate chunks
 * 
 * Route Configuration:
 * - path: URL path
 * - component: Component to display
 * - loadComponent: Lazy load a standalone component
 * - loadChildren: Lazy load a module
 * - canActivate: Guards to check before activation
 * - canActivateChild: Guards for child routes
 * - data: Static data attached to route
 * - resolve: Resolvers to pre-fetch data
 */

import { Routes } from '@angular/router';
import { authGuard } from './core/guards/auth.guard';
import { roleGuard } from './core/guards/role.guard';

export const routes: Routes = [
  /**
   * Default route - redirects to home
   */
  {
    path: '',
    redirectTo: '/home',
    pathMatch: 'full'
  },

  /**
   * Home route - public access
   */
  {
    path: 'home',
    loadComponent: () => import('./features/dashboard/home/home.component').then(m => m.HomeComponent),
    title: 'Home'
  },

  /**
   * Login route - public access
   */
  {
    path: 'login',
    loadComponent: () => import('./features/auth/login/login.component').then(m => m.LoginComponent),
    title: 'Login'
  },

  /**
   * Register route - public access
   */
  {
    path: 'register',
    loadComponent: () => import('./features/auth/register/register.component').then(m => m.RegisterComponent),
    title: 'Register'
  },

  /**
   * Dashboard route - requires authentication
   * 
   * canActivate: Array of guards that must all pass
   * Guards are executed in order
   */
  {
    path: 'dashboard',
    loadComponent: () => import('./features/dashboard/dashboard/dashboard.component').then(m => m.DashboardComponent),
    canActivate: [authGuard],
    title: 'Dashboard'
  },

  /**
   * Users feature - lazy loaded module
   * Requires authentication
   */
  {
    path: 'users',
    loadChildren: () => import('./features/users/users.routes').then(m => m.USER_ROUTES),
    canActivate: [authGuard],
    title: 'Users'
  },

  /**
   * Products feature - lazy loaded
   * Requires authentication
   */
  {
    path: 'products',
    loadChildren: () => import('./features/products/products.routes').then(m => m.PRODUCT_ROUTES),
    canActivate: [authGuard],
    title: 'Products'
  },

  /**
   * Admin routes - requires admin role
   * 
   * roleGuard checks the 'roles' property in route data
   */
  {
    path: 'admin',
    loadComponent: () => import('./features/dashboard/admin/admin.component').then(m => m.AdminComponent),
    canActivate: [authGuard, roleGuard],
    data: { roles: ['admin'] },
    title: 'Admin Panel'
  },

  /**
   * Storage demo - demonstrates storage services
   */
  {
    path: 'storage-demo',
    loadComponent: () => import('./features/dashboard/storage-demo/storage-demo.component').then(m => m.StorageDemoComponent),
    canActivate: [authGuard],
    title: 'Storage Demo'
  },

  /**
   * Forms demo - demonstrates template and reactive forms
   */
  {
    path: 'forms-demo',
    loadComponent: () => import('./features/dashboard/forms-demo/forms-demo.component').then(m => m.FormsDemoComponent),
    canActivate: [authGuard],
    title: 'Forms Demo'
  },

  /**
   * RxJS demo - demonstrates observables
   */
  {
    path: 'rxjs-demo',
    loadComponent: () => import('./features/dashboard/rxjs-demo/rxjs-demo.component').then(m => m.RxjsDemoComponent),
    canActivate: [authGuard],
    title: 'RxJS Demo'
  },

  /**
   * Unauthorized page
   */
  {
    path: 'unauthorized',
    loadComponent: () => import('./features/dashboard/unauthorized/unauthorized.component').then(m => m.UnauthorizedComponent),
    title: 'Unauthorized'
  },

  /**
   * Wildcard route - must be last
   * Catches all unmatched routes and redirects to 404 or home
   */
  {
    path: '**',
    loadComponent: () => import('./features/dashboard/not-found/not-found.component').then(m => m.NotFoundComponent),
    title: 'Page Not Found'
  }
];

