// @ts-nocheck
import { Component, Input } from '@angular/core';
import { NgFor } from '@angular/common';

@Component({
  selector: 'app-activity-feed',
  standalone: true,
  imports: [NgFor],
  template: `
    <section>
      <h2>Recent Activity</h2>
      <ul>
        <li *ngFor="let item of activity">
          <span class="name">{{ item.name }}</span>
          <span class="status" [class.active]="item.status === 'active'">{{ item.status }}</span>
        </li>
      </ul>
    </section>
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
  @Input({ required: true }) activity: { name: string; status: string }[] = [];
}
