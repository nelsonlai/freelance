-- Problem: Count Apples and Oranges
-- Difficulty: Medium
-- Tags: database

-- Approach: Sum boxes with apple and orange, filter by date
-- Time Complexity: O(n) where n is boxes
-- Space Complexity: O(1)

SELECT 
    SUM(CASE WHEN box_id IN (SELECT box_id FROM Boxes WHERE apple_count > 0) THEN apple_count ELSE 0 END) AS apple_count,
    SUM(CASE WHEN box_id IN (SELECT box_id FROM Boxes WHERE orange_count > 0) THEN orange_count ELSE 0 END) AS orange_count
FROM Boxes b
JOIN Chests c ON b.chest_id = c.chest_id
WHERE b.box_id IN (
    SELECT box_id FROM Boxes WHERE apple_count > 0 OR orange_count > 0
);

