-- ===================================================================
-- Sample Data for School Management System
-- ===================================================================
-- This file contains comprehensive sample data for all tables in the 
-- school management database. It demonstrates:
-- 1. Realistic academic department data
-- 2. Diverse student profiles with various academic performance levels
-- 3. Comprehensive course catalog across multiple departments
-- 4. Realistic enrollment patterns and grade distributions
-- 5. Different student statuses (active, graduated, inactive)
-- ===================================================================

-- Switch to the learning database
-- Note: This should be 'learning_db' not 'school_management' to match our setup
USE learning_db;

-- ===================================================================
-- SECTION 1: INSERT SAMPLE DEPARTMENTS
-- ===================================================================
-- Create realistic academic departments with varying budgets and establishment dates
-- Demonstrates: INSERT with multiple values, realistic data patterns
INSERT INTO departments (dept_name, budget, established_date) VALUES
-- STEM departments with higher budgets (more equipment/lab costs)
('Computer Science', 500000.00, '1990-09-01'),    -- Modern department, high budget for tech
('Mathematics', 300000.00, '1985-09-01'),         -- Established department, moderate budget
('Physics', 400000.00, '1988-09-01'),             -- Lab-intensive, higher budget
('Chemistry', 350000.00, '1987-09-01'),           -- Lab equipment costs
('Biology', 450000.00, '1989-09-01'),             -- Lab and field work costs

-- Liberal Arts departments with lower budgets
('English Literature', 250000.00, '1980-09-01'), -- Traditional department, lower costs
('History', 200000.00, '1975-09-01'),            -- Longest established, minimal equipment
('Psychology', 320000.00, '1995-09-01');         -- Newer department, some lab needs

-- ===================================================================
-- SECTION 2: INSERT SAMPLE STUDENTS
-- ===================================================================
-- Create diverse student profiles with realistic academic performance data
-- Demonstrates: Various GPA ranges, different enrollment years, mixed statuses
INSERT INTO students (first_name, last_name, email, phone, enrollment_date, gpa, status) VALUES
-- High-performing students (GPA 3.7+)
('John', 'Doe', 'john.doe@university.edu', '555-0101', '2023-09-01', 3.75, 'active'),      -- Strong student
('Jane', 'Smith', 'jane.smith@university.edu', '555-0102', '2023-09-01', 3.85, 'active'),  -- Excellent student
('Alice', 'Brown', 'alice.brown@university.edu', '555-0104', '2023-09-01', 3.95, 'active'), -- Top performer
('Grace', 'Martinez', 'grace.martinez@university.edu', '555-0109', '2023-09-01', 3.85, 'active'), -- High achiever
('Noah', 'Martin', 'noah.martin@university.edu', '555-0116', '2023-09-01', 3.85, 'active'), -- Strong performer

-- Average-performing students (GPA 3.0-3.7)
('Bob', 'Johnson', 'bob.johnson@university.edu', '555-0103', '2023-09-01', 3.45, 'active'), -- Solid student
('Eve', 'Miller', 'eve.miller@university.edu', '555-0107', '2023-09-01', 3.55, 'active'),   -- Good student
('Henry', 'Anderson', 'henry.anderson@university.edu', '555-0110', '2023-09-01', 3.35, 'active'), -- Average student
('Ivy', 'Taylor', 'ivy.taylor@university.edu', '555-0111', '2023-09-01', 3.75, 'active'),   -- Good student
('Jack', 'Thomas', 'jack.thomas@university.edu', '555-0112', '2023-09-01', 3.45, 'active'),  -- Solid student
('Kate', 'Jackson', 'kate.jackson@university.edu', '555-0113', '2023-09-01', 3.65, 'active'), -- Good student
('Maya', 'Harris', 'maya.harris@university.edu', '555-0115', '2023-09-01', 3.55, 'active'), -- Good student
('Olivia', 'Thompson', 'olivia.thompson@university.edu', '555-0117', '2023-09-01', 3.45, 'active'), -- Solid student
('Quinn', 'Martinez', 'quinn.martinez@university.edu', '555-0119', '2023-09-01', 3.75, 'active'), -- Good student
('Rachel', 'Robinson', 'rachel.robinson@university.edu', '555-0120', '2023-09-01', 3.65, 'active'), -- Good student

-- Lower-performing students (GPA < 3.5)
('Charlie', 'Wilson', 'charlie.wilson@university.edu', '555-0105', '2023-09-01', 3.25, 'active'), -- Struggling student
('Frank', 'Garcia', 'frank.garcia@university.edu', '555-0108', '2023-09-01', 3.15, 'active'),     -- Needs improvement
('Leo', 'White', 'leo.white@university.edu', '555-0114', '2023-09-01', 3.25, 'active'),          -- Struggling student
('Paul', 'Garcia', 'paul.garcia@university.edu', '555-0118', '2023-09-01', 3.15, 'active'),       -- Needs improvement

-- Graduated student (different enrollment year)
('Diana', 'Davis', 'diana.davis@university.edu', '555-0106', '2022-09-01', 3.65, 'graduated'); -- Completed student

-- Insert sample courses
INSERT INTO courses (course_code, course_name, credits, dept_id, description) VALUES
-- Computer Science courses
('CS101', 'Introduction to Programming', 3, 1, 'Basic programming concepts using Python and Java'),
('CS102', 'Computer Science Fundamentals', 3, 1, 'Introduction to computer science concepts'),
('CS201', 'Data Structures', 3, 1, 'Fundamental data structures and algorithms'),
('CS202', 'Object-Oriented Programming', 3, 1, 'OOP concepts and design patterns'),
('CS301', 'Database Systems', 3, 1, 'Relational database design and SQL'),
('CS302', 'Software Engineering', 3, 1, 'Software development methodologies'),
('CS401', 'Advanced Algorithms', 3, 1, 'Complex algorithms and complexity analysis'),
('CS402', 'Machine Learning', 3, 1, 'Introduction to machine learning concepts'),

-- Mathematics courses
('MATH101', 'Calculus I', 4, 2, 'Differential and integral calculus'),
('MATH102', 'Calculus II', 4, 2, 'Advanced calculus topics'),
('MATH201', 'Linear Algebra', 3, 2, 'Vector spaces and linear transformations'),
('MATH202', 'Discrete Mathematics', 3, 2, 'Discrete structures and logic'),
('MATH301', 'Probability and Statistics', 3, 2, 'Statistical methods and probability theory'),
('MATH302', 'Differential Equations', 3, 2, 'Ordinary and partial differential equations'),

-- Physics courses
('PHYS101', 'General Physics I', 4, 3, 'Mechanics and thermodynamics'),
('PHYS102', 'General Physics II', 4, 3, 'Electricity, magnetism, and waves'),
('PHYS201', 'Modern Physics', 3, 3, 'Quantum mechanics and relativity'),
('PHYS202', 'Thermodynamics', 3, 3, 'Heat, temperature, and energy'),

-- Chemistry courses
('CHEM101', 'General Chemistry I', 4, 4, 'Atomic structure and chemical bonding'),
('CHEM102', 'General Chemistry II', 4, 4, 'Chemical reactions and equilibrium'),
('CHEM201', 'Organic Chemistry I', 3, 4, 'Carbon compounds and reactions'),
('CHEM202', 'Physical Chemistry', 3, 4, 'Chemical thermodynamics and kinetics'),

-- Biology courses
('BIO101', 'General Biology I', 4, 5, 'Cell biology and genetics'),
('BIO102', 'General Biology II', 4, 5, 'Evolution and ecology'),
('BIO201', 'Molecular Biology', 3, 5, 'DNA, RNA, and protein synthesis'),
('BIO202', 'Genetics', 3, 5, 'Heredity and genetic variation'),

-- English Literature courses
('ENG101', 'Introduction to Literature', 3, 6, 'Survey of major literary works'),
('ENG102', 'Creative Writing', 3, 6, 'Fiction and poetry writing'),
('ENG201', 'Shakespeare', 3, 6, 'Works of William Shakespeare'),
('ENG202', 'Modern Literature', 3, 6, 'Contemporary literary movements'),

-- History courses
('HIST101', 'World History I', 3, 7, 'Ancient civilizations to medieval period'),
('HIST102', 'World History II', 3, 7, 'Renaissance to modern era'),
('HIST201', 'American History', 3, 7, 'United States history'),
('HIST202', 'European History', 3, 7, 'European historical development'),

-- Psychology courses
('PSYC101', 'Introduction to Psychology', 3, 8, 'Basic psychological concepts'),
('PSYC102', 'Developmental Psychology', 3, 8, 'Human development across lifespan'),
('PSYC201', 'Abnormal Psychology', 3, 8, 'Psychological disorders and treatment'),
('PSYC202', 'Social Psychology', 3, 8, 'Social behavior and group dynamics');

-- Insert sample enrollments
INSERT INTO enrollments (student_id, course_id, enrollment_date, grade, status) VALUES
-- John Doe's enrollments
(1, 1, '2023-09-01', 85.5, 'completed'),
(1, 2, '2023-09-01', 88.0, 'completed'),
(1, 9, '2023-09-01', 82.5, 'completed'),
(1, 10, '2024-01-15', NULL, 'enrolled'),
(1, 11, '2024-01-15', NULL, 'enrolled'),

-- Jane Smith's enrollments
(2, 1, '2023-09-01', 92.0, 'completed'),
(2, 3, '2023-09-01', 89.5, 'completed'),
(2, 5, '2023-09-01', 94.0, 'completed'),
(2, 6, '2024-01-15', NULL, 'enrolled'),
(2, 7, '2024-01-15', NULL, 'enrolled'),

-- Bob Johnson's enrollments
(3, 9, '2023-09-01', 78.5, 'completed'),
(3, 10, '2023-09-01', 81.0, 'completed'),
(3, 11, '2023-09-01', 76.0, 'completed'),
(3, 12, '2024-01-15', NULL, 'enrolled'),
(3, 13, '2024-01-15', NULL, 'enrolled'),

-- Alice Brown's enrollments
(4, 15, '2023-09-01', 88.0, 'completed'),
(4, 16, '2023-09-01', 91.5, 'completed'),
(4, 17, '2023-09-01', 86.0, 'completed'),
(4, 18, '2024-01-15', NULL, 'enrolled'),
(4, 19, '2024-01-15', NULL, 'enrolled'),

-- Charlie Wilson's enrollments
(5, 21, '2023-09-01', 82.5, 'completed'),
(5, 22, '2023-09-01', 79.0, 'completed'),
(5, 23, '2023-09-01', 85.5, 'completed'),
(5, 24, '2024-01-15', NULL, 'enrolled'),
(5, 25, '2024-01-15', NULL, 'enrolled'),

-- Diana Davis's enrollments (graduated student)
(6, 1, '2022-09-01', 87.0, 'completed'),
(6, 2, '2022-09-01', 89.5, 'completed'),
(6, 3, '2022-09-01', 91.0, 'completed'),
(6, 5, '2022-09-01', 88.5, 'completed'),
(6, 9, '2022-09-01', 85.0, 'completed'),
(6, 10, '2022-09-01', 87.5, 'completed'),

-- Eve Miller's enrollments
(7, 27, '2023-09-01', 83.0, 'completed'),
(7, 28, '2023-09-01', 86.5, 'completed'),
(7, 29, '2023-09-01', 81.5, 'completed'),
(7, 30, '2024-01-15', NULL, 'enrolled'),
(7, 31, '2024-01-15', NULL, 'enrolled'),

-- Frank Garcia's enrollments
(8, 33, '2023-09-01', 77.0, 'completed'),
(8, 34, '2023-09-01', 79.5, 'completed'),
(8, 35, '2023-09-01', 75.0, 'completed'),
(8, 36, '2024-01-15', NULL, 'enrolled'),
(8, 37, '2024-01-15', NULL, 'enrolled'),

-- Grace Martinez's enrollments
(9, 1, '2023-09-01', 90.0, 'completed'),
(9, 3, '2023-09-01', 92.5, 'completed'),
(9, 5, '2023-09-01', 89.0, 'completed'),
(9, 7, '2024-01-15', NULL, 'enrolled'),
(9, 8, '2024-01-15', NULL, 'enrolled'),

-- Henry Anderson's enrollments
(10, 9, '2023-09-01', 80.0, 'completed'),
(10, 11, '2023-09-01', 78.5, 'completed'),
(10, 13, '2023-09-01', 82.0, 'completed'),
(10, 14, '2024-01-15', NULL, 'enrolled'),
(10, 15, '2024-01-15', NULL, 'enrolled'),

-- Additional enrollments for more data
(11, 1, '2023-09-01', 85.0, 'completed'),
(11, 2, '2023-09-01', 87.5, 'completed'),
(11, 3, '2024-01-15', NULL, 'enrolled'),

(12, 9, '2023-09-01', 83.5, 'completed'),
(12, 10, '2023-09-01', 81.0, 'completed'),
(12, 11, '2024-01-15', NULL, 'enrolled'),

(13, 15, '2023-09-01', 88.5, 'completed'),
(13, 16, '2023-09-01', 86.0, 'completed'),
(13, 17, '2024-01-15', NULL, 'enrolled'),

(14, 21, '2023-09-01', 79.0, 'completed'),
(14, 22, '2023-09-01', 82.5, 'completed'),
(14, 23, '2024-01-15', NULL, 'enrolled'),

(15, 27, '2023-09-01', 84.0, 'completed'),
(15, 28, '2023-09-01', 87.0, 'completed'),
(15, 29, '2024-01-15', NULL, 'enrolled'),

(16, 33, '2023-09-01', 91.0, 'completed'),
(16, 34, '2023-09-01', 89.5, 'completed'),
(16, 35, '2024-01-15', NULL, 'enrolled'),

(17, 1, '2023-09-01', 76.5, 'completed'),
(17, 2, '2023-09-01', 78.0, 'completed'),
(17, 3, '2024-01-15', NULL, 'enrolled'),

(18, 9, '2023-09-01', 74.0, 'completed'),
(18, 10, '2023-09-01', 76.5, 'completed'),
(18, 11, '2024-01-15', NULL, 'enrolled'),

(19, 15, '2023-09-01', 88.0, 'completed'),
(19, 16, '2023-09-01', 90.5, 'completed'),
(19, 17, '2024-01-15', NULL, 'enrolled'),

(20, 21, '2023-09-01', 85.5, 'completed'),
(20, 22, '2023-09-01', 87.0, 'completed'),
(20, 23, '2024-01-15', NULL, 'enrolled');

-- Insert some additional sample data for testing
-- Add more students with different statuses
INSERT INTO students (first_name, last_name, email, phone, enrollment_date, gpa, status) VALUES
('Sarah', 'Williams', 'sarah.williams@university.edu', '555-0121', '2023-09-01', 2.85, 'inactive'),
('Tom', 'Jones', 'tom.jones@university.edu', '555-0122', '2023-09-01', 3.95, 'active'),
('Lisa', 'Garcia', 'lisa.garcia@university.edu', '555-0123', '2023-09-01', 3.05, 'active'),
('Mike', 'Brown', 'mike.brown@university.edu', '555-0124', '2023-09-01', 2.95, 'inactive'),
('Emma', 'Davis', 'emma.davis@university.edu', '555-0125', '2023-09-01', 3.75, 'active');

-- Add some enrollments for the new students
INSERT INTO enrollments (student_id, course_id, enrollment_date, grade, status) VALUES
(21, 1, '2023-09-01', 65.0, 'dropped'),
(21, 2, '2023-09-01', 70.0, 'completed'),
(21, 9, '2023-09-01', 68.0, 'completed'),

(22, 1, '2023-09-01', 95.0, 'completed'),
(22, 2, '2023-09-01', 97.0, 'completed'),
(22, 3, '2023-09-01', 96.0, 'completed'),
(22, 5, '2024-01-15', NULL, 'enrolled'),

(23, 9, '2023-09-01', 72.0, 'completed'),
(23, 10, '2023-09-01', 75.0, 'completed'),
(23, 11, '2024-01-15', NULL, 'enrolled'),

(24, 1, '2023-09-01', 60.0, 'dropped'),
(24, 2, '2023-09-01', 65.0, 'dropped'),
(24, 9, '2023-09-01', 70.0, 'completed'),

(25, 1, '2023-09-01', 88.0, 'completed'),
(25, 2, '2023-09-01', 90.0, 'completed'),
(25, 3, '2023-09-01', 87.0, 'completed'),
(25, 5, '2024-01-15', NULL, 'enrolled');

-- Display summary of inserted data
SELECT 'Departments' AS table_name, COUNT(*) AS record_count FROM departments
UNION ALL
SELECT 'Students', COUNT(*) FROM students
UNION ALL
SELECT 'Courses', COUNT(*) FROM courses
UNION ALL
SELECT 'Enrollments', COUNT(*) FROM enrollments;
