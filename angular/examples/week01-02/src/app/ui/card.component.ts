// @ts-nocheck
import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'ui-card',
  standalone: true,
  imports: [CommonModule],
  template: `
    <article class="card" [ngClass]="variant">
      <header *ngIf="title" class="card__header">
        <h3>{{ title }}</h3>
        <ng-content select="[card-actions]"></ng-content>
      </header>

      <section class="card__body">
        <ng-content></ng-content>
      </section>

      <footer *ngIf="footer" class="card__footer">{{ footer }}</footer>
    </article>
  `,
  styles: [
    `
      .card {
        background: white;
        border-radius: 1rem;
        padding: 1.5rem;
        box-shadow: 0 10px 30px rgba(15, 23, 42, 0.12);
        display: grid;
        gap: 1rem;
      }
      .card__header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        gap: 1rem;
      }
      .card__footer {
        font-size: 0.875rem;
        color: #6b7280;
      }
      .outlined {
        border: 1px solid #e5e7eb;
        box-shadow: none;
      }
    `,
  ],
})
export class CardComponent {
  @Input() title?: string;
  @Input() footer?: string;
  @Input() variant: 'elevated' | 'outlined' = 'elevated';
}
