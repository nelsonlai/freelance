-- Part of Exercise 2.1
-- Define a function that increments and sums elements of nested lists.
sumIncAll :: [[Integer]] -> [Integer]
sumIncAll xss = map (sum . map (+1)) xss
