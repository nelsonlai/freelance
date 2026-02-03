module Fibonacci where
fibonacci :: Integer -> Integer
fibonacci n
  | n < 0     = error "fibonacci: negative input"
  | n == 0    = 0
  | n == 1    = 1
  | otherwise = fibonacci (n - 1) + fibonacci (n - 2)