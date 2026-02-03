// @ts-nocheck
import { selectProjectsViewModel } from './projects.selectors';
import { ProjectsState } from './projects.reducer';

const baseState: ProjectsState = {
  ids: ['1'],
  entities: {
    '1': { id: '1', name: 'Project One', status: 'active', budget: 5000, lastUpdated: '2024-01-01' },
  },
  loading: false,
  error: null,
};

describe('Projects Selectors', () => {
  it('projects view model computes aggregates', () => {
    const result = selectProjectsViewModel.projector([baseState.entities['1']], 1);
    expect(result.activeCount).toBe(1);
    expect(result.totalBudget).toBe(5000);
    expect(result.totalCount).toBe(1);
  });
});
