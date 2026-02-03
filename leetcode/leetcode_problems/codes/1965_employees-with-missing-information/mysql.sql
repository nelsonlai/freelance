-- Problem: Employees with Missing Information
-- Difficulty: Easy
-- Tags: database
-- 
-- Approach: Find employees missing in either Salaries or Employees table
-- Time Complexity: O(n + m) where n, m are table sizes
-- Space Complexity: O(n + m)

SELECT employee_id
FROM Employees
WHERE employee_id NOT IN (SELECT employee_id FROM Salaries)
UNION
SELECT employee_id
FROM Salaries
WHERE employee_id NOT IN (SELECT employee_id FROM Employees)
ORDER BY employee_id;


