-- ===================================================================
-- Solution 1: Basic SQL Queries - Complete Solutions
-- ===================================================================
-- This file contains complete, commented solutions for all exercises
-- in exercise_01_basic_queries.sql. Each solution includes:
-- 1. Detailed explanations of SQL concepts
-- 2. Alternative approaches where applicable
-- 3. Performance considerations
-- 4. Best practices and tips
-- ===================================================================

-- ===================================================================
-- EXERCISE 1.1: BASIC SELECT STATEMENTS
-- ===================================================================
-- These exercises introduce the fundamental SELECT statement and its variations

-- 1. Select all columns from the students table
-- This is the simplest SELECT statement using the wildcard (*) operator
-- Note: In production, avoid SELECT * and specify only needed columns
SELECT * FROM students;

-- 2. Select only specific columns from students table
-- Best practice: Always specify only the columns you need
-- This improves performance and makes queries more maintainable
SELECT first_name, last_name, email FROM students;

-- 3. Select students with GPA above 3.5 using WHERE clause
-- WHERE clause filters rows based on specified conditions
-- Comparison operators: =, !=, <>, <, >, <=, >=
SELECT * FROM students WHERE gpa > 3.5;

-- 4. Select students whose last name starts with 'S' using LIKE operator
-- LIKE operator performs pattern matching with wildcards:
-- % matches any sequence of characters (including zero characters)
-- _ matches exactly one character
SELECT * FROM students WHERE last_name LIKE 'S%';

-- 5. Select students enrolled in 2023, sorted by GPA (highest first)
-- YEAR() function extracts the year from a date
-- ORDER BY sorts results (ASC = ascending, DESC = descending)
-- Multiple columns can be specified for complex sorting
SELECT * FROM students 
WHERE YEAR(enrollment_date) = 2023 
ORDER BY gpa DESC;

-- ===================================================================
-- EXERCISE 1.2: WHERE CLAUSE PRACTICE
-- ===================================================================
-- These exercises focus on filtering data using various WHERE conditions

-- 1. Find all active students using equality comparison
-- Exact match using = operator
-- ENUM values are case-sensitive in MySQL
SELECT * FROM students WHERE status = 'active';

-- 2. Find students with GPA between 3.0 and 3.8 using BETWEEN operator
-- BETWEEN is inclusive of both boundary values
-- Equivalent to: WHERE gpa >= 3.0 AND gpa <= 3.8
SELECT * FROM students WHERE gpa BETWEEN 3.0 AND 3.8;

-- 3. Find students whose email contains '@university.edu' using LIKE
-- % wildcard matches any characters before and after '@university.edu'
-- This finds emails ending with '@university.edu'
SELECT * FROM students WHERE email LIKE '%@university.edu';

-- 4. Find students with NULL phone numbers using IS NULL
-- NULL values require special handling with IS NULL or IS NOT NULL
-- Cannot use = NULL or != NULL for NULL comparisons
SELECT * FROM students WHERE phone IS NULL;

-- 5. Find students with status 'active' OR 'graduated' using IN operator
-- IN operator checks if value matches any in a list
-- More efficient than multiple OR conditions
-- Equivalent to: WHERE status = 'active' OR status = 'graduated'
SELECT * FROM students WHERE status IN ('active', 'graduated');

-- Exercise 1.3: ORDER BY and LIMIT
-- Write queries to:

-- 1. Show students sorted by last name (alphabetical)
SELECT * FROM students ORDER BY last_name;

-- 2. Show top 5 students by GPA
SELECT * FROM students ORDER BY gpa DESC LIMIT 5;

-- 3. Show students sorted by enrollment date (newest first)
SELECT * FROM students ORDER BY enrollment_date DESC;

-- 4. Show the 3rd through 5th students when sorted by GPA
SELECT * FROM students ORDER BY gpa DESC LIMIT 3 OFFSET 2;

-- Exercise 1.4: Aggregate functions
-- Write queries to:

-- 1. Count total number of students
SELECT COUNT(*) AS total_students FROM students;

-- 2. Calculate average GPA of all students
SELECT AVG(gpa) AS average_gpa FROM students;

-- 3. Find minimum and maximum GPA
SELECT MIN(gpa) AS min_gpa, MAX(gpa) AS max_gpa FROM students;

-- 4. Count students by status
SELECT status, COUNT(*) AS count FROM students GROUP BY status;

-- 5. Calculate average GPA by status
SELECT status, AVG(gpa) AS average_gpa FROM students GROUP BY status;

-- Exercise 1.5: Data insertion
-- Write INSERT statements to:

-- 1. Insert a new student with the following data:
--    First name: 'Test', Last name: 'Student', Email: 'test.student@university.edu'
--    Phone: '555-9999', Enrollment date: '2024-01-15', GPA: 3.5, Status: 'active'
INSERT INTO students (first_name, last_name, email, phone, enrollment_date, gpa, status)
VALUES ('Test', 'Student', 'test.student@university.edu', '555-9999', '2024-01-15', 3.5, 'active');

-- 2. Insert a new department:
--    Name: 'Test Department', Budget: 100000.00, Established date: '2024-01-01'
INSERT INTO departments (dept_name, budget, established_date)
VALUES ('Test Department', 100000.00, '2024-01-01');

-- 3. Insert a new course:
--    Code: 'TEST101', Name: 'Test Course', Credits: 3, Department: Test Department
INSERT INTO courses (course_code, course_name, credits, dept_id)
VALUES ('TEST101', 'Test Course', 3, (SELECT dept_id FROM departments WHERE dept_name = 'Test Department'));

-- Exercise 1.6: Data modification
-- Write UPDATE statements to:

-- 1. Update the GPA of student with ID 1 to 3.8
UPDATE students SET gpa = 3.8 WHERE student_id = 1;

-- 2. Update all inactive students to have status 'active'
UPDATE students SET status = 'active' WHERE status = 'inactive';

-- 3. Update the phone number of student with email 'test.student@university.edu' to '555-8888'
UPDATE students SET phone = '555-8888' WHERE email = 'test.student@university.edu';

-- Exercise 1.7: Data deletion
-- Write DELETE statements to:

-- 1. Delete the test student you created
DELETE FROM students WHERE email = 'test.student@university.edu';

-- 2. Delete the test department you created
DELETE FROM departments WHERE dept_name = 'Test Department';

-- 3. Delete the test course you created
DELETE FROM courses WHERE course_code = 'TEST101';

-- Exercise 1.8: Complex queries
-- Write queries to:

-- 1. Find students whose first name is exactly 4 characters long
SELECT * FROM students WHERE LENGTH(first_name) = 4;

-- 2. Find students enrolled in both 2023 and 2024 (hint: use subqueries or multiple conditions)
SELECT DISTINCT s.* FROM students s
WHERE s.student_id IN (
    SELECT student_id FROM enrollments WHERE YEAR(enrollment_date) = 2023
)
AND s.student_id IN (
    SELECT student_id FROM enrollments WHERE YEAR(enrollment_date) = 2024
);

-- 3. Find the student with the highest GPA in each status group
SELECT s1.* FROM students s1
WHERE s1.gpa = (
    SELECT MAX(s2.gpa) 
    FROM students s2 
    WHERE s2.status = s1.status
);

-- 4. Calculate the percentage of students with GPA above 3.5
SELECT 
    COUNT(CASE WHEN gpa > 3.5 THEN 1 END) * 100.0 / COUNT(*) AS percentage_above_3_5
FROM students;

-- 5. Find students whose email domain is NOT '@university.edu'
SELECT * FROM students WHERE email NOT LIKE '%@university.edu';

-- Bonus Exercise: Create a comprehensive student report
-- Write a query that shows:
-- Student ID, Full Name (First Last), Email, Phone, GPA, Status, Enrollment Year
-- Only for active students, sorted by GPA (highest first)
SELECT 
    student_id,
    CONCAT(first_name, ' ', last_name) AS full_name,
    email,
    phone,
    gpa,
    status,
    YEAR(enrollment_date) AS enrollment_year
FROM students 
WHERE status = 'active'
ORDER BY gpa DESC;
