-- Problem: Number of Calls Between Two Persons
-- Difficulty: Medium
-- Tags: database

-- Approach: Count calls between two persons (order person1 < person2)
-- Time Complexity: O(n) where n is calls
-- Space Complexity: O(1)

SELECT 
    LEAST(from_id, to_id) AS person1,
    GREATEST(from_id, to_id) AS person2,
    COUNT(*) AS call_count,
    SUM(duration) AS total_duration
FROM Calls
GROUP BY LEAST(from_id, to_id), GREATEST(from_id, to_id);

