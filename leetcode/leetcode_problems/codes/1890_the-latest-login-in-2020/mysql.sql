-- Problem: The Latest Login in 2020
-- Difficulty: Easy
-- Tags: database

-- Approach: Filter by year 2020, find latest login per user
-- Time Complexity: O(n) where n is logins
-- Space Complexity: O(1)

SELECT 
    user_id,
    MAX(time_stamp) AS last_stamp
FROM Logins
WHERE YEAR(time_stamp) = 2020
GROUP BY user_id;

