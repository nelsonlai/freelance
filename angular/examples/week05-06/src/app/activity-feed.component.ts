// @ts-nocheck
import { Component, inject } from '@angular/core';
import { AsyncPipe, NgFor, NgIf } from '@angular/common';
import { MetricsService } from './metrics.service';

@Component({
  selector: 'app-activity-feed',
  standalone: true,
  imports: [AsyncPipe, NgFor, NgIf],
  template: `
    <section *ngIf="projects$ | async as projects; else loading">
      <h2>Recent Activity</h2>
      <ul>
        <li *ngFor="let item of projects">
          <span class="name">{{ item.name }}</span>
          <span class="status" [class.active]="item.status === 'active'">{{ item.status }}</span>
        </li>
      </ul>
    </section>
    <ng-template #loading>
      <p>Loading activity…</p>
    </ng-template>
  `,
  styles: [
    `
      ul {
        display: grid;
        gap: 0.75rem;
      }
      li {
        display: flex;
        justify-content: space-between;
        padding: 0.75rem 1rem;
        border-radius: 0.75rem;
        border: 1px solid #e5e7eb;
      }
      .status.active {
        color: #16a34a;
        font-weight: 600;
      }
    `,
  ],
})
export class ActivityFeedComponent {
  private metricsService = inject(MetricsService);
  projects$ = this.metricsService.fetchProjects();
}
