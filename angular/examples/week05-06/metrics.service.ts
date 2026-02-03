// @ts-nocheck
import { Injectable, inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, Subject, shareReplay, switchMap, tap } from 'rxjs';

export interface MetricSummary {
  id: string;
  label: string;
  value: number;
  delta?: number;
}

@Injectable({ providedIn: 'root' })
export class MetricsService {
  private http = inject(HttpClient);
  private refresh$ = new Subject<void>();
  private cache = new Map<string, Observable<unknown>>();

  readonly summaries$ = this.refreshableRequest<MetricSummary[]>(() =>
    this.http.get<MetricSummary[]>('/api/metrics/summary'),
  );

  refresh(): void {
    this.refresh$.next();
  }

  fetchProjects(): Observable<{ name: string; status: string }[]> {
    return this.http.get<{ name: string; status: string }[]>('/api/projects');
  }

  cacheResponse<T>(key: string) {
    return (source$: Observable<T>) => {
      const cached = this.cache.get(key) as Observable<T> | undefined;
      if (cached) {
        return cached;
      }
      const shared = source$.pipe(shareReplay({ bufferSize: 1, refCount: true }));
      this.cache.set(key, shared);
      return shared;
    };
  }

  private refreshableRequest<T>(factory: () => Observable<T>): Observable<T> {
    return this.refresh$.pipe(switchMap(() => factory()), shareReplay({ bufferSize: 1, refCount: true }));
  }

  ngOnInit(): void {
    this.refresh();
  }
}
