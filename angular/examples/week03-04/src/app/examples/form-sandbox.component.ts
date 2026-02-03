// @ts-nocheck
import { Component } from '@angular/core';
import { HighlightDirective } from '../shared/highlight.directive';
import { IfViewportDirective } from '../shared/if-viewport.directive';
import { RegistrationFormComponent } from './registration-form.component';

@Component({
  selector: 'app-form-sandbox',
  standalone: true,
  imports: [HighlightDirective, IfViewportDirective, RegistrationFormComponent],
  template: `
    <section class="layout">
      <aside appHighlight="#dbeafe" appHighlightHoverColor="#bfdbfe">
        <h2>Directive Playground</h2>
        <p>
          Resize the browser to see the callout toggle with the viewport structural directive.
        </p>
        <div *appIfViewport="960" class="callout">
          Visible at ≥ 960px. Use structural directives to control complex layouts.
        </div>
      </aside>

      <main>
        <app-registration-form></app-registration-form>
      </main>
    </section>
  `,
  styles: [
    `
      .layout {
        display: grid;
        gap: 2rem;
        grid-template-columns: repeat(auto-fit, minmax(18rem, 1fr));
        align-items: start;
      }
      aside {
        padding: 1.5rem;
        border-radius: 1rem;
      }
      .callout {
        margin-top: 1rem;
        padding: 1rem;
        border-radius: 0.75rem;
        background: #ecfccb;
        color: #365314;
      }
    `,
  ],
})
export class FormSandboxComponent {}
