## Ricky Backend (Express + Prisma)

Backend API for auth flows to support your login screen.

### Tech
- Express.js
- Prisma (SQLite by default)
- JWT auth, bcrypt password hashing

### Setup
1. Create `.env` in the project root:

```
DATABASE_URL="file:./dev.db"
JWT_SECRET="replace-with-a-strong-secret"
PORT=4000
```

2. Install deps and generate Prisma client:

```bash
npm i
npx prisma generate
npx prisma migrate dev --name init
```

3. Run the dev server:

```bash
npm run dev
```

API base: `http://localhost:4000`

### Endpoints
- POST `/auth/register` { email, password }
- POST `/auth/login` { email, password }
- POST `/auth/forgot` { email }  (logs reset token to console)
- POST `/auth/reset` { token, password }
- GET `/health`

Auth responses include `token` (JWT). Send it as `Authorization: Bearer <token>` for protected routes (if you add any).


