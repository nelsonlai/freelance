import { IsString, IsEmail, IsNotEmpty, IsOptional, IsInt, Min, Max } from 'class-validator';

export class CreateUserDto {
  @IsString()
  @IsNotEmpty()
  name: string;

  @IsEmail()
  @IsNotEmpty()
  email: string;

  @IsInt()
  @Min(18)
  @Max(100)
  @IsOptional()
  age?: number;
}

