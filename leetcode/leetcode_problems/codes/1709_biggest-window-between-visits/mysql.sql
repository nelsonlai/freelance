-- Problem: Biggest Window Between Visits
-- Difficulty: Medium
-- Tags: database

-- Approach: Find maximum gap between consecutive visits for each user
-- Time Complexity: O(n log n) where n is visits
-- Space Complexity: O(n)

WITH visit_gaps AS (
    SELECT 
        user_id,
        visit_date,
        LAG(visit_date) OVER (PARTITION BY user_id ORDER BY visit_date) AS prev_visit,
        DATEDIFF(visit_date, LAG(visit_date) OVER (PARTITION BY user_id ORDER BY visit_date)) AS gap
    FROM UserVisits
)
SELECT 
    user_id,
    MAX(COALESCE(gap, DATEDIFF('2021-1-1', visit_date))) AS biggest_window
FROM visit_gaps
GROUP BY user_id
ORDER BY user_id;

