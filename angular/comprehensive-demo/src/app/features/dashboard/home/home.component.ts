/**
 * Home Component
 * 
 * Landing page component that demonstrates:
 * - Component basics
 * - Data binding
 * - Template expressions
 */

import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-home',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent {
  title = 'Welcome to Angular Comprehensive Demo';
  description = 'This application demonstrates core Angular concepts and best practices.';
  
  features = [
    'Components & Templates',
    'Data Binding',
    'Directives',
    'Services & Dependency Injection',
    'Routing & Lazy Loading',
    'Forms (Template + Reactive)',
    'HTTP & REST API',
    'RxJS & Observables',
    'Guards & Interceptors',
    'State Management',
    'Pipes',
    'Storage (LocalStorage, SessionStorage, Cookies, IndexedDB)'
  ];
}

