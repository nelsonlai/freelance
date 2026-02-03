import { DynamicModule, Module } from '@nestjs/common';
import { CacheService } from './cache.service';

export interface CacheModuleOptions {
  host: string;
  port: number;
  ttl?: number;
}

@Module({})
export class CacheModule {
  static forRoot(options: CacheModuleOptions): DynamicModule {
    return {
      module: CacheModule,
      providers: [
        {
          provide: 'CACHE_OPTIONS',
          useValue: options,
        },
        CacheService,
      ],
      exports: [CacheService],
      global: true,
    };
  }
}

