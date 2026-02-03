{-|
Module      : SetsWithLists
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Implementing sets using lists
-}

module SetsWithLists where

data Set a = Set [a]
   deriving Show


{-
Exercise 7

Complete the functions setEquals, addElement, setUnion.

Write down the best, worse and average case time complexity for each.

-}


-- | Returns the definition for the empty set for this data structure
-- best O(1), worst O(1), average O(1)
emptySet :: Set a
emptySet = Set []


-- | The number of elements in a set.
-- best O(n), worst O(n), average O(n)
setSize :: Integral b => Set a -> b
setSize (Set list) = case list of
  []    -> 0
  _: xs -> 1 + setSize (Set xs)


-- | Checks if an element is present in a set
-- best O(1), worst O(n), average O(n)
containsElement :: (Eq a) => Set a -> a -> Bool
containsElement (Set list) element = elem element list


-- | Equality on sets (as lists could be in different order, we want [1,2,3]
-- | to represent the same set as [3,2,1])
-- best O(n), worst O(n), average O(n)  
setEquals :: (Eq a) => Set a -> Set a -> Bool
setEquals (Set xs) (Set ys) = all (\x -> elem x ys) xs && all (\y -> elem y xs) ys


-- | Adds an element to a set, if it does not already exist
-- best O(1), worst O(n), average O(n)
addElement :: (Eq a) => a -> Set a -> Set a
addElement x (Set xs)
    | elem x xs = Set xs
    | otherwise = Set (x:xs)

  
-- | Computes the union of two sets (all the elements in at least one of the two sets)
-- best O(n), worst O(n²), average O(n²)
setUnion :: (Eq a) => Set a -> Set a -> Set a
setUnion (Set xs) (Set ys) = Set (xs ++ filter (\y -> not (elem y xs)) ys)


-- ============================================
--  Functions below are Optional Extensions 
-- ============================================


-- | Removes an element from a set, if it is present
-- best O(?), worst O(?), average O(?)
removeElement :: (Eq a) => a -> Set a -> Set a 
removeElement = undefined

-- | Computes the intersection of two sets (all the elements in both sets)
-- best O(?), worst O(?), average O(?)
setIntersection :: (Eq a) => Set a -> Set a -> Set a 
setIntersection = undefined

-- | Computes the set difference (all the elements in the first set, but not the second)
-- best O(?), worst O(?), average O(?)
setDifference :: (Eq a) => Set a -> Set a -> Set a 
setDifference = undefined




