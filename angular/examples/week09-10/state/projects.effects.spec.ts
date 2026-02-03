// @ts-nocheck
import { provideMockActions } from '@ngrx/effects/testing';
import { TestBed } from '@angular/core/testing';
import { Observable, of, throwError } from 'rxjs';
import { ProjectsEffects } from './projects.effects';
import { ProjectsActions } from './projects.actions';
import { provideMockStore } from '@ngrx/store/testing';
import { ProjectsService } from '../ssr/projects.service';
import { ToastService } from '../../week05-06/toast.service';
import { hot, cold } from 'jest-marbles';

describe('ProjectsEffects', () => {
  let actions$: Observable<unknown>;
  let effects: ProjectsEffects;
  let service: jasmine.SpyObj<ProjectsService>;
  let toast: jasmine.SpyObj<ToastService>;

  beforeEach(() => {
    service = jasmine.createSpyObj('ProjectsService', ['getProjects']);
    toast = jasmine.createSpyObj('ToastService', ['success']);

    TestBed.configureTestingModule({
      providers: [
        ProjectsEffects,
        provideMockActions(() => actions$),
        provideMockStore(),
        { provide: ProjectsService, useValue: service },
        { provide: ToastService, useValue: toast },
      ],
    });

    effects = TestBed.inject(ProjectsEffects);
  });

  it('loads projects on loadRequested success', () => {
    const projects = [{ id: '1', name: 'A', status: 'active', budget: 1000, lastUpdated: '2024-01-01' }];

    actions$ = hot('-a', { a: ProjectsActions.loadRequested({ tenantId: 'default' }) });
    service.getProjects.and.returnValue(cold('-b|', { b: projects }));

    const expected = cold('--c', { c: ProjectsActions.loadSucceeded({ projects }) });

    expect(effects.load$).toBeObservable(expected);
  });

  it('dispatches loadFailed on error', () => {
    const error = new Error('Network');
    actions$ = hot('-a', { a: ProjectsActions.loadRequested({ tenantId: 'default' }) });
    service.getProjects.and.returnValue(cold('-#|', {}, error));

    const expected = cold('--c', { c: ProjectsActions.loadFailed({ error }) });

    expect(effects.load$).toBeObservable(expected);
  });
});
