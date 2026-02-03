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