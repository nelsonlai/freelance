/**
 * Login Component
 * 
 * This component demonstrates:
 * - Template-driven forms
 * - Two-way data binding with [(ngModel)]
 * - Form validation
 * - Event handling
 * - Router navigation
 * - Service integration
 * 
 * Template-Driven Forms:
 * - Forms are defined in the template
 * - Angular creates FormControl objects automatically
 * - Simpler for basic forms
 * - Less programmatic control
 */

import { Component, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Router, ActivatedRoute, RouterLink } from '@angular/router';
import { AuthService } from '../../../core/services/auth/auth.service';
import { AppStateService } from '../../../state/app.state';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterLink],
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent {
  // Inject services
  private authService = inject(AuthService);
  private router = inject(Router);
  private route = inject(ActivatedRoute);
  private appState = inject(AppStateService);

  /**
   * Login form model
   * 
   * In template-driven forms, we use a simple object to hold form data.
   * Angular's [(ngModel)] directive binds to these properties.
   */
  loginForm = {
    email: '',
    password: ''
  };

  /**
   * Loading state
   * Used to show loading spinner during login
   */
  isLoading = false;

  /**
   * Error message
   * Displayed if login fails
   */
  errorMessage: string | null = null;

  /**
   * Return URL
   * Where to redirect after successful login
   */
  returnUrl: string = '/dashboard';

  /**
   * Constructor
   * 
   * Gets return URL from query parameters if available.
   */
  constructor() {
    // Get return URL from route query params
    this.route.queryParams.subscribe(params => {
      this.returnUrl = params['returnUrl'] || '/dashboard';
    });
  }

  /**
   * Handle form submission
   * 
   * Called when user submits the login form.
   * 
   * @param form - Form reference (for validation)
   */
  onSubmit(form: any): void {
    // Check if form is valid
    if (form.invalid) {
      // Mark all fields as touched to show validation errors
      Object.keys(form.controls).forEach(key => {
        form.controls[key].markAsTouched();
      });
      return;
    }

    // Reset error message
    this.errorMessage = null;
    this.isLoading = true;

    // Call authentication service
    this.authService.login({
      email: this.loginForm.email,
      password: this.loginForm.password
    }).subscribe({
      next: (user) => {
        // Login successful
        this.isLoading = false;
        console.log('Login successful:', user);
        
        // Update app state
        this.appState.addNotification({
          type: 'success',
          message: 'Login successful!'
        });

        // Navigate to return URL or dashboard
        this.router.navigate([this.returnUrl]);
      },
      error: (error) => {
        // Login failed
        this.isLoading = false;
        
        // Only show error if it's not a demo mode error (status 0 in development)
        // Demo mode errors are handled by auth service with mock login
        if (error.status === 0 && !error.message) {
          // This shouldn't happen since auth service handles status 0, but just in case
          this.errorMessage = null;
        } else {
          this.errorMessage = error.message || 'Login failed. Please check your credentials.';
          
          // Show error notification only if there's a real error
          if (this.errorMessage) {
            this.appState.addNotification({
              type: 'error',
              message: this.errorMessage
            });
          }
        }
      }
    });
  }

  /**
   * Reset form
   */
  resetForm(): void {
    this.loginForm = {
      email: '',
      password: ''
    };
    this.errorMessage = null;
  }
}

