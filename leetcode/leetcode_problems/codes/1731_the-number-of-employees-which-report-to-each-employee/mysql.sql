-- Problem: The Number of Employees Which Report to Each Employee
-- Difficulty: Medium
-- Tags: database

-- Approach: Count direct reports for each manager
-- Time Complexity: O(n) where n is employees
-- Space Complexity: O(1)

SELECT 
    e1.employee_id,
    e1.name,
    COUNT(e2.employee_id) AS reports_count,
    ROUND(AVG(e2.age)) AS average_age
FROM Employees e1
LEFT JOIN Employees e2 ON e1.employee_id = e2.reports_to
WHERE e2.employee_id IS NOT NULL
GROUP BY e1.employee_id, e1.name
ORDER BY e1.employee_id;

