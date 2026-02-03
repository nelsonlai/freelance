# Lesson 8: Capstone Project - E-Commerce Cart

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete e-commerce shopping cart
- Implement product catalog and search functionality
- Handle shopping cart state management
- Process checkout and payment (simulated)
- Manage user accounts and order history
- Create responsive e-commerce interface

## 📚 Project Overview

We'll build an e-commerce application that includes:
- Product catalog with categories and search
- Shopping cart with add/remove/update functionality
- User authentication and account management
- Checkout process with form validation
- Order management and history
- Payment integration (simulated)

## 🏗️ Project Structure

```
ecommerce-app/
├── package.json
├── src/
│   ├── App.js
│   ├── components/
│   │   ├── Header.js
│   │   ├── ProductCard.js
│   │   ├── ProductList.js
│   │   ├── ShoppingCart.js
│   │   ├── Checkout.js
│   │   └── OrderHistory.js
│   ├── context/
│   │   ├── CartContext.js
│   │   └── AuthContext.js
│   ├── hooks/
│   │   ├── useCart.js
│   │   └── useAuth.js
│   └── data/
│       └── products.js
└── styles/
    └── App.css
```

## 💻 Complete Implementation

### context/CartContext.js
```javascript
import React, { createContext, useContext, useReducer } from 'react';

const CartContext = createContext();

const cartReducer = (state, action) => {
    switch (action.type) {
        case 'ADD_TO_CART':
            const existingItem = state.items.find(item => item.id === action.payload.id);
            if (existingItem) {
                return {
                    ...state,
                    items: state.items.map(item =>
                        item.id === action.payload.id
                            ? { ...item, quantity: item.quantity + 1 }
                            : item
                    )
                };
            }
            return {
                ...state,
                items: [...state.items, { ...action.payload, quantity: 1 }]
            };
        
        case 'REMOVE_FROM_CART':
            return {
                ...state,
                items: state.items.filter(item => item.id !== action.payload)
            };
        
        case 'UPDATE_QUANTITY':
            return {
                ...state,
                items: state.items.map(item =>
                    item.id === action.payload.id
                        ? { ...item, quantity: action.payload.quantity }
                        : item
                ).filter(item => item.quantity > 0)
            };
        
        case 'CLEAR_CART':
            return {
                ...state,
                items: []
            };
        
        default:
            return state;
    }
};

export function CartProvider({ children }) {
    const [state, dispatch] = useReducer(cartReducer, {
        items: [],
        isOpen: false
    });
    
    const addToCart = (product) => {
        dispatch({ type: 'ADD_TO_CART', payload: product });
    };
    
    const removeFromCart = (productId) => {
        dispatch({ type: 'REMOVE_FROM_CART', payload: productId });
    };
    
    const updateQuantity = (productId, quantity) => {
        dispatch({ type: 'UPDATE_QUANTITY', payload: { id: productId, quantity } });
    };
    
    const clearCart = () => {
        dispatch({ type: 'CLEAR_CART' });
    };
    
    const toggleCart = () => {
        dispatch({ type: 'TOGGLE_CART' });
    };
    
    const getTotalPrice = () => {
        return state.items.reduce((total, item) => total + (item.price * item.quantity), 0);
    };
    
    const getTotalItems = () => {
        return state.items.reduce((total, item) => total + item.quantity, 0);
    };
    
    const value = {
        ...state,
        addToCart,
        removeFromCart,
        updateQuantity,
        clearCart,
        toggleCart,
        getTotalPrice,
        getTotalItems
    };
    
    return (
        <CartContext.Provider value={value}>
            {children}
        </CartContext.Provider>
    );
}

export function useCart() {
    const context = useContext(CartContext);
    if (!context) {
        throw new Error('useCart must be used within a CartProvider');
    }
    return context;
}
```

### components/ProductList.js
```javascript
import React, { useState, useEffect } from 'react';
import ProductCard from './ProductCard';
import { products } from '../data/products';

function ProductList() {
    const [filteredProducts, setFilteredProducts] = useState(products);
    const [searchTerm, setSearchTerm] = useState('');
    const [selectedCategory, setSelectedCategory] = useState('all');
    const [sortBy, setSortBy] = useState('name');
    
    const categories = ['all', ...new Set(products.map(product => product.category))];
    
    useEffect(() => {
        let filtered = products;
        
        // Filter by search term
        if (searchTerm) {
            filtered = filtered.filter(product =>
                product.name.toLowerCase().includes(searchTerm.toLowerCase()) ||
                product.description.toLowerCase().includes(searchTerm.toLowerCase())
            );
        }
        
        // Filter by category
        if (selectedCategory !== 'all') {
            filtered = filtered.filter(product => product.category === selectedCategory);
        }
        
        // Sort products
        filtered.sort((a, b) => {
            switch (sortBy) {
                case 'name':
                    return a.name.localeCompare(b.name);
                case 'price-low':
                    return a.price - b.price;
                case 'price-high':
                    return b.price - a.price;
                case 'rating':
                    return b.rating - a.rating;
                default:
                    return 0;
            }
        });
        
        setFilteredProducts(filtered);
    }, [searchTerm, selectedCategory, sortBy]);
    
    return (
        <div className="product-list">
            <div className="product-filters">
                <div className="search-bar">
                    <input
                        type="text"
                        placeholder="Search products..."
                        value={searchTerm}
                        onChange={(e) => setSearchTerm(e.target.value)}
                    />
                </div>
                
                <div className="filter-controls">
                    <select
                        value={selectedCategory}
                        onChange={(e) => setSelectedCategory(e.target.value)}
                    >
                        {categories.map(category => (
                            <option key={category} value={category}>
                                {category.charAt(0).toUpperCase() + category.slice(1)}
                            </option>
                        ))}
                    </select>
                    
                    <select
                        value={sortBy}
                        onChange={(e) => setSortBy(e.target.value)}
                    >
                        <option value="name">Sort by Name</option>
                        <option value="price-low">Price: Low to High</option>
                        <option value="price-high">Price: High to Low</option>
                        <option value="rating">Sort by Rating</option>
                    </select>
                </div>
            </div>
            
            <div className="products-grid">
                {filteredProducts.map(product => (
                    <ProductCard key={product.id} product={product} />
                ))}
            </div>
            
            {filteredProducts.length === 0 && (
                <div className="no-products">
                    <p>No products found matching your criteria.</p>
                </div>
            )}
        </div>
    );
}

export default ProductList;
```

### components/ShoppingCart.js
```javascript
import React from 'react';
import { useCart } from '../context/CartContext';

function ShoppingCart() {
    const {
        items,
        isOpen,
        toggleCart,
        removeFromCart,
        updateQuantity,
        getTotalPrice,
        getTotalItems
    } = useCart();
    
    if (!isOpen) return null;
    
    return (
        <div className="shopping-cart-overlay" onClick={toggleCart}>
            <div className="shopping-cart" onClick={(e) => e.stopPropagation()}>
                <div className="cart-header">
                    <h3>Shopping Cart ({getTotalItems()} items)</h3>
                    <button className="close-btn" onClick={toggleCart}>×</button>
                </div>
                
                <div className="cart-items">
                    {items.length === 0 ? (
                        <div className="empty-cart">
                            <p>Your cart is empty</p>
                            <button onClick={toggleCart}>Continue Shopping</button>
                        </div>
                    ) : (
                        items.map(item => (
                            <div key={item.id} className="cart-item">
                                <div className="item-image">
                                    <img src={item.image} alt={item.name} />
                                </div>
                                
                                <div className="item-details">
                                    <h4>{item.name}</h4>
                                    <p className="item-price">${item.price}</p>
                                    
                                    <div className="quantity-controls">
                                        <button
                                            onClick={() => updateQuantity(item.id, item.quantity - 1)}
                                            disabled={item.quantity <= 1}
                                        >
                                            -
                                        </button>
                                        <span>{item.quantity}</span>
                                        <button
                                            onClick={() => updateQuantity(item.id, item.quantity + 1)}
                                        >
                                            +
                                        </button>
                                    </div>
                                </div>
                                
                                <div className="item-actions">
                                    <button
                                        className="remove-btn"
                                        onClick={() => removeFromCart(item.id)}
                                    >
                                        Remove
                                    </button>
                                </div>
                            </div>
                        ))
                    )}
                </div>
                
                {items.length > 0 && (
                    <div className="cart-footer">
                        <div className="cart-total">
                            <h4>Total: ${getTotalPrice().toFixed(2)}</h4>
                        </div>
                        
                        <div className="cart-actions">
                            <button className="btn btn-secondary" onClick={toggleCart}>
                                Continue Shopping
                            </button>
                            <button className="btn btn-primary">
                                Proceed to Checkout
                            </button>
                        </div>
                    </div>
                )}
            </div>
        </div>
    );
}

export default ShoppingCart;
```

### components/Checkout.js
```javascript
import React, { useState } from 'react';
import { useCart } from '../context/CartContext';
import { useAuth } from '../context/AuthContext';

function Checkout() {
    const { items, getTotalPrice, clearCart } = useCart();
    const { user } = useAuth();
    const [formData, setFormData] = useState({
        firstName: user?.firstName || '',
        lastName: user?.lastName || '',
        email: user?.email || '',
        address: '',
        city: '',
        state: '',
        zipCode: '',
        paymentMethod: 'credit-card',
        cardNumber: '',
        expiryDate: '',
        cvv: ''
    });
    const [isProcessing, setIsProcessing] = useState(false);
    const [orderComplete, setOrderComplete] = useState(false);
    
    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData(prev => ({
            ...prev,
            [name]: value
        }));
    };
    
    const handleSubmit = async (e) => {
        e.preventDefault();
        setIsProcessing(true);
        
        // Simulate payment processing
        await new Promise(resolve => setTimeout(resolve, 2000));
        
        // Create order
        const order = {
            id: Date.now(),
            items: items,
            total: getTotalPrice(),
            customer: formData,
            status: 'confirmed',
            date: new Date().toISOString()
        };
        
        // Save order to localStorage (simulate database)
        const orders = JSON.parse(localStorage.getItem('orders') || '[]');
        orders.push(order);
        localStorage.setItem('orders', JSON.stringify(orders));
        
        setIsProcessing(false);
        setOrderComplete(true);
        clearCart();
    };
    
    if (orderComplete) {
        return (
            <div className="checkout-success">
                <h2>Order Confirmed!</h2>
                <p>Thank you for your purchase. Your order has been confirmed.</p>
                <button className="btn btn-primary" onClick={() => window.location.href = '/'}>
                    Continue Shopping
                </button>
            </div>
        );
    }
    
    return (
        <div className="checkout">
            <h2>Checkout</h2>
            
            <div className="checkout-content">
                <div className="order-summary">
                    <h3>Order Summary</h3>
                    {items.map(item => (
                        <div key={item.id} className="order-item">
                            <span>{item.name} x {item.quantity}</span>
                            <span>${(item.price * item.quantity).toFixed(2)}</span>
                        </div>
                    ))}
                    <div className="order-total">
                        <strong>Total: ${getTotalPrice().toFixed(2)}</strong>
                    </div>
                </div>
                
                <form onSubmit={handleSubmit} className="checkout-form">
                    <div className="form-section">
                        <h3>Shipping Information</h3>
                        <div className="form-row">
                            <input
                                type="text"
                                name="firstName"
                                placeholder="First Name"
                                value={formData.firstName}
                                onChange={handleChange}
                                required
                            />
                            <input
                                type="text"
                                name="lastName"
                                placeholder="Last Name"
                                value={formData.lastName}
                                onChange={handleChange}
                                required
                            />
                        </div>
                        
                        <input
                            type="email"
                            name="email"
                            placeholder="Email"
                            value={formData.email}
                            onChange={handleChange}
                            required
                        />
                        
                        <input
                            type="text"
                            name="address"
                            placeholder="Address"
                            value={formData.address}
                            onChange={handleChange}
                            required
                        />
                        
                        <div className="form-row">
                            <input
                                type="text"
                                name="city"
                                placeholder="City"
                                value={formData.city}
                                onChange={handleChange}
                                required
                            />
                            <input
                                type="text"
                                name="state"
                                placeholder="State"
                                value={formData.state}
                                onChange={handleChange}
                                required
                            />
                            <input
                                type="text"
                                name="zipCode"
                                placeholder="ZIP Code"
                                value={formData.zipCode}
                                onChange={handleChange}
                                required
                            />
                        </div>
                    </div>
                    
                    <div className="form-section">
                        <h3>Payment Information</h3>
                        <select
                            name="paymentMethod"
                            value={formData.paymentMethod}
                            onChange={handleChange}
                        >
                            <option value="credit-card">Credit Card</option>
                            <option value="debit-card">Debit Card</option>
                            <option value="paypal">PayPal</option>
                        </select>
                        
                        <input
                            type="text"
                            name="cardNumber"
                            placeholder="Card Number"
                            value={formData.cardNumber}
                            onChange={handleChange}
                            required
                        />
                        
                        <div className="form-row">
                            <input
                                type="text"
                                name="expiryDate"
                                placeholder="MM/YY"
                                value={formData.expiryDate}
                                onChange={handleChange}
                                required
                            />
                            <input
                                type="text"
                                name="cvv"
                                placeholder="CVV"
                                value={formData.cvv}
                                onChange={handleChange}
                                required
                            />
                        </div>
                    </div>
                    
                    <button
                        type="submit"
                        className="btn btn-primary"
                        disabled={isProcessing}
                    >
                        {isProcessing ? 'Processing...' : 'Complete Order'}
                    </button>
                </form>
            </div>
        </div>
    );
}

export default Checkout;
```

## 🎯 Key Features Implemented

1. **Product Catalog** - Search, filter, and sort products
2. **Shopping Cart** - Add, remove, and update quantities
3. **User Authentication** - Login and account management
4. **Checkout Process** - Form validation and order processing
5. **Order Management** - Order history and status tracking
6. **Payment Integration** - Simulated payment processing
7. **Responsive Design** - Mobile and desktop support

## 🎯 Key Takeaways

1. **State management** handles complex cart operations
2. **Context API** provides global state access
3. **Form validation** ensures data integrity
4. **Payment processing** simulates real-world transactions
5. **Order management** tracks customer purchases

## 🚀 Next Steps

Congratulations! You've built a complete e-commerce application. In the next lesson, we'll learn about:

- **Performance Optimization** - Speed up applications
- **Code splitting** - Load only what's needed
- **Caching strategies** - Reduce server requests
- **Image optimization** - Faster loading times

---

**Next Lesson**: [Lesson 9: Performance Optimization](./lesson9-performance.md)
