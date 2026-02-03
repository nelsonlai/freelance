/**
 * Register Component
 * 
 * This component demonstrates:
 * - Reactive forms (FormBuilder, FormGroup, FormControl)
 * - Form validation with validators
 * - Custom validators
 * - Programmatic form control
 * - Better type safety than template-driven forms
 * 
 * Reactive Forms:
 * - Forms are defined in the component class
 * - More control and flexibility
 * - Easier to test
 * - Better for complex forms
 * - Type-safe with TypeScript
 */

import { Component, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormBuilder, FormGroup, Validators, ReactiveFormsModule, AbstractControl, ValidationErrors } from '@angular/forms';
import { Router, RouterLink } from '@angular/router';
import { AuthService } from '../../../core/services/auth/auth.service';
import { AppStateService } from '../../../state/app.state';

@Component({
  selector: 'app-register',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule, RouterLink],
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.scss']
})
export class RegisterComponent {
  // Inject services
  private fb = inject(FormBuilder);
  private authService = inject(AuthService);
  private router = inject(Router);
  private appState = inject(AppStateService);

  /**
   * Reactive form group
   * 
   * FormGroup represents the entire form.
   * It contains FormControls for each field.
   */
  registerForm: FormGroup;

  /**
   * Loading state
   */
  isLoading = false;

  /**
   * Error message
   */
  errorMessage: string | null = null;

  /**
   * Constructor
   * 
   * Initializes the reactive form with validators.
   */
  constructor() {
    // Build form with FormBuilder
    // FormBuilder provides a convenient way to create forms
    this.registerForm = this.fb.group({
      firstName: ['', [Validators.required, Validators.minLength(2)]],
      lastName: ['', [Validators.required, Validators.minLength(2)]],
      email: ['', [Validators.required, Validators.email]],
      password: ['', [Validators.required, Validators.minLength(6)]],
      confirmPassword: ['', [Validators.required]]
    }, {
      // Form-level validator
      // Validators are functions that return ValidationErrors or null
      validators: this.passwordMatchValidator
    });
  }

  /**
   * Custom validator: Check if passwords match
   * 
   * Custom validators are functions that:
   * - Take an AbstractControl (FormControl or FormGroup)
   * - Return ValidationErrors object if invalid, null if valid
   * 
   * @param control - Form control or form group
   * @returns ValidationErrors or null
   */
  passwordMatchValidator(control: AbstractControl): ValidationErrors | null {
    const password = control.get('password');
    const confirmPassword = control.get('confirmPassword');

    if (!password || !confirmPassword) {
      return null;
    }

    // Check if passwords match
    if (password.value !== confirmPassword.value) {
      // Return error object
      // The key is the error name, value is the error data
      return { passwordMismatch: true };
    }

    return null;
  }

  /**
   * Getter for easy access to form controls
   * 
   * This allows us to use form.firstName instead of form.get('firstName')
   * in the template.
   */
  get firstName() {
    return this.registerForm.get('firstName');
  }

  get lastName() {
    return this.registerForm.get('lastName');
  }

  get email() {
    return this.registerForm.get('email');
  }

  get password() {
    return this.registerForm.get('password');
  }

  get confirmPassword() {
    return this.registerForm.get('confirmPassword');
  }

  /**
   * Handle form submission
   */
  onSubmit(): void {
    // Check if form is valid
    if (this.registerForm.invalid) {
      // Mark all fields as touched to show validation errors
      Object.keys(this.registerForm.controls).forEach(key => {
        this.registerForm.get(key)?.markAsTouched();
      });
      return;
    }

    // Reset error message
    this.errorMessage = null;
    this.isLoading = true;

    // Get form values
    const formValue = this.registerForm.value;

    // Call registration service
    this.authService.register({
      firstName: formValue.firstName,
      lastName: formValue.lastName,
      email: formValue.email,
      password: formValue.password,
      role: 'user' // Default role
    }).subscribe({
      next: (user) => {
        // Registration successful
        this.isLoading = false;
        console.log('Registration successful:', user);
        
        // Show success notification
        this.appState.addNotification({
          type: 'success',
          message: 'Registration successful! Welcome!'
        });

        // Navigate to dashboard
        this.router.navigate(['/dashboard']);
      },
      error: (error) => {
        // Registration failed
        this.isLoading = false;
        
        // Only show error if it's not a demo mode error (status 0 in development)
        // Demo mode errors are handled by auth service with mock registration
        if (error.status === 0 && !error.message) {
          // This shouldn't happen since auth service handles status 0, but just in case
          this.errorMessage = null;
        } else {
          this.errorMessage = error.message || 'Registration failed. Please try again.';
          
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
    this.registerForm.reset();
    this.errorMessage = null;
  }

  /**
   * Check if field has error
   * 
   * Helper method to check if a field has a specific error.
   * 
   * @param fieldName - Name of the form control
   * @param errorName - Name of the error to check
   * @returns true if field has the error, false otherwise
   */
  hasError(fieldName: string, errorName: string): boolean {
    const control = this.registerForm.get(fieldName);
    return !!(control && control.hasError(errorName) && control.touched);
  }
}

