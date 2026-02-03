import {
  IsString,
  IsEmail,
  IsOptional,
  IsInt,
  Min,
  Max,
  MinLength,
  MaxLength,
} from 'class-validator';

export class CreateUserDto {
  @IsString()
  @MinLength(3)
  @MaxLength(50)
  name: string;

  @IsEmail()
  email: string;

  @IsOptional()
  @IsInt()
  @Min(18)
  @Max(100)
  age?: number;
}

