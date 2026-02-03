# 6. Web Development & APIs - Building Modern Applications

Web development and APIs are essential for building modern applications. This lesson covers building web applications, working with REST APIs, and using frameworks like Flask and FastAPI for professional development.

## HTTP and REST APIs

### Understanding HTTP

```python
import requests
import json
from urllib.parse import urlencode

# Basic HTTP requests
def basic_http_demo():
    """Demonstrate basic HTTP operations."""
    print("=== Basic HTTP Operations ===")
    
    # GET request
    response = requests.get('https://httpbin.org/get')
    print(f"GET Status: {response.status_code}")
    print(f"GET Response: {response.json()}")
    
    # POST request with JSON data
    data = {'name': 'John', 'age': 30}
    response = requests.post('https://httpbin.org/post', json=data)
    print(f"\nPOST Status: {response.status_code}")
    print(f"POST Response: {response.json()}")
    
    # PUT request
    response = requests.put('https://httpbin.org/put', json=data)
    print(f"\nPUT Status: {response.status_code}")
    
    # DELETE request
    response = requests.delete('https://httpbin.org/delete')
    print(f"DELETE Status: {response.status_code}")

# Error handling
def http_error_handling():
    """Demonstrate HTTP error handling."""
    print("\n=== HTTP Error Handling ===")
    
    try:
        response = requests.get('https://httpbin.org/status/404', timeout=5)
        response.raise_for_status()  # Raises exception for 4xx/5xx status codes
    except requests.exceptions.HTTPError as e:
        print(f"HTTP Error: {e}")
    except requests.exceptions.Timeout:
        print("Request timed out")
    except requests.exceptions.RequestException as e:
        print(f"Request error: {e}")

# Headers and authentication
def http_headers_auth():
    """Demonstrate headers and authentication."""
    print("\n=== HTTP Headers and Authentication ===")
    
    # Custom headers
    headers = {
        'User-Agent': 'MyApp/1.0',
        'Accept': 'application/json',
        'Authorization': 'Bearer your-token-here'
    }
    
    response = requests.get('https://httpbin.org/headers', headers=headers)
    print(f"Headers response: {response.json()}")
    
    # Basic authentication
    auth = ('username', 'password')
    response = requests.get('https://httpbin.org/basic-auth/username/password', auth=auth)
    print(f"Basic auth response: {response.json()}")

# Query parameters
def query_parameters():
    """Demonstrate query parameters."""
    print("\n=== Query Parameters ===")
    
    params = {'page': 1, 'limit': 10, 'search': 'python'}
    response = requests.get('https://httpbin.org/get', params=params)
    print(f"Query params response: {response.json()}")

# Run HTTP demos
basic_http_demo()
http_error_handling()
http_headers_auth()
query_parameters()
```

### REST API Client

```python
class APIClient:
    """Generic REST API client."""
    
    def __init__(self, base_url, api_key=None):
        self.base_url = base_url.rstrip('/')
        self.session = requests.Session()
        
        if api_key:
            self.session.headers.update({'Authorization': f'Bearer {api_key}'})
        
        self.session.headers.update({
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        })
    
    def get(self, endpoint, params=None):
        """GET request."""
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        response = self.session.get(url, params=params)
        response.raise_for_status()
        return response.json()
    
    def post(self, endpoint, data=None):
        """POST request."""
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        response = self.session.post(url, json=data)
        response.raise_for_status()
        return response.json()
    
    def put(self, endpoint, data=None):
        """PUT request."""
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        response = self.session.put(url, json=data)
        response.raise_for_status()
        return response.json()
    
    def delete(self, endpoint):
        """DELETE request."""
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        response = self.session.delete(url)
        response.raise_for_status()
        return response.status_code == 204

# Using the API client
print("\n=== REST API Client ===")
client = APIClient('https://jsonplaceholder.typicode.com')

# Get all posts
posts = client.get('/posts')
print(f"Retrieved {len(posts)} posts")

# Get specific post
post = client.get('/posts/1')
print(f"Post 1: {post['title']}")

# Create new post
new_post = {
    'title': 'My New Post',
    'body': 'This is the content of my new post.',
    'userId': 1
}
created_post = client.post('/posts', new_post)
print(f"Created post with ID: {created_post['id']}")
```

## Flask Web Framework

### Basic Flask Application

```python
from flask import Flask, request, jsonify, render_template_string
from datetime import datetime

app = Flask(__name__)

# Basic routes
@app.route('/')
def home():
    """Home page."""
    return jsonify({
        'message': 'Welcome to the Flask API',
        'timestamp': datetime.now().isoformat()
    })

@app.route('/users', methods=['GET'])
def get_users():
    """Get all users."""
    users = [
        {'id': 1, 'name': 'Alice', 'email': 'alice@example.com'},
        {'id': 2, 'name': 'Bob', 'email': 'bob@example.com'},
        {'id': 3, 'name': 'Charlie', 'email': 'charlie@example.com'}
    ]
    return jsonify(users)

@app.route('/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    """Get specific user."""
    users = {
        1: {'id': 1, 'name': 'Alice', 'email': 'alice@example.com'},
        2: {'id': 2, 'name': 'Bob', 'email': 'bob@example.com'},
        3: {'id': 3, 'name': 'Charlie', 'email': 'charlie@example.com'}
    }
    
    if user_id not in users:
        return jsonify({'error': 'User not found'}), 404
    
    return jsonify(users[user_id])

@app.route('/users', methods=['POST'])
def create_user():
    """Create new user."""
    data = request.get_json()
    
    if not data or 'name' not in data or 'email' not in data:
        return jsonify({'error': 'Name and email are required'}), 400
    
    new_user = {
        'id': len(users) + 1,
        'name': data['name'],
        'email': data['email']
    }
    
    return jsonify(new_user), 201

# Error handlers
@app.errorhandler(404)
def not_found(error):
    """Handle 404 errors."""
    return jsonify({'error': 'Not found'}), 404

@app.errorhandler(500)
def internal_error(error):
    """Handle 500 errors."""
    return jsonify({'error': 'Internal server error'}), 500

# Middleware example
@app.before_request
def before_request():
    """Execute before each request."""
    print(f"Request: {request.method} {request.path}")

@app.after_request
def after_request(response):
    """Execute after each request."""
    response.headers['X-Content-Type-Options'] = 'nosniff'
    return response

# Template example
@app.route('/html')
def html_page():
    """Return HTML page."""
    template = """
    <!DOCTYPE html>
    <html>
    <head>
        <title>Flask App</title>
    </head>
    <body>
        <h1>Welcome to Flask!</h1>
        <p>Current time: {{ current_time }}</p>
        <ul>
            {% for user in users %}
            <li>{{ user.name }} - {{ user.email }}</li>
            {% endfor %}
        </ul>
    </body>
    </html>
    """
    
    users = [
        {'name': 'Alice', 'email': 'alice@example.com'},
        {'name': 'Bob', 'email': 'bob@example.com'}
    ]
    
    return render_template_string(template, 
                                current_time=datetime.now(),
                                users=users)

# Run Flask app (commented out for demo)
# if __name__ == '__main__':
#     app.run(debug=True, port=5000)
```

### Advanced Flask Features

```python
from flask import Flask, request, jsonify, g, session, redirect, url_for
from functools import wraps
import jwt
import hashlib

app = Flask(__name__)
app.secret_key = 'your-secret-key-here'

# Database simulation
users_db = {}
posts_db = []

def token_required(f):
    """Decorator for token authentication."""
    @wraps(f)
    def decorated(*args, **kwargs):
        token = request.headers.get('Authorization')
        
        if not token:
            return jsonify({'error': 'Token is missing'}), 401
        
        try:
            if token.startswith('Bearer '):
                token = token[7:]
            
            data = jwt.decode(token, app.secret_key, algorithms=['HS256'])
            g.current_user = data['user_id']
        except jwt.ExpiredSignatureError:
            return jsonify({'error': 'Token has expired'}), 401
        except jwt.InvalidTokenError:
            return jsonify({'error': 'Token is invalid'}), 401
        
        return f(*args, **kwargs)
    
    return decorated

@app.route('/register', methods=['POST'])
def register():
    """User registration."""
    data = request.get_json()
    
    if not data or 'username' not in data or 'password' not in data:
        return jsonify({'error': 'Username and password are required'}), 400
    
    username = data['username']
    if username in users_db:
        return jsonify({'error': 'Username already exists'}), 400
    
    # Hash password
    password_hash = hashlib.sha256(data['password'].encode()).hexdigest()
    users_db[username] = {
        'username': username,
        'password_hash': password_hash,
        'created_at': datetime.now().isoformat()
    }
    
    return jsonify({'message': 'User registered successfully'}), 201

@app.route('/login', methods=['POST'])
def login():
    """User login."""
    data = request.get_json()
    
    if not data or 'username' not in data or 'password' not in data:
        return jsonify({'error': 'Username and password are required'}), 400
    
    username = data['username']
    password = data['password']
    
    if username not in users_db:
        return jsonify({'error': 'Invalid credentials'}), 401
    
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    if users_db[username]['password_hash'] != password_hash:
        return jsonify({'error': 'Invalid credentials'}), 401
    
    # Generate JWT token
    token = jwt.encode({
        'user_id': username,
        'exp': datetime.utcnow().timestamp() + 3600  # 1 hour
    }, app.secret_key, algorithm='HS256')
    
    return jsonify({'token': token})

@app.route('/posts', methods=['GET'])
def get_posts():
    """Get all posts."""
    return jsonify(posts_db)

@app.route('/posts', methods=['POST'])
@token_required
def create_post():
    """Create new post (requires authentication)."""
    data = request.get_json()
    
    if not data or 'title' not in data or 'content' not in data:
        return jsonify({'error': 'Title and content are required'}), 400
    
    new_post = {
        'id': len(posts_db) + 1,
        'title': data['title'],
        'content': data['content'],
        'author': g.current_user,
        'created_at': datetime.now().isoformat()
    }
    
    posts_db.append(new_post)
    return jsonify(new_post), 201

@app.route('/posts/<int:post_id>', methods=['PUT'])
@token_required
def update_post(post_id):
    """Update post (requires authentication)."""
    data = request.get_json()
    
    post = next((p for p in posts_db if p['id'] == post_id), None)
    if not post:
        return jsonify({'error': 'Post not found'}), 404
    
    if post['author'] != g.current_user:
        return jsonify({'error': 'Not authorized'}), 403
    
    if 'title' in data:
        post['title'] = data['title']
    if 'content' in data:
        post['content'] = data['content']
    
    return jsonify(post)

@app.route('/posts/<int:post_id>', methods=['DELETE'])
@token_required
def delete_post(post_id):
    """Delete post (requires authentication)."""
    global posts_db
    
    post = next((p for p in posts_db if p['id'] == post_id), None)
    if not post:
        return jsonify({'error': 'Post not found'}), 404
    
    if post['author'] != g.current_user:
        return jsonify({'error': 'Not authorized'}), 403
    
    posts_db = [p for p in posts_db if p['id'] != post_id]
    return jsonify({'message': 'Post deleted successfully'})
```

## FastAPI Framework

### Basic FastAPI Application

```python
from fastapi import FastAPI, HTTPException, Depends, status
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from pydantic import BaseModel, EmailStr
from typing import List, Optional
from datetime import datetime
import jwt

app = FastAPI(title="FastAPI Demo", version="1.0.0")

# Pydantic models
class UserCreate(BaseModel):
    username: str
    email: str
    password: str

class User(BaseModel):
    id: int
    username: str
    email: str
    created_at: datetime

class PostCreate(BaseModel):
    title: str
    content: str

class Post(BaseModel):
    id: int
    title: str
    content: str
    author: str
    created_at: datetime

# Database simulation
users_db = {}
posts_db = []

# Security
security = HTTPBearer()

def get_current_user(credentials: HTTPAuthorizationCredentials = Depends(security)):
    """Get current user from token."""
    try:
        token = credentials.credentials
        payload = jwt.decode(token, "secret", algorithms=["HS256"])
        user_id = payload.get("user_id")
        
        if user_id not in users_db:
            raise HTTPException(status_code=401, detail="Invalid token")
        
        return user_id
    except jwt.ExpiredSignatureError:
        raise HTTPException(status_code=401, detail="Token expired")
    except jwt.InvalidTokenError:
        raise HTTPException(status_code=401, detail="Invalid token")

# Routes
@app.get("/")
async def root():
    """Root endpoint."""
    return {"message": "Welcome to FastAPI", "timestamp": datetime.now()}

@app.post("/users/", response_model=User, status_code=status.HTTP_201_CREATED)
async def create_user(user: UserCreate):
    """Create new user."""
    if user.username in users_db:
        raise HTTPException(status_code=400, detail="Username already exists")
    
    user_id = len(users_db) + 1
    new_user = {
        "id": user_id,
        "username": user.username,
        "email": user.email,
        "created_at": datetime.now()
    }
    
    users_db[user.username] = new_user
    return new_user

@app.get("/users/", response_model=List[User])
async def get_users():
    """Get all users."""
    return list(users_db.values())

@app.get("/users/{username}", response_model=User)
async def get_user(username: str):
    """Get specific user."""
    if username not in users_db:
        raise HTTPException(status_code=404, detail="User not found")
    
    return users_db[username]

@app.post("/posts/", response_model=Post, status_code=status.HTTP_201_CREATED)
async def create_post(post: PostCreate, current_user: str = Depends(get_current_user)):
    """Create new post."""
    post_id = len(posts_db) + 1
    new_post = {
        "id": post_id,
        "title": post.title,
        "content": post.content,
        "author": current_user,
        "created_at": datetime.now()
    }
    
    posts_db.append(new_post)
    return new_post

@app.get("/posts/", response_model=List[Post])
async def get_posts():
    """Get all posts."""
    return posts_db

@app.get("/posts/{post_id}", response_model=Post)
async def get_post(post_id: int):
    """Get specific post."""
    post = next((p for p in posts_db if p["id"] == post_id), None)
    if not post:
        raise HTTPException(status_code=404, detail="Post not found")
    
    return post

@app.put("/posts/{post_id}", response_model=Post)
async def update_post(post_id: int, post: PostCreate, current_user: str = Depends(get_current_user)):
    """Update post."""
    existing_post = next((p for p in posts_db if p["id"] == post_id), None)
    if not existing_post:
        raise HTTPException(status_code=404, detail="Post not found")
    
    if existing_post["author"] != current_user:
        raise HTTPException(status_code=403, detail="Not authorized")
    
    existing_post["title"] = post.title
    existing_post["content"] = post.content
    
    return existing_post

@app.delete("/posts/{post_id}")
async def delete_post(post_id: int, current_user: str = Depends(get_current_user)):
    """Delete post."""
    global posts_db
    
    post = next((p for p in posts_db if p["id"] == post_id), None)
    if not post:
        raise HTTPException(status_code=404, detail="Post not found")
    
    if post["author"] != current_user:
        raise HTTPException(status_code=403, detail="Not authorized")
    
    posts_db = [p for p in posts_db if p["id"] != post_id]
    return {"message": "Post deleted successfully"}

# Run FastAPI app (commented out for demo)
# if __name__ == "__main__":
#     import uvicorn
#     uvicorn.run(app, host="0.0.0.0", port=8000)
```

## API Testing

### Testing with pytest

```python
import pytest
import requests
from unittest.mock import patch, Mock

class TestAPI:
    """Test cases for API endpoints."""
    
    def setup_method(self):
        """Set up test fixtures."""
        self.base_url = "http://localhost:5000"
        self.headers = {"Content-Type": "application/json"}
    
    def test_get_users(self):
        """Test getting all users."""
        response = requests.get(f"{self.base_url}/users")
        assert response.status_code == 200
        assert isinstance(response.json(), list)
    
    def test_create_user(self):
        """Test creating a new user."""
        user_data = {
            "name": "Test User",
            "email": "test@example.com"
        }
        
        response = requests.post(
            f"{self.base_url}/users",
            json=user_data,
            headers=self.headers
        )
        
        assert response.status_code == 201
        assert response.json()["name"] == user_data["name"]
    
    def test_get_user_not_found(self):
        """Test getting non-existent user."""
        response = requests.get(f"{self.base_url}/users/999")
        assert response.status_code == 404
    
    @patch('requests.get')
    def test_api_with_mock(self, mock_get):
        """Test API with mocked response."""
        mock_response = Mock()
        mock_response.json.return_value = {"message": "Mocked response"}
        mock_response.status_code = 200
        mock_get.return_value = mock_response
        
        response = requests.get("http://example.com/api")
        assert response.status_code == 200
        assert response.json()["message"] == "Mocked response"

# API Documentation
def generate_api_docs():
    """Generate API documentation."""
    print("\n=== API Documentation ===")
    
    endpoints = [
        {
            "method": "GET",
            "path": "/users",
            "description": "Get all users",
            "response": "List of users"
        },
        {
            "method": "POST",
            "path": "/users",
            "description": "Create new user",
            "body": {"name": "string", "email": "string"},
            "response": "Created user object"
        },
        {
            "method": "GET",
            "path": "/users/{id}",
            "description": "Get specific user",
            "response": "User object"
        },
        {
            "method": "POST",
            "path": "/posts",
            "description": "Create new post",
            "headers": {"Authorization": "Bearer token"},
            "body": {"title": "string", "content": "string"},
            "response": "Created post object"
        }
    ]
    
    for endpoint in endpoints:
        print(f"\n{endpoint['method']} {endpoint['path']}")
        print(f"Description: {endpoint['description']}")
        if 'body' in endpoint:
            print(f"Body: {endpoint['body']}")
        if 'headers' in endpoint:
            print(f"Headers: {endpoint['headers']}")
        print(f"Response: {endpoint['response']}")

generate_api_docs()
```

## Web Scraping

### Basic Web Scraping

```python
import requests
from bs4 import BeautifulSoup
import json
import csv

def scrape_website(url):
    """Scrape a website and extract data."""
    try:
        response = requests.get(url)
        response.raise_for_status()
        
        soup = BeautifulSoup(response.content, 'html.parser')
        
        # Extract title
        title = soup.find('title').text if soup.find('title') else 'No title'
        
        # Extract all links
        links = [a.get('href') for a in soup.find_all('a', href=True)]
        
        # Extract all text
        text = soup.get_text()
        
        return {
            'url': url,
            'title': title,
            'links': links,
            'text_length': len(text),
            'status_code': response.status_code
        }
    
    except requests.RequestException as e:
        return {'error': str(e), 'url': url}

def scrape_multiple_urls(urls):
    """Scrape multiple URLs."""
    results = []
    
    for url in urls:
        print(f"Scraping: {url}")
        result = scrape_website(url)
        results.append(result)
    
    return results

# Example usage
urls = [
    'https://httpbin.org/html',
    'https://example.com',
    'https://httpbin.org/json'
]

scraped_data = scrape_multiple_urls(urls)

# Save to JSON
with open('scraped_data.json', 'w') as f:
    json.dump(scraped_data, f, indent=2)

# Save to CSV
with open('scraped_data.csv', 'w', newline='') as f:
    if scraped_data:
        writer = csv.DictWriter(f, fieldnames=scraped_data[0].keys())
        writer.writeheader()
        writer.writerows(scraped_data)

print("\n=== Web Scraping Results ===")
for data in scraped_data:
    print(f"URL: {data.get('url')}")
    print(f"Title: {data.get('title')}")
    print(f"Status: {data.get('status_code')}")
    print(f"Links found: {len(data.get('links', []))}")
    print("-" * 50)
```

## Key Takeaways

1. **HTTP** is the foundation of web communication
2. **REST APIs** provide standardized ways to interact with web services
3. **Flask** is a lightweight framework for building web applications
4. **FastAPI** offers modern features with automatic documentation
5. **Authentication** is crucial for securing APIs
6. **Error handling** improves user experience and debugging
7. **Testing** ensures API reliability and correctness
8. **Web scraping** extracts data from websites programmatically

## Next Steps

In the next lesson, we'll explore Databases and ORMs - working with SQLite, SQLAlchemy, and database management for data persistence in applications.
