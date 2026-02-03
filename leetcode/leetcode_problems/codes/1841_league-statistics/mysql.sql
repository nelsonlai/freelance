-- Problem: League Statistics
-- Difficulty: Medium
-- Tags: database

-- Approach: Calculate statistics for each team
-- Time Complexity: O(n) where n is matches
-- Space Complexity: O(1)

SELECT 
    team_name,
    COUNT(*) AS matches_played,
    SUM(CASE WHEN team_goals > opponent_goals THEN 3
             WHEN team_goals = opponent_goals THEN 1
             ELSE 0 END) AS points,
    SUM(team_goals) AS goal_for,
    SUM(opponent_goals) AS goal_against,
    SUM(team_goals) - SUM(opponent_goals) AS goal_diff
FROM (
    SELECT home_team_id AS team_id, home_team_goals AS team_goals, 
           away_team_goals AS opponent_goals
    FROM Matches
    UNION ALL
    SELECT away_team_id AS team_id, away_team_goals AS team_goals,
           home_team_goals AS opponent_goals
    FROM Matches
) AS team_stats
JOIN Teams ON team_stats.team_id = Teams.team_id
GROUP BY team_name
ORDER BY points DESC, goal_diff DESC, team_name;

