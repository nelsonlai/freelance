"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.UsersService = void 0;
const common_1 = require("@nestjs/common");
let UsersService = class UsersService {
    constructor() {
        this.users = [
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
    }
    findAll() {
        return this.users;
    }
    findOne(id) {
        const user = this.users.find((user) => user.id === id);
        if (!user) {
            throw new common_1.NotFoundException(`User with ID ${id} not found`);
        }
        return user;
    }
    findByEmail(email) {
        return this.users.find((user) => user.email === email);
    }
    create(createUserDto) {
        const existingUser = this.findByEmail(createUserDto.email);
        if (existingUser) {
            throw new common_1.ConflictException('User with this email already exists');
        }
        const user = {
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
    update(id, updateUserDto) {
        const user = this.findOne(id);
        if (updateUserDto.email && updateUserDto.email !== user.email) {
            const existingUser = this.findByEmail(updateUserDto.email);
            if (existingUser) {
                throw new common_1.ConflictException('User with this email already exists');
            }
        }
        Object.assign(user, updateUserDto);
        user.updatedAt = new Date();
        return user;
    }
    remove(id) {
        const index = this.users.findIndex((user) => user.id === id);
        if (index === -1) {
            throw new common_1.NotFoundException(`User with ID ${id} not found`);
        }
        this.users.splice(index, 1);
    }
};
exports.UsersService = UsersService;
exports.UsersService = UsersService = __decorate([
    (0, common_1.Injectable)()
], UsersService);
//# sourceMappingURL=users.service.js.map