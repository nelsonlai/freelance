// Exercise 2: HTTP Request Manager
// This exercise demonstrates building a comprehensive HTTP request manager

console.log("=== Exercise 2: HTTP Request Manager ===");

// HTTP Request Manager class
class HTTPRequestManager {
    constructor(baseURL = '', defaultOptions = {}) {
        this.baseURL = baseURL;
        this.defaultOptions = {
            timeout: 10000,
            retries: 3,
            retryDelay: 1000,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            },
            ...defaultOptions
        };
        this.interceptors = {
            request: [],
            response: []
        };
        this.requestQueue = [];
        this.activeRequests = 0;
        this.maxConcurrentRequests = 5;
    }
    
    // Add request interceptor
    addRequestInterceptor(interceptor) {
        this.interceptors.request.push(interceptor);
    }
    
    // Add response interceptor
    addResponseInterceptor(interceptor) {
        this.interceptors.response.push(interceptor);
    }
    
    // Build full URL
    buildURL(endpoint) {
        if (endpoint.startsWith('http')) {
            return endpoint;
        }
        return `${this.baseURL}${endpoint}`;
    }
    
    // Apply request interceptors
    async applyRequestInterceptors(config) {
        let modifiedConfig = { ...config };
        
        for (const interceptor of this.interceptors.request) {
            modifiedConfig = await interceptor(modifiedConfig);
        }
        
        return modifiedConfig;
    }
    
    // Apply response interceptors
    async applyResponseInterceptors(response) {
        let modifiedResponse = response;
        
        for (const interceptor of this.interceptors.response) {
            modifiedResponse = await interceptor(modifiedResponse);
        }
        
        return modifiedResponse;
    }
    
    // Mock fetch with enhanced features
    async mockFetch(url, options = {}) {
        return new Promise((resolve, reject) => {
            console.log(`Making request to: ${url}`);
            console.log('Request options:', options);
            
            // Simulate network delay
            const delay = Math.random() * 1000 + 500;
            
            setTimeout(() => {
                // Simulate different responses
                if (url.includes('/error')) {
                    reject(new Error('Network error'));
                    return;
                }
                
                if (url.includes('/timeout')) {
                    reject(new Error('Request timeout'));
                    return;
                }
                
                if (url.includes('/404')) {
                    resolve(new MockResponse('Not Found', 404, 'Not Found'));
                    return;
                }
                
                if (url.includes('/500')) {
                    resolve(new MockResponse('Server Error', 500, 'Internal Server Error'));
                    return;
                }
                
                // Success response
                const data = {
                    url,
                    method: options.method || 'GET',
                    timestamp: new Date().toISOString(),
                    data: options.body ? JSON.parse(options.body) : null
                };
                
                resolve(new MockResponse(JSON.stringify(data)));
            }, delay);
        });
    }
    
    // Core request method
    async request(endpoint, options = {}) {
        const config = {
            ...this.defaultOptions,
            ...options,
            url: this.buildURL(endpoint)
        };
        
        // Apply request interceptors
        const modifiedConfig = await this.applyRequestInterceptors(config);
        
        // Handle request queue if at max concurrent requests
        if (this.activeRequests >= this.maxConcurrentRequests) {
            return new Promise((resolve, reject) => {
                this.requestQueue.push({ config: modifiedConfig, resolve, reject });
            });
        }
        
        return this.executeRequest(modifiedConfig);
    }
    
    // Execute request with retry logic
    async executeRequest(config) {
        this.activeRequests++;
        
        try {
            const response = await this.requestWithRetry(config);
            const processedResponse = await this.applyResponseInterceptors(response);
            
            this.activeRequests--;
            this.processQueue();
            
            return processedResponse;
            
        } catch (error) {
            this.activeRequests--;
            this.processQueue();
            throw error;
        }
    }
    
    // Request with retry logic
    async requestWithRetry(config) {
        let lastError;
        
        for (let attempt = 1; attempt <= config.retries; attempt++) {
            try {
                console.log(`Attempt ${attempt}/${config.retries} for ${config.url}`);
                
                const response = await this.requestWithTimeout(config);
                
                if (!response.ok) {
                    throw new Error(`HTTP error! status: ${response.status}`);
                }
                
                return response;
                
            } catch (error) {
                lastError = error;
                console.log(`Attempt ${attempt} failed:`, error.message);
                
                if (attempt < config.retries) {
                    const delay = config.retryDelay * Math.pow(2, attempt - 1);
                    console.log(`Retrying in ${delay}ms...`);
                    await this.delay(delay);
                }
            }
        }
        
        throw lastError;
    }
    
    // Request with timeout
    async requestWithTimeout(config) {
        return Promise.race([
            this.mockFetch(config.url, config),
            new Promise((_, reject) => {
                setTimeout(() => reject(new Error('Request timeout')), config.timeout);
            })
        ]);
    }
    
    // Process queued requests
    processQueue() {
        if (this.requestQueue.length > 0 && this.activeRequests < this.maxConcurrentRequests) {
            const { config, resolve, reject } = this.requestQueue.shift();
            this.executeRequest(config).then(resolve).catch(reject);
        }
    }
    
    // Utility methods
    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
    
    // HTTP method shortcuts
    async get(endpoint, options = {}) {
        return this.request(endpoint, { ...options, method: 'GET' });
    }
    
    async post(endpoint, data, options = {}) {
        return this.request(endpoint, {
            ...options,
            method: 'POST',
            body: JSON.stringify(data)
        });
    }
    
    async put(endpoint, data, options = {}) {
        return this.request(endpoint, {
            ...options,
            method: 'PUT',
            body: JSON.stringify(data)
        });
    }
    
    async delete(endpoint, options = {}) {
        return this.request(endpoint, { ...options, method: 'DELETE' });
    }
    
    async patch(endpoint, data, options = {}) {
        return this.request(endpoint, {
            ...options,
            method: 'PATCH',
            body: JSON.stringify(data)
        });
    }
    
    // Batch requests
    async batch(requests) {
        const promises = requests.map(({ endpoint, options }) => 
            this.request(endpoint, options)
        );
        
        return Promise.allSettled(promises);
    }
    
    // Get request statistics
    getStats() {
        return {
            activeRequests: this.activeRequests,
            queuedRequests: this.requestQueue.length,
            maxConcurrentRequests: this.maxConcurrentRequests,
            requestInterceptors: this.interceptors.request.length,
            responseInterceptors: this.interceptors.response.length
        };
    }
}

// Mock response class (reused from previous example)
class MockResponse {
    constructor(data, status = 200, statusText = 'OK') {
        this.data = data;
        this.status = status;
        this.statusText = statusText;
        this.ok = status >= 200 && status < 300;
        this.headers = new Map();
    }
    
    async json() {
        return JSON.parse(this.data);
    }
    
    async text() {
        return this.data;
    }
}

// Test the HTTP Request Manager
console.log("Testing HTTP Request Manager...");

const httpManager = new HTTPRequestManager('https://api.example.com');

// Add request interceptor for logging
httpManager.addRequestInterceptor(async (config) => {
    console.log(`🚀 Request interceptor: ${config.method || 'GET'} ${config.url}`);
    return config;
});

// Add response interceptor for logging
httpManager.addResponseInterceptor(async (response) => {
    console.log(`📥 Response interceptor: ${response.status} ${response.statusText}`);
    return response;
});

// Add authentication interceptor
httpManager.addRequestInterceptor(async (config) => {
    const token = 'your-jwt-token';
    config.headers = {
        ...config.headers,
        'Authorization': `Bearer ${token}`
    };
    return config;
});

// Test 1: Basic GET request
console.log("\n=== Test 1: Basic GET Request ===");
httpManager.get('/users')
    .then(response => response.json())
    .then(data => {
        console.log('GET response:', data);
    })
    .catch(error => {
        console.error('GET error:', error.message);
    });

// Test 2: POST request
console.log("\n=== Test 2: POST Request ===");
const userData = {
    name: 'John Doe',
    email: 'john@example.com',
    age: 30
};

httpManager.post('/users', userData)
    .then(response => response.json())
    .then(data => {
        console.log('POST response:', data);
    })
    .catch(error => {
        console.error('POST error:', error.message);
    });

// Test 3: PUT request
console.log("\n=== Test 3: PUT Request ===");
const updatedData = {
    name: 'John Doe Updated',
    email: 'john.updated@example.com',
    age: 31
};

httpManager.put('/users/1', updatedData)
    .then(response => response.json())
    .then(data => {
        console.log('PUT response:', data);
    })
    .catch(error => {
        console.error('PUT error:', error.message);
    });

// Test 4: DELETE request
console.log("\n=== Test 4: DELETE Request ===");
httpManager.delete('/users/1')
    .then(response => {
        console.log('DELETE response:', response.status);
    })
    .catch(error => {
        console.error('DELETE error:', error.message);
    });

// Test 5: Batch requests
console.log("\n=== Test 5: Batch Requests ===");
const batchRequests = [
    { endpoint: '/users', options: { method: 'GET' } },
    { endpoint: '/posts', options: { method: 'GET' } },
    { endpoint: '/comments', options: { method: 'GET' } }
];

httpManager.batch(batchRequests)
    .then(results => {
        console.log('Batch results:');
        results.forEach((result, index) => {
            if (result.status === 'fulfilled') {
                console.log(`Request ${index + 1}: Success`);
            } else {
                console.log(`Request ${index + 1}: Failed - ${result.reason.message}`);
            }
        });
    })
    .catch(error => {
        console.error('Batch error:', error.message);
    });

// Test 6: Error handling
console.log("\n=== Test 6: Error Handling ===");
httpManager.get('/error')
    .then(response => {
        console.log('Unexpected success:', response);
    })
    .catch(error => {
        console.log('Expected error handled:', error.message);
    });

// Test 7: Request statistics
console.log("\n=== Test 7: Request Statistics ===");
setTimeout(() => {
    const stats = httpManager.getStats();
    console.log('HTTP Manager stats:', stats);
}, 2000);

// Test 8: Concurrent request limiting
console.log("\n=== Test 8: Concurrent Request Limiting ===");
const concurrentRequests = Array.from({ length: 8 }, (_, i) => 
    httpManager.get(`/resource/${i}`)
);

Promise.allSettled(concurrentRequests)
    .then(results => {
        console.log(`Completed ${results.length} concurrent requests`);
        const successful = results.filter(r => r.status === 'fulfilled').length;
        console.log(`Successful: ${successful}, Failed: ${results.length - successful}`);
    });

console.log("\n=== HTTP Request Manager Summary ===");
console.log("✓ Comprehensive HTTP request management");
console.log("✓ Request and response interceptors");
console.log("✓ Automatic retry logic with exponential backoff");
console.log("✓ Request timeout handling");
console.log("✓ Concurrent request limiting and queuing");
console.log("✓ Batch request processing");
console.log("✓ Authentication and header management");
console.log("✓ Error handling and logging");
console.log("✓ Request statistics and monitoring");
console.log("✓ Promise-based asynchronous operations");
