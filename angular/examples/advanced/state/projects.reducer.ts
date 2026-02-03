// @ts-nocheck
import { createReducer, on } from '@ngrx/store';
import { createEntityAdapter } from '@ngrx/entity';
import { ProjectsActions } from './projects.actions';
import { Project } from './projects.models';

export interface ProjectsState {
  loading: boolean;
  error: unknown;
  ids: string[];
  entities: Record<string, Project>;
}

const adapter = createEntityAdapter<Project>();

const initialState = adapter.getInitialState<ProjectsState>({
  loading: false,
  error: null,
});

export const projectsReducer = createReducer(
  initialState,
  on(ProjectsActions.loadRequested, (state) => ({ ...state, loading: true, error: null })),
  on(ProjectsActions.loadSucceeded, (state, { projects }) =>
    adapter.setAll(projects, { ...state, loading: false }),
  ),
  on(ProjectsActions.loadFailed, (state, { error }) => ({ ...state, loading: false, error })),
  on(ProjectsActions.createSucceeded, (state, { project }) => adapter.addOne(project, state)),
);
