import { Controller, Get, UseInterceptors, CacheInterceptor } from '@nestjs/common';
import { AppService } from './app.service';
import { CurrentUser } from './common/decorators/current-user.decorator';
import { ApiOperation, ApiResponse, ApiTags } from '@nestjs/swagger';

@ApiTags('App')
@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  @ApiOperation({ summary: 'Get hello message' })
  @ApiResponse({ status: 200, description: 'Returns hello message' })
  getHello(): string {
    return this.appService.getHello();
  }

  @Get('health')
  @ApiOperation({ summary: 'Health check' })
  getHealth() {
    return {
      status: 'ok',
      message: 'Server is running',
      timestamp: new Date().toISOString(),
    };
  }

  @Get('profile')
  @UseInterceptors(CacheInterceptor)
  @ApiOperation({ summary: 'Get current user profile' })
  getProfile(@CurrentUser() user: any) {
    return {
      message: 'User profile',
      user,
    };
  }
}

