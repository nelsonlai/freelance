-- Problem: Number of Accounts That Did Not Stream
-- Difficulty: Medium
-- Tags: database
-- 
-- Approach: Find accounts that exist in Subscriptions but not in Streams
-- Time Complexity: O(n + m) where n, m are table sizes
-- Space Complexity: O(n + m)

SELECT COUNT(DISTINCT s.account_id) AS accounts_count
FROM Subscriptions s
LEFT JOIN Streams st ON s.account_id = st.account_id 
    AND s.start_date <= st.stream_date 
    AND st.stream_date <= s.end_date
WHERE st.account_id IS NULL
    AND s.start_date <= '2021-12-31'
    AND s.end_date >= '2021-01-01';



