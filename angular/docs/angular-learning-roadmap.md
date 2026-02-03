# Angular Learning Roadmap

## 1. Prerequisites & Environment Setup

### 1.1 Prior Knowledge Checklist
- Proficiency with modern JavaScript/TypeScript (ES6+, async/await, modules, generics)
- Familiarity with npm or yarn workflows and basic CLI usage
- Understanding of HTML5 semantics and modern CSS (Flexbox, Grid)
- Comfort with Git fundamentals (clone, branches, pull requests)

### 1.2 Workstation Setup
- Install Node.js LTS (v20.x) from https://nodejs.org; verify with `node --version` and `npm --version`.
- Install a package manager:
  - Prefer `npm` (bundled with Node) or `pnpm` (`npm install -g pnpm`) for faster installs.
- Choose an IDE with Angular support:
  - VS Code with extensions: Angular Language Service, ESLint, Prettier, Nx Console (optional).
- Configure Git credentials and SSH keys if contributing to remote repos.

### 1.3 Angular Tooling
- Install the Angular CLI globally: `npm install -g @angular/cli`.
- Verify installation: `ng version`.
- Create a scratch workspace: `ng new angular-lab --routing --style=scss`.
- Run the dev server to ensure the setup works: `cd angular-lab && ng serve -o`.

### 1.4 Recommended Browser & DevTools
- Use Chrome or Edge for best Angular devtools support.
- Install Angular DevTools extension for component tree inspection and change detection profiling.

### 1.5 Optional Enhancements
- Docker (if you plan to containerize demos).
- nvm or fnm to manage Node versions when working across multiple projects.

### 1.6 TypeScript Refreshers for Angular
- Interfaces vs. classes for models.
- Type narrowing and discriminated unions (useful in component logic).
- Decorators (`@Component`, `@Injectable`) and metadata reflection basics.
- Generics for reusable services (e.g., typed HTTP responses).
- Strict compiler options (`strict`, `noImplicitAny`, `strictTemplates`).

## 2. Core Angular Foundations

### 2.1 Angular Project Anatomy
- **Objectives**: Understand Angular workspace structure (`angular.json`, `src/app`), module vs. standalone setups, and build pipeline (`ng build`).
- **Study**: Angular docs - Getting Started; `ng new` walkthrough; video: Angular Standalone Components (YouTube - Angular team).
- **Practice**: Inspect the generated project files; convert default `AppComponent` to standalone; build and analyze the output bundle.

### 2.2 Components & Templates
- **Objectives**: Author components, manage inputs/outputs, template syntax, lifecycle hooks.
- **Study**: Angular docs - Components & Templates; blog: Netanel Basal "Smart vs. Presentational Components".
- **Practice**: Create a reusable `ButtonComponent` with `@Input()` props and `@Output()` events; use `ng-content` for projection.

### 2.3 Data Binding & Directives
- **Objectives**: Master interpolation, property/event/two-way binding, structural (`*ngIf`, `*ngFor`) and attribute directives.
- **Study**: Angular docs - Template Syntax; Angular In Depth article on structural directives.
- **Practice**: Build a filterable list component leveraging pipes, custom directives to highlight selection, and `[(ngModel)]` in template-driven forms.

### 2.4 Dependency Injection & Services
- **Objectives**: Provide and inject services, tree-shakable providers, injection tokens.
- **Study**: Angular docs - Dependency Injection; video: Deborah Kurata on DI best practices.
- **Practice**: Create a logging service with an injection token controlling log level; inject into multiple components; explore `providedIn` scopes.

### 2.5 Routing & Navigation
- **Objectives**: Configure routes, lazy loading, route guards, resolvers.
- **Study**: Angular Router docs; Angular Labs on standalone routing APIs.
- **Practice**: Add feature routes with lazy-loaded components; implement an auth guard and a resolver fetching data before navigation.

### 2.6 Forms (Template vs Reactive)
- **Objectives**: Contrast template-driven and reactive forms, form validation strategies, custom validators.
- **Study**: Angular docs - Forms overview; RxJS documentation on Subjects for form events.
- **Practice**: Build a signup form twice (template-driven and reactive); implement async validator hitting a mock API; display validation feedback.

### 2.7 HTTP & Observables
- **Objectives**: Use `HttpClient`, interceptors, error handling, working with RxJS observables and operators.
- **Study**: Angular docs - HTTP; RxJS docs for `map`, `switchMap`, `mergeMap`, `catchError`; blog: Angular University on interceptors.
- **Practice**: Integrate a public REST API; add an interceptor for auth headers and error notifications; wrap calls in a service returning typed observables.

### 2.8 State & Change Detection Basics
- **Objectives**: Understand Angular change detection zones, `OnPush` strategy, immutability patterns, harness RxJS for component state.
- **Study**: Articles by Mark Pieszak on Change Detection; Nx docs on component store.
- **Practice**: Refactor a dashboard component to `OnPush`, use `async` pipe for streams, benchmark difference with Angular DevTools profiler.

## 3. Project-Based Progression

### 3.1 Component Library Sandbox
- **Focus**: Reusable UI components, Storybook, inputs/outputs, accessibility.
- **Deliverables**:
  - Build 5+ components (button, card, modal, tabs, toast).
  - Document components with Storybook stories and controls.
  - Add Jest or Karma unit tests for inputs/outputs and template rendering.
- **Best Practices**: Use presentational/container pattern; enforce accessibility checks with `@storybook/addon-a11y`.

### 3.2 Data-Driven Dashboard
- **Focus**: HTTP communication, services, RxJS streams, routing.
- **Deliverables**:
  - Fetch data from a REST API (public or mocked) with caching service.
  - Implement route params, child routes, and guards.
  - Create charts/tables with third-party libraries (e.g., ngx-charts).
  - Write integration tests using Angular Testing Library; mock HTTP with `HttpClientTestingModule`.
- **Best Practices**: Centralize API typings; use `async` pipe; handle errors via interceptor + toast service.

### 3.3 Full CRUD Application
- **Focus**: Forms, state management, authentication, modular architecture.
- **Deliverables**:
  - Implement authentication flow with route guards and refresh tokens (mock backend acceptable).
  - Build reactive forms with dynamic controls and custom validators.
  - Introduce feature modules or standalone route-based organization.
  - Add end-to-end (E2E) tests with Cypress or Playwright covering critical paths.
- **Best Practices**: Adopt `OnPush` change detection; use feature-based folder structure; configure ESLint + Prettier pipelines.

### 3.4 Production Hardening Sprint
- **Focus**: Performance, accessibility, CI/CD.
- **Deliverables**:
  - Optimize bundle size with lazy loading, route-level code splitting, and image optimization.
  - Add Lighthouse audits and fix issues.
  - Configure GitHub Actions (or similar) to run unit, integration, and E2E tests.
- **Best Practices**: Enable strict mode, budgets in `angular.json`, and environment-specific configurations.

## 4. Advanced Topics & Capstone

### 4.1 Reactive Architecture with RxJS
- Learn higher-order mapping (`switchMap`, `exhaustMap`), multicasting (`shareReplay`), and backpressure strategies.
- Explore RxJS marble testing for complex streams.
- Build a real-time feature (e.g., live search) with debouncing and cancellation.

### 4.2 State Management Patterns
- Compare NgRx, NGXS, Akita, and Angular Component Store.
- Implement NgRx feature module: actions, reducers, effects, selectors.
- Add entity adapters, router-store, and testing for effects with marble diagrams.

### 4.3 Server-Side Rendering & Hydration
- Use Angular Universal to render initial HTML on the server.
- Configure pre-rendering, lazy-loading-friendly routes, and API integration on the server.
- Measure performance gains using WebPageTest or Lighthouse.

### 4.4 Micro Frontends & Module Federation
- Study Nx module federation or single-spa integration.
- Build a proof-of-concept splitting features across two Angular remotes with shared libraries.

### 4.5 Performance & Accessibility
- Profile change detection (Angular DevTools), use `trackBy`, manual `ChangeDetectorRef` strategies.
- Apply `ngOptimizedImage`, defer loading, and budget alerts.
- Run aXe or pa11y for accessibility compliance.

### 4.6 Testing Depth
- Add contract tests for APIs using Pact.
- Expand E2E suites with Cypress component testing.
- Integrate visual regression tests (Percy, Chromatic).

### 4.7 Capstone Project: SaaS Admin Portal
- **Scope**: Multi-tenant admin panel with dashboards, CRUD, real-time updates, role-based access.
- **Requirements**:
  - Authentication + authorization with guards and directive-based permissioning.
  - Modular architecture with lazy-loaded domains and shared design system.
  - Offline support (PWA) with service workers and caching strategies.
  - SSR for marketing pages and SEO.
  - Comprehensive testing strategy (unit + integration + E2E + performance budgets).
- **Assessment Criteria**:
  - Code quality: modular structure, strict typing, linting compliance.
  - UX: responsive, accessible, consistent design system.
  - Reliability: passing automated tests, error handling, logging strategy.
  - Performance: meets bundle budgets, SSR/Lighthouse score targets (>90 Performance, >95 Accessibility).
  - Documentation: README with architecture decisions, setup steps, and demo walkthrough.

## 5. Pacing & Evaluation

### 5.1 Suggested 12-Week Schedule
- **Weeks 1-2**: Environment setup, project anatomy, components/templates. Deliverable: component library sandbox skeleton.
- **Weeks 3-4**: Directives, forms, DI/services. Deliverable: completed component library with stories/tests.
- **Weeks 5-6**: Routing, HTTP, observables. Deliverable: data-driven dashboard MVP.
- **Weeks 7-8**: CRUD app build-out, authentication, testing coverage. Deliverable: fully tested CRUD app with E2E suite.
- **Weeks 9-10**: Advanced topics deep dive (RxJS, NgRx, performance). Deliverable: integration of state management + performance audits.
- **Weeks 11-12**: Capstone project implementation and polish. Deliverable: SaaS admin portal demo + documentation.

### 5.2 Checkpoints & Evaluation
- End of each module: create a short demo video or written summary highlighting learnings.
- Weekly retrospective: note blockers, concepts to review, next week's focus.
- Bi-weekly code review: share repo with a peer/mentor for feedback via PRs.
- Testing goals: maintain >80% unit test coverage; ensure E2E suites pass before milestones.

### 5.3 Learning Reinforcement
- Blog about solutions to tricky problems encountered (<500 words weekly).
- Teach-back sessions: explain a concept (e.g., DI, RxJS) to a colleague or via meetup/lightning talk.
- Participate in community: Angular Discord, StackOverflow, GitHub issues to stay current.

### 5.4 Continued Growth
- Follow Angular release notes; schedule quarterly upgrade sprints.
- Contribute to open-source Angular libraries to solidify expertise.
- Explore complementary tech: Nx monorepos, analog.js, Builder.io/Qwik integrations.
