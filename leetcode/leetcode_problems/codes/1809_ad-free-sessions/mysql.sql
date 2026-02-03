-- Problem: Ad-Free Sessions
-- Difficulty: Easy
-- Tags: database

-- Approach: Find sessions that don't have any ads
-- Time Complexity: O(n) where n is sessions
-- Space Complexity: O(1)

SELECT DISTINCT session_id
FROM Playback
WHERE session_id NOT IN (
    SELECT DISTINCT session_id
    FROM Ads
    WHERE timestamp BETWEEN start_time AND end_time
);

