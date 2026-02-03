// Exercise 3: Social Media API Client
// This exercise demonstrates building a social media API client with advanced features

console.log("=== Exercise 3: Social Media API Client ===");

// Social Media API Client
class SocialMediaAPIClient {
    constructor(baseURL = 'https://api.social.com') {
        this.baseURL = baseURL;
        this.userToken = null;
        this.following = new Set();
        this.likedPosts = new Set();
    }
    
    // Authentication
    async login(username, password) {
        console.log(`🔐 Logging in user: ${username}`);
        
        // Mock authentication
        return new Promise((resolve) => {
            setTimeout(() => {
                this.userToken = 'token_' + Date.now();
                console.log('✅ Login successful');
                resolve({ token: this.userToken, user: { username, id: 1 } });
            }, 500);
        });
    }
    
    logout() {
        this.userToken = null;
        this.following.clear();
        this.likedPosts.clear();
        console.log('👋 Logged out');
    }
    
    // Mock API responses
    async mockRequest(endpoint, method = 'GET', data = null) {
        console.log(`📱 ${method} ${endpoint}`);
        
        return new Promise((resolve) => {
            setTimeout(() => {
                const response = this.generateSocialResponse(endpoint, method, data);
                resolve({
                    ok: true,
                    status: 200,
                    json: () => Promise.resolve(response)
                });
            }, 300);
        });
    }
    
    generateSocialResponse(endpoint, method, data) {
        if (endpoint.includes('/feed')) {
            return {
                posts: [
                    { id: 1, author: 'alice', content: 'Just finished a great JavaScript course!', likes: 15, comments: 3 },
                    { id: 2, author: 'bob', content: 'Beautiful sunset today 🌅', likes: 8, comments: 1 },
                    { id: 3, author: 'charlie', content: 'Working on a new project', likes: 12, comments: 5 }
                ],
                hasMore: true
            };
        }
        
        if (endpoint.includes('/posts')) {
            if (method === 'POST') {
                return {
                    id: Date.now(),
                    ...JSON.parse(data),
                    likes: 0,
                    comments: 0,
                    createdAt: new Date().toISOString()
                };
            }
        }
        
        if (endpoint.includes('/users')) {
            return {
                users: [
                    { id: 1, username: 'alice', followers: 150, following: 75 },
                    { id: 2, username: 'bob', followers: 200, following: 100 },
                    { id: 3, username: 'charlie', followers: 80, following: 50 }
                ]
            };
        }
        
        return { message: 'Success' };
    }
    
    // Feed operations
    async getFeed(page = 1, limit = 10) {
        const response = await this.mockRequest(`/feed?page=${page}&limit=${limit}`);
        return response.json();
    }
    
    // Post operations
    async createPost(content, imageUrl = null) {
        const postData = {
            content,
            imageUrl,
            author: 'current_user'
        };
        
        const response = await this.mockRequest('/posts', 'POST', JSON.stringify(postData));
        return response.json();
    }
    
    async likePost(postId) {
        if (this.likedPosts.has(postId)) {
            this.likedPosts.delete(postId);
            console.log(`👎 Unliked post ${postId}`);
        } else {
            this.likedPosts.add(postId);
            console.log(`👍 Liked post ${postId}`);
        }
        
        const response = await this.mockRequest(`/posts/${postId}/like`, 'POST');
        return response.json();
    }
    
    async commentOnPost(postId, comment) {
        const response = await this.mockRequest(`/posts/${postId}/comments`, 'POST', JSON.stringify({ comment }));
        return response.json();
    }
    
    // User operations
    async searchUsers(query) {
        const response = await this.mockRequest(`/users/search?q=${query}`);
        return response.json();
    }
    
    async followUser(userId) {
        this.following.add(userId);
        console.log(`👥 Following user ${userId}`);
        
        const response = await this.mockRequest(`/users/${userId}/follow`, 'POST');
        return response.json();
    }
    
    async unfollowUser(userId) {
        this.following.delete(userId);
        console.log(`👥 Unfollowed user ${userId}`);
        
        const response = await this.mockRequest(`/users/${userId}/unfollow`, 'POST');
        return response.json();
    }
    
    async getUserProfile(userId) {
        const response = await this.mockRequest(`/users/${userId}`);
        return response.json();
    }
    
    // Notifications
    async getNotifications() {
        const response = await this.mockRequest('/notifications');
        return response.json();
    }
    
    // Analytics
    async getPostAnalytics(postId) {
        const response = await this.mockRequest(`/posts/${postId}/analytics`);
        return response.json();
    }
    
    // Get user stats
    getUserStats() {
        return {
            following: this.following.size,
            likedPosts: this.likedPosts.size,
            isLoggedIn: !!this.userToken
        };
    }
}

// Test the social media API client
console.log("Testing social media API client...");

const socialClient = new SocialMediaAPIClient();

// Test 1: Login
console.log("\n=== Test 1: User Login ===");
socialClient.login('john_doe', 'password123')
    .then(auth => {
        console.log('🔐 Authentication result:', auth);
    });

// Test 2: Get feed
console.log("\n=== Test 2: Get Feed ===");
socialClient.getFeed()
    .then(feed => {
        console.log('📱 Feed:', feed);
    });

// Test 3: Create post
console.log("\n=== Test 3: Create Post ===");
socialClient.createPost('Just learned about REST APIs! 🚀')
    .then(post => {
        console.log('📝 Created post:', post);
    });

// Test 4: Like and comment on posts
console.log("\n=== Test 4: Interact with Posts ===");
socialClient.likePost(1)
    .then(() => {
        return socialClient.commentOnPost(1, 'Great post!');
    })
    .then(comment => {
        console.log('💬 Added comment:', comment);
    });

// Test 5: Search and follow users
console.log("\n=== Test 5: User Management ===");
socialClient.searchUsers('alice')
    .then(users => {
        console.log('🔍 Search results:', users);
        return socialClient.followUser(1);
    })
    .then(() => {
        console.log('👥 Followed user');
    });

// Test 6: Get notifications
console.log("\n=== Test 6: Notifications ===");
socialClient.getNotifications()
    .then(notifications => {
        console.log('🔔 Notifications:', notifications);
    });

// Test 7: User stats
console.log("\n=== Test 7: User Stats ===");
const stats = socialClient.getUserStats();
console.log('📊 User stats:', stats);

// Test 8: Logout
console.log("\n=== Test 8: Logout ===");
socialClient.logout();
console.log('👋 User logged out');

console.log("\n=== Social Media API Client Summary ===");
console.log("✓ Social media API client with authentication");
console.log("✓ Feed management and post creation");
console.log("✓ User interactions (like, comment, follow)");
console.log("✓ User search and profile management");
console.log("✓ Notification system");
console.log("✓ Analytics and statistics");
console.log("✓ Session management and logout");
console.log("✓ Real-world social media functionality");
