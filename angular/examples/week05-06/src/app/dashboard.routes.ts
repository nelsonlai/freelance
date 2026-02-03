// @ts-nocheck
import { Routes } from '@angular/router';
import { provideRouter, withComponentInputBinding } from '@angular/router';
import { DashboardComponent } from './dashboard.component';
import { AuthGuard } from './auth.guard';
import { ProjectsResolver } from './projects.resolver';

export const DASHBOARD_ROUTES: Routes = [
  {
    path: '',
    component: DashboardComponent,
    canActivate: [AuthGuard],
    resolve: {
      projects: ProjectsResolver,
    },
    children: [
      {
        path: 'metrics',
        loadComponent: () => import('./metrics-widget.component').then((m) => m.MetricsWidgetComponent),
      },
      {
        path: 'activity',
        loadComponent: () => import('./activity-feed.component').then((m) => m.ActivityFeedComponent),
      },
      {
        path: '',
        pathMatch: 'full',
        redirectTo: 'metrics',
      },
    ],
  },
];

export const DASHBOARD_PROVIDERS = [provideRouter(DASHBOARD_ROUTES, withComponentInputBinding())];
