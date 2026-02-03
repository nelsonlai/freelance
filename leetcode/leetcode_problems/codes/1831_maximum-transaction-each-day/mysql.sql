-- Problem: Maximum Transaction Each Day
-- Difficulty: Medium
-- Tags: database

-- Approach: Find maximum amount per day, then get transactions with that amount
-- Time Complexity: O(n) where n is transactions
-- Space Complexity: O(1)

SELECT transaction_id
FROM Transactions
WHERE (DATE(day), amount) IN (
    SELECT DATE(day), MAX(amount)
    FROM Transactions
    GROUP BY DATE(day)
)
ORDER BY transaction_id;

