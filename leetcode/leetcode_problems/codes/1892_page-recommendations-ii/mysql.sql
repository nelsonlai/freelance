-- Problem: Page Recommendations II
-- Difficulty: Hard
-- Tags: database

-- Approach: Find mutual friends and recommend pages they liked
-- Time Complexity: O(n * m) where n is users, m is pages
-- Space Complexity: O(n * m)

WITH Friends AS (
    SELECT user1_id AS user_id, user2_id AS friend_id FROM Friendship
    UNION
    SELECT user2_id AS user_id, user1_id AS friend_id FROM Friendship
),
RecommendedPages AS (
    SELECT DISTINCT f.user_id, l.page_id
    FROM Friends f
    JOIN Likes l ON f.friend_id = l.user_id
    WHERE NOT EXISTS (
        SELECT 1 FROM Likes l2
        WHERE l2.user_id = f.user_id AND l2.page_id = l.page_id
    )
)
SELECT 
    user_id,
    page_id,
    COUNT(*) AS friends_likes
FROM RecommendedPages
GROUP BY user_id, page_id
ORDER BY user_id, friends_likes DESC, page_id;

