// @ts-nocheck
import { TestBed } from '@angular/core/testing';
import { HttpClientTestingModule, HttpTestingController } from '@angular/common/http/testing';
import { CustomerService } from './customer.service';

describe('CustomerService', () => {
  let service: CustomerService;
  let http: HttpTestingController;

  beforeEach(() => {
    TestBed.configureTestingModule({
      imports: [HttpClientTestingModule],
    });
    service = TestBed.inject(CustomerService);
    http = TestBed.inject(HttpTestingController);
  });

  afterEach(() => {
    http.verify();
  });

  it('loads customers and updates signal', () => {
    const mock = [{ id: '1', name: 'Ada Lovelace', email: 'ada@example.com', status: 'active' }];
    service.load().subscribe();
    http.expectOne('/api/customers').flush(mock);
    expect(service.customers()).toEqual(mock);
  });
});
