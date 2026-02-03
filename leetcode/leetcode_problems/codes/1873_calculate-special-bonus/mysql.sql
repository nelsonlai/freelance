-- Problem: Calculate Special Bonus
-- Difficulty: Easy
-- Tags: database

-- Approach: Use CASE to calculate bonus based on conditions
-- Time Complexity: O(n) where n is employees
-- Space Complexity: O(1)

SELECT 
    employee_id,
    CASE 
        WHEN employee_id % 2 = 1 AND name NOT LIKE 'M%' THEN salary
        ELSE 0
    END AS bonus
FROM Employees
ORDER BY employee_id;

