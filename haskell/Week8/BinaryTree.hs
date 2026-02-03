{-|
Module      : BinaryTree
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Functions on Binary Trees
-}

module BinaryTree where
    
import DrawTree

data BinaryTree a = Null | Node (BinaryTree a) a (BinaryTree a)
  deriving Show

tree1 :: BinaryTree Integer
tree1 = Node (Node (Node Null 2 (Node Null 11 Null)) 4 (Node (Node Null 0 Null) 
    1 (Node Null (-3) Null))) 5 (Node (Node (Node Null (-4) Null) 8 
    (Node Null 7 Null)) 3 Null)

{-
Exercise 1: treeSize

Counts the number of elements in a tree
-}

treeSize :: BinaryTree a -> Int
treeSize Null = 0
treeSize (Node left _ right) = 1 + treeSize left + treeSize right

{-
Exercise 2: treeDepth

Write a function that computes the depth of a tree, which is defined as
the length of the longest path from the root node down to any leaf.
-}

treeDepth :: BinaryTree a -> Int
treeDepth Null = 0 
treeDepth (Node Null _ Null)= 0 
treeDepth (Node left _ right) = 1 + max (treeDepth left) (treeDepth right)


{-
Exercise 3: leavesTree

Write a function that takes a tree, and returns a list containing
only the elements in leaf nodes.
-}

leavesTree :: BinaryTree a -> [a]
leavesTree Null  = []
leavesTree (Node Null x Null) = [x]
leavesTree (Node left _ right) = (leavesTree left) ++ (leavesTree right) 


{-
Exercise 4: treeMap

Write a function that works analogously to `map`, by applying a function
to each node in a tree.
-}

treeMap :: (a -> b) -> (BinaryTree a) -> (BinaryTree b)
treeMap _ Null = Null
treeMap f (Node left x right) = Node (treeMap f left) (f x) (treeMap f right)

{-
Exercise 5: elemTree

Write a function that takes an `Integer`, and checks if it is
present inside a tree of `Integer`'s.
-}

elemTree :: Integer -> (BinaryTree Integer) -> Bool
elemTree _ Null = False
elemTree x (Node left value right) 
  | x  == value = True
  | otherwise = (elemTree x left) || (elemTree x right)




{- 
Exercise 6: treeMaximum

Write two functions, to find the minimum and maximum element in a tree
of type `Integer`.
-}

treeMaximum :: BinaryTree Integer -> Integer
treeMaximum t = case t of 
  Null -> error  " none "
  Node Null x Null -> x
  Node Null x right -> max x (treeMaximum right) 
  Node left x Null -> max x (treeMaximum left) 
  Node left value right -> maximum [value, treeMaximum left, treeMaximum right]

  
treeMinimum :: BinaryTree Integer -> Integer

treeMinimum t =  case t of 
  Null -> error  " none "
  Node Null x Null -> x
  Node Null x right -> min x (treeMinimum right) 
  Node left x Null -> min x (treeMinimum left) 
  Node left value right -> minimum [value, treeMinimum left, treeMinimum right]

  



{-
Exercise 7: flattentree

Write a function that takes a tree, and returns a list containing
all the elements from that tree. We call such an operation **flattening**
a tree.
-}

flattenTree :: BinaryTree a -> [a]
flattenTree Null = []
flattenTree (Node left x right) = flattenTree left ++ [x] ++ flattenTree right

