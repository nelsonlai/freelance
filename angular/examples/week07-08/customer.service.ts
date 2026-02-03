// @ts-nocheck
import { Injectable, inject, signal } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { tap } from 'rxjs';

export interface Customer {
  id: string;
  name: string;
  email: string;
  status: 'active' | 'inactive';
}

@Injectable({ providedIn: 'root' })
export class CustomerService {
  private http = inject(HttpClient);
  customers = signal<Customer[]>([]);

  load() {
    return this.http.get<Customer[]>('/api/customers').pipe(tap((customers) => this.customers.set(customers)));
  }

  create(payload: Omit<Customer, 'id'>) {
    const tempId = crypto.randomUUID();
    const optimistic: Customer = { id: tempId, ...payload } as Customer;
    this.customers.update((list) => [optimistic, ...list]);

    return this.http.post<Customer>('/api/customers', payload).pipe(
      tap((customerFromServer) => {
        this.customers.update((list) =>
          list.map((customer) => (customer.id === tempId ? customerFromServer : customer)),
        );
      }),
    );
  }

  update(id: string, changes: Partial<Customer>) {
    this.customers.update((list) =>
      list.map((customer) => (customer.id === id ? { ...customer, ...changes } : customer)),
    );

    return this.http.patch<Customer>(`/api/customers/${id}`, changes).pipe(
      tap((customerFromServer) => {
        this.customers.update((list) =>
          list.map((customer) => (customer.id === id ? customerFromServer : customer)),
        );
      }),
    );
  }

  remove(id: string) {
    const snapshot = this.customers();
    this.customers.update((list) => list.filter((customer) => customer.id !== id));

    return this.http.delete(`/api/customers/${id}`).pipe(
      tap({
        error: () => this.customers.set(snapshot),
      }),
    );
  }
}
