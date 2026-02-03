// @ts-nocheck
import { Injectable, inject } from '@angular/core';
import { Actions, createEffect, ofType } from '@ngrx/effects';
import { ProjectsActions } from './projects.actions';
import { ProjectsService } from '../services/projects.service';
import { catchError, exhaustMap, map, of } from 'rxjs';

@Injectable()
export class ProjectsEffects {
  private actions$ = inject(Actions);
  private service = inject(ProjectsService);

  loadProjects$ = createEffect(() =>
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
}
