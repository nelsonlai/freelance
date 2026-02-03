import { Injectable, NotFoundException } from '@nestjs/common';
import { CreateUserDto } from './dto/create-user.dto';

export interface User {
  id: string;
  name: string;
  email: string;
  age?: number;
  createdAt: Date;
  updatedAt: Date;
}

@Injectable()
export class UsersService {
  private users: User[] = [
    {
      id: '1',
      name: 'John Doe',
      email: 'john@example.com',
      age: 30,
      createdAt: new Date(),
      updatedAt: new Date(),
    },
    {
      id: '2',
      name: 'Jane Smith',
      email: 'jane@example.com',
      age: 25,
      createdAt: new Date(),
      updatedAt: new Date(),
    },
  ];

  findAll(): User[] {
    return this.users;
  }

  findOne(id: string): User {
    const user = this.users.find((user) => user.id === id);
    if (!user) {
      throw new NotFoundException(`User with ID ${id} not found`);
    }
    return user;
  }

  create(createUserDto: CreateUserDto): User {
    const user: User = {
      id: Date.now().toString(),
      name: createUserDto.name,
      email: createUserDto.email,
      age: createUserDto.age,
      createdAt: new Date(),
      updatedAt: new Date(),
    };
    this.users.push(user);
    return user;
  }

  update(id: string, updateUserDto: Partial<CreateUserDto>): User {
    const user = this.findOne(id);
    Object.assign(user, updateUserDto);
    user.updatedAt = new Date();
    return user;
  }

  remove(id: string): void {
    const index = this.users.findIndex((user) => user.id === id);
    if (index === -1) {
      throw new NotFoundException(`User with ID ${id} not found`);
    }
    this.users.splice(index, 1);
  }
}

