# Lesson 13: Stored Procedures and Functions

## 📚 Learning Objectives

By the end of this lesson, you will be able to:
- Create and execute stored procedures
- Define user-defined functions
- Use parameters in procedures and functions
- Handle errors and exceptions
- Understand security implications
- Optimize database operations with stored code

## 🎯 Prerequisites

- Completed Lessons 1-12
- Understanding of SQL statements and data manipulation
- Knowledge of views and indexes
- Basic understanding of programming concepts

## 📖 Table of Contents

1. [Introduction to Stored Procedures](#introduction-to-stored-procedures)
2. [Creating Stored Procedures](#creating-stored-procedures)
3. [Parameters and Variables](#parameters-and-variables)
4. [Control Structures](#control-structures)
5. [Error Handling](#error-handling)
6. [User-Defined Functions](#user-defined-functions)
7. [Security Considerations](#security-considerations)
8. [Best Practices](#best-practices)
9. [Common Pitfalls](#common-pitfalls)

---

## 1. Introduction to Stored Procedures

A **stored procedure** is a prepared SQL code that you can save and reuse. It's like a function in other programming languages - you can pass parameters and get return values.

### Benefits of Stored Procedures

- **Performance**: Pre-compiled and optimized
- **Security**: Centralized business logic
- **Maintainability**: Single point of code maintenance
- **Reusability**: Can be called from multiple applications
- **Network Efficiency**: Reduce network traffic

### When to Use Stored Procedures

- Complex business logic
- Data validation and constraints
- Batch operations
- Security-sensitive operations
- Performance-critical operations

---

## 2. Creating Stored Procedures

### Basic Stored Procedure

```sql
-- Simple procedure to get student information
DELIMITER //
CREATE PROCEDURE GetStudentInfo(IN student_id_param INT)
BEGIN
    SELECT 
        s.student_id,
        s.first_name,
        s.last_name,
        s.email,
        d.name AS department_name,
        s.gpa
    FROM students s
    JOIN departments d ON s.department_id = d.department_id
    WHERE s.student_id = student_id_param;
END //
DELIMITER ;

-- Call the procedure
CALL GetStudentInfo(1);
```

### Procedure with Multiple Parameters

```sql
-- Procedure to add a new student
DELIMITER //
CREATE PROCEDURE AddStudent(
    IN first_name_param VARCHAR(50),
    IN last_name_param VARCHAR(50),
    IN email_param VARCHAR(100),
    IN department_id_param INT,
    IN gpa_param DECIMAL(3,2)
)
BEGIN
    INSERT INTO students (
        first_name, 
        last_name, 
        email, 
        department_id, 
        gpa,
        status,
        enrollment_date
    ) VALUES (
        first_name_param,
        last_name_param,
        email_param,
        department_id_param,
        gpa_param,
        'Active',
        CURDATE()
    );
    
    SELECT LAST_INSERT_ID() AS new_student_id;
END //
DELIMITER ;

-- Call the procedure
CALL AddStudent('John', 'Doe', 'john.doe@email.com', 1, 3.75);
```

---

## 3. Parameters and Variables

### Parameter Types

```sql
-- Procedure with different parameter types
DELIMITER //
CREATE PROCEDURE UpdateStudentGPA(
    IN student_id_param INT,           -- Input parameter
    IN new_gpa_param DECIMAL(3,2),    -- Input parameter
    OUT success_param BOOLEAN,         -- Output parameter
    OUT message_param VARCHAR(255)     -- Output parameter
)
BEGIN
    DECLARE student_exists INT DEFAULT 0;
    
    -- Check if student exists
    SELECT COUNT(*) INTO student_exists
    FROM students
    WHERE student_id = student_id_param;
    
    IF student_exists > 0 THEN
        -- Update the GPA
        UPDATE students 
        SET gpa = new_gpa_param
        WHERE student_id = student_id_param;
        
        SET success_param = TRUE;
        SET message_param = 'GPA updated successfully';
    ELSE
        SET success_param = FALSE;
        SET message_param = 'Student not found';
    END IF;
END //
DELIMITER ;

-- Call with output parameters
SET @success = FALSE;
SET @message = '';
CALL UpdateStudentGPA(1, 3.85, @success, @message);
SELECT @success, @message;
```

### Local Variables

```sql
-- Procedure with local variables
DELIMITER //
CREATE PROCEDURE CalculateDepartmentStats(IN dept_id_param INT)
BEGIN
    DECLARE total_students INT DEFAULT 0;
    DECLARE avg_gpa DECIMAL(4,2) DEFAULT 0.00;
    DECLARE dept_name VARCHAR(100);
    
    -- Get department name
    SELECT name INTO dept_name
    FROM departments
    WHERE department_id = dept_id_param;
    
    -- Count students
    SELECT COUNT(*) INTO total_students
    FROM students
    WHERE department_id = dept_id_param
      AND gpa IS NOT NULL;
    
    -- Calculate average GPA
    IF total_students > 0 THEN
        SELECT AVG(gpa) INTO avg_gpa
        FROM students
        WHERE department_id = dept_id_param
          AND gpa IS NOT NULL;
    END IF;
    
    -- Return results
    SELECT 
        dept_name AS department_name,
        total_students,
        avg_gpa,
        CASE 
            WHEN avg_gpa >= 3.5 THEN 'Excellent'
            WHEN avg_gpa >= 3.0 THEN 'Good'
            WHEN avg_gpa >= 2.5 THEN 'Average'
            ELSE 'Below Average'
        END AS performance_rating;
END //
DELIMITER ;

-- Call the procedure
CALL CalculateDepartmentStats(1);
```

---

## 4. Control Structures

### IF-ELSE Statements

```sql
-- Procedure with conditional logic
DELIMITER //
CREATE PROCEDURE EnrollStudent(
    IN student_id_param INT,
    IN course_id_param INT,
    OUT result_param VARCHAR(255)
)
BEGIN
    DECLARE student_exists INT DEFAULT 0;
    DECLARE course_exists INT DEFAULT 0;
    DECLARE already_enrolled INT DEFAULT 0;
    DECLARE max_capacity INT DEFAULT 0;
    DECLARE current_enrollments INT DEFAULT 0;
    
    -- Check if student exists
    SELECT COUNT(*) INTO student_exists
    FROM students
    WHERE student_id = student_id_param AND status = 'Active';
    
    -- Check if course exists
    SELECT COUNT(*) INTO course_exists
    FROM courses
    WHERE course_id = course_id_param;
    
    -- Check if already enrolled
    SELECT COUNT(*) INTO already_enrolled
    FROM enrollments
    WHERE student_id = student_id_param AND course_id = course_id_param;
    
    -- Check course capacity
    SELECT capacity, 
           (SELECT COUNT(*) FROM enrollments WHERE course_id = course_id_param)
    INTO max_capacity, current_enrollments
    FROM courses
    WHERE course_id = course_id_param;
    
    -- Decision logic
    IF student_exists = 0 THEN
        SET result_param = 'Error: Student not found or inactive';
    ELSEIF course_exists = 0 THEN
        SET result_param = 'Error: Course not found';
    ELSEIF already_enrolled > 0 THEN
        SET result_param = 'Error: Student already enrolled in this course';
    ELSEIF current_enrollments >= max_capacity THEN
        SET result_param = 'Error: Course is at maximum capacity';
    ELSE
        -- Enroll the student
        INSERT INTO enrollments (student_id, course_id, enrollment_date)
        VALUES (student_id_param, course_id_param, CURDATE());
        SET result_param = 'Success: Student enrolled successfully';
    END IF;
END //
DELIMITER ;

-- Test the procedure
SET @result = '';
CALL EnrollStudent(1, 1, @result);
SELECT @result;
```

### Loops

```sql
-- Procedure with loop to generate sample data
DELIMITER //
CREATE PROCEDURE GenerateSampleGrades(IN course_id_param INT)
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE student_id_var INT;
    DECLARE grade_var INT;
    DECLARE enrollment_cursor CURSOR FOR 
        SELECT enrollment_id, student_id 
        FROM enrollments 
        WHERE course_id = course_id_param AND grade IS NULL;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    OPEN enrollment_cursor;
    
    read_loop: LOOP
        FETCH enrollment_cursor INTO enrollment_id_var, student_id_var;
        IF done THEN
            LEAVE read_loop;
        END IF;
        
        -- Generate random grade between 60 and 100
        SET grade_var = FLOOR(RAND() * 41) + 60;
        
        -- Update the enrollment with the grade
        UPDATE enrollments 
        SET grade = grade_var
        WHERE enrollment_id = enrollment_id_var;
        
    END LOOP;
    
    CLOSE enrollment_cursor;
    
    SELECT CONCAT('Generated grades for course ID: ', course_id_param) AS result;
END //
DELIMITER ;

-- Call the procedure
CALL GenerateSampleGrades(1);
```

---

## 5. Error Handling

### Basic Error Handling

```sql
-- Procedure with error handling
DELIMITER //
CREATE PROCEDURE SafeUpdateStudent(
    IN student_id_param INT,
    IN new_gpa_param DECIMAL(3,2)
)
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
        RESIGNAL;
    END;
    
    START TRANSACTION;
    
    -- Validate GPA range
    IF new_gpa_param < 0 OR new_gpa_param > 4.0 THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'GPA must be between 0.0 and 4.0';
    END IF;
    
    -- Update student GPA
    UPDATE students 
    SET gpa = new_gpa_param
    WHERE student_id = student_id_param;
    
    IF ROW_COUNT() = 0 THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Student not found';
    END IF;
    
    COMMIT;
    
    SELECT 'Student GPA updated successfully' AS result;
END //
DELIMITER ;

-- Test with valid data
CALL SafeUpdateStudent(1, 3.75);

-- Test with invalid data
CALL SafeUpdateStudent(1, 5.0);
```

### Advanced Error Handling

```sql
-- Procedure with comprehensive error handling
DELIMITER //
CREATE PROCEDURE ProcessStudentEnrollment(
    IN student_id_param INT,
    IN course_id_param INT
)
BEGIN
    DECLARE error_occurred BOOLEAN DEFAULT FALSE;
    DECLARE error_message VARCHAR(255) DEFAULT '';
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        GET DIAGNOSTICS CONDITION 1
            error_message = MESSAGE_TEXT;
        ROLLBACK;
        SELECT CONCAT('Error: ', error_message) AS result;
    END;
    
    START TRANSACTION;
    
    -- Validation checks
    IF NOT EXISTS (SELECT 1 FROM students WHERE student_id = student_id_param) THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Invalid student ID';
    END IF;
    
    IF NOT EXISTS (SELECT 1 FROM courses WHERE course_id = course_id_param) THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Invalid course ID';
    END IF;
    
    IF EXISTS (SELECT 1 FROM enrollments 
               WHERE student_id = student_id_param AND course_id = course_id_param) THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Student already enrolled in this course';
    END IF;
    
    -- Perform enrollment
    INSERT INTO enrollments (student_id, course_id, enrollment_date)
    VALUES (student_id_param, course_id_param, CURDATE());
    
    COMMIT;
    SELECT 'Enrollment processed successfully' AS result;
END //
DELIMITER ;
```

---

## 6. User-Defined Functions

### Scalar Functions

```sql
-- Function to calculate letter grade
DELIMITER //
CREATE FUNCTION GetLetterGrade(numeric_grade INT) 
RETURNS VARCHAR(2)
READS SQL DATA
DETERMINISTIC
BEGIN
    DECLARE letter_grade VARCHAR(2);
    
    IF numeric_grade >= 90 THEN
        SET letter_grade = 'A';
    ELSEIF numeric_grade >= 80 THEN
        SET letter_grade = 'B';
    ELSEIF numeric_grade >= 70 THEN
        SET letter_grade = 'C';
    ELSEIF numeric_grade >= 60 THEN
        SET letter_grade = 'D';
    ELSE
        SET letter_grade = 'F';
    END IF;
    
    RETURN letter_grade;
END //
DELIMITER ;

-- Use the function
SELECT 
    e.enrollment_id,
    s.first_name,
    s.last_name,
    c.course_code,
    e.grade,
    GetLetterGrade(e.grade) AS letter_grade
FROM enrollments e
JOIN students s ON e.student_id = s.student_id
JOIN courses c ON e.course_id = c.course_id
WHERE e.grade IS NOT NULL;
```

### Table-Valued Functions (MySQL doesn't support table-valued functions, but we can create procedures that return result sets)

```sql
-- Procedure that acts like a table-valued function
DELIMITER //
CREATE PROCEDURE GetTopStudents(IN limit_param INT)
BEGIN
    SELECT 
        s.student_id,
        s.first_name,
        s.last_name,
        d.name AS department_name,
        s.gpa,
        COUNT(e.enrollment_id) AS total_courses,
        AVG(e.grade) AS average_grade
    FROM students s
    JOIN departments d ON s.department_id = d.department_id
    LEFT JOIN enrollments e ON s.student_id = e.student_id
    WHERE s.status = 'Active' 
      AND s.gpa IS NOT NULL
      AND e.grade IS NOT NULL
    GROUP BY s.student_id, s.first_name, s.last_name, d.name, s.gpa
    ORDER BY s.gpa DESC, average_grade DESC
    LIMIT limit_param;
END //
DELIMITER ;

-- Call the procedure
CALL GetTopStudents(10);
```

---

## 7. Security Considerations

### SQL Injection Prevention

```sql
-- Secure procedure with parameterized queries
DELIMITER //
CREATE PROCEDURE GetStudentByEmail(IN email_param VARCHAR(100))
BEGIN
    -- This is automatically protected against SQL injection
    -- because we're using parameters
    SELECT 
        student_id,
        first_name,
        last_name,
        email,
        status
    FROM students
    WHERE email = email_param;
END //
DELIMITER ;

-- ❌ DANGEROUS: Don't do this
-- CREATE PROCEDURE BadProcedure(IN query_param TEXT)
-- BEGIN
--     SET @sql = CONCAT('SELECT * FROM students WHERE ', query_param);
--     PREPARE stmt FROM @sql;
--     EXECUTE stmt;
--     DEALLOCATE PREPARE stmt;
-- END;
```

### Privilege Management

```sql
-- Grant execute privilege to specific user
GRANT EXECUTE ON PROCEDURE school_db.GetStudentInfo TO 'student_user'@'localhost';

-- Create procedure with definer rights (runs with creator's privileges)
DELIMITER //
CREATE DEFINER='admin'@'localhost' PROCEDURE AdminOnlyProcedure()
SQL SECURITY DEFINER
BEGIN
    -- This procedure runs with admin privileges
    SELECT * FROM sensitive_table;
END //
DELIMITER ;

-- Create procedure with invoker rights (runs with caller's privileges)
DELIMITER //
CREATE PROCEDURE UserSpecificProcedure()
SQL SECURITY INVOKER
BEGIN
    -- This procedure runs with caller's privileges
    SELECT * FROM user_accessible_table;
END //
DELIMITER ;
```

---

## 8. Best Practices

### Naming Conventions

```sql
-- Use descriptive names
CREATE PROCEDURE sp_GetStudentAcademicHistory(IN student_id INT);
CREATE FUNCTION fn_CalculateGPA(grade1 DECIMAL, grade2 DECIMAL) RETURNS DECIMAL;

-- Use prefixes for clarity
-- sp_ = stored procedure
-- fn_ = function
-- tr_ = trigger (next lesson)
```

### Documentation

```sql
-- Well-documented procedure
DELIMITER //
-- Procedure: sp_EnrollStudentInCourse
-- Purpose: Enrolls a student in a course with validation
-- Parameters:
--   - student_id_param: ID of the student to enroll
--   - course_id_param: ID of the course to enroll in
-- Returns: Success/error message
-- Author: Database Team
-- Created: 2024-01-15
-- Modified: 2024-01-15
CREATE PROCEDURE sp_EnrollStudentInCourse(
    IN student_id_param INT,
    IN course_id_param INT
)
BEGIN
    -- Implementation here
END //
DELIMITER ;
```

### Performance Optimization

```sql
-- Efficient procedure with proper indexing
DELIMITER //
CREATE PROCEDURE GetStudentPerformance(IN student_id_param INT)
BEGIN
    -- Use indexed columns in WHERE clauses
    SELECT 
        s.first_name,
        s.last_name,
        c.course_code,
        e.grade,
        e.semester
    FROM students s
    JOIN enrollments e ON s.student_id = e.student_id  -- Indexed
    JOIN courses c ON e.course_id = c.course_id        -- Indexed
    WHERE s.student_id = student_id_param              -- Indexed
    ORDER BY e.semester DESC, c.course_code;           -- Indexed columns
END //
DELIMITER ;
```

---

## 9. Common Pitfalls

### Pitfall 1: Missing DELIMITER Changes

```sql
-- ❌ ERROR: Missing delimiter change
CREATE PROCEDURE BadProcedure()
BEGIN
    SELECT * FROM students;
END;  -- This will cause syntax error

-- ✅ CORRECT: Use delimiter changes
DELIMITER //
CREATE PROCEDURE GoodProcedure()
BEGIN
    SELECT * FROM students;
END //
DELIMITER ;
```

### Pitfall 2: Not Handling NULL Values

```sql
-- ❌ POTENTIAL ISSUE: Not handling NULL values
CREATE FUNCTION BadFunction(grade INT) 
RETURNS VARCHAR(10)
BEGIN
    IF grade >= 90 THEN
        RETURN 'A';
    -- Missing NULL check
END;

-- ✅ BETTER: Handle NULL values
CREATE FUNCTION GoodFunction(grade INT) 
RETURNS VARCHAR(10)
BEGIN
    IF grade IS NULL THEN
        RETURN 'N/A';
    ELSEIF grade >= 90 THEN
        RETURN 'A';
    END IF;
END;
```

### Pitfall 3: Infinite Loops

```sql
-- ❌ DANGEROUS: Potential infinite loop
DELIMITER //
CREATE PROCEDURE BadLoop()
BEGIN
    DECLARE counter INT DEFAULT 0;
    
    WHILE counter < 10 DO
        -- Missing counter increment - infinite loop!
        SELECT counter;
    END WHILE;
END //
DELIMITER ;

-- ✅ CORRECT: Proper loop control
DELIMITER //
CREATE PROCEDURE GoodLoop()
BEGIN
    DECLARE counter INT DEFAULT 0;
    
    WHILE counter < 10 DO
        SELECT counter;
        SET counter = counter + 1;  -- Increment counter
    END WHILE;
END //
DELIMITER ;
```

---

## 🎯 Summary

Stored procedures and functions are powerful tools for database programming:

### Stored Procedures
- **Reusable code blocks** for complex operations
- **Parameters** for input and output
- **Control structures** for logic flow
- **Error handling** for robust operations
- **Security** through centralized business logic

### User-Defined Functions
- **Scalar functions** for calculations and transformations
- **Deterministic** and **non-deterministic** options
- **Performance** benefits for repeated calculations
- **Reusability** across queries and procedures

### Key Takeaways
1. **Use procedures** for complex business logic and data manipulation
2. **Use functions** for calculations and data transformations
3. **Always handle errors** and validate input parameters
4. **Follow security best practices** to prevent SQL injection
5. **Document your code** for maintainability
6. **Test thoroughly** before deploying to production

## 🔄 Next Steps

- Practice creating stored procedures for your common operations
- Experiment with user-defined functions
- Move on to Lesson 14: Triggers
- Consider security implications in your database design

## 📚 Additional Resources

- MySQL Documentation: [Stored Procedures](https://dev.mysql.com/doc/refman/8.0/en/stored-programs-defining.html)
- MySQL Documentation: [Functions](https://dev.mysql.com/doc/refman/8.0/en/create-procedure.html)
- MySQL Documentation: [Error Handling](https://dev.mysql.com/doc/refman/8.0/en/declare-handler.html)
