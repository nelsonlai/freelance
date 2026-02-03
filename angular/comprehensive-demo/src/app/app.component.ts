/**
 * Root Application Component
 * 
 * This is the root component of the Angular application.
 * It serves as the container for all other components.
 * 
 * Component Structure:
 * - selector: HTML tag name for the component
 * - templateUrl: Path to HTML template
 * - styleUrls: Array of style file paths
 * - standalone: true means this is a standalone component (Angular 14+)
 * 
 * Standalone Components:
 * - Don't need to be declared in a module
 * - Can import other standalone components/directives/pipes directly
 * - Modern Angular approach (recommended)
 */

import { Component, OnInit, OnDestroy, inject } from '@angular/core';
import { RouterOutlet, RouterLink, RouterLinkActive } from '@angular/router';
import { CommonModule } from '@angular/common';
import { Subscription } from 'rxjs';
import { AuthService } from './core/services/auth/auth.service';
import { AppStateService } from './state/app.state';
import { IndexedDBService } from './core/services/storage/indexed-db.service';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    CommonModule,
    RouterOutlet,
    RouterLink,
    RouterLinkActive
  ],
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit, OnDestroy {
  title = 'Angular Comprehensive Demo';

  // Inject services using inject() function (Angular 14+)
  private authService = inject(AuthService);
  private appState = inject(AppStateService);
  private indexedDB = inject(IndexedDBService);

  // Subscription management
  private subscriptions = new Subscription();

  /**
   * Observable of current user
   * Components can subscribe to this to react to auth changes
   */
  currentUser$ = this.authService.currentUser$;

  /**
   * Observable of authentication status
   */
  isAuthenticated$ = this.authService.isAuthenticated$;

  /**
   * Lifecycle hook - called after component initialization
   * 
   * ngOnInit is the right place to:
   * - Initialize component data
   * - Subscribe to observables
   * - Make initial API calls
   */
  ngOnInit(): void {
    // Initialize IndexedDB
    this.initializeIndexedDB();

    // Subscribe to authentication state
    const authSub = this.authService.currentUser$.subscribe(user => {
      if (user) {
        // Update app state when user logs in
        this.appState.setUser(user);
      } else {
        // Clear app state when user logs out
        this.appState.setUser(null);
      }
    });
    this.subscriptions.add(authSub);

    // Subscribe to theme changes
    const themeSub = this.appState.select(state => state.theme).subscribe(theme => {
      // Theme is already applied in AppStateService
      console.log('Theme changed to:', theme);
    });
    this.subscriptions.add(themeSub);
  }

  /**
   * Lifecycle hook - called when component is destroyed
   * 
   * Clean up subscriptions to prevent memory leaks
   */
  ngOnDestroy(): void {
    this.subscriptions.unsubscribe();
  }

  /**
   * Initialize IndexedDB
   * 
   * Sets up the IndexedDB database on app startup.
   */
  private initializeIndexedDB(): void {
    this.indexedDB.init().subscribe({
      next: () => {
        console.log('IndexedDB initialized successfully');
      },
      error: (error) => {
        console.error('Failed to initialize IndexedDB:', error);
      }
    });
  }

  /**
   * Logout handler
   * 
   * Called when user clicks logout button.
   */
  logout(): void {
    this.authService.logout();
  }
}

