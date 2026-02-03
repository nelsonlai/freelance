{-|
Module      : Type
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Exercises with types
-}

module Type where

{- 
Exercise 1: (Optional)

Work out the type classes for the following types.
The first one has been done for you.


Integer                 (Integral)
Double                  (?)
Char                    (?)
Bool                    (?)
(Integer, Integer)      (?)
(Integer, Double)       (?)
String                  (?)
[Integer]               (?)
Integer -> Integer      (?)
Maybe Integer           (?)
-}



{-
Exercise 2:

What are the types of these functions?
(Don't just cheat and punch it in GHCi. Try to work it out yourself.)
-}

--cow :: ???
cow :: Bool -> Char -> String -> Bool
cow x y z = x && (elem y z)

--foo :: ???
foo :: Char -> String -> [String] -> Bool
foo x y z = (elem x y) && (elem y z)

--bar :: ???
bar :: Num a => a -> Maybe a -> a
bar x y = case y of
    Nothing -> x
    Just z  -> x + z

-- snap :: ???
snap :: (Show a, Ord a) => a -> a -> String
snap x y
    | x > y = show x
    | otherwise = show y

