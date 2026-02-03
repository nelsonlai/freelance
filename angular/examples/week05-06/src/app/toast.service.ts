// @ts-nocheck
import { Injectable } from '@angular/core';

@Injectable({ providedIn: 'root' })
export class ToastService {
  error(message: string): void {
    console.error('[Toast]', message);
  }

  success(message: string): void {
    console.info('[Toast]', message);
  }
}
