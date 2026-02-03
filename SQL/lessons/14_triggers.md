# Lesson 14: Triggers

## 📚 Learning Objectives

By the end of this lesson, you will be able to:
- Create and manage database triggers
- Understand BEFORE and AFTER trigger types
- Implement INSERT, UPDATE, and DELETE triggers
- Use triggers for data validation and auditing
- Handle trigger errors and exceptions
- Understand trigger performance implications

## 🎯 Prerequisites

- Completed Lessons 1-13
- Understanding of stored procedures and functions
- Knowledge of database constraints and validation
- Basic understanding of event-driven programming

## 📖 Table of Contents

1. [Introduction to Triggers](#introduction-to-triggers)
2. [Trigger Types and Timing](#trigger-types-and-timing)
3. [Creating Triggers](#creating-triggers)
4. [Data Validation Triggers](#data-validation-triggers)
5. [Audit and Logging Triggers](#audit-and-logging-triggers)
6. [Business Logic Triggers](#business-logic-triggers)
7. [Managing Triggers](#managing-triggers)
8. [Best Practices](#best-practices)
9. [Common Pitfalls](#common-pitfalls)

---

## 1. Introduction to Triggers

A **trigger** is a stored program that automatically executes in response to specific database events. Triggers are event-driven and cannot be called directly.

### When Triggers Execute

- **Before** or **After** INSERT operations
- **Before** or **After** UPDATE operations  
- **Before** or **After** DELETE operations
- **Automatically** when specified events occur

### Benefits of Triggers

- **Data Integrity**: Enforce complex business rules
- **Auditing**: Track all data changes
- **Automation**: Reduce application complexity
- **Consistency**: Ensure data consistency across tables
- **Security**: Implement additional security checks

### When to Use Triggers

- Complex data validation
- Maintaining audit trails
- Synchronizing related tables
- Enforcing business rules
- Data transformation during operations

---

## 2. Trigger Types and Timing

### BEFORE Triggers
Execute **before** the triggering event occurs.

```sql
-- BEFORE INSERT trigger example
DELIMITER //
CREATE TRIGGER before_student_insert
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    -- Validate email format
    IF NEW.email NOT REGEXP '^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$' THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Invalid email format';
    END IF;
    
    -- Set default values
    IF NEW.status IS NULL THEN
        SET NEW.status = 'Active';
    END IF;
    
    IF NEW.enrollment_date IS NULL THEN
        SET NEW.enrollment_date = CURDATE();
    END IF;
END //
DELIMITER ;
```

### AFTER Triggers
Execute **after** the triggering event occurs.

```sql
-- AFTER INSERT trigger example
DELIMITER //
CREATE TRIGGER after_student_insert
AFTER INSERT ON students
FOR EACH ROW
BEGIN
    -- Log the new student creation
    INSERT INTO audit_log (
        table_name,
        operation,
        record_id,
        user_name,
        timestamp,
        details
    ) VALUES (
        'students',
        'INSERT',
        NEW.student_id,
        USER(),
        NOW(),
        CONCAT('New student: ', NEW.first_name, ' ', NEW.last_name)
    );
END //
DELIMITER ;
```

---

## 3. Creating Triggers

### Basic Trigger Syntax

```sql
DELIMITER //
CREATE TRIGGER trigger_name
{BEFORE | AFTER} {INSERT | UPDATE | DELETE}
ON table_name
FOR EACH ROW
BEGIN
    -- Trigger logic here
END //
DELIMITER ;
```

### Trigger for Data Validation

```sql
-- Validate GPA range before insert or update
DELIMITER //
CREATE TRIGGER validate_gpa
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    IF NEW.gpa IS NOT NULL THEN
        IF NEW.gpa < 0 OR NEW.gpa > 4.0 THEN
            SIGNAL SQLSTATE '45000' 
            SET MESSAGE_TEXT = 'GPA must be between 0.0 and 4.0';
        END IF;
    END IF;
END //
DELIMITER ;

-- Also create for UPDATE operations
DELIMITER //
CREATE TRIGGER validate_gpa_update
BEFORE UPDATE ON students
FOR EACH ROW
BEGIN
    IF NEW.gpa IS NOT NULL THEN
        IF NEW.gpa < 0 OR NEW.gpa > 4.0 THEN
            SIGNAL SQLSTATE '45000' 
            SET MESSAGE_TEXT = 'GPA must be between 0.0 and 4.0';
        END IF;
    END IF;
END //
DELIMITER ;
```

### Trigger for Automatic Calculations

```sql
-- Calculate full name automatically
DELIMITER //
CREATE TRIGGER set_full_name_insert
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    SET NEW.full_name = CONCAT(NEW.first_name, ' ', NEW.last_name);
END //
DELIMITER ;

DELIMITER //
CREATE TRIGGER set_full_name_update
BEFORE UPDATE ON students
FOR EACH ROW
BEGIN
    SET NEW.full_name = CONCAT(NEW.first_name, ' ', NEW.last_name);
END //
DELIMITER ;
```

---

## 4. Data Validation Triggers

### Complex Validation Logic

```sql
-- Validate enrollment capacity
DELIMITER //
CREATE TRIGGER check_enrollment_capacity
BEFORE INSERT ON enrollments
FOR EACH ROW
BEGIN
    DECLARE current_count INT DEFAULT 0;
    DECLARE max_capacity INT DEFAULT 0;
    
    -- Get current enrollment count
    SELECT COUNT(*) INTO current_count
    FROM enrollments
    WHERE course_id = NEW.course_id;
    
    -- Get course capacity
    SELECT capacity INTO max_capacity
    FROM courses
    WHERE course_id = NEW.course_id;
    
    -- Check if course is full
    IF current_count >= max_capacity THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Course is at maximum capacity';
    END IF;
    
    -- Check if student is already enrolled
    IF EXISTS (
        SELECT 1 FROM enrollments 
        WHERE student_id = NEW.student_id 
          AND course_id = NEW.course_id
    ) THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Student is already enrolled in this course';
    END IF;
END //
DELIMITER ;
```

### Cross-Table Validation

```sql
-- Ensure student and course are in the same department
DELIMITER //
CREATE TRIGGER validate_department_consistency
BEFORE INSERT ON enrollments
FOR EACH ROW
BEGIN
    DECLARE student_dept_id INT;
    DECLARE course_dept_id INT;
    
    -- Get student's department
    SELECT department_id INTO student_dept_id
    FROM students
    WHERE student_id = NEW.student_id;
    
    -- Get course's department
    SELECT department_id INTO course_dept_id
    FROM courses
    WHERE course_id = NEW.course_id;
    
    -- Validate department consistency
    IF student_dept_id != course_dept_id THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Student and course must be in the same department';
    END IF;
END //
DELIMITER ;
```

---

## 5. Audit and Logging Triggers

### Comprehensive Audit System

First, create an audit table:

```sql
-- Create audit log table
CREATE TABLE audit_log (
    log_id INT AUTO_INCREMENT PRIMARY KEY,
    table_name VARCHAR(50) NOT NULL,
    operation ENUM('INSERT', 'UPDATE', 'DELETE') NOT NULL,
    record_id INT NOT NULL,
    old_values JSON,
    new_values JSON,
    user_name VARCHAR(100) NOT NULL,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ip_address VARCHAR(45),
    session_id VARCHAR(100)
);
```

### Audit Triggers

```sql
-- Audit trigger for students table
DELIMITER //
CREATE TRIGGER audit_students_insert
AFTER INSERT ON students
FOR EACH ROW
BEGIN
    INSERT INTO audit_log (
        table_name,
        operation,
        record_id,
        new_values,
        user_name,
        ip_address
    ) VALUES (
        'students',
        'INSERT',
        NEW.student_id,
        JSON_OBJECT(
            'first_name', NEW.first_name,
            'last_name', NEW.last_name,
            'email', NEW.email,
            'department_id', NEW.department_id,
            'gpa', NEW.gpa,
            'status', NEW.status
        ),
        USER(),
        CONNECTION_ID()
    );
END //
DELIMITER ;

-- Audit trigger for updates
DELIMITER //
CREATE TRIGGER audit_students_update
AFTER UPDATE ON students
FOR EACH ROW
BEGIN
    INSERT INTO audit_log (
        table_name,
        operation,
        record_id,
        old_values,
        new_values,
        user_name,
        ip_address
    ) VALUES (
        'students',
        'UPDATE',
        NEW.student_id,
        JSON_OBJECT(
            'first_name', OLD.first_name,
            'last_name', OLD.last_name,
            'email', OLD.email,
            'department_id', OLD.department_id,
            'gpa', OLD.gpa,
            'status', OLD.status
        ),
        JSON_OBJECT(
            'first_name', NEW.first_name,
            'last_name', NEW.last_name,
            'email', NEW.email,
            'department_id', NEW.department_id,
            'gpa', NEW.gpa,
            'status', NEW.status
        ),
        USER(),
        CONNECTION_ID()
    );
END //
DELIMITER ;

-- Audit trigger for deletes
DELIMITER //
CREATE TRIGGER audit_students_delete
AFTER DELETE ON students
FOR EACH ROW
BEGIN
    INSERT INTO audit_log (
        table_name,
        operation,
        record_id,
        old_values,
        user_name,
        ip_address
    ) VALUES (
        'students',
        'DELETE',
        OLD.student_id,
        JSON_OBJECT(
            'first_name', OLD.first_name,
            'last_name', OLD.last_name,
            'email', OLD.email,
            'department_id', OLD.department_id,
            'gpa', OLD.gpa,
            'status', OLD.status
        ),
        USER(),
        CONNECTION_ID()
    );
END //
DELIMITER ;
```

---

## 6. Business Logic Triggers

### Automatic Status Updates

```sql
-- Update student status based on GPA
DELIMITER //
CREATE TRIGGER update_student_status
AFTER UPDATE ON students
FOR EACH ROW
BEGIN
    DECLARE new_status VARCHAR(20);
    
    -- Determine new status based on GPA
    IF NEW.gpa IS NULL THEN
        SET new_status = 'Active';
    ELSEIF NEW.gpa >= 3.5 THEN
        SET new_status = 'Honor Roll';
    ELSEIF NEW.gpa >= 2.0 THEN
        SET new_status = 'Active';
    ELSE
        SET new_status = 'Academic Probation';
    END IF;
    
    -- Update status if it changed
    IF new_status != NEW.status THEN
        UPDATE students 
        SET status = new_status 
        WHERE student_id = NEW.student_id;
    END IF;
END //
DELIMITER ;
```

### Cascade Operations

```sql
-- Maintain course enrollment count
DELIMITER //
CREATE TRIGGER update_course_enrollment_count
AFTER INSERT ON enrollments
FOR EACH ROW
BEGIN
    UPDATE courses 
    SET enrollment_count = enrollment_count + 1
    WHERE course_id = NEW.course_id;
END //
DELIMITER ;

DELIMITER //
CREATE TRIGGER update_course_enrollment_count_delete
AFTER DELETE ON enrollments
FOR EACH ROW
BEGIN
    UPDATE courses 
    SET enrollment_count = enrollment_count - 1
    WHERE course_id = OLD.course_id;
END //
DELIMITER ;
```

### Derived Data Maintenance

```sql
-- Calculate and store student statistics
DELIMITER //
CREATE TRIGGER update_student_stats
AFTER UPDATE ON students
FOR EACH ROW
BEGIN
    DECLARE total_courses INT DEFAULT 0;
    DECLARE avg_grade DECIMAL(5,2) DEFAULT 0.00;
    
    -- Calculate statistics
    SELECT 
        COUNT(*),
        AVG(grade)
    INTO total_courses, avg_grade
    FROM enrollments
    WHERE student_id = NEW.student_id
      AND grade IS NOT NULL;
    
    -- Update student record with calculated values
    UPDATE students 
    SET 
        total_courses_completed = total_courses,
        average_grade = avg_grade
    WHERE student_id = NEW.student_id;
END //
DELIMITER ;
```

---

## 7. Managing Triggers

### Viewing Triggers

```sql
-- Show all triggers
SHOW TRIGGERS;

-- Show triggers for specific table
SHOW TRIGGERS LIKE 'students';

-- Get detailed trigger information
SELECT 
    TRIGGER_NAME,
    EVENT_MANIPULATION,
    EVENT_OBJECT_TABLE,
    ACTION_TIMING,
    ACTION_STATEMENT
FROM information_schema.TRIGGERS
WHERE TRIGGER_SCHEMA = 'school_db';
```

### Modifying Triggers

```sql
-- Drop existing trigger
DROP TRIGGER IF EXISTS validate_gpa;

-- Create updated trigger
DELIMITER //
CREATE TRIGGER validate_gpa_enhanced
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    -- Enhanced validation logic
    IF NEW.gpa IS NOT NULL THEN
        IF NEW.gpa < 0 OR NEW.gpa > 4.0 THEN
            SIGNAL SQLSTATE '45000' 
            SET MESSAGE_TEXT = 'GPA must be between 0.0 and 4.0';
        END IF;
        
        -- Additional business rule: warn about very high GPA
        IF NEW.gpa > 3.9 THEN
            INSERT INTO warnings (
                student_id,
                warning_type,
                message,
                created_at
            ) VALUES (
                NEW.student_id,
                'HIGH_GPA',
                'GPA above 3.9 requires verification',
                NOW()
            );
        END IF;
    END IF;
END //
DELIMITER ;
```

### Disabling Triggers

```sql
-- MySQL doesn't have built-in trigger disable, but you can:
-- 1. Drop the trigger temporarily
DROP TRIGGER validate_gpa;

-- 2. Or add a condition to bypass trigger logic
DELIMITER //
CREATE TRIGGER validate_gpa_conditional
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    -- Only validate if not in maintenance mode
    IF @maintenance_mode != 1 THEN
        IF NEW.gpa IS NOT NULL THEN
            IF NEW.gpa < 0 OR NEW.gpa > 4.0 THEN
                SIGNAL SQLSTATE '45000' 
                SET MESSAGE_TEXT = 'GPA must be between 0.0 and 4.0';
            END IF;
        END IF;
    END IF;
END //
DELIMITER ;

-- Set maintenance mode
SET @maintenance_mode = 1;
```

---

## 8. Best Practices

### Performance Considerations

```sql
-- Efficient trigger - minimal operations
DELIMITER //
CREATE TRIGGER efficient_audit
AFTER UPDATE ON students
FOR EACH ROW
BEGIN
    -- Only log if important fields changed
    IF OLD.gpa != NEW.gpa OR OLD.status != NEW.status THEN
        INSERT INTO audit_log (
            table_name,
            operation,
            record_id,
            user_name,
            timestamp
        ) VALUES (
            'students',
            'UPDATE',
            NEW.student_id,
            USER(),
            NOW()
        );
    END IF;
END //
DELIMITER ;
```

### Error Handling

```sql
-- Robust trigger with error handling
DELIMITER //
CREATE TRIGGER robust_validation
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        -- Log the error
        INSERT INTO error_log (
            error_message,
            table_name,
            operation,
            timestamp
        ) VALUES (
            'Trigger validation failed',
            'students',
            'INSERT',
            NOW()
        );
        
        -- Re-raise the error
        RESIGNAL;
    END;
    
    -- Validation logic here
    IF NEW.email IS NULL OR NEW.email = '' THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'Email is required';
    END IF;
END //
DELIMITER ;
```

### Documentation

```sql
-- Well-documented trigger
DELIMITER //
-- Trigger: audit_student_changes
-- Purpose: Log all changes to student records for audit trail
-- Events: INSERT, UPDATE, DELETE on students table
-- Author: Database Team
-- Created: 2024-01-15
-- Dependencies: audit_log table must exist
CREATE TRIGGER audit_student_changes
AFTER INSERT ON students
FOR EACH ROW
BEGIN
    -- Implementation here
END //
DELIMITER ;
```

---

## 9. Common Pitfalls

### Pitfall 1: Infinite Recursion

```sql
-- ❌ DANGEROUS: Can cause infinite recursion
DELIMITER //
CREATE TRIGGER bad_trigger
AFTER UPDATE ON students
FOR EACH ROW
BEGIN
    -- This update will trigger the same trigger again!
    UPDATE students 
    SET last_updated = NOW() 
    WHERE student_id = NEW.student_id;
END //
DELIMITER ;

-- ✅ BETTER: Use BEFORE trigger to avoid recursion
DELIMITER //
CREATE TRIGGER good_trigger
BEFORE UPDATE ON students
FOR EACH ROW
BEGIN
    SET NEW.last_updated = NOW();
END //
DELIMITER ;
```

### Pitfall 2: Performance Issues

```sql
-- ❌ INEFFICIENT: Complex operations in trigger
DELIMITER //
CREATE TRIGGER slow_trigger
AFTER INSERT ON enrollments
FOR EACH ROW
BEGIN
    -- This could be very slow for large datasets
    UPDATE courses 
    SET enrollment_count = (
        SELECT COUNT(*) 
        FROM enrollments 
        WHERE course_id = NEW.course_id
    )
    WHERE course_id = NEW.course_id;
END //
DELIMITER ;

-- ✅ BETTER: Simple increment/decrement
DELIMITER //
CREATE TRIGGER fast_trigger
AFTER INSERT ON enrollments
FOR EACH ROW
BEGIN
    UPDATE courses 
    SET enrollment_count = enrollment_count + 1
    WHERE course_id = NEW.course_id;
END //
DELIMITER ;
```

### Pitfall 3: Missing Error Handling

```sql
-- ❌ RISKY: No error handling
DELIMITER //
CREATE TRIGGER risky_trigger
AFTER INSERT ON students
FOR EACH ROW
BEGIN
    -- If this fails, the entire transaction fails
    INSERT INTO external_system (student_id, name)
    VALUES (NEW.student_id, CONCAT(NEW.first_name, ' ', NEW.last_name));
END //
DELIMITER ;

-- ✅ BETTER: Handle errors gracefully
DELIMITER //
CREATE TRIGGER safe_trigger
AFTER INSERT ON students
FOR EACH ROW
BEGIN
    DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
    BEGIN
        -- Log error but don't fail the transaction
        INSERT INTO error_log (error_message, timestamp)
        VALUES ('Failed to sync with external system', NOW());
    END;
    
    INSERT INTO external_system (student_id, name)
    VALUES (NEW.student_id, CONCAT(NEW.first_name, ' ', NEW.last_name));
END //
DELIMITER ;
```

---

## 🎯 Summary

Triggers are powerful tools for maintaining data integrity and implementing business logic:

### Key Concepts
- **Event-driven execution** based on table operations
- **BEFORE vs AFTER** timing for different use cases
- **Data validation** and business rule enforcement
- **Audit trails** and change tracking
- **Automatic calculations** and derived data maintenance

### Best Practices
1. **Keep triggers simple** and efficient
2. **Handle errors gracefully** to avoid transaction failures
3. **Avoid infinite recursion** with careful UPDATE logic
4. **Document triggers** for maintainability
5. **Test thoroughly** before deploying to production
6. **Monitor performance** impact on operations

### When to Use Triggers
- **Data validation** that can't be handled by constraints
- **Audit logging** for compliance requirements
- **Business logic** that must always be enforced
- **Data synchronization** between related tables
- **Automatic calculations** for derived fields

## 🔄 Next Steps

- Practice creating triggers for your database
- Implement audit logging for important tables
- Move on to Lesson 15: Performance Optimization
- Consider trigger performance implications

## 📚 Additional Resources

- MySQL Documentation: [Triggers](https://dev.mysql.com/doc/refman/8.0/en/triggers.html)
- MySQL Documentation: [Trigger Syntax](https://dev.mysql.com/doc/refman/8.0/en/create-trigger.html)
- MySQL Documentation: [Error Handling](https://dev.mysql.com/doc/refman/8.0/en/declare-handler.html)
