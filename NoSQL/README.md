# NoSQL Database Training: MongoDB from Scratch

## Table of Contents
1. [Introduction to NoSQL Databases](#introduction-to-nosql-databases)
2. [What is MongoDB?](#what-is-mongodb)
3. [MongoDB Installation](#mongodb-installation)
4. [MongoDB Core Concepts](#mongodb-core-concepts)
5. [MongoDB Shell (mongosh) Guide](#mongodb-shell-mongosh-guide)
6. [Python Integration with MongoDB](#python-integration-with-mongodb)
7. [Best Practices](#best-practices)
8. [Additional Resources](#additional-resources)

---

## Introduction to NoSQL Databases

### What is NoSQL?

**NoSQL** stands for "Not Only SQL" or "Non-SQL". It refers to a broad class of database management systems that differ from traditional relational database management systems (RDBMS) in several key ways:

#### Key Differences from SQL Databases:

1. **Data Model**
   - **SQL (Relational)**: Data stored in tables with rows and columns. Relationships defined through foreign keys.
   - **NoSQL**: Various data models (document, key-value, graph, column-family)

2. **Schema**
   - **SQL**: Fixed schema - must define structure before inserting data
   - **NoSQL**: Schema-less or flexible schema - can add fields on the fly

3. **Scalability**
   - **SQL**: Primarily vertical scaling (more powerful hardware)
   - **NoSQL**: Designed for horizontal scaling (distribute across multiple servers)

4. **ACID Properties**
   - **SQL**: Strong ACID (Atomicity, Consistency, Isolation, Durability) guarantees
   - **NoSQL**: Often prioritizes performance and scalability over strict ACID compliance

#### Types of NoSQL Databases:

1. **Document Databases** (MongoDB, CouchDB)
   - Store data as documents (JSON-like structures)
   - Best for: Content management, user profiles, catalogs

2. **Key-Value Stores** (Redis, DynamoDB)
   - Simple key-value pairs
   - Best for: Caching, session storage, real-time analytics

3. **Column-Family Stores** (Cassandra, HBase)
   - Store data in columns rather than rows
   - Best for: Time-series data, big data analytics

4. **Graph Databases** (Neo4j, ArangoDB)
   - Store data as nodes and edges
   - Best for: Social networks, recommendation engines, fraud detection

---

## What is MongoDB?

**MongoDB** is a popular open-source, document-oriented NoSQL database. It stores data in flexible, JSON-like documents called BSON (Binary JSON).

### Why MongoDB?

1. **Flexible Schema**: No need to define schema upfront
2. **Rich Query Language**: Powerful querying capabilities
3. **Horizontal Scalability**: Built-in sharding for distributing data
4. **High Performance**: Fast read/write operations
5. **Developer Friendly**: Natural fit for modern application development
6. **Rich Ecosystem**: Extensive tooling and community support

### MongoDB Architecture:

```
MongoDB Server
    ├── Databases
    │   ├── Collections
    │   │   ├── Documents
    │   │   │   ├── Fields (Key-Value pairs)
    │   │   │   └── Embedded Documents
    │   │   └── Indexes
    │   └── Views
    └── Replica Sets (for high availability)
```

**Analogy to SQL:**
- **Database** ≈ Database
- **Collection** ≈ Table
- **Document** ≈ Row
- **Field** ≈ Column

---

## MongoDB Installation

### macOS Installation:

```bash
# Using Homebrew (recommended)
brew tap mongodb/brew
brew install mongodb-community

# Start MongoDB service
brew services start mongodb-community

# Or run manually
mongod --config /usr/local/etc/mongod.conf
```

### Linux Installation:

```bash
# Import MongoDB public GPG key
wget -qO - https://www.mongodb.org/static/pgp/server-7.0.asc | sudo apt-key add -

# Add MongoDB repository
echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu jammy/mongodb-org/7.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-7.0.list

# Install MongoDB
sudo apt-get update
sudo apt-get install -y mongodb-org

# Start MongoDB
sudo systemctl start mongod
sudo systemctl enable mongod
```

### Windows Installation:

1. Download MongoDB Community Server from [mongodb.com](https://www.mongodb.com/try/download/community)
2. Run the installer
3. MongoDB will be installed as a Windows service

### Verify Installation:

```bash
# Check MongoDB version
mongod --version

# Connect to MongoDB shell
mongosh
```

---

## MongoDB Core Concepts

### 1. Database

A database is a container for collections. MongoDB can have multiple databases.

```javascript
// List all databases
show dbs

// Switch to a database (creates if doesn't exist)
use myDatabase

// Show current database
db
```

### 2. Collection

A collection is a group of documents. It's similar to a table in SQL but schema-less.

```javascript
// Collections are created automatically when you insert the first document
// But you can also create them explicitly:
db.createCollection("users")

// List all collections
show collections
```

### 3. Document

A document is a set of key-value pairs. Documents in a collection can have different structures.

**Example Document:**
```json
{
  "_id": ObjectId("507f1f77bcf86cd799439011"),
  "name": "John Doe",
  "age": 30,
  "email": "john@example.com",
  "address": {
    "street": "123 Main St",
    "city": "New York",
    "zip": "10001"
  },
  "hobbies": ["reading", "swimming", "coding"],
  "created_at": ISODate("2024-01-15T10:30:00Z")
}
```

**Key Points:**
- `_id` field is automatically added if not provided (unique identifier)
- Documents can contain nested objects and arrays
- Field names are case-sensitive
- Order matters for arrays, not for objects

### 4. BSON Data Types

MongoDB uses BSON (Binary JSON) which supports more data types than JSON:

- **String**: UTF-8 strings
- **Integer**: 32-bit or 64-bit integers
- **Double**: Floating point numbers
- **Boolean**: true/false
- **Date**: Date and time
- **ObjectId**: Unique identifier (12-byte)
- **Null**: Null value
- **Array**: Ordered list of values
- **Object/Embedded Document**: Nested documents
- **Binary Data**: Binary data
- **Regular Expression**: Regex patterns

---

## MongoDB Shell (mongosh) Guide

The MongoDB Shell (mongosh) is an interactive JavaScript interface to MongoDB. It allows you to interact with MongoDB directly from the command line.

### Starting mongosh

```bash
# Connect to local MongoDB instance
mongosh

# Connect to remote MongoDB
mongosh "mongodb://username:password@host:port/database"

# Connect with connection string
mongosh "mongodb+srv://cluster.mongodb.net/database"
```

### Basic Operations

See **[mongosh-examples.md](./mongosh-examples.md)** for detailed CRUD operations with comprehensive examples covering:
- CREATE operations (insertOne, insertMany)
- READ operations (find, findOne, queries, projections)
- UPDATE operations (updateOne, updateMany, operators)
- DELETE operations (deleteOne, deleteMany)
- Advanced operations (aggregation, indexes, text search)

---

## Python Integration with MongoDB

Python integrates with MongoDB through the `pymongo` driver, which provides a Pythonic interface to MongoDB.

### Installation

```bash
cd python-examples
pip install -r requirements.txt
```

### Python Examples Structure

The `python-examples/` directory contains comprehensive Python code examples:

1. **01_basic_connection.py** - Connecting to MongoDB, listing databases/collections
2. **02_create_operations.py** - Inserting documents (insert_one, insert_many)
3. **03_read_operations.py** - Querying documents (find, find_one, filters, sorting)
4. **04_update_operations.py** - Updating documents (update_one, update_many, operators)
5. **05_delete_operations.py** - Deleting documents (delete_one, delete_many)
6. **06_advanced_operations.py** - Aggregation, indexes, transactions, bulk operations

See **[python-examples/README.md](./python-examples/README.md)** for detailed documentation and usage examples.

---

## Best Practices

### 1. Indexing
- Create indexes on frequently queried fields
- Use compound indexes for multi-field queries
- Monitor index usage and remove unused indexes

### 2. Schema Design
- Embed related data that's accessed together
- Reference data that's accessed separately
- Consider read/write patterns when designing schema

### 3. Performance
- Use projection to limit returned fields
- Use pagination for large result sets
- Monitor query performance with `explain()`

### 4. Security
- Enable authentication
- Use role-based access control
- Encrypt data in transit and at rest
- Regularly update MongoDB

### 5. Data Modeling
- Denormalize for read performance
- Normalize for write performance
- Consider data growth patterns

---

## Additional Resources

- [MongoDB Official Documentation](https://docs.mongodb.com/)
- [MongoDB University](https://university.mongodb.com/)
- [PyMongo Documentation](https://pymongo.readthedocs.io/)
- [MongoDB Atlas (Cloud Database)](https://www.mongodb.com/cloud/atlas)

---

## Next Steps

1. **Setup your environment** - Follow the [SETUP.md](./SETUP.md) guide to install MongoDB and Python
2. **Read mongosh examples** - Study [mongosh-examples.md](./mongosh-examples.md) for detailed CRUD operations
3. **Run Python examples** - Work through the examples in `python-examples/` directory
4. **Practice exercises** - Complete the exercises provided in each guide
5. **Build a project** - Apply what you've learned by building a small application

## File Structure

```
NonSQL/
├── README.md                 # Main training guide (this file)
├── SETUP.md                  # Installation and setup instructions
├── mongosh-examples.md       # Detailed MongoDB shell CRUD operations
└── python-examples/          # Python MongoDB integration examples
    ├── README.md             # Python examples guide
    ├── requirements.txt      # Python dependencies
    ├── 01_basic_connection.py
    ├── 02_create_operations.py
    ├── 03_read_operations.py
    ├── 04_update_operations.py
    ├── 05_delete_operations.py
    └── 06_advanced_operations.py
```

---

**Happy Learning! 🚀**

