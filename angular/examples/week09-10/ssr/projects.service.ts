// @ts-nocheck
import { Injectable, inject, PLATFORM_ID } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { isPlatformServer } from '@angular/common';
import { Project } from '../state/projects.models';
import { map, Observable } from 'rxjs';

@Injectable({ providedIn: 'root' })
export class ProjectsService {
  private http = inject(HttpClient);
  private platformId = inject(PLATFORM_ID);

  getProjects(tenantId: string): Observable<Project[]> {
    const baseUrl = isPlatformServer(this.platformId) ? process.env['API_URL'] ?? 'http://internal-api' : '/api';
    return this.http.get<Project[]>(`${baseUrl}/tenants/${tenantId}/projects`).pipe(
      map((projects) =>
        projects.map((project) => ({
          ...project,
          budget: project.budget ?? 0,
          lastUpdated: project.lastUpdated ?? new Date().toISOString(),
        })),
      ),
    );
  }

  saveProject(project: Project): Observable<Project> {
    const baseUrl = isPlatformServer(this.platformId) ? process.env['API_URL'] ?? 'http://internal-api' : '/api';
    const url = project.id ? `${baseUrl}/projects/${project.id}` : `${baseUrl}/projects`;
    const method = project.id ? 'patch' : 'post';
    return (this.http as any)[method](url, project);
  }

  deleteProject(id: string): Observable<void> {
    const baseUrl = isPlatformServer(this.platformId) ? process.env['API_URL'] ?? 'http://internal-api' : '/api';
    return this.http.delete<void>(`${baseUrl}/projects/${id}`);
  }
}
