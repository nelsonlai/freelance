# Lesson 3: Data Types and Constraints

## Learning Objectives
- Understand MySQL data types in detail
- Learn about various constraints and their purposes
- Practice creating tables with appropriate data types
- Understand data validation and integrity

## Numeric Data Types

### Integer Types

```sql
-- TINYINT: Very small integers
CREATE TABLE example_tinyint (
    id TINYINT,                    -- -128 to 127 (signed)
    unsigned_id TINYINT UNSIGNED   -- 0 to 255 (unsigned)
);

-- SMALLINT: Small integers
CREATE TABLE example_smallint (
    id SMALLINT,                   -- -32,768 to 32,767
    unsigned_id SMALLINT UNSIGNED  -- 0 to 65,535
);

-- MEDIUMINT: Medium integers
CREATE TABLE example_mediumint (
    id MEDIUMINT,                  -- -8,388,608 to 8,388,607
    unsigned_id MEDIUMINT UNSIGNED -- 0 to 16,777,215
);

-- INT: Standard integers
CREATE TABLE example_int (
    id INT,                        -- -2,147,483,648 to 2,147,483,647
    unsigned_id INT UNSIGNED       -- 0 to 4,294,967,295
);

-- BIGINT: Large integers
CREATE TABLE example_bigint (
    id BIGINT,                     -- Very large range
    unsigned_id BIGINT UNSIGNED    -- 0 to 18,446,744,073,709,551,615
);
```

### Decimal Types

```sql
-- DECIMAL: Fixed-point decimal numbers
CREATE TABLE prices (
    product_id INT,
    price DECIMAL(10, 2),          -- 10 total digits, 2 after decimal
    discount DECIMAL(5, 3)         -- 5 total digits, 3 after decimal
);

-- FLOAT: Single precision floating point
CREATE TABLE measurements (
    id INT,
    temperature FLOAT,              -- Approximate value
    pressure FLOAT(7, 4)           -- 7 digits total, 4 after decimal
);

-- DOUBLE: Double precision floating point
CREATE TABLE scientific_data (
    id INT,
    value DOUBLE,                  -- Higher precision than FLOAT
    precision_value DOUBLE(15, 8)  -- 15 digits total, 8 after decimal
);
```

## String Data Types

### Variable Length Strings

```sql
-- VARCHAR: Variable character string
CREATE TABLE users (
    id INT,
    username VARCHAR(50),          -- Up to 50 characters
    email VARCHAR(255),            -- Up to 255 characters
    bio VARCHAR(1000)              -- Up to 1000 characters
);

-- TEXT: Large text data
CREATE TABLE articles (
    id INT,
    title VARCHAR(200),
    content TEXT,                  -- Up to 65,535 characters
    summary MEDIUMTEXT,            -- Up to 16,777,215 characters
    full_text LONGTEXT             -- Up to 4,294,967,295 characters
);
```

### Fixed Length Strings

```sql
-- CHAR: Fixed character string
CREATE TABLE codes (
    id INT,
    country_code CHAR(2),          -- Always exactly 2 characters
    postal_code CHAR(5),           -- Always exactly 5 characters
    status CHAR(1)                 -- Always exactly 1 character
);
```

### Binary Data Types

```sql
-- BLOB: Binary large object
CREATE TABLE files (
    id INT,
    filename VARCHAR(255),
    file_data BLOB,                -- Up to 65,535 bytes
    large_file MEDIUMBLOB,         -- Up to 16,777,215 bytes
    aws_s3_link VARCHAR(255)       -- /MyAWS_S3/Project_AA/{timestamp}.pdf
    huge_file LONGBLOB             -- Up to 4,294,967,295 bytes
);
```

## Date and Time Data Types

```sql
-- DATE: Date only
CREATE TABLE events (
    id INT,
    event_name VARCHAR(100),
    event_date DATE                -- Format: YYYY-MM-DD
);

-- TIME: Time only
CREATE TABLE schedules (
    id INT,
    activity VARCHAR(100),
    start_time TIME,               -- Format: HH:MM:SS
    duration TIME                  -- Format: HH:MM:SS
);

-- DATETIME: Date and time
CREATE TABLE appointments (
    id INT,
    patient_name VARCHAR(100),
    appointment_datetime DATETIME  -- Format: YYYY-MM-DD HH:MM:SS
);

-- TIMESTAMP: Automatic timestamp
CREATE TABLE logs (
    id INT,
    action VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- YEAR: Year only
CREATE TABLE cars (
    id INT,
    make VARCHAR(50),
    model VARCHAR(50),
    year YEAR                      -- Format: YYYY (1901-2155)
);
```

## Special Data Types

### ENUM

```sql
-- ENUM: Enumeration of predefined values
CREATE TABLE orders (
    id INT,
    customer_name VARCHAR(100),
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled'),
    priority ENUM('low', 'medium', 'high', 'urgent') DEFAULT 'medium'
);
```

### SET

```sql
-- SET: Set of predefined values
CREATE TABLE products (
    id INT,
    name VARCHAR(100),
    tags SET('electronics', 'clothing', 'books', 'home', 'sports'),
    features SET('warranty', 'free_shipping', 'discount', 'new_arrival')
);
```

### JSON

```sql
-- JSON: JSON data type (MySQL 5.7+)
CREATE TABLE user_profiles (
    id INT,
    username VARCHAR(50),
    profile_data JSON,             -- Store JSON objects
    preferences JSON               -- Store JSON arrays
);
```

## Constraints

### Primary Key

```sql
-- Single column primary key
CREATE TABLE customers (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE
);

-- Composite primary key
CREATE TABLE order_items (
    order_id INT,
    product_id INT,
    quantity INT,
    price DECIMAL(10, 2),
    PRIMARY KEY (order_id, product_id)
);
```

### Foreign Key

```sql
-- Basic foreign key
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT,
    order_date DATE,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

-- Foreign key with actions
CREATE TABLE order_items (
    item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT,
    product_id INT,
    quantity INT,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE RESTRICT
);
```

### Unique Constraints

```sql
-- Single column unique
CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE,
    email VARCHAR(255) UNIQUE
);

-- Composite unique constraint
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    semester VARCHAR(20),
    UNIQUE KEY unique_enrollment (student_id, course_id, semester)
);
```

### Check Constraints

```sql
-- Check constraints for data validation
CREATE TABLE employees (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    age INT CHECK (age >= 18 AND age <= 65),
    salary DECIMAL(10, 2) CHECK (salary > 0),
    email VARCHAR(255) CHECK (email LIKE '%@%'),
    status ENUM('active', 'inactive') DEFAULT 'active'
);
```

### Default Values

```sql
-- Default values
CREATE TABLE products (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    stock_quantity INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    status ENUM('active', 'inactive', 'discontinued') DEFAULT 'active'
);
```

## Complete Example: E-commerce System

```sql
-- Create e-commerce database
CREATE DATABASE ecommerce;
USE ecommerce;

-- Categories table
CREATE TABLE categories (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL UNIQUE,
    description TEXT,
    parent_id INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (parent_id) REFERENCES categories(category_id) ON DELETE SET NULL
);

-- Products table
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(200) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2) NOT NULL CHECK (price > 0),
    cost DECIMAL(10, 2) CHECK (cost >= 0),
    sku VARCHAR(50) UNIQUE,
    stock_quantity INT DEFAULT 0 CHECK (stock_quantity >= 0),
    min_stock_level INT DEFAULT 5 CHECK (min_stock_level >= 0),
    category_id INT,
    weight DECIMAL(8, 3) CHECK (weight >= 0),
    dimensions JSON, -- Store length, width, height
    status ENUM('active', 'inactive', 'discontinued') DEFAULT 'active',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (category_id) REFERENCES categories(category_id) ON DELETE SET NULL
);

-- Customers table
CREATE TABLE customers (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    phone VARCHAR(20),
    date_of_birth DATE CHECK (date_of_birth <= CURDATE()),
    gender ENUM('male', 'female', 'other'),
    address JSON, -- Store address components
    status ENUM('active', 'inactive', 'banned') DEFAULT 'active',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Orders table
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT NOT NULL,
    order_number VARCHAR(20) UNIQUE NOT NULL,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled') DEFAULT 'pending',
    total_amount DECIMAL(12, 2) NOT NULL CHECK (total_amount >= 0),
    tax_amount DECIMAL(10, 2) DEFAULT 0 CHECK (tax_amount >= 0),
    shipping_amount DECIMAL(8, 2) DEFAULT 0 CHECK (shipping_amount >= 0),
    notes TEXT,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) ON DELETE RESTRICT
);

-- Order items table
CREATE TABLE order_items (
    item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    unit_price DECIMAL(10, 2) NOT NULL CHECK (unit_price >= 0),
    total_price DECIMAL(12, 2) NOT NULL CHECK (total_price >= 0),
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id) ON DELETE RESTRICT,
    UNIQUE KEY unique_order_product (order_id, product_id)
);
```

## Hands-on Exercise

### Exercise 1: Create a Blog System

Create tables for a blog system with the following requirements:

1. **Users table**: id, username (unique), email (unique), password_hash, first_name, last_name, bio (TEXT), avatar_url, created_at, updated_at
2. **Categories table**: id, name (unique), description, slug (unique), created_at
3. **Posts table**: id, title, slug (unique), content (LONGTEXT), excerpt (TEXT), featured_image_url, status (ENUM: draft, published, archived), author_id (FK), category_id (FK), published_at, created_at, updated_at
4. **Comments table**: id, post_id (FK), user_id (FK), content (TEXT), status (ENUM: pending, approved, rejected), created_at, updated_at
5. **Tags table**: id, name (unique), slug (unique), description, created_at
6. **Post tags table**: post_id (FK), tag_id (FK) - many-to-many relationship

### Exercise 2: Add Constraints

Add appropriate constraints to ensure data integrity:
- Check constraints for email format
- Check constraints for slug format (alphanumeric and hyphens only)
- Check constraints for positive values where appropriate
- Default values for timestamps and status fields

## Key Takeaways

- Choose data types based on the data you'll store and operations you'll perform
- Use constraints to maintain data integrity and consistency
- DECIMAL is preferred over FLOAT for monetary values
- VARCHAR is more flexible than CHAR for most text fields
- Use ENUM for predefined values, JSON for flexible data structures
- Foreign keys maintain referential integrity between tables

## Next Steps

In the next lesson, we'll learn how to insert data into our tables and work with the data we've created.

## Practice Questions

1. When would you use DECIMAL instead of FLOAT for storing prices?
2. What's the difference between VARCHAR(255) and TEXT?
3. How do you create a composite primary key?
4. What's the purpose of the AUTO_INCREMENT attribute?
5. When would you use ON DELETE CASCADE vs ON DELETE RESTRICT?
