# Run Guide: User Form (Next.js + Express + MySQL)

This guide explains how to run the full stack: **frontend** (Next.js form), **backend** (Express API), and **database** (MySQL). The form collects first name, last name, and email and saves them to MySQL.

---

## Prerequisites

- **Node.js** (v18 or newer) – [nodejs.org](https://nodejs.org)
- **MySQL** (5.7+ or 8.x) – [mysql.com](https://dev.mysql.com/downloads/) or install via Homebrew (`brew install mysql`), etc.
- **npm** (comes with Node.js)

---

## 1. Set up MySQL

### 1.1 Start MySQL

Make sure the MySQL server is running.

- **macOS (Homebrew):** `brew services start mysql`
- **Windows:** Start MySQL from Services or MySQL installer.
- **Linux:** `sudo systemctl start mysql` (or your distro’s equivalent).

### 1.2 Create database and table

From the project root:

```bash
# Option A: Run the schema file (you will be prompted for MySQL password)
mysql -u root -p < backend/schema.sql

# Option B: Log in and paste the SQL
mysql -u root -p
```

Then in the MySQL shell:

```sql
CREATE DATABASE IF NOT EXISTS myapp;
USE myapp;

CREATE TABLE IF NOT EXISTS users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  first_name VARCHAR(100) NOT NULL,
  last_name VARCHAR(100) NOT NULL,
  email VARCHAR(255) NOT NULL UNIQUE,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

---

## 2. Backend (Express + MySQL)

### 2.1 Install dependencies

```bash
cd backend
npm install
```

### 2.2 Configure environment (optional)

Copy the example env file and edit if your MySQL settings differ from defaults:

```bash
cp .env.example .env
```

Edit `.env` if needed:

- `MYSQL_HOST` – default `localhost`
- `MYSQL_USER` – default `root`
- `MYSQL_PASSWORD` – your MySQL password (empty if none)
- `MYSQL_DB` – default `myapp`
- `PORT` – default `4000`

### 2.3 Start the backend

```bash
npm start
```

You should see: `Backend running at http://localhost:4000`

Leave this terminal open. The API serves:

- `POST /api/users` – create user (first name, last name, email)
- `GET /api/users` – list users
- `GET /api/health` – health check

---

## 3. Frontend (Next.js)

Open a **new terminal** (backend keeps running in the first).

### 3.1 Install dependencies

```bash
cd frontend
npm install
```

### 3.2 Configure API URL (optional)

The frontend calls the backend at `http://localhost:4000` by default. To override:

```bash
cp .env.local.example .env.local
```

Edit `.env.local`:

```env
NEXT_PUBLIC_API_URL=http://localhost:4000
```

Change the URL only if your backend runs on a different host/port.

### 3.3 Start the frontend

```bash
npm run dev
```

You should see: `Ready on http://localhost:3000`

### 3.4 Use the form

1. Open a browser and go to **http://localhost:3000**
2. Fill in **First name**, **Last name**, and **Email**
3. Click **Submit**
4. You should see “Saved successfully!” and the form clear. The user is stored in MySQL.

---

## 4. Quick reference: run order

| Step | Where        | Command              |
|------|--------------|----------------------|
| 1    | Project root | Create DB/table (see §1) |
| 2    | `backend/`   | `npm install` then `npm start` |
| 3    | `frontend/`  | `npm install` then `npm run dev` |
| 4    | Browser      | Open http://localhost:3000 |

---

## 5. Verify it works

- **Frontend:** http://localhost:3000 – form with first name, last name, email.
- **Backend health:** http://localhost:4000/api/health – should return `{"ok":true}`.
- **List users:** http://localhost:4000/api/users – after submitting the form, you should see the new user in the JSON array.

---

## 6. Troubleshooting

| Problem | What to check |
|--------|----------------|
| “Network error. Is the backend running?” | Backend must be running on port 4000. Start it with `cd backend && npm start`. |
| “Email already exists” | The email is unique; use a different email or delete the row in MySQL. |
| MySQL connection refused | MySQL server must be running. Check host/port/user/password in `.env`. |
| “Cannot find module” in backend | Run `npm install` in `backend/`. |
| Frontend build/run errors | Run `npm install` in `frontend/`. Ensure Node.js is v18+. |

---

## 7. Project layout

```
cursor_ai/
├── RUN_GUIDE.md           ← this file
├── FRONTEND_BACKEND_DESIGN.md
├── backend/
│   ├── package.json
│   ├── server.js          ← Express API
│   ├── schema.sql         ← MySQL DB + table
│   └── .env.example
└── frontend/
    ├── package.json
    ├── next.config.js
    ├── app/
    │   ├── layout.tsx
    │   ├── page.tsx       ← User form
    │   └── globals.css
    └── .env.local.example
```

For design details and request flow, see **FRONTEND_BACKEND_DESIGN.md**.
