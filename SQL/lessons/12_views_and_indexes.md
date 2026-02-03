# Lesson 12: Views and Indexes

## 📚 Learning Objectives

By the end of this lesson, you will be able to:
- Create and manage database views
- Understand different types of indexes
- Implement appropriate indexing strategies
- Use views for security and data abstraction
- Optimize query performance with indexes
- Understand when to use views vs tables

## 🎯 Prerequisites

- Completed Lessons 1-11
- Understanding of SELECT statements and JOINs
- Knowledge of aggregation functions
- Basic understanding of database performance concepts

## 📖 Table of Contents

1. [Introduction to Views](#introduction-to-views)
2. [Creating and Managing Views](#creating-and-managing-views)
3. [Types of Views](#types-of-views)
4. [Introduction to Indexes](#introduction-to-indexes)
5. [Types of Indexes](#types-of-indexes)
6. [Index Strategies](#index-strategies)
7. [Performance Optimization](#performance-optimization)
8. [Best Practices](#best-practices)
9. [Common Pitfalls](#common-pitfalls)

---

## 1. Introduction to Views

A **view** is a virtual table based on the result of a SQL statement. Views contain rows and columns just like real tables, but the data comes from one or more base tables.

### Benefits of Views

- **Security**: Restrict access to sensitive data
- **Simplicity**: Hide complex queries from users
- **Consistency**: Provide standardized data access
- **Maintenance**: Centralize business logic
- **Abstraction**: Present data in user-friendly formats

### When to Use Views

- Complex queries used frequently
- Data security requirements
- Standardizing data access patterns
- Providing calculated fields
- Simplifying user interfaces

---

## 2. Creating and Managing Views

### Basic View Creation

```sql
-- Create a simple view for active students
CREATE VIEW active_students AS
SELECT 
    s.student_id,
    s.first_name,
    s.last_name,
    s.email,
    d.name AS department_name,
    s.gpa
FROM students s
JOIN departments d ON s.department_id = d.department_id
WHERE s.status = 'Active';
```

### Using Views

```sql
-- Query the view like a regular table
SELECT * FROM active_students
WHERE gpa >= 3.5
ORDER BY gpa DESC;

-- Count students by department using the view
SELECT 
    department_name,
    COUNT(*) AS student_count,
    AVG(gpa) AS average_gpa
FROM active_students
GROUP BY department_name
ORDER BY average_gpa DESC;
```

### Modifying Views

```sql
-- Alter an existing view
CREATE OR REPLACE VIEW active_students AS
SELECT 
    s.student_id,
    s.first_name,
    s.last_name,
    s.email,
    d.name AS department_name,
    s.gpa,
    s.enrollment_date
FROM students s
JOIN departments d ON s.department_id = d.department_id
WHERE s.status = 'Active'
  AND s.gpa IS NOT NULL;
```

### Dropping Views

```sql
-- Drop a view
DROP VIEW active_students;

-- Drop with IF EXISTS to avoid errors
DROP VIEW IF EXISTS active_students;
```

---

## 3. Types of Views

### Simple Views
Views based on a single table with no aggregation.

```sql
-- Simple view for course information
CREATE VIEW course_info AS
SELECT 
    course_id,
    course_code,
    name AS course_name,
    credits,
    description
FROM courses
WHERE credits >= 3;
```

### Complex Views
Views with JOINs, aggregations, and calculations.

```sql
-- Complex view for enrollment statistics
CREATE VIEW enrollment_stats AS
SELECT 
    c.course_id,
    c.course_code,
    c.name AS course_name,
    d.name AS department_name,
    COUNT(e.enrollment_id) AS total_enrollments,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN e.grade >= 85 THEN 1 END) AS passing_students,
    ROUND(
        (COUNT(CASE WHEN e.grade >= 85 THEN 1 END) * 100.0 / COUNT(e.enrollment_id)), 2
    ) AS pass_rate_percentage
FROM courses c
JOIN departments d ON c.department_id = d.department_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
WHERE e.grade IS NOT NULL
GROUP BY c.course_id, c.course_code, c.name, d.name;
```

### Nested Views
Views based on other views.

```sql
-- View based on another view
CREATE VIEW high_performing_courses AS
SELECT 
    course_code,
    course_name,
    department_name,
    total_enrollments,
    average_grade,
    pass_rate_percentage
FROM enrollment_stats
WHERE average_grade >= 85
  AND pass_rate_percentage >= 80
ORDER BY average_grade DESC;
```

---

## 4. Introduction to Indexes

An **index** is a database object that improves the speed of data retrieval operations on a database table. Indexes can be created using one or more columns.

### How Indexes Work

- **B-tree Structure**: Most common index type
- **Sorted Data**: Indexes maintain sorted data for fast lookups
- **Pointer System**: Indexes point to actual table rows
- **Trade-off**: Faster reads, slower writes, additional storage

### When to Use Indexes

- **Frequent WHERE clauses**: Columns used in filtering
- **JOIN conditions**: Foreign key columns
- **ORDER BY**: Columns used for sorting
- **Large tables**: Tables with many rows
- **Unique constraints**: Enforcing uniqueness

### When NOT to Use Indexes

- **Small tables**: Tables with few rows
- **Frequently updated columns**: High write overhead
- **Low cardinality**: Columns with few unique values
- **Temporary tables**: Short-lived data

---

## 5. Types of Indexes

### Primary Key Index
Automatically created on primary key columns.

```sql
-- Primary key index is automatically created
CREATE TABLE students (
    student_id INT PRIMARY KEY,  -- Index automatically created
    first_name VARCHAR(50),
    last_name VARCHAR(50)
);
```

### Unique Index
Ensures uniqueness and provides fast lookups.

```sql
-- Create unique index on email
CREATE UNIQUE INDEX idx_student_email ON students(email);

-- Create unique composite index
CREATE UNIQUE INDEX idx_course_semester ON courses(course_code, semester);
```

### Regular Index
Improves query performance without uniqueness constraint.

```sql
-- Single column index
CREATE INDEX idx_student_department ON students(department_id);

-- Composite index
CREATE INDEX idx_enrollment_student_course ON enrollments(student_id, course_id);

-- Index on calculated expression
CREATE INDEX idx_student_fullname ON students(CONCAT(first_name, ' ', last_name));
```

### Partial Index
Index only a subset of rows based on a condition.

```sql
-- Index only active students
CREATE INDEX idx_active_students ON students(gpa) 
WHERE status = 'Active';

-- Index only passing grades
CREATE INDEX idx_passing_grades ON enrollments(grade) 
WHERE grade >= 85;
```

---

## 6. Index Strategies

### Single Column Indexes

```sql
-- Index frequently queried columns
CREATE INDEX idx_student_lastname ON students(last_name);
CREATE INDEX idx_student_gpa ON students(gpa);
CREATE INDEX idx_enrollment_date ON enrollments(enrollment_date);
```

### Composite Indexes

```sql
-- Composite index for common query patterns
CREATE INDEX idx_student_dept_gpa ON students(department_id, gpa);

-- Order matters: most selective column first
CREATE INDEX idx_enrollment_course_grade ON enrollments(course_id, grade);

-- Covering index (includes all needed columns)
CREATE INDEX idx_student_covering ON students(department_id, gpa, first_name, last_name);
```

### Index for Specific Queries

```sql
-- Analyze query patterns first
EXPLAIN SELECT 
    s.first_name, 
    s.last_name, 
    s.gpa
FROM students s
WHERE s.department_id = 1 
  AND s.gpa >= 3.5
ORDER BY s.gpa DESC;

-- Create index to support this query
CREATE INDEX idx_dept_gpa_covering ON students(department_id, gpa, first_name, last_name);
```

---

## 7. Performance Optimization

### Using EXPLAIN to Analyze Queries

```sql
-- Analyze query execution plan
EXPLAIN SELECT 
    s.first_name,
    s.last_name,
    d.name AS department_name
FROM students s
JOIN departments d ON s.department_id = d.department_id
WHERE s.gpa >= 3.0
ORDER BY s.gpa DESC;

-- More detailed analysis
EXPLAIN FORMAT=JSON SELECT 
    s.first_name,
    s.last_name,
    d.name AS department_name
FROM students s
JOIN departments d ON s.department_id = d.department_id
WHERE s.gpa >= 3.0
ORDER BY s.gpa DESC;
```

### Index Optimization Examples

```sql
-- Before: Full table scan
EXPLAIN SELECT * FROM students WHERE gpa >= 3.5;

-- After: Create index
CREATE INDEX idx_gpa ON students(gpa);
EXPLAIN SELECT * FROM students WHERE gpa >= 3.5;

-- Optimize JOIN performance
CREATE INDEX idx_student_dept ON students(department_id);
CREATE INDEX idx_department_id ON departments(department_id);

-- Optimize ORDER BY
CREATE INDEX idx_gpa_desc ON students(gpa DESC);
```

### Monitoring Index Usage

```sql
-- Check index usage statistics
SELECT 
    TABLE_NAME,
    INDEX_NAME,
    CARDINALITY,
    NULLABLE,
    INDEX_TYPE
FROM information_schema.STATISTICS
WHERE TABLE_SCHEMA = 'school_db'
ORDER BY TABLE_NAME, INDEX_NAME;

-- Find unused indexes
SELECT 
    s.TABLE_NAME,
    s.INDEX_NAME,
    s.CARDINALITY
FROM information_schema.STATISTICS s
LEFT JOIN information_schema.INDEX_STATISTICS i 
    ON s.TABLE_NAME = i.TABLE_NAME 
    AND s.INDEX_NAME = i.INDEX_NAME
WHERE s.TABLE_SCHEMA = 'school_db'
  AND i.INDEX_NAME IS NULL;
```

---

## 8. Best Practices

### View Best Practices

```sql
-- 1. Use descriptive names
CREATE VIEW student_academic_summary AS ...

-- 2. Include only necessary columns
CREATE VIEW student_basic_info AS
SELECT student_id, first_name, last_name, email
FROM students;

-- 3. Document complex views
-- View: student_performance_analysis
-- Purpose: Provides comprehensive student performance metrics
-- Last Updated: 2024-01-15
CREATE VIEW student_performance_analysis AS ...

-- 4. Use consistent naming conventions
CREATE VIEW vw_student_enrollments AS ...
CREATE VIEW vw_course_statistics AS ...
```

### Index Best Practices

```sql
-- 1. Create indexes on foreign keys
CREATE INDEX idx_student_department ON students(department_id);
CREATE INDEX idx_course_department ON courses(department_id);

-- 2. Index columns used in WHERE clauses
CREATE INDEX idx_student_status ON students(status);
CREATE INDEX idx_enrollment_semester ON enrollments(semester);

-- 3. Index columns used in ORDER BY
CREATE INDEX idx_student_gpa ON students(gpa DESC);

-- 4. Use composite indexes for multi-column queries
CREATE INDEX idx_student_dept_gpa ON students(department_id, gpa);

-- 5. Avoid over-indexing
-- Don't create indexes on every column
-- Monitor and remove unused indexes
```

### Performance Best Practices

```sql
-- 1. Use appropriate data types
-- Smaller data types = smaller indexes = better performance

-- 2. Limit SELECT * in views
CREATE VIEW student_list AS
SELECT student_id, first_name, last_name  -- Not SELECT *
FROM students;

-- 3. Use covering indexes
CREATE INDEX idx_covering ON students(department_id, gpa, first_name, last_name);

-- 4. Regular maintenance
ANALYZE TABLE students;
OPTIMIZE TABLE students;
```

---

## 9. Common Pitfalls

### View Pitfalls

```sql
-- ❌ PITFALL: Views can hide performance issues
CREATE VIEW slow_view AS
SELECT s.*, d.*, c.*, e.*
FROM students s
JOIN departments d ON s.department_id = d.department_id
JOIN enrollments e ON s.student_id = e.student_id
JOIN courses c ON e.course_id = c.course_id;

-- ✅ BETTER: Optimize the underlying query
CREATE VIEW optimized_view AS
SELECT 
    s.student_id,
    s.first_name,
    s.last_name,
    d.name AS department_name,
    c.course_code,
    e.grade
FROM students s
JOIN departments d ON s.department_id = d.department_id
JOIN enrollments e ON s.student_id = e.student_id
JOIN courses c ON e.course_id = c.course_id
WHERE e.grade IS NOT NULL;
```

### Index Pitfalls

```sql
-- ❌ PITFALL: Too many indexes
CREATE INDEX idx1 ON students(first_name);
CREATE INDEX idx2 ON students(last_name);
CREATE INDEX idx3 ON students(first_name, last_name);  -- Redundant

-- ✅ BETTER: Strategic indexing
CREATE INDEX idx_name ON students(last_name, first_name);  -- Covers both

-- ❌ PITFALL: Wrong column order in composite index
CREATE INDEX idx_bad ON students(gpa, department_id);  -- Low selectivity first

-- ✅ BETTER: High selectivity first
CREATE INDEX idx_good ON students(department_id, gpa);

-- ❌ PITFALL: Indexing frequently updated columns
CREATE INDEX idx_updated ON students(last_login);  -- Updated on every login

-- ✅ BETTER: Consider if the performance gain is worth the overhead
```

---

## 🎯 Summary

Views and indexes are essential tools for database optimization and data management:

### Views
- **Virtual tables** based on SQL queries
- **Security and abstraction** benefits
- **Simplified data access** for users
- **Centralized business logic**

### Indexes
- **Performance optimization** tools
- **Faster data retrieval** at the cost of storage and write speed
- **Strategic placement** on frequently queried columns
- **Monitoring and maintenance** required

### Key Takeaways
1. **Views**: Use for security, simplification, and consistency
2. **Indexes**: Use strategically for performance, not everywhere
3. **Analysis**: Use EXPLAIN to understand query performance
4. **Maintenance**: Regular monitoring and optimization needed
5. **Balance**: Performance vs storage vs write speed trade-offs

## 🔄 Next Steps

- Practice creating views for your common queries
- Analyze your queries with EXPLAIN
- Create strategic indexes for performance
- Move on to Lesson 13: Stored Procedures and Functions

## 📚 Additional Resources

- MySQL Documentation: [Views](https://dev.mysql.com/doc/refman/8.0/en/views.html)
- MySQL Documentation: [Indexes](https://dev.mysql.com/doc/refman/8.0/en/optimization-indexes.html)
- MySQL Documentation: [EXPLAIN](https://dev.mysql.com/doc/refman/8.0/en/explain.html)
