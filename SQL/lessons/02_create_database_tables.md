# Lesson 2: Creating Databases and Tables

## Learning Objectives
- Learn how to create and manage databases
- Understand table creation syntax
- Learn about different data types
- Practice creating tables with various constraints

## Creating Databases

### Basic Database Creation

```sql
-- Create a new database
CREATE DATABASE school_management;

-- Create database with character set specification
CREATE DATABASE school_management 
CHARACTER SET utf8mb4 
COLLATE utf8mb4_unicode_ci;

-- Check if database exists before creating
CREATE DATABASE IF NOT EXISTS school_management;

-- Use the database
USE school_management;

-- Show current database
SELECT DATABASE();
```

### Database Management Commands

```sql
-- Show all databases
SHOW DATABASES;

-- Show database creation statement
SHOW CREATE DATABASE school_management;

-- Drop a database (be careful!)
DROP DATABASE IF EXISTS old_database;

-- Rename database (MySQL 8.0+)
-- Note: This is not directly supported, you need to dump and recreate
```

## Creating Tables

### Basic Table Creation

```sql
-- Create a simple table
CREATE TABLE students (
    student_id INT,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    email VARCHAR(100),
    enrollment_date DATE
);
```

### Table with Constraints

```sql
-- Create table with various constraints
CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    enrollment_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    gpa DECIMAL(3,2) CHECK (gpa >= 0.0 AND gpa <= 4.0),
    status ENUM('active', 'inactive', 'graduated') DEFAULT 'active',
    dateUpdate TIMESTAMP
);
```

## Data Types in MySQL

### Numeric Types

```sql
-- Integer types
TINYINT      -- -128 to 127 (signed) or 0 to 255 (unsigned)
SMALLINT     -- -32,768 to 32,767 (signed) or 0 to 65,535 (unsigned)
MEDIUMINT    -- -8,388,608 to 8,388,607 (signed) or 0 to 16,777,215 (unsigned)
INT          -- -2,147,483,648 to 2,147,483,647 (signed) or 0 to 4,294,967,295 (unsigned)
BIGINT       -- Very large integers

-- Decimal types
DECIMAL(5,2) -- Fixed-point: 999.99
FLOAT        -- Single precision floating point
DOUBLE       -- Double precision floating point
```

### String Types

```sql
-- Variable length strings
VARCHAR(255) -- Variable character string (1-65,535 characters)
TEXT         -- Large text (up to 65,535 characters)
MEDIUMTEXT   -- Medium text (up to 16,777,215 characters)
LONGTEXT     -- Long text (up to 4,294,967,295 characters)

-- Fixed length strings
CHAR(10)     -- Fixed character string (always 10 characters)

-- Binary types
BLOB         -- Binary large object
MEDIUMBLOB   -- Medium binary object
LONGBLOB     -- Long binary object
```

### Date and Time Types

```sql
DATE         -- Date only (YYYY-MM-DD)
TIME         -- Time only (HH:MM:SS)
DATETIME     -- Date and time (YYYY-MM-DD HH:MM:SS)
TIMESTAMP    -- Automatic timestamp (YYYY-MM-DD HH:MM:SS)
YEAR         -- Year only (YYYY)
```

### Other Types

```sql
ENUM('value1', 'value2', 'value3')  -- Enumeration
SET('value1', 'value2', 'value3')   -- Set of values
JSON         -- JSON data type (MySQL 5.7+)
BOOLEAN      -- Synonym for TINYINT(1)
```

## Table Constraints

### Primary Key

```sql
-- Single column primary key
CREATE TABLE courses (
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL
);

-- Composite primary key
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    enrollment_date DATE,
    PRIMARY KEY (student_id, course_id)
);
```

### Foreign Key

```sql
-- Create tables with foreign key relationships
CREATE TABLE departments (
    id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(100) NOT NULL,
    budget DECIMAL(12,2)
);

CREATE TABLE courses (
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL,
    dept_id INT,
    FOREIGN KEY (dept_id) REFERENCES departments(id)
);
```

### Other Constraints

```sql
CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    age INT CHECK (age >= 16 AND age <= 100),
    status ENUM('active', 'inactive', 'graduated') DEFAULT 'active',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
```

## Complete Example: School Management System

```sql
-- Create the database
CREATE DATABASE school_management;
USE school_management;

-- Create departments table
CREATE TABLE departments (
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(100) NOT NULL UNIQUE,
    budget DECIMAL(12,2) DEFAULT 0.00,
    established_date DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create students table
CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    enrollment_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    gpa DECIMAL(3,2) CHECK (gpa >= 0.0 AND gpa <= 4.0),
    status ENUM('active', 'inactive', 'graduated') DEFAULT 'active',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Create courses table
CREATE TABLE courses (
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    course_code VARCHAR(10) NOT NULL UNIQUE,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL CHECK (credits > 0),
    dept_id INT,
    description TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id) ON DELETE SET NULL
);

-- Create enrollments table
CREATE TABLE enrollments (
    enrollment_id INT PRIMARY KEY AUTO_INCREMENT,
    student_id INT NOT NULL,
    course_id INT NOT NULL,
    enrollment_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    grade DECIMAL(5,2) CHECK (grade >= 0.0 AND grade <= 100.0),
    status ENUM('enrolled', 'completed', 'dropped') DEFAULT 'enrolled',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    UNIQUE KEY unique_enrollment (student_id, course_id)
);
```

## Table Management Commands

```sql
-- Show table structure
DESCRIBE students;
SHOW COLUMNS FROM students;

-- Show table creation statement
SHOW CREATE TABLE students;

-- Show all tables
SHOW TABLES;

-- Rename table
RENAME TABLE old_name TO new_name;

-- Add column
ALTER TABLE students ADD COLUMN middle_name VARCHAR(50);

-- Modify column
ALTER TABLE students MODIFY COLUMN email VARCHAR(150);

-- Drop column
ALTER TABLE students DROP COLUMN middle_name;

-- Add constraint
ALTER TABLE students ADD CONSTRAINT chk_age CHECK (age >= 16);

-- Drop constraint
ALTER TABLE students DROP CONSTRAINT chk_age;

-- Drop table
DROP TABLE IF EXISTS old_table;
```

## Hands-on Exercise

### Exercise 1: Create Library Management System

Create a database and tables for a library management system with the following entities:

1. **Books**: book_id, title, author, isbn, publication_year, genre
2. **Members**: member_id, first_name, last_name, email, phone, membership_date
3. **Borrowings**: borrowing_id, book_id, member_id, borrow_date, return_date, status

### Exercise 2: Add Constraints

Add appropriate constraints to your tables:
- Primary keys
- Foreign keys
- Unique constraints
- Check constraints
- Default values

## Key Takeaways

- Use `CREATE DATABASE` to create new databases
- Use `CREATE TABLE` with appropriate data types and constraints
- Choose data types based on the data you'll store
- Use constraints to maintain data integrity
- Always test your table creation with sample data

## Next Steps

In the next lesson, we'll learn about data types and constraints in more detail, and then move on to inserting data into our tables.

## Practice Questions

1. What's the difference between `VARCHAR` and `CHAR`?
2. When would you use `DECIMAL` instead of `FLOAT`?
3. What's the purpose of the `AUTO_INCREMENT` attribute?
4. How do foreign keys help maintain data integrity?
5. What happens when you use `ON DELETE CASCADE` in a foreign key constraint?
