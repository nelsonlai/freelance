{-|
Module      : Complexity
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Exercises about complexity
-}

module Complexity where

import Prelude hiding (elem, length, head, last, (++))
-- Note that we will be defining many functions that already
-- exist in the Prelude. This flag prevents Haskell from
-- importing them from the Prelude, so we don't need to worry about
-- names clashing, and we can use the same names that the Prelude
-- uses.


{-
Exercise 4

Describe the complexity class of these functions in the best,
worse and average cases.
The first has already been done for you.
-}

-- | Checks if an element is present in a list.
-- best O(1), worst O(n), average O(n)
elem :: (Eq a) => a -> [a] -> Bool
elem e list = case list of
    [] -> False
    x:xs
        |e == x -> True
        |otherwise -> elem e xs

-- | Computes the length of the input list
-- best O(n), worst O(n), average O(n)
length :: [a] -> Integer
length list = case list of
    [] -> 0
    _:xs -> 1 + length xs

-- | Takes in a list, and throws the list away, and returns zero.
-- best O(n), worst O(n), average O(n)
zero :: [a] -> Integer
zero list = case list of
    [] -> 0
    _:xs -> zero xs

-- | Returns the first element in a list
-- best O(1), worst O(1), average O(1)
head :: [a] -> a
head list = case list of
    [] -> error "head: Empty list has no first element"
    x:_ -> x

-- | Returns the last element in a list
-- best O(n), worst O(n), average O(n)
last :: [a] -> a
last list = case list of
    [] -> error "last: Empty list has no last element"
    [x] -> x
    x:xs -> last xs

-- | Takes a list, and removes the duplicate elements
-- best O(n), worst O(n²), average O(n²)
nub :: (Eq a) => [a] -> [a]
nub list = case list of
    [] -> []
    x:xs
        |elem x xs ->  nub xs
        |otherwise -> x : nub xs

-- | Concatenates two lists together
-- best O(n), worst O(n), average O(n)
(++) :: [a] -> [a] -> [a]
xs ++ ys = case xs of  
  [] -> ys
  x:rest -> x : (rest ++ ys)

-- | Reverses a list
-- best O(n²), worst O(n²), average O(n²)
rev1 :: [a] -> [a]
rev1 list = case list of
    [] -> []
    x:xs -> (rev1 xs) ++ [x]

-- | Reverses a list
-- best O(n), worst O(n), average O(n)
rev2 :: [a] -> [a]
rev2 list = revHelper list []
    where
    revHelper list2 acc = case list2 of
        [] -> acc
        x:xs -> revHelper xs (x:acc) 

{-
Exercise 5

Work out the complexity for these functions: fib1, fib2, power.
-}

-- | Computes 2^n deliberately inefficiently
-- best O(2^n), worse O(2^n), average O(2^n)
exp2 :: Integer -> Integer
exp2 n
    |n < 0     = error "exp2: undefined for negative arguments"
    |n == 0    = 1
    |otherwise = exp2 (n - 1) + exp2 (n - 1) 

-- | Computes the fibonacci function
-- best O(2^n), worst O(2^n), average O(2^n)
fib1 :: Integer -> Integer
fib1 n
    |n < 0  = error "fib: undefined for negative arguments"
    |n == 0 = 0
    |n == 1 = 1
    |otherwise = fib1 (n-1) + fib1 (n-2)

-- | Computes the fibonacci function
-- best O(n), worst O(n), average O(n)
fib2 :: Integer -> Integer
fib2 n 
    |n < 0      = error "fib2: undefined for negative arguments"
    |otherwise  = fibHelper n 0 1
        where
        fibHelper 0 curr _    = curr
        fibHelper n2 curr prev = fibHelper (n2-1) (curr + prev) curr

-- | Computes exponentiation via repeated multiplication
-- best O(n), worst O(n), average O(n)
power :: (Num a) => a -> Integer -> a
power base index
    |index < 0 = error "power: negative exponent"
    |index == 0 = 1
    |otherwise = base * (power base (index - 1))

{-
Exercise 6

The power function can be optimised to be faster. 
Use the fact that x^(2n) = (x^n)^2 and x^(2n+1) = (x^n)^2 * x
to write a faster version.

Do not use (**) or (^) to solve this problem.
-}

-- | Optimised exponentiation
-- | Number of multiplications to compute x^n: O(log n)
powerFast :: (Num a) => a -> Integer -> a
powerFast base index
    | index < 0 = error "powerFast: negative exponent"
    | index == 0 = 1
    | index == 1 = base
    | even index = square (powerFast base (index `div` 2))
    | otherwise = base * square (powerFast base (index `div` 2))

-- | A useful helper function that squares a number.
square :: (Num a) => a -> a
square x = x * x

