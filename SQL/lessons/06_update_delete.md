# Lesson 6: Updating and Deleting Data

## Learning Objectives
- Learn how to update existing data in tables
- Understand how to delete records from tables
- Practice safe data modification techniques
- Learn about transaction management

## UPDATE Statement

### Basic UPDATE Syntax

```sql
-- Basic UPDATE syntax
UPDATE table_name 
SET column1 = value1, column2 = value2, ...
WHERE condition;

-- Update a single record
UPDATE students 
SET gpa = 3.8 
WHERE student_id = 1;

-- Update multiple columns
UPDATE students 
SET gpa = 3.9, status = 'graduated' 
WHERE student_id = 1;
```

### UPDATE with WHERE Clause

```sql
-- Update specific students
UPDATE students 
SET status = 'graduated' 
WHERE status = 'active' AND gpa >= 3.5;

-- Update based on date
UPDATE students 
SET status = 'inactive' 
WHERE enrollment_date < '2020-01-01';

-- Update with pattern matching
UPDATE students 
SET phone = '555-0000' 
WHERE email LIKE '%@olduniversity.edu';
```

### UPDATE with JOIN

```sql
-- Update students based on course information
UPDATE students s
INNER JOIN enrollments e ON s.student_id = e.student_id
INNER JOIN courses c ON e.course_id = c.course_id
SET s.status = 'graduated'
WHERE c.course_code = 'CS401' AND e.grade >= 90;

-- Update course information based on department
UPDATE courses c
INNER JOIN departments d ON c.dept_id = d.dept_id
SET c.description = CONCAT(c.description, ' (', d.dept_name, ' Department)')
WHERE d.dept_name = 'Computer Science';
```

### UPDATE with Subqueries

```sql
-- Update students based on subquery results
UPDATE students 
SET status = 'honors'
WHERE student_id IN (
    SELECT student_id 
    FROM enrollments 
    WHERE grade >= 90 
    GROUP BY student_id 
    HAVING COUNT(*) >= 3
);

-- Update GPA based on average grade
UPDATE students s
SET gpa = (
    SELECT AVG(e.grade) / 25.0  -- Convert 100-point scale to 4.0 scale
    FROM enrollments e
    WHERE e.student_id = s.student_id
    AND e.status = 'completed'
)
WHERE s.student_id IN (
    SELECT DISTINCT student_id 
    FROM enrollments 
    WHERE status = 'completed'
);
```

## DELETE Statement

### Basic DELETE Syntax

```sql
-- Basic DELETE syntax
DELETE FROM table_name WHERE condition;

-- Delete specific record
DELETE FROM students WHERE student_id = 25;

-- Delete multiple records
DELETE FROM enrollments WHERE status = 'dropped';
```

### DELETE with WHERE Clause

```sql
-- Delete inactive students
DELETE FROM students WHERE status = 'inactive';

-- Delete old enrollments
DELETE FROM enrollments 
WHERE enrollment_date < '2020-01-01' AND status = 'completed';

-- Delete with pattern matching
DELETE FROM students 
WHERE email LIKE '%@test.com';
```

### DELETE with JOIN

```sql
-- Delete students who haven't enrolled in any courses
DELETE s FROM students s
LEFT JOIN enrollments e ON s.student_id = e.student_id
WHERE e.student_id IS NULL;

-- Delete enrollments for dropped courses
DELETE e FROM enrollments e
INNER JOIN courses c ON e.course_id = c.course_id
WHERE c.course_code = 'OLD101';
```

### DELETE with Subqueries

```sql
-- Delete students with low performance
DELETE FROM students 
WHERE student_id IN (
    SELECT student_id 
    FROM enrollments 
    WHERE grade < 60 
    GROUP BY student_id 
    HAVING COUNT(*) >= 2
);

-- Delete courses with no enrollments
DELETE FROM courses 
WHERE course_id NOT IN (
    SELECT DISTINCT course_id 
    FROM enrollments
);
```

## Safe Data Modification Practices

### Always Use WHERE Clause

```sql
-- DANGEROUS: Updates all records
UPDATE students SET status = 'inactive';

-- SAFE: Updates only specific records
UPDATE students SET status = 'inactive' WHERE student_id = 1;
```

### Test with SELECT First

```sql
-- First, see what will be updated
SELECT * FROM students WHERE status = 'active' AND gpa < 2.0;

-- Then perform the update
UPDATE students SET status = 'inactive' WHERE status = 'active' AND gpa < 2.0;
```

### Use Transactions

```sql
-- Start transaction
START TRANSACTION;

-- Perform multiple operations
UPDATE students SET status = 'graduated' WHERE student_id = 1;
INSERT INTO enrollments (student_id, course_id, status) VALUES (1, 5, 'completed');

-- Check if everything is correct
SELECT * FROM students WHERE student_id = 1;
SELECT * FROM enrollments WHERE student_id = 1;

-- Commit if everything looks good
COMMIT;

-- Or rollback if there's an issue
-- ROLLBACK;
```

## Advanced UPDATE Examples

### Conditional Updates

```sql
-- Update GPA based on grade ranges
UPDATE students s
SET gpa = CASE
    WHEN (
        SELECT AVG(e.grade) 
        FROM enrollments e 
        WHERE e.student_id = s.student_id 
        AND e.status = 'completed'
    ) >= 90 THEN 4.0
    WHEN (
        SELECT AVG(e.grade) 
        FROM enrollments e 
        WHERE e.student_id = s.student_id 
        AND e.status = 'completed'
    ) >= 80 THEN 3.0
    WHEN (
        SELECT AVG(e.grade) 
        FROM enrollments e 
        WHERE e.student_id = s.student_id 
        AND e.status = 'completed'
    ) >= 70 THEN 2.0
    WHEN (
        SELECT AVG(e.grade) 
        FROM enrollments e 
        WHERE e.student_id = s.student_id 
        AND e.status = 'completed'
    ) >= 60 THEN 1.0
    ELSE 0.0
END
WHERE s.student_id IN (
    SELECT DISTINCT student_id 
    FROM enrollments 
    WHERE status = 'completed'
);
```

### Bulk Updates

```sql
-- Update all students' status based on enrollment date
UPDATE students 
SET status = CASE
    WHEN enrollment_date < '2020-01-01' THEN 'graduated'
    WHEN enrollment_date < '2023-01-01' THEN 'active'
    ELSE 'new'
END;

-- Update course descriptions
UPDATE courses 
SET description = CONCAT('Course: ', course_name, ' (', credits, ' credits)')
WHERE description IS NULL OR description = '';
```

## Advanced DELETE Examples

### Cascading Deletes

```sql
-- Delete a student and all their enrollments (due to CASCADE)
DELETE FROM students WHERE student_id = 1;

-- Delete a course and all its enrollments (due to CASCADE)
DELETE FROM courses WHERE course_id = 1;
```

### Conditional Deletes

```sql
-- Delete students who haven't been active for 2 years
DELETE FROM students 
WHERE status = 'inactive' 
AND enrollment_date < DATE_SUB(CURDATE(), INTERVAL 2 YEAR);

-- Delete old completed enrollments
DELETE FROM enrollments 
WHERE status = 'completed' 
AND enrollment_date < DATE_SUB(CURDATE(), INTERVAL 5 YEAR);
```

## Data Integrity Considerations

### Foreign Key Constraints

```sql
-- Check foreign key constraints before deleting
SELECT COUNT(*) FROM enrollments WHERE student_id = 1;

-- If there are dependent records, delete them first
DELETE FROM enrollments WHERE student_id = 1;
DELETE FROM students WHERE student_id = 1;
```

### Check Constraints

```sql
-- This will fail due to check constraint
UPDATE students SET gpa = 5.0 WHERE student_id = 1;

-- This will succeed
UPDATE students SET gpa = 3.8 WHERE student_id = 1;
```

## Hands-on Exercise

### Exercise 1: Basic Updates

Write UPDATE statements to:

1. Change student ID 1's GPA to 3.8
2. Update all active students' status to 'graduated' if GPA >= 3.5
3. Set phone numbers to NULL for students with email '@test.com'
4. Update course descriptions to include department name

### Exercise 2: Basic Deletes

Write DELETE statements to:

1. Delete student with ID 25
2. Delete all enrollments with status 'dropped'
3. Delete students who have no enrollments
4. Delete courses with no enrollments

### Exercise 3: Advanced Operations

Write statements to:

1. Update student GPAs based on their average grades
2. Delete students with consistently low performance
3. Update course information based on department data
4. Clean up old inactive records

### Exercise 4: Transaction Management

Create a transaction that:

1. Updates a student's status to 'graduated'
2. Inserts a new enrollment record
3. Updates the student's GPA
4. Commits or rolls back based on validation

## Key Takeaways

- Always use WHERE clause to avoid updating/deleting all records
- Test with SELECT before UPDATE/DELETE
- Use transactions for multiple related operations
- Consider foreign key constraints and cascading effects
- Be aware of check constraints when updating data
- Use JOINs and subqueries for complex updates/deletes

## Next Steps

In the next lesson, we'll learn about JOINs and how to combine data from multiple tables.

## Practice Questions

1. What happens if you forget the WHERE clause in an UPDATE statement?
2. How do you safely test an UPDATE before executing it?
3. What's the difference between DELETE and TRUNCATE?
4. When would you use a transaction for data modification?
5. How do foreign key constraints affect DELETE operations?
