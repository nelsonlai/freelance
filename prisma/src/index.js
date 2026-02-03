/**
 * Entry point: Express server with Prisma-backed routes.
 * - Loads env via dotenv
 * - Health endpoint
 * - Domain routes (users, posts, comments)
 * - Raw SQL stats example
 * - Centralized error handler
 */
require('dotenv').config();
const express = require('express');
const app = express();
const { prisma } = require('./prisma');
const { errorHandler } = require('./middleware/errorHandler');

app.use(express.json());

// Root path
app.get('/', (req, res) => {
  res.json({
    message: 'Welcome to the API',
    endpoints: {
      health: '/health',
      users: '/users',
      posts: '/posts',
      comments: '/comments',
      stats: '/stats/post-count?published=true'
    }
  });
});

// Health check
app.get('/health', async (req, res) => {
  const now = new Date().toISOString();
  res.json({ ok: true, now });
});

// Domain routes
app.use('/users', require('./routes/users'));
app.use('/posts', require('./routes/posts'));
app.use('/comments', require('./routes/comments'));

// Raw SQL (parameterized) example
// GET /stats/post-count?published=true
app.get('/stats/post-count', async (req, res, next) => {
  try {
    const published = req.query.published === 'true';
    const rows = await prisma.$queryRaw`SELECT COUNT(*) AS c FROM Post WHERE published = ${published}`;
    const count = Number(rows?.[0]?.c || 0);
    res.json({ data: { published, count } });
  } catch (err) { next(err); }
});

// Error handler must be last
app.use(errorHandler);

const PORT = Number(process.env.PORT || 3000);
app.listen(PORT, () => {
  console.log(`[server] Listening on http://localhost:${PORT}`);
  console.log(`[server] Try: GET /users  |  GET /posts  |  GET /comments`);
});
