# Module 2: Python FastAPI

FastAPI is a modern, high-performance Python web framework for building APIs. It uses **type hints** and **Pydantic** for validation and automatically generates **OpenAPI (Swagger)** documentation.

---

## 1. Why FastAPI?

- **Fast**: Built on Starlette (ASGI); supports async/await.
- **Type-safe**: Uses Python type hints and Pydantic for request/response validation.
- **Auto docs**: Swagger UI at `/docs`, ReDoc at `/redoc`.
- **Standards**: OpenAPI 3.0, JSON Schema.
- **Dependency injection**: Built-in system for shared logic (DB, auth).

---

## 2. Setup

```bash
python -m venv venv
source venv/bin/activate   # Windows: venv\Scripts\activate
pip install fastapi uvicorn[standard]
```

---

## 3. Minimal App

```python
from fastapi import FastAPI

app = FastAPI(title="My API", version="1.0.0")

@app.get("/")
async def root():
    return {"message": "Hello World"}

@app.get("/health")
async def health():
    return {"status": "ok"}
```

Run:

```bash
uvicorn main:app --reload
```

- **Swagger UI**: http://127.0.0.1:8000/docs  
- **ReDoc**: http://127.0.0.1:8000/redoc  

---

## 4. Path and Query Parameters

```python
from fastapi import FastAPI, Query

app = FastAPI()

# Path parameter
@app.get("/users/{user_id}")
async def get_user(user_id: int):
    return {"user_id": user_id}

# Query parameters (optional with defaults)
@app.get("/items")
async def list_items(
    skip: int = 0,
    limit: int = Query(10, le=100),
    q: str | None = None
):
    return {"skip": skip, "limit": limit, "q": q}
```

- Path params are required; type conversion is automatic (e.g. `user_id: int`).
- Query params use `Query()` for validation (e.g. `le=100`).

---

## 5. Request Body with Pydantic

```python
from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

class ItemCreate(BaseModel):
    name: str
    price: float
    description: str | None = None

class Item(ItemCreate):
    id: int

@app.post("/items", response_model=Item, status_code=201)
async def create_item(item: ItemCreate):
    # item is validated and typed
    new_item = Item(id=1, **item.model_dump())
    return new_item
```

- **Pydantic** validates the JSON body; invalid data returns 422.
- `response_model=Item` shapes and documents the response.

---

## 6. Status Codes and Exceptions

```python
from fastapi import FastAPI, HTTPException

app = FastAPI()

@app.get("/users/{user_id}")
async def get_user(user_id: int):
    user = find_user(user_id)  # your logic
    if not user:
        raise HTTPException(status_code=404, detail="User not found")
    return user
```

- Use `HTTPException(status_code=..., detail="...")` for API errors.
- Return appropriate status codes (201 for create, 204 for delete, etc.).

---

## 7. Dependency Injection

```python
from fastapi import FastAPI, Depends

app = FastAPI()

def get_db():
    db = ...  # create connection
    try:
        yield db
    finally:
        db.close()

@app.get("/users")
async def list_users(db = Depends(get_db)):
    return db.query_users()
```

- Use `Depends(get_db)` to inject shared dependencies (DB, auth).
- Use `yield` for setup/teardown (e.g. close DB).

---

## 8. Async vs Sync

- Prefer **async** for I/O-bound work (DB, HTTP calls):

  ```python
  @app.get("/users")
  async def list_users():
      users = await db.fetch_users()  # async DB
      return users
  ```

- **Sync** is fine for CPU-bound or simple logic; FastAPI runs it in a thread pool.

---

## 9. Project Structure (Typical)

```
my_api/
  app/
    __init__.py
    main.py          # FastAPI app, routers
    routers/
      users.py
      items.py
    models/          # Pydantic models
    schemas/
    db.py            # DB connection, session
  requirements.txt
```

Mount routers:

```python
from fastapi import FastAPI
from app.routers import users, items

app = FastAPI()
app.include_router(users.router, prefix="/users", tags=["users"])
app.include_router(items.router, prefix="/items", tags=["items"])
```

---

## 10. Security (Basic)

- **API Key**: Use `APIKeyHeader` or `APIKeyQuery` with `Depends()`.
- **OAuth2 / JWT**: Use `OAuth2PasswordBearer` and verify the token in a dependency; raise `HTTPException(401)` if invalid.

---

## 11. CORS

```python
from fastapi.middleware.cors import CORSMiddleware

app.add_middleware(
    CORSMiddleware,
    allow_origins=["https://myfrontend.com"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
```

---

## 12. Running in Production

```bash
uvicorn app.main:app --host 0.0.0.0 --port 8000 --workers 4
```

- Use **HTTPS** (reverse proxy: nginx, Traefik).
- Set `workers` based on CPU; each worker runs the app.

---

## Lesson Plan

1. Hello World and `/docs`.
2. Path and query parameters.
3. Request body and Pydantic models.
4. CRUD (create, read, update, delete) with in-memory or DB.
5. Dependency injection (DB, auth).
6. Error handling and status codes.
7. Middleware (CORS, logging).

---

## Example in This Repo

- **FastAPI curriculum + sample app**: `../python_backend/curriculum/fastapi/`  
  - Run: `cd ../python_backend/curriculum/fastapi && pip install -r requirements.txt && uvicorn app.main:app --reload`  
  - Open: http://127.0.0.1:8000/docs  

---

## Next

- [01_restful_api](../01_restful_api/) — REST concepts  
- [03_python_flask](../03_python_flask/) — Flask (APIs and server-rendered pages)  
- [06_sql](../06_sql/) / [07_nosql](../07_nosql/) — Databases  
