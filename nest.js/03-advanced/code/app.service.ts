import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';

@Injectable()
export class AppService {
  constructor(private configService: ConfigService) {}

  getHello(): string {
    const appName = this.configService.get<string>('app.name', 'NestJS');
    return `Hello World! Welcome to ${appName} Advanced Tutorial`;
  }
}

