/**
 * Authentication Guard
 * 
 * Route guards in Angular control access to routes based on conditions.
 * This guard protects routes that require authentication.
 * 
 * How Guards Work:
 * - CanActivate: Checks if route can be activated (accessed)
 * - CanActivateChild: Checks if child routes can be activated
 * - CanDeactivate: Checks if route can be deactivated (leaving)
 * - CanLoad: Checks if lazy-loaded module can be loaded
 * - Resolve: Pre-fetches data before route activation
 * 
 * This guard implements CanActivate to check authentication before
 * allowing access to protected routes.
 * 
 * Usage in routes:
 * {
 *   path: 'dashboard',
 *   component: DashboardComponent,
 *   canActivate: [AuthGuard]
 * }
 */

import { Injectable, inject } from '@angular/core';
import { Router, CanActivateFn, ActivatedRouteSnapshot, RouterStateSnapshot } from '@angular/router';
import { Observable, map, take } from 'rxjs';
import { AuthService } from '../services/auth/auth.service';

/**
 * Functional Guard (Angular 15+)
 * 
 * Functional guards are the modern approach in Angular.
 * They're easier to test and more composable.
 * 
 * @param route - Activated route snapshot
 * @param state - Router state snapshot
 * @returns Observable or Promise that resolves to boolean
 */
export const authGuard: CanActivateFn = (
  route: ActivatedRouteSnapshot,
  state: RouterStateSnapshot
): Observable<boolean> | Promise<boolean> | boolean => {
  const authService = inject(AuthService);
  const router = inject(Router);

  // Check if user is authenticated
  return authService.isAuthenticated$.pipe(
    take(1), // Take only the first value and complete
    map((isAuthenticated) => {
      if (isAuthenticated) {
        // User is authenticated, allow access
        return true;
      } else {
        // User is not authenticated, redirect to login
        // Store the attempted URL for redirect after login
        router.navigate(['/login'], {
          queryParams: { returnUrl: state.url }
        });
        return false;
      }
    })
  );
};

/**
 * Class-based Guard (Alternative approach)
 * 
 * This is the traditional class-based approach.
 * Still valid but functional guards are preferred in newer Angular versions.
 */
@Injectable({
  providedIn: 'root'
})
export class AuthGuard {
  constructor(
    private authService: AuthService,
    private router: Router
  ) {}

  canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot
  ): Observable<boolean> | Promise<boolean> | boolean {
    return this.authService.isAuthenticated$.pipe(
      take(1),
      map((isAuthenticated) => {
        if (isAuthenticated) {
          return true;
        } else {
          this.router.navigate(['/login'], {
            queryParams: { returnUrl: state.url }
          });
          return false;
        }
      })
    );
  }
}

