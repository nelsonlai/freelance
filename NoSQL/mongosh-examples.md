# MongoDB Shell (mongosh) - Complete CRUD Operations Guide

This guide provides comprehensive examples of all CRUD (Create, Read, Update, Delete) operations in MongoDB using the MongoDB Shell (mongosh).

## Table of Contents
1. [Getting Started](#getting-started)
2. [CREATE Operations](#create-operations)
3. [READ Operations](#read-operations)
4. [UPDATE Operations](#update-operations)
5. [DELETE Operations](#delete-operations)
6. [Advanced Operations](#advanced-operations)
7. [Indexes](#indexes)
8. [Aggregation Pipeline](#aggregation-pipeline)

---

## Getting Started

### Connect to MongoDB

```bash
# Connect to local MongoDB
mongosh

# Connect to specific database
mongosh myDatabase

# Connect with authentication
mongosh -u username -p password --authenticationDatabase admin
```

### Basic Commands

```javascript
// Show all databases
show dbs

// Switch to a database (creates if doesn't exist)
use myDatabase

// Show current database name
db

// Show all collections in current database
show collections

// Get database statistics
db.stats()

// Get collection statistics
db.collectionName.stats()
```

---

## CREATE Operations

### 1. Insert Single Document

**Syntax:**
```javascript
db.collectionName.insertOne(document)
```

**Example:**
```javascript
// Insert a single user document
db.users.insertOne({
  name: "John Doe",
  age: 30,
  email: "john@example.com",
  city: "New York",
  isActive: true,
  createdAt: new Date()
})

// Output:
// {
//   acknowledged: true,
//   insertedId: ObjectId("507f1f77bcf86cd799439011")
// }
```

### 2. Insert Multiple Documents

**Syntax:**
```javascript
db.collectionName.insertMany([document1, document2, ...])
```

**Example:**
```javascript
// Insert multiple users
db.users.insertMany([
  {
    name: "Jane Smith",
    age: 25,
    email: "jane@example.com",
    city: "Los Angeles",
    isActive: true,
    createdAt: new Date()
  },
  {
    name: "Bob Johnson",
    age: 35,
    email: "bob@example.com",
    city: "Chicago",
    isActive: false,
    createdAt: new Date()
  },
  {
    name: "Alice Williams",
    age: 28,
    email: "alice@example.com",
    city: "New York",
    isActive: true,
    createdAt: new Date()
  }
])

// Output:
// {
//   acknowledged: true,
//   insertedIds: {
//     '0': ObjectId("507f1f77bcf86cd799439012"),
//     '1': ObjectId("507f1f77bcf86cd799439013"),
//     '2': ObjectId("507f1f77bcf86cd799439014")
//   }
// }
```

### 3. Insert with Custom _id

**Example:**
```javascript
// Insert document with custom _id
db.users.insertOne({
  _id: "user001",
  name: "Charlie Brown",
  age: 40,
  email: "charlie@example.com"
})

// Note: _id must be unique. If it already exists, you'll get an error.
```

### 4. Insert Documents with Nested Objects

**Example:**
```javascript
db.users.insertOne({
  name: "David Lee",
  age: 32,
  email: "david@example.com",
  address: {
    street: "456 Oak Avenue",
    city: "San Francisco",
    state: "CA",
    zipCode: "94102",
    country: "USA"
  },
  contact: {
    phone: "555-1234",
    mobile: "555-5678"
  },
  createdAt: new Date()
})
```

### 5. Insert Documents with Arrays

**Example:**
```javascript
db.users.insertOne({
  name: "Emma Davis",
  age: 27,
  email: "emma@example.com",
  hobbies: ["reading", "swimming", "coding", "traveling"],
  skills: [
    { name: "Python", level: "expert" },
    { name: "JavaScript", level: "intermediate" },
    { name: "MongoDB", level: "beginner" }
  ],
  tags: ["developer", "tech-enthusiast"],
  createdAt: new Date()
})
```

### 6. Insert with Validation

**Example:**
```javascript
// MongoDB will validate data types
db.users.insertOne({
  name: "Frank Miller",
  age: "thirty-five",  // String instead of number
  email: "frank@example.com"
})
// This will insert successfully, but age will be stored as string
// Always validate data in your application layer
```

### 7. Insert with Timestamps

**Example:**
```javascript
db.users.insertOne({
  name: "Grace Wilson",
  age: 29,
  email: "grace@example.com",
  createdAt: new Date(),
  updatedAt: new Date(),
  timestamp: Date.now()  // Unix timestamp in milliseconds
})
```

---

## READ Operations

### 1. Find All Documents

**Syntax:**
```javascript
db.collectionName.find()
```

**Example:**
```javascript
// Get all users
db.users.find()

// Pretty print (formatted output)
db.users.find().pretty()

// Limit number of results
db.users.find().limit(5)

// Skip documents
db.users.find().skip(10)

// Combine limit and skip (pagination)
db.users.find().skip(0).limit(10)  // First page
db.users.find().skip(10).limit(10)  // Second page
```

### 2. Find One Document

**Syntax:**
```javascript
db.collectionName.findOne(query)
```

**Example:**
```javascript
// Find first document
db.users.findOne()

// Find specific document
db.users.findOne({ name: "John Doe" })

// Find by _id
db.users.findOne({ _id: ObjectId("507f1f77bcf86cd799439011") })
```

### 3. Find with Query Filters

#### Equality Query

```javascript
// Find users with specific age
db.users.find({ age: 30 })

// Find active users
db.users.find({ isActive: true })

// Find by email
db.users.find({ email: "john@example.com" })
```

#### Comparison Operators

```javascript
// Greater than
db.users.find({ age: { $gt: 25 } })  // age > 25

// Greater than or equal
db.users.find({ age: { $gte: 30 } })  // age >= 30

// Less than
db.users.find({ age: { $lt: 30 } })   // age < 30

// Less than or equal
db.users.find({ age: { $lte: 30 } })  // age <= 30

// Not equal
db.users.find({ age: { $ne: 30 } })   // age != 30

// In array
db.users.find({ age: { $in: [25, 30, 35] } })  // age in [25, 30, 35]

// Not in array
db.users.find({ age: { $nin: [25, 30] } })     // age not in [25, 30]

// Multiple conditions
db.users.find({ age: { $gt: 25, $lt: 35 } })  // 25 < age < 35
```

#### Logical Operators

```javascript
// AND (implicit)
db.users.find({ age: 30, isActive: true })

// AND (explicit)
db.users.find({ $and: [
  { age: { $gt: 25 } },
  { isActive: true }
]})

// OR
db.users.find({ $or: [
  { age: { $lt: 25 } },
  { age: { $gt: 35 } }
]})

// NOT
db.users.find({ $not: { age: { $gt: 30 } } })

// NOR (neither condition true)
db.users.find({ $nor: [
  { age: { $lt: 25 } },
  { isActive: false }
]})
```

#### Element Operators

```javascript
// Field exists
db.users.find({ email: { $exists: true } })

// Field doesn't exist
db.users.find({ email: { $exists: false } })

// Type check
db.users.find({ age: { $type: "number" } })
db.users.find({ age: { $type: "string" } })
```

#### Array Operators

```javascript
// All elements match
db.users.find({ hobbies: { $all: ["reading", "swimming"] } })

// Array size
db.users.find({ hobbies: { $size: 3 } })

// Element matches
db.users.find({ hobbies: "reading" })  // Array contains "reading"

// Array element at specific position
db.users.find({ "hobbies.0": "reading" })  // First element is "reading"

// Match array element with conditions
db.users.find({ "skills.level": "expert" })
```

#### String Operators

```javascript
// Case-sensitive regex
db.users.find({ name: /John/ })

// Case-insensitive regex
db.users.find({ name: /john/i })

// Starts with
db.users.find({ name: /^John/ })

// Ends with
db.users.find({ name: /Doe$/ })

// Contains
db.users.find({ name: /.*John.*/ })

// Using $regex operator
db.users.find({ name: { $regex: "John", $options: "i" } })
```

#### Nested Document Queries

```javascript
// Exact match (order matters)
db.users.find({ address: { city: "New York", state: "NY" } })

// Dot notation (recommended)
db.users.find({ "address.city": "New York" })
db.users.find({ "address.zipCode": "10001" })

// Nested conditions
db.users.find({ "address.city": { $in: ["New York", "Los Angeles"] } })
```

### 4. Projection (Select Specific Fields)

**Syntax:**
```javascript
db.collectionName.find(query, projection)
```

**Example:**
```javascript
// Include specific fields
db.users.find({}, { name: 1, email: 1, age: 1 })

// Exclude specific fields
db.users.find({}, { password: 0, _id: 0 })

// Mix include/exclude (only _id can be excluded with includes)
db.users.find({}, { name: 1, email: 1, _id: 0 })

// Project nested fields
db.users.find({}, { name: 1, "address.city": 1, "address.state": 1 })
```

### 5. Sorting

**Syntax:**
```javascript
db.collectionName.find().sort({ field: 1 })  // 1 = ascending, -1 = descending
```

**Example:**
```javascript
// Sort by age ascending
db.users.find().sort({ age: 1 })

// Sort by age descending
db.users.find().sort({ age: -1 })

// Sort by multiple fields
db.users.find().sort({ city: 1, age: -1 })  // Sort by city, then age

// Combine with other operations
db.users.find({ isActive: true })
  .sort({ age: -1 })
  .limit(10)
```

### 6. Count Documents

**Syntax:**
```javascript
db.collectionName.countDocuments(query)
```

**Example:**
```javascript
// Count all documents
db.users.countDocuments()

// Count with query
db.users.countDocuments({ age: { $gt: 30 } })

// Count active users
db.users.countDocuments({ isActive: true })
```

### 7. Distinct Values

**Syntax:**
```javascript
db.collectionName.distinct(field)
```

**Example:**
```javascript
// Get distinct cities
db.users.distinct("city")

// Get distinct values with query
db.users.distinct("city", { isActive: true })
```

### 8. Advanced Query Examples

```javascript
// Complex query combining multiple operators
db.users.find({
  $and: [
    { age: { $gte: 25, $lte: 40 } },
    { isActive: true },
    { $or: [
      { "address.city": "New York" },
      { "address.city": "Los Angeles" }
    ]},
    { hobbies: { $in: ["reading", "coding"] } }
  ]
}).sort({ age: 1 }).limit(20)

// Query with regex and array
db.users.find({
  name: { $regex: /^J/, $options: "i" },
  hobbies: { $size: { $gt: 2 } }
})
```

---

## UPDATE Operations

### 1. Update One Document

**Syntax:**
```javascript
db.collectionName.updateOne(filter, update, options)
```

**Example:**
```javascript
// Update single field
db.users.updateOne(
  { name: "John Doe" },
  { $set: { age: 31 } }
)

// Update multiple fields
db.users.updateOne(
  { email: "john@example.com" },
  { $set: { age: 31, city: "Boston" } }
)

// Output:
// {
//   acknowledged: true,
//   matchedCount: 1,
//   modifiedCount: 1,
//   upsertedId: null
// }
```

### 2. Update Multiple Documents

**Syntax:**
```javascript
db.collectionName.updateMany(filter, update, options)
```

**Example:**
```javascript
// Update all active users
db.users.updateMany(
  { isActive: true },
  { $set: { lastLogin: new Date() } }
)

// Increment age for all users
db.users.updateMany(
  {},
  { $inc: { age: 1 } }
)
```

### 3. Replace Document

**Syntax:**
```javascript
db.collectionName.replaceOne(filter, replacement)
```

**Example:**
```javascript
// Replace entire document (except _id)
db.users.replaceOne(
  { name: "John Doe" },
  {
    name: "John Doe",
    age: 32,
    email: "john.doe@example.com",
    city: "Boston",
    isActive: true,
    updatedAt: new Date()
  }
)
```

### 4. Update Operators

#### $set - Set Field Value

```javascript
// Set single field
db.users.updateOne(
  { name: "John Doe" },
  { $set: { city: "Boston" } }
)

// Set nested field
db.users.updateOne(
  { name: "John Doe" },
  { $set: { "address.city": "Boston" } }
)

// Set multiple fields
db.users.updateOne(
  { name: "John Doe" },
  { $set: { city: "Boston", age: 31, isActive: true } }
)
```

#### $unset - Remove Field

```javascript
// Remove field
db.users.updateOne(
  { name: "John Doe" },
  { $unset: { middleName: "" } }
)

// Remove nested field
db.users.updateOne(
  { name: "John Doe" },
  { $unset: { "address.zipCode": "" } }
)
```

#### $inc - Increment/Decrement

```javascript
// Increment by 1
db.users.updateOne(
  { name: "John Doe" },
  { $inc: { age: 1 } }
)

// Increment by specific amount
db.users.updateOne(
  { name: "John Doe" },
  { $inc: { age: 5 } }
)

// Decrement
db.users.updateOne(
  { name: "John Doe" },
  { $inc: { age: -1 } }
)

// Increment multiple fields
db.users.updateOne(
  { name: "John Doe" },
  { $inc: { age: 1, loginCount: 1 } }
)
```

#### $mul - Multiply

```javascript
// Multiply field value
db.users.updateOne(
  { name: "John Doe" },
  { $mul: { age: 1.1 } }  // Increase age by 10%
)
```

#### $min / $max - Set Minimum/Maximum

```javascript
// Set minimum value
db.users.updateOne(
  { name: "John Doe" },
  { $min: { age: 25 } }  // Only update if current age < 25
)

// Set maximum value
db.users.updateOne(
  { name: "John Doe" },
  { $max: { age: 50 } }  // Only update if current age > 50
)
```

#### $rename - Rename Field

```javascript
// Rename field
db.users.updateOne(
  { name: "John Doe" },
  { $rename: { "city": "location" } }
)

// Rename nested field
db.users.updateOne(
  { name: "John Doe" },
  { $rename: { "address.street": "address.streetAddress" } }
)
```

#### Array Update Operators

**$push - Add to Array**

```javascript
// Add single element
db.users.updateOne(
  { name: "John Doe" },
  { $push: { hobbies: "gaming" } }
)

// Add multiple elements
db.users.updateOne(
  { name: "John Doe" },
  { $push: { hobbies: { $each: ["gaming", "photography"] } } }
)

// Add with position
db.users.updateOne(
  { name: "John Doe" },
  { $push: { hobbies: { $each: ["gaming"], $position: 0 } } }
)

// Add with conditions
db.users.updateOne(
  { name: "John Doe" },
  { $push: { hobbies: { $each: ["gaming"], $slice: 5 } } }  // Keep only 5 elements
)
```

**$addToSet - Add if Not Exists**

```javascript
// Add only if not already in array
db.users.updateOne(
  { name: "John Doe" },
  { $addToSet: { hobbies: "reading" } }
)

// Add multiple unique values
db.users.updateOne(
  { name: "John Doe" },
  { $addToSet: { hobbies: { $each: ["gaming", "photography"] } } }
)
```

**$pop - Remove from Array**

```javascript
// Remove last element
db.users.updateOne(
  { name: "John Doe" },
  { $pop: { hobbies: 1 } }
)

// Remove first element
db.users.updateOne(
  { name: "John Doe" },
  { $pop: { hobbies: -1 } }
)
```

**$pull - Remove Matching Elements**

```javascript
// Remove specific value
db.users.updateOne(
  { name: "John Doe" },
  { $pull: { hobbies: "reading" } }
)

// Remove matching condition
db.users.updateOne(
  { name: "John Doe" },
  { $pull: { skills: { level: "beginner" } } }
)

// Remove multiple values
db.users.updateOne(
  { name: "John Doe" },
  { $pull: { hobbies: { $in: ["reading", "swimming"] } } }
)
```

**$pullAll - Remove All Matching Values**

```javascript
db.users.updateOne(
  { name: "John Doe" },
  { $pullAll: { hobbies: ["reading", "swimming"] } }
)
```

#### Update Array Elements

```javascript
// Update element at specific index
db.users.updateOne(
  { name: "John Doe" },
  { $set: { "hobbies.0": "new hobby" } }
)

// Update all matching array elements
db.users.updateOne(
  { name: "John Doe", "skills.name": "Python" },
  { $set: { "skills.$.level": "expert" } }  // $ refers to matched element
)

// Update all array elements
db.users.updateOne(
  { name: "John Doe" },
  { $set: { "hobbies.$[]": "updated" } }  // Updates all elements
)
```

### 5. Upsert (Insert if Not Exists)

**Syntax:**
```javascript
db.collectionName.updateOne(filter, update, { upsert: true })
```

**Example:**
```javascript
// Update if exists, insert if not
db.users.updateOne(
  { email: "newuser@example.com" },
  {
    $set: {
      name: "New User",
      age: 25,
      email: "newuser@example.com",
      createdAt: new Date()
    }
  },
  { upsert: true }
)
```

### 6. Update Options

```javascript
// Update with options
db.users.updateOne(
  { name: "John Doe" },
  { $set: { age: 31 } },
  {
    upsert: true,           // Insert if not found
    writeConcern: { w: 1 }  // Write concern
  }
)
```

---

## DELETE Operations

### 1. Delete One Document

**Syntax:**
```javascript
db.collectionName.deleteOne(filter)
```

**Example:**
```javascript
// Delete single document
db.users.deleteOne({ name: "John Doe" })

// Delete by _id
db.users.deleteOne({ _id: ObjectId("507f1f77bcf86cd799439011") })

// Output:
// {
//   acknowledged: true,
//   deletedCount: 1
// }
```

### 2. Delete Multiple Documents

**Syntax:**
```javascript
db.collectionName.deleteMany(filter)
```

**Example:**
```javascript
// Delete all inactive users
db.users.deleteMany({ isActive: false })

// Delete users older than 50
db.users.deleteMany({ age: { $gt: 50 } })

// Delete all documents (be careful!)
db.users.deleteMany({})
```

### 3. Find and Delete

**Syntax:**
```javascript
db.collectionName.findOneAndDelete(filter, options)
```

**Example:**
```javascript
// Find and delete, return deleted document
db.users.findOneAndDelete({ name: "John Doe" })

// With options
db.users.findOneAndDelete(
  { age: { $gt: 50 } },
  { sort: { age: -1 } }  // Delete oldest first
)
```

---

## Advanced Operations

### 1. Bulk Operations

```javascript
// Bulk write operations
db.users.bulkWrite([
  { insertOne: { document: { name: "User1", age: 20 } } },
  { updateOne: { filter: { name: "User2" }, update: { $set: { age: 25 } } } },
  { deleteOne: { filter: { name: "User3" } } },
  { replaceOne: { filter: { name: "User4" }, replacement: { name: "User4", age: 30 } } }
])
```

### 2. Transactions (MongoDB 4.0+)

```javascript
// Start a session
const session = db.getMongo().startSession()

// Start transaction
session.startTransaction()

try {
  // Operations within transaction
  session.getDatabase("myDatabase").users.insertOne({ name: "User1" })
  session.getDatabase("myDatabase").users.updateOne(
    { name: "User2" },
    { $set: { age: 25 } }
  )
  
  // Commit transaction
  session.commitTransaction()
} catch (error) {
  // Abort transaction on error
  session.abortTransaction()
} finally {
  session.endSession()
}
```

### 3. Text Search

```javascript
// Create text index
db.users.createIndex({ name: "text", email: "text" })

// Text search
db.users.find({ $text: { $search: "John" } })

// Text search with score
db.users.find(
  { $text: { $search: "John" } },
  { score: { $meta: "textScore" } }
).sort({ score: { $meta: "textScore" } })
```

---

## Indexes

### 1. Create Index

```javascript
// Single field index
db.users.createIndex({ email: 1 })  // 1 = ascending, -1 = descending

// Compound index
db.users.createIndex({ name: 1, age: -1 })

// Unique index
db.users.createIndex({ email: 1 }, { unique: true })

// Sparse index (only indexes documents with the field)
db.users.createIndex({ middleName: 1 }, { sparse: true })

// TTL index (auto-delete after expiration)
db.sessions.createIndex({ createdAt: 1 }, { expireAfterSeconds: 3600 })

// Text index
db.users.createIndex({ name: "text", bio: "text" })
```

### 2. List Indexes

```javascript
// Show all indexes
db.users.getIndexes()

// Show index size
db.users.totalIndexSize()
```

### 3. Drop Index

```javascript
// Drop specific index
db.users.dropIndex({ email: 1 })

// Drop all indexes (except _id)
db.users.dropIndexes()
```

### 4. Explain Query

```javascript
// Analyze query execution
db.users.find({ age: { $gt: 30 } }).explain()

// Execution stats
db.users.find({ age: { $gt: 30 } }).explain("executionStats")
```

---

## Aggregation Pipeline

### Basic Aggregation

```javascript
// Simple aggregation
db.users.aggregate([
  { $match: { isActive: true } },
  { $group: { _id: "$city", count: { $sum: 1 } } },
  { $sort: { count: -1 } }
])
```

### Common Aggregation Stages

```javascript
// $match - Filter documents
db.users.aggregate([
  { $match: { age: { $gt: 25 } } }
])

// $group - Group documents
db.users.aggregate([
  { $group: {
    _id: "$city",
    totalUsers: { $sum: 1 },
    avgAge: { $avg: "$age" },
    maxAge: { $max: "$age" },
    minAge: { $min: "$age" }
  }}
])

// $project - Reshape documents
db.users.aggregate([
  { $project: { name: 1, email: 1, age: 1 } }
])

// $sort - Sort documents
db.users.aggregate([
  { $sort: { age: -1 } }
])

// $limit - Limit results
db.users.aggregate([
  { $limit: 10 }
])

// $skip - Skip documents
db.users.aggregate([
  { $skip: 10 }
])

// $unwind - Deconstruct array
db.users.aggregate([
  { $unwind: "$hobbies" }
])

// $lookup - Join collections
db.orders.aggregate([
  { $lookup: {
    from: "users",
    localField: "userId",
    foreignField: "_id",
    as: "user"
  }}
])
```

### Complex Aggregation Example

```javascript
// Get statistics by city
db.users.aggregate([
  // Stage 1: Filter active users
  { $match: { isActive: true } },
  
  // Stage 2: Group by city
  { $group: {
    _id: "$city",
    totalUsers: { $sum: 1 },
    avgAge: { $avg: "$age" },
    users: { $push: { name: "$name", age: "$age" } }
  }},
  
  // Stage 3: Sort by total users
  { $sort: { totalUsers: -1 } },
  
  // Stage 4: Limit to top 5
  { $limit: 5 },
  
  // Stage 5: Reshape output
  { $project: {
    city: "$_id",
    totalUsers: 1,
    avgAge: { $round: ["$avgAge", 2] },
    _id: 0
  }}
])
```

---

## Best Practices for mongosh

1. **Always use pretty() for readability**
   ```javascript
   db.users.find().pretty()
   ```

2. **Use projection to limit returned data**
   ```javascript
   db.users.find({}, { name: 1, email: 1 })
   ```

3. **Create indexes for frequently queried fields**
   ```javascript
   db.users.createIndex({ email: 1 })
   ```

4. **Use explain() to analyze query performance**
   ```javascript
   db.users.find({ age: { $gt: 30 } }).explain("executionStats")
   ```

5. **Be careful with updateMany and deleteMany**
   - Always test with find() first
   - Use transactions for multiple related operations

6. **Use bulk operations for multiple writes**
   ```javascript
   db.users.bulkWrite([...])
   ```

---

## Practice Exercises

1. Create a collection called "products" and insert 10 products with fields: name, price, category, stock, createdAt

2. Find all products in a specific category

3. Update the price of all products in a category by 10%

4. Find products with stock less than 10

5. Delete all products with price less than $5

6. Create an index on the "category" field

7. Use aggregation to find average price by category

---

**Happy Learning! 🚀**

