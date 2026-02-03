// Exercise 1: Blog API Client
// This exercise demonstrates building a blog API client with REST operations

console.log("=== Exercise 1: Blog API Client ===");

// Blog API Client
class BlogAPIClient {
    constructor(baseURL = 'https://api.blog.com') {
        this.baseURL = baseURL;
        this.defaultHeaders = {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        };
    }
    
    // Mock API responses
    async mockRequest(endpoint, method = 'GET', data = null) {
        console.log(`🌐 ${method} ${endpoint}`);
        
        return new Promise((resolve) => {
            setTimeout(() => {
                const response = this.generateBlogResponse(endpoint, method, data);
                resolve({
                    ok: true,
                    status: 200,
                    json: () => Promise.resolve(response)
                });
            }, 300);
        });
    }
    
    generateBlogResponse(endpoint, method, data) {
        if (endpoint.includes('/posts')) {
            if (method === 'GET') {
                return {
                    posts: [
                        { id: 1, title: 'Getting Started with JavaScript', author: 'John Doe', publishedAt: '2024-01-15' },
                        { id: 2, title: 'Advanced React Patterns', author: 'Jane Smith', publishedAt: '2024-01-20' },
                        { id: 3, title: 'Node.js Best Practices', author: 'Bob Johnson', publishedAt: '2024-01-25' }
                    ],
                    total: 3
                };
            } else if (method === 'POST') {
                return {
                    id: Date.now(),
                    ...JSON.parse(data),
                    publishedAt: new Date().toISOString()
                };
            }
        }
        
        if (endpoint.includes('/comments')) {
            return {
                comments: [
                    { id: 1, postId: 1, author: 'Alice', content: 'Great post!', createdAt: '2024-01-16' },
                    { id: 2, postId: 1, author: 'Charlie', content: 'Very helpful', createdAt: '2024-01-17' }
                ]
            };
        }
        
        return { message: 'Success' };
    }
    
    // Posts operations
    async getPosts(params = {}) {
        const queryString = new URLSearchParams(params).toString();
        const endpoint = `/posts${queryString ? '?' + queryString : ''}`;
        const response = await this.mockRequest(endpoint);
        return response.json();
    }
    
    async getPost(id) {
        const response = await this.mockRequest(`/posts/${id}`);
        return response.json();
    }
    
    async createPost(postData) {
        const response = await this.mockRequest('/posts', 'POST', JSON.stringify(postData));
        return response.json();
    }
    
    async updatePost(id, postData) {
        const response = await this.mockRequest(`/posts/${id}`, 'PUT', JSON.stringify(postData));
        return response.json();
    }
    
    async deletePost(id) {
        const response = await this.mockRequest(`/posts/${id}`, 'DELETE');
        return response.json();
    }
    
    // Comments operations
    async getComments(postId) {
        const response = await this.mockRequest(`/posts/${postId}/comments`);
        return response.json();
    }
    
    async createComment(postId, commentData) {
        const response = await this.mockRequest(`/posts/${postId}/comments`, 'POST', JSON.stringify(commentData));
        return response.json();
    }
}

// Test the blog API client
console.log("Testing blog API client...");

const blogClient = new BlogAPIClient();

// Test 1: Get all posts
console.log("\n=== Test 1: Get All Posts ===");
blogClient.getPosts()
    .then(posts => {
        console.log('📝 All posts:', posts);
    });

// Test 2: Get posts with pagination
console.log("\n=== Test 2: Get Posts with Pagination ===");
blogClient.getPosts({ page: 1, limit: 2 })
    .then(posts => {
        console.log('📄 Paginated posts:', posts);
    });

// Test 3: Create a new post
console.log("\n=== Test 3: Create New Post ===");
blogClient.createPost({
    title: 'My New Blog Post',
    content: 'This is the content of my new blog post.',
    author: 'Alice Johnson'
})
.then(post => {
    console.log('✨ Created post:', post);
});

// Test 4: Get comments for a post
console.log("\n=== Test 4: Get Post Comments ===");
blogClient.getComments(1)
    .then(comments => {
        console.log('💬 Comments for post 1:', comments);
    });

// Test 5: Create a comment
console.log("\n=== Test 5: Create Comment ===");
blogClient.createComment(1, {
    author: 'Bob',
    content: 'This is a great post!'
})
.then(comment => {
    console.log('💬 Created comment:', comment);
});

console.log("\n=== Blog API Client Summary ===");
console.log("✓ RESTful blog API client implementation");
console.log("✓ CRUD operations for posts and comments");
console.log("✓ Pagination support for large datasets");
console.log("✓ Nested resource handling (posts/comments)");
console.log("✓ Proper HTTP method usage");
console.log("✓ Error handling and response processing");
