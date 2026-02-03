-- Exercise 2: JOIN Operations
-- Complete the following exercises to practice JOIN operations

-- Exercise 2.1: Basic JOINs
-- Write queries to:

-- 1. Show all students with their enrollments (INNER JOIN)
-- Display: student name, enrollment date, grade, status
-- Your query here:

-- 2. Show all courses with their department names (INNER JOIN)
-- Display: course code, course name, department name, credits
-- Your query here:

-- 3. Show all students, even if they have no enrollments (LEFT JOIN)
-- Display: student name, enrollment date (or NULL), grade (or NULL)
-- Your query here:

-- 4. Show all courses, even if no students are enrolled (LEFT JOIN)
-- Display: course code, course name, enrollment count
-- Your query here:

-- Exercise 2.2: Multiple Table JOINs
-- Write queries to:

-- 1. Show students with their enrolled courses and department names
-- Display: student name, course code, course name, department name, grade
-- Your query here:

-- 2. Show all enrollments with student info, course info, and department info
-- Display: student name, course code, course name, department name, enrollment date, grade
-- Your query here:

-- 3. Show students with their completed courses and average grade
-- Display: student name, number of completed courses, average grade
-- Your query here:

-- Exercise 2.3: Finding Missing Data
-- Write queries to:

-- 1. Find students who are NOT enrolled in any courses
-- Your query here:

-- 2. Find courses with NO enrollments
-- Your query here:

-- 3. Find students who have enrollments but no completed courses
-- Your query here:

-- 4. Find departments with no courses
-- Your query here:

-- Exercise 2.4: Aggregation with JOINs
-- Write queries to:

-- 1. Count enrollments per student
-- Display: student name, enrollment count
-- Your query here:

-- 2. Count students per course
-- Display: course code, course name, student count
-- Your query here:

-- 3. Calculate average grade per course
-- Display: course code, course name, average grade, enrollment count
-- Your query here:

-- 4. Calculate average grade per department
-- Display: department name, average grade, total enrollments
-- Your query here:

-- Exercise 2.5: Complex JOIN Analysis
-- Write queries to:

-- 1. Show student performance by department
-- Display: student name, department name, average grade in that department
-- Your query here:

-- 2. Find the most popular course in each department
-- Display: department name, course code, course name, enrollment count
-- Your query here:

-- 3. Show students enrolled in multiple courses
-- Display: student name, course count
-- Your query here:

-- 4. Create a comprehensive student transcript
-- Display: student name, course code, course name, department name, grade, status
-- Sort by student name, then by course code
-- Your query here:

-- Exercise 2.6: Advanced JOIN Challenges
-- Write queries to:

-- 1. Find students who are enrolled in courses from multiple departments
-- Display: student name, department count, list of departments
-- Your query here:

-- 2. Show course difficulty analysis (pass/fail rates)
-- Display: course code, course name, total enrollments, pass count, fail count, pass rate
-- Your query here:

-- 3. Find students with above-average performance in their department
-- Display: student name, department name, student's average grade, department average grade
-- Your query here:

-- 4. Show enrollment trends by year and department
-- Display: year, department name, enrollment count
-- Your query here:

-- Exercise 2.7: Self JOINs
-- Write queries to:

-- 1. Find students with the same GPA
-- Display: student1 name, student2 name, GPA
-- Your query here:

-- 2. Find students enrolled in the same courses
-- Display: student1 name, student2 name, course code, course name
-- Your query here:

-- 3. Find students with similar academic performance (GPA within 0.1)
-- Display: student1 name, student2 name, GPA1, GPA2
-- Your query here:

-- Exercise 2.8: CROSS JOIN Applications
-- Write queries to:

-- 1. Show all possible student-course combinations
-- Display: student name, course code, course name, enrollment status
-- Limit to first 20 results
-- Your query here:

-- 2. Find students who could potentially enroll in courses they're not currently taking
-- Display: student name, course code, course name
-- Your query here:

-- Bonus Exercise: Comprehensive Analysis
-- Create a detailed report showing:
-- Student ID, Student Name, Department, Courses Taken, Average Grade, Academic Standing
-- Only for active students, sorted by average grade (highest first)
-- Your query here:
