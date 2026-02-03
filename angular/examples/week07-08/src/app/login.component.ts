// @ts-nocheck
import { Component, inject, signal } from '@angular/core';
import { NgIf } from '@angular/common';
import { FormBuilder, Validators, ReactiveFormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { AuthHttpService } from './auth-http.service';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [NgIf, ReactiveFormsModule],
  template: `
    <form [formGroup]="form" (ngSubmit)="submit()" class="login">
      <h1>Sign in</h1>
      <label>
        Email
        <input formControlName="email" type="email" autocomplete="email" />
      </label>
      <label>
        Password
        <input formControlName="password" type="password" autocomplete="current-password" />
      </label>
      <button type="submit" [disabled]="form.invalid || loading()">Log in</button>
      <p *ngIf="error()" class="error">{{ error() }}</p>
    </form>
  `,
  styles: [
    `
      .login {
        max-width: 24rem;
        margin: 0 auto;
        display: grid;
        gap: 1rem;
        padding: 2rem;
        border-radius: 1rem;
        border: 1px solid #e5e7eb;
        box-shadow: 0 20px 45px rgba(15, 23, 42, 0.1);
      }
      label {
        display: grid;
        gap: 0.5rem;
      }
      button {
        padding: 0.75rem 1.5rem;
        background: #2563eb;
        color: white;
        border: none;
        border-radius: 0.75rem;
        cursor: pointer;
      }
      .error {
        color: #dc2626;
      }
    `,
  ],
})
export class LoginComponent {
  private fb = inject(FormBuilder);
  private auth = inject(AuthHttpService);
  private router = inject(Router);

  loading = signal(false);
  error = signal<string | null>(null);

  form = this.fb.nonNullable.group({
    email: ['', [Validators.required, Validators.email]],
    password: ['', Validators.required],
  });

  submit(): void {
    if (this.form.invalid) {
      return;
    }
    this.loading.set(true);
    this.error.set(null);
    this.auth.login(this.form.getRawValue()).subscribe({
      next: () => {
        this.loading.set(false);
        this.router.navigate(['/customers']);
      },
      error: () => {
        this.loading.set(false);
        this.error.set('Invalid credentials');
      },
    });
  }
}
