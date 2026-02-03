# Express.js rewrite of Flask RESTful API Demo

Files added:
- `server.js` — Express.js implementation mirroring `app.py` behavior and endpoints.
- `package.json` — dependencies and start scripts.

How to run:

1. Install dependencies:

```bash
npm install
```

2. Start server:

```bash
npm start
```

3. The server listens on port 54321 by default. Test with curl or Postman.

Notes:
- This is a line-by-line feature port of the provided Flask demo into Express. The in-memory "databases" behave the same for demo purposes.
- No persistence; restart will reset data.
# Flask RESTful API Demo Backend

This is a comprehensive demo backend built with Python Flask to demonstrate RESTful API concepts. It's designed to help students understand how to build a backend that can handle various types of HTTP requests and responses.

## 🚀 Features Demonstrated

### HTTP Methods
- **GET**: Retrieve data (with filtering, pagination, and sorting)
- **POST**: Create new resources
- **PUT**: Update existing resources completely
- **PATCH**: Partially update existing resources
- **DELETE**: Remove resources
- **HEAD**: Get headers only (metadata without body)
- **OPTIONS**: Get allowed methods and CORS preflight support

### Request Processing
- **Headers**: Processing and validation of request headers
- **Query Parameters**: URL parameters for filtering, pagination, and sorting
- **JSON Body**: Parsing and validation of request body data
- **Path Parameters**: Dynamic URL segments for resource identification

### Response Handling
- **Status Codes**: 200 (OK), 201 (Created), 400 (Bad Request), 404 (Not Found), 409 (Conflict), 422 (Unprocessable Entity), 500 (Internal Server Error)
- **JSON Responses**: Structured data with consistent formatting
- **Error Handling**: Comprehensive error messages with timestamps

### Mock Database
- **Users**: User management with CRUD operations
- **Products**: Product catalog with inventory management
- **Orders**: Order processing with business logic validation

## 📋 API Endpoints

### 1. Welcome & Information
- **GET** `/` - Welcome message and API documentation

### 2. User Management
- **GET** `/users` - List all users (with filtering and pagination)
- **HEAD** `/users` - Get user collection headers only
- **OPTIONS** `/users` - Get allowed methods for users collection
- **GET** `/users/<id>` - Get specific user by ID
- **HEAD** `/users/<id>` - Get user headers only
- **OPTIONS** `/users/<id>` - Get allowed methods for user operations
- **POST** `/users` - Create new user
- **PUT** `/users/<id>` - Update user completely
- **PATCH** `/users/<id>` - Partially update user
- **DELETE** `/users/<id>` - Delete user

### 3. Product Management
- **GET** `/products` - List all products (with filtering and sorting)
- **HEAD** `/products` - Get product collection headers only
- **OPTIONS** `/products` - Get allowed methods for products collection
- **GET** `/products/<id>` - Get specific product by ID
- **HEAD** `/products/<id>` - Get product headers only
- **OPTIONS** `/products/<id>` - Get allowed methods for product operations
- **POST** `/products` - Create new product
- **PUT** `/products/<id>` - Update product completely
- **PATCH** `/products/<id>` - Partially update product
- **DELETE** `/products/<id>` - Delete product

### 4. Order Management
- **GET** `/orders` - List all orders (with filtering)
- **HEAD** `/orders` - Get order collection headers only
- **OPTIONS** `/orders` - Get allowed methods for orders collection
- **POST** `/orders` - Create new order

### 5. System
- **GET** `/health` - Health check endpoint
- **HEAD** `/health` - Health check headers only
- **OPTIONS** `/health` - Health check allowed methods

## 🛠️ Installation & Setup

### Prerequisites
- Python 3.7 or higher
- pip (Python package installer)

### Installation Steps

1. **Clone or download the project files**

2. **Install dependencies**
   ```bash
   pip install -r requirements.txt
   ```

3. **Run the application**
   ```bash
   python app.py
   ```

4. **Access the API**
   - The server will start on `http://localhost:54321`
   - You can test the API using Postman, curl, or any HTTP client

## 🧪 Testing with Postman

### Setting up Postman Collection

1. **Create a new collection** called "Flask RESTful API Demo"

2. **Set base URL**: `http://localhost:54321`

3. **Add the following requests**:

#### GET Requests (Read Operations)

**Welcome Endpoint**
- Method: `GET`
- URL: `{{base_url}}/`
- Description: Get API information and available endpoints

**Get All Users**
- Method: `GET`
- URL: `{{base_url}}/users`
- Query Params: 
  - `page`: 1
  - `limit`: 10
  - `active`: true
- Headers:
  - `Accept-Language`: en-US
  - `User-Agent`: PostmanRuntime/7.32.3

**Get Specific User**
- Method: `GET`
- URL: `{{base_url}}/users/1`
- Description: Retrieve user with ID 1

**Get All Products**
- Method: `GET`
- URL: `{{base_url}}/products`
- Query Params:
  - `category`: Electronics
  - `min_price`: 50.0
  - `max_price`: 1000.0
  - `sort_by`: price
  - `order`: asc

**Get All Orders**
- Method: `GET`
- URL: `{{base_url}}/orders`
- Query Params:
  - `user_id`: 1
  - `status`: pending

#### POST Requests (Create Operations)

**Create New User**
- Method: `POST`
- URL: `{{base_url}}/users`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "username": "alice_wong",
    "email": "alice@example.com",
    "age": 28,
    "active": true
  }
  ```

**Create New Product**
- Method: `POST`
- URL: `{{base_url}}/products`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "name": "Wireless Headphones",
    "price": 149.99,
    "category": "Electronics",
    "stock": 25
  }
  ```

**Create New Order**
- Method: `POST`
- URL: `{{base_url}}/orders`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "user_id": 1,
    "product_id": 2,
    "quantity": 3
  }
  ```

#### PUT Requests (Complete Update Operations)

**Update User (Complete)**
- Method: `PUT`
- URL: `{{base_url}}/users/1`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "username": "john_doe_updated",
    "email": "john.updated@example.com",
    "age": 26,
    "active": true
  }
  ```

**Update Product (Complete)**
- Method: `PUT`
- URL: `{{base_url}}/products/1`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "name": "Gaming Laptop",
    "price": 1299.99,
    "category": "Electronics",
    "stock": 45
  }
  ```

#### PATCH Requests (Partial Update Operations)

**Partially Update User**
- Method: `PATCH`
- URL: `{{base_url}}/users/1`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "age": 27,
    "active": false
  }
  ```

**Partially Update Product**
- Method: `PATCH`
- URL: `{{base_url}}/products/1`
- Headers:
  - `Content-Type`: application/json
- Body (raw JSON):
  ```json
  {
    "price": 1399.99,
    "stock": 40
  }
  ```



#### HEAD Requests (Headers Only)

**Get User Collection Headers**
- Method: `HEAD`
- URL: `{{base_url}}/users`
- Description: Get metadata about users collection without response body

**Get Product Collection Headers**
- Method: `HEAD`
- URL: `{{base_url}}/products`
- Description: Get metadata about products collection without response body

**Get Order Collection Headers**
- Method: `HEAD`
- URL: `{{base_url}}/orders`
- Description: Get metadata about orders collection without response body

**Get Health Check Headers**
- Method: `HEAD`
- URL: `{{base_url}}/health`
- Description: Get health status headers without response body

#### OPTIONS Requests (Method Discovery)

**Get Users Collection Methods**
- Method: `OPTIONS`
- URL: `{{base_url}}/users`
- Description: Discover allowed methods for users collection (CORS preflight)

**Get Products Collection Methods**
- Method: `OPTIONS`
- URL: `{{base_url}}/products`
- Description: Discover allowed methods for products collection (CORS preflight)

**Get Orders Collection Methods**
- Method: `OPTIONS`
- URL: `{{base_url}}/orders`
- Description: Discover allowed methods for orders collection (CORS preflight)

#### DELETE Requests (Delete Operations)

**Delete User**
- Method: `DELETE`
- URL: `{{base_url}}/users/3`
- Description: Remove user with ID 3

**Delete Product**
- Method: `DELETE`
- URL: `{{base_url}}/products/3`
- Description: Remove product with ID 3

### Testing Error Scenarios

#### 400 Bad Request
- Send POST request to `/users` without required fields
- Send request with invalid JSON body

#### 404 Not Found
- Try to GET, PUT, or DELETE non-existent resources
- Use invalid IDs in URLs

#### 409 Conflict
- Try to create a user with an existing username

#### 422 Unprocessable Entity
- Try to create an order with insufficient stock
- Use invalid quantity values

## 🔍 Key Learning Points

### 1. RESTful Design Principles
- **Resource-based URLs**: `/users`, `/products`, `/orders`
- **HTTP methods for CRUD operations**: GET, POST, PUT, PATCH, DELETE
- **Additional HTTP methods**: HEAD (metadata), OPTIONS (method discovery)
- **Consistent response formats**: JSON with status codes and messages

### 2. Request Handling
- **Query Parameters**: For filtering, pagination, and sorting
- **Path Parameters**: For resource identification
- **Request Body**: JSON validation and processing
- **Headers**: Processing and using request metadata

### 3. Response Management
- **Status Codes**: Appropriate HTTP status codes for different scenarios
- **Error Handling**: Comprehensive error messages with context
- **Data Formatting**: Consistent JSON response structure

### 4. Business Logic
- **Validation**: Input validation and business rule enforcement
- **Data Relationships**: Handling related data (users, products, orders)
- **State Management**: Updating related data when resources change

## 🚨 Common Issues & Solutions

### Port Already in Use
If you get "Address already in use" error:
```bash
# Find process using port 5000
lsof -i :5000

# Kill the process
kill -9 <PID>
```

### Import Errors
Make sure all dependencies are installed:
```bash
pip install -r requirements.txt
```

### CORS Issues
The app includes CORS support, but if you encounter issues, you can modify the CORS configuration in `app.py`.

## 📚 Next Steps

After understanding this demo, students can:

1. **Add Database Integration**: Replace mock data with real database (SQLite, PostgreSQL, etc.)
2. **Implement Authentication**: Add JWT tokens, user sessions, or OAuth
3. **Add More Validation**: Implement more sophisticated input validation
4. **Create Frontend**: Build a web interface to interact with the API
5. **Add Testing**: Implement unit tests and integration tests
6. **Deploy**: Deploy the API to cloud platforms like Heroku, AWS, or Google Cloud

## 🤝 Contributing

This is a demo project for educational purposes. Feel free to modify and extend it to suit your learning needs!

## 📄 License

This project is open source and available under the MIT License.
