import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';
export declare class UsersController {
    private readonly usersService;
    constructor(usersService: UsersService);
    findAll(minAge?: string, maxAge?: string): import("./users.service").User[];
    findOne(id: string): import("./users.service").User;
    create(createUserDto: CreateUserDto): {
        message: string;
        data: import("./users.service").User;
    };
    update(id: string, updateUserDto: Partial<CreateUserDto>): {
        message: string;
        data: import("./users.service").User;
    };
    remove(id: string): {
        message: string;
    };
}
