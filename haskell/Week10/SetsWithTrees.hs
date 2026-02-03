{-|
Module      : SetsWithTrees
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Implementing sets using trees
-}

module SetsWithTrees where

import BinaryTree

data Set a = Set (BSTree a)
   deriving Show

{-
Exercise 9

Complete all these functions, and state their complexity class.

Required:   setEquals, 
            addElement, 
            setUnion

Optional:   removeElement, 
            setIntersection, 
            setDifference
-}



-- | Returns the definition for the empty set for this data structure
-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
emptySet :: Set a
emptySet = Set Null


-- | The number of elements in a set.
-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
setSize :: Integral b => Set a -> b
setSize (Set tree) = treeSize tree 


-- | Checks if an element is present in a set
-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
containsElement :: (Ord a) => Set a -> a -> Bool
containsElement (Set tree) = elemBSTree tree


-- | Equality on sets (as lists could be in different order, we want [1,2,3]
-- | to represent the same set as [3,2,1])
-- Balanced tree: best O(n), worst O(n)
-- Any tree:      best O(n), worst O(n)
setEquals :: (Ord a) => Set a -> Set a -> Bool
setEquals (Set tree1) (Set tree2) = flattenTreeOrd tree1 == flattenTreeOrd tree2


-- | Adds an element to a set, if it does not already exist
-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
addElement :: (Ord a) => a -> Set a -> Set a
addElement x (Set tree) = Set (treeInsert tree x)
  

-- | Computes the union of two sets (all the elements in at least one of the two sets)
-- Balanced tree: best O(n log n), worst O(n log n)
-- Any tree:      best O(n log n), worst O(n²)
setUnion :: (Ord a) => Set a -> Set a -> Set a
setUnion (Set tree1) (Set tree2) = 
    let list1 = flattenTreeOrd tree1
        list2 = flattenTreeOrd tree2
        allElements = list1 ++ filter (\x -> not (elem x list1)) list2
        insertAll tree [] = tree
        insertAll tree (x:xs) = insertAll (treeInsert tree x) xs
    in Set (insertAll Null allElements)

-- ===========================================
-- Functions below are optional extensions
-- ===========================================

-- | Removes an element from a set, if it is present
-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
removeElement :: (Ord a) => a -> Set a -> Set a
removeElement = undefined

-- | Computes the intersection of two sets (all the elements in both sets)
-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
setIntersection :: (Ord a) => Set a -> Set a -> Set a
setIntersection = undefined

-- | Computes the set difference (all the elements in the first set, but not the second)
-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
setDifference :: (Ord a) => Set a -> Set a -> Set a
setDifference = undefined


