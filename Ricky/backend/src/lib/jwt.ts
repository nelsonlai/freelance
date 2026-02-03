import jwt from 'jsonwebtoken';

const jwtSecret = process.env.JWT_SECRET;
if (!jwtSecret) {
	throw new Error('JWT_SECRET not set');
}

export function signJwt(payload: Record<string, unknown>, expiresIn = '7d'): string {
	return jwt.sign(payload, jwtSecret, { expiresIn });
}

export function verifyJwt<T = any>(token: string): T {
	return jwt.verify(token, jwtSecret) as T;
}


