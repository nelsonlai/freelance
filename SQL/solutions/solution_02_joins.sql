-- Solution 2: JOIN Operations
-- Complete solutions for exercise_02_joins.sql

-- Exercise 2.1: Basic JOINs
-- Write queries to:

-- 1. Show all students with their enrollments (INNER JOIN)
-- Display: student name, enrollment date, grade, status
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    e.enrollment_date,
    e.grade,
    e.status
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id;

-- 2. Show all courses with their department names (INNER JOIN)
-- Display: course code, course name, department name, credits
SELECT 
    c.course_code,
    c.course_name,
    d.dept_name,
    c.credits
FROM courses c
INNER JOIN departments d ON c.dept_id = d.dept_id;

-- 3. Show all students, even if they have no enrollments (LEFT JOIN)
-- Display: student name, enrollment date (or NULL), grade (or NULL)
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    e.enrollment_date,
    e.grade
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id;

-- 4. Show all courses, even if no students are enrolled (LEFT JOIN)
-- Display: course code, course name, enrollment count
SELECT 
    c.course_code,
    c.course_name,
    COUNT(e.student_id) AS enrollment_count
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.course_name;

-- Exercise 2.2: Multiple Table JOINs
-- Write queries to:

-- 1. Show students with their enrolled courses and department names
-- Display: student name, course code, course name, department name, grade
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    c.course_code,
    c.course_name,
    d.dept_name,
    e.grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id;

-- 2. Show all enrollments with student info, course info, and department info
-- Display: student name, course code, course name, department name, enrollment date, grade
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    c.course_code,
    c.course_name,
    d.dept_name,
    e.enrollment_date,
    e.grade
FROM enrollments e
INNER JOIN students s ON e.student_id = s.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id;

-- 3. Show students with their completed courses and average grade
-- Display: student name, number of completed courses, average grade
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    COUNT(e.course_id) AS completed_courses,
    AVG(e.grade) AS average_grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
WHERE e.status = 'completed'
GROUP BY s.student_id, s.first_name, s.last_name;

-- Exercise 2.3: Finding Missing Data
-- Write queries to:

-- 1. Find students who are NOT enrolled in any courses
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id
WHERE e.student_id IS NULL;

-- 2. Find courses with NO enrollments
SELECT 
    c.course_code,
    c.course_name
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
WHERE e.course_id IS NULL;

-- 3. Find students who have enrollments but no completed courses
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
WHERE s.student_id NOT IN (
    SELECT DISTINCT student_id 
    FROM enrollments 
    WHERE status = 'completed'
);

-- 4. Find departments with no courses
SELECT 
    d.dept_name
FROM departments d
LEFT JOIN courses c ON d.dept_id = c.dept_id
WHERE c.dept_id IS NULL;

-- Exercise 2.4: Aggregation with JOINs
-- Write queries to:

-- 1. Count enrollments per student
-- Display: student name, enrollment count
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    COUNT(e.enrollment_id) AS enrollment_count
FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id
GROUP BY s.student_id, s.first_name, s.last_name;

-- 2. Count students per course
-- Display: course code, course name, student count
SELECT 
    c.course_code,
    c.course_name,
    COUNT(e.student_id) AS student_count
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.course_name;

-- 3. Calculate average grade per course
-- Display: course code, course name, average grade, enrollment count
SELECT 
    c.course_code,
    c.course_name,
    AVG(e.grade) AS average_grade,
    COUNT(e.student_id) AS enrollment_count
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.course_id, c.course_code, c.course_name;

-- 4. Calculate average grade per department
-- Display: department name, average grade, total enrollments
SELECT 
    d.dept_name,
    AVG(e.grade) AS average_grade,
    COUNT(e.enrollment_id) AS total_enrollments
FROM departments d
LEFT JOIN courses c ON d.dept_id = c.dept_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY d.dept_id, d.dept_name;

-- Exercise 2.5: Complex JOIN Analysis
-- Write queries to:

-- 1. Show student performance by department
-- Display: student name, department name, average grade in that department
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    d.dept_name,
    AVG(e.grade) AS average_grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id
GROUP BY s.student_id, s.first_name, s.last_name, d.dept_id, d.dept_name;

-- 2. Find the most popular course in each department
-- Display: department name, course code, course name, enrollment count
SELECT 
    d.dept_name,
    c.course_code,
    c.course_name,
    COUNT(e.student_id) AS enrollment_count
FROM departments d
INNER JOIN courses c ON d.dept_id = c.dept_id
LEFT JOIN enrollments e ON c.course_id = e.course_id
GROUP BY d.dept_id, d.dept_name, c.course_id, c.course_code, c.course_name
HAVING COUNT(e.student_id) = (
    SELECT MAX(enrollment_count)
    FROM (
        SELECT COUNT(e2.student_id) AS enrollment_count
        FROM courses c2
        LEFT JOIN enrollments e2 ON c2.course_id = e2.course_id
        WHERE c2.dept_id = d.dept_id
        GROUP BY c2.course_id
    ) AS dept_courses
);

-- 3. Show students enrolled in multiple courses
-- Display: student name, course count
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    COUNT(e.course_id) AS course_count
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
GROUP BY s.student_id, s.first_name, s.last_name
HAVING COUNT(e.course_id) > 1;

-- 4. Create a comprehensive student transcript
-- Display: student name, course code, course name, department name, grade, status
-- Sort by student name, then by course code
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    c.course_code,
    c.course_name,
    d.dept_name,
    e.grade,
    e.status
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id
ORDER BY s.last_name, s.first_name, c.course_code;

-- Exercise 2.6: Advanced JOIN Challenges
-- Write queries to:

-- 1. Find students who are enrolled in courses from multiple departments
-- Display: student name, department count, list of departments
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    COUNT(DISTINCT d.dept_id) AS department_count,
    GROUP_CONCAT(DISTINCT d.dept_name ORDER BY d.dept_name) AS departments
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id
GROUP BY s.student_id, s.first_name, s.last_name
HAVING COUNT(DISTINCT d.dept_id) > 1;

-- 2. Show course difficulty analysis (pass/fail rates)
-- Display: course code, course name, total enrollments, pass count, fail count, pass rate
SELECT 
    c.course_code,
    c.course_name,
    COUNT(e.student_id) AS total_enrollments,
    COUNT(CASE WHEN e.grade >= 70 THEN 1 END) AS pass_count,
    COUNT(CASE WHEN e.grade < 70 THEN 1 END) AS fail_count,
    ROUND(COUNT(CASE WHEN e.grade >= 70 THEN 1 END) * 100.0 / COUNT(e.student_id), 2) AS pass_rate
FROM courses c
LEFT JOIN enrollments e ON c.course_id = e.course_id
WHERE e.grade IS NOT NULL
GROUP BY c.course_id, c.course_code, c.course_name;

-- 3. Find students with above-average performance in their department
-- Display: student name, department name, student's average grade, department average grade
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    d.dept_name,
    AVG(e.grade) AS student_avg_grade,
    dept_avg.dept_average_grade
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id
INNER JOIN (
    SELECT 
        d2.dept_id,
        AVG(e2.grade) AS dept_average_grade
    FROM departments d2
    INNER JOIN courses c2 ON d2.dept_id = c2.dept_id
    INNER JOIN enrollments e2 ON c2.course_id = e2.course_id
    GROUP BY d2.dept_id
) dept_avg ON d.dept_id = dept_avg.dept_id
GROUP BY s.student_id, s.first_name, s.last_name, d.dept_id, d.dept_name, dept_avg.dept_average_grade
HAVING AVG(e.grade) > dept_avg.dept_average_grade;

-- 4. Show enrollment trends by year and department
-- Display: year, department name, enrollment count
SELECT 
    YEAR(e.enrollment_date) AS enrollment_year,
    d.dept_name,
    COUNT(e.enrollment_id) AS enrollment_count
FROM enrollments e
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id
GROUP BY YEAR(e.enrollment_date), d.dept_id, d.dept_name
ORDER BY enrollment_year, enrollment_count DESC;

-- Exercise 2.7: Self JOINs
-- Write queries to:

-- 1. Find students with the same GPA
-- Display: student1 name, student2 name, GPA
SELECT 
    CONCAT(s1.first_name, ' ', s1.last_name) AS student1_name,
    CONCAT(s2.first_name, ' ', s2.last_name) AS student2_name,
    s1.gpa
FROM students s1
INNER JOIN students s2 ON s1.gpa = s2.gpa AND s1.student_id < s2.student_id;

-- 2. Find students enrolled in the same courses
-- Display: student1 name, student2 name, course code, course name
SELECT 
    CONCAT(s1.first_name, ' ', s1.last_name) AS student1_name,
    CONCAT(s2.first_name, ' ', s2.last_name) AS student2_name,
    c.course_code,
    c.course_name
FROM students s1
INNER JOIN enrollments e1 ON s1.student_id = e1.student_id
INNER JOIN enrollments e2 ON e1.course_id = e2.course_id AND e1.student_id < e2.student_id
INNER JOIN students s2 ON e2.student_id = s2.student_id
INNER JOIN courses c ON e1.course_id = c.course_id;

-- 3. Find students with similar academic performance (GPA within 0.1)
-- Display: student1 name, student2 name, GPA1, GPA2
SELECT 
    CONCAT(s1.first_name, ' ', s1.last_name) AS student1_name,
    CONCAT(s2.first_name, ' ', s2.last_name) AS student2_name,
    s1.gpa AS gpa1,
    s2.gpa AS gpa2
FROM students s1
INNER JOIN students s2 ON ABS(s1.gpa - s2.gpa) <= 0.1 AND s1.student_id < s2.student_id;

-- Exercise 2.8: CROSS JOIN Applications
-- Write queries to:

-- 1. Show all possible student-course combinations
-- Display: student name, course code, course name, enrollment status
-- Limit to first 20 results
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    c.course_code,
    c.course_name,
    CASE 
        WHEN e.student_id IS NOT NULL THEN 'Enrolled'
        ELSE 'Not Enrolled'
    END AS enrollment_status
FROM students s
CROSS JOIN courses c
LEFT JOIN enrollments e ON s.student_id = e.student_id AND c.course_id = e.course_id
LIMIT 20;

-- 2. Find students who could potentially enroll in courses they're not currently taking
-- Display: student name, course code, course name
SELECT 
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    c.course_code,
    c.course_name
FROM students s
CROSS JOIN courses c
LEFT JOIN enrollments e ON s.student_id = e.student_id AND c.course_id = e.course_id
WHERE e.student_id IS NULL
LIMIT 20;

-- Bonus Exercise: Comprehensive Analysis
-- Create a detailed report showing:
-- Student ID, Student Name, Department, Courses Taken, Average Grade, Academic Standing
-- Only for active students, sorted by average grade (highest first)
SELECT 
    s.student_id,
    CONCAT(s.first_name, ' ', s.last_name) AS student_name,
    GROUP_CONCAT(DISTINCT d.dept_name ORDER BY d.dept_name) AS departments,
    COUNT(e.course_id) AS courses_taken,
    AVG(e.grade) AS average_grade,
    CASE 
        WHEN AVG(e.grade) >= 90 THEN 'A'
        WHEN AVG(e.grade) >= 80 THEN 'B'
        WHEN AVG(e.grade) >= 70 THEN 'C'
        WHEN AVG(e.grade) >= 60 THEN 'D'
        ELSE 'F'
    END AS academic_standing
FROM students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
INNER JOIN departments d ON c.dept_id = d.dept_id
WHERE s.status = 'active'
GROUP BY s.student_id, s.first_name, s.last_name
ORDER BY average_grade DESC;
