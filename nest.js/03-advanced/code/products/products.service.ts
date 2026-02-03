import { Injectable, NotFoundException, ConflictException } from '@nestjs/common';
import { CreateProductDto } from './dto/create-product.dto';
import { CacheService } from '../cache/cache.service';

export interface Product {
  id: string;
  name: string;
  description?: string;
  price: number;
  stock?: number;
  imageUrl?: string;
  category?: string;
  createdAt: Date;
  updatedAt: Date;
}

@Injectable()
export class ProductsService {
  private products: Product[] = [
    {
      id: '1',
      name: 'Laptop',
      description: 'High-performance laptop',
      price: 999.99,
      stock: 10,
      category: 'electronics',
      createdAt: new Date(),
      updatedAt: new Date(),
    },
    {
      id: '2',
      name: 'Smartphone',
      description: 'Latest smartphone model',
      price: 699.99,
      stock: 25,
      category: 'electronics',
      createdAt: new Date(),
      updatedAt: new Date(),
    },
  ];

  constructor(private cacheService: CacheService) {}

  async findAll(): Promise<Product[]> {
    const cacheKey = 'products:all';
    const cached = await this.cacheService.get<Product[]>(cacheKey);
    
    if (cached) {
      return cached;
    }

    const products = this.products;
    await this.cacheService.set(cacheKey, products, 300); // Cache for 5 minutes
    return products;
  }

  async findOne(id: string): Promise<Product> {
    const cacheKey = `products:${id}`;
    const cached = await this.cacheService.get<Product>(cacheKey);
    
    if (cached) {
      return cached;
    }

    const product = this.products.find((p) => p.id === id);
    if (!product) {
      throw new NotFoundException(`Product with ID ${id} not found`);
    }

    await this.cacheService.set(cacheKey, product, 300);
    return product;
  }

  async create(createProductDto: CreateProductDto): Promise<Product> {
    // Check for duplicate name
    const existingProduct = this.products.find(
      (p) => p.name.toLowerCase() === createProductDto.name.toLowerCase(),
    );
    if (existingProduct) {
      throw new ConflictException('Product with this name already exists');
    }

    const product: Product = {
      id: Date.now().toString(),
      ...createProductDto,
      stock: createProductDto.stock || 0,
      createdAt: new Date(),
      updatedAt: new Date(),
    };

    this.products.push(product);
    
    // Invalidate cache
    await this.cacheService.del('products:all');
    
    return product;
  }

  async update(id: string, updateProductDto: Partial<CreateProductDto>): Promise<Product> {
    const product = await this.findOne(id);

    // Check for duplicate name if name is being updated
    if (updateProductDto.name && updateProductDto.name !== product.name) {
      const existingProduct = this.products.find(
        (p) => p.id !== id && p.name.toLowerCase() === updateProductDto.name.toLowerCase(),
      );
      if (existingProduct) {
        throw new ConflictException('Product with this name already exists');
      }
    }

    Object.assign(product, updateProductDto);
    product.updatedAt = new Date();

    // Invalidate cache
    await this.cacheService.del(`products:${id}`);
    await this.cacheService.del('products:all');

    return product;
  }

  async remove(id: string): Promise<void> {
    const index = this.products.findIndex((p) => p.id === id);
    if (index === -1) {
      throw new NotFoundException(`Product with ID ${id} not found`);
    }

    this.products.splice(index, 1);

    // Invalidate cache
    await this.cacheService.del(`products:${id}`);
    await this.cacheService.del('products:all');
  }

  async findByCategory(category: string): Promise<Product[]> {
    return this.products.filter((p) => p.category === category);
  }
}

