import express from 'express';
import cors from 'cors';
import morgan from 'morgan';
import authRouter from '../routes/auth.js';

const app = express();

app.use(cors());
app.use(express.json());
app.use(morgan('dev'));

app.get('/health', (_req, res) => {
	res.json({ ok: true });
});

app.use('/auth', authRouter);

// Centralized error handler
// eslint-disable-next-line @typescript-eslint/no-unused-vars
app.use((err: any, _req: express.Request, res: express.Response, _next: express.NextFunction) => {
	console.error(err);
	const status = err.status || 500;
	res.status(status).json({
		error: err.code || 'INTERNAL_SERVER_ERROR',
		message: err.message || 'Something went wrong'
	});
});

export default app;


