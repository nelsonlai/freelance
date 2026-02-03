# Week 03-04 Sandbox: Startup & Request/Response Flow

This document explains, in detail, how the Angular application boots, renders the page, and exchanges data with the Express backend when you submit the registration form.

---

## 1. Development Environment Startup

### 1.1 Backend
1. Run `npm run server` in `examples/week03-04/`.
2. `server.js` starts an Express app on `http://localhost:4000`:
   - Applies `cors()` and `express.json()`.
   - Registers `POST /api/contact` that logs the payload and returns a JSON response with the echoed fields.

### 1.2 Frontend
1. Run `npm start` (alias for `ng serve`).
2. Angular CLI reads `angular.json`:
   - `build.options.browser` → `src/main.ts` (entry point).
   - `build.options.polyfills` → `zone.js`.
   - `serve.options.proxyConfig` → `proxy.conf.json` (proxy `/api` to `http://localhost:4000`).
3. Dev server compiles TypeScript, serves bundles, and enables hot module replacement.

---

## 2. Browser Boot Sequence

1. The dev server serves `src/index.html`. It contains only `<app-root></app-root>` in the body.
2. Bundled JavaScript loads and executes `src/main.ts`:
   ```ts
   bootstrapApplication(AppComponent, appConfig).catch((err) => console.error(err));
   ```
3. `appConfig` (`src/app/app.config.ts`) registers providers:
   - `provideZoneChangeDetection({ eventCoalescing: true })`
   - `provideRouter(routes)` (routes defined in `src/app/app.routes.ts`)
   - `provideHttpClient(withFetch())` (enables HTTP requests)
4. Angular creates the root injector, sets up zone.js patches, and instantiates `AppComponent`.

---

## 3. Rendering the UI

1. `AppComponent` (`src/app/app.component.ts`) is a standalone component with template `<router-outlet />`.
2. Router resolves routes from `app.routes.ts`:
   ```ts
   export const routes: Routes = [
     { path: '', component: FormSandboxComponent },
   ];
   ```
3. Angular creates `FormSandboxComponent` (`src/app/examples/form-sandbox.component.ts`) and renders its template:
   - Applies `HighlightDirective` and `IfViewportDirective`.
   - Displays an informational aside and the `<app-registration-form>` component.
4. `RegistrationFormComponent` (`src/app/examples/registration-form.component.ts`):
   - Standalone component importing `CommonModule` and `ReactiveFormsModule`.
   - Builds a reactive form with fields: `name`, `email`, `role`, `newsletter`, `password`, `confirmPassword`.
   - Uses Angular signals to manage `submitting`, `result`, and `error` state.
   - Template renders the form, validation messages, submit button, and the backend response section.
5. Change detection keeps the UI in sync with form values and signal updates.

---

## 4. Submitting the Form

### 4.1 Collecting & Validating Data
- `submit()` in `RegistrationFormComponent` runs on form submission:
  1. If the form is invalid, `markAllAsTouched()` exposes validation errors.
  2. Extracts values using `this.form.getRawValue()` and removes `confirmPassword` from the payload.
  3. Sets `submitting` to `true` and clears previous errors.

### 4.2 Sending the Request
- `ApiService.submitRegistration(payload)` executes:
  ```ts
  return this.http.post<RegistrationResponse>(`${this.baseUrl}/contact`, payload);
  ```
- `API_BASE_URL` defaults to `/api`, so the request URL becomes `/api/contact`.
- Because `proxy.conf.json` maps `/api` → `http://localhost:4000`, Angular CLI forwards the request to the Express server.

### 4.3 Backend Processing
- Express route (`server.js`):
  ```js
  app.post('/api/contact', (req, res) => {
    const data = req.body ?? {};
    console.log('📩 Registration received:', data);
    res.json({
      message: 'Registration payload received by backend.',
      receivedAt: new Date().toISOString(),
      data,
    });
  });
  ```
- Logs the payload in the terminal.
- Responds with JSON containing `message`, `receivedAt`, and `data` (the submitted fields).

### 4.4 Handling the Response on the Frontend
- The RxJS `subscribe` in `submit()` handles success and error paths:
  ```ts
  this.api.submitRegistration(payload).subscribe({
    next: (response) => {
      this.submitting.set(false);
      this.result.set(response);
      this.form.reset({ role: 'developer', newsletter: false, password: '', confirmPassword: '' });
    },
    error: () => {
      this.submitting.set(false);
      this.error.set('Unable to reach the server. Please try again.');
    },
  });
  ```
- On success:
  - `submitting` → `false`
  - `result` signal stores the echoed data
  - Form resets to defaults
- On failure (e.g., backend not running):
  - `submitting` → `false`
  - `error` signal displays a message under the form

### 4.5 Rendering the Response
- Template shows results when `result()` is truthy:
  ```html
  <section *ngIf="result()" class="result">
    <h3>Backend Response</h3>
    <p>{{ result()?.message }}</p>
    <ul>
      <li><strong>Name:</strong> {{ result()?.data?.name ?? '—' }}</li>
      <li><strong>Email:</strong> {{ result()?.data?.email ?? '—' }}</li>
      <li><strong>Role:</strong> {{ result()?.data?.role ?? '—' }}</li>
      <li><strong>Newsletter:</strong> {{ result()?.data?.newsletter ? 'Yes' : 'No' }}</li>
      <li><strong>Password:</strong> {{ result()?.data?.password ?? '—' }}</li>
      <li><strong>Received At:</strong> {{ result()?.receivedAt | date:'medium' }}</li>
    </ul>
  </section>
  ```
- `error()` signal renders an error paragraph when the backend is unreachable.

---

## 5. End-to-End Summary

1. **Startup**: Backend and Angular dev server run in parallel.
2. **Bootstrap**: Browser loads `index.html`, executes `main.ts`, and renders routing hierarchy down to `RegistrationFormComponent`.
3. **User Input**: Reactive form enforces validations and exposes `submit()`.
4. **Request**: `ApiService` posts JSON to `/api/contact`; Angular CLI proxies to Express.
5. **Backend Response**: Express logs, echoes payload, and returns response JSON.
6. **Frontend Update**: Response stored in a signal → UI shows the echoed field values; errors are surfaced if the request fails.

With both processes running (`npm run server` and `npm start`), clicking **Create Account** will display the submitted data in the app and print it in the backend terminal.
