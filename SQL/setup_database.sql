-- ===================================================================
-- Database Setup Script for Learning SQL Course
-- ===================================================================
-- This script creates the complete database structure for the school 
-- management system. It demonstrates:
-- 1. Database creation with proper character set
-- 2. Table creation with various data types and constraints
-- 3. Foreign key relationships and referential integrity
-- 4. Index creation for performance optimization
-- 5. User creation and privilege management
-- ===================================================================

-- ===================================================================
-- STEP 1: CREATE THE DATABASE
-- ===================================================================
-- Create the main database for our learning course
-- CHARACTER SET utf8mb4: Supports full Unicode including emojis
-- COLLATE utf8mb4_unicode_ci: Case-insensitive Unicode collation
CREATE DATABASE IF NOT EXISTS learning_db 
CHARACTER SET utf8mb4 
COLLATE utf8mb4_unicode_ci;

-- Switch to the newly created database
-- This ensures all subsequent commands operate on this database
USE learning_db;

-- ===================================================================
-- STEP 2: CREATE THE DEPARTMENTS TABLE
-- ===================================================================
-- This table stores information about academic departments
-- Demonstrates: Primary key, UNIQUE constraint, DEFAULT values, TIMESTAMP
CREATE TABLE IF NOT EXISTS departments (
    -- Primary key: Auto-incrementing integer for unique department ID
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    
    -- Department name: Required, unique across all departments
    dept_name VARCHAR(100) NOT NULL UNIQUE,
    
    -- Budget: Decimal with 12 total digits, 2 after decimal point
    -- DEFAULT 0.00: If no budget specified, defaults to zero
    budget DECIMAL(12,2) DEFAULT 0.00,
    
    -- When the department was established (optional)
    established_date DATE,
    
    -- Automatic timestamp when record is created
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ===================================================================
-- STEP 3: CREATE THE STUDENTS TABLE
-- ===================================================================
-- This table stores student information
-- Demonstrates: CHECK constraints, ENUM, automatic timestamps, ON UPDATE
CREATE TABLE IF NOT EXISTS students (
    -- Primary key: Auto-incrementing student ID
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    
    -- Student's first and last names (required fields)
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    
    -- Email: Must be unique and not null (required for communication)
    email VARCHAR(100) UNIQUE NOT NULL,
    
    -- Phone number (optional - can be NULL)
    phone VARCHAR(20),
    
    -- Enrollment date: Defaults to current date if not specified
    enrollment_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    
    -- GPA: Decimal with 3 total digits, 2 after decimal (0.00 to 4.00)
    -- CHECK constraint ensures GPA is within valid range
    gpa DECIMAL(3,2) CHECK (gpa >= 0.0 AND gpa <= 4.0),
    
    -- Student status: Only allows specific values
    -- DEFAULT 'active': New students are active by default
    status ENUM('active', 'inactive', 'graduated') DEFAULT 'active',
    
    -- Automatic timestamp when record is created
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    
    -- Automatic timestamp that updates whenever record is modified
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- ===================================================================
-- STEP 4: CREATE THE COURSES TABLE
-- ===================================================================
-- This table stores course information
-- Demonstrates: Foreign key relationships, TEXT data type, ON DELETE SET NULL
CREATE TABLE IF NOT EXISTS courses (
    -- Primary key: Auto-incrementing course ID
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    
    -- Course code: Short identifier (e.g., "CS101"), must be unique
    course_code VARCHAR(10) NOT NULL UNIQUE,
    
    -- Full course name
    course_name VARCHAR(100) NOT NULL,
    
    -- Number of credits: Must be positive integer
    credits INT NOT NULL CHECK (credits > 0),
    
    -- Foreign key: References departments table
    -- Can be NULL if department is deleted (ON DELETE SET NULL)
    dept_id INT,
    
    -- Course description: Large text field for detailed information
    description TEXT,
    
    -- Automatic timestamp when record is created
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    
    -- Foreign key constraint: Links to departments table
    -- ON DELETE SET NULL: If department is deleted, set dept_id to NULL
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id) ON DELETE SET NULL
);

-- ===================================================================
-- STEP 5: CREATE THE ENROLLMENTS TABLE
-- ===================================================================
-- This table stores student-course enrollment relationships
-- Demonstrates: Composite unique key, CASCADE delete, multiple foreign keys
CREATE TABLE IF NOT EXISTS enrollments (
    -- Primary key: Auto-incrementing enrollment ID
    enrollment_id INT PRIMARY KEY AUTO_INCREMENT,
    
    -- Foreign key: References students table
    student_id INT NOT NULL,
    
    -- Foreign key: References courses table
    course_id INT NOT NULL,
    
    -- When the student enrolled: Defaults to current date
    enrollment_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    
    -- Grade: Decimal with 5 total digits, 2 after decimal (0.00 to 100.00)
    -- CHECK constraint ensures grade is within valid range
    grade DECIMAL(5,2) CHECK (grade >= 0.0 AND grade <= 100.0),
    
    -- Enrollment status: Only allows specific values
    status ENUM('enrolled', 'completed', 'dropped') DEFAULT 'enrolled',
    
    -- Automatic timestamp when record is created
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    
    -- Foreign key constraints with CASCADE delete
    -- If student is deleted, delete all their enrollments
    FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
    
    -- If course is deleted, delete all enrollments for that course
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    
    -- Composite unique constraint: Prevents duplicate enrollments
    -- A student can only enroll in the same course once
    UNIQUE KEY unique_enrollment (student_id, course_id)
);

-- ===================================================================
-- STEP 6: CREATE INDEXES FOR PERFORMANCE OPTIMIZATION
-- ===================================================================
-- Indexes speed up queries by creating sorted references to data
-- Create indexes on frequently queried columns

-- Index on student status (for filtering active/inactive students)
CREATE INDEX idx_students_status ON students(status);

-- Index on GPA (for sorting and filtering by academic performance)
CREATE INDEX idx_students_gpa ON students(gpa);

-- Index on enrollment date (for date range queries)
CREATE INDEX idx_students_enrollment_date ON students(enrollment_date);

-- Index on department ID in courses (for JOIN operations)
CREATE INDEX idx_courses_dept_id ON courses(dept_id);

-- Index on student ID in enrollments (for finding student's courses)
CREATE INDEX idx_enrollments_student_id ON enrollments(student_id);

-- Index on course ID in enrollments (for finding course enrollments)
CREATE INDEX idx_enrollments_course_id ON enrollments(course_id);

-- Index on enrollment status (for filtering by completion status)
CREATE INDEX idx_enrollments_status ON enrollments(status);

-- Index on grades (for sorting and filtering by performance)
CREATE INDEX idx_enrollments_grade ON enrollments(grade);

-- ===================================================================
-- STEP 7: CREATE DATABASE USER AND SET PERMISSIONS
-- ===================================================================
-- Create a dedicated user for the course with appropriate permissions

-- Create user 'student' with password 'password123'
-- IF NOT EXISTS: Only create if user doesn't already exist
CREATE USER IF NOT EXISTS 'student'@'localhost' IDENTIFIED BY 'password123';

-- Grant all privileges on the learning_db database to the student user
-- This allows the user to perform all operations (SELECT, INSERT, UPDATE, DELETE, etc.)
GRANT ALL PRIVILEGES ON learning_db.* TO 'student'@'localhost';

-- Apply the privilege changes immediately
FLUSH PRIVILEGES;

-- ===================================================================
-- STEP 8: VERIFICATION AND SUCCESS MESSAGE
-- ===================================================================
-- Display confirmation messages to verify successful setup

-- Show success message
SELECT 'Database setup completed successfully!' AS message;

-- Show information about what was created
SELECT 'Tables created:' AS info;

-- Display all tables in the database
SHOW TABLES;
