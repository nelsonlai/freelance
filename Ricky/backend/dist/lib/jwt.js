import jwt from 'jsonwebtoken';
const jwtSecret = process.env.JWT_SECRET;
if (!jwtSecret) {
    throw new Error('JWT_SECRET not set');
}
export function signJwt(payload, expiresIn = '7d') {
    return jwt.sign(payload, jwtSecret, { expiresIn });
}
export function verifyJwt(token) {
    return jwt.verify(token, jwtSecret);
}
//# sourceMappingURL=jwt.js.map