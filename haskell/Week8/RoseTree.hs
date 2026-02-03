{-|
Module      : RoseTree
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Functions on Rose Trees
-}

module RoseTree where

import Data.Char

data RoseTree a = RoseNode a [RoseTree a]
    deriving (Eq,Show)

data BinaryTree a = Null | Node (BinaryTree a) a (BinaryTree a)
    deriving (Eq,Show)
    
things :: RoseTree String
things = 
    RoseNode "thing" [
        RoseNode "animal" [
            RoseNode "cat" [], RoseNode "dog" []
        ],
        
        RoseNode "metal" [
            RoseNode "alloy" [
                RoseNode "steel" [], RoseNode "bronze" []
            ],
            RoseNode "element" [
                RoseNode "gold" [], RoseNode "tin" [], RoseNode "iron" []
            ]
        ],
        
        RoseNode "fruit" [
            RoseNode "apple" [
                RoseNode "Granny Smith" [], RoseNode "Pink Lady" []
            ],
            RoseNode "banana" [],
            RoseNode "orange" []
        ],

        RoseNode "astronomical object" [
            RoseNode "Planet" [
                RoseNode "Earth" [], RoseNode "Mars" []
            ],
            RoseNode "Star" [
                RoseNode "The Sun" [], RoseNode "Sirius" []
            ],
            RoseNode "Galaxy" [
                RoseNode "Milky Way" []
            ]
        ]
    ] 

{-
Exercise 8: roseSize

Write a function
that counts the number of elements in a rosetree.
-}

roseSize :: RoseTree a -> Int
roseSize (RoseNode _ children) = 1 + sum (map roseSize children) 

{-
Exercise 9: roseLeaves

Write a function
that returns a list of all leaves of the rosetree.
-}

roseLeaves :: RoseTree a -> [a]
roseLeaves (RoseNode x []) = [x]
roseLeaves (RoseNode _ children) = concat (map roseLeaves children)

{-
Exercise 10: roseFlatten

Write a function
that returns a list of all elements in the rosetree.
-}

roseFlatten :: RoseTree a -> [a]
roseFlatten (RoseNode x children) = x : concat (map roseFlatten children)



-- Turns strings into all upper case
allCaps :: String -> String
allCaps x = map toUpper x

{-
Exercise 11: roseMap

Write a function
that takes a function, and applies it to every element of a rosetree.
Test the result by mapping the function `allCaps` to the rosetree `things`.
All the elements should now be written in uppercase.
-}

roseMap :: (a -> b) -> RoseTree a -> RoseTree b
roseMap f (RoseNode x children) = RoseNode (f x) (map (roseMap f) children)

{-
Exercise 12: binaryTreeToRose

Write a function
that converts a binary tree to a rosetree. The new rosetree should
have the same structure as the binary tree.
-}

binaryTreeToRose :: BinaryTree a -> RoseTree a
binaryTreeToRose Null = error "Cannot convert empty binary tree to rose tree"
binaryTreeToRose (Node left x right) = RoseNode x [binaryTreeToRose left, binaryTreeToRose right]
