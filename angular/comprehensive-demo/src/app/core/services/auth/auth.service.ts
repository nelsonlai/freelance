/**
 * Authentication Service
 * 
 * This service handles user authentication, including login, logout,
 * token management, and user session state.
 * 
 * Key Features:
 * - JWT token management
 * - User session state
 * - Integration with storage services
 * - Observable-based authentication state
 * - Token refresh support
 * 
 * Security Best Practices:
 * - Tokens stored in multiple places for redundancy
 * - Automatic token expiration handling
 * - Secure token storage (consider HttpOnly cookies in production)
 * - Clear separation of concerns
 */

import { Injectable, inject } from '@angular/core';
import { BehaviorSubject, Observable, of, throwError } from 'rxjs';
import { tap, catchError, map } from 'rxjs/operators';
import { ApiService } from '../http/api.service';
import { LocalStorageService } from '../storage/local-storage.service';
import { SessionStorageService } from '../storage/session-storage.service';
import { CookieService } from '../storage/cookie.service';
import { User, LoginCredentials, AuthResponse } from '../../../models/user.model';
import { environment } from '../../../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  // Inject dependencies using inject() function (Angular 14+)
  // Alternative to constructor injection
  private apiService = inject(ApiService);
  private localStorage = inject(LocalStorageService);
  private sessionStorage = inject(SessionStorageService);
  private cookieService = inject(CookieService);

  /**
   * BehaviorSubject for current user
   * 
   * BehaviorSubject is a special type of Observable that:
   * - Holds the current value
   * - Emits the current value to new subscribers immediately
   * - Allows reading the current value synchronously
   * 
   * This is perfect for authentication state that needs to be
   * accessible throughout the application.
   */
  private currentUserSubject = new BehaviorSubject<User | null>(null);

  /**
   * Public Observable of current user
   * Components can subscribe to this to react to auth state changes
   */
  public currentUser$: Observable<User | null> = this.currentUserSubject.asObservable();

  /**
   * BehaviorSubject for authentication status
   */
  private isAuthenticatedSubject = new BehaviorSubject<boolean>(false);

  /**
   * Public Observable of authentication status
   */
  public isAuthenticated$: Observable<boolean> = this.isAuthenticatedSubject.asObservable();

  /**
   * Constructor
   * 
   * Checks for existing authentication on service initialization.
   * This allows the app to restore user session on page refresh.
   */
  constructor() {
    this.initializeAuth();
  }

  /**
   * Initialize authentication state
   * 
   * Restores user session from storage if available.
   * This is called on service initialization.
   */
  private initializeAuth(): void {
    // Try to restore user from storage
    const storedUser = this.localStorage.get<User>('currentUser');
    const token = this.getToken();

    if (storedUser && token) {
      // Restore authentication state
      this.currentUserSubject.next(storedUser);
      this.isAuthenticatedSubject.next(true);
    } else {
      // Clear any partial state
      this.logout();
    }
  }

  /**
   * Login user
   * 
   * Authenticates user with credentials and stores authentication data.
   * 
   * @param credentials - User login credentials
   * @returns Observable that emits the authenticated user
   * 
   * @example
   * this.authService.login({ email: 'user@example.com', password: 'password' })
   *   .subscribe({
   *     next: user => console.log('Logged in:', user),
   *     error: err => console.error('Login failed:', err)
   *   });
   */
  login(credentials: LoginCredentials): Observable<User> {
    // Make API call to authenticate
    return this.apiService.post<AuthResponse>('/auth/login', credentials).pipe(
      // Use tap operator for side effects (doesn't modify the stream)
      tap((response: AuthResponse) => {
        // Store authentication data
        this.setToken(response.token);
        this.setRefreshToken(response.refreshToken);
        this.setUser(response.user);
        
        // Update authentication state
        this.currentUserSubject.next(response.user);
        this.isAuthenticatedSubject.next(true);
      }),
      // Extract user from response
      map((response: AuthResponse) => response.user),
      // Handle errors - for demo purposes, allow mock login
      catchError((error) => {
        // If backend is not available, create a mock user for demo
        if (error.status === 0 || error.status === null) {
          console.info('Backend not available - using demo login');
          const mockUser: User = {
            id: 1,
            firstName: credentials.email.split('@')[0] || 'Demo',
            lastName: 'User',
            email: credentials.email,
            role: 'user',
            isActive: true,
            createdAt: new Date().toISOString(),
            updatedAt: new Date().toISOString()
          };
          
          // Store mock authentication
          this.setToken('demo_token_' + Date.now());
          this.setRefreshToken('demo_refresh_token');
          this.setUser(mockUser);
          
          this.currentUserSubject.next(mockUser);
          this.isAuthenticatedSubject.next(true);
          
          return of(mockUser);
        }
        
        console.error('Login error:', error);
        return throwError(() => error);
      })
    );
  }

  /**
   * Logout user
   * 
   * Clears all authentication data and resets state.
   */
  logout(): void {
    // Clear all stored authentication data
    this.localStorage.remove('currentUser');
    this.localStorage.remove(environment.auth.tokenKey);
    this.localStorage.remove(environment.auth.refreshTokenKey);
    
    this.sessionStorage.remove('currentUser');
    this.sessionStorage.remove(environment.auth.tokenKey);
    
    this.cookieService.remove(environment.auth.tokenKey);
    
    // Reset state
    this.currentUserSubject.next(null);
    this.isAuthenticatedSubject.next(false);
  }

  /**
   * Register new user
   * 
   * Creates a new user account and automatically logs them in.
   * 
   * @param userData - User registration data
   * @returns Observable that emits the authenticated user
   */
  register(userData: any): Observable<User> {
    return this.apiService.post<AuthResponse>('/auth/register', userData).pipe(
      tap((response: AuthResponse) => {
        // Store authentication data (same as login)
        this.setToken(response.token);
        this.setRefreshToken(response.refreshToken);
        this.setUser(response.user);
        
        this.currentUserSubject.next(response.user);
        this.isAuthenticatedSubject.next(true);
      }),
      map((response: AuthResponse) => response.user),
      catchError((error) => {
        // If backend is not available, create a mock user for demo
        if (error.status === 0 || error.status === null) {
          console.info('Backend not available - using demo registration');
          const mockUser: User = {
            id: Date.now(),
            firstName: userData.firstName || 'Demo',
            lastName: userData.lastName || 'User',
            email: userData.email,
            role: userData.role || 'user',
            isActive: true,
            createdAt: new Date().toISOString(),
            updatedAt: new Date().toISOString()
          };
          
          // Store mock authentication
          this.setToken('demo_token_' + Date.now());
          this.setRefreshToken('demo_refresh_token');
          this.setUser(mockUser);
          
          this.currentUserSubject.next(mockUser);
          this.isAuthenticatedSubject.next(true);
          
          return of(mockUser);
        }
        
        console.error('Registration error:', error);
        return throwError(() => error);
      })
    );
  }

  /**
   * Get current user
   * 
   * Returns the current user synchronously (from BehaviorSubject).
   * Use currentUser$ Observable for reactive updates.
   * 
   * @returns Current user or null if not authenticated
   */
  getCurrentUser(): User | null {
    return this.currentUserSubject.value;
  }

  /**
   * Check if user is authenticated
   * 
   * @returns true if user is authenticated, false otherwise
   */
  isAuthenticated(): boolean {
    return this.isAuthenticatedSubject.value;
  }

  /**
   * Get authentication token
   * 
   * Retrieves token from storage (checks multiple locations).
   * 
   * @returns JWT token or null
   */
  getToken(): string | null {
    // Check localStorage first
    const token = this.localStorage.get<string>(environment.auth.tokenKey);
    if (token) return token;

    // Check sessionStorage
    const sessionToken = this.sessionStorage.get<string>(environment.auth.tokenKey);
    if (sessionToken) return sessionToken;

    // Check cookies
    const cookieToken = this.cookieService.get(environment.auth.tokenKey);
    if (cookieToken) return cookieToken;

    return null;
  }

  /**
   * Set authentication token
   * 
   * Stores token in multiple locations for redundancy.
   * 
   * @param token - JWT token to store
   */
  private setToken(token: string): void {
    // Store in localStorage (persists across sessions)
    this.localStorage.set(environment.auth.tokenKey, token);
    
    // Store in sessionStorage (cleared on tab close)
    this.sessionStorage.set(environment.auth.tokenKey, token);
    
    // Store in cookie (sent with requests, can be HttpOnly on server)
    this.cookieService.set(environment.auth.tokenKey, token, {
      expires: environment.auth.tokenExpirationTime / 86400, // Convert seconds to days
      secure: environment.production, // Only secure in production
      sameSite: 'lax'
    });
  }

  /**
   * Set refresh token
   * 
   * @param refreshToken - Refresh token to store
   */
  private setRefreshToken(refreshToken: string): void {
    this.localStorage.set(environment.auth.refreshTokenKey, refreshToken);
  }

  /**
   * Get refresh token
   * 
   * @returns Refresh token or null
   */
  getRefreshToken(): string | null {
    return this.localStorage.get<string>(environment.auth.refreshTokenKey);
  }

  /**
   * Set current user
   * 
   * Stores user data in storage.
   * 
   * @param user - User object to store
   */
  private setUser(user: User): void {
    this.localStorage.set('currentUser', user);
    this.sessionStorage.set('currentUser', user);
  }

  /**
   * Refresh authentication token
   * 
   * Uses refresh token to obtain a new access token.
   * 
   * @returns Observable that emits the new token
   */
  refreshToken(): Observable<string> {
    const refreshToken = this.getRefreshToken();
    
    if (!refreshToken) {
      return throwError(() => new Error('No refresh token available'));
    }

    return this.apiService.post<{ token: string }>('/auth/refresh', { refreshToken }).pipe(
      tap((response) => {
        this.setToken(response.token);
      }),
      map((response) => response.token),
      catchError((error) => {
        // If refresh fails, logout user
        this.logout();
        return throwError(() => error);
      })
    );
  }

  /**
   * Check if user has specific role
   * 
   * @param role - Role to check
   * @returns true if user has the role, false otherwise
   */
  hasRole(role: string): boolean {
    const user = this.getCurrentUser();
    return user?.role === role;
  }

  /**
   * Check if user has any of the specified roles
   * 
   * @param roles - Array of roles to check
   * @returns true if user has any of the roles, false otherwise
   */
  hasAnyRole(roles: string[]): boolean {
    const user = this.getCurrentUser();
    return user ? roles.includes(user.role) : false;
  }
}

