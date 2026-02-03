{-|
Module      : BST
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Binary Search Tree exercises 
-}

module BST where

import DrawTree

-- ======= BINARY SEARCH TREES =========

-- data BinaryTree a = Null | Node (BinaryTree a) a (BinaryTree a)
--     deriving Show

type BSTree a = BinaryTree a

-- A graphical representation of 'notBSTree'
--
--        5
--      /   \
--     3     7
--    / \   / \
--   1   2 6   9 
--
-- Question: Why isn't this a binary search tree?

notBSTree :: BinaryTree Integer
notBSTree = Node (Node (Node Null 1 Null) 3 (Node Null 2 Null))
                    5
                 (Node (Node Null 6 Null) 7 (Node Null 9 Null))

-- A graphical representation of 'goodTree'                 
--
--                           15
--                          /  \
--                         /    \
--                        /      \ 
--                       /        \
--                      /          \
--                     7           23        
--                    / \         /  \
--                   /   \       /    \
--                  3    12     17    26  
--                 / \   / \   /  \   / \
--                1   5 10 13 16  18 25 31     
--
--  Question: Why is this a valid binary search tree?

goodTree :: BSTree Integer
goodTree =  Node 
                (Node
                    (Node 
                        (Node 
                                Null 
                            1 
                                Null) 
                    3 
                        (Node 
                                Null 
                            5 
                                Null))
                7
                    (Node   
                        (Node 
                                Null 
                            10 
                                Null) 
                    12 
                        (Node 
                                Null 
                            13 
                                Null)))
            15

                (Node 
                    (Node
                        (Node 
                                Null 
                            16 
                                Null) 
                    17 
                        (Node 
                                Null 
                            18 
                                Null))
                23
                    (Node
                        (Node 
                                Null 
                            25 
                                Null) 
                    26 
                        (Node 
                                Null 
                            31 
                                Null)))

-- A graphical representation of 'unbalancedTree':
--
--                        3
--                       / \
--                      1   7 
--                         / \
--                        5  12
--                          /  \
--                         10  15
--                            /  \
--                           13  17
--                              /  \ 
--                             16  23
--                                /  \
--                               18  26
--                                  /  \
--                                 25  31 
--
--  Question: Why is this tree unbalanced?

unbalancedTree :: BSTree Integer
unbalancedTree = Node (Node Null 1 Null) 3
            (Node (Node Null 5 Null) 7
                (Node (Node Null 10 Null) 12
                    (Node (Node Null 13 Null) 15
                        (Node (Node Null 16 Null) 17
                            (Node (Node Null 18 Null) 23
                                (Node (Node Null 25 Null) 26
                                        (Node Null 31 Null)))))))


-- A graphical representation of 'smallTree':
--
--                   5
--                  / \
--                 1  10

smallTree :: BSTree Integer
smallTree = Node (Node Null 1 Null) 5 (Node Null 10 Null)

{-
Exercise 4: elemBSTree

Rewrite the `elemTree` function from Lab 9 before, but this time you may assume
that the input tree satisfies the binary search ordering constraint. Do
not use the same function as before, you should be able to search more
efficiently, as we did in the example above.

-}

elemBSTree :: (Ord a) => a -> (BSTree a) -> Bool
elemBSTree _ Null = False
elemBSTree v (Node left x right)
    | v == x = True
    | v < x  = elemBSTree v left
    | otherwise = elemBSTree v right

{-
Exercise 5: treeBSMax

Rewrite the `treeMaximum` and `treeMinimum` functions, again assuming
the input tree is a binary search tree. Be efficient!
-}

treeBSMax :: (Ord a) => BSTree a -> a
treeBSMax Null = error "treeBSMax: empty tree"
treeBSMax (Node _ x Null) = x
treeBSMax (Node _ _ right) = treeBSMax right

treeBSMin :: (Ord a) => BSTree a -> a
treeBSMin Null = error "treeBSMin: empty tree"
treeBSMin (Node Null x _) = x
treeBSMin (Node left _ _) = treeBSMin left

{-
Exercise 6: isBSTree

Write a function 
that takes a `BinaryTree Integer` as input, and checks if the
binary search constraint holds.
-}

isBSTree :: (Ord a) => BinaryTree a -> Bool
isBSTree t = isBSTreeBetween t Nothing Nothing

-- Helper: check all nodes are within optional (min, max) bounds
isBSTreeBetween :: (Ord a) => BinaryTree a -> Maybe a -> Maybe a -> Bool
isBSTreeBetween Null _ _ = True
isBSTreeBetween (Node left x right) lo hi = within && leftOk && rightOk
    where
        within = case lo of
                Nothing -> True
                Just l -> l < x || l == x
            && case hi of
                Nothing -> True
                Just h -> x < h || x == h
        leftOk = isBSTreeBetween left lo (Just x)
        rightOk = isBSTreeBetween right (Just x) hi

{-
Exercise 7: treeInsert

Write a function that takes a binary search tree, and an element, and inserts
that element into the tree, ensuring the binary search property still holds.
(If the element is already in the tree, leave the tree unchanged.)
-}

treeInsert :: (Ord a) => BSTree a -> a -> BSTree a
treeInsert Null v = Node Null v Null
treeInsert (Node left x right) v
    | v == x = Node left x right
    | v < x  = Node (treeInsert left v) x right
    | otherwise = Node left x (treeInsert right v)

{-      
Exercise 8: flattenTreeOrd

Write a function
that flattens a binary search tree, but preserves the ordering.
(That is, when a binary search tree is flattened, the resulting list
should be sorted.)
-}

flattenTreeOrd :: BSTree a -> [a]
flattenTreeOrd Null = []
flattenTreeOrd (Node left x right) = flattenTreeOrd left ++ [x] ++ flattenTreeOrd right


