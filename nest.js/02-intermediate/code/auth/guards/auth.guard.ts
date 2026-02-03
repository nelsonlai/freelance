import {
  Injectable,
  CanActivate,
  ExecutionContext,
  UnauthorizedException,
} from '@nestjs/common';
import { Reflector } from '@nestjs/core';
import { IS_PUBLIC_KEY } from '../decorators/public.decorator';

@Injectable()
export class AuthGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate(context: ExecutionContext): boolean {
    const isPublic = this.reflector.getAllAndOverride<boolean>(IS_PUBLIC_KEY, [
      context.getHandler(),
      context.getClass(),
    ]);

    if (isPublic) {
      return true;
    }

    const request = context.switchToHttp().getRequest();
    const token = request.headers.authorization;

    if (!token) {
      throw new UnauthorizedException('No token provided');
    }

    // In a real application, you would validate the JWT token here
    // For this tutorial, we'll just check if it exists
    // Extract token from "Bearer <token>" format
    const tokenValue = token.replace('Bearer ', '');
    
    // Simple validation (in production, use JWT verification)
    if (tokenValue === 'valid-token' || tokenValue.length > 0) {
      // Attach user to request (in real app, decode JWT and get user)
      request.user = {
        id: '1',
        email: 'user@example.com',
        roles: ['user'],
      };
      return true;
    }

    throw new UnauthorizedException('Invalid token');
  }
}

