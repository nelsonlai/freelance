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
} from '@nestjs/common';
import { TodosService } from './todos.service';
import { CreateTodoDto } from './dto/create-todo.dto';

@Controller('todos')
export class TodosController {
  constructor(private readonly todosService: TodosService) {}

  // GET /todos - Get all todos
  @Get()
  findAll() {
    return {
      success: true,
      data: this.todosService.findAll(),
    };
  }

  // GET /todos/:id - Get a specific todo
  @Get(':id')
  findOne(@Param('id') id: string) {
    return {
      success: true,
      data: this.todosService.findOne(id),
    };
  }

  // POST /todos - Create a new todo
  @Post()
  @HttpCode(HttpStatus.CREATED)
  create(@Body() createTodoDto: CreateTodoDto) {
    return {
      success: true,
      message: 'Todo created successfully',
      data: this.todosService.create(createTodoDto),
    };
  }

  // PUT /todos/:id - Update a todo
  @Put(':id')
  update(@Param('id') id: string, @Body() updateTodoDto: Partial<CreateTodoDto>) {
    return {
      success: true,
      message: 'Todo updated successfully',
      data: this.todosService.update(id, updateTodoDto),
    };
  }

  // DELETE /todos/:id - Delete a todo
  @Delete(':id')
  @HttpCode(HttpStatus.NO_CONTENT)
  remove(@Param('id') id: string) {
    this.todosService.remove(id);
    return {
      success: true,
      message: 'Todo deleted successfully',
    };
  }
}

