import { Injectable, NotFoundException } from '@nestjs/common';
import { CreateTaskDto } from './dto/create-task.dto';

export interface Task {
  id: string;
  title: string;
  description?: string;
  completed: boolean;
  createdAt: Date;
  updatedAt: Date;
}

@Injectable()
export class TasksService {
  private tasks: Task[] = [
    {
      id: '1',
      title: 'Learn NestJS',
      description: 'Complete the NestJS tutorial',
      completed: false,
      createdAt: new Date(),
      updatedAt: new Date(),
    },
    {
      id: '2',
      title: 'Build RESTful API',
      description: 'Create a complete REST API with all methods',
      completed: true,
      createdAt: new Date(),
      updatedAt: new Date(),
    },
  ];

  findAll(): Task[] {
    return this.tasks;
  }

  findOne(id: string): Task {
    const task = this.tasks.find((task) => task.id === id);
    if (!task) {
      throw new NotFoundException(`Task with ID ${id} not found`);
    }
    return task;
  }

  create(createTaskDto: CreateTaskDto): Task {
    const task: Task = {
      id: Date.now().toString(),
      title: createTaskDto.title,
      description: createTaskDto.description,
      completed: createTaskDto.completed || false,
      createdAt: new Date(),
      updatedAt: new Date(),
    };
    this.tasks.push(task);
    return task;
  }

  update(id: string, updateTaskDto: Partial<CreateTaskDto>): Task {
    const task = this.findOne(id);
    Object.assign(task, updateTaskDto);
    task.updatedAt = new Date();
    return task;
  }

  remove(id: string): void {
    const index = this.tasks.findIndex((task) => task.id === id);
    if (index === -1) {
      throw new NotFoundException(`Task with ID ${id} not found`);
    }
    this.tasks.splice(index, 1);
  }
}

