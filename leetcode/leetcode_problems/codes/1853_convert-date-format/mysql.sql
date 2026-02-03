-- Problem: Convert Date Format
-- Difficulty: Easy
-- Tags: database

-- Approach: Use DATE_FORMAT to convert date format
-- Time Complexity: O(n) where n is rows
-- Space Complexity: O(1)

SELECT 
    DATE_FORMAT(day, '%W, %M %e, %Y') AS day
FROM Days;

