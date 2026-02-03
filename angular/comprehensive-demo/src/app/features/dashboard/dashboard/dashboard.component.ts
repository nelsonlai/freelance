/**
 * Dashboard Component
 * 
 * Main dashboard that demonstrates:
 * - Service injection
 * - Observable subscriptions
 * - Data binding
 * - Component communication
 */

import { Component, OnInit, OnDestroy, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';
import { Subscription } from 'rxjs';
import { AuthService } from '../../../core/services/auth/auth.service';
import { AppStateService } from '../../../state/app.state';
import { User } from '../../../models/user.model';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss']
})
export class DashboardComponent implements OnInit, OnDestroy {
  private authService = inject(AuthService);
  private appState = inject(AppStateService);

  currentUser: User | null = null;
  isAuthenticated = false;
  loading = false;

  // Subscription to manage observables
  private subscriptions = new Subscription();

  ngOnInit(): void {
    // Subscribe to current user
    const userSub = this.authService.currentUser$.subscribe(user => {
      this.currentUser = user;
    });
    this.subscriptions.add(userSub);

    // Subscribe to authentication status
    const authSub = this.authService.isAuthenticated$.subscribe(isAuth => {
      this.isAuthenticated = isAuth;
    });
    this.subscriptions.add(authSub);

    // Subscribe to loading state
    const loadingSub = this.appState.select(state => state.loading).subscribe(loading => {
      this.loading = loading;
    });
    this.subscriptions.add(loadingSub);
  }

  ngOnDestroy(): void {
    // Unsubscribe from all observables to prevent memory leaks
    this.subscriptions.unsubscribe();
  }
}

