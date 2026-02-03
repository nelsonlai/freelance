import { Router } from 'express';
import { prisma } from '../lib/prisma.js';
import bcrypt from 'bcryptjs';
import { z } from 'zod';
import crypto from 'crypto';
import { signJwt } from '../lib/jwt.js';

const router = Router();

const emailSchema = z.string().email().min(1);
const passwordSchema = z.string().min(8, 'Password must be at least 8 characters');

router.post('/register', async (req, res, next) => {
	try {
		const bodySchema = z.object({
			email: emailSchema,
			password: passwordSchema
		});
		const { email, password } = bodySchema.parse(req.body);

		const existing = await prisma.user.findUnique({ where: { email } });
		if (existing) {
			return res.status(409).json({ error: 'EMAIL_TAKEN', message: 'Email already registered' });
		}
		const passwordHash = await bcrypt.hash(password, 12);
		const user = await prisma.user.create({
			data: { email, passwordHash }
		});
		const token = signJwt({ userId: user.id });
		res.status(201).json({ token, user: { id: user.id, email: user.email } });
	} catch (err) {
		next(err);
	}
});

router.post('/login', async (req, res, next) => {
	try {
		const bodySchema = z.object({
			email: emailSchema,
			password: z.string().min(1)
		});
		const { email, password } = bodySchema.parse(req.body);

		const user = await prisma.user.findUnique({ where: { email } });
		if (!user) {
			return res.status(401).json({ error: 'INVALID_CREDENTIALS', message: 'Invalid email or password' });
		}
		const ok = await bcrypt.compare(password, user.passwordHash);
		if (!ok) {
			return res.status(401).json({ error: 'INVALID_CREDENTIALS', message: 'Invalid email or password' });
		}
		const token = signJwt({ userId: user.id });
		res.json({ token, user: { id: user.id, email: user.email } });
	} catch (err) {
		next(err);
	}
});

router.post('/forgot', async (req, res, next) => {
	try {
		const { email } = z.object({ email: emailSchema }).parse(req.body);
		const user = await prisma.user.findUnique({ where: { email } });
		// Intentionally do not reveal whether user exists
		if (user) {
			const token = crypto.randomBytes(24).toString('hex');
			const expiry = new Date(Date.now() + 1000 * 60 * 60); // 1h
			await prisma.user.update({
				where: { id: user.id },
				data: { resetToken: token, resetTokenExpiry: expiry }
			});
			// Replace with real email service in production
			console.log(`[password reset] email=${email} token=${token}`);
		}
		res.json({ ok: true });
	} catch (err) {
		next(err);
	}
});

router.post('/reset', async (req, res, next) => {
	try {
		const { token, password } = z
			.object({
				token: z.string().min(1),
				password: passwordSchema
			})
			.parse(req.body);
		const user = await prisma.user.findFirst({
			where: {
				resetToken: token,
				resetTokenExpiry: { gt: new Date() }
			}
		});
		if (!user) {
			return res.status(400).json({ error: 'INVALID_TOKEN', message: 'Token is invalid or expired' });
		}
		const passwordHash = await bcrypt.hash(password, 12);
		await prisma.user.update({
			where: { id: user.id },
			data: { passwordHash, resetToken: null, resetTokenExpiry: null }
		});
		res.json({ ok: true });
	} catch (err) {
		next(err);
	}
});

export default router;


