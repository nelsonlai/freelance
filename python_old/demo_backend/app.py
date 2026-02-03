from flask import Flask, request, jsonify, make_response
from flask_cors import CORS
import json
from datetime import datetime
import uuid

app = Flask(__name__)
CORS(app)

# Mock database for demo purposes
users_db = [
    {"id": 1, "username": "john_doe", "email": "john@example.com", "age": 25, "active": True},
    {"id": 2, "username": "jane_smith", "email": "jane@example.com", "age": 30, "active": True},
    {"id": 3, "username": "bob_wilson", "email": "bob@example.com", "age": 35, "active": False}
]

products_db = [
    {"id": 1, "name": "Laptop", "price": 999.99, "category": "Electronics", "stock": 50},
    {"id": 2, "name": "Mouse", "price": 29.99, "category": "Electronics", "stock": 100},
    {"id": 3, "name": "Keyboard", "price": 79.99, "category": "Electronics", "stock": 75}
]

orders_db = [
    {"id": 1, "user_id": 1, "product_id": 1, "quantity": 2, "total": 1999.98, "status": "pending"},
    {"id": 2, "user_id": 2, "product_id": 2, "quantity": 1, "total": 29.99, "status": "completed"}
]

@app.route('/')
def home():
    """GET - Welcome endpoint with basic information"""
    return jsonify({
        "message": "Welcome to Flask RESTful API Demo",
        "version": "1.0.0",
        "endpoints": {
            "GET": ["/", "/users", "/users/<id>", "/products", "/products/<id>"],
            "POST": ["/users", "/products", "/orders"],
            "PUT": ["/users/<id>", "/products/<id>"],
            "PATCH": ["/users/<id>", "/products/<id>"],
            "DELETE": ["/users/<id>", "/products/<id>"],
            "HEAD": ["/users", "/products", "/orders"],
            "OPTIONS": ["/users", "/products", "/orders"]
        },
        "timestamp": datetime.now().isoformat()
    }), 200

@app.route('/users', methods=['GET', 'HEAD', 'OPTIONS'])
def users_endpoint():
    """Handle GET, HEAD, and OPTIONS requests for users collection"""
    if request.method == 'OPTIONS':
        # Handle preflight request for CORS
        response = make_response()
        response.headers['Allow'] = 'GET, POST, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Methods'] = 'GET, POST, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Max-Age'] = '86400'
        return response, 200
    
    elif request.method == 'HEAD':
        # HEAD request - return headers only, no body
        response = make_response()
        response.headers['Content-Type'] = 'application/json'
        response.headers['X-Total-Count'] = str(len(users_db))
        response.headers['X-API-Version'] = '1.0.0'
        return response, 200
    
    else:  # GET request
        # Process query parameters
        page = request.args.get('page', 1, type=int)
        limit = request.args.get('limit', 10, type=int)
        active = request.args.get('active', type=str)
        
        # Process headers
        user_agent = request.headers.get('User-Agent', 'Unknown')
        accept_language = request.headers.get('Accept-Language', 'en')
        
        # Filter users based on query parameters
        filtered_users = users_db
        if active is not None:
            active_bool = active.lower() == 'true'
            filtered_users = [user for user in users_db if user['active'] == active_bool]
        
        # Pagination (mock implementation)
        start_idx = (page - 1) * limit
        end_idx = start_idx + limit
        paginated_users = filtered_users[start_idx:end_idx]
        
        return jsonify({
            "users": paginated_users,
            "pagination": {
                "page": page,
                "limit": limit,
                "total": len(filtered_users),
                "pages": (len(filtered_users) + limit - 1) // limit
            },
            "headers_received": {
                "user_agent": user_agent,
                "accept_language": accept_language
            }
        }), 200

@app.route('/users/<int:user_id>', methods=['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'HEAD', 'OPTIONS'])
def user_operations(user_id):
    """Handle all operations for a specific user"""
    if request.method == 'OPTIONS':
        # Handle preflight request for CORS
        response = make_response()
        response.headers['Allow'] = 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Methods'] = 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Max-Age'] = '86400'
        return response, 200
    
    elif request.method == 'HEAD':
        # HEAD request - return headers only, no body
        user = next((user for user in users_db if user['id'] == user_id), None)
        if not user:
            return make_response(), 404
        
        response = make_response()
        response.headers['Content-Type'] = 'application/json'
        response.headers['X-User-ID'] = str(user_id)
        response.headers['X-User-Status'] = 'active' if user['active'] else 'inactive'
        return response, 200
    
    elif request.method == 'GET':
        """GET - Retrieve a specific user by ID with error handling"""
        user = next((user for user in users_db if user['id'] == user_id), None)
        
        if not user:
            return jsonify({
                "error": "User not found",
                "message": f"User with ID {user_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        return jsonify({
            "user": user,
            "timestamp": datetime.now().isoformat()
        }), 200
    
    elif request.method == 'POST':
        """POST - Create a new user with JSON body validation"""
        # Check if request has JSON content
        if not request.is_json:
            return jsonify({
                "error": "Invalid content type",
                "message": "Request must contain JSON data",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        data = request.get_json()       ## Get frontend json body
        
        # Validate required fields
        required_fields = ['username', 'email']
        missing_fields = [field for field in required_fields if field not in data]
        
        if missing_fields:
            return jsonify({
                "error": "Missing required fields",
                "message": f"Required fields missing: {', '.join(missing_fields)}",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        # Check if username already exists
        if any(user['username'] == data['username'] for user in users_db):
            return jsonify({
                "error": "Username already exists",
                "message": f"Username '{data['username']}' is already taken",
                "timestamp": datetime.now().isoformat()
            }), 409
        
        # Create new user
        new_user = {
            "id": max(user['id'] for user in users_db) + 1,
            "username": data['username'],
            "email": data['email'],
            "age": data.get('age', None),
            "active": data.get('active', True)
        }
        
        users_db.append(new_user)
        
        return jsonify({
            "message": "User created successfully",
            "user": new_user,
            "timestamp": datetime.now().isoformat()
        }), 201
    
    elif request.method == 'PUT':
        """PUT - Update an existing user completely"""
        if not request.is_json:
            return jsonify({
                "error": "Invalid content type",
                "message": "Request must contain JSON data",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        user_index = next((i for i, user in enumerate(users_db) if user['id'] == user_id), None)
        
        if user_index is None:
            return jsonify({
                "error": "User not found",
                "message": f"User with ID {user_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        data = request.get_json()
        
        # Update user completely
        users_db[user_index].update({
            "username": data.get('username', users_db[user_index]['username']),
            "email": data.get('email', users_db[user_index]['email']),
            "age": data.get('age', users_db[user_index]['age']),
            "active": data.get('active', users_db[user_index]['active'])
        })
        
        return jsonify({
            "message": "User updated successfully",
            "user": users_db[user_index],
            "timestamp": datetime.now().isoformat()
        }), 200
    
    elif request.method == 'PATCH':
        """PATCH - Partially update an existing user"""
        if not request.is_json:
            return jsonify({
                "error": "Invalid content type",
                "message": "Request must contain JSON data",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        user_index = next((i for i, user in enumerate(users_db) if user['id'] == user_id), None)
        
        if user_index is None:
            return jsonify({
                "error": "User not found",
                "message": f"User with ID {user_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        data = request.get_json()
        
        # Partially update user (only provided fields)
        if 'username' in data:
            # Check if username already exists (if changing)
            if data['username'] != users_db[user_index]['username']:
                if any(user['username'] == data['username'] for user in users_db):
                    return jsonify({
                        "error": "Username already exists",
                        "message": f"Username '{data['username']}' is already taken",
                        "timestamp": datetime.now().isoformat()
                    }), 409
            users_db[user_index]['username'] = data['username']
        
        if 'email' in data:
            users_db[user_index]['email'] = data['email']
        if 'age' in data:
            users_db[user_index]['age'] = data['age']
        if 'active' in data:
            users_db[user_index]['active'] = data['active']
        
        return jsonify({
            "message": "User partially updated successfully",
            "user": users_db[user_index],
            "timestamp": datetime.now().isoformat()
        }), 200
    
    elif request.method == 'DELETE':
        """DELETE - Delete a user by ID"""
        user_index = next((i for i, user in enumerate(users_db) if user['id'] == user_id), None)
        
        if user_index is None:
            return jsonify({
                "error": "User not found",
                "message": f"User with ID {user_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        deleted_user = users_db.pop(user_index)
        
        return jsonify({
            "message": "User deleted successfully",
            "deleted_user": deleted_user,
            "timestamp": datetime.now().isoformat()
        }), 200

@app.route('/products', methods=['GET', 'HEAD', 'OPTIONS'])
def products_endpoint():
    """Handle GET, HEAD, and OPTIONS requests for products collection"""
    if request.method == 'OPTIONS':
        # Handle preflight request for CORS
        response = make_response()
        response.headers['Allow'] = 'GET, POST, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Methods'] = 'GET, POST, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Max-Age'] = '86400'
        return response, 200
    
    elif request.method == 'HEAD':
        # HEAD request - return headers only, no body
        response = make_response()
        response.headers['Content-Type'] = 'application/json'
        response.headers['X-Total-Count'] = str(len(products_db))
        response.headers['X-API-Version'] = '1.0.0'
        response.headers['X-Categories'] = 'Electronics, General'
        return response, 200
    
    else:  # GET request
        # Process query parameters
        category = request.args.get('category', type=str)
        min_price = request.args.get('min_price', type=float)
        max_price = request.args.get('max_price', type=float)
        sort_by = request.args.get('sort_by', 'id')
        order = request.args.get('order', 'asc')
        
        # Filter products
        filtered_products = products_db
        if category:
            filtered_products = [p for p in filtered_products if p['category'].lower() == category.lower()]
        if min_price is not None:
            filtered_products = [p for p in filtered_products if p['price'] >= min_price]
        if max_price is not None:
            filtered_products = [p for p in filtered_products if p['price'] <= max_price]
        
        # Sort products
        reverse_order = order.lower() == 'desc'
        if sort_by in ['name', 'price', 'stock']:
            filtered_products.sort(key=lambda x: x[sort_by], reverse=reverse_order)
        
        return jsonify({
            "products": filtered_products,
            "filters_applied": {
                "category": category,
                "min_price": min_price,
                "max_price": max_price,
                "sort_by": sort_by,
                "order": order
            },
            "total_count": len(filtered_products)
        }), 200

@app.route('/products/<int:product_id>', methods=['GET', 'PUT', 'PATCH', 'DELETE', 'HEAD', 'OPTIONS'])
def product_operations(product_id):
    """Handle all operations for a specific product"""
    if request.method == 'OPTIONS':
        # Handle preflight request for CORS
        response = make_response()
        response.headers['Allow'] = 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Methods'] = 'GET, PUT, PATCH, DELETE, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Max-Age'] = '86400'
        return response, 200
    
    elif request.method == 'HEAD':
        # HEAD request - return headers only, no body
        product = next((product for product in products_db if product['id'] == product_id), None)
        if not product:
            return make_response(), 404
        
        response = make_response()
        response.headers['Content-Type'] = 'application/json'
        response.headers['X-Product-ID'] = str(product_id)
        response.headers['X-Product-Category'] = product['category']
        response.headers['X-Product-Stock'] = str(product['stock'])
        return response, 200
    
    elif request.method == 'GET':
        """GET - Retrieve a specific product by ID"""
        product = next((product for product in products_db if product['id'] == product_id), None)
        
        if not product:
            return jsonify({
                "error": "Product not found",
                "message": f"Product with ID {product_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        return jsonify({
            "product": product,
            "timestamp": datetime.now().isoformat()
        }), 200
    
    elif request.method == 'POST':
        """POST - Create a new product with validation"""
        if not request.is_json:
            return jsonify({
                "error": "Invalid content type",
                "message": "Request must contain JSON data",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        data = request.get_json()
        
        # Validate required fields
        required_fields = ['name', 'price']
        missing_fields = [field for field in required_fields if field not in data]
        
        if missing_fields:
            return jsonify({
                "error": "Missing required fields",
                "message": f"Required fields missing: {', '.join(missing_fields)}",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        # Validate price
        if data['price'] <= 0:
            return jsonify({
                "error": "Invalid price",
                "message": "Price must be greater than 0",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        # Create new product
        new_product = {
            "id": max(product['id'] for product in products_db) + 1,
            "name": data['name'],
            "price": data['price'],
            "category": data.get('category', 'General'),
            "stock": data.get('stock', 0)
        }
        
        products_db.append(new_product)
        
        return jsonify({
            "message": "Product created successfully",
            "product": new_product,
            "timestamp": datetime.now().isoformat()
        }), 201
    
    elif request.method == 'PUT':
        """PUT - Update an existing product completely"""
        if not request.is_json:
            return jsonify({
                "error": "Invalid content type",
                "message": "Request must contain JSON data",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        product_index = next((i for i, product in enumerate(products_db) if product['id'] == product_id), None)
        
        if product_index is None:
            return jsonify({
                "error": "Product not found",
                "message": f"Product with ID {product_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        data = request.get_json()
        
        # Update product completely
        products_db[product_index].update({
            "name": data.get('name', products_db[product_index]['name']),
            "price": data.get('price', products_db[product_index]['price']),
            "category": data.get('category', products_db[product_index]['category']),
            "stock": data.get('stock', products_db[product_index]['stock'])
        })
        
        return jsonify({
            "message": "Product updated successfully",
            "product": products_db[product_index],
            "timestamp": datetime.now().isoformat()
        }), 200
    
    elif request.method == 'PATCH':
        """PATCH - Partially update an existing product"""
        if not request.is_json:
            return jsonify({
                "error": "Invalid content type",
                "message": "Request must contain JSON data",
                "timestamp": datetime.now().isoformat()
            }), 400
        
        product_index = next((i for i, product in enumerate(products_db) if product['id'] == product_id), None)
        
        if product_index is None:
            return jsonify({
                "error": "Product not found",
                "message": f"Product with ID {product_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        data = request.get_json()
        
        # Partially update product (only provided fields)
        if 'name' in data:
            products_db[product_index]['name'] = data['name']
        if 'price' in data:
            if data['price'] <= 0:
                return jsonify({
                    "error": "Invalid price",
                    "message": "Price must be greater than 0",
                    "timestamp": datetime.now().isoformat()
                }), 400
            products_db[product_index]['price'] = data['price']
        if 'category' in data:
            products_db[product_index]['category'] = data['category']
        if 'stock' in data:
            products_db[product_index]['stock'] = data['stock']
        
        return jsonify({
            "message": "Product partially updated successfully",
            "product": products_db[product_index],
            "timestamp": datetime.now().isoformat()
        }), 200
    
    elif request.method == 'DELETE':
        """DELETE - Delete a product by ID"""
        product_index = next((i for i, product in enumerate(products_db) if product['id'] == product_id), None)
        
        if product_index is None:
            return jsonify({
                "error": "Product not found",
                "message": f"Product with ID {product_id} does not exist",
                "timestamp": datetime.now().isoformat()
            }), 404
        
        deleted_product = products_db.pop(product_index)
        
        return jsonify({
            "message": "Product deleted successfully",
            "deleted_product": deleted_product,
            "timestamp": datetime.now().isoformat()
        }), 200

@app.route('/products', methods=['POST'])
def create_product():
    """POST - Create a new product with validation"""
    if not request.is_json:
        return jsonify({
            "error": "Invalid content type",
            "message": "Request must contain JSON data",
            "timestamp": datetime.now().isoformat()
        }), 400
    
    data = request.get_json()
    
    # Validate required fields
    required_fields = ['name', 'price']
    missing_fields = [field for field in required_fields if field not in data]
    
    if missing_fields:
        return jsonify({
            "error": "Missing required fields",
            "message": f"Required fields missing: {', '.join(missing_fields)}",
            "timestamp": datetime.now().isoformat()
        }), 400
    
    # Validate price
    if data['price'] <= 0:
        return jsonify({
            "error": "Invalid price",
            "message": "Price must be greater than 0",
            "timestamp": datetime.now().isoformat()
        }), 400
    
    # Create new product
    new_product = {
        "id": max(product['id'] for product in products_db) + 1,
        "name": data['name'],
        "price": data['price'],
        "category": data.get('category', 'General'),
        "stock": data.get('stock', 0)
    }
    
    products_db.append(new_product)
    
    return jsonify({
        "message": "Product created successfully",
        "product": new_product,
        "timestamp": datetime.now().isoformat()
    }), 201

@app.route('/orders', methods=['GET', 'HEAD', 'OPTIONS'])
def orders_endpoint():
    """Handle GET, HEAD, and OPTIONS requests for orders collection"""
    if request.method == 'OPTIONS':
        # Handle preflight request for CORS
        response = make_response()
        response.headers['Allow'] = 'GET, POST, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Methods'] = 'GET, POST, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Max-Age'] = '86400'
        return response, 200
    
    elif request.method == 'HEAD':
        # HEAD request - return headers only, no body
        response = make_response()
        response.headers['Content-Type'] = 'application/json'
        response.headers['X-Total-Count'] = str(len(orders_db))
        response.headers['X-API-Version'] = '1.0.0'
        response.headers['X-Order-Statuses'] = 'pending, completed, cancelled'
        return response, 200
    
    else:  # GET request
        # Process query parameters
        user_id = request.args.get('user_id', type=int)
        status = request.args.get('status', type=str)
        
        # Filter orders
        filtered_orders = orders_db
        if user_id:
            filtered_orders = [order for order in orders_db if order['user_id'] == user_id]
        if status:
            filtered_orders = [order for order in filtered_orders if order['status'].lower() == status.lower()]
        
        # Enrich orders with user and product details
        enriched_orders = []
        for order in filtered_orders:
            user = next((u for u in users_db if u['id'] == order['user_id']), None)
            product = next((p for p in products_db if p['id'] == order['product_id']), None)
            
            enriched_order = order.copy()
            enriched_order['user'] = user
            enriched_order['product'] = product
            enriched_orders.append(enriched_order)
        
        return jsonify({
            "orders": enriched_orders,
            "total_count": len(enriched_orders),
            "filters_applied": {
                "user_id": user_id,
                "status": status
            }
        }), 200

@app.route('/orders', methods=['POST'])
def create_order():
    """POST - Create a new order with complex validation"""
    if not request.is_json:
        return jsonify({
            "error": "Invalid content type",
            "message": "Request must contain JSON data",
            "timestamp": datetime.now().isoformat()
        }), 400
    
    data = request.get_json()
    
    # Validate required fields
    required_fields = ['user_id', 'product_id', 'quantity']
    missing_fields = [field for field in required_fields if field not in data]
    
    if missing_fields:
        return jsonify({
            "error": "Missing required fields",
            "message": f"Required fields missing: {', '.join(missing_fields)}",
            "timestamp": datetime.now().isoformat()
        }), 400
    
    # Validate user exists
    user = next((u for u in users_db if u['id'] == data['user_id']), None)
    if not user:
        return jsonify({
            "error": "User not found",
            "message": f"User with ID {data['user_id']} does not exist",
            "timestamp": datetime.now().isoformat()
        }), 404
    
    # Validate product exists
    product = next((p for p in products_db if p['id'] == data['product_id']), None)
    if not product:
        return jsonify({
            "error": "Product not found",
            "message": f"Product with ID {data['product_id']} does not exist",
            "timestamp": datetime.now().isoformat()
        }), 404
    
    # Validate quantity
    if data['quantity'] <= 0:
        return jsonify({
            "error": "Invalid quantity",
            "message": "Quantity must be greater than 0",
            "timestamp": datetime.now().isoformat()
        }), 400
    
    # Check stock availability
    if product['stock'] < data['quantity']:
        return jsonify({
            "error": "Insufficient stock",
            "message": f"Only {product['stock']} items available in stock",
            "timestamp": datetime.now().isoformat()
        }), 422
    
    # Calculate total
    total = product['price'] * data['quantity']
    
    # Create new order
    new_order = {
        "id": max(order['id'] for order in orders_db) + 1,
        "user_id": data['user_id'],
        "product_id": data['product_id'],
        "quantity": data['quantity'],
        "total": total,
        "status": "pending"
    }
    
    orders_db.append(new_order)
    
    # Update product stock
    product['stock'] -= data['quantity']
    
    return jsonify({
        "message": "Order created successfully",
        "order": new_order,
        "timestamp": datetime.now().isoformat()
    }), 200

@app.route('/health', methods=['GET', 'HEAD', 'OPTIONS'])
def health_check():
    """Health check endpoint for monitoring"""
    if request.method == 'OPTIONS':
        response = make_response()
        response.headers['Allow'] = 'GET, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Methods'] = 'GET, HEAD, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Max-Age'] = '86400'
        return response, 200
    
    elif request.method == 'HEAD':
        response = make_response()
        response.headers['Content-Type'] = 'application/json'
        response.headers['X-Status'] = 'healthy'
        response.headers['X-Timestamp'] = datetime.now().isoformat()
        return response, 200
    
    else:  # GET request
        return jsonify({
            "status": "healthy",
            "timestamp": datetime.now().isoformat(),
            "database": {
                "users_count": len(users_db),
                "products_count": len(products_db),
                "orders_count": len(orders_db)
            }
        }), 200

@app.errorhandler(404)
def not_found(error):
    """Global 404 error handler"""
    return jsonify({
        "error": "Not Found",
        "message": "The requested resource was not found",
        "timestamp": datetime.now().isoformat()
    }), 404

@app.errorhandler(405)
def method_not_allowed(error):
    """Global 405 error handler"""
    return jsonify({
        "error": "Method Not Allowed",
        "message": "The HTTP method is not allowed for this endpoint",
        "timestamp": datetime.now().isoformat()
    }), 405

@app.errorhandler(500)
def internal_server_error(error):
    """Global 500 error handler"""
    return jsonify({
        "error": "Internal Server Error",
        "message": "An unexpected error occurred",
        "timestamp": datetime.now().isoformat()
    }), 500

if __name__ == '__main__':
    print("🚀 Starting Flask RESTful API Demo...")
    print("📚 This demo showcases:")
    print("   - All HTTP methods (GET, POST, PUT, PATCH, DELETE, HEAD, OPTIONS)")
    print("   - Header processing and validation")
    print("   - Query parameter handling")
    print("   - JSON body parsing and validation")
    print("   - Various HTTP status codes (200, 201, 400, 404, 409, 422, 500)")
    print("   - Error handling and custom error responses")
    print("   - Mock database operations")
    print("   - CORS preflight handling")
    print("\n🌐 Available endpoints:")
    print("   GET     / - Welcome and API info")
    print("   GET     /users - List users with filtering")
    print("   HEAD    /users - Get user collection headers")
    print("   OPTIONS /users - Get allowed methods")
    print("   GET     /users/<id> - Get specific user")
    print("   PUT     /users/<id> - Update user completely")
    print("   PATCH   /users/<id> - Partially update user")
    print("   DELETE  /users/<id> - Delete user")
    print("   HEAD    /users/<id> - Get user headers")
    print("   OPTIONS /users/<id> - Get allowed methods")
    print("   POST    /users - Create new user")
    print("   GET     /products - List products with filtering")
    print("   HEAD    /products - Get product collection headers")
    print("   OPTIONS /products - Get allowed methods")
    print("   GET     /products/<id> - Get specific product")
    print("   PUT     /products/<id> - Update product completely")
    print("   PATCH   /products/<id> - Partially update product")
    print("   DELETE  /products/<id> - Delete product")
    print("   HEAD    /products/<id> - Get product headers")
    print("   OPTIONS /products/<id> - Get allowed methods")
    print("   POST    /products - Create new product")
    print("   GET     /orders - List orders with details")
    print("   HEAD    /orders - Get order collection headers")
    print("   OPTIONS /orders - Get allowed methods")
    print("   POST    /orders - Create new order")
    print("   GET     /health - Health check")
    print("   HEAD    /health - Health check headers")
    print("   OPTIONS /health - Health check methods")
    print("\n🔧 Test with Postman or curl!")
    
    app.run(debug=True, host='0.0.0.0', port=54321)
    # URL: http://localhost:54321/endpoints
    # RESTFul API : URL+Endpoints
    # Method: GET, POST, PUT, PATCH, DELETE, HEAD, OPTIONS
    # Headers, Parameters, Request Body (JSON)
    # Response (JSON)