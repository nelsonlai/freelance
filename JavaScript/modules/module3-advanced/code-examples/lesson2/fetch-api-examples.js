// Lesson 2: Fetch API Examples
// Note: These examples simulate fetch behavior for Node.js
// In a real browser, you would use the actual fetch API

console.log("=== Fetch API Examples ===");
console.log("Note: These examples simulate fetch behavior for Node.js");
console.log("In a real browser, you would use the actual fetch API");

// Mock fetch implementation for Node.js
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
    
    async blob() {
        return new Blob([this.data]);
    }
    
    clone() {
        return new MockResponse(this.data, this.status, this.statusText);
    }
}

// Mock fetch function
function mockFetch(url, options = {}) {
    return new Promise((resolve, reject) => {
        console.log(`Fetching: ${url}`);
        console.log('Options:', options);
        
        // Simulate network delay
        setTimeout(() => {
            // Simulate different responses based on URL
            if (url.includes('/users')) {
                const users = [
                    { id: 1, name: 'John Doe', email: 'john@example.com' },
                    { id: 2, name: 'Jane Smith', email: 'jane@example.com' },
                    { id: 3, name: 'Bob Johnson', email: 'bob@example.com' }
                ];
                resolve(new MockResponse(JSON.stringify(users)));
            } else if (url.includes('/posts')) {
                const posts = [
                    { id: 1, title: 'Post 1', body: 'Content of post 1' },
                    { id: 2, title: 'Post 2', body: 'Content of post 2' }
                ];
                resolve(new MockResponse(JSON.stringify(posts)));
            } else if (url.includes('/error')) {
                reject(new Error('Network error'));
            } else if (url.includes('/404')) {
                resolve(new MockResponse('Not Found', 404, 'Not Found'));
            } else if (url.includes('/500')) {
                resolve(new MockResponse('Server Error', 500, 'Internal Server Error'));
            } else {
                resolve(new MockResponse(JSON.stringify({ message: 'Success' })));
            }
        }, 100);
    });
}

// Example 1: Basic GET Request
console.log("\n=== Example 1: Basic GET Request ===");

async function basicGetRequest() {
    try {
        const response = await mockFetch('https://api.example.com/users');
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const data = await response.json();
        console.log('Fetched data:', data);
        return data;
    } catch (error) {
        console.error('Error:', error.message);
        return null;
    }
}

// Run basic GET request
basicGetRequest();

// Example 2: GET Request with Error Handling
console.log("\n=== Example 2: GET Request with Error Handling ===");

async function getRequestWithErrorHandling() {
    try {
        const response = await mockFetch('https://api.example.com/users');
        
        // Check if response is ok
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        // Check content type
        const contentType = response.headers.get('content-type');
        if (!contentType || !contentType.includes('application/json')) {
            throw new Error('Response is not JSON');
        }
        
        const data = await response.json();
        console.log('Successfully fetched data:', data);
        return data;
        
    } catch (error) {
        if (error.name === 'TypeError') {
            console.error('Network error:', error.message);
        } else {
            console.error('Request failed:', error.message);
        }
        return null;
    }
}

getRequestWithErrorHandling();

// Example 3: POST Request
console.log("\n=== Example 3: POST Request ===");

async function postRequest() {
    const userData = {
        name: 'Alice Johnson',
        email: 'alice@example.com',
        age: 30
    };
    
    try {
        const response = await mockFetch('https://api.example.com/users', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            },
            body: JSON.stringify(userData)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const result = await response.json();
        console.log('User created:', result);
        return result;
        
    } catch (error) {
        console.error('Error creating user:', error.message);
        return null;
    }
}

postRequest();

// Example 4: PUT Request
console.log("\n=== Example 4: PUT Request ===");

async function putRequest() {
    const updatedData = {
        name: 'Alice Johnson Updated',
        email: 'alice.updated@example.com',
        age: 31
    };
    
    try {
        const response = await mockFetch('https://api.example.com/users/1', {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(updatedData)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const result = await response.json();
        console.log('User updated:', result);
        return result;
        
    } catch (error) {
        console.error('Error updating user:', error.message);
        return null;
    }
}

putRequest();

// Example 5: DELETE Request
console.log("\n=== Example 5: DELETE Request ===");

async function deleteRequest() {
    try {
        const response = await mockFetch('https://api.example.com/users/1', {
            method: 'DELETE'
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        console.log('User deleted successfully');
        return true;
        
    } catch (error) {
        console.error('Error deleting user:', error.message);
        return false;
    }
}

deleteRequest();

// Example 6: Handling Different Response Types
console.log("\n=== Example 6: Handling Different Response Types ===");

async function handleDifferentResponseTypes() {
    try {
        // JSON response
        const jsonResponse = await mockFetch('https://api.example.com/users');
        const jsonData = await jsonResponse.json();
        console.log('JSON data:', jsonData);
        
        // Text response
        const textResponse = await mockFetch('https://api.example.com/text');
        const textData = await textResponse.text();
        console.log('Text data:', textData);
        
        // Blob response (simulated)
        const blobResponse = await mockFetch('https://api.example.com/file');
        const blobData = await blobResponse.blob();
        console.log('Blob data:', blobData);
        
    } catch (error) {
        console.error('Error handling responses:', error.message);
    }
}

handleDifferentResponseTypes();

// Example 7: Request with Query Parameters
console.log("\n=== Example 7: Request with Query Parameters ===");

function buildUrlWithParams(baseUrl, params) {
    const url = new URL(baseUrl);
    Object.keys(params).forEach(key => {
        if (params[key] !== null && params[key] !== undefined) {
            url.searchParams.append(key, params[key]);
        }
    });
    return url.toString();
}

async function requestWithQueryParams() {
    const params = {
        page: 1,
        limit: 10,
        sort: 'name',
        order: 'asc'
    };
    
    const url = buildUrlWithParams('https://api.example.com/users', params);
    
    try {
        const response = await mockFetch(url);
        const data = await response.json();
        console.log('Data with query params:', data);
        return data;
    } catch (error) {
        console.error('Error with query params:', error.message);
        return null;
    }
}

requestWithQueryParams();

// Example 8: Request with Authentication
console.log("\n=== Example 8: Request with Authentication ===");

async function authenticatedRequest() {
    const token = 'your-jwt-token-here';
    
    try {
        const response = await mockFetch('https://api.example.com/protected', {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${token}`,
                'Content-Type': 'application/json'
            }
        });
        
        if (!response.ok) {
            if (response.status === 401) {
                throw new Error('Unauthorized - invalid token');
            }
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const data = await response.json();
        console.log('Authenticated request successful:', data);
        return data;
        
    } catch (error) {
        console.error('Authentication error:', error.message);
        return null;
    }
}

authenticatedRequest();

// Example 9: Concurrent Requests
console.log("\n=== Example 9: Concurrent Requests ===");

async function concurrentRequests() {
    try {
        const [usersResponse, postsResponse] = await Promise.all([
            mockFetch('https://api.example.com/users'),
            mockFetch('https://api.example.com/posts')
        ]);
        
        const [users, posts] = await Promise.all([
            usersResponse.json(),
            postsResponse.json()
        ]);
        
        console.log('Users:', users);
        console.log('Posts:', posts);
        
        return { users, posts };
        
    } catch (error) {
        console.error('Error in concurrent requests:', error.message);
        return null;
    }
}

concurrentRequests();

// Example 10: Request Timeout
console.log("\n=== Example 10: Request Timeout ===");

function fetchWithTimeout(url, options = {}, timeout = 5000) {
    return Promise.race([
        mockFetch(url, options),
        new Promise((_, reject) => {
            setTimeout(() => reject(new Error('Request timeout')), timeout);
        })
    ]);
}

async function requestWithTimeout() {
    try {
        const response = await fetchWithTimeout('https://api.example.com/users', {}, 2000);
        const data = await response.json();
        console.log('Request completed within timeout:', data);
        return data;
    } catch (error) {
        console.error('Request failed or timed out:', error.message);
        return null;
    }
}

requestWithTimeout();

// Example 11: Retry Logic
console.log("\n=== Example 11: Retry Logic ===");

async function fetchWithRetry(url, options = {}, maxRetries = 3) {
    let lastError;
    
    for (let attempt = 1; attempt <= maxRetries; attempt++) {
        try {
            console.log(`Attempt ${attempt}/${maxRetries}`);
            const response = await mockFetch(url, options);
            
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            
            return response;
            
        } catch (error) {
            lastError = error;
            console.log(`Attempt ${attempt} failed:`, error.message);
            
            if (attempt < maxRetries) {
                const delay = Math.pow(2, attempt) * 1000; // Exponential backoff
                console.log(`Retrying in ${delay}ms...`);
                await new Promise(resolve => setTimeout(resolve, delay));
            }
        }
    }
    
    throw lastError;
}

async function retryRequest() {
    try {
        const response = await fetchWithRetry('https://api.example.com/users');
        const data = await response.json();
        console.log('Request succeeded after retries:', data);
        return data;
    } catch (error) {
        console.error('Request failed after all retries:', error.message);
        return null;
    }
}

retryRequest();

console.log("\n=== Fetch API Summary ===");
console.log("✓ Basic GET, POST, PUT, DELETE requests");
console.log("✓ Error handling and status code management");
console.log("✓ Different response types (JSON, text, blob)");
console.log("✓ Query parameters and URL building");
console.log("✓ Authentication with headers");
console.log("✓ Concurrent requests with Promise.all");
console.log("✓ Request timeout handling");
console.log("✓ Retry logic with exponential backoff");
console.log("✓ Async/await for cleaner code");
console.log("✓ Proper error handling patterns");
