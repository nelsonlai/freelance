-- Problem: Percentage of Users Attended a Contest
-- Difficulty: Easy
-- Tags: database

-- Approach: Calculate percentage of users who registered for each contest
-- Time Complexity: O(n * m) where n is contests, m is registrations
-- Space Complexity: O(1)

SELECT contest_id,
       ROUND(COUNT(DISTINCT user_id) * 100.0 / (SELECT COUNT(*) FROM Users), 2) AS percentage
FROM Register
GROUP BY contest_id
ORDER BY percentage DESC, contest_id ASC;

