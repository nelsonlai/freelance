-- Problem: Accepted Candidates From the Interviews
-- Difficulty: Medium
-- Tags: database
-- 
-- Approach: Join Candidates and Rounds, filter by score requirements
-- Time Complexity: O(n * m) where n is candidates, m is rounds
-- Space Complexity: O(n + m)

SELECT c.candidate_id
FROM Candidates c
INNER JOIN Rounds r ON c.interview_id = r.interview_id
WHERE c.years_of_exp >= 2
GROUP BY c.candidate_id
HAVING SUM(r.score) > 15;



