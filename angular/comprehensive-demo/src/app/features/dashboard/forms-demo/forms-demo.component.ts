/**
 * Forms Demo Component
 * 
 * Demonstrates both template-driven and reactive forms side by side.
 */

import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, NgForm } from '@angular/forms';
import { FormBuilder, FormGroup, Validators, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-forms-demo',
  standalone: true,
  imports: [CommonModule, FormsModule, ReactiveFormsModule],
  templateUrl: './forms-demo.component.html',
  styleUrls: ['./forms-demo.component.scss']
})
export class FormsDemoComponent {
  // Template-driven form data
  templateForm = {
    name: '',
    email: ''
  };

  // Reactive form
  reactiveForm: FormGroup;

  constructor(private fb: FormBuilder) {
    this.reactiveForm = this.fb.group({
      name: ['', [Validators.required, Validators.minLength(2)]],
      email: ['', [Validators.required, Validators.email]]
    });
  }

  // Template-driven form submission
  onSubmitTemplate(form: NgForm): void {
    if (form.valid) {
      console.log('Template form submitted:', this.templateForm);
      alert('Template form submitted successfully!');
    }
  }

  // Reactive form submission
  onSubmitReactive(): void {
    if (this.reactiveForm.valid) {
      console.log('Reactive form submitted:', this.reactiveForm.value);
      alert('Reactive form submitted successfully!');
    } else {
      Object.keys(this.reactiveForm.controls).forEach(key => {
        this.reactiveForm.get(key)?.markAsTouched();
      });
    }
  }

  get name() {
    return this.reactiveForm.get('name');
  }

  get email() {
    return this.reactiveForm.get('email');
  }
}

