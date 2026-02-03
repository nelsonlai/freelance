# Lesson 7: Joins and Relationships

## Learning Objectives
- Understand different types of JOINs
- Learn how to combine data from multiple tables
- Practice writing complex queries with JOINs
- Understand relationship types and foreign keys

## Understanding Relationships

### Types of Relationships

1. **One-to-One**: Each record in Table A relates to exactly one record in Table B
2. **One-to-Many**: Each record in Table A can relate to many records in Table B
3. **Many-to-Many**: Records in Table A can relate to many records in Table B, and vice versa

### Foreign Keys

```sql
-- Example of foreign key relationships
CREATE TABLE departments (
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(100) NOT NULL
);

CREATE TABLE courses (
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    course_name VARCHAR(100) NOT NULL,
    dept_id INT,
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id)
);

CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL
);

CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    enrollment_date DATE,
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (course_id) REFERENCES courses(course_id)
);
```

## INNER JOIN

### Basic INNER JOIN

```sql
-- Join students with their enrollments
SELECT 
    s.first_name,   -- student.first_name
    s.last_name,
    e.enrollment_date,  -- enrollements
    e.grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id;

-- Join courses with departments
SELECT 
    c.course_code,
    c.course_name,
    d.dept_name
FROM courses c
INNER JOIN departments d ON c.dept_id = d.dept_id;
```

### Multiple Table INNER JOIN

```sql
-- Join students, enrollments, and courses
SELECT 
    s.first_name,
    s.last_name,
    c.course_code,
    c.course_name,
    e.enrollment_date,
    e.grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id;

-- Join with departments as well
SELECT 
    s.first_name,
    s.last_name,
    c.course_code,
    c.course_name,
    d.dept_name,
    e.grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id;
```

## LEFT JOIN (LEFT OUTER JOIN)

### Basic LEFT JOIN

```sql
-- Show all students, even if they have no enrollments
SELECT 
    s.first_name,
    s.last_name,
    e.enrollment_date,
    e.grade
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id;

-- Show all courses, even if no students are enrolled
SELECT 
    c.course_code,
    c.course_name,
    COUNT(e.student_id) AS enrolled_students
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.course_name;
```

### LEFT JOIN with WHERE

```sql
-- Find students who are NOT enrolled in any courses
SELECT 
    s.first_name,
    s.last_name
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id
WHERE e.student_id IS NULL;

-- Find courses with no enrollments
SELECT 
    c.course_code,
    c.course_name
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
WHERE e.course_id IS NULL;
```

## RIGHT JOIN (RIGHT OUTER JOIN)

### Basic RIGHT JOIN

```sql
-- Show all enrollments, even if student doesn't exist (data integrity check)
SELECT 
    s.first_name,
    s.last_name,
    e.enrollment_date,
    e.grade
FROM students s
RIGHT JOIN enrollments e ON s.student_id = e.student_id;

-- Show all departments, even if they have no courses
SELECT 
    d.dept_name,
    c.course_code,
    c.course_name
FROM departments d
RIGHT JOIN courses c ON d.dept_id = c.dept_id;
```

## FULL OUTER JOIN

### Simulating FULL OUTER JOIN in MySQL

```sql
-- MySQL doesn't have FULL OUTER JOIN, but we can simulate it
-- Show all students and all enrollments
SELECT 
    s.first_name,
    s.last_name,
    e.enrollment_date,
    e.grade
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id

UNION

SELECT 
    s.first_name,
    s.last_name,
    e.enrollment_date,
    e.grade
FROM students s
RIGHT JOIN enrollments e ON s.student_id = e.student_id
WHERE s.student_id IS NULL;
```

## CROSS JOIN

### Basic CROSS JOIN

```sql
-- Cartesian product of students and courses
SELECT 
    s.first_name,
    s.last_name,
    c.course_code,
    c.course_name
FROM students s
CROSS JOIN courses c;

-- Useful for generating all possible combinations
SELECT 
    s.first_name,
    s.last_name,
    c.course_code,
    CASE 
        WHEN e.student_id IS NOT NULL THEN 'Enrolled'
        ELSE 'Not Enrolled'
    END AS enrollment_status
FROM students s
CROSS JOIN courses c
LEFT JOIN enrollments e ON s.student_id = e.student_id AND c.course_id = e.course_id;
```

## Self JOIN

### Self JOIN Examples

```sql
-- Find students with the same GPA (self join)
SELECT 
    s1.first_name AS student1_first,
    s1.last_name AS student1_last,
    s2.first_name AS student2_first,
    s2.last_name AS student2_last,
    s1.gpa
FROM students s1
INNER JOIN students s2 ON s1.gpa = s2.gpa AND s1.student_id < s2.student_id;

-- Find students enrolled in multiple courses
SELECT 
    s.first_name,
    s.last_name,
    COUNT(e.course_id) AS course_count
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
GROUP BY s.student_id, s.first_name, s.last_name
HAVING COUNT(e.course_id) > 1;
```

## Complex JOIN Examples

### Student Performance Analysis

```sql
-- Comprehensive student performance report
SELECT 
    s.student_id,
    CONCAT(s.first_name, ' ', s.last_name) AS full_name,
    s.gpa AS student_gpa,
    COUNT(e.course_id) AS courses_taken,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN e.grade >= 90 THEN 1 END) AS A_grades,
    COUNT(CASE WHEN e.grade >= 80 AND e.grade < 90 THEN 1 END) AS B_grades,
    COUNT(CASE WHEN e.grade >= 70 AND e.grade < 80 THEN 1 END) AS C_grades,
    COUNT(CASE WHEN e.grade < 70 THEN 1 END) AS failing_grades
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id AND e.status = 'completed'
GROUP BY s.student_id, s.first_name, s.last_name, s.gpa
ORDER BY average_grade DESC;
```

### Department Analysis

```sql
-- Department performance metrics
SELECT 
    d.dept_name,
    COUNT(DISTINCT c.course_id) AS total_courses,
    COUNT(DISTINCT e.student_id) AS total_students,
    COUNT(e.enrollment_id) AS total_enrollments,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN e.status = 'completed' THEN 1 END) AS completed_enrollments,
    COUNT(CASE WHEN e.status = 'enrolled' THEN 1 END) AS active_enrollments
FROM departments d
LEFT JOIN courses c ON d.dept_id = c.dept_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY d.dept_id, d.dept_name
ORDER BY total_enrollments DESC;
```

### Course Popularity Analysis

```sql
-- Most popular courses
SELECT 
    c.course_code,
    c.course_name,
    d.dept_name,
    COUNT(e.student_id) AS enrollment_count,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN e.grade >= 90 THEN 1 END) AS A_students,
    COUNT(CASE WHEN e.grade < 70 THEN 1 END) AS failing_students,
    ROUND(COUNT(CASE WHEN e.grade >= 70 THEN 1 END) * 100.0 / COUNT(e.student_id), 2) AS pass_rate
FROM courses c
LEFT JOIN departments d ON c.dept_id = d.dept_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.course_name, d.dept_name
HAVING COUNT(e.student_id) > 0
ORDER BY enrollment_count DESC, average_grade DESC;
```

## JOIN Performance Tips

### Indexing for JOINs

```sql
-- Create indexes on foreign key columns for better JOIN performance
CREATE INDEX idx_enrollments_student_id ON enrollments(student_id);
CREATE INDEX idx_enrollments_course_id ON enrollments(course_id);
CREATE INDEX idx_courses_dept_id ON courses(dept_id);

-- Composite indexes for multi-column JOINs
CREATE INDEX idx_enrollments_student_course ON enrollments(student_id, course_id);
```

### Query Optimization

```sql
-- Use appropriate JOIN types
-- Use INNER JOIN when you only want matching records
-- Use LEFT JOIN when you want all records from the left table
-- Use RIGHT JOIN when you want all records from the right table

-- Filter early with WHERE clause
SELECT s.first_name, s.last_name, e.grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
WHERE s.status = 'active'  -- Filter before JOIN
AND e.grade >= 80;

-- Use LIMIT to reduce result set
SELECT s.first_name, s.last_name, e.grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
ORDER BY e.grade DESC
LIMIT 10;
```

## Hands-on Exercise

### Exercise 1: Basic JOINs

Write queries to:

1. Show all students with their enrolled courses
2. Show all courses with their department names
3. Find students who haven't enrolled in any courses
4. Find courses with no enrollments

### Exercise 2: Complex JOINs

Write queries to:

1. Show student performance by department
2. Find the most popular course in each department
3. Show students who are enrolled in multiple courses
4. Create a report showing all students and their course enrollments (including students with no enrollments)

### Exercise 3: Analytical Queries

Write queries to:

1. Calculate department statistics (courses, students, average grades)
2. Find students with above-average performance in their department
3. Show course difficulty analysis (pass rates, average grades)
4. Create a comprehensive student transcript report

## Key Takeaways

- INNER JOIN returns only matching records from both tables
- LEFT JOIN returns all records from the left table and matching records from the right table
- RIGHT JOIN returns all records from the right table and matching records from the left table
- CROSS JOIN returns the Cartesian product of both tables
- Self JOINs are useful for comparing records within the same table
- Proper indexing improves JOIN performance
- Use appropriate JOIN types based on your data requirements

## Next Steps

In the next lesson, we'll learn about aggregation functions and grouping data.

## Practice Questions

1. What's the difference between INNER JOIN and LEFT JOIN?
2. When would you use a CROSS JOIN?
3. How do you find records that don't have matches in another table?
4. What's the purpose of a self JOIN?
5. How can you optimize JOIN performance?
