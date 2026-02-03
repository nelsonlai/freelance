// @ts-nocheck
import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'ui-button',
  standalone: true,
  imports: [CommonModule],
  template: `
    <button
      class="btn"
      [attr.aria-label]="ariaLabel || label"
      [disabled]="disabled"
      [ngClass]="variant"
      type="button"
    >
      <ng-content></ng-content>
      <span *ngIf="useLabelFallback">{{ label }}</span>
    </button>
  `,
  styles: [
    `
      .btn {
        display: inline-flex;
        align-items: center;
        justify-content: center;
        gap: 0.5rem;
        padding: 0.5rem 1rem;
        border-radius: 0.5rem;
        border: none;
        font-weight: 600;
        cursor: pointer;
        transition: transform 150ms ease, box-shadow 150ms ease;
      }
      .btn:disabled {
        opacity: 0.6;
        cursor: not-allowed;
      }
      .primary {
        background: #2563eb;
        color: white;
        box-shadow: 0 10px 15px -3px rgba(37, 99, 235, 0.3);
      }
      .secondary {
        background: #f3f4f6;
        color: #1f2937;
      }
      .ghost {
        background: transparent;
        color: #111827;
        border: 1px solid currentColor;
      }
    `,
  ],
})
export class ButtonComponent {
  @Input() label = 'Click me';
  @Input() variant: 'primary' | 'secondary' | 'ghost' = 'primary';
  @Input() disabled = false;
  @Input() ariaLabel?: string;
  @Input() useLabelFallback = false;
}
