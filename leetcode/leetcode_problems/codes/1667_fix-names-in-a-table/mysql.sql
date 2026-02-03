-- Problem: Fix Names in a Table
-- Difficulty: Easy
-- Tags: database

-- Approach: Capitalize first letter, lowercase rest
-- Time Complexity: O(n) where n is rows
-- Space Complexity: O(1)

SELECT 
    user_id,
    CONCAT(
        UPPER(LEFT(name, 1)),
        LOWER(SUBSTRING(name, 2))
    ) AS name
FROM Users
ORDER BY user_id;

