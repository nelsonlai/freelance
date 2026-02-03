/**
 * Express Backend Server
 * 
 * This server provides REST API endpoints for the Angular Comprehensive Demo application.
 * 
 * Features:
 * - RESTful API endpoints
 * - JWT authentication
 * - CORS support
 * - In-memory data storage
 * - Error handling
 * 
 * To run:
 *   npm install
 *   npm start
 * 
 * Server runs on: http://localhost:3000
 */

const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcryptjs');

const app = express();
const PORT = 3000;
const JWT_SECRET = 'your-secret-key-change-in-production'; // In production, use environment variable

// Middleware
app.use(cors()); // Enable CORS for all routes
app.use(bodyParser.json()); // Parse JSON request bodies
app.use(bodyParser.urlencoded({ extended: true })); // Parse URL-encoded bodies

/**
 * In-Memory Data Storage
 * 
 * In a production application, you would use a database (MongoDB, PostgreSQL, etc.)
 * For this demo, we use in-memory storage which resets on server restart.
 */

// Users database
let users = [
  {
    id: 1,
    firstName: 'John',
    lastName: 'Doe',
    email: 'john@example.com',
    password: bcrypt.hashSync('password123', 10), // Hashed password
    role: 'user',
    isActive: true,
    createdAt: new Date().toISOString(),
    updatedAt: new Date().toISOString()
  },
  {
    id: 2,
    firstName: 'Jane',
    lastName: 'Smith',
    email: 'jane@example.com',
    password: bcrypt.hashSync('password123', 10),
    role: 'admin',
    isActive: true,
    createdAt: new Date().toISOString(),
    updatedAt: new Date().toISOString()
  }
];

// Products database
let products = [
  {
    id: 1,
    name: 'Laptop',
    description: 'High-performance laptop for professionals',
    price: 999.99,
    category: 'Electronics',
    stock: 10,
    isAvailable: true,
    rating: 4.5,
    createdAt: new Date().toISOString(),
    updatedAt: new Date().toISOString()
  },
  {
    id: 2,
    name: 'Smartphone',
    description: 'Latest smartphone with advanced features',
    price: 699.99,
    category: 'Electronics',
    stock: 25,
    isAvailable: true,
    rating: 4.8,
    createdAt: new Date().toISOString(),
    updatedAt: new Date().toISOString()
  },
  {
    id: 3,
    name: 'Headphones',
    description: 'Wireless noise-cancelling headphones',
    price: 199.99,
    category: 'Electronics',
    stock: 50,
    isAvailable: true,
    rating: 4.6,
    createdAt: new Date().toISOString(),
    updatedAt: new Date().toISOString()
  }
];

let nextUserId = 3;
let nextProductId = 4;

/**
 * Authentication Middleware
 * 
 * Verifies JWT token in Authorization header
 */
const authenticateToken = (req, res, next) => {
  const authHeader = req.headers['authorization'];
  const token = authHeader && authHeader.split(' ')[1]; // Bearer TOKEN

  if (!token) {
    return res.status(401).json({ error: 'Access token required' });
  }

  jwt.verify(token, JWT_SECRET, (err, user) => {
    if (err) {
      return res.status(403).json({ error: 'Invalid or expired token' });
    }
    req.user = user;
    next();
  });
};

/**
 * Helper function to generate JWT token
 */
const generateToken = (user) => {
  return jwt.sign(
    { id: user.id, email: user.email, role: user.role },
    JWT_SECRET,
    { expiresIn: '1h' }
  );
};

/**
 * Helper function to generate refresh token
 */
const generateRefreshToken = (user) => {
  return jwt.sign(
    { id: user.id, email: user.email },
    JWT_SECRET,
    { expiresIn: '7d' }
  );
};

/**
 * Helper function to sanitize user object (remove password)
 */
const sanitizeUser = (user) => {
  const { password, ...userWithoutPassword } = user;
  return userWithoutPassword;
};

// ==================== AUTHENTICATION ROUTES ====================

/**
 * POST /api/auth/register
 * Register a new user
 */
app.post('/api/auth/register', async (req, res) => {
  try {
    const { firstName, lastName, email, password, role = 'user' } = req.body;

    // Validation
    if (!firstName || !lastName || !email || !password) {
      return res.status(400).json({ error: 'All fields are required' });
    }

    if (password.length < 6) {
      return res.status(400).json({ error: 'Password must be at least 6 characters' });
    }

    // Check if user already exists
    const existingUser = users.find(u => u.email === email);
    if (existingUser) {
      return res.status(400).json({ error: 'User with this email already exists' });
    }

    // Create new user
    const newUser = {
      id: nextUserId++,
      firstName,
      lastName,
      email,
      password: bcrypt.hashSync(password, 10),
      role,
      isActive: true,
      createdAt: new Date().toISOString(),
      updatedAt: new Date().toISOString()
    };

    users.push(newUser);

    // Generate tokens
    const token = generateToken(newUser);
    const refreshToken = generateRefreshToken(newUser);

    // Return response
    res.status(201).json({
      token,
      refreshToken,
      user: sanitizeUser(newUser),
      expiresIn: 3600
    });
  } catch (error) {
    console.error('Registration error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * POST /api/auth/login
 * Login user
 */
app.post('/api/auth/login', async (req, res) => {
  try {
    const { email, password } = req.body;

    // Validation
    if (!email || !password) {
      return res.status(400).json({ error: 'Email and password are required' });
    }

    // Find user
    const user = users.find(u => u.email === email);
    if (!user) {
      return res.status(401).json({ error: 'Invalid credentials' });
    }

    // Check password
    const isValidPassword = bcrypt.compareSync(password, user.password);
    if (!isValidPassword) {
      return res.status(401).json({ error: 'Invalid credentials' });
    }

    // Check if user is active
    if (!user.isActive) {
      return res.status(403).json({ error: 'Account is inactive' });
    }

    // Generate tokens
    const token = generateToken(user);
    const refreshToken = generateRefreshToken(user);

    // Return response
    res.json({
      token,
      refreshToken,
      user: sanitizeUser(user),
      expiresIn: 3600
    });
  } catch (error) {
    console.error('Login error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * POST /api/auth/refresh
 * Refresh access token
 */
app.post('/api/auth/refresh', (req, res) => {
  try {
    const { refreshToken } = req.body;

    if (!refreshToken) {
      return res.status(400).json({ error: 'Refresh token is required' });
    }

    jwt.verify(refreshToken, JWT_SECRET, (err, decoded) => {
      if (err) {
        return res.status(403).json({ error: 'Invalid refresh token' });
      }

      // Find user
      const user = users.find(u => u.id === decoded.id);
      if (!user) {
        return res.status(404).json({ error: 'User not found' });
      }

      // Generate new access token
      const token = generateToken(user);

      res.json({
        token,
        expiresIn: 3600
      });
    });
  } catch (error) {
    console.error('Refresh token error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

// ==================== USER ROUTES ====================

/**
 * GET /api/users
 * Get all users (requires authentication)
 */
app.get('/api/users', authenticateToken, (req, res) => {
  try {
    // Return all users without passwords
    const sanitizedUsers = users.map(user => sanitizeUser(user));
    res.json(sanitizedUsers);
  } catch (error) {
    console.error('Get users error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * GET /api/users/:id
 * Get user by ID (requires authentication)
 */
app.get('/api/users/:id', authenticateToken, (req, res) => {
  try {
    const id = parseInt(req.params.id);
    const user = users.find(u => u.id === id);

    if (!user) {
      return res.status(404).json({ error: 'User not found' });
    }

    res.json(sanitizeUser(user));
  } catch (error) {
    console.error('Get user error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * POST /api/users
 * Create new user (requires authentication, admin only)
 */
app.post('/api/users', authenticateToken, (req, res) => {
  try {
    // Check if user is admin
    if (req.user.role !== 'admin') {
      return res.status(403).json({ error: 'Admin access required' });
    }

    const { firstName, lastName, email, password, role = 'user' } = req.body;

    // Validation
    if (!firstName || !lastName || !email || !password) {
      return res.status(400).json({ error: 'All fields are required' });
    }

    // Check if user already exists
    const existingUser = users.find(u => u.email === email);
    if (existingUser) {
      return res.status(400).json({ error: 'User with this email already exists' });
    }

    // Create new user
    const newUser = {
      id: nextUserId++,
      firstName,
      lastName,
      email,
      password: bcrypt.hashSync(password, 10),
      role,
      isActive: true,
      createdAt: new Date().toISOString(),
      updatedAt: new Date().toISOString()
    };

    users.push(newUser);
    res.status(201).json(sanitizeUser(newUser));
  } catch (error) {
    console.error('Create user error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * PUT /api/users/:id
 * Update user (requires authentication)
 */
app.put('/api/users/:id', authenticateToken, (req, res) => {
  try {
    const id = parseInt(req.params.id);
    const userIndex = users.findIndex(u => u.id === id);

    if (userIndex === -1) {
      return res.status(404).json({ error: 'User not found' });
    }

    // Check permissions (users can only update themselves, admins can update anyone)
    if (req.user.id !== id && req.user.role !== 'admin') {
      return res.status(403).json({ error: 'Permission denied' });
    }

    const { firstName, lastName, email, role, isActive } = req.body;
    const user = users[userIndex];

    // Update user
    users[userIndex] = {
      ...user,
      firstName: firstName || user.firstName,
      lastName: lastName || user.lastName,
      email: email || user.email,
      role: req.user.role === 'admin' ? (role || user.role) : user.role,
      isActive: req.user.role === 'admin' ? (isActive !== undefined ? isActive : user.isActive) : user.isActive,
      updatedAt: new Date().toISOString()
    };

    res.json(sanitizeUser(users[userIndex]));
  } catch (error) {
    console.error('Update user error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * DELETE /api/users/:id
 * Delete user (requires authentication, admin only)
 */
app.delete('/api/users/:id', authenticateToken, (req, res) => {
  try {
    // Check if user is admin
    if (req.user.role !== 'admin') {
      return res.status(403).json({ error: 'Admin access required' });
    }

    const id = parseInt(req.params.id);
    const userIndex = users.findIndex(u => u.id === id);

    if (userIndex === -1) {
      return res.status(404).json({ error: 'User not found' });
    }

    users.splice(userIndex, 1);
    res.status(204).send();
  } catch (error) {
    console.error('Delete user error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

// ==================== PRODUCT ROUTES ====================

/**
 * GET /api/products
 * Get all products (requires authentication)
 */
app.get('/api/products', authenticateToken, (req, res) => {
  try {
    res.json(products);
  } catch (error) {
    console.error('Get products error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * GET /api/products/:id
 * Get product by ID (requires authentication)
 */
app.get('/api/products/:id', authenticateToken, (req, res) => {
  try {
    const id = parseInt(req.params.id);
    const product = products.find(p => p.id === id);

    if (!product) {
      return res.status(404).json({ error: 'Product not found' });
    }

    res.json(product);
  } catch (error) {
    console.error('Get product error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * POST /api/products
 * Create new product (requires authentication, admin only)
 */
app.post('/api/products', authenticateToken, (req, res) => {
  try {
    // Check if user is admin
    if (req.user.role !== 'admin') {
      return res.status(403).json({ error: 'Admin access required' });
    }

    const { name, description, price, category, imageUrl, stock, isAvailable } = req.body;

    // Validation
    if (!name || !description || price === undefined || !category || stock === undefined) {
      return res.status(400).json({ error: 'Required fields: name, description, price, category, stock' });
    }

    // Create new product
    const newProduct = {
      id: nextProductId++,
      name,
      description,
      price: parseFloat(price),
      category,
      imageUrl: imageUrl || '',
      stock: parseInt(stock),
      isAvailable: isAvailable !== undefined ? isAvailable : true,
      rating: 0,
      createdAt: new Date().toISOString(),
      updatedAt: new Date().toISOString()
    };

    products.push(newProduct);
    res.status(201).json(newProduct);
  } catch (error) {
    console.error('Create product error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * PUT /api/products/:id
 * Update product (requires authentication, admin only)
 */
app.put('/api/products/:id', authenticateToken, (req, res) => {
  try {
    // Check if user is admin
    if (req.user.role !== 'admin') {
      return res.status(403).json({ error: 'Admin access required' });
    }

    const id = parseInt(req.params.id);
    const productIndex = products.findIndex(p => p.id === id);

    if (productIndex === -1) {
      return res.status(404).json({ error: 'Product not found' });
    }

    const product = products[productIndex];
    const { name, description, price, category, imageUrl, stock, isAvailable, rating } = req.body;

    // Update product
    products[productIndex] = {
      ...product,
      name: name || product.name,
      description: description || product.description,
      price: price !== undefined ? parseFloat(price) : product.price,
      category: category || product.category,
      imageUrl: imageUrl !== undefined ? imageUrl : product.imageUrl,
      stock: stock !== undefined ? parseInt(stock) : product.stock,
      isAvailable: isAvailable !== undefined ? isAvailable : product.isAvailable,
      rating: rating !== undefined ? parseFloat(rating) : product.rating,
      updatedAt: new Date().toISOString()
    };

    res.json(products[productIndex]);
  } catch (error) {
    console.error('Update product error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

/**
 * DELETE /api/products/:id
 * Delete product (requires authentication, admin only)
 */
app.delete('/api/products/:id', authenticateToken, (req, res) => {
  try {
    // Check if user is admin
    if (req.user.role !== 'admin') {
      return res.status(403).json({ error: 'Admin access required' });
    }

    const id = parseInt(req.params.id);
    const productIndex = products.findIndex(p => p.id === id);

    if (productIndex === -1) {
      return res.status(404).json({ error: 'Product not found' });
    }

    products.splice(productIndex, 1);
    res.status(204).send();
  } catch (error) {
    console.error('Delete product error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

// ==================== HEALTH CHECK ====================

/**
 * GET /api/health
 * Health check endpoint
 */
app.get('/api/health', (req, res) => {
  res.json({ status: 'ok', message: 'Server is running' });
});

// ==================== ERROR HANDLING ====================

// 404 handler
app.use((req, res) => {
  res.status(404).json({ error: 'Route not found' });
});

// Global error handler
app.use((err, req, res, next) => {
  console.error('Unhandled error:', err);
  res.status(500).json({ error: 'Internal server error' });
});

// ==================== START SERVER ====================

app.listen(PORT, () => {
  console.log(`\n🚀 Backend server running on http://localhost:${PORT}`);
  console.log(`📡 API endpoints available at http://localhost:${PORT}/api`);
  console.log(`\nAvailable endpoints:`);
  console.log(`  POST   /api/auth/register`);
  console.log(`  POST   /api/auth/login`);
  console.log(`  POST   /api/auth/refresh`);
  console.log(`  GET    /api/users (auth required)`);
  console.log(`  GET    /api/users/:id (auth required)`);
  console.log(`  POST   /api/users (auth required, admin only)`);
  console.log(`  PUT    /api/users/:id (auth required)`);
  console.log(`  DELETE /api/users/:id (auth required, admin only)`);
  console.log(`  GET    /api/products (auth required)`);
  console.log(`  GET    /api/products/:id (auth required)`);
  console.log(`  POST   /api/products (auth required, admin only)`);
  console.log(`  PUT    /api/products/:id (auth required, admin only)`);
  console.log(`  DELETE /api/products/:id (auth required, admin only)`);
  console.log(`\n💡 Default users:`);
  console.log(`  Admin: jane@example.com / password123`);
  console.log(`  User:  john@example.com / password123`);
  console.log(`\n`);
});

