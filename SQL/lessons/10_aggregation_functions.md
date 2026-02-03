# Lesson 10: Aggregation Functions

## 📚 Learning Objectives

By the end of this lesson, you will be able to:
- Use basic aggregation functions (COUNT, SUM, AVG, MIN, MAX)
- Group data using GROUP BY clauses
- Filter grouped data with HAVING
- Understand the difference between WHERE and HAVING
- Use window functions for advanced aggregations
- Apply aggregation functions in real-world scenarios

## 🎯 Prerequisites

- Completed Lessons 1-9
- Understanding of SELECT statements
- Knowledge of JOINs and relationships
- Basic understanding of data types

## 📖 Table of Contents

1. [Introduction to Aggregation Functions](#introduction-to-aggregation-functions)
2. [Basic Aggregation Functions](#basic-aggregation-functions)
3. [GROUP BY Clauses](#group-by-clauses)
4. [HAVING vs WHERE](#having-vs-where)
5. [Window Functions](#window-functions)
6. [Practical Examples](#practical-examples)
7. [Best Practices](#best-practices)
8. [Common Pitfalls](#common-pitfalls)

---

## 1. Introduction to Aggregation Functions

Aggregation functions allow you to perform calculations on sets of rows and return a single result. These functions are essential for data analysis and reporting.

### Why Use Aggregation Functions?

- **Summarize data**: Get totals, averages, and counts
- **Group data**: Analyze patterns by categories
- **Compare values**: Find minimums, maximums, and ranges
- **Generate reports**: Create business intelligence insights

---

## 2. Basic Aggregation Functions

### COUNT() - Counting Records

```sql
-- Count total number of students
SELECT COUNT(*) AS total_students
FROM students;

-- Count students with GPA (non-NULL values)
SELECT COUNT(gpa) AS students_with_gpa
FROM students;

-- Count distinct departments
SELECT COUNT(DISTINCT department_id) AS unique_departments
FROM students;
```

### SUM() - Summing Values

```sql
-- Calculate total credits enrolled by all students
SELECT SUM(credits) AS total_credits_enrolled
FROM courses;

-- Sum GPA values (if stored as numeric)
SELECT SUM(gpa) AS total_gpa_sum
FROM students
WHERE gpa IS NOT NULL;
```

### AVG() - Calculating Averages

```sql
-- Calculate average GPA
SELECT AVG(gpa) AS average_gpa
FROM students
WHERE gpa IS NOT NULL;

-- Calculate average credits per course
SELECT AVG(credits) AS average_credits
FROM courses;
```

### MIN() and MAX() - Finding Extremes

```sql
-- Find highest and lowest GPA
SELECT 
    MIN(gpa) AS lowest_gpa,
    MAX(gpa) AS highest_gpa
FROM students
WHERE gpa IS NOT NULL;

-- Find earliest and latest enrollment dates
SELECT 
    MIN(enrollment_date) AS earliest_enrollment,
    MAX(enrollment_date) AS latest_enrollment
FROM enrollments;
```

---

## 3. GROUP BY Clauses

GROUP BY allows you to group rows that have the same values and apply aggregation functions to each group.

### Basic GROUP BY

```sql
-- Count students by department
SELECT 
    d.name AS department_name,
    COUNT(s.student_id) AS student_count
FROM departments d
LEFT JOIN students s ON d.department_id = s.department_id
GROUP BY d.department_id, d.name
ORDER BY student_count DESC;
```

### Multiple Column GROUP BY

```sql
-- Count enrollments by course and semester
SELECT 
    c.course_code,
    c.name AS course_name,
    e.semester,
    COUNT(e.enrollment_id) AS enrollment_count
FROM courses c
JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.name, e.semester
ORDER BY c.course_code, e.semester;
```

### GROUP BY with Multiple Aggregations

```sql
-- Department statistics
SELECT 
    d.name AS department_name,
    COUNT(s.student_id) AS student_count,
    AVG(s.gpa) AS average_gpa,
    MIN(s.gpa) AS min_gpa,
    MAX(s.gpa) AS max_gpa
FROM departments d
LEFT JOIN students s ON d.department_id = s.department_id
WHERE s.gpa IS NOT NULL
GROUP BY d.department_id, d.name
ORDER BY average_gpa DESC;
```

---

## 4. HAVING vs WHERE

Understanding the difference between WHERE and HAVING is crucial for effective SQL querying.

### WHERE Clause
- Filters rows **before** grouping
- Cannot use aggregation functions
- Applied to individual rows

### HAVING Clause
- Filters groups **after** grouping
- Can use aggregation functions
- Applied to grouped results

### Examples

```sql
-- WHERE: Filter students before grouping
SELECT 
    d.name AS department_name,
    COUNT(s.student_id) AS student_count,
    AVG(s.gpa) AS average_gpa
FROM departments d
LEFT JOIN students s ON d.department_id = s.department_id
WHERE s.gpa >= 3.0  -- Filter individual students with GPA >= 3.0
GROUP BY d.department_id, d.name;

-- HAVING: Filter groups after grouping
SELECT 
    d.name AS department_name,
    COUNT(s.student_id) AS student_count,
    AVG(s.gpa) AS average_gpa
FROM departments d
LEFT JOIN students s ON d.department_id = s.department_id
GROUP BY d.department_id, d.name
HAVING COUNT(s.student_id) >= 5  -- Only departments with 5+ students
   AND AVG(s.gpa) >= 3.0;       -- Only departments with avg GPA >= 3.0
```

### Combined WHERE and HAVING

```sql
-- Use both WHERE and HAVING together
SELECT 
    c.course_code,
    c.name AS course_name,
    COUNT(e.enrollment_id) AS enrollment_count,
    AVG(e.grade) AS average_grade
FROM courses c
JOIN enrollments e ON c.course_id = e.course_id
WHERE e.grade IS NOT NULL  -- Filter out NULL grades before grouping
GROUP BY c.course_id, c.course_code, c.name
HAVING COUNT(e.enrollment_id) >= 3  -- Only courses with 3+ enrollments
   AND AVG(e.grade) >= 85;          -- Only courses with avg grade >= 85
```

---

## 5. Window Functions

Window functions allow you to perform calculations across a set of table rows that are somehow related to the current row.

### ROW_NUMBER()

```sql
-- Rank students by GPA within their department
SELECT 
    s.student_id,
    s.first_name,
    s.last_name,
    d.name AS department_name,
    s.gpa,
    ROW_NUMBER() OVER (
        PARTITION BY s.department_id 
        ORDER BY s.gpa DESC
    ) AS department_rank
FROM students s
JOIN departments d ON s.department_id = d.department_id
WHERE s.gpa IS NOT NULL;
```

### RANK() and DENSE_RANK()

```sql
-- Rank courses by enrollment count
SELECT 
    c.course_code,
    c.name AS course_name,
    COUNT(e.enrollment_id) AS enrollment_count,
    RANK() OVER (ORDER BY COUNT(e.enrollment_id) DESC) AS rank_position,
    DENSE_RANK() OVER (ORDER BY COUNT(e.enrollment_id) DESC) AS dense_rank_position
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.name
ORDER BY enrollment_count DESC;
```

### LAG() and LEAD()

```sql
-- Compare student GPA with previous student in department
SELECT 
    s.student_id,
    s.first_name,
    s.last_name,
    d.name AS department_name,
    s.gpa,
    LAG(s.gpa) OVER (
        PARTITION BY s.department_id 
        ORDER BY s.gpa DESC
    ) AS previous_student_gpa,
    s.gpa - LAG(s.gpa) OVER (
        PARTITION BY s.department_id 
        ORDER BY s.gpa DESC
    ) AS gpa_difference
FROM students s
JOIN departments d ON s.department_id = d.department_id
WHERE s.gpa IS NOT NULL;
```

### SUM() OVER()

```sql
-- Running total of enrollments by date
SELECT 
    e.enrollment_id,
    s.first_name,
    s.last_name,
    c.course_code,
    e.enrollment_date,
    COUNT(*) OVER (
        ORDER BY e.enrollment_date 
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS running_total_enrollments
FROM enrollments e
JOIN students s ON e.student_id = s.student_id
JOIN courses c ON e.course_id = c.course_id
ORDER BY e.enrollment_date;
```

---

## 6. Practical Examples

### Example 1: Department Performance Analysis

```sql
-- Comprehensive department analysis
SELECT 
    d.name AS department_name,
    COUNT(DISTINCT s.student_id) AS total_students,
    COUNT(DISTINCT c.course_id) AS total_courses,
    AVG(s.gpa) AS average_gpa,
    COUNT(e.enrollment_id) AS total_enrollments,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN s.status = 'Active' THEN 1 END) AS active_students,
    COUNT(CASE WHEN e.grade >= 90 THEN 1 END) AS a_grades
FROM departments d
LEFT JOIN students s ON d.department_id = s.department_id
LEFT JOIN courses c ON d.department_id = c.department_id
LEFT JOIN enrollments e ON s.student_id = e.student_id
GROUP BY d.department_id, d.name
HAVING COUNT(DISTINCT s.student_id) > 0
ORDER BY average_gpa DESC;
```

### Example 2: Course Popularity Trends

```sql
-- Course enrollment trends by semester
SELECT 
    c.course_code,
    c.name AS course_name,
    e.semester,
    COUNT(e.enrollment_id) AS enrollment_count,
    AVG(e.grade) AS average_grade,
    COUNT(CASE WHEN e.grade >= 85 THEN 1 END) AS passing_students,
    ROUND(
        (COUNT(CASE WHEN e.grade >= 85 THEN 1 END) * 100.0 / COUNT(e.enrollment_id)), 2
    ) AS pass_rate_percentage
FROM courses c
JOIN enrollments e ON c.course_id = e.course_id
WHERE e.grade IS NOT NULL
GROUP BY c.course_id, c.course_code, c.name, e.semester
HAVING COUNT(e.enrollment_id) >= 2
ORDER BY c.course_code, e.semester;
```

### Example 3: Student Performance Ranking

```sql
-- Student performance with department and overall rankings
SELECT 
    s.student_id,
    s.first_name,
    s.last_name,
    d.name AS department_name,
    s.gpa,
    COUNT(e.enrollment_id) AS total_enrollments,
    AVG(e.grade) AS average_grade,
    RANK() OVER (ORDER BY s.gpa DESC) AS overall_gpa_rank,
    RANK() OVER (PARTITION BY s.department_id ORDER BY s.gpa DESC) AS dept_gpa_rank,
    RANK() OVER (ORDER BY AVG(e.grade) DESC) AS overall_grade_rank
FROM students s
JOIN departments d ON s.department_id = d.department_id
LEFT JOIN enrollments e ON s.student_id = e.student_id AND e.grade IS NOT NULL
WHERE s.gpa IS NOT NULL
GROUP BY s.student_id, s.first_name, s.last_name, d.department_id, d.name, s.gpa
ORDER BY s.gpa DESC;
```

---

## 7. Best Practices

### 1. Always Consider NULL Values
```sql
-- Good: Handle NULL values explicitly
SELECT 
    COUNT(CASE WHEN gpa IS NOT NULL THEN 1 END) AS students_with_gpa,
    AVG(gpa) AS average_gpa
FROM students;

-- Better: Use COALESCE for default values
SELECT 
    AVG(COALESCE(gpa, 0)) AS average_gpa_with_defaults
FROM students;
```

### 2. Use Meaningful Aliases
```sql
-- Good: Clear, descriptive aliases
SELECT 
    COUNT(*) AS total_students,
    AVG(gpa) AS average_gpa,
    MIN(gpa) AS minimum_gpa,
    MAX(gpa) AS maximum_gpa
FROM students;
```

### 3. Optimize GROUP BY
```sql
-- Good: Group by primary keys when possible
SELECT 
    d.department_id,
    d.name AS department_name,
    COUNT(s.student_id) AS student_count
FROM departments d
LEFT JOIN students s ON d.department_id = s.department_id
GROUP BY d.department_id, d.name;  -- Group by primary key + display column
```

### 4. Use Appropriate Aggregation Functions
```sql
-- Use COUNT(*) for counting rows, COUNT(column) for non-NULL values
SELECT 
    COUNT(*) AS total_rows,
    COUNT(gpa) AS rows_with_gpa,
    COUNT(DISTINCT department_id) AS unique_departments
FROM students;
```

---

## 8. Common Pitfalls

### Pitfall 1: Mixing Aggregate and Non-Aggregate Columns
```sql
-- ❌ ERROR: Non-aggregate column without GROUP BY
SELECT 
    first_name,  -- This will cause an error
    AVG(gpa)
FROM students;

-- ✅ CORRECT: Include in GROUP BY or use aggregate function
SELECT 
    department_id,
    AVG(gpa)
FROM students
GROUP BY department_id;
```

### Pitfall 2: Using WHERE with Aggregate Functions
```sql
-- ❌ ERROR: Cannot use aggregate functions in WHERE
SELECT 
    department_id,
    AVG(gpa)
FROM students
WHERE AVG(gpa) > 3.0;  -- This will cause an error

-- ✅ CORRECT: Use HAVING instead
SELECT 
    department_id,
    AVG(gpa)
FROM students
GROUP BY department_id
HAVING AVG(gpa) > 3.0;
```

### Pitfall 3: Forgetting to Handle NULL Values
```sql
-- ❌ POTENTIAL ISSUE: NULL values can affect results
SELECT 
    AVG(grade) AS average_grade
FROM enrollments;  -- Includes NULL grades

-- ✅ BETTER: Explicitly handle NULL values
SELECT 
    AVG(grade) AS average_grade
FROM enrollments
WHERE grade IS NOT NULL;
```

---

## 🎯 Summary

Aggregation functions are powerful tools for data analysis and reporting. Key takeaways:

1. **Basic Functions**: COUNT, SUM, AVG, MIN, MAX for summarizing data
2. **GROUP BY**: Essential for grouping data and applying aggregations
3. **HAVING vs WHERE**: Filter groups vs filter rows
4. **Window Functions**: Advanced aggregations across related rows
5. **Best Practices**: Handle NULLs, use meaningful aliases, optimize queries
6. **Common Pitfalls**: Avoid mixing aggregate/non-aggregate columns incorrectly

## 🔄 Next Steps

- Practice with the provided examples
- Try the exercises in Exercise 5
- Move on to Lesson 12: Views and Indexes
- Experiment with different aggregation scenarios in your database

## 📚 Additional Resources

- MySQL Documentation: [Aggregate Functions](https://dev.mysql.com/doc/refman/8.0/en/aggregate-functions.html)
- MySQL Documentation: [Window Functions](https://dev.mysql.com/doc/refman/8.0/en/window-functions.html)
- SQL Tutorial: [GROUP BY and HAVING](https://www.w3schools.com/sql/sql_groupby.asp)
