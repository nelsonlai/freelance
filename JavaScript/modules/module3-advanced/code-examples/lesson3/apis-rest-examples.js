// Lesson 3: APIs & REST Concepts Examples
// This lesson demonstrates REST API principles and HTTP methods

console.log("=== APIs & REST Concepts Examples ===");

// REST API Client class
class RESTAPIClient {
    constructor(baseURL) {
        this.baseURL = baseURL;
        this.defaultHeaders = {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        };
    }
    
    // Build full URL
    buildURL(endpoint) {
        if (endpoint.startsWith('http')) {
            return endpoint;
        }
        return `${this.baseURL}${endpoint}`;
    }
    
    // Build query string from parameters
    buildQueryString(params) {
        if (!params || Object.keys(params).length === 0) {
            return '';
        }
        
        const searchParams = new URLSearchParams();
        Object.keys(params).forEach(key => {
            const value = params[key];
            if (value !== null && value !== undefined) {
                if (Array.isArray(value)) {
                    value.forEach(item => searchParams.append(key, item));
                } else {
                    searchParams.append(key, value);
                }
            }
        });
        
        return searchParams.toString();
    }
    
    // Build URL with query parameters
    buildURLWithParams(endpoint, params = {}) {
        const url = this.buildURL(endpoint);
        const queryString = this.buildQueryString(params);
        
        if (queryString) {
            return `${url}?${queryString}`;
        }
        
        return url;
    }
    
    // Mock HTTP request
    async mockRequest(url, options = {}) {
        console.log(`🌐 ${options.method || 'GET'} ${url}`);
        
        if (options.body) {
            console.log('📤 Request body:', options.body);
        }
        
        return new Promise((resolve, reject) => {
            setTimeout(() => {
                // Simulate different responses based on URL and method
                if (url.includes('/error')) {
                    reject(new Error('Network error'));
                    return;
                }
                
                if (url.includes('/404')) {
                    resolve({
                        ok: false,
                        status: 404,
                        statusText: 'Not Found',
                        json: () => Promise.resolve({ error: 'Resource not found' })
                    });
                    return;
                }
                
                if (url.includes('/500')) {
                    resolve({
                        ok: false,
                        status: 500,
                        statusText: 'Internal Server Error',
                        json: () => Promise.resolve({ error: 'Server error' })
                    });
                    return;
                }
                
                // Success response
                const responseData = this.generateMockResponse(url, options);
                resolve({
                    ok: true,
                    status: 200,
                    statusText: 'OK',
                    json: () => Promise.resolve(responseData)
                });
            }, Math.random() * 500 + 200);
        });
    }
    
    // Generate mock response based on endpoint and method
    generateMockResponse(url, options) {
        const method = options.method || 'GET';
        
        if (url.includes('/users')) {
            if (method === 'GET') {
                return {
                    users: [
                        { id: 1, name: 'John Doe', email: 'john@example.com' },
                        { id: 2, name: 'Jane Smith', email: 'jane@example.com' },
                        { id: 3, name: 'Bob Johnson', email: 'bob@example.com' }
                    ],
                    total: 3,
                    page: 1,
                    limit: 10
                };
            } else if (method === 'POST') {
                const body = JSON.parse(options.body || '{}');
                return {
                    id: Date.now(),
                    ...body,
                    createdAt: new Date().toISOString()
                };
            } else if (method === 'PUT' || method === 'PATCH') {
                const body = JSON.parse(options.body || '{}');
                return {
                    id: parseInt(url.split('/').pop()),
                    ...body,
                    updatedAt: new Date().toISOString()
                };
            } else if (method === 'DELETE') {
                return { message: 'User deleted successfully' };
            }
        }
        
        if (url.includes('/posts')) {
            return {
                posts: [
                    { id: 1, title: 'Post 1', content: 'Content 1', userId: 1 },
                    { id: 2, title: 'Post 2', content: 'Content 2', userId: 2 }
                ]
            };
        }
        
        return { message: 'Success', timestamp: new Date().toISOString() };
    }
    
    // GET request
    async get(endpoint, params = {}) {
        const url = this.buildURLWithParams(endpoint, params);
        const response = await this.mockRequest(url, {
            method: 'GET',
            headers: this.defaultHeaders
        });
        
        if (!response.ok) {
            throw new Error(`HTTP ${response.status}: ${response.statusText}`);
        }
        
        return response.json();
    }
    
    // POST request
    async post(endpoint, data) {
        const url = this.buildURL(endpoint);
        const response = await this.mockRequest(url, {
            method: 'POST',
            headers: this.defaultHeaders,
            body: JSON.stringify(data)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP ${response.status}: ${response.statusText}`);
        }
        
        return response.json();
    }
    
    // PUT request
    async put(endpoint, data) {
        const url = this.buildURL(endpoint);
        const response = await this.mockRequest(url, {
            method: 'PUT',
            headers: this.defaultHeaders,
            body: JSON.stringify(data)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP ${response.status}: ${response.statusText}`);
        }
        
        return response.json();
    }
    
    // PATCH request
    async patch(endpoint, data) {
        const url = this.buildURL(endpoint);
        const response = await this.mockRequest(url, {
            method: 'PATCH',
            headers: this.defaultHeaders,
            body: JSON.stringify(data)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP ${response.status}: ${response.statusText}`);
        }
        
        return response.json();
    }
    
    // DELETE request
    async delete(endpoint) {
        const url = this.buildURL(endpoint);
        const response = await this.mockRequest(url, {
            method: 'DELETE',
            headers: this.defaultHeaders
        });
        
        if (!response.ok) {
            throw new Error(`HTTP ${response.status}: ${response.statusText}`);
        }
        
        return response.json();
    }
}

// Example 1: Basic REST Operations
console.log("\n=== Example 1: Basic REST Operations ===");

const apiClient = new RESTAPIClient('https://api.example.com');

// GET - Retrieve all users
async function getAllUsers() {
    try {
        const response = await apiClient.get('/users');
        console.log('📥 GET /users:', response);
        return response;
    } catch (error) {
        console.error('❌ Error fetching users:', error.message);
        return null;
    }
}

// POST - Create a new user
async function createUser(userData) {
    try {
        const response = await apiClient.post('/users', userData);
        console.log('📤 POST /users:', response);
        return response;
    } catch (error) {
        console.error('❌ Error creating user:', error.message);
        return null;
    }
}

// PUT - Update a user
async function updateUser(userId, userData) {
    try {
        const response = await apiClient.put(`/users/${userId}`, userData);
        console.log('🔄 PUT /users/:id:', response);
        return response;
    } catch (error) {
        console.error('❌ Error updating user:', error.message);
        return null;
    }
}

// DELETE - Delete a user
async function deleteUser(userId) {
    try {
        const response = await apiClient.delete(`/users/${userId}`);
        console.log('🗑️ DELETE /users/:id:', response);
        return response;
    } catch (error) {
        console.error('❌ Error deleting user:', error.message);
        return null;
    }
}

// Test basic operations
getAllUsers();
createUser({ name: 'Alice Johnson', email: 'alice@example.com' });
updateUser(1, { name: 'John Doe Updated', email: 'john.updated@example.com' });
deleteUser(2);

// Example 2: Query Parameters
console.log("\n=== Example 2: Query Parameters ===");

async function getUsersWithParams() {
    const params = {
        page: 1,
        limit: 5,
        sort: 'name',
        order: 'asc',
        search: 'john',
        status: ['active', 'pending'],
        include: 'profile'
    };
    
    try {
        const response = await apiClient.get('/users', params);
        console.log('📥 GET /users with params:', response);
        return response;
    } catch (error) {
        console.error('❌ Error with params:', error.message);
        return null;
    }
}

getUsersWithParams();

// Example 3: Nested Resources
console.log("\n=== Example 3: Nested Resources ===");

async function getUserPosts(userId) {
    try {
        const response = await apiClient.get(`/users/${userId}/posts`);
        console.log(`📥 GET /users/${userId}/posts:`, response);
        return response;
    } catch (error) {
        console.error('❌ Error fetching user posts:', error.message);
        return null;
    }
}

async function createUserPost(userId, postData) {
    try {
        const response = await apiClient.post(`/users/${userId}/posts`, postData);
        console.log(`📤 POST /users/${userId}/posts:`, response);
        return response;
    } catch (error) {
        console.error('❌ Error creating user post:', error.message);
        return null;
    }
}

getUserPosts(1);
createUserPost(1, { title: 'New Post', content: 'Post content' });

// Example 4: Error Handling
console.log("\n=== Example 4: Error Handling ===");

async function handleErrors() {
    try {
        // This will cause a 404 error
        await apiClient.get('/users/999');
    } catch (error) {
        console.log('✅ Caught 404 error:', error.message);
    }
    
    try {
        // This will cause a 500 error
        await apiClient.get('/users/500');
    } catch (error) {
        console.log('✅ Caught 500 error:', error.message);
    }
    
    try {
        // This will cause a network error
        await apiClient.get('/error');
    } catch (error) {
        console.log('✅ Caught network error:', error.message);
    }
}

handleErrors();

// Example 5: Batch Operations
console.log("\n=== Example 5: Batch Operations ===");

async function batchOperations() {
    try {
        // Execute multiple requests concurrently
        const [users, posts] = await Promise.all([
            apiClient.get('/users'),
            apiClient.get('/posts')
        ]);
        
        console.log('📥 Batch GET results:');
        console.log('Users:', users);
        console.log('Posts:', posts);
        
        return { users, posts };
    } catch (error) {
        console.error('❌ Batch operation failed:', error.message);
        return null;
    }
}

batchOperations();

// Example 6: Pagination
console.log("\n=== Example 6: Pagination ===");

class PaginatedAPI {
    constructor(apiClient, endpoint) {
        this.apiClient = apiClient;
        this.endpoint = endpoint;
        this.currentPage = 1;
        this.pageSize = 10;
        this.totalPages = null;
    }
    
    async getPage(page = 1) {
        const params = {
            page,
            limit: this.pageSize
        };
        
        try {
            const response = await this.apiClient.get(this.endpoint, params);
            this.currentPage = page;
            this.totalPages = Math.ceil(response.total / this.pageSize);
            
            console.log(`📄 Page ${page}/${this.totalPages}:`, response);
            return response;
        } catch (error) {
            console.error(`❌ Error fetching page ${page}:`, error.message);
            return null;
        }
    }
    
    async nextPage() {
        if (this.currentPage < this.totalPages) {
            return this.getPage(this.currentPage + 1);
        }
        console.log('📄 No more pages available');
        return null;
    }
    
    async previousPage() {
        if (this.currentPage > 1) {
            return this.getPage(this.currentPage - 1);
        }
        console.log('📄 Already on first page');
        return null;
    }
    
    async getAllPages() {
        const allData = [];
        let page = 1;
        
        while (true) {
            const response = await this.getPage(page);
            if (!response) break;
            
            allData.push(...response.users || response.posts || []);
            
            if (page >= this.totalPages) break;
            page++;
        }
        
        console.log(`📄 Retrieved all ${allData.length} items across ${this.totalPages} pages`);
        return allData;
    }
}

const paginatedUsers = new PaginatedAPI(apiClient, '/users');
paginatedUsers.getPage(1);

// Example 7: API Response Caching
console.log("\n=== Example 7: API Response Caching ===");

class CachedAPIClient extends RESTAPIClient {
    constructor(baseURL) {
        super(baseURL);
        this.cache = new Map();
        this.cacheTimeout = 5 * 60 * 1000; // 5 minutes
    }
    
    getCacheKey(endpoint, params) {
        const queryString = this.buildQueryString(params);
        return `${endpoint}${queryString ? '?' + queryString : ''}`;
    }
    
    isCacheValid(timestamp) {
        return Date.now() - timestamp < this.cacheTimeout;
    }
    
    async get(endpoint, params = {}) {
        const cacheKey = this.getCacheKey(endpoint, params);
        const cached = this.cache.get(cacheKey);
        
        if (cached && this.isCacheValid(cached.timestamp)) {
            console.log('💾 Using cached response for:', cacheKey);
            return cached.data;
        }
        
        console.log('🌐 Fetching fresh data for:', cacheKey);
        const data = await super.get(endpoint, params);
        
        this.cache.set(cacheKey, {
            data,
            timestamp: Date.now()
        });
        
        return data;
    }
    
    clearCache() {
        this.cache.clear();
        console.log('🗑️ Cache cleared');
    }
    
    getCacheStats() {
        return {
            size: this.cache.size,
            keys: Array.from(this.cache.keys())
        };
    }
}

const cachedClient = new CachedAPIClient('https://api.example.com');

// First request - will fetch from API
cachedClient.get('/users');

// Second request - will use cache
setTimeout(() => {
    cachedClient.get('/users');
    console.log('Cache stats:', cachedClient.getCacheStats());
}, 1000);

// Example 8: API Rate Limiting
console.log("\n=== Example 8: API Rate Limiting ===");

class RateLimitedAPIClient extends RESTAPIClient {
    constructor(baseURL, requestsPerMinute = 60) {
        super(baseURL);
        this.requestsPerMinute = requestsPerMinute;
        this.requestTimes = [];
    }
    
    async waitForRateLimit() {
        const now = Date.now();
        const oneMinuteAgo = now - 60000;
        
        // Remove old request times
        this.requestTimes = this.requestTimes.filter(time => time > oneMinuteAgo);
        
        if (this.requestTimes.length >= this.requestsPerMinute) {
            const oldestRequest = Math.min(...this.requestTimes);
            const waitTime = oldestRequest + 60000 - now;
            
            if (waitTime > 0) {
                console.log(`⏳ Rate limit reached, waiting ${waitTime}ms`);
                await new Promise(resolve => setTimeout(resolve, waitTime));
            }
        }
        
        this.requestTimes.push(now);
    }
    
    async request(endpoint, options = {}) {
        await this.waitForRateLimit();
        return super.request(endpoint, options);
    }
}

const rateLimitedClient = new RateLimitedAPIClient('https://api.example.com', 10);

// Make multiple requests to test rate limiting
for (let i = 0; i < 12; i++) {
    rateLimitedClient.get('/users').catch(error => {
        console.log(`Request ${i + 1} completed`);
    });
}

console.log("\n=== APIs & REST Concepts Summary ===");
console.log("✓ REST API principles and HTTP methods");
console.log("✓ Query parameter building and URL construction");
console.log("✓ CRUD operations (Create, Read, Update, Delete)");
console.log("✓ Nested resource endpoints");
console.log("✓ Error handling and HTTP status codes");
console.log("✓ Batch operations and concurrent requests");
console.log("✓ Pagination for large datasets");
console.log("✓ Response caching for performance");
console.log("✓ Rate limiting for API protection");
console.log("✓ Real-world API integration patterns");
