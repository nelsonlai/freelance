// @ts-nocheck
import { Injectable, inject, signal } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { tap } from 'rxjs';

interface AuthResponse {
  token: string;
  refreshToken: string;
  user: {
    id: string;
    name: string;
    roles: string[];
  };
}

@Injectable({ providedIn: 'root' })
export class AuthHttpService {
  private http = inject(HttpClient);
  private storageKey = 'demo-auth';

  currentUser = signal<AuthResponse['user'] | null>(null);

  constructor() {
    const cached = localStorage.getItem(this.storageKey);
    if (cached) {
      const parsed: AuthResponse = JSON.parse(cached);
      this.currentUser.set(parsed.user);
    }
  }

  login(credentials: { email: string; password: string }) {
    return this.http.post<AuthResponse>('/api/auth/login', credentials).pipe(
      tap((response) => this.persist(response)),
    );
  }

  refresh(refreshToken: string) {
    return this.http.post<AuthResponse>('/api/auth/refresh', { refreshToken }).pipe(
      tap((response) => this.persist(response)),
    );
  }

  logout(): void {
    localStorage.removeItem(this.storageKey);
    this.currentUser.set(null);
  }

  hasRole(role: string): boolean {
    return this.currentUser()?.roles.includes(role) ?? false;
  }

  private persist(response: AuthResponse) {
    localStorage.setItem(this.storageKey, JSON.stringify(response));
    this.currentUser.set(response.user);
  }
}
