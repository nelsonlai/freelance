// @ts-nocheck
import { HttpEvent, HttpHandlerFn, HttpInterceptorFn, HttpRequest } from '@angular/common/http';
import { inject } from '@angular/core';
import { Observable, catchError } from 'rxjs';
import { AuthService } from './auth.service';
import { ToastService } from './toast.service';

export const authInterceptor: HttpInterceptorFn = (req: HttpRequest<unknown>, next: HttpHandlerFn): Observable<HttpEvent<unknown>> => {
  const auth = inject(AuthService);
  const toast = inject(ToastService);

  const cloned = auth.isAuthenticated()
    ? req.clone({ setHeaders: { Authorization: 'Bearer fake-jwt-token' } })
    : req;

  return next(cloned).pipe(
    catchError((error) => {
      toast.error('Request failed. Please try again.');
      throw error;
    }),
  );
};
