// @ts-nocheck
import { Component, EventEmitter, Input, Output } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'ui-modal',
  standalone: true,
  imports: [CommonModule],
  template: `
    <section class="backdrop" *ngIf="open" (click)="onBackdropClick($event)">
      <article class="modal" role="dialog" [attr.aria-modal]="true" [attr.aria-label]="title">
        <header class="modal__header">
          <h2>{{ title }}</h2>
          <button type="button" (click)="requestClose.emit()">×</button>
        </header>
        <section class="modal__body">
          <ng-content></ng-content>
        </section>
        <footer class="modal__footer">
          <ng-content select="[modal-actions]"></ng-content>
        </footer>
      </article>
    </section>
  `,
  styles: [
    `
      .backdrop {
        position: fixed;
        inset: 0;
        background: rgba(15, 23, 42, 0.46);
        display: grid;
        place-items: center;
        backdrop-filter: blur(4px);
      }
      .modal {
        background: white;
        border-radius: 1rem;
        width: min(32rem, 90vw);
        display: grid;
        gap: 1.5rem;
        padding: 1.5rem;
        box-shadow: 0 25px 50px -12px rgba(15, 23, 42, 0.35);
      }
      .modal__header {
        display: flex;
        justify-content: space-between;
        align-items: center;
      }
      .modal__footer {
        display: flex;
        justify-content: flex-end;
        gap: 0.75rem;
      }
      button {
        border: none;
        background: transparent;
        font-size: 1.5rem;
        cursor: pointer;
      }
    `,
  ],
})
export class ModalComponent {
  @Input() open = false;
  @Input() title = 'Modal title';
  @Output() requestClose = new EventEmitter<void>();

  onBackdropClick(event: MouseEvent): void {
    if (event.target === event.currentTarget) {
      this.requestClose.emit();
    }
  }
}
