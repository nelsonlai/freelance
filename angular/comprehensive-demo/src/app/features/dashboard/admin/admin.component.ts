import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-admin',
  standalone: true,
  imports: [CommonModule],
  template: `
    <div class="admin-container">
      <h1>Admin Panel</h1>
      <p>This page is only accessible to users with admin role.</p>
      <p>Protected by roleGuard with data: {{ '{' }} roles: ['admin'] {{ '}' }}</p>
    </div>
  `,
  styles: [`
    .admin-container {
      max-width: 800px;
      margin: 0 auto;
      padding: 2rem;
      background: white;
      border-radius: 8px;
      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    }
  `]
})
export class AdminComponent {}

