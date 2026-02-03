# Module 4: Node.js Backend Development

Node.js lets you build backend services in **JavaScript** (or **TypeScript**) using the same language as the browser. **Express** is the most common web framework for REST APIs.

---

## 1. Why Node.js for Backend?

- **Single language**: JavaScript/TypeScript for frontend and backend.
- **Non-blocking I/O**: Event loop and async I/O suit APIs and DB-heavy workloads.
- **Ecosystem**: npm has many packages (Express, Prisma, Zod, etc.).
- **Fast to prototype**: Minimal setup for HTTP servers and APIs.

---

## 2. Prerequisites

- **Node.js** 18+ (LTS recommended): https://nodejs.org  
- **npm** (comes with Node) or **pnpm** / **yarn**

---

## 3. Project Setup

```bash
mkdir my-api && cd my-api
npm init -y
npm install express
```

Optional TypeScript:

```bash
npm install -D typescript @types/node @types/express tsx
npx tsc --init
```

---

## 4. Minimal Express App

```javascript
// index.js (CommonJS)
const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

app.get('/', (req, res) => {
  res.json({ message: 'Hello World' });
});

app.get('/health', (req, res) => {
  res.json({ status: 'ok', now: new Date().toISOString() });
});

app.listen(PORT, () => {
  console.log(`Server listening on http://localhost:${PORT}`);
});
```

Run: `node index.js`  

With TypeScript (ESM):

```typescript
// src/index.ts
import express from 'express';

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

app.get('/health', (req, res) => {
  res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

app.listen(PORT, () => {
  console.log(`Server on http://localhost:${PORT}`);
});
```

Run: `npx tsx src/index.ts` or `npm run dev` with `"dev": "tsx watch src/index.ts"`.

---

## 5. Routing

```javascript
const express = require('express');
const router = express.Router();

// GET /users
router.get('/', async (req, res, next) => {
  try {
    const users = await getUsers();  // your logic
    res.json({ data: users });
  } catch (err) {
    next(err);
  }
});

// GET /users/:id
router.get('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    const user = await getUser(id);
    if (!user) return res.status(404).json({ error: { message: 'User not found' } });
    res.json({ data: user });
  } catch (err) {
    next(err);
  }
});

// POST /users
router.post('/', async (req, res, next) => {
  try {
    const { email, name } = req.body;
    const user = await createUser({ email, name });
    res.status(201).json({ data: user });
  } catch (err) {
    next(err);
  }
});

// PATCH /users/:id
router.patch('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    const { email, name } = req.body;
    const user = await updateUser(id, { email, name });
    res.json({ data: user });
  } catch (err) {
    next(err);
  }
});

// DELETE /users/:id
router.delete('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    await deleteUser(id);
    res.status(204).send();
  } catch (err) {
    next(err);
  }
});

module.exports = router;
```

Mount in main app:

```javascript
const express = require('express');
const usersRouter = require('./routes/users');

const app = express();
app.use(express.json());
app.use('/users', usersRouter);
```

---

## 6. Request / Response

- **Path params**: `req.params.id` (string; parse to number if needed).
- **Query**: `req.query.page`, `req.query.limit`.
- **Body**: `req.body` (after `express.json()`).
- **Headers**: `req.headers.authorization`.
- **Response**: `res.json(obj)`, `res.status(201).json(obj)`, `res.status(204).send()`.

---

## 7. Error Handling

Central error handler (place **last**):

```javascript
function errorHandler(err, req, res, next) {
  console.error(err);
  const status = err.statusCode || 500;
  res.status(status).json({
    error: {
      code: err.code || 'INTERNAL_ERROR',
      message: err.message || 'Internal server error',
    },
  });
}

app.use(errorHandler);
```

In routes, pass errors to `next(err)` so the central handler runs.

---

## 8. Middleware

- **Order matters**: Middleware runs in sequence.
- **Body parsing**: `app.use(express.json())` for JSON bodies.
- **CORS**: `npm install cors` then `app.use(cors())` or `cors({ origin: 'https://...' })`.
- **Security**: `helmet()` for secure headers.
- **Rate limiting**: `express-rate-limit` to limit requests per IP.

---

## 9. Validation

- **Manual**: Check `req.body` and return 400 if invalid.
- **Zod** (TypeScript-friendly):

  ```javascript
  const { z } = require('zod');
  const CreateUserSchema = z.object({ email: z.string().email(), name: z.string().optional() });
  const result = CreateUserSchema.safeParse(req.body);
  if (!result.success) return res.status(400).json({ error: result.error.flatten() });
  const { email, name } = result.data;
  ```

---

## 10. Database (Prisma Example)

- **Prisma**: ORM for PostgreSQL, MySQL, SQLite.
- Init: `npx prisma init` → edit `prisma/schema.prisma`, then `npx prisma generate` and `npx prisma migrate dev`.
- In code: `const { prisma } = require('./prisma');` then `prisma.user.findMany()`, `prisma.user.create()`, etc.

See `../src/` for an Express + Prisma example (users, posts, comments).

---

## 11. Project Structure (Typical)

```
my-api/
  src/
    index.js          # or index.ts — app entry, listen()
    routes/
      users.js
      posts.js
    middleware/
      errorHandler.js
      auth.js
    prisma.js         # Prisma client singleton
  prisma/
    schema.prisma
  package.json
  .env
```

---

## 12. Environment Variables

- Use **dotenv**: `require('dotenv').config();` at top of entry file.
- Store `PORT`, `DATABASE_URL`, `JWT_SECRET`, etc. in `.env` (never commit secrets).

---

## Lesson Plan

1. Hello World with Express.
2. Routes: GET, POST, PATCH, DELETE.
3. Routers and mounting.
4. Request body, params, query.
5. Central error handler.
6. Middleware (CORS, helmet, rate limit).
7. Validation (Zod or similar).
8. Database with Prisma (or another ORM).

---

## Example in This Repo

- **Express + Prisma**: `../src/` — `index.js`, `routes/users.js`, `routes/posts.js`, `routes/comments.js`, `middleware/errorHandler.js`, `prisma.js`.

---

## Next

- [01_restful_api](../01_restful_api/) — REST  
- [05_nestjs](../05_nestjs/) — Nest.js (structured TypeScript backend)  
- [06_sql](../06_sql/) / [07_nosql](../07_nosql/) — Databases  
