# Angular Startup & Modal Interaction (Week 01-02 Sandbox)

## How the App Boots and Renders

1. **Static Host Page**  
   `src/index.html` provides the bare HTML page with `<app-root></app-root>`. This is the DOM node Angular will attach to.

2. **Entry Script (`main.ts`)**  
   ```ts
   import { bootstrapApplication } from '@angular/platform-browser';
   import { appConfig } from './app/app.config';
   import { AppComponent } from './app/app.component';

   bootstrapApplication(AppComponent, appConfig).catch((err) => console.error(err));
   ```
   - `bootstrapApplication` spins up Angular using the standalone API.
   - `AppComponent` is declared as the root component.
   - `appConfig` registers global providers, including routing and zone-based change detection.

3. **App Configuration (`app.config.ts`)**  
   ```ts
   export const appConfig: ApplicationConfig = {
     providers: [
       provideZoneChangeDetection({ eventCoalescing: true }),
       provideRouter(routes),
     ],
   };
   ```
   - Ensures Angular listens for browser events and runs change detection.
   - Registers the router with the route definition that points `/` to the sandbox component.

4. **Root Component (`app.component.ts`)**  
   ```ts
   @Component({
     selector: 'app-root',
     standalone: true,
     imports: [RouterOutlet],
     template: `<router-outlet />`,
   })
   export class AppComponent {}
   ```
   - When bootstrapped, Angular renders `<router-outlet>` into `<app-root>`.
   - The router then loads the `SandboxComponent` for the default route.

5. **Sandbox Route (`app.routes.ts`)**  
   ```ts
   export const routes: Routes = [
     { path: '', component: SandboxComponent },
   ];
   ```
   - Navigating to `/` instantiates `SandboxComponent` and inserts its template into the page.

## How the “Show Modal” Button Works

1. **Sandbox State**  
   ```ts
   export class SandboxComponent {
     modalOpen = signal(false);

     toggleModal(state: boolean): void {
       this.modalOpen.set(state);
     }
   }
   ```
   - `signal(false)` stores modal visibility. Signals are reactive primitives in Angular 16+.
   - `toggleModal(true)` opens the modal; `toggleModal(false)` closes it.

2. **Button Interaction**  
   ```html
   <ui-button (click)="toggleModal(true)">Show Modal</ui-button>
   ```
   - When the user clicks, Angular executes `toggleModal(true)`.
   - The signal updates to `true`, marking `SandboxComponent` for change detection.

3. **Modal Template Binding**  
   ```html
   <ui-modal
     [open]="modalOpen()"
     title="Component Library"
     (requestClose)="toggleModal(false)"
   >
     <!-- modal body -->
   </ui-modal>
   ```
   - The custom `ui-modal` component receives the signal value via `[open]="modalOpen()"`.
   - Angular re-evaluates the template after the signal changes and passes `true` to the modal.

4. **Modal Component Logic**  
   ```ts
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
   })
   export class ModalComponent {
     @Input() open = false;
     @Output() requestClose = new EventEmitter<void>();

     onBackdropClick(event: MouseEvent): void {
       if (event.target === event.currentTarget) {
         this.requestClose.emit();
       }
     }
   }
   ```
   - When `[open]` is `true`, the `*ngIf` renders the modal markup.
   - Clicking the close button or backdrop emits `requestClose`, which calls `toggleModal(false)` in the sandbox.

5. **Angular Change Detection Cycle**  
   - The button click runs inside Angular’s zone; change detection runs automatically.
   - The signal change updates the view, showing the modal instantly without manual DOM manipulation.

## Try It Yourself

```bash
cd examples/week01-02
npm install
npm start
```
- Navigate to `http://localhost:4200` and click **Show Modal** to see the signal-driven UI.
- Modify text or styling in `ui-modal` or `ui-button` and watch the updates live via Angular CLI’s HMR.
