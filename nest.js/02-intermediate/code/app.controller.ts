import { Controller, Get, UseGuards } from '@nestjs/common';
import { AppService } from './app.service';
import { AuthGuard } from './auth/guards/auth.guard';
import { Public } from './auth/decorators/public.decorator';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Public()
  @Get()
  getHello(): string {
    return this.appService.getHello();
  }

  @Public()
  @Get('health')
  getHealth() {
    return {
      status: 'ok',
      message: 'Server is running',
      timestamp: new Date().toISOString(),
    };
  }

  @UseGuards(AuthGuard)
  @Get('protected')
  getProtected() {
    return {
      message: 'This is a protected route',
      timestamp: new Date().toISOString(),
    };
  }
}

