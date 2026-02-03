/**
 * Session Storage Service
 * 
 * This service provides a typed wrapper around the browser's sessionStorage API.
 * 
 * Key Differences from LocalStorage:
 * - Data persists only for the current browser tab/window session
 * - Data is cleared when the tab/window is closed
 * - Each tab has its own independent sessionStorage
 * - Storage limit: typically 5-10MB
 * 
 * Use Cases:
 * - Temporary form data
 * - Tab-specific state
 * - Data that should not persist across sessions
 * - Multi-step form progress
 * - Shopping cart (if you want it cleared on close)
 */

import { Injectable } from '@angular/core';
import { environment } from '../../../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class SessionStorageService {
  private readonly prefix: string = environment.storage.sessionStoragePrefix;

  /**
   * Check if sessionStorage is available
   */
  private isAvailable(): boolean {
    try {
      const test = '__sessionStorage_test__';
      sessionStorage.setItem(test, test);
      sessionStorage.removeItem(test);
      return true;
    } catch {
      return false;
    }
  }

  /**
   * Get a value from sessionStorage
   * 
   * @param key - The key to retrieve (without prefix)
   * @param defaultValue - Optional default value if key doesn't exist
   * @returns The stored value or default value
   */
  get<T>(key: string, defaultValue?: T): T | null {
    if (!this.isAvailable()) {
      console.warn('sessionStorage is not available');
      return defaultValue ?? null;
    }

    try {
      const prefixedKey = `${this.prefix}${key}`;
      const item = sessionStorage.getItem(prefixedKey);
      
      if (item === null) {
        return defaultValue ?? null;
      }

      return JSON.parse(item) as T;
    } catch (error) {
      console.error(`Error reading from sessionStorage for key "${key}":`, error);
      return defaultValue ?? null;
    }
  }

  /**
   * Set a value in sessionStorage
   * 
   * @param key - The key to store (without prefix)
   * @param value - The value to store (will be JSON stringified)
   * @returns true if successful, false otherwise
   */
  set<T>(key: string, value: T): boolean {
    if (!this.isAvailable()) {
      console.warn('sessionStorage is not available');
      return false;
    }

    try {
      const prefixedKey = `${this.prefix}${key}`;
      const serialized = JSON.stringify(value);
      sessionStorage.setItem(prefixedKey, serialized);
      return true;
    } catch (error) {
      if (error instanceof DOMException && error.name === 'QuotaExceededError') {
        console.error('sessionStorage quota exceeded.');
      } else {
        console.error(`Error writing to sessionStorage for key "${key}":`, error);
      }
      return false;
    }
  }

  /**
   * Remove a value from sessionStorage
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
      sessionStorage.removeItem(prefixedKey);
      return true;
    } catch (error) {
      console.error(`Error removing from sessionStorage for key "${key}":`, error);
      return false;
    }
  }

  /**
   * Clear all sessionStorage items with the app's prefix
   * 
   * @returns true if successful, false otherwise
   */
  clear(): boolean {
    if (!this.isAvailable()) {
      return false;
    }

    try {
      const keys: string[] = [];
      
      for (let i = 0; i < sessionStorage.length; i++) {
        const key = sessionStorage.key(i);
        if (key?.startsWith(this.prefix)) {
          keys.push(key);
        }
      }

      keys.forEach(key => sessionStorage.removeItem(key));
      return true;
    } catch (error) {
      console.error('Error clearing sessionStorage:', error);
      return false;
    }
  }

  /**
   * Check if a key exists in sessionStorage
   * 
   * @param key - The key to check (without prefix)
   * @returns true if key exists, false otherwise
   */
  has(key: string): boolean {
    if (!this.isAvailable()) {
      return false;
    }

    const prefixedKey = `${this.prefix}${key}`;
    return sessionStorage.getItem(prefixedKey) !== null;
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
    for (let i = 0; i < sessionStorage.length; i++) {
      const key = sessionStorage.key(i);
      if (key?.startsWith(this.prefix)) {
        keys.push(key.substring(this.prefix.length));
      }
    }
    return keys;
  }
}

