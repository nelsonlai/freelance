// @ts-nocheck
import { Injectable, inject } from '@angular/core';
import { Actions, createEffect, ofType } from '@ngrx/effects';
import { ProjectsActions } from './projects.actions';
import { ProjectsService } from '../ssr/projects.service';
import { ToastService } from '../../week05-06/toast.service';
import { catchError, exhaustMap, map, mergeMap, of, tap } from 'rxjs';

@Injectable()
export class ProjectsEffects {
  private actions$ = inject(Actions);
  private service = inject(ProjectsService);
  private toast = inject(ToastService);

  enter$ = createEffect(() =>
    this.actions$.pipe(
      ofType(ProjectsActions.enterPage),
      map(() => ProjectsActions.loadRequested({ tenantId: 'default' })),
    ),
  );

  load$ = createEffect(() =>
    this.actions$.pipe(
      ofType(ProjectsActions.loadRequested),
      exhaustMap(({ tenantId }) =>
        this.service.getProjects(tenantId).pipe(
          map((projects) => ProjectsActions.loadSucceeded({ projects })),
          catchError((error) => of(ProjectsActions.loadFailed({ error }))),
        ),
      ),
    ),
  );

  upsert$ = createEffect(() =>
    this.actions$.pipe(
      ofType(ProjectsActions.upsertRequested),
      mergeMap(({ project }) =>
        this.service.saveProject(project).pipe(
          map((saved) => ProjectsActions.upsertSucceeded({ project: saved })),
          tap(() => this.toast.success('Project saved')), 
          catchError((error) => of(ProjectsActions.loadFailed({ error }))),
        ),
      ),
    ),
  );

  delete$ = createEffect(() =>
    this.actions$.pipe(
      ofType(ProjectsActions.deleteRequested),
      mergeMap(({ id }) =>
        this.service.deleteProject(id).pipe(
          map(() => ProjectsActions.deleteSucceeded({ id })),
          tap(() => this.toast.success('Project removed')), 
          catchError((error) => of(ProjectsActions.loadFailed({ error }))),
        ),
      ),
    ),
  );
}
