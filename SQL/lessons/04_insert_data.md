# Lesson 4: Inserting Data

## Learning Objectives
- Learn how to insert data into tables
- Understand different INSERT statement variations
- Practice inserting single and multiple records
- Learn about data validation during insertion

## Basic INSERT Statement

### Insert Single Record

```sql
-- Basic INSERT syntax
INSERT INTO table_name (column1, column2, column3)
VALUES (value1, value2, value3);

-- Insert into students table
INSERT INTO students (first_name, last_name, email, enrollment_date)
VALUES ('John', 'Doe', 'john.doe@email.com', '2024-01-15');

-- Insert with all columns (if table has few columns)
INSERT INTO departments (dept_name, budget, established_date)
VALUES ('Computer Science', 500000.00, '1990-09-01');
```

### Insert Multiple Records

```sql
-- Insert multiple records in one statement
INSERT INTO students (first_name, last_name, email, enrollment_date)
VALUES 
    ('Jane', 'Smith', 'jane.smith@email.com', '2024-01-15'),
    ('Bob', 'Johnson', 'bob.johnson@email.com', '2024-01-16'),
    ('Alice', 'Brown', 'alice.brown@email.com', '2024-01-17'),
    ('Charlie', 'Wilson', 'charlie.wilson@email.com', '2024-01-18');
```

### Insert with Default Values

```sql
-- Insert using DEFAULT keyword
INSERT INTO students (first_name, last_name, email, enrollment_date, status)
VALUES ('David', 'Lee', 'david.lee@email.com', DEFAULT, DEFAULT);

-- Insert with NULL values
INSERT INTO students (first_name, last_name, email, phone, enrollment_date)
VALUES ('Emma', 'Davis', 'emma.davis@email.com', NULL, '2024-01-20');
```

## INSERT with Different Data Types

### String Data

```sql
-- Insert text data
INSERT INTO articles (title, content, author, published_date)
VALUES (
    'Introduction to SQL',
    'SQL (Structured Query Language) is a programming language designed for managing and manipulating relational databases...',
    'John Smith',
    '2024-01-15'
);

-- Insert with special characters
INSERT INTO products (name, description, price)
VALUES (
    'Café Mocha',
    'Delicious coffee with chocolate and steamed milk. Price: $4.50',
    4.50
);
```

### Numeric Data

```sql
-- Insert decimal values
INSERT INTO products (name, price, cost, stock_quantity)
VALUES 
    ('Laptop', 999.99, 750.00, 50),
    ('Mouse', 25.50, 15.00, 200),
    ('Keyboard', 75.00, 45.00, 150);

-- Insert with different numeric types
INSERT INTO measurements (temperature, pressure, humidity)
VALUES (23.5, 1013.25, 65.8);
```

### Date and Time Data

```sql
-- Insert date values
INSERT INTO events (event_name, event_date, start_time, duration)
VALUES 
    ('Conference', '2024-06-15', '09:00:00', '08:00:00'),
    ('Workshop', '2024-06-16', '14:30:00', '03:30:00');

-- Insert datetime values
INSERT INTO appointments (patient_name, appointment_datetime)
VALUES 
    ('John Doe', '2024-02-15 10:30:00'),
    ('Jane Smith', '2024-02-15 14:00:00');

-- Insert with current date/time functions
INSERT INTO orders (customer_id, order_date, status)
VALUES (1, CURDATE(), 'pending');

INSERT INTO logs (action, created_at)
VALUES ('User login', NOW());
```

### ENUM and SET Data

```sql
-- Insert ENUM values
INSERT INTO orders (customer_id, status, priority)
VALUES 
    (1, 'pending', 'high'),
    (2, 'processing', 'medium'),
    (3, 'shipped', 'low');

-- Insert SET values
INSERT INTO products (name, tags, features)
VALUES 
    ('Smartphone', 'electronics,home', 'warranty,free_shipping'),
    ('T-Shirt', 'clothing', 'discount'),
    ('Book', 'books,home', 'free_shipping,new_arrival');
```

### JSON Data

```sql
-- Insert JSON data
INSERT INTO user_profiles (username, profile_data, preferences)
VALUES (
    'john_doe',
    '{"age": 30, "location": "New York", "interests": ["technology", "music"]}',
    '["email_notifications", "dark_mode", "newsletter"]'
);

-- Insert complex JSON
INSERT INTO products (name, dimensions, specifications)
VALUES (
    'Laptop',
    '{"length": 35.5, "width": 24.5, "height": 2.0}',
    '{"cpu": "Intel i7", "ram": "16GB", "storage": "512GB SSD", "screen": "15.6 inch"}'
);
```

## INSERT with SELECT (Copy Data)

### Copy Data Between Tables

```sql
-- Copy data from one table to another
INSERT INTO students_backup (first_name, last_name, email, enrollment_date)
SELECT first_name, last_name, email, enrollment_date
FROM students
WHERE enrollment_date >= '2024-01-01';

-- Copy with transformations
INSERT INTO student_summary (full_name, email_domain, enrollment_year)
SELECT 
    CONCAT(first_name, ' ', last_name),
    SUBSTRING(email, LOCATE('@', email) + 1),
    YEAR(enrollment_date)
FROM students;
```

### Insert from Another Database

```sql
-- Insert data from another database
INSERT INTO current_db.students (first_name, last_name, email)
SELECT first_name, last_name, email
FROM old_db.students
WHERE status = 'active';
```

## Handling Errors and Validation

### Duplicate Key Handling

```sql
-- INSERT IGNORE: Skip duplicate entries
INSERT IGNORE INTO students (student_id, first_name, last_name, email)
VALUES 
    (1, 'John', 'Doe', 'john.doe@email.com'),
    (2, 'Jane', 'Smith', 'jane.smith@email.com'),
    (1, 'Bob', 'Johnson', 'bob.johnson@email.com'); -- This will be ignored

-- ON DUPLICATE KEY UPDATE: Update on duplicate
INSERT INTO students (student_id, first_name, last_name, email, updated_at)
VALUES (1, 'John', 'Doe', 'john.doe@email.com', NOW())
ON DUPLICATE KEY UPDATE
    first_name = VALUES(first_name),
    last_name = VALUES(last_name),
    updated_at = NOW();
```

### Constraint Violations

```sql
-- This will fail due to NOT NULL constraint
INSERT INTO students (first_name, last_name, email)
VALUES ('John', 'Doe', NULL); -- Error: email cannot be NULL

-- This will fail due to UNIQUE constraint
INSERT INTO students (first_name, last_name, email)
VALUES ('John', 'Doe', 'john.doe@email.com'); -- Error if email already exists

-- This will fail due to CHECK constraint
INSERT INTO students (first_name, last_name, email, gpa)
VALUES ('John', 'Doe', 'john.doe@email.com', 5.0); -- Error: gpa must be <= 4.0
```

## Complete Example: Populating School Database

```sql
-- Use the school management database
USE school_management;

-- Insert departments
INSERT INTO departments (dept_name, budget, established_date)
VALUES 
    ('Computer Science', 500000.00, '1990-09-01'),
    ('Mathematics', 300000.00, '1985-09-01'),
    ('Physics', 400000.00, '1988-09-01'),
    ('Chemistry', 350000.00, '1987-09-01'),
    ('Biology', 450000.00, '1989-09-01');

-- Insert students
INSERT INTO students (first_name, last_name, email, phone, enrollment_date, gpa, status)
VALUES 
    ('John', 'Doe', 'john.doe@university.edu', '555-0101', '2023-09-01', 3.75, 'active'),
    ('Jane', 'Smith', 'jane.smith@university.edu', '555-0102', '2023-09-01', 3.85, 'active'),
    ('Bob', 'Johnson', 'bob.johnson@university.edu', '555-0103', '2023-09-01', 3.45, 'active'),
    ('Alice', 'Brown', 'alice.brown@university.edu', '555-0104', '2023-09-01', 3.95, 'active'),
    ('Charlie', 'Wilson', 'charlie.wilson@university.edu', '555-0105', '2023-09-01', 3.25, 'active'),
    ('Diana', 'Davis', 'diana.davis@university.edu', '555-0106', '2022-09-01', 3.65, 'graduated'),
    ('Eve', 'Miller', 'eve.miller@university.edu', '555-0107', '2023-09-01', 3.55, 'active');

-- Insert courses
INSERT INTO courses (course_code, course_name, credits, dept_id, description)
VALUES 
    ('CS101', 'Introduction to Programming', 3, 1, 'Basic programming concepts using Python'),
    ('CS201', 'Data Structures', 3, 1, 'Fundamental data structures and algorithms'),
    ('CS301', 'Database Systems', 3, 1, 'Relational database design and SQL'),
    ('MATH101', 'Calculus I', 4, 2, 'Differential and integral calculus'),
    ('MATH201', 'Linear Algebra', 3, 2, 'Vector spaces and linear transformations'),
    ('PHYS101', 'General Physics I', 4, 3, 'Mechanics and thermodynamics'),
    ('CHEM101', 'General Chemistry I', 4, 4, 'Atomic structure and chemical bonding'),
    ('BIO101', 'General Biology I', 4, 5, 'Cell biology and genetics');

-- Insert enrollments
INSERT INTO enrollments (student_id, course_id, enrollment_date, grade, status)
VALUES 
    (1, 1, '2023-09-01', 85.5, 'completed'),
    (1, 2, '2024-01-15', NULL, 'enrolled'),
    (2, 1, '2023-09-01', 92.0, 'completed'),
    (2, 3, '2024-01-15', NULL, 'enrolled'),
    (3, 4, '2023-09-01', 78.5, 'completed'),
    (3, 5, '2024-01-15', NULL, 'enrolled'),
    (4, 6, '2023-09-01', 88.0, 'completed'),
    (4, 7, '2024-01-15', NULL, 'enrolled'),
    (5, 8, '2023-09-01', 82.5, 'completed'),
    (5, 1, '2024-01-15', NULL, 'enrolled');
```

## Hands-on Exercise

### Exercise 1: Insert Sample Data

Using the e-commerce database from Lesson 3, insert sample data:

1. **Categories**: Electronics, Clothing, Books, Home & Garden, Sports
2. **Products**: At least 10 products across different categories
3. **Customers**: At least 5 customers with complete information
4. **Orders**: At least 3 orders with multiple items each

### Exercise 2: Handle Edge Cases

Practice inserting data that tests your constraints:

1. Try inserting duplicate emails (should fail)
2. Try inserting negative prices (should fail)
3. Try inserting NULL values in NOT NULL columns (should fail)
4. Use INSERT IGNORE and ON DUPLICATE KEY UPDATE

## Key Takeaways

- Use INSERT to add new records to tables
- INSERT can handle single or multiple records
- Use DEFAULT and NULL appropriately
- Handle duplicate keys with INSERT IGNORE or ON DUPLICATE KEY UPDATE
- Validate data before insertion to avoid constraint violations
- Use INSERT...SELECT to copy data between tables

## Next Steps

In the next lesson, we'll learn how to query and retrieve data from our tables using SELECT statements.

## Practice Questions

1. What's the difference between INSERT and INSERT IGNORE?
2. How do you insert multiple records in a single statement?
3. When would you use ON DUPLICATE KEY UPDATE?
4. How do you insert the current date/time into a table?
5. What happens when you try to insert data that violates a constraint?
