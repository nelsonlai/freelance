-- Problem: Grand Slam Titles
-- Difficulty: Medium
-- Tags: database

-- Approach: UNION ALL all tournaments, then COUNT and GROUP BY
-- Time Complexity: O(n) where n is total matches
-- Space Complexity: O(n)

SELECT 
    player_id,
    player_name,
    SUM(
        CASE WHEN tournament = 'Wimbledon' THEN 1 ELSE 0 END +
        CASE WHEN tournament = 'Fr Open' THEN 1 ELSE 0 END +
        CASE WHEN tournament = 'US Open' THEN 1 ELSE 0 END +
        CASE WHEN tournament = 'Au Open' THEN 1 ELSE 0 END
    ) AS grand_slams_count
FROM (
    SELECT player_id, player_name, 'Wimbledon' AS tournament FROM Championships
    UNION ALL
    SELECT player_id, player_name, 'Fr Open' AS tournament FROM Championships
    UNION ALL
    SELECT player_id, player_name, 'US Open' AS tournament FROM Championships
    UNION ALL
    SELECT player_id, player_name, 'Au Open' AS tournament FROM Championships
) AS all_tournaments
GROUP BY player_id, player_name
HAVING grand_slams_count > 0;

