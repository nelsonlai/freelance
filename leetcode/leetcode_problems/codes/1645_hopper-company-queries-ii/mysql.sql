-- Problem: Hopper Company Queries II
-- Difficulty: Hard
-- Tags: database

-- Approach: Calculate working drivers and percentage per month
-- Time Complexity: O(n) where n is months
-- Space Complexity: O(n)

WITH RECURSIVE months AS (
    SELECT 1 AS month
    UNION ALL
    SELECT month + 1 FROM months WHERE month < 12
),
working_drivers AS (
    SELECT 
        m.month,
        COUNT(DISTINCT d.driver_id) AS working_drivers
    FROM months m
    LEFT JOIN Drivers d ON YEAR(d.join_date) < 2020 
        OR (YEAR(d.join_date) = 2020 AND MONTH(d.join_date) <= m.month)
    LEFT JOIN AcceptedRides a ON d.driver_id = a.driver_id
    LEFT JOIN Rides r ON a.ride_id = r.ride_id 
        AND YEAR(r.requested_at) = 2020 
        AND MONTH(r.requested_at) = m.month
    WHERE r.ride_id IS NOT NULL
    GROUP BY m.month
),
active_drivers AS (
    SELECT 
        m.month,
        COUNT(DISTINCT d.driver_id) AS active_drivers
    FROM months m
    LEFT JOIN Drivers d ON YEAR(d.join_date) < 2020 
        OR (YEAR(d.join_date) = 2020 AND MONTH(d.join_date) <= m.month)
    GROUP BY m.month
)
SELECT 
    ad.month,
    CASE 
        WHEN ad.active_drivers = 0 THEN 0
        ELSE ROUND(COALESCE(wd.working_drivers, 0) * 100.0 / ad.active_drivers, 2)
    END AS working_percentage
FROM active_drivers ad
LEFT JOIN working_drivers wd ON ad.month = wd.month
ORDER BY ad.month;

