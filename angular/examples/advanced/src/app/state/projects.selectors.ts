// @ts-nocheck
import { createFeatureSelector, createSelector } from '@ngrx/store';
import { ProjectsStateType } from './projects.reducer';

export const selectProjectsState = createFeatureSelector<ProjectsStateType>('projects');

export const selectAll = createSelector(selectProjectsState, (state) => {
  return Object.values(state.entities).filter((project): project is NonNullable<typeof project> => project !== null);
});

export const selectLoading = createSelector(selectProjectsState, (state) => state.loading);

export const selectError = createSelector(selectProjectsState, (state) => state.error);

