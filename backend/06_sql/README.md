# Module 6: SQL Databases for Backend

Relational databases (SQL) store data in **tables** with **rows** and **columns**, linked by **relationships** and **foreign keys**. They are the default choice for structured, transactional data in backend applications.

---

## 1. Why SQL for Backend?

- **ACID**: Transactions ensure consistency (Atomicity, Consistency, Isolation, Durability).
- **Structured data**: Tables, schemas, and constraints enforce data integrity.
- **Relationships**: Joins model one-to-one, one-to-many, many-to-many.
- **Query power**: SELECT, JOIN, aggregation, subqueries, views, indexes.
- **Mature tooling**: ORMs (SQLAlchemy, Prisma, TypeORM), migrations, backups.

---

## 2. Common SQL Databases

| Database   | Notes                                      |
|-----------|---------------------------------------------|
| **MySQL** | Popular, good for web apps; MariaDB compatible |
| **PostgreSQL** | Rich types, JSON, extensions; strong for complex queries |
| **SQLite** | File-based, no server; ideal for dev/small apps |
| **SQL Server** | Microsoft ecosystem                        |

---

## 3. Core Concepts

### Tables and Schema

- **Table**: Entity (e.g. `users`, `orders`, `products`).
- **Column**: Attribute with a type (INT, VARCHAR, DATE, DECIMAL, etc.).
- **Primary key**: Unique identifier (e.g. `id`).
- **Foreign key**: Reference to another table (e.g. `order.user_id` → `users.id`).

### Basic Operations (CRUD)

- **Create**: `INSERT INTO users (name, email) VALUES ('Alice', 'alice@example.com');`
- **Read**: `SELECT * FROM users WHERE id = 1;`
- **Update**: `UPDATE users SET name = 'Bob' WHERE id = 1;`
- **Delete**: `DELETE FROM users WHERE id = 1;`

### Joins

- **INNER JOIN**: Rows that match in both tables.
- **LEFT JOIN**: All from left table, matching from right (or NULL).
- **RIGHT JOIN**: All from right, matching from left.
- **FULL OUTER JOIN**: All from both (syntax varies by DB).

### Aggregation and Filtering

- **GROUP BY**, **COUNT**, **SUM**, **AVG**, **MIN**, **MAX**.
- **HAVING** for filtering after aggregation.
- **ORDER BY**, **LIMIT**, **OFFSET** for sorting and pagination.

---

## 4. Using SQL from Backends

### Python (SQLAlchemy)

- **Engine**: `create_engine("mysql+pymysql://user:pass@host/db")` or PostgreSQL URL.
- **ORM**: Define models (tables), use sessions for CRUD; relationships via `relationship()`.
- **Raw SQL**: `session.execute(text("SELECT ..."))` when needed.

### Node.js (Prisma)

- **Schema**: Define models in `prisma/schema.prisma`; run `prisma generate` and migrations.
- **Client**: `prisma.user.findMany()`, `prisma.user.create()`, etc.
- **Raw SQL**: `prisma.$queryRaw` for parameterized queries.

### General Practices

- **Parameterized queries**: Never concatenate user input into SQL; use placeholders to avoid injection.
- **Migrations**: Version your schema (e.g. Alembic, Prisma Migrate) and apply changes in a repeatable way.
- **Indexes**: Add indexes on columns used in WHERE, JOIN, ORDER BY to improve performance.

---

## 5. When to Use SQL

- Structured, relational data (users, orders, products, enrollments).
- Need for transactions and strong consistency.
- Complex queries (joins, aggregations, reporting).
- Existing ecosystem (ORMs, admin UIs, backups).

---

## 6. Full SQL Course in This Repo

A full SQL curriculum with lessons, exercises, and Python examples lives in:

**`../SQL/`**

- **README.md** — Course overview and setup.
- **COURSE_SUMMARY.md** — Full curriculum summary.
- **lessons/** — 01–17: setup, tables, CRUD, joins, design, functions, stored procedures, triggers, optimization, SQLAlchemy.
- **exercises/** — Basic queries, joins, design, functions.
- **solutions/** — Solutions to exercises.
- **python_examples/** — SQLAlchemy scripts for each topic.

**Getting started**: See `../SQL/GETTING_STARTED.md` and `../SQL/README.md`.

---

## Next

- [07_nosql](../07_nosql/) — NoSQL (MongoDB, etc.)  
- [01_restful_api](../01_restful_api/) — REST APIs  
- [02_python_fastapi](../02_python_fastapi/) / [04_nodejs](../04_nodejs/) — Backend frameworks  
