// @ts-nocheck
import { Component, inject } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { MetricsService } from './metrics.service';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [RouterOutlet],
  template: `
    <section class="dashboard">
      <header>
        <h1>Analytics Dashboard</h1>
        <button type="button" (click)="refresh()">Refresh Data</button>
      </header>

      <nav>
        <a routerLink="metrics" routerLinkActive="active">Metrics</a>
        <a routerLink="activity" routerLinkActive="active">Activity</a>
      </nav>

      <section class="outlet">
        <router-outlet></router-outlet>
      </section>
    </section>
  `,
  styles: [
    `
      .dashboard {
        display: grid;
        gap: 1.5rem;
      }
      header {
        display: flex;
        justify-content: space-between;
        align-items: center;
      }
      nav {
        display: inline-flex;
        gap: 1rem;
      }
      a {
        text-decoration: none;
        color: #1d4ed8;
      }
      a.active {
        font-weight: 700;
        border-bottom: 2px solid currentColor;
      }
      button {
        border: none;
        background: #2563eb;
        color: white;
        padding: 0.5rem 1rem;
        border-radius: 0.5rem;
        cursor: pointer;
      }
    `,
  ],
})
export class DashboardComponent {
  private metrics = inject(MetricsService);

  refresh(): void {
    this.metrics.refresh();
  }
}
