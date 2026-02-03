import {
  Controller,
  Get,
  Post,
  Put,
  Delete,
  Body,
  Param,
  HttpCode,
  HttpStatus,
  UseInterceptors,
  UseGuards,
  Query,
  ParseIntPipe as CustomParseIntPipe,
} from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';
import { TransformInterceptor } from '../common/interceptors/transform.interceptor';
import { AuthGuard } from '../auth/guards/auth.guard';
import { Roles } from '../auth/decorators/roles.decorator';
import { RolesGuard } from '../auth/guards/roles.guard';

@Controller('users')
@UseInterceptors(TransformInterceptor)
@UseGuards(AuthGuard)
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  // GET /users - Get all users (with optional query parameters)
  @Get()
  findAll(@Query('minAge') minAge?: string, @Query('maxAge') maxAge?: string) {
    let users = this.usersService.findAll();

    // Filter by age if provided
    if (minAge) {
      const min = parseInt(minAge, 10);
      users = users.filter((user) => user.age && user.age >= min);
    }
    if (maxAge) {
      const max = parseInt(maxAge, 10);
      users = users.filter((user) => user.age && user.age <= max);
    }

    return users;
  }

  // GET /users/:id - Get a specific user
  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.usersService.findOne(id);
  }

  // POST /users - Create a new user
  @Post()
  @HttpCode(HttpStatus.CREATED)
  create(@Body() createUserDto: CreateUserDto) {
    return {
      message: 'User created successfully',
      data: this.usersService.create(createUserDto),
    };
  }

  // PUT /users/:id - Update a user
  @Put(':id')
  update(@Param('id') id: string, @Body() updateUserDto: Partial<CreateUserDto>) {
    return {
      message: 'User updated successfully',
      data: this.usersService.update(id, updateUserDto),
    };
  }

  // DELETE /users/:id - Delete a user (Admin only)
  @Delete(':id')
  @Roles('admin')
  @UseGuards(RolesGuard)
  @HttpCode(HttpStatus.NO_CONTENT)
  remove(@Param('id') id: string) {
    this.usersService.remove(id);
    return {
      message: 'User deleted successfully',
    };
  }
}

