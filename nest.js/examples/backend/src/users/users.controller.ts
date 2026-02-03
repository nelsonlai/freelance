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
  Options,
} from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';

@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  // GET /api/users - Get all users
  @Get()
  findAll() {
    return {
      success: true,
      data: this.usersService.findAll(),
    };
  }

  // GET /api/users/:id - Get a specific user
  @Get(':id')
  findOne(@Param('id') id: string) {
    return {
      success: true,
      data: this.usersService.findOne(id),
    };
  }

  // POST /api/users - Create a new user
  @Post()
  @HttpCode(HttpStatus.CREATED)
  create(@Body() createUserDto: CreateUserDto) {
    return {
      success: true,
      message: 'User created successfully',
      data: this.usersService.create(createUserDto),
    };
  }

  // PUT /api/users/:id - Update a user
  @Put(':id')
  update(@Param('id') id: string, @Body() updateUserDto: Partial<CreateUserDto>) {
    return {
      success: true,
      message: 'User updated successfully',
      data: this.usersService.update(id, updateUserDto),
    };
  }

  // DELETE /api/users/:id - Delete a user
  @Delete(':id')
  @HttpCode(HttpStatus.NO_CONTENT)
  remove(@Param('id') id: string) {
    this.usersService.remove(id);
    return {
      success: true,
      message: 'User deleted successfully',
    };
  }

  // OPTIONS /api/users - CORS preflight
  @Options()
  @HttpCode(HttpStatus.NO_CONTENT)
  options() {
    return;
  }
}

