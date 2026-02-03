-- Problem: Hopper Company Queries I
-- Difficulty: Hard
-- Tags: database

-- Approach: Generate month sequence, calculate active drivers and accepted rides per month
-- Time Complexity: O(n) where n is months
-- Space Complexity: O(n)

WITH RECURSIVE months AS (
    SELECT 1 AS month
    UNION ALL
    SELECT month + 1 FROM months WHERE month < 12
),
active_drivers AS (
    SELECT 
        m.month,
        COUNT(DISTINCT d.driver_id) AS active_drivers
    FROM months m
    LEFT JOIN Drivers d ON YEAR(d.join_date) < 2020 
        OR (YEAR(d.join_date) = 2020 AND MONTH(d.join_date) <= m.month)
    GROUP BY m.month
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
    ad.month,
    ad.active_drivers,
    COALESCE(ar.accepted_rides, 0) AS accepted_rides
FROM active_drivers ad
LEFT JOIN accepted_rides ar ON ad.month = ar.month
ORDER BY ad.month;

