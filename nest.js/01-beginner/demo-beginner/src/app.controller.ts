import { Controller, Get, Res } from '@nestjs/common';
import { AppService } from './app.service';
import type { Response } from 'express';
import { join } from 'path';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  getIndex(@Res() res: Response) {
    // Serve index.html at root path
    res.sendFile(join(__dirname, '..', 'public', 'index.html'));
  }

  @Get('hello')
  getHello(): string {
    return this.appService.getHello();
  }

  @Get('health')
  getHealth() {
    return {
      status: 'ok',
      message: 'Server is running',
      timestamp: new Date().toISOString(),
    };
  }
}

