// @ts-nocheck
import { Injectable, inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { API_BASE_URL } from './api-token';
import { Observable } from 'rxjs';

export interface RegistrationRequest {
  name: string;
  email: string;
  role: string;
  newsletter: boolean;
  password: string;
}

export interface RegistrationResponse {
  receivedAt: string;
  data: RegistrationRequest;
  message: string;
}

@Injectable({ providedIn: 'root' })
export class ApiService {
  private http = inject(HttpClient);
  private baseUrl = inject(API_BASE_URL);

  submitRegistration(payload: RegistrationRequest): Observable<RegistrationResponse> {
    return this.http.post<RegistrationResponse>(`${this.baseUrl}/contact`, payload);
  }
}
