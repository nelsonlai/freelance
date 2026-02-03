import { Request, Response, NextFunction } from 'express';
import { verifyJwt } from '../lib/jwt.js';

export function requireAuth(req: Request, res: Response, next: NextFunction) {
	const header = req.headers.authorization;
	if (!header || !header.startsWith('Bearer ')) {
		return res.status(401).json({ error: 'UNAUTHORIZED', message: 'Missing bearer token' });
	}
	const token = header.slice('Bearer '.length);
	try {
		const payload = verifyJwt<{ userId: string }>(token);
		(req as any).userId = payload.userId;
		next();
	} catch {
		return res.status(401).json({ error: 'UNAUTHORIZED', message: 'Invalid token' });
	}
}


