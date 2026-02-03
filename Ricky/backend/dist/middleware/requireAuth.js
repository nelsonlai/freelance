import { verifyJwt } from '../lib/jwt.js';
export function requireAuth(req, res, next) {
    const header = req.headers.authorization;
    if (!header || !header.startsWith('Bearer ')) {
        return res.status(401).json({ error: 'UNAUTHORIZED', message: 'Missing bearer token' });
    }
    const token = header.slice('Bearer '.length);
    try {
        const payload = verifyJwt(token);
        req.userId = payload.userId;
        next();
    }
    catch {
        return res.status(401).json({ error: 'UNAUTHORIZED', message: 'Invalid token' });
    }
}
//# sourceMappingURL=requireAuth.js.map