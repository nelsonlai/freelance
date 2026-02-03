# Lesson 8: Database Design Principles and Normalization

## Learning Objectives
- Understand the fundamentals of relational database design
- Learn about database normalization (1NF, 2NF, 3NF, BCNF)
- Master entity-relationship modeling concepts
- Practice designing efficient database schemas
- Understand data types and their appropriate usage
- Learn about indexing strategies and performance optimization

## Table of Contents
1. [Introduction to Database Design](#introduction-to-database-design)
2. [Entity-Relationship Modeling](#entity-relationship-modeling)
3. [Database Normalization](#database-normalization)
4. [Data Types and Storage](#data-types-and-storage)
5. [Indexing Strategies](#indexing-strategies)
6. [Design Patterns and Best Practices](#design-patterns-and-best-practices)
7. [Performance Considerations](#performance-considerations)
8. [Real-World Design Examples](#real-world-design-examples)

## Introduction to Database Design

### What is Database Design?

Database design is the process of creating a detailed data model of a database. It involves:
- **Analyzing requirements** and understanding business rules
- **Identifying entities** and their relationships
- **Designing tables** with appropriate columns and data types
- **Establishing relationships** between tables
- **Optimizing for performance** and maintainability

### Key Principles of Good Database Design

#### 1. **Data Integrity**
```sql
-- Example: Ensuring data consistency
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT NOT NULL,
    order_date DATE NOT NULL,
    total_amount DECIMAL(10,2) NOT NULL CHECK (total_amount > 0),
    status ENUM('pending', 'processing', 'shipped', 'delivered') DEFAULT 'pending',
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);
```

#### 2. **Elimination of Redundancy**
```sql
-- BAD: Redundant data storage
CREATE TABLE bad_orders (
    order_id INT,
    customer_name VARCHAR(100),  -- Redundant if stored in customers table
    customer_email VARCHAR(100), -- Redundant if stored in customers table
    product_name VARCHAR(100),   -- Redundant if stored in products table
    product_price DECIMAL(10,2) -- Redundant if stored in products table
);

-- GOOD: Normalized design
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    customer_id INT,
    order_date DATE,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

CREATE TABLE order_items (
    order_id INT,
    product_id INT,
    quantity INT,
    unit_price DECIMAL(10,2),
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);
```

#### 3. **Flexibility and Scalability**
```sql
-- Flexible design that can accommodate future changes
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    -- JSON field for flexible user attributes
    metadata JSON
);
```

## Entity-Relationship Modeling

### Understanding Entities and Relationships

#### **Entities**
Entities are objects or concepts that have independent existence and can be uniquely identified.

**Example Entities:**
- Student
- Course
- Professor
- Department
- Enrollment

#### **Attributes**
Attributes are properties or characteristics of entities.

**Types of Attributes:**
- **Simple vs Composite**: Simple (age) vs Composite (address)
- **Single-valued vs Multi-valued**: Single (SSN) vs Multi-valued (phone numbers)
- **Stored vs Derived**: Stored (birth_date) vs Derived (age)
- **Key vs Non-key**: Key (student_id) vs Non-key (name)

#### **Relationships**
Relationships describe how entities are connected.

**Relationship Types:**

##### 1. **One-to-One (1:1)**
```sql
-- Example: User and UserProfile
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL
);

CREATE TABLE user_profiles (
    profile_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT UNIQUE NOT NULL,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    bio TEXT,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);
```

##### 2. **One-to-Many (1:M)**
```sql
-- Example: Department and Employees
CREATE TABLE departments (
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(100) NOT NULL
);

CREATE TABLE employees (
    emp_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    dept_id INT,
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id)
);
```

##### 3. **Many-to-Many (M:N)**
```sql
-- Example: Students and Courses
CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL
);

CREATE TABLE courses (
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL
);

-- Junction table for many-to-many relationship
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    enrollment_date DATE DEFAULT (CURRENT_DATE),
    grade DECIMAL(5,2),
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (course_id) REFERENCES courses(course_id)
);
```

### ER Diagram Notation

```
Entity: [Entity Name]
    |-- Attribute (Key)
    |-- Attribute
    |-- Attribute (Derived)

Relationship: Entity1 --< Relationship >-- Entity2
```

**Example ER Diagram:**
```
[Student]                    [Course]
    |-- student_id (PK)         |-- course_id (PK)
    |-- first_name              |-- course_name
    |-- last_name               |-- credits
    |-- email                   |-- dept_id (FK)
    |-- gpa                     |
                                |
[Enrollment] (Junction Table)
    |-- student_id (FK)
    |-- course_id (FK)
    |-- enrollment_date
    |-- grade
```

## Database Normalization

### What is Normalization?

Normalization is the process of organizing data in a database to:
- **Eliminate redundancy**
- **Reduce data anomalies**
- **Improve data integrity**
- **Optimize storage space**

### First Normal Form (1NF)

**Rules:**
1. Each table cell must contain only atomic (indivisible) values
2. Each record must be unique
3. No repeating groups or arrays

#### **Example: Violating 1NF**
```sql
-- BAD: Violates 1NF - repeating groups
CREATE TABLE bad_students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100),
    course1 VARCHAR(50),
    course2 VARCHAR(50),
    course3 VARCHAR(50),
    grade1 DECIMAL(5,2),
    grade2 DECIMAL(5,2),
    grade3 DECIMAL(5,2)
);
```

#### **Example: Satisfying 1NF**
```sql
-- GOOD: Satisfies 1NF
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL
);

CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    grade DECIMAL(5,2),
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (course_id) REFERENCES courses(course_id)
);
```

### Second Normal Form (2NF)

**Rules:**
1. Must be in 1NF
2. All non-key attributes must be fully functionally dependent on the primary key
3. No partial dependencies

#### **Example: Violating 2NF**
```sql
-- BAD: Violates 2NF - partial dependency
CREATE TABLE bad_enrollments (
    student_id INT,
    course_id INT,
    student_name VARCHAR(100),  -- Depends only on student_id
    course_name VARCHAR(100),  -- Depends only on course_id
    grade DECIMAL(5,2),        -- Depends on both student_id and course_id
    PRIMARY KEY (student_id, course_id)
);
```

#### **Example: Satisfying 2NF**
```sql
-- GOOD: Satisfies 2NF
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL
);

CREATE TABLE courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL
);

CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    grade DECIMAL(5,2),
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (course_id) REFERENCES courses(course_id)
);
```

### Third Normal Form (3NF)

**Rules:**
1. Must be in 2NF
2. No transitive dependencies
3. All non-key attributes must be non-transitively dependent on the primary key

#### **Example: Violating 3NF**
```sql
-- BAD: Violates 3NF - transitive dependency
CREATE TABLE bad_employees (
    emp_id INT PRIMARY KEY,
    emp_name VARCHAR(100),
    dept_id INT,
    dept_name VARCHAR(100),    -- Transitive dependency: dept_name depends on dept_id
    dept_location VARCHAR(100), -- Transitive dependency: dept_location depends on dept_id
    salary DECIMAL(10,2)
);
```

#### **Example: Satisfying 3NF**
```sql
-- GOOD: Satisfies 3NF
CREATE TABLE departments (
    dept_id INT PRIMARY KEY,
    dept_name VARCHAR(100) NOT NULL,
    dept_location VARCHAR(100)
);

CREATE TABLE employees (
    emp_id INT PRIMARY KEY,
    emp_name VARCHAR(100) NOT NULL,
    dept_id INT,
    salary DECIMAL(10,2),
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id)
);
```

### Boyce-Codd Normal Form (BCNF)

**Rules:**
1. Must be in 3NF
2. Every determinant must be a candidate key

#### **Example: Violating BCNF**
```sql
-- BAD: Violates BCNF
CREATE TABLE bad_course_instructors (
    course_id INT,
    instructor_id INT,
    instructor_name VARCHAR(100), -- instructor_name depends on instructor_id
    PRIMARY KEY (course_id, instructor_id)
);
-- Problem: instructor_name depends on instructor_id, but instructor_id is not a candidate key
```

#### **Example: Satisfying BCNF**
```sql
-- GOOD: Satisfies BCNF
CREATE TABLE instructors (
    instructor_id INT PRIMARY KEY,
    instructor_name VARCHAR(100) NOT NULL
);

CREATE TABLE course_instructors (
    course_id INT,
    instructor_id INT,
    PRIMARY KEY (course_id, instructor_id),
    FOREIGN KEY (instructor_id) REFERENCES instructors(instructor_id)
);
```

### Higher Normal Forms

#### **Fourth Normal Form (4NF)**
- Eliminates multi-valued dependencies
- Each multi-valued dependency must be a functional dependency

#### **Fifth Normal Form (5NF)**
- Eliminates join dependencies
- Every join dependency must be implied by candidate keys

## Data Types and Storage

### Choosing Appropriate Data Types

#### **Numeric Types**

```sql
-- Integer Types
TINYINT      -- -128 to 127 (1 byte)
SMALLINT     -- -32,768 to 32,767 (2 bytes)
MEDIUMINT    -- -8,388,608 to 8,388,607 (3 bytes)
INT          -- -2,147,483,648 to 2,147,483,647 (4 bytes)
BIGINT       -- Very large integers (8 bytes)

-- When to use each:
CREATE TABLE user_preferences (
    user_id INT,                    -- Use INT for primary keys
    age TINYINT UNSIGNED,           -- Use TINYINT for small numbers (0-255)
    population_count BIGINT,        -- Use BIGINT for very large numbers
    rating TINYINT UNSIGNED         -- Use TINYINT for ratings (1-5)
);

-- Decimal Types
DECIMAL(10,2)  -- Fixed-point: 99999999.99 (exact precision)
FLOAT          -- Single precision floating point (approximate)
DOUBLE         -- Double precision floating point (approximate)

-- When to use each:
CREATE TABLE financial_data (
    account_id INT,
    balance DECIMAL(15,2),          -- Use DECIMAL for money (exact precision)
    interest_rate DECIMAL(5,4),     -- Use DECIMAL for percentages
    temperature FLOAT,               -- Use FLOAT for measurements (approximate OK)
    scientific_value DOUBLE         -- Use DOUBLE for scientific calculations
);
```

#### **String Types**

```sql
-- Variable Length Strings
VARCHAR(255)  -- Variable length, up to 65,535 characters
TEXT          -- Up to 65,535 characters
MEDIUMTEXT    -- Up to 16,777,215 characters
LONGTEXT      -- Up to 4,294,967,295 characters

-- Fixed Length Strings
CHAR(10)      -- Always exactly 10 characters

-- When to use each:
CREATE TABLE user_data (
    user_id INT,
    username VARCHAR(50),           -- Use VARCHAR for variable-length strings
    email VARCHAR(255),              -- Use VARCHAR for emails
    bio TEXT,                        -- Use TEXT for long descriptions
    country_code CHAR(2),            -- Use CHAR for fixed-length codes
    postal_code CHAR(5)              -- Use CHAR for fixed-length codes
);
```

#### **Date and Time Types**

```sql
-- Date and Time Types
DATE          -- YYYY-MM-DD (3 bytes)
TIME          -- HH:MM:SS (3 bytes)
DATETIME      -- YYYY-MM-DD HH:MM:SS (8 bytes)
TIMESTAMP     -- YYYY-MM-DD HH:MM:SS (4 bytes, timezone aware)
YEAR          -- YYYY (1 byte)

-- When to use each:
CREATE TABLE events (
    event_id INT,
    event_name VARCHAR(100),
    event_date DATE,                 -- Use DATE for dates only
    start_time TIME,                 -- Use TIME for time only
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Use TIMESTAMP for automatic timestamps
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    birth_year YEAR                  -- Use YEAR for year-only data
);
```

#### **Special Types**

```sql
-- ENUM and SET
ENUM('small', 'medium', 'large')     -- Choose one value from list
SET('red', 'green', 'blue')          -- Choose multiple values from list

-- JSON (MySQL 5.7+)
JSON                                  -- Store JSON data

-- When to use each:
CREATE TABLE products (
    product_id INT,
    name VARCHAR(100),
    size ENUM('XS', 'S', 'M', 'L', 'XL'),  -- Use ENUM for predefined choices
    colors SET('red', 'green', 'blue', 'yellow'), -- Use SET for multiple choices
    attributes JSON,                          -- Use JSON for flexible data
    status ENUM('active', 'inactive', 'discontinued') DEFAULT 'active'
);
```

### Storage Optimization

#### **Choosing Efficient Data Types**

```sql
-- BAD: Inefficient storage
CREATE TABLE inefficient_table (
    id INT,                          -- Could be SMALLINT if < 32,767
    status VARCHAR(10),              -- Could be ENUM
    flag VARCHAR(3),                 -- Could be TINYINT
    description TEXT,                -- Could be VARCHAR if < 255 chars
    created_date DATETIME            -- Could be DATE if time not needed
);

-- GOOD: Efficient storage
CREATE TABLE efficient_table (
    id SMALLINT,                     -- Use smallest type that fits
    status ENUM('active', 'inactive'), -- Use ENUM for predefined values
    flag TINYINT,                    -- Use TINYINT for boolean-like values
    description VARCHAR(200),       -- Use VARCHAR for shorter text
    created_date DATE                -- Use DATE if time component not needed
);
```

## Indexing Strategies

### Types of Indexes

#### **Primary Key Index**
```sql
-- Automatically created for PRIMARY KEY
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,  -- Primary key index
    username VARCHAR(50) UNIQUE,             -- Unique index
    email VARCHAR(100)
);
```

#### **Unique Index**
```sql
-- Ensures uniqueness and provides fast lookups
CREATE UNIQUE INDEX idx_email ON users(email);
CREATE UNIQUE INDEX idx_username ON users(username);
```

#### **Regular Index**
```sql
-- Improves query performance for frequently searched columns
CREATE INDEX idx_last_name ON users(last_name);
CREATE INDEX idx_created_at ON users(created_at);
```

#### **Composite Index**
```sql
-- Index on multiple columns
CREATE INDEX idx_name_location ON users(last_name, city);
CREATE INDEX idx_status_date ON orders(status, order_date);
```

#### **Partial Index**
```sql
-- Index only on rows that meet certain conditions
CREATE INDEX idx_active_users ON users(username) WHERE status = 'active';
CREATE INDEX idx_recent_orders ON orders(order_id) WHERE order_date >= '2023-01-01';
```

### Index Design Best Practices

#### **When to Create Indexes**

```sql
-- 1. Primary and Foreign Keys (automatic)
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,  -- Indexed automatically
    customer_id INT,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) -- Indexed automatically
);

-- 2. Frequently searched columns
CREATE INDEX idx_customer_email ON customers(email);
CREATE INDEX idx_product_category ON products(category_id);

-- 3. Columns used in WHERE clauses
CREATE INDEX idx_order_status ON orders(status);
CREATE INDEX idx_user_active ON users(is_active);

-- 4. Columns used in ORDER BY
CREATE INDEX idx_order_date ON orders(order_date);
CREATE INDEX idx_product_price ON products(price);

-- 5. Columns used in JOIN conditions
CREATE INDEX idx_order_customer ON orders(customer_id);
CREATE INDEX idx_order_item_product ON order_items(product_id);
```

#### **When NOT to Create Indexes**

```sql
-- 1. Small tables (< 1000 rows)
-- 2. Columns with low cardinality (few unique values)
-- 3. Columns that are frequently updated
-- 4. Columns used only in SELECT (not WHERE/ORDER BY/JOIN)

-- Example of unnecessary index:
CREATE TABLE small_table (
    id INT PRIMARY KEY,
    status ENUM('active', 'inactive')  -- Don't index if only 2 values
);
-- CREATE INDEX idx_status ON small_table(status); -- Unnecessary
```

## Design Patterns and Best Practices

### Common Design Patterns

#### **1. Audit Trail Pattern**
```sql
-- Track changes to important data
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) NOT NULL,
    email VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    created_by INT,
    updated_by INT
);

-- Audit log table
CREATE TABLE user_audit_log (
    audit_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT,
    action ENUM('INSERT', 'UPDATE', 'DELETE'),
    old_values JSON,
    new_values JSON,
    changed_by INT,
    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

#### **2. Soft Delete Pattern**
```sql
-- Instead of physically deleting records, mark them as deleted
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    is_deleted BOOLEAN DEFAULT FALSE,
    deleted_at TIMESTAMP NULL,
    deleted_by INT NULL
);

-- Query active products
SELECT * FROM products WHERE is_deleted = FALSE;

-- Query all products including deleted
SELECT * FROM products;
```

#### **3. Hierarchical Data Pattern**
```sql
-- Self-referencing table for hierarchical data
CREATE TABLE categories (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    parent_id INT NULL,
    level INT NOT NULL DEFAULT 0,
    path VARCHAR(500), -- Materialized path
    FOREIGN KEY (parent_id) REFERENCES categories(category_id)
);

-- Query all children of a category
SELECT * FROM categories WHERE path LIKE '1/2/%';
```

#### **4. Polymorphic Association Pattern**
```sql
-- One table can reference multiple other tables
CREATE TABLE comments (
    comment_id INT PRIMARY KEY AUTO_INCREMENT,
    content TEXT NOT NULL,
    commentable_type ENUM('post', 'photo', 'video'),
    commentable_id INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Index for polymorphic queries
CREATE INDEX idx_commentable ON comments(commentable_type, commentable_id);
```

### Naming Conventions

#### **Table Names**
```sql
-- Use plural nouns, lowercase with underscores
CREATE TABLE users (...);
CREATE TABLE order_items (...);
CREATE TABLE user_profiles (...);
```

#### **Column Names**
```sql
-- Use descriptive names, lowercase with underscores
CREATE TABLE users (
    user_id INT PRIMARY KEY,           -- Primary key: table_name + _id
    first_name VARCHAR(50),           -- Descriptive names
    last_name VARCHAR(50),
    email_address VARCHAR(100),        -- Clear and specific
    created_at TIMESTAMP,              -- Timestamps: action + _at
    updated_at TIMESTAMP,
    is_active BOOLEAN                  -- Boolean: is_ + description
);
```

#### **Index Names**
```sql
-- Use descriptive prefixes
CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_orders_customer_date ON orders(customer_id, order_date);
CREATE UNIQUE INDEX uk_users_username ON users(username);
```

## Performance Considerations

### Query Optimization

#### **Efficient Query Design**
```sql
-- BAD: Inefficient query
SELECT * FROM users u
JOIN orders o ON u.user_id = o.user_id
JOIN order_items oi ON o.order_id = oi.order_id
JOIN products p ON oi.product_id = p.product_id
WHERE u.created_at > '2023-01-01';

-- GOOD: Efficient query
SELECT u.user_id, u.username, COUNT(o.order_id) as order_count
FROM users u
JOIN orders o ON u.user_id = o.user_id
WHERE u.created_at > '2023-01-01'
GROUP BY u.user_id, u.username;
```

#### **Proper Use of Indexes**
```sql
-- Create indexes for common query patterns
CREATE INDEX idx_users_created_active ON users(created_at, is_active);
CREATE INDEX idx_orders_customer_status ON orders(customer_id, status);

-- Query that uses the index efficiently
SELECT * FROM users 
WHERE created_at > '2023-01-01' AND is_active = TRUE;
```

### Denormalization Strategies

Sometimes, denormalization is necessary for performance:

#### **Read-Heavy Applications**
```sql
-- Denormalize frequently accessed data
CREATE TABLE order_summary (
    order_id INT PRIMARY KEY,
    customer_name VARCHAR(100),      -- Denormalized from customers table
    total_amount DECIMAL(10,2),      -- Denormalized calculated field
    item_count INT,                  -- Denormalized count
    order_date DATE
);
```

#### **Reporting Tables**
```sql
-- Pre-calculated reporting data
CREATE TABLE daily_sales_summary (
    date DATE PRIMARY KEY,
    total_orders INT,
    total_revenue DECIMAL(12,2),
    average_order_value DECIMAL(10,2),
    top_product_id INT
);
```

## Real-World Design Examples

### Example 1: E-commerce Database

```sql
-- E-commerce database design
CREATE DATABASE ecommerce;
USE ecommerce;

-- Users and Authentication
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    phone VARCHAR(20),
    date_of_birth DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    is_active BOOLEAN DEFAULT TRUE
);

-- User Addresses
CREATE TABLE user_addresses (
    address_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    address_type ENUM('billing', 'shipping') DEFAULT 'shipping',
    street_address VARCHAR(255) NOT NULL,
    city VARCHAR(100) NOT NULL,
    state VARCHAR(50) NOT NULL,
    postal_code VARCHAR(20) NOT NULL,
    country VARCHAR(50) NOT NULL DEFAULT 'USA',
    is_default BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

-- Categories (Hierarchical)
CREATE TABLE categories (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    parent_id INT NULL,
    level INT NOT NULL DEFAULT 0,
    path VARCHAR(500),
    is_active BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (parent_id) REFERENCES categories(category_id)
);

-- Products
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    sku VARCHAR(50) UNIQUE NOT NULL,
    name VARCHAR(200) NOT NULL,
    description TEXT,
    short_description VARCHAR(500),
    category_id INT,
    brand VARCHAR(100),
    price DECIMAL(10,2) NOT NULL,
    cost DECIMAL(10,2),
    weight DECIMAL(8,3),
    dimensions JSON, -- {length, width, height}
    images JSON,     -- Array of image URLs
    specifications JSON,
    inventory_count INT DEFAULT 0,
    min_stock_level INT DEFAULT 5,
    is_active BOOLEAN DEFAULT TRUE,
    is_featured BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (category_id) REFERENCES categories(category_id)
);

-- Product Variants (size, color, etc.)
CREATE TABLE product_variants (
    variant_id INT PRIMARY KEY AUTO_INCREMENT,
    product_id INT NOT NULL,
    sku VARCHAR(50) UNIQUE NOT NULL,
    variant_name VARCHAR(100) NOT NULL,
    attributes JSON, -- {size: 'L', color: 'red'}
    price_adjustment DECIMAL(10,2) DEFAULT 0.00,
    inventory_count INT DEFAULT 0,
    is_active BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE CASCADE
);

-- Shopping Cart
CREATE TABLE cart_items (
    cart_item_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    product_id INT,
    variant_id INT NULL,
    quantity INT NOT NULL DEFAULT 1,
    added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE CASCADE,
    FOREIGN KEY (variant_id) REFERENCES product_variants(variant_id) ON DELETE CASCADE
);

-- Orders
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    order_number VARCHAR(20) UNIQUE NOT NULL,
    user_id INT NOT NULL,
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled', 'refunded') DEFAULT 'pending',
    subtotal DECIMAL(10,2) NOT NULL,
    tax_amount DECIMAL(10,2) DEFAULT 0.00,
    shipping_amount DECIMAL(10,2) DEFAULT 0.00,
    discount_amount DECIMAL(10,2) DEFAULT 0.00,
    total_amount DECIMAL(10,2) NOT NULL,
    payment_status ENUM('pending', 'paid', 'failed', 'refunded') DEFAULT 'pending',
    payment_method VARCHAR(50),
    shipping_address JSON,
    billing_address JSON,
    notes TEXT,
    shipped_at TIMESTAMP NULL,
    delivered_at TIMESTAMP NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Order Items
CREATE TABLE order_items (
    order_item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    variant_id INT NULL,
    product_name VARCHAR(200) NOT NULL, -- Denormalized for historical accuracy
    variant_name VARCHAR(100),
    sku VARCHAR(50) NOT NULL,
    quantity INT NOT NULL,
    unit_price DECIMAL(10,2) NOT NULL,
    total_price DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id),
    FOREIGN KEY (variant_id) REFERENCES product_variants(variant_id)
);

-- Reviews
CREATE TABLE product_reviews (
    review_id INT PRIMARY KEY AUTO_INCREMENT,
    product_id INT NOT NULL,
    user_id INT NOT NULL,
    order_id INT NULL, -- Optional: link to order
    rating TINYINT NOT NULL CHECK (rating >= 1 AND rating <= 5),
    title VARCHAR(200),
    content TEXT,
    is_verified_purchase BOOLEAN DEFAULT FALSE,
    is_approved BOOLEAN DEFAULT FALSE,
    helpful_count INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE SET NULL,
    UNIQUE KEY unique_user_product_review (user_id, product_id)
);

-- Create Indexes for Performance
CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_users_username ON users(username);
CREATE INDEX idx_products_category ON products(category_id);
CREATE INDEX idx_products_active ON products(is_active);
CREATE INDEX idx_products_featured ON products(is_featured);
CREATE INDEX idx_orders_user ON orders(user_id);
CREATE INDEX idx_orders_status ON orders(status);
CREATE INDEX idx_orders_created ON orders(created_at);
CREATE INDEX idx_order_items_order ON order_items(order_id);
CREATE INDEX idx_order_items_product ON order_items(product_id);
CREATE INDEX idx_reviews_product ON product_reviews(product_id);
CREATE INDEX idx_reviews_rating ON product_reviews(rating);
CREATE INDEX idx_cart_user ON cart_items(user_id);
```

### Example 2: Content Management System

```sql
-- CMS Database Design
CREATE DATABASE cms;
USE cms;

-- Users and Roles
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    avatar_url VARCHAR(255),
    bio TEXT,
    is_active BOOLEAN DEFAULT TRUE,
    last_login TIMESTAMP NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Roles and Permissions
CREATE TABLE roles (
    role_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) UNIQUE NOT NULL,
    description TEXT,
    permissions JSON -- Array of permission strings
);

CREATE TABLE user_roles (
    user_id INT,
    role_id INT,
    assigned_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    assigned_by INT,
    PRIMARY KEY (user_id, role_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (role_id) REFERENCES roles(role_id) ON DELETE CASCADE,
    FOREIGN KEY (assigned_by) REFERENCES users(user_id)
);

-- Content Types
CREATE TABLE content_types (
    content_type_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) UNIQUE NOT NULL,
    label VARCHAR(100) NOT NULL,
    description TEXT,
    fields JSON, -- Field definitions
    is_active BOOLEAN DEFAULT TRUE
);

-- Categories
CREATE TABLE categories (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    slug VARCHAR(100) UNIQUE NOT NULL,
    description TEXT,
    parent_id INT NULL,
    level INT NOT NULL DEFAULT 0,
    path VARCHAR(500),
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (parent_id) REFERENCES categories(category_id)
);

-- Tags
CREATE TABLE tags (
    tag_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) UNIQUE NOT NULL,
    slug VARCHAR(50) UNIQUE NOT NULL,
    description TEXT,
    usage_count INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Content
CREATE TABLE content (
    content_id INT PRIMARY KEY AUTO_INCREMENT,
    content_type_id INT NOT NULL,
    title VARCHAR(255) NOT NULL,
    slug VARCHAR(255) UNIQUE NOT NULL,
    excerpt TEXT,
    body LONGTEXT,
    author_id INT NOT NULL,
    status ENUM('draft', 'published', 'archived') DEFAULT 'draft',
    featured_image_url VARCHAR(255),
    meta_title VARCHAR(255),
    meta_description TEXT,
    published_at TIMESTAMP NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (content_type_id) REFERENCES content_types(content_type_id),
    FOREIGN KEY (author_id) REFERENCES users(user_id)
);

-- Content Categories (Many-to-Many)
CREATE TABLE content_categories (
    content_id INT,
    category_id INT,
    PRIMARY KEY (content_id, category_id),
    FOREIGN KEY (content_id) REFERENCES content(content_id) ON DELETE CASCADE,
    FOREIGN KEY (category_id) REFERENCES categories(category_id) ON DELETE CASCADE
);

-- Content Tags (Many-to-Many)
CREATE TABLE content_tags (
    content_id INT,
    tag_id INT,
    PRIMARY KEY (content_id, tag_id),
    FOREIGN KEY (content_id) REFERENCES content(content_id) ON DELETE CASCADE,
    FOREIGN KEY (tag_id) REFERENCES tags(tag_id) ON DELETE CASCADE
);

-- Comments
CREATE TABLE comments (
    comment_id INT PRIMARY KEY AUTO_INCREMENT,
    content_id INT NOT NULL,
    parent_id INT NULL, -- For nested comments
    author_name VARCHAR(100) NOT NULL,
    author_email VARCHAR(100) NOT NULL,
    author_url VARCHAR(255),
    content TEXT NOT NULL,
    status ENUM('pending', 'approved', 'spam', 'trash') DEFAULT 'pending',
    ip_address VARCHAR(45),
    user_agent TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (content_id) REFERENCES content(content_id) ON DELETE CASCADE,
    FOREIGN KEY (parent_id) REFERENCES comments(comment_id) ON DELETE CASCADE
);

-- Media Library
CREATE TABLE media (
    media_id INT PRIMARY KEY AUTO_INCREMENT,
    filename VARCHAR(255) NOT NULL,
    original_filename VARCHAR(255) NOT NULL,
    file_path VARCHAR(500) NOT NULL,
    file_size INT NOT NULL,
    mime_type VARCHAR(100) NOT NULL,
    alt_text VARCHAR(255),
    caption TEXT,
    uploaded_by INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (uploaded_by) REFERENCES users(user_id)
);

-- Create Indexes
CREATE INDEX idx_content_type ON content(content_type_id);
CREATE INDEX idx_content_author ON content(author_id);
CREATE INDEX idx_content_status ON content(status);
CREATE INDEX idx_content_published ON content(published_at);
CREATE INDEX idx_content_slug ON content(slug);
CREATE INDEX idx_comments_content ON comments(content_id);
CREATE INDEX idx_comments_status ON comments(status);
CREATE INDEX idx_media_uploader ON media(uploaded_by);
CREATE INDEX idx_categories_parent ON categories(parent_id);
CREATE INDEX idx_categories_active ON categories(is_active);
```

## Hands-on Exercise

### Exercise 1: Design a Library Management System

Design a complete database schema for a library management system with the following requirements:

1. **Books**: title, author, ISBN, publication year, genre, copies available
2. **Members**: name, email, phone, membership type, join date
3. **Borrowing**: member borrows book, due date, return date, fine amount
4. **Staff**: librarians with different access levels
5. **Reservations**: members can reserve books

### Exercise 2: Normalization Practice

Given the following denormalized table, normalize it to 3NF:

```sql
CREATE TABLE bad_employee_data (
    emp_id INT,
    emp_name VARCHAR(100),
    dept_id INT,
    dept_name VARCHAR(100),
    dept_location VARCHAR(100),
    manager_id INT,
    manager_name VARCHAR(100),
    project_id INT,
    project_name VARCHAR(100),
    project_start_date DATE,
    project_end_date DATE,
    hours_worked INT,
    hourly_rate DECIMAL(10,2)
);
```

### Exercise 3: Performance Optimization

Design indexes for the following query patterns:

1. Find all orders by customer in date range
2. Find products by category and price range
3. Find users who haven't logged in recently
4. Generate monthly sales reports

## Key Takeaways

- **Design for the future**: Consider scalability and flexibility
- **Normalize appropriately**: Balance normalization with performance needs
- **Choose data types wisely**: Match data types to actual data requirements
- **Index strategically**: Create indexes for common query patterns
- **Document everything**: Clear naming and documentation are essential
- **Test thoroughly**: Validate design with realistic data volumes
- **Plan for maintenance**: Include audit trails and soft deletes where appropriate

## Next Steps

In the next lesson, we'll learn about advanced SQL features including views, stored procedures, and triggers.

## Practice Questions

1. What are the main benefits of database normalization?
2. When might you choose to denormalize data?
3. How do you determine the appropriate data type for a column?
4. What factors should you consider when creating indexes?
5. How do you handle hierarchical data in a relational database?
