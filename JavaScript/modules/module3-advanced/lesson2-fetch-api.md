# Lesson 2: Fetch API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Make GET requests to fetch data from APIs
- Make POST requests to send data to servers
- Handle different response formats (JSON, text, blob)
- Manage HTTP status codes and errors
- Use fetch with async/await for cleaner code
- Implement proper error handling for network requests

## 📚 What is the Fetch API?

The **Fetch API** provides a modern way to make HTTP requests in JavaScript. It's built into browsers and returns Promises, making it perfect for asynchronous programming.

### Basic GET Request
```javascript
fetch('https://api.example.com/data')
    .then(response => response.json())
    .then(data => console.log(data))
    .catch(error => console.log('Error:', error));
```

### Using Async/Await
```javascript
async function fetchData() {
    try {
        const response = await fetch('https://api.example.com/data');
        const data = await response.json();
        console.log(data);
    } catch (error) {
        console.log('Error:', error);
    }
}
```

## 📥 Making Different Types of Requests

### GET Request
```javascript
async function getUsers() {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/users');
        const users = await response.json();
        return users;
    } catch (error) {
        console.log('Error fetching users:', error);
    }
}
```

### POST Request
```javascript
async function createUser(userData) {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/users', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(userData)
        });
        
        const newUser = await response.json();
        return newUser;
    } catch (error) {
        console.log('Error creating user:', error);
    }
}
```

### PUT Request
```javascript
async function updateUser(userId, userData) {
    try {
        const response = await fetch(`https://jsonplaceholder.typicode.com/users/${userId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(userData)
        });
        
        const updatedUser = await response.json();
        return updatedUser;
    } catch (error) {
        console.log('Error updating user:', error);
    }
}
```

### DELETE Request
```javascript
async function deleteUser(userId) {
    try {
        const response = await fetch(`https://jsonplaceholder.typicode.com/users/${userId}`, {
            method: 'DELETE'
        });
        
        if (response.ok) {
            console.log('User deleted successfully');
        } else {
            console.log('Failed to delete user');
        }
    } catch (error) {
        console.log('Error deleting user:', error);
    }
}
```

## 🔍 Handling Different Response Types

### JSON Response
```javascript
const response = await fetch('/api/data');
const data = await response.json();
```

### Text Response
```javascript
const response = await fetch('/api/text');
const text = await response.text();
```

### Blob Response (for files)
```javascript
const response = await fetch('/api/image');
const blob = await response.blob();
const imageUrl = URL.createObjectURL(blob);
```

## 🚨 Error Handling

### Checking Response Status
```javascript
async function fetchData() {
    try {
        const response = await fetch('https://api.example.com/data');
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const data = await response.json();
        return data;
    } catch (error) {
        console.log('Error:', error.message);
    }
}
```

### Handling Different Error Types
```javascript
async function robustFetch(url) {
    try {
        const response = await fetch(url);
        
        if (response.status === 404) {
            throw new Error('Resource not found');
        } else if (response.status === 500) {
            throw new Error('Server error');
        } else if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        return await response.json();
    } catch (error) {
        if (error.name === 'TypeError') {
            console.log('Network error:', error.message);
        } else {
            console.log('API error:', error.message);
        }
        throw error;
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: Fetch User Data
Create a function that fetches user data from an API:

**Solution:**
```javascript
async function fetchUser(userId) {
    try {
        const response = await fetch(`https://jsonplaceholder.typicode.com/users/${userId}`);
        
        if (!response.ok) {
            throw new Error(`User not found: ${response.status}`);
        }
        
        const user = await response.json();
        return user;
    } catch (error) {
        console.log('Error fetching user:', error.message);
        return null;
    }
}

// Usage
fetchUser(1).then(user => {
    if (user) {
        console.log('User:', user.name, user.email);
    }
});
```

### Exercise 2: Create a Post
Create a function that posts data to an API:

**Solution:**
```javascript
async function createPost(postData) {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/posts', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(postData)
        });
        
        if (!response.ok) {
            throw new Error(`Failed to create post: ${response.status}`);
        }
        
        const newPost = await response.json();
        return newPost;
    } catch (error) {
        console.log('Error creating post:', error.message);
        return null;
    }
}

// Usage
const postData = {
    title: 'My New Post',
    body: 'This is the content of my post',
    userId: 1
};

createPost(postData).then(post => {
    if (post) {
        console.log('Post created:', post.id);
    }
});
```

### Exercise 3: Fetch Multiple Resources
Create a function that fetches multiple resources in parallel:

**Solution:**
```javascript
async function fetchMultipleResources() {
    try {
        const [usersResponse, postsResponse, commentsResponse] = await Promise.all([
            fetch('https://jsonplaceholder.typicode.com/users'),
            fetch('https://jsonplaceholder.typicode.com/posts'),
            fetch('https://jsonplaceholder.typicode.com/comments')
        ]);
        
        const [users, posts, comments] = await Promise.all([
            usersResponse.json(),
            postsResponse.json(),
            commentsResponse.json()
        ]);
        
        return { users, posts, comments };
    } catch (error) {
        console.log('Error fetching resources:', error.message);
        return null;
    }
}

// Usage
fetchMultipleResources().then(data => {
    if (data) {
        console.log('Users:', data.users.length);
        console.log('Posts:', data.posts.length);
        console.log('Comments:', data.comments.length);
    }
});
```

## 🎯 Key Takeaways

1. **Fetch API** is the modern way to make HTTP requests
2. **GET requests** fetch data from servers
3. **POST requests** send data to servers
4. **Response methods** parse different data types
5. **Error handling** is crucial for robust applications
6. **Async/await** makes fetch code more readable

## 🚀 Next Steps

Great! You now understand the Fetch API. In the next lesson, we'll learn about:

- **REST API concepts** - understanding API design
- **HTTP methods** - GET, POST, PUT, DELETE
- **API endpoints** - how to structure requests

## 📚 Additional Resources

- [MDN Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
- [Fetch API Guide](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API/Using_Fetch)
- [JSONPlaceholder API](https://jsonplaceholder.typicode.com/)

## 🎉 Congratulations!

You've mastered the Fetch API! You now know how to:

- Make HTTP requests to APIs
- Handle different response types
- Implement proper error handling
- Use async/await with fetch

Practice with the exercises, and get ready for Lesson 3 where we'll learn about REST API concepts!

---

**Next Lesson**: [Lesson 3: APIs & REST Concepts](./lesson3-apis-rest.md)
