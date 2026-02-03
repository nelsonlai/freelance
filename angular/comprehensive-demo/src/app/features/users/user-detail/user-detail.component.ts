import { Component, OnInit, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ActivatedRoute, RouterLink } from '@angular/router';
import { ApiService } from '../../../core/services/http/api.service';
import { User } from '../../../models/user.model';

@Component({
  selector: 'app-user-detail',
  standalone: true,
  imports: [CommonModule, RouterLink],
  template: `
    <div class="user-detail-container">
      <h1>User Details</h1>
      <div *ngIf="user">
        <div class="user-card">
          <h2>{{ user.firstName }} {{ user.lastName }}</h2>
          <p><strong>Email:</strong> {{ user.email }}</p>
          <p><strong>Role:</strong> {{ user.role }}</p>
          <p><strong>Status:</strong> {{ user.isActive ? 'Active' : 'Inactive' }}</p>
        </div>
      </div>
      <div *ngIf="!user && !loading">User not found</div>
      <a routerLink="/users" class="btn btn-secondary">Back to Users</a>
    </div>
  `,
  styles: [`
    .user-detail-container {
      max-width: 800px;
      margin: 0 auto;
      padding: 2rem;

      .user-card {
        background: white;
        padding: 2rem;
        border-radius: 8px;
        margin-bottom: 1rem;
        box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
      }
    }
  `]
})
export class UserDetailComponent implements OnInit {
  private route = inject(ActivatedRoute);
  private apiService = inject(ApiService);

  user: User | null = null;
  loading = false;

  ngOnInit(): void {
    const id = this.route.snapshot.paramMap.get('id');
    if (id) {
      this.loadUser(+id);
    }
  }

  loadUser(id: number): void {
    this.loading = true;
    this.apiService.get<User>(`/users/${id}`).subscribe({
      next: (user) => {
        this.user = user;
        this.loading = false;
      },
      error: () => {
        // Mock data for demo
        this.user = {
          id: +this.route.snapshot.paramMap.get('id')!,
          firstName: 'John',
          lastName: 'Doe',
          email: 'john@example.com',
          role: 'user',
          isActive: true,
          createdAt: new Date().toISOString(),
          updatedAt: new Date().toISOString()
        };
        this.loading = false;
      }
    });
  }
}

