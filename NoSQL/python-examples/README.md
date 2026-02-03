# Python MongoDB Integration - Complete Guide

This directory contains comprehensive Python examples for working with MongoDB using PyMongo.

## Table of Contents

1. [Setup and Installation](#setup-and-installation)
2. [File Overview](#file-overview)
3. [Running the Examples](#running-the-examples)
4. [Code Examples Summary](#code-examples-summary)
5. [Best Practices](#best-practices)
6. [Common Patterns](#common-patterns)

---

## Setup and Installation

### Prerequisites

- Python 3.7 or higher
- MongoDB installed and running (local or remote)
- pip (Python package installer)

### Installation Steps

1. **Install Python dependencies:**

```bash
cd python-examples
pip install -r requirements.txt
```

2. **Verify MongoDB is running:**

```bash
# Check if MongoDB is running
mongosh --eval "db.adminCommand('ping')"
```

3. **Update connection string (if needed):**

If your MongoDB is not running on `localhost:27017`, update the connection string in each Python file:

```python
# For local MongoDB
client = MongoClient("mongodb://localhost:27017/")

# For MongoDB Atlas (cloud)
client = MongoClient("mongodb+srv://username:password@cluster.mongodb.net/")

# For remote MongoDB with authentication
client = MongoClient("mongodb://username:password@host:port/database")
```

---

## File Overview

### 01_basic_connection.py
- Connect to MongoDB
- List databases and collections
- Get server information
- Basic connection management

### 02_create_operations.py
- Insert single document (`insert_one`)
- Insert multiple documents (`insert_many`)
- Insert with nested objects and arrays
- Insert with custom `_id`
- Bulk insert operations

### 03_read_operations.py
- Find all documents
- Find with query filters
- Find one document
- Projection (select specific fields)
- Sorting
- Pagination (limit and skip)
- Query nested fields
- Array operators
- Count and distinct operations

### 04_update_operations.py
- Update one document (`update_one`)
- Update many documents (`update_many`)
- Update operators (`$set`, `$unset`, `$inc`, `$mul`, etc.)
- Update nested fields
- Update arrays (`$push`, `$pull`, `$addToSet`, etc.)
- Replace documents (`replace_one`)
- Upsert operations
- Find and update (`find_one_and_update`)

### 05_delete_operations.py
- Delete one document (`delete_one`)
- Delete many documents (`delete_many`)
- Find and delete (`find_one_and_delete`)
- Delete with conditions
- Delete collections
- Safe deletion patterns

### 06_advanced_operations.py
- Aggregation pipeline
- Index creation and management
- Text search
- Bulk operations
- Transactions
- Advanced projections
- Date operations
- $lookup (joins)

---

## Running the Examples

### Run Individual Files

```bash
# Basic connection
python 01_basic_connection.py

# CREATE operations
python 02_create_operations.py

# READ operations
python 03_read_operations.py

# UPDATE operations
python 04_update_operations.py

# DELETE operations
python 05_delete_operations.py

# Advanced operations
python 06_advanced_operations.py
```

### Run in Order

For best results, run the files in sequence:

```bash
# 1. First, establish connection
python 01_basic_connection.py

# 2. Create some data
python 02_create_operations.py

# 3. Read the data
python 03_read_operations.py

# 4. Update the data
python 04_update_operations.py

# 5. Delete some data
python 05_delete_operations.py

# 6. Try advanced operations
python 06_advanced_operations.py
```

---

## Code Examples Summary

### Basic Connection

```python
from pymongo import MongoClient

# Connect to MongoDB
client = MongoClient("mongodb://localhost:27017/")

# Get database
db = client["my_database"]

# Get collection
collection = db["my_collection"]

# Close connection
client.close()
```

### CREATE Operations

```python
# Insert one document
result = collection.insert_one({
    "name": "John Doe",
    "age": 30,
    "email": "john@example.com"
})
print(f"Inserted ID: {result.inserted_id}")

# Insert many documents
result = collection.insert_many([
    {"name": "Jane", "age": 25},
    {"name": "Bob", "age": 35}
])
print(f"Inserted IDs: {result.inserted_ids}")
```

### READ Operations

```python
# Find all documents
for doc in collection.find():
    print(doc)

# Find with query
users = collection.find({"age": {"$gt": 25}})

# Find one
user = collection.find_one({"email": "john@example.com"})

# Count
count = collection.count_documents({"isActive": True})
```

### UPDATE Operations

```python
# Update one
result = collection.update_one(
    {"email": "john@example.com"},
    {"$set": {"age": 31}}
)

# Update many
result = collection.update_many(
    {"isActive": True},
    {"$set": {"lastLogin": datetime.now()}}
)

# Upsert
result = collection.update_one(
    {"email": "new@example.com"},
    {"$set": {"name": "New User"}},
    upsert=True
)
```

### DELETE Operations

```python
# Delete one
result = collection.delete_one({"email": "john@example.com"})

# Delete many
result = collection.delete_many({"isActive": False})

# Find and delete
deleted = collection.find_one_and_delete({"email": "john@example.com"})
```

### Aggregation Pipeline

```python
pipeline = [
    {"$match": {"isActive": True}},
    {"$group": {
        "_id": "$city",
        "count": {"$sum": 1},
        "avgAge": {"$avg": "$age"}
    }},
    {"$sort": {"count": -1}}
]

results = collection.aggregate(pipeline)
```

---

## Best Practices

### 1. Connection Management

```python
# Use context manager or close explicitly
client = MongoClient("mongodb://localhost:27017/")
try:
    db = client["my_database"]
    # ... operations ...
finally:
    client.close()

# Or use context manager (Python 3.7+)
from contextlib import contextmanager

@contextmanager
def get_db():
    client = MongoClient("mongodb://localhost:27017/")
    try:
        yield client["my_database"]
    finally:
        client.close()

# Usage
with get_db() as db:
    collection = db["users"]
    # ... operations ...
```

### 2. Error Handling

```python
from pymongo.errors import DuplicateKeyError, OperationFailure

try:
    collection.insert_one({"email": "john@example.com"})
except DuplicateKeyError:
    print("Email already exists")
except OperationFailure as e:
    print(f"Operation failed: {e}")
```

### 3. Indexes

```python
# Create indexes for frequently queried fields
collection.create_index("email", unique=True)
collection.create_index([("city", 1), ("age", -1)])
```

### 4. Projection

```python
# Always use projection to limit returned data
users = collection.find(
    {"isActive": True},
    {"name": 1, "email": 1, "_id": 0}
)
```

### 5. Bulk Operations

```python
# Use bulk_write for multiple operations
operations = [
    {"insertOne": {"document": {...}}},
    {"updateOne": {"filter": {...}, "update": {...}}},
    {"deleteOne": {"filter": {...}}}
]
collection.bulk_write(operations)
```

### 6. Transactions

```python
# Use transactions for related operations
with client.start_session() as session:
    with session.start_transaction():
        collection1.insert_one({...}, session=session)
        collection2.update_one({...}, {...}, session=session)
        session.commit_transaction()
```

---

## Common Patterns

### Pattern 1: Pagination

```python
def get_users(page=1, page_size=10):
    skip = (page - 1) * page_size
    users = collection.find().skip(skip).limit(page_size)
    total = collection.count_documents({})
    return {
        "users": list(users),
        "total": total,
        "page": page,
        "page_size": page_size
    }
```

### Pattern 2: Search with Filters

```python
def search_users(name=None, city=None, min_age=None, max_age=None):
    query = {}
    if name:
        query["name"] = {"$regex": name, "$options": "i"}
    if city:
        query["city"] = city
    if min_age or max_age:
        query["age"] = {}
        if min_age:
            query["age"]["$gte"] = min_age
        if max_age:
            query["age"]["$lte"] = max_age
    
    return list(collection.find(query))
```

### Pattern 3: Update or Insert (Upsert)

```python
def update_or_create_user(email, user_data):
    result = collection.update_one(
        {"email": email},
        {"$set": user_data},
        upsert=True
    )
    return result.upserted_id or collection.find_one({"email": email})["_id"]
```

### Pattern 4: Soft Delete

```python
def soft_delete_user(email):
    return collection.update_one(
        {"email": email},
        {"$set": {"deleted": True, "deletedAt": datetime.now()}}
    )

def get_active_users():
    return collection.find({"deleted": {"$ne": True}})
```

### Pattern 5: Aggregation for Statistics

```python
def get_user_statistics():
    pipeline = [
        {"$group": {
            "_id": "$city",
            "total": {"$sum": 1},
            "avgAge": {"$avg": "$age"},
            "maxAge": {"$max": "$age"},
            "minAge": {"$min": "$age"}
        }},
        {"$sort": {"total": -1}}
    ]
    return list(collection.aggregate(pipeline))
```

---

## Troubleshooting

### Common Issues

1. **Connection Error**
   - Verify MongoDB is running: `mongosh --eval "db.adminCommand('ping')"`
   - Check connection string
   - Verify network/firewall settings

2. **Authentication Error**
   - Check username and password
   - Verify authentication database
   - Ensure user has proper permissions

3. **Duplicate Key Error**
   - Check for unique indexes
   - Verify `_id` values are unique
   - Use upsert for update-or-insert operations

4. **Performance Issues**
   - Create indexes on frequently queried fields
   - Use projection to limit returned data
   - Use pagination for large result sets
   - Analyze queries with `explain()`

---

## Additional Resources

- [PyMongo Documentation](https://pymongo.readthedocs.io/)
- [MongoDB Python Driver](https://github.com/mongodb/mongo-python-driver)
- [MongoDB Manual](https://docs.mongodb.com/manual/)
- [MongoDB University](https://university.mongodb.com/)

---

## Exercises

1. **Create a user management system:**
   - Create, read, update, delete users
   - Search users by name, email, city
   - Get user statistics by city

2. **Build a product catalog:**
   - Manage products with categories
   - Filter products by price range
   - Get product statistics by category

3. **Implement a blog system:**
   - Create posts with tags
   - Search posts by title/content
   - Get popular tags using aggregation

---

**Happy Coding! 🚀**

