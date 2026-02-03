// @ts-nocheck
import { Injectable, inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({ providedIn: 'root' })
export class LoggerService {
  private http = inject(HttpClient);
  private endpoint = '/api/logs';

  info(message: string, context?: Record<string, unknown>): void {
    this.dispatch('info', message, context);
  }

  warn(message: string, context?: Record<string, unknown>): void {
    this.dispatch('warn', message, context);
  }

  error(message: string, context?: Record<string, unknown>): void {
    this.dispatch('error', message, context);
  }

  private dispatch(level: 'info' | 'warn' | 'error', message: string, context?: Record<string, unknown>) {
    if (typeof window === 'undefined') {
      console[level](`[server] ${message}`, context);
      return;
    }

    void this.http.post(this.endpoint, {
      level,
      message,
      context,
      timestamp: new Date().toISOString(),
    }).toPromise();
  }
}
