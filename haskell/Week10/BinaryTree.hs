{-|
Module      : BinaryTree
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Complexity with Binary Trees 
-}

module BinaryTree where

type BSTree a = BinaryTree a

data BinaryTree a = Null | Node (BinaryTree a) a (BinaryTree a)
    deriving (Eq,Show)


{-
Exercise 8

Copy in your solutions from Lab 8 and Lab 9
(or finish them off if you haven't)

State the complexity class of each function.
They should be written as efficiently as possible.
-}

-- Copy in your solutions from Lab 8
-- Check the type signature of the original function implementation
-- against the type signature in the current file.

-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
treeSize :: Integral b => BinaryTree a -> b
treeSize tree = case tree of
    Null -> 0
    Node left _ right -> 1 + treeSize left + treeSize right

-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
treeDepth :: Integral b => BinaryTree a -> b
treeDepth tree = case tree of
    Null -> 0
    Node left _ right -> 1 + max (treeDepth left) (treeDepth right)

-- Balanced tree: best O(n), worst O(n)
-- Any tree:      best O(n), worst O(n)
leavesTree :: BinaryTree a -> [a]
leavesTree tree = case tree of
    Null -> []
    Node Null x Null -> [x]
    Node left x right -> leavesTree left ++ leavesTree right

-- Balanced tree: best O(n), worst O(n)
-- Any tree:      best O(n), worst O(n)
treeMap :: (a -> b) -> (BinaryTree a) -> (BinaryTree b)
treeMap f tree = case tree of
    Null -> Null
    Node left x right -> Node (treeMap f left) (f x) (treeMap f right)

-- Balanced tree: best O(n), worst O(n)
-- Any tree:      best O(n), worst O(n)
flattenTree :: BinaryTree a -> [a]
flattenTree tree = case tree of
    Null -> []
    Node left x right -> flattenTree left ++ [x] ++ flattenTree right


-- Copy in your solutions from Lab 9
-- You may need to edit the order of inputs compared to the 
-- original implementation in Lab 9

-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
elemBSTree :: (Ord a) =>  (BSTree a) -> a -> Bool
elemBSTree tree x = case tree of
    Null -> False
    Node left y right
        | x == y -> True
        | x < y -> elemBSTree left x
        | otherwise -> elemBSTree right x

-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
treeBSMax :: (Ord a) => BSTree a -> a
treeBSMax tree = case tree of
    Null -> error "treeBSMax: empty tree"
    Node left x Null -> x
    Node left x right -> treeBSMax right

-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
treeBSMin :: (Ord a) => BSTree a -> a
treeBSMin tree = case tree of
    Null -> error "treeBSMin: empty tree"
    Node Null x right -> x
    Node left x right -> treeBSMin left

-- Balanced tree: best O(n), worst O(n)
-- Any tree:      best O(n), worst O(n)
isBSTree :: (Ord a) => BinaryTree a -> Bool
isBSTree tree = case tree of
    Null -> True
    Node Null x Null -> True
    Node Null x right -> isBSTree right && all (x <) (flattenTree right)
    Node left x Null -> isBSTree left && all (x >) (flattenTree left)
    Node left x right -> isBSTree left && isBSTree right &&
                        all (x >) (flattenTree left) &&
                        all (x <) (flattenTree right)

-- Balanced tree: best O(log n), worst O(log n)
-- Any tree:      best O(log n), worst O(n)
treeInsert :: (Ord a) => BSTree a -> a -> BSTree a
treeInsert tree x = case tree of
    Null -> Node Null x Null
    Node left y right
        | x < y -> Node (treeInsert left x) y right
        | x > y -> Node left y (treeInsert right x)
        | otherwise -> tree  -- element already exists

-- Balanced tree: best O(n), worst O(n)
-- Any tree:      best O(n), worst O(n)
flattenTreeOrd :: BSTree a -> [a]
flattenTreeOrd tree = case tree of
    Null -> []
    Node left x right -> flattenTreeOrd left ++ [x] ++ flattenTreeOrd right 


-- =======================================
-- Functions below are optional extensions
-- =======================================

-- If you haven't implemented treeDelete or treeBalance
-- don't worry about it.

-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
treeDelete :: (Ord a) => (BSTree a) -> a -> (BSTree a)
treeDelete = undefined

-- Balanced tree: best O(?), worst O(?)
-- Any tree:      best O(?), worst O(?)
treeBalance :: (Ord a) => BSTree a -> BSTree a
treeBalance = undefined


{-
Module for drawing nice looking trees
David Quarel 13/02/2019

Don't worry too much about how this works,
or the types of these functions.
It's beyond the scope of this course.

Code modified from
http://hackage.haskell.org/package/containers-0.5.7.1/docs/src/Data.Tree.html#drawTree
-}

printTree :: (Show a) => BinaryTree a -> IO ()
printTree = putStr.unlines.draw

draw :: (Show a) => BinaryTree a -> [String]
draw Null = ["Null"]
draw (Node left x right) = (show x) : drawSubTrees [right,left]
  where
    drawSubTrees [] = []
    drawSubTrees [t] =
        "|" : shift "`- " "   " (draw t)
    drawSubTrees (t:ts) =
        "|" : shift "+- " "|  " (draw t) ++ drawSubTrees ts

    shift first other = zipWith (++) (first : repeat other)


notBSTree :: BinaryTree Integer
notBSTree = Node (Node (Node Null 1 Null) 3 (Node Null 2 Null))
                    5
                 (Node (Node Null 6 Null) 7 (Node Null 9 Null))

-- I've tried my best to textually display the tree in a nice way
-- Sorry if it's more confusing now

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

unbalancedTree :: BSTree Integer
unbalancedTree = Node (Node Null 1 Null) 3
            (Node (Node Null 5 Null) 7
                (Node (Node Null 10 Null) 12
                    (Node (Node Null 13 Null) 15
                        (Node (Node Null 16 Null) 17
                            (Node (Node Null 18 Null) 23
                                (Node (Node Null 25 Null) 26
                                        (Node Null 31 Null)))))))

smallTree :: BSTree Integer
smallTree = Node (Node Null 1 Null) 5 (Node Null 10 Null)

