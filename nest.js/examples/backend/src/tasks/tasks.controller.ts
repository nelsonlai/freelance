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
import { TasksService } from './tasks.service';
import { CreateTaskDto } from './dto/create-task.dto';

@Controller('tasks')
export class TasksController {
  constructor(private readonly tasksService: TasksService) {}

  // GET /api/tasks - Get all tasks
  @Get()
  findAll() {
    return {
      success: true,
      data: this.tasksService.findAll(),
    };
  }

  // GET /api/tasks/:id - Get a specific task
  @Get(':id')
  findOne(@Param('id') id: string) {
    return {
      success: true,
      data: this.tasksService.findOne(id),
    };
  }

  // POST /api/tasks - Create a new task
  @Post()
  @HttpCode(HttpStatus.CREATED)
  create(@Body() createTaskDto: CreateTaskDto) {
    return {
      success: true,
      message: 'Task created successfully',
      data: this.tasksService.create(createTaskDto),
    };
  }

  // PUT /api/tasks/:id - Update a task
  @Put(':id')
  update(@Param('id') id: string, @Body() updateTaskDto: Partial<CreateTaskDto>) {
    return {
      success: true,
      message: 'Task updated successfully',
      data: this.tasksService.update(id, updateTaskDto),
    };
  }

  // DELETE /api/tasks/:id - Delete a task
  @Delete(':id')
  @HttpCode(HttpStatus.NO_CONTENT)
  remove(@Param('id') id: string) {
    this.tasksService.remove(id);
    return {
      success: true,
      message: 'Task deleted successfully',
    };
  }

  // OPTIONS /api/tasks - CORS preflight
  @Options()
  @HttpCode(HttpStatus.NO_CONTENT)
  options() {
    return;
  }
}

