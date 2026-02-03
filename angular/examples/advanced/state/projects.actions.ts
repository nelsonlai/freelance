// @ts-nocheck
import { createActionGroup, props } from '@ngrx/store';
import { Project } from './projects.models';

export const ProjectsActions = createActionGroup({
  source: 'Projects',
  events: {
    'Load Requested': props<{ tenantId: string }>(),
    'Load Succeeded': props<{ projects: Project[] }>(),
    'Load Failed': props<{ error: unknown }>(),
    'Create Requested': props<{ project: Project }>(),
    'Create Succeeded': props<{ project: Project }>(),
  },
});
