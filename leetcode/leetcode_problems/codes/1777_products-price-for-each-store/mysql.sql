-- Problem: Products Price for Each Store
-- Difficulty: Easy
-- Tags: database

-- Approach: Pivot using CASE statements
-- Time Complexity: O(n) where n is products
-- Space Complexity: O(1)

SELECT 
    product_id,
    MAX(CASE WHEN store = 'store1' THEN price END) AS store1,
    MAX(CASE WHEN store = 'store2' THEN price END) AS store2,
    MAX(CASE WHEN store = 'store3' THEN price END) AS store3
FROM Products
GROUP BY product_id;

