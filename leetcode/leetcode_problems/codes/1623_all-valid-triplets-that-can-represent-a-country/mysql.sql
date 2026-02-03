-- Problem: All Valid Triplets That Can Represent a Country
-- Difficulty: Easy
-- Tags: database

-- Approach: Find all valid triplets from three tables using JOINs
-- Time Complexity: O(n * m * k) where n, m, k are table sizes
-- Space Complexity: O(1)

SELECT a.student_name AS member_a,
       b.student_name AS member_b,
       c.student_name AS member_c
FROM SchoolA a
CROSS JOIN SchoolB b
CROSS JOIN SchoolC c
WHERE a.student_id != b.student_id
  AND b.student_id != c.student_id
  AND a.student_id != c.student_id
  AND a.student_name != b.student_name
  AND b.student_name != c.student_name
  AND a.student_name != c.student_name;

