/**
 * IndexedDB Service
 * 
 * This service provides a simplified interface to IndexedDB, a powerful
 * client-side database for storing large amounts of structured data.
 * 
 * IndexedDB vs Other Storage:
 * - Much larger storage capacity (typically 50% of disk space)
 * - Stores structured data (not just strings)
 * - Supports indexes for fast queries
 * - Asynchronous API (non-blocking)
 * - Transaction support
 * - Can store files, blobs, and complex objects
 * 
 * Use Cases:
 * - Large datasets that need to be queried
 * - Offline-first applications
 * - Caching API responses
 * - Storing user-generated content
 * - Progressive Web Apps (PWAs)
 * - File storage
 * 
 * Architecture:
 * - Database: Top-level container
 * - Object Store: Like a table in SQL
 * - Index: For fast lookups on specific fields
 * - Transaction: Ensures data consistency
 */

import { Injectable } from '@angular/core';
import { Observable, from, throwError } from 'rxjs';
import { map, catchError } from 'rxjs/operators';
import { environment } from '../../../../environments/environment';

/**
 * Database Configuration
 */
interface DBConfig {
  name: string;
  version: number;
  stores: StoreConfig[];
}

/**
 * Object Store Configuration
 */
interface StoreConfig {
  name: string;
  keyPath: string; // Primary key field
  autoIncrement?: boolean;
  indexes?: IndexConfig[];
}

/**
 * Index Configuration
 */
interface IndexConfig {
  name: string;
  keyPath: string | string[];
  unique?: boolean;
}

@Injectable({
  providedIn: 'root'
})
export class IndexedDBService {
  private dbName: string = environment.storage.indexedDBName;
  private dbVersion: number = environment.storage.indexedDBVersion;
  private db: IDBDatabase | null = null;

  /**
   * Initialize the IndexedDB database
   * 
   * This method opens the database and creates object stores if they don't exist.
   * It uses the onupgradeneeded event to handle schema changes.
   * 
   * @returns Observable that completes when database is ready
   */
  init(): Observable<IDBDatabase> {
    return new Observable(observer => {
      // Check if IndexedDB is supported
      if (!('indexedDB' in window)) {
        observer.error(new Error('IndexedDB is not supported in this browser'));
        return;
      }

      // Open database connection
      const request = indexedDB.open(this.dbName, this.dbVersion);

      // Handle successful database opening
      request.onsuccess = (event: Event) => {
        this.db = (event.target as IDBOpenDBRequest).result;
        console.log('IndexedDB opened successfully');
        observer.next(this.db!);
        observer.complete();
      };

      // Handle database errors
      request.onerror = (event: Event) => {
        const error = (event.target as IDBOpenDBRequest).error;
        console.error('Error opening IndexedDB:', error);
        observer.error(error);
      };

      // Handle database upgrades (schema changes)
      request.onupgradeneeded = (event: IDBVersionChangeEvent) => {
        const db = (event.target as IDBOpenDBRequest).result;
        
        // Create object stores if they don't exist
        // Users store
        if (!db.objectStoreNames.contains('users')) {
          const userStore = db.createObjectStore('users', { keyPath: 'id', autoIncrement: false });
          userStore.createIndex('email', 'email', { unique: true });
          userStore.createIndex('role', 'role', { unique: false });
        }

        // Products store
        if (!db.objectStoreNames.contains('products')) {
          const productStore = db.createObjectStore('products', { keyPath: 'id', autoIncrement: false });
          productStore.createIndex('category', 'category', { unique: false });
          productStore.createIndex('name', 'name', { unique: false });
        }

        // Cache store for API responses
        if (!db.objectStoreNames.contains('cache')) {
          const cacheStore = db.createObjectStore('cache', { keyPath: 'key' });
          cacheStore.createIndex('timestamp', 'timestamp', { unique: false });
        }

        console.log('IndexedDB schema upgraded');
      };
    });
  }

  /**
   * Add or update a record in an object store
   * 
   * @param storeName - Name of the object store
   * @param data - Data to store
   * @returns Observable that completes when operation finishes
   * 
   * @example
   * this.indexedDB.add('users', { id: 1, name: 'John', email: 'john@example.com' })
   *   .subscribe(result => console.log('User added'));
   */
  add<T>(storeName: string, data: T): Observable<T> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readwrite');
      const store = transaction.objectStore(storeName);
      const request = store.put(data); // put() adds or updates

      request.onsuccess = () => {
        observer.next(data);
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }

  /**
   * Get a record by key
   * 
   * @param storeName - Name of the object store
   * @param key - Primary key value
   * @returns Observable with the record or null if not found
   * 
   * @example
   * this.indexedDB.get<User>('users', 1)
   *   .subscribe(user => console.log(user));
   */
  get<T>(storeName: string, key: IDBValidKey): Observable<T | null> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readonly');
      const store = transaction.objectStore(storeName);
      const request = store.get(key);

      request.onsuccess = () => {
        observer.next((request.result as T) || null);
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }

  /**
   * Get all records from an object store
   * 
   * @param storeName - Name of the object store
   * @returns Observable with array of all records
   * 
   * @example
   * this.indexedDB.getAll<Product>('products')
   *   .subscribe(products => console.log(products));
   */
  getAll<T>(storeName: string): Observable<T[]> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readonly');
      const store = transaction.objectStore(storeName);
      const request = store.getAll();

      request.onsuccess = () => {
        observer.next(request.result as T[]);
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }

  /**
   * Get records by index
   * 
   * @param storeName - Name of the object store
   * @param indexName - Name of the index
   * @param value - Value to search for
   * @returns Observable with array of matching records
   * 
   * @example
   * // Get all products in 'electronics' category
   * this.indexedDB.getByIndex<Product>('products', 'category', 'electronics')
   *   .subscribe(products => console.log(products));
   */
  getByIndex<T>(storeName: string, indexName: string, value: any): Observable<T[]> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readonly');
      const store = transaction.objectStore(storeName);
      const index = store.index(indexName);
      const request = index.getAll(value);

      request.onsuccess = () => {
        observer.next(request.result as T[]);
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }

  /**
   * Delete a record by key
   * 
   * @param storeName - Name of the object store
   * @param key - Primary key value
   * @returns Observable that completes when deletion finishes
   * 
   * @example
   * this.indexedDB.delete('users', 1)
   *   .subscribe(() => console.log('User deleted'));
   */
  delete(storeName: string, key: IDBValidKey): Observable<void> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readwrite');
      const store = transaction.objectStore(storeName);
      const request = store.delete(key);

      request.onsuccess = () => {
        observer.next();
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }

  /**
   * Clear all records from an object store
   * 
   * @param storeName - Name of the object store
   * @returns Observable that completes when clear finishes
   */
  clear(storeName: string): Observable<void> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readwrite');
      const store = transaction.objectStore(storeName);
      const request = store.clear();

      request.onsuccess = () => {
        observer.next();
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }

  /**
   * Count records in an object store
   * 
   * @param storeName - Name of the object store
   * @returns Observable with the count
   */
  count(storeName: string): Observable<number> {
    if (!this.db) {
      return throwError(() => new Error('Database not initialized. Call init() first.'));
    }

    return new Observable(observer => {
      const transaction = this.db!.transaction([storeName], 'readonly');
      const store = transaction.objectStore(storeName);
      const request = store.count();

      request.onsuccess = () => {
        observer.next(request.result);
        observer.complete();
      };

      request.onerror = () => {
        observer.error(request.error);
      };
    });
  }
}

