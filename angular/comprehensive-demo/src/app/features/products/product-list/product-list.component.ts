import { Component, OnInit, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ApiService } from '../../../core/services/http/api.service';
import { Product } from '../../../models/product.model';
import { CurrencyFormatPipe } from '../../../shared/pipes/currency-format.pipe';
import { TruncatePipe } from '../../../shared/pipes/truncate.pipe';
import { FilterPipe } from '../../../shared/pipes/filter.pipe';
import { HighlightDirective } from '../../../shared/directives/highlight.directive';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-product-list',
  standalone: true,
  imports: [CommonModule, FormsModule, CurrencyFormatPipe, TruncatePipe, FilterPipe, HighlightDirective],
  templateUrl: './product-list.component.html',
  styleUrls: ['./product-list.component.scss']
})
export class ProductListComponent implements OnInit {
  private apiService = inject(ApiService);

  products: Product[] = [];
  filteredProducts: Product[] = [];
  searchTerm = '';
  loading = false;

  ngOnInit(): void {
    this.loadProducts();
  }

  loadProducts(): void {
    this.loading = true;
    this.apiService.get<Product[]>('/products').subscribe({
      next: (products) => {
        this.products = products;
        this.filteredProducts = products;
        this.loading = false;
      },
      error: () => {
        // Mock data
        this.products = this.getMockProducts();
        this.filteredProducts = this.products;
        this.loading = false;
      }
    });
  }

  private getMockProducts(): Product[] {
    return [
      {
        id: 1,
        name: 'Laptop',
        description: 'High-performance laptop for professionals',
        price: 999.99,
        category: 'Electronics',
        stock: 10,
        isAvailable: true,
        rating: 4.5,
        createdAt: new Date().toISOString(),
        updatedAt: new Date().toISOString()
      },
      {
        id: 2,
        name: 'Smartphone',
        description: 'Latest smartphone with advanced features',
        price: 699.99,
        category: 'Electronics',
        stock: 25,
        isAvailable: true,
        rating: 4.8,
        createdAt: new Date().toISOString(),
        updatedAt: new Date().toISOString()
      }
    ];
  }
}

