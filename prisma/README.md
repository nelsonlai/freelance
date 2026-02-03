# Prisma Teaching – Complete Project (Node.js + Express + SQLite)

This project matches the 90‑minute Prisma lesson:
- Prisma schema & migrations (User–Post–Comment)
- Type‑safe CRUD, relations (select/include), cursor pagination
- Interactive transactions (`POST /posts/:id/publish`)
- Prisma Studio for quick data edits
- Express API for users, posts, comments
- Raw SQL (parameterized) example

## Quick Start

```bash
npm install
npx prisma generate
npm run prisma:migrate
npm run seed
npm run dev
# open http://localhost:3000
# Studio: npm run prisma:studio
```

### Example Requests (HTTP file friendly)

```
GET http://localhost:3000/health

### Users
GET http://localhost:3000/users
GET http://localhost:3000/users/1
POST http://localhost:3000/users
Content-Type: application/json

{ "email": "carol@example.com", "name": "Carol" }

### Posts
GET http://localhost:3000/posts?take=5&published=true
GET http://localhost:3000/posts/1
POST http://localhost:3000/posts
Content-Type: application/json

{ "title": "Intro", "content": "hi", "authorEmail": "carol@example.com" }

PATCH http://localhost:3000/posts/1
Content-Type: application/json

{ "title": "New Title" }

POST http://localhost:3000/posts/1/publish

### Comments
GET http://localhost:3000/posts/1/comments
POST http://localhost:3000/posts/1/comments
Content-Type: application/json

{ "authorEmail": "carol@example.com", "content": "Nice!" }

### Stats
GET http://localhost:3000/stats/post-count?published=true
```

## Switch to Postgres/MySQL
1) In `prisma/schema.prisma`, change `provider` to `"postgresql"` or `"mysql"`  
2) Update `.env` `DATABASE_URL`  
3) Re‑run:
```bash
npx prisma generate
npx prisma migrate dev --name init
```
Use a pooler (PgBouncer) or Prisma Accelerate for serverless/high concurrency setups.
