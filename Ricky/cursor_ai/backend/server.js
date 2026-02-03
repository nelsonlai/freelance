const express = require('express');
const mysql = require('mysql2/promise');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 4000;

app.use(express.json());
app.use(cors({ origin: process.env.FRONTEND_ORIGIN || 'http://localhost:3000' }));

const pool = mysql.createPool({
  host: process.env.MYSQL_HOST || 'localhost',
  user: process.env.MYSQL_USER || 'root',
  password: process.env.MYSQL_PASSWORD || '',
  database: process.env.MYSQL_DB || 'myapp',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});

app.post('/api/users', async (req, res) => {
  try {
    const { firstName, lastName, email } = req.body;

    if (!firstName || !lastName || !email) {
      return res.status(400).json({
        success: false,
        error: 'First name, last name, and email are required',
      });
    }

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

app.get('/api/health', (req, res) => {
  res.json({ ok: true });
});

app.listen(PORT, () => {
  console.log(`Backend running at http://localhost:${PORT}`);
});
