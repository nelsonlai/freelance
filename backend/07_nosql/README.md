# Module 7: NoSQL Databases for Backend

NoSQL databases use storage models other than traditional relational tables. Common types: **document** (e.g. MongoDB), **key-value** (e.g. Redis), **wide-column** (e.g. Cassandra), **graph** (e.g. Neo4j). This module focuses on **document stores** (MongoDB) and **key-value** (Redis) as they are widely used in backends.

---

## 1. Why NoSQL?

- **Flexible schema**: Documents can have different fields; good for evolving or heterogeneous data.
- **Scale-out**: Sharding and replication are built into many NoSQL systems.
- **Use-case fit**: Document DBs for nested objects; key-value for cache/session; graph for relationships.
- **Performance**: Tuned for specific access patterns (e.g. key lookup, document by ID).

---

## 2. Document Stores (MongoDB)

Data is stored as **documents** (e.g. JSON/BSON). No fixed table schema; each document can have different fields.

### Core Concepts

- **Database** → **Collection** → **Document**.
- **Document**: JSON-like object with nested objects and arrays.
- **_id**: Unique identifier (usually auto-generated).

### Basic Operations (MongoDB shell or driver)

```javascript
// Insert
db.users.insertOne({ name: "Alice", email: "alice@example.com", roles: ["admin"] });

// Find one
db.users.findOne({ _id: ObjectId("...") });

// Find many with filter
db.users.find({ status: "active" }).sort({ createdAt: -1 }).limit(10);

// Update
db.users.updateOne({ _id: id }, { $set: { name: "Bob" } });

// Delete
db.users.deleteOne({ _id: id });
```

### Using MongoDB from Backends

**Node.js (MongoDB driver or Mongoose)**

```javascript
// Native driver
const { MongoClient } = require('mongodb');
const client = new MongoClient(process.env.MONGODB_URI);
const db = client.db('myapp');
const users = db.collection('users');
const user = await users.findOne({ email: 'alice@example.com' });
await users.insertOne({ name: 'Jane', email: 'jane@example.com' });
```

**Mongoose** (ODM: schemas, validation, middleware):

```javascript
const mongoose = require('mongoose');
const userSchema = new mongoose.Schema({ name: String, email: { type: String, required: true } });
const User = mongoose.model('User', userSchema);
await User.create({ name: 'Jane', email: 'jane@example.com' });
const user = await User.findOne({ email: 'jane@example.com' });
```

**Python (PyMongo or Motor for async)**

```python
from pymongo import MongoClient

client = MongoClient(os.environ["MONGODB_URI"])
db = client.myapp
users = db.users
user = users.find_one({"email": "alice@example.com"})
users.insert_one({"name": "Jane", "email": "jane@example.com"})
```

### When to Use MongoDB

- Nested or variable-shaped data (e.g. profiles, configs, logs).
- Rapid iteration on schema.
- Horizontal scaling and replication.
- Not a substitute for complex relational queries (joins, strict ACID across many entities); use SQL for that.

---

## 3. Key-Value Stores (Redis)

Store values by **key**; ideal for cache, session, rate limiting, queues.

### Core Concepts

- **Key**: String (or other types in Redis).
- **Value**: String, hash, list, set, sorted set.
- **TTL**: Keys can expire after a number of seconds.

### Basic Operations (Redis CLI or client)

```bash
SET user:1001 '{"name":"Alice"}'
GET user:1001
EXPIRE user:1001 3600

HSET user:1001 name Alice email alice@example.com
HGET user:1001 name
```

### Using Redis from Backends

**Node.js (ioredis or node-redis)**

```javascript
const Redis = require('ioredis');
const redis = new Redis(process.env.REDIS_URL);

await redis.set('user:1001', JSON.stringify({ name: 'Alice' }), 'EX', 3600);
const data = await redis.get('user:1001');
```

**Python (redis-py)**

```python
import redis
import json

r = redis.Redis.from_url(os.environ["REDIS_URL"])
r.setex("user:1001", 3600, json.dumps({"name": "Alice"}))
data = r.get("user:1001")
```

### When to Use Redis

- Caching (e.g. API responses, DB query results).
- Session storage.
- Rate limiting (e.g. INCR + EXPIRE per key).
- Simple queues or pub/sub.

---

## 4. SQL vs NoSQL (Quick Comparison)

| Aspect        | SQL (e.g. PostgreSQL, MySQL) | NoSQL Document (e.g. MongoDB) |
|---------------|------------------------------|---------------------------------|
| Schema        | Fixed tables, columns        | Flexible documents              |
| Relationships | Joins, foreign keys          | Embedding or references         |
| Transactions  | Full ACID, multi-table       | Limited or single-document      |
| Query style   | Declarative (SQL)            | API/query language per product  |
| Scaling       | Vertical + replication       | Horizontal sharding common     |
| Use cases     | Structured, relational data  | Nested, variable, or high volume |

---

## 5. Best Practices

### Document DBs (MongoDB)

- Design documents for how you **read** (avoid deep joins; embed when it makes sense).
- Use **indexes** on frequently queried fields.
- Use **projection** to return only needed fields.
- Validate input and consider schema validation (e.g. Mongoose schemas, MongoDB JSON Schema).

### Key-Value (Redis)

- Use **TTL** for cache and session keys to avoid unbounded growth.
- Prefer **hashes** or **structured keys** (e.g. `user:1001:profile`) for clarity.
- Don’t store large values; use Redis for small, fast data.

### General

- **Security**: Use authentication, TLS, and network isolation; never expose DB ports publicly.
- **Backups**: Configure backups and test restore for any persistent store.

---

## 6. Learning Path

1. **MongoDB**: Install locally or use Atlas; run CRUD in shell or Compass; then use a driver/Mongoose in your backend (Node or Python).
2. **Redis**: Install locally or use a managed service; use for a simple cache or session in your API.
3. **When to choose**: Prefer SQL for strongly relational, transactional data; use document or key-value when the use case clearly benefits (flexible schema, cache, session).

---

## Next

- [06_sql](../06_sql/) — SQL and relational databases  
- [01_restful_api](../01_restful_api/) — REST APIs  
- [02_python_fastapi](../02_python_fastapi/) / [04_nodejs](../04_nodejs/) — Backend frameworks  
