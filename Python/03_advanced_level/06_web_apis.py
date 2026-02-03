# Web APIs Examples
import requests
import json
from flask import Flask, request, jsonify
from typing import Dict, List, Any
import time

print("Web APIs Examples")
print("=" * 20)

# 1. Consuming APIs with requests
print("1. Consuming APIs with requests")
print("-" * 30)

def get_weather_data(city: str) -> Dict[str, Any]:
    """Get weather data for a city."""
    # Note: This is a mock example. In real usage, you'd use a real API key
    api_key = "your_api_key_here"
    url = f"http://api.openweathermap.org/data/2.5/weather"
    params = {
        'q': city,
        'appid': api_key,
        'units': 'metric'
    }
    
    try:
        response = requests.get(url, params=params)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        return {"error": str(e)}

def get_github_user(username: str) -> Dict[str, Any]:
    """Get GitHub user information."""
    url = f"https://api.github.com/users/{username}"
    
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        return {"error": str(e)}

def get_random_quote() -> Dict[str, Any]:
    """Get a random quote from an API."""
    url = "https://api.quotable.io/random"
    
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        return {"error": str(e)}

# Test API consumption
print("Testing API consumption:")
print(f"Weather data for London: {get_weather_data('London')}")
print(f"GitHub user 'octocat': {get_github_user('octocat')}")
print(f"Random quote: {get_random_quote()}")

# 2. Building APIs with Flask
print("\n2. Building APIs with Flask")
print("-" * 25)

app = Flask(__name__)

# Sample data
users = [
    {"id": 1, "name": "Alice", "email": "alice@example.com"},
    {"id": 2, "name": "Bob", "email": "bob@example.com"},
    {"id": 3, "name": "Charlie", "email": "charlie@example.com"}
]

posts = [
    {"id": 1, "title": "First Post", "content": "This is the first post", "user_id": 1},
    {"id": 2, "title": "Second Post", "content": "This is the second post", "user_id": 2},
    {"id": 3, "title": "Third Post", "content": "This is the third post", "user_id": 1}
]

@app.route('/api/users', methods=['GET'])
def get_users():
    """Get all users."""
    return jsonify(users)

@app.route('/api/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    """Get a specific user."""
    user = next((u for u in users if u['id'] == user_id), None)
    if user:
        return jsonify(user)
    return jsonify({"error": "User not found"}), 404

@app.route('/api/users', methods=['POST'])
def create_user():
    """Create a new user."""
    data = request.get_json()
    if not data or 'name' not in data or 'email' not in data:
        return jsonify({"error": "Name and email are required"}), 400
    
    new_user = {
        "id": max(u['id'] for u in users) + 1,
        "name": data['name'],
        "email": data['email']
    }
    users.append(new_user)
    return jsonify(new_user), 201

@app.route('/api/users/<int:user_id>', methods=['PUT'])
def update_user(user_id):
    """Update a user."""
    user = next((u for u in users if u['id'] == user_id), None)
    if not user:
        return jsonify({"error": "User not found"}), 404
    
    data = request.get_json()
    if not data:
        return jsonify({"error": "No data provided"}), 400
    
    user.update(data)
    return jsonify(user)

@app.route('/api/users/<int:user_id>', methods=['DELETE'])
def delete_user(user_id):
    """Delete a user."""
    global users
    users = [u for u in users if u['id'] != user_id]
    return jsonify({"message": "User deleted"}), 200

@app.route('/api/posts', methods=['GET'])
def get_posts():
    """Get all posts."""
    return jsonify(posts)

@app.route('/api/posts/<int:post_id>', methods=['GET'])
def get_post(post_id):
    """Get a specific post."""
    post = next((p for p in posts if p['id'] == post_id), None)
    if post:
        return jsonify(post)
    return jsonify({"error": "Post not found"}), 404

@app.route('/api/posts', methods=['POST'])
def create_post():
    """Create a new post."""
    data = request.get_json()
    if not data or 'title' not in data or 'content' not in data or 'user_id' not in data:
        return jsonify({"error": "Title, content, and user_id are required"}), 400
    
    new_post = {
        "id": max(p['id'] for p in posts) + 1,
        "title": data['title'],
        "content": data['content'],
        "user_id": data['user_id']
    }
    posts.append(new_post)
    return jsonify(new_post), 201

@app.route('/api/posts/<int:post_id>', methods=['PUT'])
def update_post(post_id):
    """Update a post."""
    post = next((p for p in posts if p['id'] == post_id), None)
    if not post:
        return jsonify({"error": "Post not found"}), 404
    
    data = request.get_json()
    if not data:
        return jsonify({"error": "No data provided"}), 400
    
    post.update(data)
    return jsonify(post)

@app.route('/api/posts/<int:post_id>', methods=['DELETE'])
def delete_post(post_id):
    """Delete a post."""
    global posts
    posts = [p for p in posts if p['id'] != post_id]
    return jsonify({"message": "Post deleted"}), 200

@app.errorhandler(404)
def not_found(error):
    """Handle 404 errors."""
    return jsonify({"error": "Not found"}), 404

@app.errorhandler(500)
def internal_error(error):
    """Handle 500 errors."""
    return jsonify({"error": "Internal server error"}), 500

# 3. HTTP Methods and Status Codes
print("\n3. HTTP Methods and Status Codes")
print("-" * 30)

def demonstrate_http_methods():
    """Demonstrate different HTTP methods."""
    
    # GET request
    def make_get_request(url: str) -> Dict[str, Any]:
        try:
            response = requests.get(url)
            return {
                "status_code": response.status_code,
                "data": response.json() if response.headers.get('content-type', '').startswith('application/json') else response.text
            }
        except requests.exceptions.RequestException as e:
            return {"error": str(e)}
    
    # POST request
    def make_post_request(url: str, data: Dict[str, Any]) -> Dict[str, Any]:
        try:
            response = requests.post(url, json=data)
            return {
                "status_code": response.status_code,
                "data": response.json() if response.headers.get('content-type', '').startswith('application/json') else response.text
            }
        except requests.exceptions.RequestException as e:
            return {"error": str(e)}
    
    # PUT request
    def make_put_request(url: str, data: Dict[str, Any]) -> Dict[str, Any]:
        try:
            response = requests.put(url, json=data)
            return {
                "status_code": response.status_code,
                "data": response.json() if response.headers.get('content-type', '').startswith('application/json') else response.text
            }
        except requests.exceptions.RequestException as e:
            return {"error": str(e)}
    
    # DELETE request
    def make_delete_request(url: str) -> Dict[str, Any]:
        try:
            response = requests.delete(url)
            return {
                "status_code": response.status_code,
                "data": response.json() if response.headers.get('content-type', '').startswith('application/json') else response.text
            }
        except requests.exceptions.RequestException as e:
            return {"error": str(e)}
    
    # PATCH request
    def make_patch_request(url: str, data: Dict[str, Any]) -> Dict[str, Any]:
        try:
            response = requests.patch(url, json=data)
            return {
                "status_code": response.status_code,
                "data": response.json() if response.headers.get('content-type', '').startswith('application/json') else response.text
            }
        except requests.exceptions.RequestException as e:
            return {"error": str(e)}
    
    return {
        "get": make_get_request,
        "post": make_post_request,
        "put": make_put_request,
        "delete": make_delete_request,
        "patch": make_patch_request
    }

# Test HTTP methods
http_methods = demonstrate_http_methods()

# Test with a mock API endpoint
test_url = "https://httpbin.org"
test_data = {"name": "Test", "value": 123}

print("Testing HTTP methods:")
print(f"GET request: {http_methods['get'](f'{test_url}/get')}")
print(f"POST request: {http_methods['post'](f'{test_url}/post', test_data)}")
print(f"PUT request: {http_methods['put'](f'{test_url}/put', test_data)}")
print(f"DELETE request: {http_methods['delete'](f'{test_url}/delete')}")
print(f"PATCH request: {http_methods['patch'](f'{test_url}/patch', test_data)}")

# 4. API Authentication
print("\n4. API Authentication")
print("-" * 22)

def api_key_authentication(api_key: str) -> Dict[str, str]:
    """API key authentication."""
    return {"X-API-Key": api_key}

def basic_authentication(username: str, password: str) -> Dict[str, str]:
    """Basic authentication."""
    import base64
    credentials = f"{username}:{password}"
    encoded_credentials = base64.b64encode(credentials.encode()).decode()
    return {"Authorization": f"Basic {encoded_credentials}"}

def bearer_token_authentication(token: str) -> Dict[str, str]:
    """Bearer token authentication."""
    return {"Authorization": f"Bearer {token}"}

def jwt_authentication(token: str) -> Dict[str, str]:
    """JWT authentication."""
    return {"Authorization": f"Bearer {token}"}

def oauth2_authentication(access_token: str) -> Dict[str, str]:
    """OAuth 2.0 authentication."""
    return {"Authorization": f"Bearer {access_token}"}

def session_authentication(session_id: str) -> Dict[str, str]:
    """Session-based authentication."""
    return {"Cookie": f"session_id={session_id}"}

# Test authentication methods
print("Testing authentication methods:")
print(f"API Key: {api_key_authentication('your_api_key')}")
print(f"Basic Auth: {basic_authentication('username', 'password')}")
print(f"Bearer Token: {bearer_token_authentication('your_token')}")
print(f"JWT: {jwt_authentication('your_jwt_token')}")
print(f"OAuth 2.0: {oauth2_authentication('your_access_token')}")
print(f"Session: {session_authentication('your_session_id')}")

# 5. API Documentation
print("\n5. API Documentation")
print("-" * 20)

def create_api_documentation():
    """Create API documentation."""
    
    api_docs = {
        "title": "Sample API",
        "version": "1.0.0",
        "description": "A sample REST API for demonstration purposes",
        "base_url": "https://api.example.com",
        "endpoints": [
            {
                "path": "/api/users",
                "methods": ["GET", "POST"],
                "description": "Manage users",
                "parameters": {
                    "GET": [],
                    "POST": [
                        {"name": "name", "type": "string", "required": True, "description": "User's name"},
                        {"name": "email", "type": "string", "required": True, "description": "User's email"}
                    ]
                },
                "responses": {
                    "200": "Success",
                    "201": "Created",
                    "400": "Bad Request",
                    "500": "Internal Server Error"
                }
            },
            {
                "path": "/api/users/{id}",
                "methods": ["GET", "PUT", "DELETE"],
                "description": "Manage a specific user",
                "parameters": {
                    "GET": [
                        {"name": "id", "type": "integer", "required": True, "description": "User ID"}
                    ],
                    "PUT": [
                        {"name": "id", "type": "integer", "required": True, "description": "User ID"},
                        {"name": "name", "type": "string", "required": False, "description": "User's name"},
                        {"name": "email", "type": "string", "required": False, "description": "User's email"}
                    ],
                    "DELETE": [
                        {"name": "id", "type": "integer", "required": True, "description": "User ID"}
                    ]
                },
                "responses": {
                    "200": "Success",
                    "404": "Not Found",
                    "500": "Internal Server Error"
                }
            }
        ],
        "authentication": {
            "type": "API Key",
            "header": "X-API-Key",
            "description": "Include your API key in the X-API-Key header"
        },
        "rate_limiting": {
            "limit": "1000 requests per hour",
            "header": "X-RateLimit-Limit",
            "remaining": "X-RateLimit-Remaining",
            "reset": "X-RateLimit-Reset"
        },
        "examples": {
            "python": {
                "get_users": """
import requests

response = requests.get('https://api.example.com/api/users', 
                       headers={'X-API-Key': 'your_api_key'})
users = response.json()
""",
                "create_user": """
import requests

data = {'name': 'John Doe', 'email': 'john@example.com'}
response = requests.post('https://api.example.com/api/users', 
                        json=data,
                        headers={'X-API-Key': 'your_api_key'})
user = response.json()
"""
            },
            "curl": {
                "get_users": """
curl -X GET "https://api.example.com/api/users" \\
     -H "X-API-Key: your_api_key"
""",
                "create_user": """
curl -X POST "https://api.example.com/api/users" \\
     -H "Content-Type: application/json" \\
     -H "X-API-Key: your_api_key" \\
     -d '{"name": "John Doe", "email": "john@example.com"}'
"""
            }
        },
        "error_codes": {
            "400": "Bad Request - Invalid input data",
            "401": "Unauthorized - Invalid or missing API key",
            "403": "Forbidden - Insufficient permissions",
            "404": "Not Found - Resource not found",
            "429": "Too Many Requests - Rate limit exceeded",
            "500": "Internal Server Error - Server error"
        }
    }
    
    return api_docs

# Create API documentation
api_docs = create_api_documentation()
print("API Documentation created:")
print(json.dumps(api_docs, indent=2))

# 6. Error Handling
print("\n6. Error Handling")
print("-" * 18)

def handle_api_errors(response: requests.Response) -> Dict[str, Any]:
    """Handle API errors."""
    try:
        if response.status_code == 200:
            return {"success": True, "data": response.json()}
        elif response.status_code == 201:
            return {"success": True, "data": response.json(), "message": "Created"}
        elif response.status_code == 400:
            return {"success": False, "error": "Bad Request", "details": response.json()}
        elif response.status_code == 401:
            return {"success": False, "error": "Unauthorized", "message": "Invalid API key"}
        elif response.status_code == 403:
            return {"success": False, "error": "Forbidden", "message": "Insufficient permissions"}
        elif response.status_code == 404:
            return {"success": False, "error": "Not Found", "message": "Resource not found"}
        elif response.status_code == 429:
            return {"success": False, "error": "Too Many Requests", "message": "Rate limit exceeded"}
        elif response.status_code == 500:
            return {"success": False, "error": "Internal Server Error", "message": "Server error"}
        else:
            return {"success": False, "error": f"Unknown error: {response.status_code}"}
    except Exception as e:
        return {"success": False, "error": f"Error parsing response: {str(e)}"}

# Test error handling
test_responses = [
    requests.Response(),
    requests.Response(),
    requests.Response(),
    requests.Response(),
    requests.Response()
]

# Set status codes for test responses
test_responses[0].status_code = 200
test_responses[1].status_code = 400
test_responses[2].status_code = 401
test_responses[3].status_code = 404
test_responses[4].status_code = 500

print("Testing error handling:")
for i, response in enumerate(test_responses):
    print(f"Response {i+1}: {handle_api_errors(response)}")

# 7. Rate Limiting
print("\n7. Rate Limiting")
print("-" * 15)

class RateLimiter:
    """Rate limiter for API requests."""
    
    def __init__(self, max_requests: int, time_window: int):
        self.max_requests = max_requests
        self.time_window = time_window
        self.requests = []
    
    def is_allowed(self) -> bool:
        """Check if request is allowed."""
        current_time = time.time()
        
        # Remove old requests outside the time window
        self.requests = [req_time for req_time in self.requests 
                        if current_time - req_time < self.time_window]
        
        # Check if we can make another request
        if len(self.requests) < self.max_requests:
            self.requests.append(current_time)
            return True
        
        return False
    
    def get_retry_after(self) -> int:
        """Get seconds to wait before retry."""
        if not self.requests:
            return 0
        
        oldest_request = min(self.requests)
        retry_after = self.time_window - (time.time() - oldest_request)
        return max(0, int(retry_after))

# Test rate limiting
rate_limiter = RateLimiter(max_requests=5, time_window=60)  # 5 requests per minute

print("Testing rate limiting:")
for i in range(7):
    if rate_limiter.is_allowed():
        print(f"Request {i+1}: Allowed")
    else:
        print(f"Request {i+1}: Rate limited. Retry after {rate_limiter.get_retry_after()} seconds")

# 8. API Testing
print("\n8. API Testing")
print("-" * 15)

def test_api_endpoint(url: str, method: str = 'GET', data: Dict[str, Any] = None, 
                     headers: Dict[str, str] = None) -> Dict[str, Any]:
    """Test an API endpoint."""
    try:
        if method.upper() == 'GET':
            response = requests.get(url, headers=headers)
        elif method.upper() == 'POST':
            response = requests.post(url, json=data, headers=headers)
        elif method.upper() == 'PUT':
            response = requests.put(url, json=data, headers=headers)
        elif method.upper() == 'DELETE':
            response = requests.delete(url, headers=headers)
        else:
            return {"error": f"Unsupported method: {method}"}
        
        return {
            "status_code": response.status_code,
            "headers": dict(response.headers),
            "data": response.json() if response.headers.get('content-type', '').startswith('application/json') else response.text,
            "response_time": response.elapsed.total_seconds()
        }
    except requests.exceptions.RequestException as e:
        return {"error": str(e)}

# Test API endpoints
test_endpoints = [
    {"url": "https://httpbin.org/get", "method": "GET"},
    {"url": "https://httpbin.org/post", "method": "POST", "data": {"test": "data"}},
    {"url": "https://httpbin.org/put", "method": "PUT", "data": {"test": "data"}},
    {"url": "https://httpbin.org/delete", "method": "DELETE"}
]

print("Testing API endpoints:")
for endpoint in test_endpoints:
    result = test_api_endpoint(**endpoint)
    print(f"{endpoint['method']} {endpoint['url']}: {result}")

print("\nWeb APIs examples completed!")