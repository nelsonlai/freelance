-- Problem: Find the Missing IDs
-- Difficulty: Medium
-- Tags: database

-- Approach: Generate sequence of IDs and find missing ones using recursive CTE or numbers table
-- Time Complexity: O(n) where n is range
-- Space Complexity: O(n)

WITH RECURSIVE numbers AS (
    SELECT 1 AS n
    UNION ALL
    SELECT n + 1 FROM numbers WHERE n < (SELECT MAX(customer_id) FROM Customers)
)
SELECT n AS ids
FROM numbers
WHERE n NOT IN (SELECT customer_id FROM Customers)
ORDER BY n;

