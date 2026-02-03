// @ts-nocheck
import { Component, OnInit, inject, signal } from '@angular/core';
import { AsyncPipe, NgIf } from '@angular/common';
import { CustomerService, Customer } from './customer.service';
import { CustomerTableComponent } from './customer-table.component';
import { CustomerEditorComponent } from './customer-editor.component';

@Component({
  selector: 'app-customer-shell',
  standalone: true,
  imports: [AsyncPipe, NgIf, CustomerTableComponent, CustomerEditorComponent],
  template: `
    <section class="shell">
      <app-customer-table
        [customers]="customers()"
        (create)="startCreate()"
        (edit)="startEdit($event)"
        (remove)="remove($event)"
      ></app-customer-table>

      <app-customer-editor
        *ngIf="editing()"
        [model]="editing()"
        (submitForm)="save($event)"
        (cancel)="reset()"
      ></app-customer-editor>
    </section>
  `,
  styles: [
    `
      .shell {
        display: grid;
        gap: 2rem;
        grid-template-columns: minmax(0, 2fr) minmax(0, 1fr);
      }
    `,
  ],
})
export class CustomerShellComponent implements OnInit {
  private customersService = inject(CustomerService);

  customers = this.customersService.customers;
  editing = signal<Customer | null>(null);

  ngOnInit(): void {
    this.customersService.load().subscribe();
  }

  startCreate(): void {
    this.editing.set({ id: '', name: '', email: '', status: 'active' });
  }

  startEdit(customer: Customer): void {
    this.editing.set(customer);
  }

  save(value: Omit<Customer, 'id'> | Customer): void {
    if ('id' in value && value.id) {
      this.customersService.update(value.id, value).subscribe(() => this.reset());
    } else {
      this.customersService.create(value).subscribe(() => this.reset());
    }
  }

  remove(customer: Customer): void {
    this.customersService.remove(customer.id).subscribe();
  }

  reset(): void {
    this.editing.set(null);
  }
}
