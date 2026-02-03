-- Problem: Group Employees of the Same Salary
-- Difficulty: Medium
-- Tags: database

-- Approach: Use window functions to assign ranks and group IDs
-- Time Complexity: O(n log n) for sorting
-- Space Complexity: O(n)

SELECT 
    employee_id,
    name,
    salary,
    DENSE_RANK() OVER (ORDER BY salary) AS team_id
FROM Employees
WHERE salary IN (
    SELECT salary
    FROM Employees
    GROUP BY salary
    HAVING COUNT(*) > 1
)
ORDER BY team_id, employee_id;

