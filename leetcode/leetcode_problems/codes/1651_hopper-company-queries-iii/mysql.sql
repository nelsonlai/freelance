-- Problem: Hopper Company Queries III
-- Difficulty: Hard
-- Tags: database

-- Approach: Generate month sequence, calculate accepted rides per month
-- Time Complexity: O(n) where n is months
-- Space Complexity: O(n)

WITH RECURSIVE months AS (
    SELECT 1 AS month
    UNION ALL
    SELECT month + 1 FROM months WHERE month < 12
),
accepted_rides AS (
    SELECT 
        MONTH(r.requested_at) AS month,
        COUNT(DISTINCT a.ride_id) AS accepted_rides
    FROM AcceptedRides a
    JOIN Rides r ON a.ride_id = r.ride_id
    WHERE YEAR(r.requested_at) = 2020
    GROUP BY MONTH(r.requested_at)
)
SELECT 
    m.month,
    COALESCE(ar.accepted_rides, 0) AS accepted_rides
FROM months m
LEFT JOIN accepted_rides ar ON m.month = ar.month
ORDER BY m.month;

