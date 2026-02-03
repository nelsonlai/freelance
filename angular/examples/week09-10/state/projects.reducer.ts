// @ts-nocheck
import { createReducer, on } from '@ngrx/store';
import { createEntityAdapter, EntityState } from '@ngrx/entity';
import { ProjectsActions } from './projects.actions';
import { Project } from './projects.models';

export interface ProjectsState extends EntityState<Project> {
  loading: boolean;
  error: unknown;
}

const adapter = createEntityAdapter<Project>({
  sortComparer: (a, b) => a.name.localeCompare(b.name),
});

const initialState: ProjectsState = adapter.getInitialState({
  loading: false,
  error: null,
});

export const projectsReducer = createReducer(
  initialState,
  on(ProjectsActions.enterPage, (state) => ({ ...state, loading: true, error: null })),
  on(ProjectsActions.loadRequested, (state) => ({ ...state, loading: true, error: null })),
  on(ProjectsActions.loadSucceeded, (state, { projects }) =>
    adapter.setAll(projects, { ...state, loading: false }),
  ),
  on(ProjectsActions.loadFailed, (state, { error }) => ({ ...state, loading: false, error })),
  on(ProjectsActions.upsertSucceeded, (state, { project }) => adapter.upsertOne(project, state)),
  on(ProjectsActions.deleteSucceeded, (state, { id }) => adapter.removeOne(id, state)),
);

export const { selectAll, selectTotal, selectEntities } = adapter.getSelectors();
