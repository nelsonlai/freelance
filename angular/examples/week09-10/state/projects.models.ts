// @ts-nocheck
export interface Project {
  id: string;
  name: string;
  status: 'active' | 'paused' | 'completed';
  budget: number;
  lastUpdated: string;
}

export interface ProjectsViewModel {
  projects: Project[];
  totalBudget: number;
  activeCount: number;
}
