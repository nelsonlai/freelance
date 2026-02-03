const express = require('express');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 4000;

app.use(cors());
app.use(express.json());

// In-memory data store
let customers = [
  { id: '1', name: 'John Doe', email: 'john@example.com', status: 'active' },
  { id: '2', name: 'Jane Smith', email: 'jane@example.com', status: 'active' },
  { id: '3', name: 'Bob Johnson', email: 'bob@example.com', status: 'inactive' },
];

// Auth endpoints
app.post('/api/auth/login', (req, res) => {
  const { email, password } = req.body;
  
  // Mock authentication - accept any email/password for demo
  if (email && password) {
    const response = {
      token: 'mock-jwt-token-' + Date.now(),
      refreshToken: 'mock-refresh-token-' + Date.now(),
      user: {
        id: '1',
        name: email.split('@')[0],
        roles: email.includes('admin') ? ['admin', 'user'] : ['user'],
      },
    };
    console.log('🔐 Login:', email);
    res.json(response);
  } else {
    res.status(401).json({ error: 'Invalid credentials' });
  }
});

app.post('/api/auth/refresh', (req, res) => {
  const { refreshToken } = req.body;
  const response = {
    token: 'mock-jwt-token-' + Date.now(),
    refreshToken: 'mock-refresh-token-' + Date.now(),
    user: {
      id: '1',
      name: 'User',
      roles: ['user'],
    },
  };
  console.log('🔄 Token refresh');
  res.json(response);
});

// Customer endpoints
app.get('/api/customers', (req, res) => {
  console.log('📋 Get customers');
  res.json(customers);
});

app.post('/api/customers', (req, res) => {
  const newCustomer = {
    id: Date.now().toString() + Math.random().toString(36).substr(2, 9),
    ...req.body,
  };
  customers.push(newCustomer);
  console.log('➕ Create customer:', newCustomer.name);
  res.json(newCustomer);
});

app.patch('/api/customers/:id', (req, res) => {
  const id = req.params.id;
  const index = customers.findIndex((c) => c.id === id);
  if (index !== -1) {
    customers[index] = { ...customers[index], ...req.body };
    console.log('✏️ Update customer:', customers[index].name);
    res.json(customers[index]);
  } else {
    res.status(404).json({ error: 'Customer not found' });
  }
});

app.delete('/api/customers/:id', (req, res) => {
  const id = req.params.id;
  const index = customers.findIndex((c) => c.id === id);
  if (index !== -1) {
    const deleted = customers.splice(index, 1)[0];
    console.log('🗑️ Delete customer:', deleted.name);
    res.json({ success: true });
  } else {
    res.status(404).json({ error: 'Customer not found' });
  }
});

app.listen(PORT, () => {
  console.log(`Backend listening on http://localhost:${PORT}`);
});

