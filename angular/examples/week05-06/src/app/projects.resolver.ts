// @ts-nocheck
import { inject } from '@angular/core';
import { ResolveFn } from '@angular/router';
import { MetricsService } from './metrics.service';

export const ProjectsResolver: ResolveFn<unknown> = () => {
  const metrics = inject(MetricsService);
  return metrics.fetchProjects().pipe(
    metrics.cacheResponse('projects'),
  );
};
