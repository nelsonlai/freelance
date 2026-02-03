import { CreateUserDto } from './dto/create-user.dto';
export interface User {
    id: string;
    name: string;
    email: string;
    age?: number;
    createdAt: Date;
    updatedAt: Date;
}
export declare class UsersService {
    private users;
    findAll(): User[];
    findOne(id: string): User;
    findByEmail(email: string): User | undefined;
    create(createUserDto: CreateUserDto): User;
    update(id: string, updateUserDto: Partial<CreateUserDto>): User;
    remove(id: string): void;
}
