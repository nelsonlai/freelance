-- Exercise 1: sum all non-negative integers up to and including n.
module IntegerRecursion where

sumNumbers :: Integer -> Integer
sumNumbers n
  | n <= 0    = 0                 -- base case (also handles negatives safely)
  | otherwise = n + sumNumbers (n - 1)

-- Exercise 2: report an error on invalid (negative) inputs
module IntegerRecursion where

sumNumbers :: Integer -> Integer
sumNumbers n
  | n < 0     = error "sumNumbers: negative input"
  | n == 0    = 0
  | otherwise = n + sumNumbers (n - 1)

factorial :: Integer -> Integer
factorial n
  | n < 0     = error "factorial: negative input"
  | n == 0    = 1
  | otherwise = n * factorial (n - 1)

-- Exercise 3: sum all integers from the first to the second, inclusive.
module RangeSums where

rangeSum :: Integer -> Integer -> Integer
rangeSum a b
  | a == b    = a                   -- base case
  | otherwise = a + rangeSum (a+1) b

-- Exercise 4: sum all integers from the first to the second,
-- inclusive of the first, exclusive of the second: sum [a .. b)
module RangeSums where

rangeSumEx :: Integer -> Integer -> Integer
rangeSumEx a b
  | a == b    = 0
  | a > b     = rangeSumEx b a        -- handle reversed inputs safely
  | otherwise = a + rangeSumEx (a + 1) b

-- Exercise 5: nth Fibonacci number (F0 = 0, F1 = 1)
module Fibonacci where
fibonacci :: Integer -> Integer
fibonacci n
  | n < 0     = error "fibonacci: negative input"
  | n == 0    = 0
  | n == 1    = 1
  | otherwise = fibonacci (n - 1) + fibonacci (n - 2)

-- Example check:
--  fibonacci 30  == 832040

-- Exercise 6 — All
module ListRecursion where

-- (given earlier) repeat a character n times
copy :: Integer -> Char -> String
copy n c
  | n < 0     = error "copy: negative input"
  | n == 0    = []
  | otherwise = c : copy (n - 1) c

-- Exercise 6 — Task 1
-- Return a string of c’s that is length 2n.
copy2 :: Integer -> Char -> String
copy2 n c
  | n < 0     = error "copy2: negative input"
  | otherwise = copy (2 * n) c

-- Exercise 6 — Task 2
-- List all integers from n to m inclusive, in ascending order.
-- If n > m there are no values, so return [] (and avoid infinite loops).
rangeList :: Integer -> Integer -> [Integer]
rangeList n m
  | n > m     = []
  | n == m    = [n]
  | otherwise = n : rangeList (n + 1) m

-- Exercise 7: count how many numbers are in the list
module ListFunctions where

lengthList :: [Integer] -> Integer
lengthList []     = 0
lengthList (_:xs) = 1 + lengthList xs

-- Exercise 8

module ListFunctions where

firstList :: [Integer] -> Integer
firstList []    = error "firstList: empty list"
firstList (x:_) = x

lastList :: [Integer] -> Integer
lastList []     = error "lastList: empty list"
lastList [x]    = x
lastList (_:xs) = lastList xs

-- Exercise 9
module StringOps where

-- Put a character at the front of a string
prepend :: Char -> String -> String
prepend ch s = ch : s

-- Put a character at the end of a string (recursive)
append :: Char -> String -> String
append ch []     = [ch]
append ch (x:xs) = x : append ch xs
-- (equivalently: append ch s = s ++ [ch])

-- Exercise 10

module Swap where

-- Swap the first two integers in a list, if they exist.
swapFirstTwo :: [Integer] -> [Integer]
swapFirstTwo []        = []
swapFirstTwo [x]       = [x]
swapFirstTwo (x:y:xs)  = y : x : xs
-- [9, 5, 2, 7, 6] [x:y:xs] <-> x = 9, y = 5, xs = [2, 7, 6]  y : x : xs <-> [5, 9, 2, 7, 6]

-- Swap the last two integers in a list, if they exist.
swapLastTwo :: [Integer] -> [Integer]
swapLastTwo []         = []
swapLastTwo [x]        = [x]
swapLastTwo [x,y]      = [y,x]
swapLastTwo (x:xs)     = x : swapLastTwo xs

-- [9, 5, 2, 7, 6] [x:xs] <-> x = 9, xs = [5, 2, 7, 6]

-- Exercise 11: check whether an Integer is in a list
module Find where

find :: Integer -> [Integer] -> Bool
find _ []     = False
find n (x:xs) = n == x || find n xs

-- Exercise 12
module ListSlice where

-- Task 1: takeList
-- Take the first n elements (Integer) of a list of Integer.
-- If n <= 0 → [], if list shorter than n → return whole list.
takeList :: Integer -> [Integer] -> [Integer]
takeList n _      | n <= 0 = []
takeList _ []                = []
takeList n (x:xs)            = x : takeList (n - 1) xs

-- Task 2: dropList
-- Drop the first n elements. If n <= 0 → return list unchanged.
-- If list shorter than n → [].
dropList :: Integer -> [Integer] -> [Integer]
dropList n xs     | n <= 0 = xs
dropList _ []                = []
dropList n (_:xs)            = dropList (n - 1) xs


module ListSlice where

-- (from Exercise 12)
takeList :: Integer -> [Integer] -> [Integer]
takeList n _      | n <= 0 = []
takeList _ []                = []
takeList n (x:xs)            = x : takeList (n - 1) xs

dropList :: Integer -> [Integer] -> [Integer]
dropList n xs   | n <= 0 = xs
dropList _ []              = []
dropList n (_:xs)          = dropList (n - 1) xs

-- Exercise 13: sublist starting at index m with n elements
subList :: Integer -> Integer -> [Integer] -> [Integer]
subList m n xs
  | n <= 0    = []
  | otherwise = takeList n (dropList m xs)

-- subList 2 4 [1,2,3,4,5, 6, 7, 8, 9] -> [3,4,5,6]
module Grid where

-- Extension 1: list all coordinates from (1,1) to (x,y)
gridList :: Integer -> Integer -> [(Integer, Integer)]
gridList x y
  | x <= 0 || y <= 0 = []
  | otherwise        = gridList x (y - 1) ++ row x y
  where
    -- all (i,y) for i = 1..x
    row :: Integer -> Integer -> [(Integer,Integer)]
    row n j
      | n <= 0    = []
      | otherwise = row (n - 1) j ++ [(n, j)]
-- gridList 3 3 -> [(1,1),(2,1),(3,1),(1,2),(2,2),(3,2),(1,3),(2,3),(3,3)]
-- gridList 2 4 -> [(1,1),(2,1),(1,2),(2,2),(1,3),(2,3),(1,4),(2,4)]

----------------------------
module Fibonacci1 where

-- Extension 2: Fast Fibonacci (fast-doubling, O(log n))
fastFib :: Integer -> Integer
fastFib n
  | n < 0     = error "fastFib: negative input"
  | otherwise = fst (fib n)
  where
    -- fib k returns (F_k, F_{k+1})
    fib :: Integer -> (Integer, Integer)
    fib 0 = (0, 1)
    fib k =
      let (a, b) = fib (k `div` 2)         -- a = F_m, b = F_{m+1}, where m = k/2
          c      = a * (2*b - a)           -- F_{2m}
          d      = a*a + b*b               -- F_{2m+1}
      in if even k then (c, d) else (d, c + d)

-- Example: fastFib 30 == 832040