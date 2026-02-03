# Frontend–Backend Design Guide

How to design a **Next.js frontend** that collects first name, last name, and email, and how a **Node.js + Express.js backend** receives those requests and stores them in a **MySQL** database.

---

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────────────────────┐
│  User fills form (first name, last name, email)                             │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│  FRONTEND (Next.js)                                                         │
│  - Form component with inputs                                               │
│  - On submit: sends HTTP POST with JSON body to backend API                 │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                          HTTP POST /api/users (or similar)
                          Body: { firstName, lastName, email }
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│  BACKEND (Node.js + Express.js)                                             │
│  - Express server listens for requests                                      │
│  - Route handler receives req.body (firstName, lastName, email)              │
│  - Validates input, then talks to MySQL                                     │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│  DATABASE (MySQL)                                                           │
│  - Table: e.g. users (id, first_name, last_name, email, created_at)          │
│  - Express uses a MySQL client (mysql2) to run INSERT / SELECT               │
└─────────────────────────────────────────────────────────────────────────────┘
```

**Summary:** Frontend sends data → Backend receives it in `req.body` → Backend saves to MySQL.

---

## 1. Backend (Node.js + Express.js + MySQL)

### 1.1 Stack

- **Node.js** – runtime
- **Express.js** – web framework (handles HTTP, routes, `req`/`res`)
- **MySQL** – database; Express connects via a driver (e.g. `mysql2`)

Express does not “are” the database; it runs your API and uses a MySQL client to talk to the DB.

### 1.2 Backend: How It Receives Frontend Requests

1. Frontend sends an **HTTP request** (e.g. `POST https://your-api.com/api/users`) with a **JSON body**.
2. Express uses **middleware** to parse that body into a JavaScript object.
3. Your **route handler** receives that object as `req.body`.

**Important:** Use `express.json()` so Express can read JSON from the request body.

```javascript
const express = require('express');
const app = express();

// Required: parse JSON request body into req.body
app.use(express.json());

// POST /api/users – frontend will send { firstName, lastName, email }
app.post('/api/users', (req, res) => {
  // Backend receives frontend data here
  const { firstName, lastName, email } = req.body;

  // Validate, then save to MySQL (see below)
  if (!firstName || !lastName || !email) {
    return res.status(400).json({ error: 'Missing required fields' });
  }

  // ... insert into MySQL and respond
});
```

So: **frontend sends JSON → Express parses it → you read `req.body` in the route.**

### 1.3 Backend Project Setup (minimal)

```bash
mkdir backend && cd backend
npm init -y
npm install express mysql2 cors
```

- **express** – server and routes  
- **mysql2** – MySQL driver for Node  
- **cors** – allow requests from your Next.js origin (e.g. `http://localhost:3000`)

### 1.4 MySQL Table (example)

```sql
CREATE DATABASE IF NOT EXISTS myapp;
USE myapp;

CREATE TABLE users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  first_name VARCHAR(100) NOT NULL,
  last_name VARCHAR(100) NOT NULL,
  email VARCHAR(255) NOT NULL UNIQUE,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### 1.5 Backend: Full Example (Express + MySQL)

```javascript
// backend/server.js (or index.js)
const express = require('express');
const mysql = require('mysql2/promise');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 4000;

// Middleware: parse JSON body so req.body is available
app.use(express.json());
// Allow frontend (Next.js) to call this API
app.use(cors({ origin: 'http://localhost:3000' }));

// MySQL connection pool
const pool = mysql.createPool({
  host: process.env.MYSQL_HOST || 'localhost',
  user: process.env.MYSQL_USER || 'root',
  password: process.env.MYSQL_PASSWORD || '',
  database: process.env.MYSQL_DB || 'myapp',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});

// POST /api/users – how backend receives frontend request
app.post('/api/users', async (req, res) => {
  try {
    // 1. Backend receives data from frontend here
    const { firstName, lastName, email } = req.body;

    if (!firstName || !lastName || !email) {
      return res.status(400).json({
        success: false,
        error: 'First name, last name, and email are required',
      });
    }

    // 2. Optional: validate email format, etc.

    // 3. Save to MySQL
    const [result] = await pool.execute(
      'INSERT INTO users (first_name, last_name, email) VALUES (?, ?, ?)',
      [firstName.trim(), lastName.trim(), email.trim()]
    );

    res.status(201).json({
      success: true,
      message: 'User created',
      id: result.insertId,
    });
  } catch (err) {
    console.error(err);
    if (err.code === 'ER_DUP_ENTRY') {
      return res.status(409).json({ success: false, error: 'Email already exists' });
    }
    res.status(500).json({ success: false, error: 'Server error' });
  }
});

// Optional: GET users (for testing or listing)
app.get('/api/users', async (req, res) => {
  try {
    const [rows] = await pool.execute(
      'SELECT id, first_name, last_name, email, created_at FROM users ORDER BY created_at DESC'
    );
    res.json({ success: true, data: rows });
  } catch (err) {
    console.error(err);
    res.status(500).json({ success: false, error: 'Server error' });
  }
});

app.listen(PORT, () => {
  console.log(`Backend running at http://localhost:${PORT}`);
});
```

**How the backend receives the frontend request:**

| Step | What happens |
|------|-------------------------------|
| 1 | Frontend sends `POST /api/users` with body `{ "firstName": "...", "lastName": "...", "email": "..." }`. |
| 2 | `express.json()` parses the body and puts it in `req.body`. |
| 3 | Your handler reads `req.body.firstName`, `req.body.lastName`, `req.body.email`. |
| 4 | You validate, then run `INSERT` via `mysql2` and send a JSON response. |

---

## 2. Frontend (Next.js)

### 2.1 Stack

- **Next.js** – React framework; you can use App Router or Pages Router.
- Form with **first name**, **last name**, **email**.
- On submit: send a **POST** request to the backend with that data as JSON.

### 2.2 How the Frontend Sends Data to the Backend

1. User fills the form and clicks Submit.
2. You prevent the default form submit and read values from state or refs.
3. You call `fetch` (or axios) to the backend URL with:
   - **Method:** `POST`
   - **Headers:** `Content-Type: application/json`
   - **Body:** `JSON.stringify({ firstName, lastName, email })`
4. Backend responds with JSON; you show success or error.

### 2.3 Frontend Project Setup

```bash
npx create-next-app@latest frontend
# Choose TypeScript, ESLint, Tailwind, etc. as you prefer
cd frontend
```

No extra packages required for a simple `fetch`; optionally add `axios` if you prefer.

### 2.4 Frontend: Form Component Example (App Router)

**File: `app/page.tsx` (or `app/contact/page.tsx`)**

```tsx
'use client';

import { useState } from 'react';

const API_URL = process.env.NEXT_PUBLIC_API_URL || 'http://localhost:4000';

export default function UserForm() {
  const [firstName, setFirstName] = useState('');
  const [lastName, setLastName] = useState('');
  const [email, setEmail] = useState('');
  const [status, setStatus] = useState<'idle' | 'loading' | 'success' | 'error'>('idle');
  const [message, setMessage] = useState('');

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setStatus('loading');
    setMessage('');

    try {
      // Send request to backend – backend will receive this as req.body
      const res = await fetch(`${API_URL}/api/users`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          firstName: firstName.trim(),
          lastName: lastName.trim(),
          email: email.trim(),
        }),
      });

      const data = await res.json();

      if (!res.ok) {
        setStatus('error');
        setMessage(data.error || 'Something went wrong');
        return;
      }

      setStatus('success');
      setMessage('Saved successfully!');
      setFirstName('');
      setLastName('');
      setEmail('');
    } catch (err) {
      setStatus('error');
      setMessage('Network error. Is the backend running?');
    }
  };

  return (
    <div className="max-w-md mx-auto p-6">
      <h1 className="text-xl font-semibold mb-4">User form</h1>
      <form onSubmit={handleSubmit} className="space-y-4">
        <div>
          <label htmlFor="firstName" className="block text-sm font-medium mb-1">
            First name
          </label>
          <input
            id="firstName"
            type="text"
            value={firstName}
            onChange={(e) => setFirstName(e.target.value)}
            required
            className="w-full border rounded px-3 py-2"
          />
        </div>
        <div>
          <label htmlFor="lastName" className="block text-sm font-medium mb-1">
            Last name
          </label>
          <input
            id="lastName"
            type="text"
            value={lastName}
            onChange={(e) => setLastName(e.target.value)}
            required
            className="w-full border rounded px-3 py-2"
          />
        </div>
        <div>
          <label htmlFor="email" className="block text-sm font-medium mb-1">
            Email
          </label>
          <input
            id="email"
            type="email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            required
            className="w-full border rounded px-3 py-2"
          />
        </div>
        <button
          type="submit"
          disabled={status === 'loading'}
          className="w-full bg-blue-600 text-white py-2 rounded disabled:opacity-50"
        >
          {status === 'loading' ? 'Sending…' : 'Submit'}
        </button>
      </form>
      {message && (
        <p className={`mt-4 ${status === 'error' ? 'text-red-600' : 'text-green-600'}`}>
          {message}
        </p>
      )}
    </div>
  );
}
```

**Environment variable (optional):**  
Create `.env.local` in the Next.js project:

```env
NEXT_PUBLIC_API_URL=http://localhost:4000
```

So: **frontend collects firstName, lastName, email → sends them in the request body as JSON → backend receives them in `req.body`.**

---

## 3. End-to-End Request Flow

| Step | Actor | Action |
|------|--------|--------|
| 1 | User | Fills first name, last name, email and clicks Submit. |
| 2 | Next.js | `handleSubmit` runs; calls `fetch(POST, body: JSON.stringify({ firstName, lastName, email }))`. |
| 3 | Network | HTTP POST to `http://localhost:4000/api/users` with JSON body. |
| 4 | Express | `express.json()` parses body → `req.body = { firstName, lastName, email }`. |
| 5 | Route | Handler reads `req.body`, validates, runs `INSERT` via `mysql2`. |
| 6 | MySQL | Row inserted into `users` table. |
| 7 | Express | Sends `res.status(201).json({ success: true, ... })`. |
| 8 | Next.js | `fetch` resolves; you set success/error state and optionally clear the form. |

---

## 4. Checklist

**Backend (Node.js + Express + MySQL):**

- [ ] `express.json()` so `req.body` is populated.
- [ ] `cors()` so Next.js (e.g. `localhost:3000`) can call the API.
- [ ] POST route (e.g. `/api/users`) that reads `req.body.firstName`, `req.body.lastName`, `req.body.email`.
- [ ] Validate and then INSERT using `mysql2` (or another MySQL client).
- [ ] Respond with JSON (e.g. 201 + `{ success: true }` or 400/409/500 + error message).

**Frontend (Next.js):**

- [ ] Form with controlled inputs for first name, last name, email.
- [ ] On submit: `fetch(backendUrl, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ firstName, lastName, email }) })`.
- [ ] Handle response and show success/error; optionally reset form.

**Database:**

- [ ] MySQL server running; table created (e.g. `users` with `first_name`, `last_name`, `email`).
- [ ] Backend connection config (host, user, password, database) correct.

---

## 5. Running Everything

1. **MySQL:** Start MySQL and create the database/table (see SQL above).
2. **Backend:** `cd backend && node server.js` (or `npm start`). Should listen on e.g. port 4000.
3. **Frontend:** `cd frontend && npm run dev`. Should run on e.g. port 3000.
4. Open `http://localhost:3000`, submit the form; backend should log the request and insert into MySQL.

This markdown file describes how to design the frontend (form + request) and how the backend receives and processes those requests with Express and MySQL.
