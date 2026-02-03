// Exercise 2: E-commerce API Integration
// This exercise demonstrates building an e-commerce API client

console.log("=== Exercise 2: E-commerce API Integration ===");

// E-commerce API Client
class EcommerceAPIClient {
    constructor(baseURL = 'https://api.shop.com') {
        this.baseURL = baseURL;
        this.cart = [];
        this.sessionId = this.generateSessionId();
    }
    
    generateSessionId() {
        return 'session_' + Date.now() + '_' + Math.random().toString(36).substr(2, 9);
    }
    
    // Mock API responses
    async mockRequest(endpoint, method = 'GET', data = null) {
        console.log(`🛒 ${method} ${endpoint}`);
        
        return new Promise((resolve) => {
            setTimeout(() => {
                const response = this.generateEcommerceResponse(endpoint, method, data);
                resolve({
                    ok: true,
                    status: 200,
                    json: () => Promise.resolve(response)
                });
            }, 200);
        });
    }
    
    generateEcommerceResponse(endpoint, method, data) {
        if (endpoint.includes('/products')) {
            return {
                products: [
                    { id: 1, name: 'Laptop', price: 999.99, category: 'Electronics', stock: 10 },
                    { id: 2, name: 'Smartphone', price: 699.99, category: 'Electronics', stock: 25 },
                    { id: 3, name: 'Book', price: 19.99, category: 'Books', stock: 100 }
                ],
                total: 3
            };
        }
        
        if (endpoint.includes('/cart')) {
            return {
                items: this.cart,
                total: this.cart.reduce((sum, item) => sum + (item.price * item.quantity), 0),
                sessionId: this.sessionId
            };
        }
        
        if (endpoint.includes('/orders')) {
            return {
                orderId: Date.now(),
                status: 'pending',
                items: JSON.parse(data || '[]'),
                total: 0,
                createdAt: new Date().toISOString()
            };
        }
        
        return { message: 'Success' };
    }
    
    // Product operations
    async getProducts(filters = {}) {
        const queryString = new URLSearchParams(filters).toString();
        const endpoint = `/products${queryString ? '?' + queryString : ''}`;
        const response = await this.mockRequest(endpoint);
        return response.json();
    }
    
    async getProduct(id) {
        const response = await this.mockRequest(`/products/${id}`);
        return response.json();
    }
    
    // Cart operations
    async getCart() {
        const response = await this.mockRequest(`/cart/${this.sessionId}`);
        return response.json();
    }
    
    async addToCart(productId, quantity = 1) {
        const product = await this.getProduct(productId);
        const existingItem = this.cart.find(item => item.id === productId);
        
        if (existingItem) {
            existingItem.quantity += quantity;
        } else {
            this.cart.push({
                id: productId,
                name: product.name,
                price: product.price,
                quantity: quantity
            });
        }
        
        const response = await this.mockRequest(`/cart/${this.sessionId}`, 'POST', JSON.stringify(this.cart));
        return response.json();
    }
    
    async removeFromCart(productId) {
        this.cart = this.cart.filter(item => item.id !== productId);
        const response = await this.mockRequest(`/cart/${this.sessionId}`, 'PUT', JSON.stringify(this.cart));
        return response.json();
    }
    
    async updateCartItem(productId, quantity) {
        const item = this.cart.find(item => item.id === productId);
        if (item) {
            item.quantity = quantity;
        }
        const response = await this.mockRequest(`/cart/${this.sessionId}`, 'PUT', JSON.stringify(this.cart));
        return response.json();
    }
    
    async clearCart() {
        this.cart = [];
        const response = await this.mockRequest(`/cart/${this.sessionId}`, 'DELETE');
        return response.json();
    }
    
    // Order operations
    async createOrder(orderData) {
        const response = await this.mockRequest('/orders', 'POST', JSON.stringify(orderData));
        return response.json();
    }
    
    async getOrder(orderId) {
        const response = await this.mockRequest(`/orders/${orderId}`);
        return response.json();
    }
    
    async getOrders() {
        const response = await this.mockRequest('/orders');
        return response.json();
    }
}

// Test the e-commerce API client
console.log("Testing e-commerce API client...");

const shopClient = new EcommerceAPIClient();

// Test 1: Browse products
console.log("\n=== Test 1: Browse Products ===");
shopClient.getProducts()
    .then(products => {
        console.log('🛍️ Available products:', products);
    });

// Test 2: Filter products by category
console.log("\n=== Test 2: Filter Products ===");
shopClient.getProducts({ category: 'Electronics' })
    .then(products => {
        console.log('📱 Electronics:', products);
    });

// Test 3: Add items to cart
console.log("\n=== Test 3: Add to Cart ===");
shopClient.addToCart(1, 2) // Add 2 laptops
    .then(cart => {
        console.log('🛒 Cart after adding laptops:', cart);
        return shopClient.addToCart(2, 1); // Add 1 smartphone
    })
    .then(cart => {
        console.log('🛒 Cart after adding smartphone:', cart);
    });

// Test 4: Update cart item
console.log("\n=== Test 4: Update Cart Item ===");
shopClient.updateCartItem(1, 1) // Change laptops quantity to 1
    .then(cart => {
        console.log('🛒 Updated cart:', cart);
    });

// Test 5: Remove from cart
console.log("\n=== Test 5: Remove from Cart ===");
shopClient.removeFromCart(2) // Remove smartphone
    .then(cart => {
        console.log('🛒 Cart after removing smartphone:', cart);
    });

// Test 6: Create order
console.log("\n=== Test 6: Create Order ===");
shopClient.createOrder({
    items: [{ id: 1, quantity: 1 }],
    shippingAddress: '123 Main St, City, Country',
    paymentMethod: 'credit_card'
})
.then(order => {
    console.log('📦 Created order:', order);
});

// Test 7: Get order history
console.log("\n=== Test 7: Order History ===");
shopClient.getOrders()
    .then(orders => {
        console.log('📋 Order history:', orders);
    });

console.log("\n=== E-commerce API Integration Summary ===");
console.log("✓ E-commerce API client with product management");
console.log("✓ Shopping cart operations (add, remove, update)");
console.log("✓ Order creation and management");
console.log("✓ Product filtering and search capabilities");
console.log("✓ Session-based cart persistence");
console.log("✓ RESTful API design patterns");
console.log("✓ Real-world e-commerce functionality");
