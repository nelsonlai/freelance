// @ts-nocheck
import { Component, signal } from '@angular/core';
import { ButtonComponent } from './button.component';
import { CardComponent } from './card.component';
import { ModalComponent } from './modal.component';

@Component({
  selector: 'app-sandbox',
  standalone: true,
  imports: [ButtonComponent, CardComponent, ModalComponent],
  template: `
    <section class="grid">
      <ui-card title="Kitchen Sink">
        <p>Build a library of components you can reuse throughout your apps.</p>
        <div card-actions>
          <ui-button (click)="toggleModal(true)">Show Modal</ui-button>
        </div>
      </ui-card>

      <ui-card title="Variants" variant="outlined">
        <ui-button variant="primary">Primary</ui-button>
        <ui-button variant="secondary">Secondary</ui-button>
        <ui-button variant="ghost">Ghost</ui-button>
      </ui-card>
    </section>

    <ui-modal [open]="modalOpen()" title="Component Library" (requestClose)="toggleModal(false)">
      <p>
        Component libraries accelerate development. Document props, events, and visual states with stories.
      </p>
      <div modal-actions>
        <ui-button variant="secondary" (click)="toggleModal(false)">Close</ui-button>
        <ui-button (click)="toggleModal(false)">Got it</ui-button>
      </div>
    </ui-modal>
  `,
  styles: [
    `
      .grid {
        display: grid;
        gap: 2rem;
        grid-template-columns: repeat(auto-fit, minmax(18rem, 1fr));
      }
    `,
  ],
})
export class SandboxComponent {
  modalOpen = signal(false);

  toggleModal(state: boolean): void {
    this.modalOpen.set(state);
  }
}
