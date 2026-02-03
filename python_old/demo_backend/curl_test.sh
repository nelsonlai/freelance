#!/usr/bin/env bash
# Run all curl commands from the Postman collection against the backend.
# Usage: BASE_URL=http://localhost:5000 ./run_api_curls.sh

BASE_URL="${BASE_URL:-http://localhost:54321}"
CURL="curl -i -s"

echo "Base URL: $BASE_URL"
echo

# Welcome & Information
echo "=== Get API Info ==="
$CURL "$BASE_URL/"

# User Management
echo
echo "=== Get All Users (with query + headers) ==="
$CURL -H "Accept-Language: en-US" -H "User-Agent: PostmanRuntime/7.32.3" "$BASE_URL/users?page=1&limit=10&active=true"

echo
echo "=== HEAD Users Collection ==="
curl -I -s "$BASE_URL/users"

echo
echo "=== OPTIONS Users Collection ==="
$CURL -X OPTIONS "$BASE_URL/users"

echo
echo "=== Get User by ID ==="
$CURL "$BASE_URL/users/1"

echo
echo "=== HEAD User by ID ==="
curl -I -s "$BASE_URL/users/1"

echo
echo "=== OPTIONS User by ID ==="
$CURL -X OPTIONS "$BASE_URL/users/1"

echo
echo "=== Create New User (POST) ==="
$CURL -X POST "$BASE_URL/users" \
  -H "Content-Type: application/json" \
  -d '{"username":"alice_wong","email":"alice@example.com","age":28,"active":true}'

echo
echo "=== Update User (PUT) ==="
$CURL -X PUT "$BASE_URL/users/1" \
  -H "Content-Type: application/json" \
  -d '{"username":"john_doe_updated","email":"john.updated@example.com","age":26,"active":true}'

echo
echo "=== Partially Update User (PATCH) ==="
$CURL -X PATCH "$BASE_URL/users/1" \
  -H "Content-Type: application/json" \
  -d '{"age":27,"active":false}'

echo
echo "=== Delete User ==="
$CURL -X DELETE "$BASE_URL/users/3"

# Product Management
echo
echo "=== Get All Products (with query) ==="
$CURL "$BASE_URL/products?category=Electronics&min_price=50.0&max_price=1000.0&sort_by=price&order=asc"

echo
echo "=== HEAD Products Collection ==="
curl -I -s "$BASE_URL/products"

echo
echo "=== OPTIONS Products Collection ==="
$CURL -X OPTIONS "$BASE_URL/products"

echo
echo "=== Get Product by ID ==="
$CURL "$BASE_URL/products/1"

echo
echo "=== HEAD Product by ID ==="
curl -I -s "$BASE_URL/products/1"

echo
echo "=== OPTIONS Product by ID ==="
$CURL -X OPTIONS "$BASE_URL/products/1"

echo
echo "=== Create New Product (POST) ==="
$CURL -X POST "$BASE_URL/products" \
  -H "Content-Type: application/json" \
  -d '{"name":"Wireless Headphones","price":149.99,"category":"Electronics","stock":25}'

echo
echo "=== Update Product (PUT) ==="
$CURL -X PUT "$BASE_URL/products/1" \
  -H "Content-Type: application/json" \
  -d '{"name":"Gaming Laptop","price":1299.99,"category":"Electronics","stock":45}'

echo
echo "=== Partially Update Product (PATCH) ==="
$CURL -X PATCH "$BASE_URL/products/1" \
  -H "Content-Type: application/json" \
  -d '{"price":1399.99,"stock":40}'

echo
echo "=== Delete Product ==="
$CURL -X DELETE "$BASE_URL/products/3"

# Order Management
echo
echo "=== Get All Orders ==="
$CURL "$BASE_URL/orders?user_id=1&status=pending"

echo
echo "=== HEAD Orders Collection ==="
curl -I -s "$BASE_URL/orders"

echo
echo "=== OPTIONS Orders Collection ==="
$CURL -X OPTIONS "$BASE_URL/orders"

echo
echo "=== Create New Order (POST) ==="
$CURL -X POST "$BASE_URL/orders" \
  -H "Content-Type: application/json" \
  -d '{"user_id":1,"product_id":2,"quantity":3}'

# System & Health
echo
echo "=== Health Check (GET) ==="
$CURL "$BASE_URL/health"

echo
echo "=== Health Check (HEAD) ==="
curl -I -s "$BASE_URL/health"

echo
echo "=== Health Check (OPTIONS) ==="
$CURL -X OPTIONS "$BASE_URL/health"

# Error Testing
echo
echo "=== 400 Bad Request - Missing Fields ==="
$CURL -X POST "$BASE_URL/users" \
  -H "Content-Type: application/json" \
  -d '{"username":"test_user"}'

echo
echo "=== 404 Not Found - Invalid User ID ==="
$CURL "$BASE_URL/users/999"

echo
echo "=== 409 Conflict - Duplicate Username ==="
$CURL -X POST "$BASE_URL/users" \
  -H "Content-Type: application/json" \
  -d '{"username":"john_doe","email":"john2@example.com"}'

echo
echo "=== 422 Unprocessable Entity - Insufficient Stock ==="
$CURL -X POST "$BASE_URL/orders" \
  -H "Content-Type: application/json" \
  -d '{"user_id":1,"product_id":2,"quantity":999}'

echo
echo "All requests complete."