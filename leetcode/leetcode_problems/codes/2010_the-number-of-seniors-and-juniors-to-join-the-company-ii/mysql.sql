-- Problem: The Number of Seniors and Juniors to Join the Company II
-- Difficulty: Hard
-- Tags: database
-- 
-- Approach: Use window functions to calculate cumulative salary and select employees
-- Time Complexity: O(n log n) for sorting
-- Space Complexity: O(n)

WITH RankedEmployees AS (
    SELECT 
        employee_id,
        experience,
        salary,
        SUM(salary) OVER (PARTITION BY experience ORDER BY salary, employee_id) AS cumulative_salary
    FROM Candidates
),
SeniorSelection AS (
    SELECT 
        employee_id,
        experience,
        salary,
        cumulative_salary
    FROM RankedEmployees
    WHERE experience = 'Senior' AND cumulative_salary <= 70000
),
JuniorSelection AS (
    SELECT 
        re.employee_id,
        re.experience,
        re.salary,
        re.cumulative_salary
    FROM RankedEmployees re
    WHERE re.experience = 'Junior'
        AND re.cumulative_salary <= 70000 - COALESCE((SELECT MAX(cumulative_salary) FROM SeniorSelection), 0)
)
SELECT 
    'Senior' AS experience,
    COUNT(*) AS accepted_candidates
FROM SeniorSelection
UNION ALL
SELECT 
    'Junior' AS experience,
    COUNT(*) AS accepted_candidates
FROM JuniorSelection;



