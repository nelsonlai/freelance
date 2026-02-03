/**
 * Storage Demo Component
 * 
 * Demonstrates all storage mechanisms:
 * - LocalStorage
 * - SessionStorage
 * - Cookies
 * - IndexedDB
 */

import { Component, OnInit, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { LocalStorageService } from '../../../core/services/storage/local-storage.service';
import { SessionStorageService } from '../../../core/services/storage/session-storage.service';
import { CookieService } from '../../../core/services/storage/cookie.service';
import { IndexedDBService } from '../../../core/services/storage/indexed-db.service';

@Component({
  selector: 'app-storage-demo',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './storage-demo.component.html',
  styleUrls: ['./storage-demo.component.scss']
})
export class StorageDemoComponent implements OnInit {
  private localStorage = inject(LocalStorageService);
  private sessionStorage = inject(SessionStorageService);
  private cookieService = inject(CookieService);
  private indexedDB = inject(IndexedDBService);

  // Form data
  storageData = {
    key: '',
    value: ''
  };

  // Display data
  localStorageData: any = null;
  sessionStorageData: any = null;
  cookieData: string | null = null;
  indexedDBData: any[] = [];

  ngOnInit(): void {
    this.loadAllData();
  }

  // LocalStorage operations
  saveToLocalStorage(): void {
    if (this.storageData.key && this.storageData.value) {
      this.localStorage.set(this.storageData.key, this.storageData.value);
      this.loadLocalStorageData();
      this.storageData = { key: '', value: '' };
    }
  }

  loadLocalStorageData(): void {
    if (this.storageData.key) {
      this.localStorageData = this.localStorage.get(this.storageData.key);
    }
  }

  clearLocalStorage(): void {
    this.localStorage.clear();
    this.localStorageData = null;
  }

  // SessionStorage operations
  saveToSessionStorage(): void {
    if (this.storageData.key && this.storageData.value) {
      this.sessionStorage.set(this.storageData.key, this.storageData.value);
      this.loadSessionStorageData();
      this.storageData = { key: '', value: '' };
    }
  }

  loadSessionStorageData(): void {
    if (this.storageData.key) {
      this.sessionStorageData = this.sessionStorage.get(this.storageData.key);
    }
  }

  clearSessionStorage(): void {
    this.sessionStorage.clear();
    this.sessionStorageData = null;
  }

  // Cookie operations
  saveToCookie(): void {
    if (this.storageData.key && this.storageData.value) {
      this.cookieService.set(this.storageData.key, this.storageData.value, {
        expires: 7 // 7 days
      });
      this.loadCookieData();
      this.storageData = { key: '', value: '' };
    }
  }

  loadCookieData(): void {
    if (this.storageData.key) {
      this.cookieData = this.cookieService.get(this.storageData.key);
    }
  }

  removeCookie(): void {
    if (this.storageData.key) {
      this.cookieService.remove(this.storageData.key);
      this.cookieData = null;
    }
  }

  // IndexedDB operations
  saveToIndexedDB(): void {
    if (this.storageData.key && this.storageData.value) {
      const data = {
        id: Date.now(),
        key: this.storageData.key,
        value: this.storageData.value,
        timestamp: new Date().toISOString()
      };

      this.indexedDB.add('cache', data).subscribe({
        next: () => {
          this.loadIndexedDBData();
          this.storageData = { key: '', value: '' };
        },
        error: (error) => console.error('Error saving to IndexedDB:', error)
      });
    }
  }

  loadIndexedDBData(): void {
    this.indexedDB.getAll<any>('cache').subscribe({
      next: (data) => {
        this.indexedDBData = data;
      },
      error: (error) => console.error('Error loading from IndexedDB:', error)
    });
  }

  clearIndexedDB(): void {
    this.indexedDB.clear('cache').subscribe({
      next: () => {
        this.indexedDBData = [];
      },
      error: (error) => console.error('Error clearing IndexedDB:', error)
    });
  }

  // Load all data
  loadAllData(): void {
    this.loadLocalStorageData();
    this.loadSessionStorageData();
    this.loadCookieData();
    this.loadIndexedDBData();
  }
}

