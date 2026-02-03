-- Problem: Sellers With No Sales
-- Difficulty: Easy
-- Tags: database

-- Approach: Find sellers who have no sales using LEFT JOIN or NOT EXISTS
-- Time Complexity: O(n + m) where n is sellers, m is orders
-- Space Complexity: O(1)

SELECT seller_name
FROM Seller
WHERE seller_id NOT IN (
    SELECT DISTINCT seller_id
    FROM Orders
    WHERE sale_date >= '2020-01-01'
)
ORDER BY seller_name;

