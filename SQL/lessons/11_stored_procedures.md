# Lesson 11: Stored Procedures and Functions

## Learning Objectives
- Understand what stored procedures and functions are
- Learn how to create and use stored procedures
- Practice creating user-defined functions
- Understand the benefits and use cases of stored procedures

## What are Stored Procedures?

Stored procedures are precompiled SQL statements stored in the database that can be executed with a simple call. They offer several advantages:

- **Performance**: Precompiled and optimized
- **Security**: Can control access to data
- **Reusability**: Can be called from multiple applications
- **Maintainability**: Centralized business logic

## Creating Stored Procedures

### Basic Stored Procedure

```sql
-- Create a simple stored procedure
DELIMITER //
CREATE PROCEDURE GetActiveStudents()
BEGIN
    SELECT 
        student_id,
        first_name,
        last_name,
        email,
        gpa
    FROM students 
    WHERE status = 'active'
    ORDER BY gpa DESC;
END //
DELIMITER ;

-- Call the stored procedure
CALL GetActiveStudents();
```

### Stored Procedure with Parameters

```sql
-- Create procedure with input parameters
DELIMITER //
CREATE PROCEDURE GetStudentsByGPA(
    IN min_gpa DECIMAL(3,2),
    IN max_gpa DECIMAL(3,2)
)
BEGIN
    SELECT 
        student_id,
        first_name,
        last_name,
        gpa,
        status
    FROM students 
    WHERE gpa BETWEEN min_gpa AND max_gpa
    ORDER BY gpa DESC;
END //
DELIMITER ;

-- Call with parameters
CALL GetStudentsByGPA(3.0, 4.0);
CALL GetStudentsByGPA(3.5, 4.0);
```

### Stored Procedure with Output Parameters

```sql
-- Create procedure with output parameters
DELIMITER //
CREATE PROCEDURE GetStudentStats(
    IN student_id_param INT,
    OUT total_courses INT,
    OUT average_grade DECIMAL(5,2),
    OUT total_credits INT
)
BEGIN
    SELECT 
        COUNT(e.course_id),
        AVG(e.grade),
        SUM(c.credits)
    INTO total_courses, average_grade, total_credits
    FROM enrollments e
    INNER JOIN courses c ON e.course_id = c.course_id
    WHERE e.student_id = student_id_param
    AND e.status = 'completed';
    
    -- Handle case when no courses found
    IF total_courses IS NULL THEN
        SET total_courses = 0;
        SET average_grade = 0.00;
        SET total_credits = 0;
    END IF;
END //
DELIMITER ;

-- Call with output parameters
SET @total_courses = 0;
SET @average_grade = 0.00;
SET @total_credits = 0;
CALL GetStudentStats(1, @total_courses, @average_grade, @total_credits);
SELECT @total_courses, @average_grade, @total_credits;
```

## Conditional Logic in Stored Procedures

### IF-ELSE Statements

```sql
-- Procedure with conditional logic
DELIMITER //
CREATE PROCEDURE GetStudentAcademicStanding(
    IN student_id_param INT,
    OUT academic_standing VARCHAR(20)
)
BEGIN
    DECLARE student_gpa DECIMAL(3,2);
    
    -- Get student GPA
    SELECT gpa INTO student_gpa
    FROM students
    WHERE student_id = student_id_param;
    
    -- Determine academic standing
    IF student_gpa >= 3.7 THEN
        SET academic_standing = 'High Honors';
    ELSEIF student_gpa >= 3.3 THEN
        SET academic_standing = 'Honors';
    ELSEIF student_gpa >= 3.0 THEN
        SET academic_standing = 'Good Standing';
    ELSE
        SET academic_standing = 'Academic Probation';
    END IF;
END //
DELIMITER ;

-- Test the procedure
SET @standing = '';
CALL GetStudentAcademicStanding(1, @standing);
SELECT @standing;
```

### CASE Statements

```sql
-- Procedure using CASE statement
DELIMITER //
CREATE PROCEDURE GetStudentGradeDistribution(
    IN student_id_param INT
)
BEGIN
    SELECT 
        CASE 
            WHEN grade >= 90 THEN 'A'
            WHEN grade >= 80 THEN 'B'
            WHEN grade >= 70 THEN 'C'
            WHEN grade >= 60 THEN 'D'
            ELSE 'F'
        END AS letter_grade,
        COUNT(*) AS count
    FROM enrollments
    WHERE student_id = student_id_param
    AND status = 'completed'
    GROUP BY 
        CASE 
            WHEN grade >= 90 THEN 'A'
            WHEN grade >= 80 THEN 'B'
            WHEN grade >= 70 THEN 'C'
            WHEN grade >= 60 THEN 'D'
            ELSE 'F'
        END
    ORDER BY letter_grade;
END //
DELIMITER ;

-- Test the procedure
CALL GetStudentGradeDistribution(1);
```

## Loops in Stored Procedures

### WHILE Loop

```sql
-- Procedure with WHILE loop
DELIMITER //
CREATE PROCEDURE GenerateStudentReport()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE student_id_var INT;
    DECLARE student_name VARCHAR(100);
    DECLARE student_gpa DECIMAL(3,2);
    
    -- Cursor declaration
    DECLARE student_cursor CURSOR FOR 
        SELECT student_id, CONCAT(first_name, ' ', last_name), gpa
        FROM students 
        WHERE status = 'active';
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    -- Create temporary table for report
    CREATE TEMPORARY TABLE student_report (
        student_id INT,
        student_name VARCHAR(100),
        gpa DECIMAL(3,2),
        academic_standing VARCHAR(20)
    );
    
    OPEN student_cursor;
    
    read_loop: WHILE NOT done DO
        FETCH student_cursor INTO student_id_var, student_name, student_gpa;
        
        IF NOT done THEN
            INSERT INTO student_report (student_id, student_name, gpa, academic_standing)
            VALUES (
                student_id_var,
                student_name,
                student_gpa,
                CASE 
                    WHEN student_gpa >= 3.7 THEN 'High Honors'
                    WHEN student_gpa >= 3.3 THEN 'Honors'
                    WHEN student_gpa >= 3.0 THEN 'Good Standing'
                    ELSE 'Academic Probation'
                END
            );
        END IF;
    END WHILE;
    
    CLOSE student_cursor;
    
    -- Return the report
    SELECT * FROM student_report ORDER BY gpa DESC;
    
    -- Clean up
    DROP TEMPORARY TABLE student_report;
END //
DELIMITER ;

-- Test the procedure
CALL GenerateStudentReport();
```

## Error Handling

### Exception Handling

```sql
-- Procedure with error handling
DELIMITER //
CREATE PROCEDURE EnrollStudent(
    IN student_id_param INT,
    IN course_id_param INT,
    OUT success BOOLEAN,
    OUT message VARCHAR(255)
)
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
        SET success = FALSE;
        SET message = 'An error occurred during enrollment';
    END;
    
    DECLARE student_exists INT DEFAULT 0;
    DECLARE course_exists INT DEFAULT 0;
    DECLARE already_enrolled INT DEFAULT 0;
    
    START TRANSACTION;
    
    -- Check if student exists
    SELECT COUNT(*) INTO student_exists
    FROM students
    WHERE student_id = student_id_param;
    
    IF student_exists = 0 THEN
        SET success = FALSE;
        SET message = 'Student not found';
        ROLLBACK;
    ELSE
        -- Check if course exists
        SELECT COUNT(*) INTO course_exists
        FROM courses
        WHERE course_id = course_id_param;
        
        IF course_exists = 0 THEN
            SET success = FALSE;
            SET message = 'Course not found';
            ROLLBACK;
        ELSE
            -- Check if already enrolled
            SELECT COUNT(*) INTO already_enrolled
            FROM enrollments
            WHERE student_id = student_id_param 
            AND course_id = course_id_param;
            
            IF already_enrolled > 0 THEN
                SET success = FALSE;
                SET message = 'Student already enrolled in this course';
                ROLLBACK;
            ELSE
                -- Enroll the student
                INSERT INTO enrollments (student_id, course_id, enrollment_date, status)
                VALUES (student_id_param, course_id_param, CURDATE(), 'enrolled');
                
                SET success = TRUE;
                SET message = 'Student enrolled successfully';
                COMMIT;
            END IF;
        END IF;
    END IF;
END //
DELIMITER ;

-- Test the procedure
SET @success = FALSE;
SET @message = '';
CALL EnrollStudent(1, 1, @success, @message);
SELECT @success, @message;
```

## User-Defined Functions

### Scalar Functions

```sql
-- Create a function to calculate letter grade
DELIMITER //
CREATE FUNCTION GetLetterGrade(numeric_grade DECIMAL(5,2))
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
    student_id,
    grade,
    GetLetterGrade(grade) AS letter_grade
FROM enrollments
WHERE grade IS NOT NULL;
```

### Table-Valued Functions

```sql
-- Create function to get student courses
DELIMITER //
CREATE FUNCTION GetStudentCourses(student_id_param INT)
RETURNS TABLE (
    course_code VARCHAR(10),
    course_name VARCHAR(100),
    credits INT,
    grade DECIMAL(5,2),
    status VARCHAR(20)
)
READS SQL DATA
DETERMINISTIC
BEGIN
    RETURN (
        SELECT 
            c.course_code,
            c.course_name,
            c.credits,
            e.grade,
            e.status
        FROM enrollments e
        INNER JOIN courses c ON e.course_id = c.course_id
        WHERE e.student_id = student_id_param
    );
END //
DELIMITER ;

-- Use the function (Note: MySQL doesn't support table-valued functions like SQL Server)
-- This is a conceptual example
```

## Managing Stored Procedures

### Viewing Stored Procedures

```sql
-- Show all stored procedures
SHOW PROCEDURE STATUS;

-- Show stored procedures in specific database
SHOW PROCEDURE STATUS WHERE Db = 'school_management';

-- Show procedure definition
SHOW CREATE PROCEDURE GetActiveStudents;

-- Show all functions
SHOW FUNCTION STATUS;
```

### Modifying and Dropping Procedures

```sql
-- Drop a stored procedure
DROP PROCEDURE IF EXISTS GetActiveStudents;

-- Drop a function
DROP FUNCTION IF EXISTS GetLetterGrade;

-- Alter procedure (MySQL doesn't support ALTER PROCEDURE)
-- You need to DROP and CREATE again
```

## Advanced Examples

### Complex Business Logic Procedure

```sql
-- Procedure for calculating semester GPA
DELIMITER //
CREATE PROCEDURE CalculateSemesterGPA(
    IN student_id_param INT,
    IN semester_year INT,
    IN semester_term VARCHAR(10),
    OUT semester_gpa DECIMAL(3,2),
    OUT total_credits INT,
    OUT total_points DECIMAL(8,2)
)
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE course_credits INT;
    DECLARE course_grade DECIMAL(5,2);
    DECLARE grade_points DECIMAL(5,2);
    
    DECLARE course_cursor CURSOR FOR
        SELECT c.credits, e.grade
        FROM enrollments e
        INNER JOIN courses c ON e.course_id = c.course_id
        WHERE e.student_id = student_id_param
        AND YEAR(e.enrollment_date) = semester_year
        AND e.status = 'completed';
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    SET total_credits = 0;
    SET total_points = 0.00;
    
    OPEN course_cursor;
    
    read_loop: WHILE NOT done DO
        FETCH course_cursor INTO course_credits, course_grade;
        
        IF NOT done THEN
            -- Convert numeric grade to grade points
            SET grade_points = CASE
                WHEN course_grade >= 90 THEN course_credits * 4.0
                WHEN course_grade >= 80 THEN course_credits * 3.0
                WHEN course_grade >= 70 THEN course_credits * 2.0
                WHEN course_grade >= 60 THEN course_credits * 1.0
                ELSE 0.0
            END;
            
            SET total_credits = total_credits + course_credits;
            SET total_points = total_points + grade_points;
        END IF;
    END WHILE;
    
    CLOSE course_cursor;
    
    -- Calculate GPA
    IF total_credits > 0 THEN
        SET semester_gpa = total_points / total_credits;
    ELSE
        SET semester_gpa = 0.00;
    END IF;
END //
DELIMITER ;

-- Test the procedure
SET @semester_gpa = 0.00;
SET @total_credits = 0;
SET @total_points = 0.00;
CALL CalculateSemesterGPA(1, 2023, 'Fall', @semester_gpa, @total_credits, @total_points);
SELECT @semester_gpa, @total_credits, @total_points;
```

## Hands-on Exercise

### Exercise 1: Basic Procedures

Create stored procedures for:

1. Get all students in a specific department
2. Get course enrollment statistics
3. Calculate student's overall GPA
4. Get students with GPA above a threshold

### Exercise 2: Advanced Procedures

Create procedures for:

1. Enroll a student in a course with validation
2. Generate a comprehensive student report
3. Calculate department performance metrics
4. Bulk update student statuses

### Exercise 3: Functions

Create user-defined functions for:

1. Calculate letter grade from numeric grade
2. Determine academic standing from GPA
3. Format student name (Last, First)
4. Calculate age from birth date

## Key Takeaways

- Stored procedures improve performance and security
- Use parameters to make procedures flexible
- Implement proper error handling
- Functions return values, procedures perform actions
- Use cursors for row-by-row processing
- Always clean up resources (close cursors, drop temp tables)

## Next Steps

In the next lesson, we'll learn about triggers and how they automatically respond to database events.

## Practice Questions

1. What are the main advantages of stored procedures?
2. What's the difference between IN, OUT, and INOUT parameters?
3. How do you handle errors in stored procedures?
4. When would you use a cursor in a stored procedure?
5. What's the difference between a stored procedure and a function?
