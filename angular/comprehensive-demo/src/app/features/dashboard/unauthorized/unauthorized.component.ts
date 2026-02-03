import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-unauthorized',
  standalone: true,
  imports: [CommonModule, RouterLink],
  template: `
    <div class="unauthorized-container">
      <h1>403 - Unauthorized</h1>
      <p>You do not have permission to access this resource.</p>
      <a routerLink="/dashboard" class="btn btn-primary">Go to Dashboard</a>
    </div>
  `,
  styles: [`
    .unauthorized-container {
      max-width: 600px;
      margin: 0 auto;
      padding: 2rem;
      text-align: center;
      background: white;
      border-radius: 8px;
      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    }
  `]
})
export class UnauthorizedComponent {}

