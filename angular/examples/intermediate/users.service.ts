// @ts-nocheck
import { Injectable, inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, map, shareReplay } from 'rxjs';

export interface UserDto {
  id: number;
  name: string;
  email: string;
  role: 'viewer' | 'editor' | 'admin';
}

@Injectable({ providedIn: 'root' })
export class UsersService {
  private http = inject(HttpClient);

  getUsers(): Observable<UserDto[]> {
    return this.http
      .get<UserDto[]>('/api/users')
      .pipe(shareReplay({ bufferSize: 1, refCount: true }));
  }

  saveUser(payload: Omit<UserDto, 'id'>): Observable<UserDto> {
    return this.http
      .post<UserDto>('/api/users', payload)
      .pipe(map((user) => ({ ...user, role: user.role ?? 'viewer' })));
  }
}
