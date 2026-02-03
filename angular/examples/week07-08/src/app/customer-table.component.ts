// @ts-nocheck
import { Component, EventEmitter, Input, Output } from '@angular/core';
import { NgFor, NgIf } from '@angular/common';
import { Customer } from './customer.service';
import { HasPermissionDirective } from './has-permission.directive';

@Component({
  selector: 'app-customer-table',
  standalone: true,
  imports: [NgFor, NgIf, HasPermissionDirective],
  template: `
    <section>
      <header class="header">
        <h2>Customers</h2>
        <button type="button" appHasPermission="admin" (click)="create.emit()">New Customer</button>
      </header>
      <table *ngIf="customers.length; else empty">
        <thead>
          <tr>
            <th>Name</th>
            <th>Email</th>
            <th>Status</th>
            <th></th>
          </tr>
        </thead>
        <tbody>
          <tr *ngFor="let customer of customers">
            <td>{{ customer.name }}</td>
            <td>{{ customer.email }}</td>
            <td>
              <span class="status" [class.inactive]="customer.status === 'inactive'">
                {{ customer.status }}
              </span>
            </td>
            <td>
              <button type="button" (click)="edit.emit(customer)">Edit</button>
              <button type="button" appHasPermission="admin" (click)="remove.emit(customer)">Delete</button>
            </td>
          </tr>
        </tbody>
      </table>
      <ng-template #empty>
        <p>No customers yet. Create your first record.</p>
      </ng-template>
    </section>
  `,
  styles: [
    `
      .header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-bottom: 1rem;
      }
      table {
        width: 100%;
        border-collapse: collapse;
      }
      th,
      td {
        padding: 0.75rem;
        border-bottom: 1px solid #e5e7eb;
      }
      button {
        margin-inline-end: 0.5rem;
      }
      .status.inactive {
        color: #dc2626;
      }
    `,
  ],
})
export class CustomerTableComponent {
  @Input() customers: Customer[] = [];
  @Output() create = new EventEmitter<void>();
  @Output() edit = new EventEmitter<Customer>();
  @Output() remove = new EventEmitter<Customer>();
}
