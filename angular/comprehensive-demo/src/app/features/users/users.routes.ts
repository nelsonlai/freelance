/**
 * Users Feature Routes
 * 
 * Lazy-loaded routes for the users feature module.
 */

import { Routes } from '@angular/router';

export const USER_ROUTES: Routes = [
  {
    path: '',
    loadComponent: () => import('./user-list/user-list.component').then(m => m.UserListComponent),
    title: 'Users'
  },
  {
    path: ':id',
    loadComponent: () => import('./user-detail/user-detail.component').then(m => m.UserDetailComponent),
    title: 'User Details'
  }
];

