# Backend Tech Stack — Quick Reference

One-page reference for REST, Python (FastAPI/Flask), Node.js/Nest.js, and SQL/NoSQL.

---

## REST

| Method   | Use      | Idempotent |
|----------|----------|------------|
| GET      | Read     | Yes        |
| POST     | Create   | No         |
| PUT      | Replace  | Yes        |
| PATCH    | Partial  | No*        |
| DELETE   | Delete   | Yes        |

**Status**: 200 OK, 201 Created, 204 No Content, 400 Bad Request, 401 Unauthorized, 403 Forbidden, 404 Not Found, 500 Internal Server Error.

**URLs**: Nouns, plurals (`/users`), sub-resources (`/users/1/orders`), query for filter/pagination (`?page=2&limit=20`).

---

## Python FastAPI

```bash
pip install fastapi uvicorn[standard]
uvicorn main:app --reload
```

- **Docs**: `/docs` (Swagger), `/redoc`.
- **Params**: Path `user_id: int`, Query `skip: int = 0`, Body Pydantic model.
- **Errors**: `raise HTTPException(status_code=404, detail="Not found")`.
- **DI**: `Depends(get_db)`.

---

## Python Flask

```bash
pip install flask
python app.py
```

- **Route**: `@app.route("/users/<int:id>", methods=["GET","POST"])`.
- **Request**: `request.args`, `request.get_json()`, `request.form`.
- **Response**: `return jsonify({...}), 201`.
- **Modular**: Blueprints, `app.register_blueprint(bp)`.

---

## Node.js (Express)

```bash
npm install express
node index.js
```

- **Route**: `app.get/post/patch/delete(path, handler)`.
- **Params**: `req.params.id`, `req.query`, `req.body` (after `express.json()`).
- **Response**: `res.json(obj)`, `res.status(201).json(obj)`, `res.status(204).send()`.
- **Errors**: `next(err)` → central `errorHandler(err, req, res, next)`.
- **Modular**: `app.use('/users', usersRouter)`.

---

## Nest.js

```bash
nest new my-api
npm run start:dev
```

- **Structure**: Module → Controller (HTTP) + Service (logic).
- **Route**: `@Controller('users')`, `@Get()`, `@Post()`, `@Body()`, `@Param('id', ParseIntPipe)`.
- **Validation**: DTOs + `class-validator`, `ValidationPipe`.
- **Errors**: `throw new NotFoundException('...')`.
- **DI**: Constructor inject `UsersService`.

---

## SQL (Backend usage)

- **Python**: SQLAlchemy (engine, session, models, `text()` for raw).
- **Node**: Prisma (`prisma.user.findMany()`, `prisma.user.create()`, `$queryRaw`).
- **Rules**: Parameterized queries only; use migrations; index hot columns.

---

## NoSQL (Backend usage)

- **MongoDB**: Document store; PyMongo/Motor (Python), mongodb driver/Mongoose (Node).
- **Redis**: Key-value/cache; redis-py (Python), ioredis/node-redis (Node); use TTL for cache/session.

---

## Module Index

| # | Topic        | Path            |
|---|--------------|-----------------|
| 1 | RESTful API  | [01_restful_api/](01_restful_api/) |
| 2 | FastAPI      | [02_python_fastapi/](02_python_fastapi/) |
| 3 | Flask        | [03_python_flask/](03_python_flask/) |
| 4 | Node.js      | [04_nodejs/](04_nodejs/) |
| 5 | Nest.js      | [05_nestjs/](05_nestjs/) |
| 6 | SQL          | [06_sql/](06_sql/) |
| 7 | NoSQL        | [07_nosql/](07_nosql/) |

See [README.md](README.md) for full overview and learning path.
