// @ts-nocheck
import { Component, inject, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormBuilder, Validators, ReactiveFormsModule, FormGroup } from '@angular/forms';
import { debounceTime, distinctUntilChanged, switchMap, of } from 'rxjs';
import { ApiService, RegistrationResponse } from '../shared/api.service';

@Component({
  selector: 'app-registration-form',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  template: `
    <form [formGroup]="form" (ngSubmit)="submit()" novalidate>
      <fieldset>
        <legend>Profile</legend>
        <label>
          Full Name
          <input formControlName="name" autocomplete="name" />
        </label>
        <span class="error" *ngIf="form.controls.name.errors?.['required'] && form.controls.name.touched">
          Name is required.
        </span>

        <label>
          Email
          <input formControlName="email" autocomplete="email" />
        </label>
        <span class="error" *ngIf="form.controls.email.errors?.['email']">
          Enter a valid email address.
        </span>
        <span class="error" *ngIf="form.controls.email.errors?.['taken']">
          This email domain is already registered.
        </span>
      </fieldset>

      <fieldset>
        <legend>Preferences</legend>
        <label>
          Role
          <select formControlName="role">
            <option value="developer">Developer</option>
            <option value="designer">Designer</option>
            <option value="manager">Manager</option>
          </select>
        </label>

        <label>
          Newsletter
          <input type="checkbox" formControlName="newsletter" /> Subscribe me
        </label>
      </fieldset>

      <fieldset>
        <legend>Security</legend>
        <label>
          Password
          <input type="password" formControlName="password" autocomplete="new-password" />
        </label>
        <span class="error" *ngIf="passwordErrors()?.['weak']">
          Password must include 12+ chars, uppercase, number, and symbol.
        </span>

        <label>
          Confirm Password
          <input type="password" formControlName="confirmPassword" autocomplete="new-password" />
        </label>
        <span class="error" *ngIf="form.errors?.['passwordMismatch'] && form.controls.confirmPassword.touched">
          Passwords must match.
        </span>
      </fieldset>

      <button type="submit" [disabled]="form.invalid || submitting()">Create Account</button>
    </form>

    <section *ngIf="result()" class="result">
      <h3>Backend Response</h3>
      <p>{{ result()?.message }}</p>
      <ul>
        <li><strong>Name:</strong> {{ result()?.data?.name ?? '—' }}</li>
        <li><strong>Email:</strong> {{ result()?.data?.email ?? '—' }}</li>
        <li><strong>Role:</strong> {{ result()?.data?.role ?? '—' }}</li>
        <li><strong>Newsletter:</strong> {{ result()?.data?.newsletter ? 'Yes' : 'No' }}</li>
        <li><strong>Password:</strong> {{ result()?.data?.password ?? '—' }}</li>
        <li><strong>Received At:</strong> {{ result()?.receivedAt | date:'medium' }}</li>
      </ul>
    </section>

    <p *ngIf="error()" class="error">{{ error() }}</p>
  `,
  styles: [
    `
      form {
        display: grid;
        gap: 1.5rem;
        max-width: 36rem;
      }
      fieldset {
        border: 1px solid #e5e7eb;
        border-radius: 0.75rem;
        padding: 1rem 1.5rem;
        display: grid;
        gap: 0.75rem;
      }
      label {
        display: grid;
        gap: 0.5rem;
        font-weight: 500;
      }
      .error {
        color: #dc2626;
        font-size: 0.85rem;
      }
      button {
        width: fit-content;
        padding: 0.75rem 1.5rem;
        border-radius: 0.75rem;
        background: #2563eb;
        color: white;
        border: none;
        cursor: pointer;
        font-weight: 600;
      }
      .result {
        margin-top: 2rem;
        padding: 1.5rem;
        border-radius: 1rem;
        background: #ecfeff;
        border: 1px solid #22d3ee;
        max-width: 36rem;
      }
      .result ul {
        list-style: none;
        padding: 0;
        margin: 0;
        display: grid;
        gap: 0.5rem;
      }
    `,
  ],
})
export class RegistrationFormComponent {
  private fb = inject(FormBuilder);
  private api = inject(ApiService);

  submitting = signal(false);
  result = signal<RegistrationResponse | null>(null);
  error = signal<string | null>(null);

  form = this.fb.nonNullable.group(
    {
      name: ['', Validators.required],
      email: ['', [Validators.required, Validators.email]],
      role: ['developer', Validators.required],
      newsletter: [false],
      password: ['', Validators.required],
      confirmPassword: ['', Validators.required],
    },
    { validators: this.passwordMatchValidator },
  );

  ngOnInit(): void {
    this.form.controls.password.valueChanges
      .pipe(debounceTime(300), distinctUntilChanged())
      .subscribe((value) => {
        const weak = !/^(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*]).{12,}$/.test(value || '');
        const control = this.form.controls.password;
        if (weak) {
          control.setErrors({ ...(control.errors ?? {}), weak: true });
        } else if (control.hasError('weak')) {
          const { weak: _weak, ...rest } = control.errors ?? {};
          control.setErrors(Object.keys(rest).length ? rest : null);
        }
      });

    this.form.controls.email.valueChanges
      .pipe(
        debounceTime(400),
        distinctUntilChanged(),
        switchMap((email) => {
          if (!email) {
            return of({});
          }
          return of({ taken: email.endsWith('@example.com') });
        }),
      )
      .subscribe((result) => {
        const control = this.form.controls.email;
        if (result['taken']) {
          control.setErrors({ ...(control.errors ?? {}), taken: true });
        } else if (control.hasError('taken')) {
          const { taken, ...rest } = control.errors ?? {};
          control.setErrors(Object.keys(rest).length ? rest : null);
        }
      });
  }

  passwordErrors() {
    return this.form.controls.password.errors;
  }

  submit(): void {
    if (this.form.invalid) {
      this.form.markAllAsTouched();
      return;
    }

    const { confirmPassword, ...payload } = this.form.getRawValue();
    this.submitting.set(true);
    this.error.set(null);

    this.api.submitRegistration(payload).subscribe({
      next: (response) => {
        this.submitting.set(false);
        this.result.set(response);
        this.form.reset({ role: 'developer', newsletter: false, password: '', confirmPassword: '' });
      },
      error: () => {
        this.submitting.set(false);
        this.error.set('Unable to reach the server. Please try again.');
      },
    });
  }

  private passwordMatchValidator(group: FormGroup) {
    const password = group.get('password')?.value;
    const confirm = group.get('confirmPassword')?.value;
    return password === confirm ? null : { passwordMismatch: true };
  }
}
