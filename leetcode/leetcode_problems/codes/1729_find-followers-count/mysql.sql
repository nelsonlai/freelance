-- Problem: Find Followers Count
-- Difficulty: Easy
-- Tags: database

-- Approach: Count distinct followers per user
-- Time Complexity: O(n) where n is follows
-- Space Complexity: O(1)

SELECT 
    user_id,
    COUNT(DISTINCT follower_id) AS followers_count
FROM Followers
GROUP BY user_id
ORDER BY user_id;

