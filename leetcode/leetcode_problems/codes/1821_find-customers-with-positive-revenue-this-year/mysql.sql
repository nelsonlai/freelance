-- Problem: Find Customers With Positive Revenue This Year
-- Difficulty: Easy
-- Tags: database

-- Approach: Filter by year and positive revenue
-- Time Complexity: O(n) where n is customers
-- Space Complexity: O(1)

SELECT customer_id
FROM Customers
WHERE year = 2021 AND revenue > 0;

