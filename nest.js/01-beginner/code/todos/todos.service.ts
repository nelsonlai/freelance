import { Injectable, NotFoundException } from '@nestjs/common';
import { CreateTodoDto } from './dto/create-todo.dto';

export interface Todo {
  id: string;
  title: string;
  description?: string;
  completed: boolean;
  createdAt: Date;
  updatedAt: Date;
}

@Injectable()
export class TodosService {
  // In-memory storage (for learning purposes)
  private todos: Todo[] = [
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

  // GET - Retrieve all todos
  findAll(): Todo[] {
    return this.todos;
  }

  // GET - Retrieve a specific todo
  findOne(id: string): Todo {
    const todo = this.todos.find((todo) => todo.id === id);
    if (!todo) {
      throw new NotFoundException(`Todo with ID ${id} not found`);
    }
    return todo;
  }

  // POST - Create a new todo
  create(createTodoDto: CreateTodoDto): Todo {
    const todo: Todo = {
      id: Date.now().toString(),
      title: createTodoDto.title,
      description: createTodoDto.description,
      completed: createTodoDto.completed || false,
      createdAt: new Date(),
      updatedAt: new Date(),
    };
    this.todos.push(todo);
    return todo;
  }

  // PUT - Update an entire todo
  update(id: string, updateTodoDto: Partial<CreateTodoDto>): Todo {
    const todo = this.findOne(id);
    Object.assign(todo, updateTodoDto);
    todo.updatedAt = new Date();
    return todo;
  }

  // DELETE - Remove a todo
  remove(id: string): void {
    const index = this.todos.findIndex((todo) => todo.id === id);
    if (index === -1) {
      throw new NotFoundException(`Todo with ID ${id} not found`);
    }
    this.todos.splice(index, 1);
  }
}

