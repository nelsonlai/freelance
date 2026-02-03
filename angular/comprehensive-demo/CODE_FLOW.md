# Code Flow Documentation

This document provides a detailed explanation of how code flows through the Angular Comprehensive Demo application, from startup to user interactions.

## Table of Contents

1. [Application Bootstrap](#application-bootstrap)
2. [Routing Flow](#routing-flow)
3. [Component Lifecycle](#component-lifecycle)
4. [Dependency Injection Flow](#dependency-injection-flow)
5. [HTTP Request Flow](#http-request-flow)
6. [Authentication Flow](#authentication-flow)
7. [Form Submission Flow](#form-submission-flow)
8. [State Management Flow](#state-management-flow)
9. [Storage Operations Flow](#storage-operations-flow)
10. [Error Handling Flow](#error-handling-flow)
11. [Complete User Journey Example](#complete-user-journey-example)

---

## Application Bootstrap

### 1. Entry Point: `main.ts`

**File:** `src/main.ts`

**Flow:**
```
1. Angular bootstraps the application
2. Calls bootstrapApplication(AppComponent, appConfig)
3. AppComponent is loaded as the root component
4. appConfig provides all necessary services and configurations
```

**Detailed Explanation:**

```typescript
// main.ts
bootstrapApplication(AppComponent, appConfig)
```

1. **`bootstrapApplication()`** - This is Angular's modern bootstrap function (Angular 14+)
   - Takes the root component (`AppComponent`) and configuration (`appConfig`)
   - Initializes the Angular platform
   - Creates the root injector
   - Renders the root component

2. **`appConfig`** - Defined in `app.config.ts`, provides:
   - Zone.js change detection
   - Router configuration with lazy loading
   - HTTP client with interceptors
   - All application-wide providers

3. **Root Component** - `AppComponent` is rendered first
   - Serves as the container for all other components
   - Initializes core services (IndexedDB, Auth state)
   - Sets up navigation structure

### 2. Application Configuration: `app.config.ts`

**File:** `src/app/app.config.ts`

**Flow:**
```
1. Zone.js change detection is configured
2. Router is configured with routes and features
3. HTTP client is configured with interceptors
4. All providers are registered in the dependency injection system
```

**Detailed Explanation:**

```typescript
export const appConfig: ApplicationConfig = {
  providers: [
    provideZoneChangeDetection({ eventCoalescing: true }),
    provideRouter(routes, withComponentInputBinding(), withViewTransitions()),
    provideHttpClient(withInterceptors([authInterceptor, loadingInterceptor, errorInterceptor]))
  ]
}
```

**Interceptor Order:**
1. **authInterceptor** - Adds authentication token to requests
2. **loadingInterceptor** - Tracks request loading state
3. **errorInterceptor** - Handles errors globally

Interceptors execute in this order for requests, and reverse order for responses.

---

## Routing Flow

### Route Configuration: `app.routes.ts`

**File:** `src/app/app.routes.ts`

**Flow:**
```
1. User navigates to a URL
2. Angular Router matches URL to route configuration
3. Guards are checked (if any)
4. Component is lazy-loaded (if configured)
5. Component is rendered in <router-outlet>
```

**Detailed Explanation:**

```typescript
{
  path: 'dashboard',
  loadComponent: () => import('./features/dashboard/dashboard/dashboard.component').then(m => m.DashboardComponent),
  canActivate: [authGuard],
  title: 'Dashboard'
}
```

**Step-by-Step:**

1. **URL Matching:**
   - User navigates to `/dashboard`
   - Router searches routes array for matching path
   - Finds route with `path: 'dashboard'`

2. **Guard Execution:**
   - `canActivate: [authGuard]` is checked
   - `authGuard` function is called
   - Guard checks `authService.isAuthenticated$`
   - If not authenticated, redirects to `/login`
   - If authenticated, allows route activation

3. **Lazy Loading:**
   - `loadComponent()` is called
   - Angular dynamically imports the component module
   - Component code is loaded from a separate chunk
   - Reduces initial bundle size

4. **Component Rendering:**
   - Component is instantiated
   - `ngOnInit()` lifecycle hook is called
   - Component template is rendered in `<router-outlet>`

### Route Guard Flow: `auth.guard.ts`

**File:** `src/app/core/guards/auth.guard.ts`

**Flow:**
```
1. Route guard is triggered
2. Injects AuthService and Router
3. Subscribes to isAuthenticated$ observable
4. Takes first value (take(1))
5. If authenticated: return true (allow route)
6. If not authenticated: redirect to login and return false
```

**Detailed Explanation:**

```typescript
export const authGuard: CanActivateFn = (route, state) => {
  const authService = inject(AuthService);
  const router = inject(Router);

  return authService.isAuthenticated$.pipe(
    take(1),  // Take only the first value and complete
    map((isAuthenticated) => {
      if (isAuthenticated) {
        return true;  // Allow route activation
      } else {
        router.navigate(['/login'], {
          queryParams: { returnUrl: state.url }  // Save attempted URL
        });
        return false;  // Block route activation
      }
    })
  );
};
```

**Why `take(1)`?**
- Prevents memory leaks
- Guards only need to check once
- Observable completes after first emission
- No need to unsubscribe manually

---

## Component Lifecycle

### Component Initialization Flow

**Example:** `DashboardComponent`

**Flow:**
```
1. Component class is instantiated
2. Dependencies are injected (constructor)
3. Component properties are initialized
4. ngOnInit() is called
5. Template is rendered
6. Change detection runs
7. User interactions trigger events
8. ngOnDestroy() is called when component is destroyed
```

**Detailed Explanation:**

```typescript
export class DashboardComponent implements OnInit, OnDestroy {
  // 1. Properties are initialized
  currentUser: User | null = null;
  isAuthenticated = false;

  // 2. Constructor - Dependencies are injected
  constructor(
    private authService = inject(AuthService),
    private appState = inject(AppStateService)
  ) {}

  // 3. ngOnInit() - Called after component initialization
  ngOnInit(): void {
    // Subscribe to observables
    const userSub = this.authService.currentUser$.subscribe(user => {
      this.currentUser = user;
    });
    this.subscriptions.add(userSub);
  }

  // 4. ngOnDestroy() - Called when component is destroyed
  ngOnDestroy(): void {
    // Clean up subscriptions to prevent memory leaks
    this.subscriptions.unsubscribe();
  }
}
```

**Lifecycle Hooks Order:**
1. **Constructor** - Dependencies injected, properties initialized
2. **ngOnInit** - Component initialized, safe to make API calls
3. **ngAfterViewInit** - View initialized, safe to access DOM
4. **ngOnDestroy** - Component being destroyed, cleanup subscriptions

---

## Dependency Injection Flow

### Service Injection

**Example:** `AuthService` injection in `LoginComponent`

**Flow:**
```
1. Component declares dependency (inject() or constructor)
2. Angular's DI system looks for provider
3. Service is found (providedIn: 'root' = singleton)
4. Service instance is injected
5. Component can use service methods
```

**Detailed Explanation:**

```typescript
// LoginComponent
export class LoginComponent {
  // Method 1: Using inject() function (Angular 14+)
  private authService = inject(AuthService);
  
  // Method 2: Using constructor injection (traditional)
  constructor(private authService: AuthService) {}
}
```

**DI Resolution Process:**

1. **Component requests service:**
   ```typescript
   private authService = inject(AuthService);
   ```

2. **Angular checks injector hierarchy:**
   - Component injector (if service provided in component)
   - Module injector (if NgModule)
   - Root injector (for `providedIn: 'root'`)

3. **Service is found:**
   ```typescript
   @Injectable({ providedIn: 'root' })
   export class AuthService { ... }
   ```
   - `providedIn: 'root'` means singleton service
   - Same instance shared across entire application
   - Created on first injection, reused thereafter

4. **Service is injected:**
   - Instance is provided to component
   - Component can call service methods
   - Service state is shared across all components using it

**Singleton Pattern:**
- All components injecting `AuthService` get the same instance
- State changes in one component affect all components
- Perfect for shared state (authentication, app state)

---

## HTTP Request Flow

### Complete Request Journey

**Example:** Loading users list

**Flow:**
```
1. Component calls apiService.get('/users')
2. Request goes through interceptors (auth, loading, error)
3. HTTP request is sent to server
4. Response comes back through interceptors (reverse order)
5. Response is transformed/validated
6. Component receives data
7. Component updates UI
```

**Detailed Explanation:**

#### Step 1: Component Initiates Request

```typescript
// user-list.component.ts
this.apiService.get<User[]>('/users').subscribe({
  next: (users) => {
    this.users = users;  // Update component state
  },
  error: (error) => {
    this.error = error.message;  // Handle error
  }
});
```

#### Step 2: API Service Processes Request

```typescript
// api.service.ts
get<T>(endpoint: string, options?: HttpOptions): Observable<T> {
  const url = `${this.apiUrl}${endpoint}`;  // http://localhost:3000/api/users
  const httpOptions = this.buildHttpOptions(options);
  
  return this.http.get<T>(url, httpOptions).pipe(
    retryWhen(...),  // Retry logic
    catchError(this.handleError<T>('GET', endpoint))
  ) as Observable<T>;
}
```

#### Step 3: Interceptors Process Request (Outbound)

**Interceptor Chain (Request):**
1. **authInterceptor** - Adds token
   ```typescript
   const token = authService.getToken();
   if (token) {
     const clonedRequest = req.clone({
       setHeaders: { Authorization: `Bearer ${token}` }
     });
     return next(clonedRequest);
   }
   ```

2. **loadingInterceptor** - Logs request start
   ```typescript
   console.log(`[HTTP] Starting request: ${req.method} ${req.url}`);
   return next(req);
   ```

3. **errorInterceptor** - Will catch errors on response

#### Step 4: HTTP Request Sent

- Browser sends HTTP request to server
- Request includes headers (Authorization, Content-Type)
- Server processes request

#### Step 5: Response Received

- Server sends HTTP response
- Response includes status code, headers, body

#### Step 6: Interceptors Process Response (Inbound)

**Interceptor Chain (Response - Reverse Order):**
1. **errorInterceptor** - Catches errors
   ```typescript
   catchError((error: HttpErrorResponse) => {
     // Handle different error status codes
     // Transform error message
     return throwError(() => ({ message, status, originalError }));
   })
   ```

2. **loadingInterceptor** - Logs completion
   ```typescript
   finalize(() => {
     console.log(`[HTTP] Request finalized`);
   })
   ```

3. **authInterceptor** - Passes through (no response modification)

#### Step 7: Component Receives Data

```typescript
.subscribe({
  next: (users) => {
    // Data received successfully
    this.users = users;
    this.loading = false;
  },
  error: (error) => {
    // Error occurred
    this.error = error.message;
    this.loading = false;
  }
});
```

#### Step 8: UI Updates

- Angular change detection detects state change
- Template re-renders with new data
- `*ngFor` displays users in the list

---

## Authentication Flow

### Complete Authentication Journey

**Flow:**
```
1. User enters credentials in login form
2. Form is validated
3. Login request is sent to API
4. Server validates credentials
5. Server returns JWT token
6. Token is stored in multiple storage locations
7. Auth state is updated
8. User is redirected to dashboard
9. Subsequent requests include token automatically
```

**Detailed Explanation:**

#### Step 1: User Submits Login Form

```typescript
// login.component.ts
onSubmit(form: NgForm): void {
  if (form.invalid) return;
  
  this.authService.login({
    email: this.loginForm.email,
    password: this.loginForm.password
  }).subscribe({ ... });
}
```

#### Step 2: Auth Service Processes Login

```typescript
// auth.service.ts
login(credentials: LoginCredentials): Observable<User> {
  return this.apiService.post<AuthResponse>('/auth/login', credentials).pipe(
    tap((response: AuthResponse) => {
      // Store authentication data
      this.setToken(response.token);
      this.setRefreshToken(response.refreshToken);
      this.setUser(response.user);
      
      // Update state
      this.currentUserSubject.next(response.user);
      this.isAuthenticatedSubject.next(true);
    }),
    map((response) => response.user)
  );
}
```

#### Step 3: Token Storage

```typescript
private setToken(token: string): void {
  // Store in localStorage (persists across sessions)
  this.localStorage.set(environment.auth.tokenKey, token);
  
  // Store in sessionStorage (cleared on tab close)
  this.sessionStorage.set(environment.auth.tokenKey, token);
  
  // Store in cookie (sent with requests)
  this.cookieService.set(environment.auth.tokenKey, token, {
    expires: 7,
    secure: environment.production,
    sameSite: 'lax'
  });
}
```

**Why Multiple Storage Locations?**
- **LocalStorage**: Persists across browser restarts
- **SessionStorage**: Cleared when tab closes (security)
- **Cookies**: Can be HttpOnly (server-side), sent automatically

#### Step 4: State Updates

```typescript
// BehaviorSubject emits new value
this.currentUserSubject.next(response.user);
this.isAuthenticatedSubject.next(true);

// All subscribers are notified
// Components update automatically
```

#### Step 5: Automatic Token Injection

```typescript
// auth.interceptor.ts
export const authInterceptor: HttpInterceptorFn = (req, next) => {
  const token = authService.getToken();
  
  if (token) {
    const clonedRequest = req.clone({
      setHeaders: { Authorization: `Bearer ${token}` }
    });
    return next(clonedRequest);
  }
  
  return next(req);
};
```

**Every HTTP request automatically includes the token!**

---

## Form Submission Flow

### Template-Driven Form Flow

**Example:** Login Form

**Flow:**
```
1. User types in input fields
2. [(ngModel)] updates component properties
3. Angular validates input
4. User submits form
5. onSubmit() is called
6. Form validation is checked
7. Service method is called
8. API request is sent
9. Response is handled
10. UI is updated
```

**Detailed Explanation:**

#### Step 1: Two-Way Data Binding

```html
<!-- login.component.html -->
<input
  type="email"
  [(ngModel)]="loginForm.email"
  name="email"
  required
  email
/>
```

**How `[(ngModel)]` Works:**
- `[ngModel]` - Property binding (component → template)
- `(ngModelChange)` - Event binding (template → component)
- `[(ngModel)]` - Shorthand for both (two-way binding)

**Flow:**
1. User types "john@example.com"
2. `(ngModelChange)` event fires
3. `loginForm.email` is updated in component
4. `[ngModel]` updates input value
5. Angular validates (required, email format)

#### Step 2: Form Validation

```typescript
// Angular automatically creates FormControl for each input
// Validation rules are checked:
- required: Field must have value
- email: Value must be valid email format
- minlength: Minimum character length
```

**Validation State:**
- `form.valid` - All fields valid
- `form.invalid` - At least one field invalid
- `form.touched` - User has interacted with form
- `form.dirty` - User has modified form

#### Step 3: Form Submission

```typescript
onSubmit(form: NgForm): void {
  // Check if form is valid
  if (form.invalid) {
    // Mark all fields as touched to show errors
    Object.keys(form.controls).forEach(key => {
      form.controls[key].markAsTouched();
    });
    return;  // Stop submission
  }
  
  // Form is valid, proceed with login
  this.authService.login({ ... }).subscribe({ ... });
}
```

### Reactive Form Flow

**Example:** Register Form

**Flow:**
```
1. FormGroup is created in component
2. FormControls are defined with validators
3. Template binds to FormGroup
4. User interacts with form
5. Validation runs automatically
6. Form submission checks validity
7. API call is made
8. Response is handled
```

**Detailed Explanation:**

#### Step 1: Form Creation

```typescript
// register.component.ts
this.registerForm = this.fb.group({
  firstName: ['', [Validators.required, Validators.minLength(2)]],
  lastName: ['', [Validators.required, Validators.minLength(2)]],
  email: ['', [Validators.required, Validators.email]],
  password: ['', [Validators.required, Validators.minLength(6)]],
  confirmPassword: ['', [Validators.required]]
}, {
  validators: this.passwordMatchValidator  // Form-level validator
});
```

**FormBuilder Benefits:**
- Type-safe form creation
- Cleaner syntax
- Easier to manage complex forms

#### Step 2: Template Binding

```html
<form [formGroup]="registerForm" (ngSubmit)="onSubmit()">
  <input formControlName="firstName" />
  <div *ngIf="hasError('firstName', 'required')">
    First name is required
  </div>
</form>
```

**Key Differences from Template-Driven:**
- `[formGroup]` - Binds to FormGroup
- `formControlName` - Binds to FormControl (not ngModel)
- Validation is programmatic, not template-based

#### Step 3: Real-Time Validation

```typescript
// Validation runs on every change
get firstName() {
  return this.registerForm.get('firstName');
}

// In template:
<div *ngIf="firstName?.invalid && firstName?.touched">
  Error message
</div>
```

**Validation Timing:**
- Runs on every value change
- Updates validation state immediately
- Shows errors when field is touched

---

## State Management Flow

### AppStateService Flow

**File:** `src/app/state/app.state.ts`

**Flow:**
```
1. Component calls appState.updateState()
2. New state object is created (immutability)
3. BehaviorSubject emits new state
4. All subscribers are notified
5. Components update automatically
```

**Detailed Explanation:**

#### Step 1: State Update

```typescript
// Component calls:
this.appState.setUser(user);

// AppStateService:
setUser(user: any | null): void {
  this.updateState({ user });
}

updateState(updates: Partial<AppState>): void {
  const currentState = this.stateSubject.value;
  const newState = { ...currentState, ...updates };  // Immutable update
  this.stateSubject.next(newState);  // Emit new state
}
```

**Immutability:**
- `{ ...currentState, ...updates }` creates a new object
- Original state is not mutated
- Angular change detection works correctly
- Enables time-travel debugging

#### Step 2: State Emission

```typescript
// BehaviorSubject holds current state
private stateSubject = new BehaviorSubject<AppState>(initialState);

// Public observable for components
public state$: Observable<AppState> = this.stateSubject.asObservable();
```

**BehaviorSubject vs Subject:**
- **BehaviorSubject**: Holds current value, emits to new subscribers immediately
- **Subject**: No initial value, only emits to current subscribers

#### Step 3: Component Subscription

```typescript
// Component subscribes to state
this.appState.select(state => state.user).subscribe(user => {
  this.currentUser = user;  // Update component property
});
```

**Select Pattern:**
- Only subscribes to specific state slice
- Better performance (less change detection)
- Automatic unsubscription when component destroys

#### Step 4: Change Detection

- State change triggers Angular change detection
- Components using state update automatically
- Template re-renders with new data

---

## Storage Operations Flow

### LocalStorage Flow

**Example:** Storing user preferences

**Flow:**
```
1. Component calls localStorageService.set('theme', 'dark')
2. Service checks if localStorage is available
3. Key is prefixed (app_theme)
4. Value is JSON stringified
5. Data is stored in browser localStorage
6. Component can retrieve with get()
```

**Detailed Explanation:**

```typescript
// Component
this.localStorage.set('theme', 'dark');

// Service
set<T>(key: string, value: T): boolean {
  const prefixedKey = `${this.prefix}${key}`;  // "app_theme"
  const serialized = JSON.stringify(value);    // "dark" → '"dark"'
  localStorage.setItem(prefixedKey, serialized);
  return true;
}
```

**Why JSON.stringify?**
- localStorage only stores strings
- Objects/arrays need serialization
- JSON.stringify converts to string
- JSON.parse converts back to object

### IndexedDB Flow

**Example:** Storing large datasets

**Flow:**
```
1. Component calls indexedDB.init()
2. Database is opened/created
3. Object stores are created if needed
4. Component calls indexedDB.add('cache', data)
5. Transaction is started
6. Data is stored in object store
7. Observable emits success
8. Component receives confirmation
```

**Detailed Explanation:**

```typescript
// Component
this.indexedDB.init().subscribe({
  next: () => {
    // Database ready
    this.indexedDB.add('cache', data).subscribe({
      next: () => console.log('Saved')
    });
  }
});

// Service
add<T>(storeName: string, data: T): Observable<T> {
  const transaction = this.db.transaction([storeName], 'readwrite');
  const store = transaction.objectStore(storeName);
  const request = store.put(data);  // put() = add or update
  
  return new Observable(observer => {
    request.onsuccess = () => {
      observer.next(data);
      observer.complete();
    };
    request.onerror = () => observer.error(request.error);
  });
}
```

**IndexedDB Advantages:**
- Large storage capacity
- Structured data (not just strings)
- Indexes for fast queries
- Transaction support

---

## Error Handling Flow

### Global Error Handling

**Flow:**
```
1. HTTP request fails
2. Error is caught by errorInterceptor
3. Error is analyzed (status code, type)
4. Error message is transformed
5. Error is logged (if enabled)
6. Error observable is returned
7. Component's error handler receives error
8. Component displays error or uses fallback
```

**Detailed Explanation:**

#### Step 1: Error Occurs

```typescript
// HTTP request fails
this.http.get('/users').subscribe({
  error: (error) => { ... }  // Error handler
});
```

#### Step 2: Error Interceptor Catches

```typescript
// error.interceptor.ts
return next(req).pipe(
  catchError((error: HttpErrorResponse) => {
    // Analyze error
    const status = error.status;
    
    switch (status) {
      case 0:
        // Connection error - backend not available
        errorMessage = '';
        break;
      case 401:
        // Unauthorized - redirect to login
        authService.logout();
        router.navigate(['/login']);
        break;
      // ... other status codes
    }
    
    return throwError(() => ({ message, status, originalError }));
  })
);
```

#### Step 3: Component Handles Error

```typescript
// user-list.component.ts
this.apiService.get<User[]>('/users').subscribe({
  error: (error) => {
    // Check if it's a demo mode error (empty message)
    if (error.message && error.message.trim() !== '') {
      this.error = error.message;  // Show error
    } else {
      this.error = null;  // Silent error, use mock data
    }
    
    // Fallback to mock data
    this.users = this.getMockUsers();
  }
});
```

**Error Handling Strategy:**
- **Status 0 (Connection Error)**: Silent, use mock data
- **Status 401 (Unauthorized)**: Logout, redirect to login
- **Status 403 (Forbidden)**: Show access denied message
- **Status 404 (Not Found)**: Show not found message
- **Status 500 (Server Error)**: Show generic error

---

## Complete User Journey Example

### Scenario: User Logs In and Views Dashboard

**Complete Flow:**

#### 1. Application Starts

```
main.ts → bootstrapApplication()
  ↓
app.config.ts → Providers registered
  ↓
app.component.ts → Root component initialized
  ↓
IndexedDB initialized
  ↓
Auth state restored from storage
  ↓
Router activated
```

#### 2. User Navigates to Login

```
User clicks "Login" link
  ↓
Router navigates to /login
  ↓
authGuard checks authentication
  ↓
User not authenticated, route allowed
  ↓
LoginComponent is lazy-loaded
  ↓
LoginComponent.ngOnInit() called
  ↓
Template rendered with form
```

#### 3. User Fills Login Form

```
User types email: "john@example.com"
  ↓
(ngModelChange) event fires
  ↓
loginForm.email = "john@example.com"
  ↓
Angular validates (required, email format)
  ↓
Form validation state updates
  ↓
Submit button enabled/disabled based on validity
```

#### 4. User Submits Form

```
User clicks "Login" button
  ↓
(ngSubmit) event fires
  ↓
onSubmit(formRef) called
  ↓
Form validation checked
  ↓
authService.login() called
  ↓
API request prepared
```

#### 5. HTTP Request Journey

```
apiService.post('/auth/login', credentials)
  ↓
authInterceptor adds token (none yet, skipped)
  ↓
loadingInterceptor logs request start
  ↓
errorInterceptor waits for response
  ↓
HTTP request sent to http://localhost:3000/api/auth/login
  ↓
Backend server receives request
  ↓
Server validates credentials
  ↓
Server generates JWT token
  ↓
Server sends response: { token, refreshToken, user }
  ↓
Response received by Angular
  ↓
errorInterceptor checks for errors (none)
  ↓
loadingInterceptor logs completion
  ↓
authInterceptor passes through
  ↓
Response data extracted
```

#### 6. Authentication Complete

```
AuthService receives response
  ↓
setToken() stores token in localStorage, sessionStorage, cookie
  ↓
setUser() stores user in localStorage, sessionStorage
  ↓
currentUserSubject.next(user) - emits new user
  ↓
isAuthenticatedSubject.next(true) - emits authenticated state
  ↓
All subscribers notified (AppComponent, etc.)
  ↓
AppComponent updates navigation (shows user name)
  ↓
LoginComponent receives success
  ↓
Router navigates to /dashboard
```

#### 7. Dashboard Loads

```
Router navigates to /dashboard
  ↓
authGuard checks authentication
  ↓
User is authenticated, route allowed
  ↓
DashboardComponent lazy-loaded
  ↓
DashboardComponent.ngOnInit() called
  ↓
Component subscribes to currentUser$
  ↓
User data already available (from BehaviorSubject)
  ↓
Component receives user immediately
  ↓
Template renders with user data
```

#### 8. User Views Users List

```
User clicks "Users" link
  ↓
Router navigates to /users
  ↓
UserListComponent loaded
  ↓
loadUsers() called
  ↓
apiService.get('/users') called
  ↓
authInterceptor adds token to request
  ↓
Request sent: Authorization: Bearer <token>
  ↓
Backend validates token
  ↓
Backend returns users list
  ↓
Component receives users
  ↓
*ngFor renders user list
```

#### 9. User Logs Out

```
User clicks "Logout" button
  ↓
logout() method called
  ↓
authService.logout() called
  ↓
All storage cleared (localStorage, sessionStorage, cookies)
  ↓
currentUserSubject.next(null)
  ↓
isAuthenticatedSubject.next(false)
  ↓
All subscribers notified
  ↓
Navigation updates (hides protected routes)
  ↓
Router redirects to /login
```

---

## Data Flow Patterns

### Unidirectional Data Flow

**Angular follows unidirectional data flow:**

```
Component State → Template → User Interaction → Event → Component Method → Service → API → Response → Component State
```

**Benefits:**
- Predictable data flow
- Easier debugging
- Better performance
- Clear separation of concerns

### Observable Data Flow

**RxJS Observables enable reactive programming:**

```
Service emits data → Observable stream → Component subscribes → Component updates → Template re-renders
```

**Example:**
```typescript
// Service emits
this.currentUserSubject.next(user);

// Component receives
this.authService.currentUser$.subscribe(user => {
  this.currentUser = user;  // Component updates
});

// Template updates automatically
{{ currentUser.firstName }}
```

### Change Detection Flow

**Angular's change detection:**

```
1. Event occurs (click, HTTP response, timer, etc.)
2. Zone.js detects async operation
3. Angular change detection runs
4. All components checked for changes
5. Changed components re-render
6. DOM updated
```

**Optimization:**
- OnPush change detection strategy
- TrackBy functions for *ngFor
- Unsubscribe from observables
- Use async pipe (auto-unsubscribes)

---

## Key Architectural Patterns

### 1. Service Layer Pattern

**All business logic in services:**
```
Component → Service → API → Backend
         ← Service ← API ← Backend
```

**Benefits:**
- Reusable logic
- Testable
- Single source of truth
- Separation of concerns

### 2. Interceptor Pattern

**Cross-cutting concerns handled by interceptors:**
```
Request → Auth Interceptor → Loading Interceptor → Error Interceptor → Server
Response ← Auth Interceptor ← Loading Interceptor ← Error Interceptor ← Server
```

**Benefits:**
- Centralized request/response handling
- No code duplication
- Easy to add/remove features

### 3. Guard Pattern

**Route protection with guards:**
```
Route Activation → Guard Check → Allow/Deny → Component Load
```

**Benefits:**
- Centralized authorization
- Reusable guards
- Clear route protection

### 4. State Management Pattern

**Centralized state with BehaviorSubject:**
```
Component Action → State Service → State Update → All Subscribers Notified
```

**Benefits:**
- Single source of truth
- Predictable state updates
- Easy to debug

---

## Performance Considerations

### Lazy Loading

**Routes are lazy-loaded:**
```typescript
{
  path: 'users',
  loadChildren: () => import('./features/users/users.routes').then(m => m.USER_ROUTES)
}
```

**Benefits:**
- Smaller initial bundle
- Faster initial load
- Code split by feature
- Load on demand

### Change Detection Optimization

**Strategies to optimize:**
1. **OnPush Change Detection:**
   ```typescript
   @Component({
     changeDetection: ChangeDetectionStrategy.OnPush
   })
   ```

2. **TrackBy Functions:**
   ```typescript
   *ngFor="let user of users; trackBy: trackByUserId"
   ```

3. **Async Pipe:**
   ```typescript
   {{ currentUser$ | async }}
   ```

### Memory Management

**Prevent memory leaks:**
1. **Unsubscribe from observables:**
   ```typescript
   ngOnDestroy() {
     this.subscriptions.unsubscribe();
   }
   ```

2. **Use async pipe (auto-unsubscribes):**
   ```html
   <div *ngIf="currentUser$ | async as user">
     {{ user.name }}
   </div>
   ```

3. **Use take(1) for one-time subscriptions:**
   ```typescript
   this.authService.isAuthenticated$.pipe(take(1)).subscribe(...)
   ```

---

## Summary

This Angular application follows a well-structured flow:

1. **Bootstrap** → Application starts, services initialized
2. **Routing** → URL matched, guards checked, component loaded
3. **Component Lifecycle** → Component initialized, data loaded
4. **User Interaction** → Events trigger component methods
5. **Service Calls** → Business logic in services
6. **HTTP Requests** → Interceptors process, API called
7. **State Updates** → State service updates, subscribers notified
8. **UI Updates** → Change detection, template re-renders

The architecture ensures:
- ✅ Separation of concerns
- ✅ Reusability
- ✅ Testability
- ✅ Maintainability
- ✅ Performance
- ✅ Type safety

Each layer has a specific responsibility, making the codebase clean, organized, and easy to understand.

