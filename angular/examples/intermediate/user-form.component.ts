// @ts-nocheck
import { Component, inject, signal } from '@angular/core';
import { FormBuilder, Validators, ReactiveFormsModule } from '@angular/forms';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';
import { UsersService } from './users.service';

@Component({
  selector: 'app-user-form',
  standalone: true,
  imports: [ReactiveFormsModule],
  template: `
    <form [formGroup]="form" (ngSubmit)="save()">
      <label>
        Name
        <input formControlName="name" />
      </label>

      <label>
        Email
        <input formControlName="email" type="email" />
      </label>

      <label>
        Role
        <select formControlName="role">
          <option value="viewer">Viewer</option>
          <option value="editor">Editor</option>
          <option value="admin">Admin</option>
        </select>
      </label>

      <button type="submit" [disabled]="form.invalid || saving()">Save</button>
    </form>

    <p *ngIf="error()" class="error">Save failed: {{ error() }}</p>
  `,
  styles: [
    `
      form {
        display: grid;
        gap: 1rem;
        max-width: 24rem;
      }
      .error {
        color: #dc2626;
        margin-top: 1rem;
      }
    `,
  ],
})
export class UserFormComponent {
  private fb = inject(FormBuilder);
  private users = inject(UsersService);

  form = this.fb.nonNullable.group({
    name: ['', Validators.required],
    email: ['', [Validators.required, Validators.email]],
    role: ['viewer', Validators.required],
  });

  saving = signal(false);
  error = signal<string | null>(null);

  save(): void {
    if (this.form.invalid || this.saving()) {
      return;
    }

    this.saving.set(true);
    this.error.set(null);

    this.users
      .saveUser(this.form.getRawValue())
      .pipe(takeUntilDestroyed())
      .subscribe({
        next: () => {
          this.saving.set(false);
          this.form.reset({ role: 'viewer' });
        },
        error: (err) => {
          this.saving.set(false);
          this.error.set(err?.message ?? 'Unknown error');
        },
      });
  }
}
