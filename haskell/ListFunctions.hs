module ListFunctions where

lengthList :: [Integer] -> Integer
lengthList []     = 0
lengthList (_:xs) = 1 + lengthList xs