# MongoDB Quick Reference Guide

A quick reference for common MongoDB operations in both mongosh and Python.

## Table of Contents

1. [MongoDB Shell (mongosh)](#mongodb-shell-mongosh)
2. [Python (PyMongo)](#python-pymongo)
3. [Common Operators](#common-operators)
4. [Data Types](#data-types)

---

## MongoDB Shell (mongosh)

### Connection

```javascript
// Connect to local MongoDB
mongosh

// Connect to specific database
mongosh myDatabase

// Connect with authentication
mongosh -u username -p password --authenticationDatabase admin
```

### Database Operations

```javascript
// Show databases
show dbs

// Switch database
use myDatabase

// Current database
db

// Show collections
show collections

// Create collection
db.createCollection("myCollection")
```

### CREATE Operations

```javascript
// Insert one
db.users.insertOne({name: "John", age: 30})

// Insert many
db.users.insertMany([
  {name: "Jane", age: 25},
  {name: "Bob", age: 35}
])
```

### READ Operations

```javascript
// Find all
db.users.find()

// Find one
db.users.findOne({age: 30})

// Find with query
db.users.find({age: {$gt: 25}})

// Find with projection
db.users.find({}, {name: 1, email: 1, _id: 0})

// Sort
db.users.find().sort({age: -1})

// Limit and skip
db.users.find().limit(10).skip(20)

// Count
db.users.countDocuments({age: {$gt: 25}})
```

### UPDATE Operations

```javascript
// Update one
db.users.updateOne(
  {email: "john@example.com"},
  {$set: {age: 31}}
)

// Update many
db.users.updateMany(
  {isActive: true},
  {$set: {lastLogin: new Date()}}
)

// Upsert
db.users.updateOne(
  {email: "new@example.com"},
  {$set: {name: "New User"}},
  {upsert: true}
)

// Replace
db.users.replaceOne(
  {email: "john@example.com"},
  {name: "John", age: 32, email: "john@example.com"}
)
```

### DELETE Operations

```javascript
// Delete one
db.users.deleteOne({email: "john@example.com"})

// Delete many
db.users.deleteMany({isActive: false})

// Find and delete
db.users.findOneAndDelete({age: {$gt: 50}})

// Delete all (be careful!)
db.users.deleteMany({})
```

---

## Python (PyMongo)

### Connection

```python
from pymongo import MongoClient

# Connect
client = MongoClient("mongodb://localhost:27017/")

# Get database
db = client["my_database"]

# Get collection
collection = db["users"]

# Close
client.close()
```

### CREATE Operations

```python
# Insert one
result = collection.insert_one({
    "name": "John",
    "age": 30
})
print(result.inserted_id)

# Insert many
result = collection.insert_many([
    {"name": "Jane", "age": 25},
    {"name": "Bob", "age": 35}
])
print(result.inserted_ids)
```

### READ Operations

```python
# Find all
for doc in collection.find():
    print(doc)

# Find one
user = collection.find_one({"age": 30})

# Find with query
users = collection.find({"age": {"$gt": 25}})

# Find with projection
users = collection.find(
    {},
    {"name": 1, "email": 1, "_id": 0}
)

# Sort
users = collection.find().sort("age", -1)

# Limit and skip
users = collection.find().skip(20).limit(10)

# Count
count = collection.count_documents({"age": {"$gt": 25}})
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

# Replace
result = collection.replace_one(
    {"email": "john@example.com"},
    {"name": "John", "age": 32, "email": "john@example.com"}
)
```

### DELETE Operations

```python
# Delete one
result = collection.delete_one({"email": "john@example.com"})

# Delete many
result = collection.delete_many({"isActive": False})

# Find and delete
deleted = collection.find_one_and_delete({"age": {"$gt": 50}})

# Delete all (be careful!)
result = collection.delete_many({})
```

---

## Common Operators

### Comparison Operators

```javascript
// mongosh / Python
{age: {$gt: 25}}      // Greater than
{age: {$gte: 25}}     // Greater than or equal
{age: {$lt: 30}}      // Less than
{age: {$lte: 30}}     // Less than or equal
{age: {$ne: 30}}      // Not equal
{age: {$in: [25, 30, 35]}}    // In array
{age: {$nin: [25, 30]}}       // Not in array
```

### Logical Operators

```javascript
// AND
{$and: [{age: {$gt: 25}}, {isActive: true}]}

// OR
{$or: [{city: "NYC"}, {city: "LA"}]}

// NOT
{$not: {age: {$gt: 30}}}

// NOR
{$nor: [{age: {$lt: 25}}, {isActive: false}]}
```

### Update Operators

```javascript
// $set - Set field
{$set: {age: 31}}

// $unset - Remove field
{$unset: {middleName: ""}}

// $inc - Increment
{$inc: {age: 1}}

// $mul - Multiply
{$mul: {price: 1.1}}

// $min - Set minimum
{$min: {age: 25}}

// $max - Set maximum
{$max: {age: 50}}

// $rename - Rename field
{$rename: {city: "location"}}
```

### Array Operators

```javascript
// $push - Add to array
{$push: {hobbies: "reading"}}

// $addToSet - Add if not exists
{$addToSet: {hobbies: "reading"}}

// $pop - Remove first/last
{$pop: {hobbies: 1}}  // 1 = last, -1 = first

// $pull - Remove matching
{$pull: {hobbies: "reading"}}

// $pullAll - Remove multiple
{$pullAll: {hobbies: ["reading", "swimming"]}}
```

### Array Query Operators

```javascript
// Contains element
{hobbies: "reading"}

// All elements
{hobbies: {$all: ["reading", "swimming"]}}

// Array size
{hobbies: {$size: 3}}

// Element match
{skills: {$elemMatch: {level: "expert"}}}
```

### Element Operators

```javascript
// Field exists
{email: {$exists: true}}

// Type check
{age: {$type: "number"}}
```

### String Operators

```javascript
// Regex (case-insensitive)
{name: {$regex: "john", $options: "i"}}

// Or using JavaScript regex
{name: /john/i}
```

---

## Data Types

### MongoDB BSON Types

```javascript
// String
{name: "John"}

// Number (Integer)
{age: 30}

// Number (Double)
{price: 99.99}

// Boolean
{isActive: true}

// Date
{createdAt: new Date()}

// Null
{middleName: null}

// Array
{hobbies: ["reading", "swimming"]}

// Object/Embedded Document
{address: {city: "NYC", zip: "10001"}}

// ObjectId
{_id: ObjectId("507f1f77bcf86cd799439011")}
```

### Python Types

```python
from datetime import datetime
from bson import ObjectId

# String
{"name": "John"}

# Integer
{"age": 30}

# Float
{"price": 99.99}

# Boolean
{"isActive": True}

# Date
{"createdAt": datetime.now()}

# None
{"middleName": None}

# List
{"hobbies": ["reading", "swimming"]}

# Dict
{"address": {"city": "NYC", "zip": "10001"}}

# ObjectId
{"_id": ObjectId()}
```

---

## Aggregation Pipeline

### Basic Pipeline

```javascript
// mongosh
db.users.aggregate([
  {$match: {isActive: true}},
  {$group: {
    _id: "$city",
    count: {$sum: 1},
    avgAge: {$avg: "$age"}
  }},
  {$sort: {count: -1}}
])
```

```python
# Python
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

### Common Pipeline Stages

```javascript
{$match: {...}}        // Filter documents
{$group: {...}}        // Group documents
{$project: {...}}     // Reshape documents
{$sort: {...}}        // Sort documents
{$limit: n}           // Limit results
{$skip: n}            // Skip documents
{$unwind: "$field"}   // Deconstruct array
{$lookup: {...}}      // Join collections
{$addFields: {...}}   // Add computed fields
```

---

## Indexes

### Create Indexes

```javascript
// mongosh
db.users.createIndex({email: 1})
db.users.createIndex({email: 1}, {unique: true})
db.users.createIndex({city: 1, age: -1})
```

```python
# Python
collection.create_index("email")
collection.create_index("email", unique=True)
collection.create_index([("city", 1), ("age", -1)])
```

### List Indexes

```javascript
// mongosh
db.users.getIndexes()
```

```python
# Python
for index in collection.list_indexes():
    print(index)
```

### Drop Index

```javascript
// mongosh
db.users.dropIndex({email: 1})
```

```python
# Python
collection.drop_index("email_1")
```

---

## Best Practices

1. **Always use indexes** on frequently queried fields
2. **Use projection** to limit returned data
3. **Use pagination** for large result sets
4. **Validate data** in application layer
5. **Use transactions** for related operations
6. **Monitor query performance** with explain()
7. **Handle errors** appropriately
8. **Close connections** when done

---

**Keep this reference handy while learning MongoDB! 📚**

