-- Problem: Orders With Maximum Quantity Above Average
-- Difficulty: Medium
-- Tags: database

-- Approach: Find orders with quantity > average quantity
-- Time Complexity: O(n) where n is orders
-- Space Complexity: O(1)

SELECT order_id
FROM OrdersDetails
GROUP BY order_id
HAVING MAX(quantity) > (
    SELECT MAX(avg_quantity)
    FROM (
        SELECT AVG(quantity) AS avg_quantity
        FROM OrdersDetails
        GROUP BY order_id
    ) AS avg_quantities
);

