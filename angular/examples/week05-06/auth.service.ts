// @ts-nocheck
import { Injectable, signal } from '@angular/core';

@Injectable({ providedIn: 'root' })
export class AuthService {
  private authenticated = signal(false);

  isAuthenticated(): boolean {
    return this.authenticated();
  }

  login(): void {
    this.authenticated.set(true);
  }

  logout(): void {
    this.authenticated.set(false);
  }
}
