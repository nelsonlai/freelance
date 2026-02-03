import { Routes } from '@angular/router';

export const routes: Routes = [
  {
    path: 'login',
    loadComponent: () => import('./login.component').then((m) => m.LoginComponent),
  },
  {
    path: 'customers',
    loadComponent: () => import('./customer-shell.component').then((m) => m.CustomerShellComponent),
  },
  {
    path: '',
    redirectTo: '/login',
    pathMatch: 'full',
  },
];

