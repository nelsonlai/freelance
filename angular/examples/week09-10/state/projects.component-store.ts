// @ts-nocheck
import { Injectable } from '@angular/core';
import { ComponentStore } from '@ngrx/component-store';
import { ProjectsService } from '../ssr/projects.service';
import { Project } from './projects.models';
import { switchMap, tapResponse } from '@ngrx/operators';

interface ProjectsLocalState {
  projects: Project[];
  loading: boolean;
}

@Injectable()
export class ProjectsComponentStore extends ComponentStore<ProjectsLocalState> {
  constructor(private service: ProjectsService) {
    super({ projects: [], loading: false });
  }

  readonly projects$ = this.select((state) => state.projects);
  readonly loading$ = this.select((state) => state.loading);

  readonly load = this.effect<string>((tenantId$) =>
    tenantId$.pipe(
      tap(() => this.patchState({ loading: true })),
      switchMap((tenantId) =>
        this.service.getProjects(tenantId).pipe(
          tapResponse(
            (projects) => this.patchState({ projects, loading: false }),
            () => this.patchState({ loading: false }),
          ),
        ),
      ),
    ),
  );
}
