-- Problem: Find Total Time Spent by Each Employee
-- Difficulty: Easy
-- Tags: database

-- Approach: Sum time spent per employee per day
-- Time Complexity: O(n) where n is entries
-- Space Complexity: O(1)

SELECT 
    event_day AS day,
    emp_id,
    SUM(out_time - in_time) AS total_time
FROM Employees
GROUP BY event_day, emp_id
ORDER BY event_day, emp_id;

