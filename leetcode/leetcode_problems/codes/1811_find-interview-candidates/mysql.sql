-- Problem: Find Interview Candidates
-- Difficulty: Medium
-- Tags: database

-- Approach: Find users who scored 100 in at least one contest and participated in at least 3 contests
-- Time Complexity: O(n) where n is contests
-- Space Complexity: O(1)

WITH GoldMedalists AS (
    SELECT contest_id, user_id
    FROM Contests
    WHERE gold_medal = user_id
),
SilverMedalists AS (
    SELECT contest_id, user_id
    FROM Contests
    WHERE silver_medal = user_id
),
BronzeMedalists AS (
    SELECT contest_id, user_id
    FROM Contests
    WHERE bronze_medal = user_id
),
PerfectScores AS (
    SELECT DISTINCT user_id
    FROM (
        SELECT gold_medal AS user_id FROM Contests
        UNION ALL
        SELECT silver_medal AS user_id FROM Contests
        UNION ALL
        SELECT bronze_medal AS user_id FROM Contests
    ) AS all_participants
    GROUP BY user_id
    HAVING COUNT(DISTINCT contest_id) >= 3
)
SELECT name, mail
FROM Users
WHERE user_id IN (
    SELECT user_id FROM PerfectScores
    UNION
    SELECT user_id FROM GoldMedalists
    GROUP BY user_id
    HAVING COUNT(DISTINCT contest_id) >= 3
)
ORDER BY user_id;

