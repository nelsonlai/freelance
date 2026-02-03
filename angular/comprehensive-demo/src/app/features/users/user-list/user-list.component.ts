/**
 * User List Component
 * 
 * Demonstrates:
 * - HTTP service usage
 * - Observable handling
 * - Error handling
 * - Loading states
 * - Data binding with *ngFor
 */

import { Component, OnInit, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';
import { ApiService } from '../../../core/services/http/api.service';
import { User } from '../../../models/user.model';
import { AppStateService } from '../../../state/app.state';

@Component({
  selector: 'app-user-list',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './user-list.component.html',
  styleUrls: ['./user-list.component.scss']
})
export class UserListComponent implements OnInit {
  private apiService = inject(ApiService);
  private appState = inject(AppStateService);

  users: User[] = [];
  loading = false;
  error: string | null = null;

  ngOnInit(): void {
    this.loadUsers();
  }

  loadUsers(): void {
    this.loading = true;
    this.error = null;
    this.appState.setLoading(true);

    // Note: This would call a real API endpoint
    // For demo purposes, we'll use mock data
    this.apiService.get<User[]>('/users').subscribe({
      next: (users) => {
        this.users = users;
        this.loading = false;
        this.appState.setLoading(false);
      },
      error: (error) => {
        // Only show error if it's not a demo mode error (status 0 in development)
        if (error.message && error.message.trim() !== '') {
          this.error = error.message;
        } else {
          this.error = null; // Don't show error in demo mode
        }
        this.loading = false;
        this.appState.setLoading(false);
        
        // For demo, use mock data
        this.users = this.getMockUsers();
      }
    });
  }

  // Mock data for demonstration
  private getMockUsers(): User[] {
    return [
      {
        id: 1,
        firstName: 'John',
        lastName: 'Doe',
        email: 'john@example.com',
        role: 'user',
        isActive: true,
        createdAt: new Date().toISOString(),
        updatedAt: new Date().toISOString()
      },
      {
        id: 2,
        firstName: 'Jane',
        lastName: 'Smith',
        email: 'jane@example.com',
        role: 'admin',
        isActive: true,
        createdAt: new Date().toISOString(),
        updatedAt: new Date().toISOString()
      }
    ];
  }
}

