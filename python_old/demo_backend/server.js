const express = require('express');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

// Mock DB
let users = [
  { id: 1, username: 'john_doe', email: 'john@example.com', age: 25, active: true },
  { id: 2, username: 'jane_smith', email: 'jane@example.com', age: 30, active: true },
  { id: 3, username: 'bob_wilson', email: 'bob@example.com', age: 35, active: false }
];

let products = [
  { id: 1, name: 'Laptop', price: 999.99, category: 'Electronics', stock: 50 },
  { id: 2, name: 'Mouse', price: 29.99, category: 'Electronics', stock: 100 },
  { id: 3, name: 'Keyboard', price: 79.99, category: 'Electronics', stock: 75 }
];

let orders = [
  { id: 1, user_id: 1, product_id: 1, quantity: 2, total: 1999.98, status: 'pending' },
  { id: 2, user_id: 2, product_id: 2, quantity: 1, total: 29.99, status: 'completed' }
];

function nowIso() { return new Date().toISOString(); }

app.get('/', (req, res) => {
  res.json({
    message: 'Welcome to Express RESTful API Demo',
    version: '1.0.0',
    endpoints: {
      GET: ['/', '/users', '/users/:id', '/products', '/products/:id'],
      POST: ['/users', '/products', '/orders'],
      PUT: ['/users/:id', '/products/:id'],
      PATCH: ['/users/:id', '/products/:id'],
      DELETE: ['/users/:id', '/products/:id'],
      HEAD: ['/users', '/products', '/orders'],
      OPTIONS: ['/users', '/products', '/orders']
    },
    timestamp: nowIso()
  });
});

// USERS
app.options('/users', (req, res) => {
  res.set('Allow', 'GET, POST, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Methods', 'GET, POST, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  res.set('Access-Control-Max-Age', '86400');
  res.sendStatus(200);
});

app.head('/users', (req, res) => {
  res.set('Content-Type', 'application/json');
  res.set('X-Total-Count', String(users.length));
  res.set('X-API-Version', '1.0.0');
  res.sendStatus(200);
});

app.get('/users', (req, res) => {
  const page = parseInt(req.query.page || '1', 10);
  const limit = parseInt(req.query.limit || '10', 10);
  const active = req.query.active;

  let filtered = users;
  if (active !== undefined) {
    const activeBool = String(active).toLowerCase() === 'true';
    filtered = users.filter(u => u.active === activeBool);
  }

  const start = (page - 1) * limit;
  const paginated = filtered.slice(start, start + limit);

  res.json({
    users: paginated,
    pagination: {
      page, limit, total: filtered.length, pages: Math.ceil(filtered.length / limit)
    },
    headers_received: {
      user_agent: req.get('User-Agent') || 'Unknown',
      accept_language: req.get('Accept-Language') || 'en'
    }
  });
});

app.post('/users', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const data = req.body;
  const required = ['username', 'email'];
  const missing = required.filter(f => !(f in data));
  if (missing.length) return res.status(400).json({ error: 'Missing required fields', message: `Required fields missing: ${missing.join(', ')}`, timestamp: nowIso() });
  if (users.some(u => u.username === data.username)) return res.status(409).json({ error: 'Username already exists', message: `Username '${data.username}' is already taken`, timestamp: nowIso() });
  const newUser = { id: Math.max(...users.map(u => u.id)) + 1, username: data.username, email: data.email, age: data.age || null, active: data.active !== undefined ? data.active : true };
  users.push(newUser);
  res.status(201).json({ message: 'User created successfully', user: newUser, timestamp: nowIso() });
});

app.options('/users/:id', (req, res) => {
  res.set('Allow', 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Methods', 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  res.set('Access-Control-Max-Age', '86400');
  res.sendStatus(200);
});

app.head('/users/:id', (req, res) => {
  const id = Number(req.params.id);
  const user = users.find(u => u.id === id);
  if (!user) return res.sendStatus(404);
  res.set('Content-Type', 'application/json');
  res.set('X-User-ID', String(id));
  res.set('X-User-Status', user.active ? 'active' : 'inactive');
  res.sendStatus(200);
});

app.get('/users/:id', (req, res) => {
  const id = Number(req.params.id);
  const user = users.find(u => u.id === id);
  if (!user) return res.status(404).json({ error: 'User not found', message: `User with ID ${id} does not exist`, timestamp: nowIso() });
  res.json({ user, timestamp: nowIso() });
});

app.put('/users/:id', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const id = Number(req.params.id);
  const idx = users.findIndex(u => u.id === id);
  if (idx === -1) return res.status(404).json({ error: 'User not found', message: `User with ID ${id} does not exist`, timestamp: nowIso() });
  const data = req.body;
  users[idx] = { ...users[idx], username: data.username || users[idx].username, email: data.email || users[idx].email, age: data.age !== undefined ? data.age : users[idx].age, active: data.active !== undefined ? data.active : users[idx].active };
  res.json({ message: 'User updated successfully', user: users[idx], timestamp: nowIso() });
});

app.patch('/users/:id', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const id = Number(req.params.id);
  const idx = users.findIndex(u => u.id === id);
  if (idx === -1) return res.status(404).json({ error: 'User not found', message: `User with ID ${id} does not exist`, timestamp: nowIso() });
  const data = req.body;
  if (data.username && data.username !== users[idx].username && users.some(u => u.username === data.username)) return res.status(409).json({ error: 'Username already exists', message: `Username '${data.username}' is already taken`, timestamp: nowIso() });
  users[idx] = { ...users[idx], ...(data.username !== undefined ? { username: data.username } : {}), ...(data.email !== undefined ? { email: data.email } : {}), ...(data.age !== undefined ? { age: data.age } : {}), ...(data.active !== undefined ? { active: data.active } : {}) };
  res.json({ message: 'User partially updated successfully', user: users[idx], timestamp: nowIso() });
});

app.delete('/users/:id', (req, res) => {
  const id = Number(req.params.id);
  const idx = users.findIndex(u => u.id === id);
  if (idx === -1) return res.status(404).json({ error: 'User not found', message: `User with ID ${id} does not exist`, timestamp: nowIso() });
  const deleted = users.splice(idx, 1)[0];
  res.json({ message: 'User deleted successfully', deleted_user: deleted, timestamp: nowIso() });
});

// PRODUCTS
app.options('/products', (req, res) => {
  res.set('Allow', 'GET, POST, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Methods', 'GET, POST, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  res.set('Access-Control-Max-Age', '86400');
  res.sendStatus(200);
});

app.head('/products', (req, res) => {
  res.set('Content-Type', 'application/json');
  res.set('X-Total-Count', String(products.length));
  res.set('X-API-Version', '1.0.0');
  res.set('X-Categories', 'Electronics, General');
  res.sendStatus(200);
});

app.get('/products', (req, res) => {
  const category = req.query.category;
  const min_price = req.query.min_price !== undefined ? parseFloat(req.query.min_price) : undefined;
  const max_price = req.query.max_price !== undefined ? parseFloat(req.query.max_price) : undefined;
  const sort_by = req.query.sort_by || 'id';
  const order = (req.query.order || 'asc').toLowerCase();

  let filtered = products.slice();
  if (category) filtered = filtered.filter(p => p.category.toLowerCase() === category.toLowerCase());
  if (min_price !== undefined) filtered = filtered.filter(p => p.price >= min_price);
  if (max_price !== undefined) filtered = filtered.filter(p => p.price <= max_price);
  const reverse = order === 'desc';
  if (['name', 'price', 'stock'].includes(sort_by)) filtered.sort((a,b) => (a[sort_by] > b[sort_by] ? 1 : -1) * (reverse ? -1 : 1));

  res.json({ products: filtered, filters_applied: { category, min_price, max_price, sort_by, order }, total_count: filtered.length });
});

app.post('/products', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const data = req.body;
  const required = ['name', 'price'];
  const missing = required.filter(f => !(f in data));
  if (missing.length) return res.status(400).json({ error: 'Missing required fields', message: `Required fields missing: ${missing.join(', ')}`, timestamp: nowIso() });
  if (data.price <= 0) return res.status(400).json({ error: 'Invalid price', message: 'Price must be greater than 0', timestamp: nowIso() });
  const newProduct = { id: Math.max(...products.map(p => p.id)) + 1, name: data.name, price: data.price, category: data.category || 'General', stock: data.stock || 0 };
  products.push(newProduct);
  res.status(201).json({ message: 'Product created successfully', product: newProduct, timestamp: nowIso() });
});

app.options('/products/:id', (req, res) => {
  res.set('Allow', 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Methods', 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  res.set('Access-Control-Max-Age', '86400');
  res.sendStatus(200);
});

app.head('/products/:id', (req, res) => {
  const id = Number(req.params.id);
  const product = products.find(p => p.id === id);
  if (!product) return res.sendStatus(404);
  res.set('Content-Type', 'application/json');
  res.set('X-Product-ID', String(id));
  res.set('X-Product-Category', product.category);
  res.set('X-Product-Stock', String(product.stock));
  res.sendStatus(200);
});

app.get('/products/:id', (req, res) => {
  const id = Number(req.params.id);
  const product = products.find(p => p.id === id);
  if (!product) return res.status(404).json({ error: 'Product not found', message: `Product with ID ${id} does not exist`, timestamp: nowIso() });
  res.json({ product, timestamp: nowIso() });
});

app.put('/products/:id', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const id = Number(req.params.id);
  const idx = products.findIndex(p => p.id === id);
  if (idx === -1) return res.status(404).json({ error: 'Product not found', message: `Product with ID ${id} does not exist`, timestamp: nowIso() });
  const data = req.body;
  products[idx] = { ...products[idx], name: data.name || products[idx].name, price: data.price !== undefined ? data.price : products[idx].price, category: data.category || products[idx].category, stock: data.stock !== undefined ? data.stock : products[idx].stock };
  res.json({ message: 'Product updated successfully', product: products[idx], timestamp: nowIso() });
});

app.patch('/products/:id', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const id = Number(req.params.id);
  const idx = products.findIndex(p => p.id === id);
  if (idx === -1) return res.status(404).json({ error: 'Product not found', message: `Product with ID ${id} does not exist`, timestamp: nowIso() });
  const data = req.body;
  if (data.price !== undefined && data.price <= 0) return res.status(400).json({ error: 'Invalid price', message: 'Price must be greater than 0', timestamp: nowIso() });
  products[idx] = { ...products[idx], ...(data.name !== undefined ? { name: data.name } : {}), ...(data.price !== undefined ? { price: data.price } : {}), ...(data.category !== undefined ? { category: data.category } : {}), ...(data.stock !== undefined ? { stock: data.stock } : {}) };
  res.json({ message: 'Product partially updated successfully', product: products[idx], timestamp: nowIso() });
});

app.delete('/products/:id', (req, res) => {
  const id = Number(req.params.id);
  const idx = products.findIndex(p => p.id === id);
  if (idx === -1) return res.status(404).json({ error: 'Product not found', message: `Product with ID ${id} does not exist`, timestamp: nowIso() });
  const deleted = products.splice(idx, 1)[0];
  res.json({ message: 'Product deleted successfully', deleted_product: deleted, timestamp: nowIso() });
});

// ORDERS
app.options('/orders', (req, res) => {
  res.set('Allow', 'GET, POST, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Methods', 'GET, POST, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  res.set('Access-Control-Max-Age', '86400');
  res.sendStatus(200);
});

app.head('/orders', (req, res) => {
  res.set('Content-Type', 'application/json');
  res.set('X-Total-Count', String(orders.length));
  res.set('X-API-Version', '1.0.0');
  res.set('X-Order-Statuses', 'pending, completed, cancelled');
  res.sendStatus(200);
});

app.get('/orders', (req, res) => {
  const user_id = req.query.user_id !== undefined ? Number(req.query.user_id) : undefined;
  const status = req.query.status;
  let filtered = orders;
  if (user_id !== undefined) filtered = filtered.filter(o => o.user_id === user_id);
  if (status) filtered = filtered.filter(o => o.status.toLowerCase() === status.toLowerCase());
  const enriched = filtered.map(o => ({ ...o, user: users.find(u => u.id === o.user_id) || null, product: products.find(p => p.id === o.product_id) || null }));
  res.json({ orders: enriched, total_count: enriched.length, filters_applied: { user_id, status } });
});

app.post('/orders', (req, res) => {
  if (!req.is('application/json')) return res.status(400).json({ error: 'Invalid content type', message: 'Request must contain JSON data', timestamp: nowIso() });
  const data = req.body;
  const required = ['user_id', 'product_id', 'quantity'];
  const missing = required.filter(f => !(f in data));
  if (missing.length) return res.status(400).json({ error: 'Missing required fields', message: `Required fields missing: ${missing.join(', ')}`, timestamp: nowIso() });
  const user = users.find(u => u.id === data.user_id);
  if (!user) return res.status(404).json({ error: 'User not found', message: `User with ID ${data.user_id} does not exist`, timestamp: nowIso() });
  const product = products.find(p => p.id === data.product_id);
  if (!product) return res.status(404).json({ error: 'Product not found', message: `Product with ID ${data.product_id} does not exist`, timestamp: nowIso() });
  if (data.quantity <= 0) return res.status(400).json({ error: 'Invalid quantity', message: 'Quantity must be greater than 0', timestamp: nowIso() });
  if (product.stock < data.quantity) return res.status(422).json({ error: 'Insufficient stock', message: `Only ${product.stock} items available in stock`, timestamp: nowIso() });
  const total = product.price * data.quantity;
  const newOrder = { id: Math.max(...orders.map(o => o.id)) + 1, user_id: data.user_id, product_id: data.product_id, quantity: data.quantity, total, status: 'pending' };
  orders.push(newOrder);
  product.stock -= data.quantity;
  res.json({ message: 'Order created successfully', order: newOrder, timestamp: nowIso() });
});

// HEALTH
app.options('/health', (req, res) => {
  res.set('Allow', 'GET, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Methods', 'GET, HEAD, OPTIONS');
  res.set('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  res.set('Access-Control-Max-Age', '86400');
  res.sendStatus(200);
});

app.head('/health', (req, res) => {
  res.set('Content-Type', 'application/json');
  res.set('X-Status', 'healthy');
  res.set('X-Timestamp', nowIso());
  res.sendStatus(200);
});

app.get('/health', (req, res) => {
  res.json({ status: 'healthy', timestamp: nowIso(), database: { users_count: users.length, products_count: products.length, orders_count: orders.length } });
});

// Error handlers
app.use((req, res) => {
  res.status(404).json({ error: 'Not Found', message: 'The requested resource was not found', timestamp: nowIso() });
});

app.use((err, req, res, next) => {
  console.error(err && err.stack ? err.stack : err);
  res.status(500).json({ error: 'Internal Server Error', message: 'An unexpected error occurred', timestamp: nowIso() });
});

const PORT = process.env.PORT || 54321;
app.listen(PORT, '0.0.0.0', () => {
  console.log('🚀 Starting Express RESTful API Demo...');
  console.log(`Listening on http://0.0.0.0:${PORT}`);
});
