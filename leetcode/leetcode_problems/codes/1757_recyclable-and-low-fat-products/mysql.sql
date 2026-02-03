-- Problem: Recyclable and Low Fat Products
-- Difficulty: Easy
-- Tags: database

-- Approach: Simple WHERE clause filter
-- Time Complexity: O(n) where n is products
-- Space Complexity: O(1)

SELECT product_id
FROM Products
WHERE low_fats = 'Y' AND recyclable = 'Y';

