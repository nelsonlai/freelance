-- Problem: Suspicious Bank Accounts
-- Difficulty: Medium
-- Tags: database

-- Approach: Find accounts with transactions > max income in any month
-- Time Complexity: O(n) where n is transactions
-- Space Complexity: O(1)

WITH MonthlyIncome AS (
    SELECT account_id, DATE_FORMAT(day, '%Y-%m') AS month, SUM(amount) AS income
    FROM Transactions
    WHERE type = 'Creditor'
    GROUP BY account_id, DATE_FORMAT(day, '%Y-%m')
),
SuspiciousMonths AS (
    SELECT DISTINCT t1.account_id
    FROM MonthlyIncome t1
    JOIN MonthlyIncome t2 ON t1.account_id = t2.account_id
        AND t1.month < t2.month
        AND t1.income > (
            SELECT MAX(income)
            FROM MonthlyIncome
            WHERE account_id = t1.account_id
        )
)
SELECT DISTINCT account_id
FROM SuspiciousMonths
ORDER BY account_id;

