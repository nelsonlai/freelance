// @ts-nocheck
import { createFeature, createSelector } from '@ngrx/store';
import { projectsReducer, ProjectsState, selectAll, selectTotal } from './projects.reducer';

export const projectsFeature = createFeature({
  name: 'projects',
  reducer: projectsReducer,
});

const selectProjectsState = projectsFeature.selectProjectsState;

export const selectAllProjects = createSelector(selectProjectsState, selectAll);

export const selectProjectsLoading = createSelector(selectProjectsState, (state: ProjectsState) => state.loading);

export const selectProjectsViewModel = createSelector(selectAllProjects, selectTotal, (projects, total) => {
  const activeCount = projects.filter((project) => project.status === 'active').length;
  const totalBudget = projects.reduce((sum, project) => sum + project.budget, 0);
  return {
    projects,
    totalBudget,
    activeCount,
    totalCount: total,
  };
});
