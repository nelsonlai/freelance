/**
 * Role Guard
 * 
 * This guard protects routes based on user roles.
 * It checks if the current user has the required role(s) before
 * allowing access to the route.
 * 
 * Role-Based Access Control (RBAC):
 * - Different users have different roles (admin, user, guest)
 * - Routes can require specific roles
 * - Guards enforce these requirements
 * 
 * Usage in routes:
 * {
 *   path: 'admin',
 *   component: AdminComponent,
 *   canActivate: [roleGuard],
 *   data: { roles: ['admin'] }
 * }
 */

import { inject } from '@angular/core';
import { CanActivateFn, ActivatedRouteSnapshot, RouterStateSnapshot, Router } from '@angular/router';
import { Observable, map, take } from 'rxjs';
import { AuthService } from '../services/auth/auth.service';

/**
 * Functional Role Guard
 * 
 * Checks if user has required role(s) specified in route data.
 * 
 * @param route - Activated route snapshot (contains route data)
 * @param state - Router state snapshot
 * @returns Observable that resolves to boolean
 */
export const roleGuard: CanActivateFn = (
  route: ActivatedRouteSnapshot,
  state: RouterStateSnapshot
): Observable<boolean> | Promise<boolean> | boolean => {
  const authService = inject(AuthService);
  const router = inject(Router);

  // Get required roles from route data
  // Route data is set in the route configuration
  const requiredRoles = route.data['roles'] as string[];

  if (!requiredRoles || requiredRoles.length === 0) {
    // No roles required, allow access
    return true;
  }

  // Check if user is authenticated first
  return authService.isAuthenticated$.pipe(
    take(1),
    map((isAuthenticated) => {
      if (!isAuthenticated) {
        // Not authenticated, redirect to login
        router.navigate(['/login'], {
          queryParams: { returnUrl: state.url }
        });
        return false;
      }

      // Check if user has required role
      const user = authService.getCurrentUser();
      if (!user) {
        router.navigate(['/login']);
        return false;
      }

      // Check if user has any of the required roles
      const hasRole = requiredRoles.includes(user.role);

      if (!hasRole) {
        // User doesn't have required role, redirect to unauthorized page
        router.navigate(['/unauthorized']);
        return false;
      }

      return true;
    })
  );
};

