// @ts-nocheck
import { Component, inject } from '@angular/core';
import { AsyncPipe, NgFor, NgIf } from '@angular/common';
import { MetricsService } from './metrics.service';

@Component({
  selector: 'app-metrics-widget',
  standalone: true,
  imports: [AsyncPipe, NgFor, NgIf],
  template: `
    <section *ngIf="metrics$ | async as metrics; else loading">
      <h2>Key Metrics</h2>
      <ul class="metrics">
        <li *ngFor="let metric of metrics">
          <p class="label">{{ metric.label }}</p>
          <p class="value">{{ metric.value | number }}</p>
          <p class="delta" [class.positive]="metric.delta && metric.delta >= 0" [class.negative]="metric.delta && metric.delta < 0">
            {{ metric.delta || 0 }}%
          </p>
        </li>
      </ul>
    </section>
    <ng-template #loading>
      <p>Loading metrics…</p>
    </ng-template>
  `,
  styles: [
    `
      .metrics {
        display: grid;
        gap: 1rem;
        grid-template-columns: repeat(auto-fit, minmax(12rem, 1fr));
      }
      li {
        list-style: none;
        padding: 1rem;
        border-radius: 0.75rem;
        border: 1px solid #e5e7eb;
        display: grid;
        gap: 0.25rem;
      }
      .label {
        font-size: 0.9rem;
        color: #6b7280;
      }
      .value {
        font-size: 1.5rem;
        font-weight: 700;
      }
      .delta {
        font-size: 0.85rem;
      }
      .delta.positive {
        color: #16a34a;
      }
      .delta.negative {
        color: #dc2626;
      }
    `,
  ],
})
export class MetricsWidgetComponent {
  private metricsService = inject(MetricsService);
  metrics$ = this.metricsService.summaries$;
}
