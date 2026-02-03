-- Problem: All the Pairs with the Maximum Number of Common Followers
-- Difficulty: Medium
-- Tags: database
-- 
-- Approach: Find pairs of users with maximum common followers
-- Time Complexity: O(n^2 * m) where n is users, m is followers
-- Space Complexity: O(n^2)

SELECT user1_id, user2_id
FROM (
    SELECT 
        r1.user_id AS user1_id,
        r2.user_id AS user2_id,
        COUNT(*) AS common_followers
    FROM Relations r1
    JOIN Relations r2 ON r1.follower_id = r2.follower_id
    WHERE r1.user_id < r2.user_id
    GROUP BY r1.user_id, r2.user_id
) AS pairs
WHERE common_followers = (
    SELECT MAX(common_followers)
    FROM (
        SELECT 
            r1.user_id AS user1_id,
            r2.user_id AS user2_id,
            COUNT(*) AS common_followers
        FROM Relations r1
        JOIN Relations r2 ON r1.follower_id = r2.follower_id
        WHERE r1.user_id < r2.user_id
        GROUP BY r1.user_id, r2.user_id
    ) AS all_pairs
)
ORDER BY user1_id, user2_id;


