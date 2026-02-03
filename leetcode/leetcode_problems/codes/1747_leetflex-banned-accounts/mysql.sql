-- Problem: Leetflex Banned Accounts
-- Difficulty: Medium
-- Tags: database

-- Approach: Find accounts that logged in from different IPs within 1 hour
-- Time Complexity: O(n^2) where n is logins
-- Space Complexity: O(1)

SELECT DISTINCT l1.account_id
FROM LogInfo l1
JOIN LogInfo l2 ON l1.account_id = l2.account_id
    AND l1.ip_address != l2.ip_address
    AND l1.login <= l2.login
    AND l2.login <= DATE_ADD(l1.login, INTERVAL 1 HOUR);

