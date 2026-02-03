// @ts-nocheck
import { Component, EventEmitter, Input, OnChanges, Output, SimpleChanges, inject } from '@angular/core';
import { FormBuilder, ReactiveFormsModule, Validators } from '@angular/forms';
import { Customer } from './customer.service';

@Component({
  selector: 'app-customer-editor',
  standalone: true,
  imports: [ReactiveFormsModule],
  template: `
    <form [formGroup]="form" (ngSubmit)="save()" class="editor">
      <h3>{{ form.value.id ? 'Edit Customer' : 'Create Customer' }}</h3>
      <label>
        Name
        <input formControlName="name" />
      </label>
      <label>
        Email
        <input formControlName="email" type="email" />
      </label>
      <label>
        Status
        <select formControlName="status">
          <option value="active">Active</option>
          <option value="inactive">Inactive</option>
        </select>
      </label>
      <button type="submit" [disabled]="form.invalid">Save</button>
      <button type="button" (click)="cancel.emit()">Cancel</button>
    </form>
  `,
  styles: [
    `
      .editor {
        display: grid;
        gap: 0.75rem;
        max-width: 24rem;
        padding: 1.5rem;
        border-radius: 0.75rem;
        border: 1px solid #e5e7eb;
        background: #f9fafb;
      }
      label {
        display: grid;
        gap: 0.5rem;
      }
      button {
        width: fit-content;
      }
    `,
  ],
})
export class CustomerEditorComponent implements OnChanges {
  private fb = inject(FormBuilder);

  @Input() model: Customer | null = null;
  @Output() submitForm = new EventEmitter<Omit<Customer, 'id'> | Customer>();
  @Output() cancel = new EventEmitter<void>();

  form = this.fb.group({
    id: [''],
    name: ['', Validators.required],
    email: ['', [Validators.required, Validators.email]],
    status: ['active', Validators.required],
  });

  ngOnChanges(changes: SimpleChanges): void {
    if (changes['model']) {
      this.form.reset({
        id: this.model?.id ?? '',
        name: this.model?.name ?? '',
        email: this.model?.email ?? '',
        status: this.model?.status ?? 'active',
      });
    }
  }

  save(): void {
    if (this.form.invalid) {
      return;
    }
    const value = this.form.getRawValue();
    const { id, ...rest } = value;
    this.submitForm.emit(id ? (value as Customer) : rest);
  }
}
