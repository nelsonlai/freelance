import { Test, TestingModule } from '@nestjs/testing';
import { ProductsService } from './products.service';
import { CacheService } from '../cache/cache.service';

describe('ProductsService', () => {
  let service: ProductsService;
  let cacheService: CacheService;

  const mockCacheService = {
    get: jest.fn(),
    set: jest.fn(),
    del: jest.fn(),
    clear: jest.fn(),
  };

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [
        ProductsService,
        {
          provide: CacheService,
          useValue: mockCacheService,
        },
      ],
    }).compile();

    service = module.get<ProductsService>(ProductsService);
    cacheService = module.get<CacheService>(CacheService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });

  it('should return all products', async () => {
    mockCacheService.get.mockResolvedValue(null);
    const products = await service.findAll();
    expect(Array.isArray(products)).toBe(true);
    expect(products.length).toBeGreaterThan(0);
  });

  it('should create a product', async () => {
    mockCacheService.del.mockResolvedValue(undefined);
    const createDto = {
      name: 'Test Product',
      price: 99.99,
      description: 'Test description',
    };
    const product = await service.create(createDto);
    expect(product).toHaveProperty('id');
    expect(product.name).toBe(createDto.name);
  });

  it('should find a product by id', async () => {
    mockCacheService.get.mockResolvedValue(null);
    const product = await service.findOne('1');
    expect(product).toHaveProperty('id');
    expect(product.id).toBe('1');
  });

  it('should throw NotFoundException for non-existent product', async () => {
    mockCacheService.get.mockResolvedValue(null);
    await expect(service.findOne('999')).rejects.toThrow();
  });
});

