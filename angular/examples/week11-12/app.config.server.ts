// @ts-nocheck
import { ApplicationConfig } from '@angular/core';
import { provideServerRendering } from '@angular/platform-server';
import { provideClientHydration } from '@angular/platform-browser';
import { provideHttpClient, withFetch } from '@angular/common/http';
import { provideRouter } from '@angular/router';
import { appRoutes } from '../../src/app/app.routes';

export const appConfigServer: ApplicationConfig = {
  providers: [
    provideServerRendering(),
    provideClientHydration(),
    provideHttpClient(withFetch()),
    provideRouter(appRoutes),
  ],
};
