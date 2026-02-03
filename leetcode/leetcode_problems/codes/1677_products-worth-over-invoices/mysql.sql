-- Problem: Product's Worth Over Invoices
-- Difficulty: Easy
-- Tags: database

-- Approach: Calculate total price per product, filter products worth over 100000
-- Time Complexity: O(n) where n is invoices
-- Space Complexity: O(1)

SELECT 
    p.name,
    COALESCE(SUM(i.rest), 0) + COALESCE(SUM(i.paid), 0) + COALESCE(SUM(i.canceled), 0) AS total
FROM Product p
LEFT JOIN Invoice i ON p.product_id = i.product_id
GROUP BY p.product_id, p.name
HAVING total > 100000
ORDER BY total DESC;

