/**
 * Local Storage Service
 * 
 * This service provides a typed, safe wrapper around the browser's localStorage API.
 * 
 * Key Features:
 * - Type-safe storage operations
 * - Automatic JSON serialization/deserialization
 * - Error handling for quota exceeded and other storage errors
 * - Prefix support to avoid key collisions
 * - Environment-aware configuration
 * 
 * LocalStorage vs SessionStorage:
 * - LocalStorage persists data until explicitly cleared
 * - Data survives browser restarts
 * - Shared across all tabs/windows of the same origin
 * - Storage limit: typically 5-10MB
 * 
 * Use Cases:
 * - User preferences
 * - Cached data that should persist
 * - Shopping cart contents
 * - Theme settings
 */

import { Injectable } from '@angular/core';
import { environment } from '../../../../environments/environment';

@Injectable({
  providedIn: 'root' // Makes this service available application-wide as a singleton
})
export class LocalStorageService {
  /**
   * Prefix for all localStorage keys
   * Prevents conflicts with other applications on the same domain
   */
  private readonly prefix: string = environment.storage.localStoragePrefix;

  /**
   * Check if localStorage is available
   * Some browsers or privacy modes may disable localStorage
   */
  private isAvailable(): boolean {
    try {
      const test = '__localStorage_test__';
      localStorage.setItem(test, test);
      localStorage.removeItem(test);
      return true;
    } catch {
      return false;
    }
  }

  /**
   * Get a value from localStorage
   * 
   * @param key - The key to retrieve (without prefix)
   * @param defaultValue - Optional default value if key doesn't exist
   * @returns The stored value or default value
   * 
   * @example
   * const user = this.localStorage.get('user', { name: 'Guest' });
   */
  get<T>(key: string, defaultValue?: T): T | null {
    if (!this.isAvailable()) {
      console.warn('localStorage is not available');
      return defaultValue ?? null;
    }

    try {
      const prefixedKey = `${this.prefix}${key}`;
      const item = localStorage.getItem(prefixedKey);
      
      if (item === null) {
        return defaultValue ?? null;
      }

      // Parse JSON string back to object
      return JSON.parse(item) as T;
    } catch (error) {
      console.error(`Error reading from localStorage for key "${key}":`, error);
      return defaultValue ?? null;
    }
  }

  /**
   * Set a value in localStorage
   * 
   * @param key - The key to store (without prefix)
   * @param value - The value to store (will be JSON stringified)
   * @returns true if successful, false otherwise
   * 
   * @example
   * this.localStorage.set('user', { name: 'John', id: 1 });
   */
  set<T>(key: string, value: T): boolean {
    if (!this.isAvailable()) {
      console.warn('localStorage is not available');
      return false;
    }

    try {
      const prefixedKey = `${this.prefix}${key}`;
      const serialized = JSON.stringify(value);
      localStorage.setItem(prefixedKey, serialized);
      return true;
    } catch (error) {
      if (error instanceof DOMException && error.name === 'QuotaExceededError') {
        console.error('localStorage quota exceeded. Consider clearing old data.');
      } else {
        console.error(`Error writing to localStorage for key "${key}":`, error);
      }
      return false;
    }
  }

  /**
   * Remove a value from localStorage
   * 
   * @param key - The key to remove (without prefix)
   * @returns true if successful, false otherwise
   */
  remove(key: string): boolean {
    if (!this.isAvailable()) {
      return false;
    }

    try {
      const prefixedKey = `${this.prefix}${key}`;
      localStorage.removeItem(prefixedKey);
      return true;
    } catch (error) {
      console.error(`Error removing from localStorage for key "${key}":`, error);
      return false;
    }
  }

  /**
   * Clear all localStorage items with the app's prefix
   * 
   * Note: This only clears items with our prefix, not all localStorage data
   * 
   * @returns true if successful, false otherwise
   */
  clear(): boolean {
    if (!this.isAvailable()) {
      return false;
    }

    try {
      const keys: string[] = [];
      
      // Collect all keys with our prefix
      for (let i = 0; i < localStorage.length; i++) {
        const key = localStorage.key(i);
        if (key?.startsWith(this.prefix)) {
          keys.push(key);
        }
      }

      // Remove all collected keys
      keys.forEach(key => localStorage.removeItem(key));
      return true;
    } catch (error) {
      console.error('Error clearing localStorage:', error);
      return false;
    }
  }

  /**
   * Check if a key exists in localStorage
   * 
   * @param key - The key to check (without prefix)
   * @returns true if key exists, false otherwise
   */
  has(key: string): boolean {
    if (!this.isAvailable()) {
      return false;
    }

    const prefixedKey = `${this.prefix}${key}`;
    return localStorage.getItem(prefixedKey) !== null;
  }

  /**
   * Get all keys stored by this application
   * 
   * @returns Array of keys (without prefix)
   */
  getAllKeys(): string[] {
    if (!this.isAvailable()) {
      return [];
    }

    const keys: string[] = [];
    for (let i = 0; i < localStorage.length; i++) {
      const key = localStorage.key(i);
      if (key?.startsWith(this.prefix)) {
        // Remove prefix before returning
        keys.push(key.substring(this.prefix.length));
      }
    }
    return keys;
  }
}

