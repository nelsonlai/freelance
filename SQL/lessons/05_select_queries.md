# Lesson 5: Querying Data (SELECT)

## Learning Objectives
- Learn the basic SELECT statement syntax
- Understand filtering data with WHERE clause
- Practice sorting results with ORDER BY
- Learn about limiting results and pagination
- Understand pattern matching with LIKE

## Basic SELECT Statement

### Select All Columns

```sql
-- Select all columns from a table
SELECT * FROM students;

-- Select all columns from multiple tables
SELECT * FROM students, courses;
```

### Select Specific Columns

```sql
-- Select specific columns
SELECT first_name, last_name, email FROM students;

-- Select with column aliases
SELECT 
    first_name AS 'First Name',
    last_name AS 'Last Name',
    email AS 'Email Address'
FROM students;

-- Select with expressions
SELECT 
    first_name,
    last_name,
    CONCAT(first_name, ' ', last_name) AS full_name,
    YEAR(enrollment_date) AS enrollment_year
FROM students;
```

### Select with DISTINCT

```sql
-- Select distinct values
SELECT DISTINCT status FROM students;

-- Select distinct combinations
SELECT DISTINCT dept_id, status FROM students;
```

## WHERE Clause - Filtering Data

### Basic WHERE Conditions

```sql
-- Filter by exact match
SELECT * FROM students WHERE status = 'active';

-- Filter by numeric comparison
SELECT * FROM students WHERE gpa >= 3.5;

-- Filter by date
SELECT * FROM students WHERE enrollment_date >= '2024-01-01';

-- Filter by NULL values
SELECT * FROM students WHERE phone IS NULL;
SELECT * FROM students WHERE phone IS NOT NULL;
```

### Multiple Conditions

```sql
-- AND condition
SELECT * FROM students 
WHERE status = 'active' AND gpa >= 3.5;

-- OR condition
SELECT * FROM students 
WHERE status = 'active' OR status = 'graduated';

-- Complex conditions with parentheses
SELECT * FROM students 
WHERE (status = 'active' AND gpa >= 3.5) 
   OR (status = 'graduated' AND gpa >= 3.0);
```

### IN and NOT IN

```sql
-- IN operator
SELECT * FROM students 
WHERE status IN ('active', 'graduated');

-- NOT IN operator
SELECT * FROM students 
WHERE status NOT IN ('inactive');

-- IN with subquery
SELECT * FROM courses 
WHERE dept_id IN (SELECT dept_id FROM departments WHERE budget > 400000);
```

### BETWEEN Operator

```sql
-- BETWEEN for numeric ranges
SELECT * FROM students WHERE gpa BETWEEN 3.0 AND 3.8;

-- BETWEEN for date ranges
SELECT * FROM students 
WHERE enrollment_date BETWEEN '2023-09-01' AND '2024-01-01';

-- NOT BETWEEN
SELECT * FROM students WHERE gpa NOT BETWEEN 2.0 AND 3.0;
```

## LIKE Operator - Pattern Matching

### Basic Pattern Matching

```sql
-- Starts with
SELECT * FROM students WHERE first_name LIKE 'J%';

-- Ends with
SELECT * FROM students WHERE email LIKE '%@university.edu';

-- Contains
SELECT * FROM students WHERE last_name LIKE '%son';

-- Exact length
SELECT * FROM students WHERE first_name LIKE '____'; -- 4 characters
```

### Advanced Pattern Matching

```sql
-- Multiple patterns
SELECT * FROM students 
WHERE first_name LIKE 'J%' OR first_name LIKE 'A%';

-- Case insensitive (MySQL default)
SELECT * FROM students WHERE first_name LIKE 'john';

-- Using REGEXP for complex patterns
SELECT * FROM students WHERE email REGEXP '^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z {2,}$';
```

## ORDER BY - Sorting Results

### Basic Sorting

```sql
-- Sort by single column (ascending)
SELECT * FROM students ORDER BY last_name;

-- Sort by single column (descending)
SELECT * FROM students ORDER BY gpa DESC;

-- Sort by multiple columns
SELECT * FROM students ORDER BY status, gpa DESC;
```

### Advanced Sorting

```sql
-- Sort by expression
SELECT 
    first_name,
    last_name,
    CONCAT(first_name, ' ', last_name) AS full_name
FROM students 
ORDER BY full_name;

-- Sort by column position
SELECT first_name, last_name, gpa FROM students ORDER BY 3 DESC;

-- Custom sorting with CASE
SELECT * FROM students 
ORDER BY 
    CASE status
        WHEN 'active' THEN student_id -- student_id
        WHEN 'graduated' THEN first_name -- first_name
        WHEN 'inactive' THEN last_name -- last_name
    END;
```

## LIMIT - Limiting Results (Pagination)

### Basic LIMIT

```sql
-- Limit number of rows
SELECT * FROM students LIMIT 5;

-- Limit with offset (pagination)
SELECT * FROM students LIMIT 5 OFFSET 10; -- Skip first 10, get next 5

-- Alternative syntax
SELECT * FROM students LIMIT 10, 5; -- Same as LIMIT 5 OFFSET 10
```

### Pagination Example

```sql
-- Page 1: First 10 students
SELECT * FROM students ORDER BY last_name LIMIT 10;

-- Page 2: Next 10 students
SELECT * FROM students ORDER BY last_name LIMIT 10 OFFSET 10;

-- Page 3: Next 10 students
SELECT * FROM students ORDER BY last_name LIMIT 10 OFFSET 20;
```

## Aggregate Functions

### Basic Aggregates

```sql
-- COUNT
SELECT COUNT(*) FROM students;
SELECT COUNT(phone) FROM students; -- Count non-NULL values

-- SUM, AVG, MIN, MAX
SELECT 
    COUNT(*) AS total_students,
    AVG(gpa) AS average_gpa,
    MIN(gpa) AS min_gpa,
    MAX(gpa) AS max_gpa,
    SUM(CASE WHEN status = 'active' THEN 1 ELSE 0 END) AS active_students
FROM students;
```

### GROUP BY

```sql
-- Group by single column
SELECT status, COUNT(*) FROM students GROUP BY status;

-- Group by multiple columns
SELECT status, YEAR(enrollment_date), COUNT(*) 
FROM students 
GROUP BY status, YEAR(enrollment_date);

-- Group with aggregate functions
SELECT 
    dept_id,
    COUNT(*) AS course_count,
    AVG(credits) AS avg_credits,
    SUM(credits) AS total_credits
FROM courses 
GROUP BY dept_id;
```

### HAVING Clause

```sql
-- HAVING filters groups (WHERE filters rows)
SELECT 
    dept_id,
    COUNT(*) AS course_count,
    AVG(credits) AS avg_credits
FROM courses 
GROUP BY dept_id
HAVING COUNT(*) > 2 AND AVG(credits) > 3;
```

## Complete Examples

### Student Analysis Query

```sql
-- Comprehensive student analysis
SELECT 
    s.student_id,
    CONCAT(s.first_name, ' ', s.last_name) AS full_name,
    s.email,
    s.gpa,
    s.status,
    YEAR(s.enrollment_date) AS enrollment_year,
    CASE 
        WHEN s.gpa >= 3.7 THEN 'High Honors'
        WHEN s.gpa >= 3.3 THEN 'Honors'
        WHEN s.gpa >= 3.0 THEN 'Good Standing'
        ELSE 'Academic Probation'
    END AS academic_standing
FROM students s
WHERE s.status = 'active'
ORDER BY s.gpa DESC, s.last_name;
```

### Course Enrollment Analysis

```sql
-- Course enrollment statistics
SELECT 
    c.course_code,
    c.course_name,
    d.dept_name,
    COUNT(e.student_id) AS enrolled_students,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN e.status = 'completed' THEN 1 END) AS completed_students
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
LEFT JOIN departments d ON c.dept_id = d.dept_id
GROUP BY c.course_id, c.course_code, c.course_name, d.dept_name
ORDER BY enrolled_students DESC;
```

### Department Statistics

```sql
-- Department performance metrics
SELECT 
    d.dept_name,
    COUNT(DISTINCT c.course_id) AS total_courses,
    COUNT(DISTINCT e.student_id) AS total_enrollments,
    AVG(e.grade) AS average_grade,
    COUNT(DISTINCT CASE WHEN e.status = 'completed' THEN e.student_id END) AS completed_students
FROM departments d
LEFT JOIN courses c ON d.dept_id = c.dept_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY d.dept_id, d.dept_name
ORDER BY total_enrollments DESC;
```

## Hands-on Exercise

### Exercise 1: Basic Queries

Write queries to:

1. Find all active students with GPA above 3.5
2. Find students whose last name starts with 'S' or 'D'
3. Find students enrolled in 2023, sorted by GPA (highest first)
4. Find the top 5 students by GPA
5. Count students by status

### Exercise 2: Advanced Queries

Write queries to:

1. Find students who have completed at least one course
2. Find courses with more than 2 enrollments
3. Find the average GPA by enrollment year
4. Find students with phone numbers (not NULL)
5. Find students whose email domain is not '@university.edu'

### Exercise 3: Complex Analysis

Write queries to:

1. Create a student report showing full name, GPA, status, and academic standing
2. Find department statistics (number of courses, total enrollments, average grade)
3. Find students who are enrolled in courses but haven't completed any
4. Create a paginated student list (10 students per page)

## Key Takeaways

- SELECT retrieves data from tables
- WHERE filters rows based on conditions
- ORDER BY sorts results
- LIMIT controls the number of returned rows
- LIKE enables pattern matching
- Aggregate functions summarize data
- GROUP BY groups rows for aggregation
- HAVING filters grouped results

## Next Steps

In the next lesson, we'll learn how to update and delete data in our tables.

## Practice Questions

1. What's the difference between WHERE and HAVING?
2. How do you sort results in descending order?
3. What's the purpose of the LIMIT clause?
4. How do you find NULL values in a column?
5. What's the difference between COUNT(*) and COUNT(column_name)?
