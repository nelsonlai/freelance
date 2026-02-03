/**
 * Application State Management
 * 
 * This file demonstrates basic state management in Angular.
 * 
 * State Management Options in Angular:
 * 1. Services with BehaviorSubject (shown here) - Simple, built-in
 * 2. NgRx - Full Redux pattern with actions, reducers, effects
 * 3. Akita - Simpler alternative to NgRx
 * 4. Ngxs - Another Redux-inspired library
 * 
 * This implementation uses RxJS BehaviorSubject for simple state management.
 * For larger applications, consider using NgRx or similar libraries.
 * 
 * State Management Principles:
 * - Single source of truth
 * - State is read-only (immutable updates)
 * - Changes are made through actions/methods
 * - Components subscribe to state changes
 */

import { Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';
import { map } from 'rxjs/operators';

/**
 * Application State Interface
 * 
 * Defines the shape of the application's global state.
 * In a larger app, this might be split into feature modules.
 */
export interface AppState {
  /**
   * Current user (if authenticated)
   */
  user: any | null;

  /**
   * Loading state for async operations
   */
  loading: boolean;

  /**
   * Error messages
   */
  error: string | null;

  /**
   * Theme preference
   */
  theme: 'light' | 'dark';

  /**
   * Language/locale
   */
  locale: string;

  /**
   * Notifications
   */
  notifications: Notification[];
}

/**
 * Notification Interface
 */
export interface Notification {
  id: string;
  type: 'success' | 'error' | 'warning' | 'info';
  message: string;
  timestamp: Date;
}

/**
 * Application State Service
 * 
 * Manages global application state using BehaviorSubject.
 * This is a simple state management solution suitable for
 * small to medium applications.
 */
@Injectable({
  providedIn: 'root'
})
export class AppStateService {
  /**
   * Initial state
   * This is the default state when the app starts
   */
  private initialState: AppState = {
    user: null,
    loading: false,
    error: null,
    theme: 'light',
    locale: 'en',
    notifications: []
  };

  /**
   * BehaviorSubject holding the current state
   * BehaviorSubject ensures new subscribers get the current value immediately
   */
  private stateSubject = new BehaviorSubject<AppState>(this.initialState);

  /**
   * Public Observable of state
   * Components subscribe to this to react to state changes
   */
  public state$: Observable<AppState> = this.stateSubject.asObservable();

  /**
   * Get current state synchronously
   * 
   * @returns Current state
   */
  getState(): AppState {
    return this.stateSubject.value;
  }

  /**
   * Update state
   * 
   * Creates a new state object (immutability) and emits it.
   * 
   * @param updates - Partial state updates
   * 
   * @example
   * this.appState.updateState({ loading: true });
   */
  updateState(updates: Partial<AppState>): void {
    const currentState = this.stateSubject.value;
    const newState = { ...currentState, ...updates };
    this.stateSubject.next(newState);
  }

  /**
   * Set user
   * 
   * @param user - User object or null
   */
  setUser(user: any | null): void {
    this.updateState({ user });
  }

  /**
   * Set loading state
   * 
   * @param loading - Loading flag
   */
  setLoading(loading: boolean): void {
    this.updateState({ loading });
  }

  /**
   * Set error
   * 
   * @param error - Error message or null
   */
  setError(error: string | null): void {
    this.updateState({ error });
  }

  /**
   * Set theme
   * 
   * @param theme - Theme name
   */
  setTheme(theme: 'light' | 'dark'): void {
    this.updateState({ theme });
    // Apply theme to document
    document.documentElement.setAttribute('data-theme', theme);
  }

  /**
   * Set locale
   * 
   * @param locale - Locale code (e.g., 'en', 'es', 'fr')
   */
  setLocale(locale: string): void {
    this.updateState({ locale });
  }

  /**
   * Add notification
   * 
   * @param notification - Notification to add
   */
  addNotification(notification: Omit<Notification, 'id' | 'timestamp'>): void {
    const newNotification: Notification = {
      ...notification,
      id: this.generateId(),
      timestamp: new Date()
    };

    const currentNotifications = this.stateSubject.value.notifications;
    this.updateState({
      notifications: [...currentNotifications, newNotification]
    });

    // Auto-remove notification after 5 seconds
    setTimeout(() => {
      this.removeNotification(newNotification.id);
    }, 5000);
  }

  /**
   * Remove notification
   * 
   * @param id - Notification ID
   */
  removeNotification(id: string): void {
    const currentNotifications = this.stateSubject.value.notifications;
    this.updateState({
      notifications: currentNotifications.filter(n => n.id !== id)
    });
  }

  /**
   * Clear all notifications
   */
  clearNotifications(): void {
    this.updateState({ notifications: [] });
  }

  /**
   * Select specific state slice
   * 
   * Returns an Observable of a specific part of the state.
   * This is useful for performance - components only subscribe
   * to the data they need.
   * 
   * @param selector - Function to select state slice
   * @returns Observable of selected state
   * 
   * @example
   * // Subscribe only to loading state
   * this.appState.select(state => state.loading)
   *   .subscribe(loading => console.log(loading));
   */
  select<T>(selector: (state: AppState) => T): Observable<T> {
    return this.state$.pipe(
      map(selector)
    );
  }

  /**
   * Reset state to initial values
   */
  reset(): void {
    this.stateSubject.next(this.initialState);
  }

  /**
   * Generate unique ID for notifications
   * 
   * @returns Unique ID string
   */
  private generateId(): string {
    return `${Date.now()}-${Math.random().toString(36).substr(2, 9)}`;
  }
}

