-- Problem: First and Last Call on the Same Day
-- Difficulty: Medium
-- Tags: database
-- 
-- Approach: Find user's first and last call on the same day
-- Time Complexity: O(n log n) where n is calls
-- Space Complexity: O(n)

SELECT DISTINCT user_id
FROM (
    SELECT 
        caller_id AS user_id,
        DATE(call_time) AS call_date,
        MIN(call_time) AS first_call,
        MAX(call_time) AS last_call
    FROM (
        SELECT caller_id, recipient_id, call_time FROM Calls
        UNION ALL
        SELECT recipient_id, caller_id, call_time FROM Calls
    ) AS all_calls
    GROUP BY caller_id, DATE(call_time)
) AS daily_calls
WHERE first_call != last_call
ORDER BY user_id;


