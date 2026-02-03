# MongoDB Training — Detailed Instructor & Student Materials

This file expands the course overview into full, ready-to-teach training materials: daily lesson plans, lecture notes, demos, labs with step-by-step exercises and solutions, quizzes, project briefs, and assessment rubrics. Use these materials directly in workshops or as a self-study curriculum.

---

## How to use these materials
- Instructor: follow the day schedules, run the demos live, grade labs with rubrics below.
- Student: follow the labs in order, run the provided commands, and submit deliverables listed at the end of each week.

Each day includes:
- Objectives: what students should know/do by the end of the session.
- Lecture Notes: key points and talking points for the instructor.
- Live Demo(s): commands and scripts to run in class.
- Lab Exercises: hands-on tasks with step-by-step instructions.
- Homework: out-of-class assignments and reading.

---

## Course-level Objectives (mapped from COURSE_OVERVIEW.md)
By course end students will be able to:
- Explain NoSQL concepts and MongoDB architecture and when to use them.
- Install and run MongoDB locally (and in Docker) and connect from `mongosh` and Python (`pymongo`).
- Execute CRUD operations in `mongosh` and via PyMongo; write queries, updates and deletes safely.
- Use the aggregation pipeline to build analytics queries and joins (`$lookup`).
- Design schema patterns (embedding vs referencing) and apply indexes effectively.
- Integrate MongoDB into Python applications, including transactions and bulk operations.

---

## Course Schedule (detailed)
Course length: 3 weeks (approx. 20–24 contact hours + 8–12 hours homework/week).

Week 1 — Foundations (mongosh + data modelling)
- Day 1: Intro + Setup
- Day 2: Documents, Collections, Schema Patterns
- Day 3: READ & Querying (selectors, projection, sorting)
- Day 4: Aggregation basics and explain()
- Day 5: UPDATE & DELETE operators and patterns

Week 2 — Python Integration (PyMongo)
- Day 1: Connections, clients, and lifecycle
- Day 2: Create & Read via PyMongo
- Day 3: Update, Delete, and bulk operations
- Day 4: Transactions, indexing, and performance
- Day 5: Advanced pipelines and migration patterns

Week 3 — Projects and assessment
- Day 1–3: Project development and coaching
- Day 4–5: Finalization, demos, and grading

---

## Week 1 — Foundations (Detailed)

Day 1 — Intro & Setup (90 minutes)

Objectives
- Understand NoSQL concepts and MongoDB use-cases.
- Install MongoDB (macOS) and confirm `mongosh` connectivity.

Lecture Notes (20 min)
- NoSQL vs SQL: flexible schemas, denormalized models, horizontal scaling tradeoffs.
- MongoDB basics: database -> collection -> document (BSON). Indexes, replica sets, and sharding at a high level.
- When to embed vs reference: read/write patterns, document growth, and atomicity boundaries.

Live Demo (20 min)
- Install with Homebrew (macOS) and verify service:

```bash
brew tap mongodb/brew
brew install mongodb-community@6.0
brew services start mongodb-community@6.0
mongosh --eval 'db.runCommand({ connectionStatus: 1 })'
```

- Start `mongosh` and show basic commands:

```js
use training
db.users.insertOne({name: 'Alice', roles: ['user'], created_at: new Date()})
db.users.find().pretty()
```

Lab (40 min)
- Follow `SETUP.md`; create a `training` DB and `users` collection, insert 20 sample users with varied cities, roles, and created_at timestamps.
- Exercises:
  1. Insert an array-based field (`roles`) and query for users containing a role.
  2. Add nested address objects to several users and query by nested field.

Step-by-step sample (answers expected):

```js
// insert many sample users
const users = Array.from({length:20}).map((_,i)=>({
  name: `user${i+1}`,
  roles: i%3===0?['admin','user']:['user'],
  address: {city: i%5===0? 'Taipei':'Kaohsiung', zip: 100+i},
  created_at: new Date(Date.now() - i*24*60*60*1000)
}));
db.users.insertMany(users)

// query users with role 'admin'
db.users.find({roles: 'admin'}).count()

// find by nested field
db.users.find({'address.city':'Taipei'}).limit(5)
```

Homework
- Read `README.md` and `mongosh-examples.md` CREATE section; complete a short multiple-choice quiz on NoSQL basics.

---

Day 2 — Schema Patterns & CRUD refresher (90 minutes)

Objectives
- Compare embedding vs referencing and create schemas for sample apps.
- Practice insertOne/insertMany, and basic read queries.

Lecture Notes (20 min)
- Embedding advantages: fewer joins, faster reads for common patterns; disadvantages: document growth and duplication.
- Referencing advantages: consistency and small document sizes; disadvantages: additional queries/joins.
- Typical patterns: one-to-many (embed small arrays), many-to-many (references), time-series (bucket pattern).

Live Demo (25 min)
- Create `posts` and `comments` patterns:

Embedded example:
```js
db.posts.insertOne({
  title: 'Post 1',
  author: 'Alice',
  comments: [
    {author: 'bob', text: 'Nice post', created: new Date()},
    {author: 'carol', text: 'Thanks', created: new Date()}
  ]
})
```

Referenced example:
```js
db.posts.insertOne({title: 'Post 2', author: 'Dan'})
db.comments.insertOne({post_id: ObjectId("<postId>"), author:'ellen', text:'Great'})
```

Lab (45 min)
- Task A: Design two schemas for a blog and write 3 sample documents for each.
- Task B: Trade-off analysis: for each schema, list when it would be preferred.

Deliverable: upload a short write-up (200–300 words) with sample documents and a decision matrix.

---

Day 3 — Read: Querying, Projection, Sorting, Pagination (90 minutes)

Objectives
- Use `find`, selectors, projections, sorting, and pagination patterns.
- Understand cursor behaviour and limits.

Lecture Notes (25 min)
- Query operators: `$eq`, `$gt`, `$gte`, `$in`, `$nin`, `$exists`, `$regex`.
- Array operators: `$all`, `$elemMatch`.
- Projection: include/exclude fields; never mix 0 and 1 (except `_id`).
- Pagination options: `limit/skip` vs range queries. When to prefer each.

Live Demo (30 min)

```js
// selectors and projection
db.users.find({created_at: {$gte: new Date(Date.now()-7*24*3600*1000)}}, {name:1, roles:1}).sort({created_at:-1}).limit(10)

// pagination using range-based (preferred for large collections)
const pageSize=20; const lastCreatedAt=ISODate('2025-01-01T00:00:00Z');
db.users.find({created_at: {$lt: lastCreatedAt}}).sort({created_at:-1}).limit(pageSize)
```

Lab (35 min)
- Exercises:
  1. Find users who have `roles` containing `'user'` and live in `Taipei`.
  2. Return only `name` and `address.city` fields.
  3. Implement simple `skip` pagination and then rewrite to range-based pagination.

Solutions (short):

```js
db.users.find({roles: 'user', 'address.city':'Taipei'}, {name:1, 'address.city':1})

// skip pagination
db.users.find().sort({created_at:-1}).skip(40).limit(20)

// range-based pagination
const last = db.users.find().sort({created_at:-1}).limit(1).toArray()[0];
db.users.find({created_at: {$lt: last.created_at}}).sort({created_at:-1}).limit(20)
```

Homework
- Read `mongosh-examples.md` READ section; practice queries and record explain() output for at least two queries.

---

Day 4 — Aggregation Pipeline (120 minutes)

Objectives
- Build pipelines using `$match`, `$group`, `$project`, `$unwind`, `$sort`, and `$limit`.
- Use `$lookup` for joins and `$facet` for multi-output pipelines.

Lecture Notes (30 min)
- Aggregation executes stages in order; minimize documents early with `$match`.
- Use `$project` to reshape documents and `$group` to compute aggregates.
- `$lookup` performs left-outer joins; be mindful of working set and memory.

Live Demo (45 min)
- Example: top 3 cities by user count

```js
db.users.aggregate([
  {$group: {_id: '$address.city', count: {$sum:1}}},
  {$sort: {count:-1}},
  {$limit:3}
])
```

- Example: monthly sales breakdown (orders collection assumed)

```js
db.orders.aggregate([
  {$match: {created_at: {$gte: ISODate('2025-01-01')}}},
  {$project: {month: {$dateToString: {format: '%Y-%m', date: '$created_at'}}, amount:1}},
  {$group: {_id: '$month', total: {$sum: '$amount'}}},
  {$sort: {_id:1}}
])
```

Lab (45 min)
- Exercise: Given a `sales` collection with fields `{product_id, quantity, price, created_at, region}`, write a pipeline that computes total revenue per product and returns top 5 products.

Solution outline:

```js
db.sales.aggregate([
  {$project: {product_id:1, revenue: {$multiply:['$quantity','$price']}}},
  {$group: {_id: '$product_id', totalRevenue: {$sum: '$revenue'}}},
  {$sort: {totalRevenue:-1}},
  {$limit:5}
])
```

---

Day 5 — Update, Delete, Index Basics (90 minutes)

Objectives
- Use update operators and delete safely; understand index creation & explain() differences.

Lecture Notes (30 min)
- Update operators: `$set`, `$inc`, `$push`, `$addToSet`, `$pull`, upserts.
- `findOneAndUpdate` vs `updateOne` semantics.
- Deletes: use `findOneAndDelete` when you need the removed document.
- Index basics: single-field, compound, TTL, text indexes. Use `explain('executionStats')` to inspect index usage.

Live Demo (30 min)

```js
// update examples
db.users.updateOne({name:'user1'}, {$set: {active:true}})
db.users.updateMany({roles:'user'}, {$inc: {login_count: 1}})

// create index
db.users.createIndex({created_at: -1})

// explain
db.users.find({created_at: {$lt: new Date()}}).sort({created_at:-1}).explain('executionStats')
```

Lab (30 min)
- Tasks:
  1. Add an index to `address.city`, run a query before/after and capture `executionStats`.
  2. Write an update that adds a tag to a `products` array only if not present (`$addToSet`).

---

## Week 1 Deliverables
- Completed lab notebooks (mongosh transcripts or screenshots).
- 1-page schema decision writeup.
- Week 1 quiz (10 questions).

---

## Week 2 — Python Integration (Detailed)

Prerequisites
- Python 3.10+ (3.11 recommended), `virtualenv` or `venv`.
- `python-examples/requirements.txt` should include `pymongo` and `faker` for sample data.

Quick setup commands for macOS (use zsh):

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r python-examples/requirements.txt
```

Day 1 — Connections & Client Patterns (90 minutes)

Objectives
- Understand `MongoClient` life cycle and connection string options (replica set, auth, TLS).

Lecture Notes (20 min)
- `MongoClient` is thread-safe and should be reused; server selection and timeouts; `serverSelectionTimeoutMS`.
- Best practices for environment secrets and connection URIs (avoid hardcoded credentials).

Demo (30 min)
- Walk through `python-examples/01_basic_connection.py`: connect, list databases, create/drop a collection.

Sample snippet (connect):

```py
from pymongo import MongoClient
client = MongoClient('mongodb://localhost:27017', serverSelectionTimeoutMS=5000)
db = client.training
print(db.list_collection_names())
```

Lab (40 min)
- Task A: Write a script to seed 500 fake user records using `faker` and `insert_many`.
- Task B: Create a small helper that wraps `MongoClient` and retries on transient errors.

Day 2 — Reads & Pagination (90 minutes)

Objectives
- Implement read helpers with projections, sorting, and pagination.

Demo (30 min)
- Walk `python-examples/03_read_operations.py`: query cursors, batch_size, `limit`, and efficient pagination using range query.

Lab (60 min)
- Build `api_helpers.py` with functions:
  - `get_users(page_size, last_id=None)` — returns next page using `_id` range.
  - `search_products(query, limit)` — uses text index if available.

Testing
- Provide a simple pytest file that asserts expected number of seeded users and that pagination returns stable results.

Day 3 — Updates, Deletes, Bulk (90 minutes)

Objectives
- Use `bulk_write` for batch operations; safely archive documents before delete.

Lecture & Demo (45 min)
- Show `bulk_write` example and `UpdateOne`, `DeleteOne` operations; show `find_one_and_update` with `return_document=ReturnDocument.AFTER`.

Lab (45 min)
- Implement `archive_then_delete(filter_query, archive_collection)` that atomically moves documents using a transaction (if replica set) or a two-step process with metadata marking when transactions not available.

Day 4 — Transactions, Indexes, Performance (90 minutes)

Objectives
- Use multi-document transactions (where supported) and understand their environment requirements.

Demo (45 min)
- Show `with client.start_session() as s: with s.start_transaction(): ...` example in `python-examples/06_advanced_operations.py`.

Lab (45 min)
- Exercise: Perform a simulated funds transfer between two accounts using a transaction, then measure performance with and without an index on `account_id`.

Day 5 — Aggregation, Profiling, Migration Patterns (90 minutes)

Objectives
- Run aggregation pipelines from Python; use database profiler and `explain()` when possible.

Demo (40 min)
- Wrap a pipeline in Python: `list(db.collection.aggregate(pipeline))` and examine `explain()` where supported.

Lab (50 min)
- Exercise: Implement server-side map-reduce alternative using aggregation to transform an existing collection into a denormalized reporting collection. Save results into `reports.daily_sales`.

Week 2 Deliverables
- Python scripts repository with seeding script, pagination helpers, transaction example, and unit tests.

---

## Week 3 — Projects, Tests & Deployment

Project Options (pick one)
- User Management System: register/login, profiles, roles, soft delete, audit logs.
- Product Catalog + Search: products, categories, text search, facets, top-selling reports.
- Blog System: posts, comments (embedded or referenced), tags, author metrics.

Project Requirements Template
- Data model design document (1–2 pages), including sample documents and index plan.
- Seed data script (`seed.py`) using `faker`.
- Minimal REST API (Flask/FastAPI recommended) with CRUD endpoints and simple auth.
- Unit tests covering DB helpers (pytest).

Assessment Rubric (100 points)
- Functionality: 40 (endpoints working, correct data flows)
- Schema & Indexing decisions: 20 (rationale and evidence using explain)
- Tests: 15 (unit tests for critical functions)
- Documentation & README: 15 (setup, run, design notes)
- Demo & Presentation: 10 (clarity and demonstration of features)

Project Hints
- Use indexes on fields used in filters/sorts; measure with `explain()`.
- For text search, create a text index on searchable fields and limit results with `score` projection.

---

## Exercises and Solutions (Selected)

Exercise 1 — mongosh: Top cities by user count
- Task: Using `db.users`, find top 3 cities by user count.
- Solution:

```js
db.users.aggregate([
  {$group: {_id: '$address.city', count: {$sum:1}}},
  {$sort: {count:-1}},
  {$limit: 3}
])
```

Exercise 2 — mongosh: Add tag if not present
- Task: Add `'featured'` to `products.tags` only when not present for product `_id = ...`.
- Solution:

```js
db.products.updateOne({_id: ObjectId("<id>")}, {$addToSet: {tags: 'featured'}})
```

Exercise 3 — Python: Pagination helper
- Task: Implement `get_users_page(db, page_size, last_id=None)` using `_id`-based paging.
- Solution (outline):

```py
from bson import ObjectId

def get_users_page(db, page_size=20, last_id=None):
    q = {}
    if last_id:
        q['_id'] = {'$lt': ObjectId(last_id)}
    cursor = db.users.find(q).sort('_id', -1).limit(page_size)
    results = list(cursor)
    next_last = results[-1]['_id'] if results else None
    return results, str(next_last) if next_last else None
```

Exercise 4 — Python: Transactional money transfer
- Task: Transfer money between two account documents atomically.
- Solution (outline):

```py
from pymongo import MongoClient

def transfer(client, from_id, to_id, amount):
    db = client.bank
    with client.start_session() as session:
        with session.start_transaction():
            res1 = db.accounts.update_one({'_id': from_id, 'balance': {'$gte': amount}}, {'$inc': {'balance': -amount}}, session=session)
            if res1.modified_count != 1:
                raise Exception('Insufficient funds')
            db.accounts.update_one({'_id': to_id}, {'$inc': {'balance': amount}}, session=session)

```

Note: Transactions require replica set or MongoDB Atlas.

---

## Quizzes & Answers (samples)

Week 1 quiz (10 items) — sample questions
1. What is BSON? (Answer: binary JSON-like format used by MongoDB)
2. When would you embed data vs reference? (Answer: embed for small, frequently-read together data; reference for many-to-many or unbounded growth)
3. Name three aggregation stages. (Answer: `$match`, `$group`, `$project`)
4. What operator adds an item to an array only if not exists? (`$addToSet`)
5. How to limit query field projection to only `name`? (Answer: `{name:1}`)

Instructor answer key and a small grading rubric should be used.

---

## Quick Reference (extract)

Common `mongosh` commands
- Connect: `mongosh "mongodb://localhost:27017"`
- Create DB: `use mydb` (switch)
- Insert: `db.coll.insertOne({...})`, `db.coll.insertMany([...])`
- Find: `db.coll.find({filter}, {projection}).sort({field:1}).limit(10)`
- Update: `db.coll.updateOne({q}, {$set:{...}})`
- Delete: `db.coll.deleteOne({q})`

Common PyMongo usage
- Client: `client = MongoClient('mongodb://localhost:27017')`
- DB: `db = client.get_database('training')`
- Insert: `db.users.insert_one(doc)`, `db.users.insert_many(docs)`
- Find: `db.users.find({'roles':'admin'}, {'password':0})`

Index tips
- Create index: `db.coll.createIndex({field:1})`
- Compound: `db.coll.createIndex({a:1, b:-1})` — order matters.
- Text index: `db.coll.createIndex({title: 'text', body: 'text'})`

Explain
- `db.coll.find({...}).explain('executionStats')` — look for `indexName`, `totalKeysExamined`, `totalDocsExamined`.

---

## Instructor Notes & Troubleshooting
- For transaction demos locally, start a single-node replica set:

```bash
mkdir -p /data/db
mongod --replSet rs0 --port 27017 --dbpath /data/db --bind_ip localhost
# in mongosh:
rs.initiate()
```

- If `pymongo.errors.ServerSelectionTimeoutError` occurs, verify MongoDB is running and connection URI is correct.
- For Docker-based workshops, provide a `docker-compose.yml` that starts a replica set and Mongo Express (optional).

---

## Additional Resources
- MongoDB docs: https://docs.mongodb.com/
- PyMongo docs: https://pymongo.readthedocs.io/
- MongoDB University courses for follow-up.

---

## Next steps (suggested)
1. Add `QUICK_REFERENCE.md` file with the condensed cheat sheet (I can create this next).
2. Expand `python-examples/README.md` with detailed per-file explanations and how to run tests.
3. Add automated unit tests and CI workflow for running Python examples (GitHub Actions).

If you'd like, I can now:
- create `QUICK_REFERENCE.md` and update `python-examples/README.md`, or
- expand individual day labs into separate `.md` lab files per day.

---

Prepared by: Course authoring helper
