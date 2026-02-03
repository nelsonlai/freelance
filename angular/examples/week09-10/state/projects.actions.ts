// @ts-nocheck
import { createActionGroup, emptyProps, props } from '@ngrx/store';
import { Project } from './projects.models';

export const ProjectsActions = createActionGroup({
  source: 'Projects',
  events: {
    'Enter Page': emptyProps(),
    'Load Requested': props<{ tenantId: string }>(),
    'Load Succeeded': props<{ projects: Project[] }>(),
    'Load Failed': props<{ error: unknown }>(),
    'Upsert Requested': props<{ project: Project }>(),
    'Upsert Succeeded': props<{ project: Project }>(),
    'Delete Requested': props<{ id: string }>(),
    'Delete Succeeded': props<{ id: string }>(),
  },
});
