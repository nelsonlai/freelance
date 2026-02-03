# Lesson 3: Promises & Async/Await Patterns

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use advanced Promise methods (allSettled, any, race)
- Implement proper async/await error handling
- Execute promises in parallel vs sequential
- Create reusable async utilities
- Handle race conditions and timeouts
- Build robust asynchronous applications

## 📚 Advanced Promise Methods

### Promise.allSettled
```javascript
// Waits for all promises to complete (success or failure)
const promises = [
    fetch('/api/users'),
    fetch('/api/posts'),
    fetch('/api/comments')
];

Promise.allSettled(promises)
    .then(results => {
        results.forEach((result, index) => {
            if (result.status === 'fulfilled') {
                console.log(`Promise ${index} succeeded:`, result.value);
            } else {
                console.log(`Promise ${index} failed:`, result.reason);
            }
        });
    });
```

### Promise.any
```javascript
// Resolves with first successful promise
const promises = [
    fetch('/api/primary'),
    fetch('/api/backup1'),
    fetch('/api/backup2')
];

Promise.any(promises)
    .then(result => {
        console.log('First successful response:', result);
    })
    .catch(errors => {
        console.log('All promises failed:', errors);
    });
```

## ⚡ Async/Await Patterns

### Parallel Execution
```javascript
// Sequential (slow)
async function fetchSequential() {
    const user = await fetch('/api/user');
    const posts = await fetch('/api/posts');
    const comments = await fetch('/api/comments');
    
    return { user, posts, comments };
}

// Parallel (fast)
async function fetchParallel() {
    const [user, posts, comments] = await Promise.all([
        fetch('/api/user'),
        fetch('/api/posts'),
        fetch('/api/comments')
    ]);
    
    return { user, posts, comments };
}
```

### Error Handling Patterns
```javascript
// Pattern 1: Try-catch with individual handling
async function fetchWithRetry(url, retries = 3) {
    for (let i = 0; i < retries; i++) {
        try {
            const response = await fetch(url);
            if (!response.ok) throw new Error(`HTTP ${response.status}`);
            return await response.json();
        } catch (error) {
            if (i === retries - 1) throw error;
            await new Promise(resolve => setTimeout(resolve, 1000 * (i + 1)));
        }
    }
}

// Pattern 2: Wrapper function
async function safeAsync(fn) {
    try {
        return { data: await fn(), error: null };
    } catch (error) {
        return { data: null, error };
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: API Data Aggregator
Create a function that fetches data from multiple APIs:

**Solution:**
```javascript
class ApiAggregator {
    constructor(baseUrl) {
        this.baseUrl = baseUrl;
    }
    
    async fetchUserData(userId) {
        const [user, posts, followers] = await Promise.allSettled([
            this.fetchUser(userId),
            this.fetchUserPosts(userId),
            this.fetchUserFollowers(userId)
        ]);
        
        return {
            user: user.status === 'fulfilled' ? user.value : null,
            posts: posts.status === 'fulfilled' ? posts.value : [],
            followers: followers.status === 'fulfilled' ? followers.value : [],
            errors: [user, posts, followers]
                .filter(result => result.status === 'rejected')
                .map(result => result.reason)
        };
    }
    
    async fetchUser(userId) {
        const response = await fetch(`${this.baseUrl}/users/${userId}`);
        if (!response.ok) throw new Error(`User ${userId} not found`);
        return response.json();
    }
    
    async fetchUserPosts(userId) {
        const response = await fetch(`${this.baseUrl}/users/${userId}/posts`);
        if (!response.ok) throw new Error(`Posts for user ${userId} not found`);
        return response.json();
    }
    
    async fetchUserFollowers(userId) {
        const response = await fetch(`${this.baseUrl}/users/${userId}/followers`);
        if (!response.ok) throw new Error(`Followers for user ${userId} not found`);
        return response.json();
    }
}

// Usage
const aggregator = new ApiAggregator('https://api.example.com');
aggregator.fetchUserData(123).then(data => {
    console.log('User data:', data);
});
```

### Exercise 2: Timeout Wrapper
Create a utility that adds timeout to async operations:

**Solution:**
```javascript
function withTimeout(promise, timeoutMs) {
    const timeoutPromise = new Promise((_, reject) => {
        setTimeout(() => reject(new Error('Operation timed out')), timeoutMs);
    });
    
    return Promise.race([promise, timeoutPromise]);
}

// Usage
async function fetchWithTimeout(url, timeout = 5000) {
    try {
        const response = await withTimeout(fetch(url), timeout);
        return await response.json();
    } catch (error) {
        if (error.message === 'Operation timed out') {
            console.log('Request timed out');
        } else {
            console.log('Request failed:', error.message);
        }
        throw error;
    }
}

// Example
fetchWithTimeout('https://api.example.com/slow-endpoint', 3000)
    .then(data => console.log('Data:', data))
    .catch(error => console.log('Error:', error.message));
```

## 🎯 Key Takeaways

1. **Promise.allSettled** waits for all promises to complete
2. **Promise.any** resolves with first successful promise
3. **Parallel execution** is faster than sequential
4. **Error handling** patterns make async code robust
5. **Timeout wrappers** prevent hanging operations

## 🚀 Next Steps

Great! You now understand advanced Promise patterns. In the next lesson, we'll learn about:

- **Iterators** - custom iteration behavior
- **Generators** - functions that can pause and resume
- **Symbol.iterator** - making objects iterable

---

**Next Lesson**: [Lesson 4: Iterators & Generators](./lesson4-iterators-generators.md)
