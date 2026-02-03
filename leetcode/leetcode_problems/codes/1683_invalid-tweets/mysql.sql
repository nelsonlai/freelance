-- Problem: Invalid Tweets
-- Difficulty: Easy
-- Tags: database

-- Approach: Filter tweets with content length > 15
-- Time Complexity: O(n) where n is tweets
-- Space Complexity: O(1)

SELECT tweet_id
FROM Tweets
WHERE CHAR_LENGTH(content) > 15;

