// @ts-nocheck
import { ChangeDetectionStrategy, Component, inject } from '@angular/core';
import { AsyncPipe, NgFor, NgIf, CurrencyPipe } from '@angular/common';
import { Store } from '@ngrx/store';
import { ProjectsActions } from './state/projects.actions';
import { selectProjectsViewModel, selectProjectsLoading } from './state/projects.selectors';

@Component({
  selector: 'app-projects-dashboard',
  standalone: true,
  imports: [AsyncPipe, NgFor, NgIf, CurrencyPipe],
  changeDetection: ChangeDetectionStrategy.OnPush,
  template: `
    <section>
      <header class="header">
        <div>
          <h1>Portfolio Overview</h1>
          <p *ngIf="(loading$ | async)">Loading projects…</p>
        </div>
        <button type="button" (click)="refresh()">Refresh</button>
      </header>

      <section *ngIf="viewModel$ | async as vm">
        <p class="summary">
          {{ vm.activeCount }} active projects · Total budget {{ vm.totalBudget | currency:'USD' }} · {{ vm.totalCount }} total
        </p>
        <ul class="list">
          <li *ngFor="let project of vm.projects; trackBy: trackById">
            <h3>{{ project.name }}</h3>
            <p>Status: {{ project.status }}</p>
            <p>Budget: {{ project.budget | currency:'USD' }}</p>
          </li>
        </ul>
      </section>
    </section>
  `,
  styles: [
    `
      .header {
        display: flex;
        justify-content: space-between;
        align-items: center;
      }
      .summary {
        color: #4b5563;
      }
      .list {
        display: grid;
        gap: 1rem;
        grid-template-columns: repeat(auto-fit, minmax(18rem, 1fr));
        padding: 0;
        list-style: none;
      }
      li {
        border: 1px solid #e5e7eb;
        border-radius: 0.75rem;
        padding: 1rem;
      }
    `,
  ],
})
export class ProjectsDashboardComponent {
  private store = inject(Store);

  viewModel$ = this.store.select(selectProjectsViewModel);
  loading$ = this.store.select(selectProjectsLoading);

  constructor() {
    this.store.dispatch(ProjectsActions.enterPage());
  }

  refresh(): void {
    this.store.dispatch(ProjectsActions.loadRequested({ tenantId: 'default' }));
  }

  trackById = (_: number, project: { id: string }) => project.id;
}
