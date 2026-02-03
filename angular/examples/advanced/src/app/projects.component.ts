// @ts-nocheck
import { Component, inject, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Store } from '@ngrx/store';
import { ProjectsActions } from './state/projects.actions';
import { selectAll, selectLoading, selectError } from './state/projects.selectors';
import { Project } from './state/projects.models';

@Component({
  selector: 'app-projects',
  standalone: true,
  imports: [CommonModule],
  template: `
    <div class="projects">
      <h1>Projects</h1>
      <button (click)="loadProjects()" [disabled]="loading$ | async">Load Projects</button>
      
      @if (loading$ | async) {
        <p>Loading...</p>
      }
      
      @if (error$ | async) {
        <p class="error">Error: {{ error$ | async }}</p>
      }
      
      <ul>
        @for (project of projects$ | async; track project.id) {
          <li>
            <strong>{{ project.name }}</strong> - {{ project.status }}
            @if (project.budget) {
              <span>($ {{ project.budget }})</span>
            }
          </li>
        }
      </ul>
    </div>
  `,
  styles: [
    `
      .projects {
        padding: 2rem;
      }
      ul {
        list-style: none;
        padding: 0;
      }
      li {
        padding: 0.5rem;
        border-bottom: 1px solid #e5e7eb;
      }
      .error {
        color: #dc2626;
      }
      button {
        padding: 0.75rem 1.5rem;
        background: #2563eb;
        color: white;
        border: none;
        border-radius: 0.5rem;
        cursor: pointer;
        margin-bottom: 1rem;
      }
      button:disabled {
        opacity: 0.5;
        cursor: not-allowed;
      }
    `,
  ],
})
export class ProjectsComponent implements OnInit {
  private store = inject(Store);

  projects$ = this.store.select(selectAll);
  loading$ = this.store.select(selectLoading);
  error$ = this.store.select(selectError);

  ngOnInit(): void {
    // Load projects for tenant 'tenant1' on init
    this.loadProjects();
  }

  loadProjects(): void {
    this.store.dispatch(ProjectsActions.loadRequested({ tenantId: 'tenant1' }));
  }
}

