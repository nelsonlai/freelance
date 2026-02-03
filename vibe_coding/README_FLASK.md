# Vibe Coding – Flask app (Login, Blog, Bot Chat)

Flask backend + frontend with **SQLAlchemy** (ORM) and **MySQL**, featuring login, blog, and bot chat.

## Tech stack

- **Backend + frontend:** Python Flask
- **ORM:** SQLAlchemy (Flask-SQLAlchemy)
- **Database:** MySQL (driver: PyMySQL)
- **Auth:** Flask-Login (sessions, login/register/logout)

## Project layout

```
vibe_coding/
├── app/
│   ├── __init__.py          # App factory, blueprints, db.create_all
│   ├── extensions.py        # db, login_manager
│   ├── config.py            # (at project root)
│   ├── models/
│   │   ├── user.py          # User (auth)
│   │   ├── post.py          # Post (blog)
│   │   └── chat_message.py  # ChatMessage (botchat)
│   ├── blueprints/
│   │   ├── auth/            # /auth/login, register, logout
│   │   ├── blog/            # /blog/ list, create, view, edit, delete
│   │   └── botchat/         # /botchat/ chat UI + /send JSON API
│   ├── templates/
│   │   └── base.html        # Shared layout, nav, flashes
│   └── static/
│       └── css/style.css    # Base styles
├── config.py                # SECRET_KEY, DATABASE_URL
├── requirements.txt
├── run.py                   # Development server
├── .env.example
└── README_FLASK.md
```

## Setup

1. **Python 3.10+** and **MySQL** installed.

2. Create a MySQL database:
   ```sql
   CREATE DATABASE vibe_coding CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
   ```

3. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```

4. Copy env and set your DB URL and secret:
   ```bash
   cp .env.example .env
   # Edit .env: DATABASE_URL (MySQL), SECRET_KEY
   # Optional: use SQLite for local try-out: DATABASE_URL=sqlite:///app.db
   ```

5. Run the app (tables are created on first request via `db.create_all()`):
   ```bash
   python run.py
   ```
   Open http://localhost:5000

## Routes

| Area   | Routes |
|--------|--------|
| **Auth**   | `/auth/login`, `/auth/register`, `/auth/logout` |
| **Blog**   | `/blog/` (list), `/blog/create`, `/blog/<id>`, `/blog/<id>/edit`, `/blog/<id>/delete` (POST) |
| **Bot Chat** | `/botchat/` (chat UI), `/botchat/send` (POST JSON `{ "message": "..." }`) |
| **Home**   | `/` → redirects to `/blog/` |

## Features

- **Login:** Register, login, logout; session-based with Flask-Login.
- **Blog:** List (paginated), view, create, edit, delete (author only).
- **Bot Chat:** Per-user chat history in MySQL; simple rule-based bot; extend `get_bot_reply()` in `app/blueprints/botchat/routes.py` or plug in an API/LLM.

## Config

- `SECRET_KEY` – set in production (e.g. from `.env`).
- `DATABASE_URL` – e.g. `mysql+pymysql://user:pass@host:3306/dbname`.

## Production

- Set `SECRET_KEY` and `DATABASE_URL` in environment.
- Run with a WSGI server, e.g.:
  ```bash
  gunicorn -w 4 -b 0.0.0.0:5000 "app:create_app()"
  ```
- For production DB migrations, consider **Flask-Migrate** (Alembic).
