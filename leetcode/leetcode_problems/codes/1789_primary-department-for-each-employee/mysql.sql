-- Problem: Primary Department for Each Employee
-- Difficulty: Easy
-- Tags: database

-- Approach: Use CASE to select primary department or first department if no primary flag
-- Time Complexity: O(n) where n is employees
-- Space Complexity: O(1)

SELECT 
    employee_id,
    department_id
FROM Employee
WHERE primary_flag = 'Y'
   OR (employee_id, 'Y') NOT IN (SELECT employee_id, primary_flag FROM Employee WHERE primary_flag = 'Y')
GROUP BY employee_id
HAVING COUNT(*) = 1;

