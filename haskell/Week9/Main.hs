module Main where

import DrawTree (printTree)
import BST
import Nat
import Type
import Fruit

main :: IO ()
main = do
    putStrLn "--- goodTree (draw) ---"
    printTree goodTree

    putStrLn "--- flattenTreeOrd goodTree ---"
    print $ flattenTreeOrd goodTree

    putStrLn "--- elemBSTree 13 in goodTree ---"
    print $ elemBSTree 13 goodTree

    putStrLn "--- treeBSMax and treeBSMin goodTree ---"
    print $ (treeBSMax goodTree, treeBSMin goodTree)

    putStrLn "--- insert 14 into goodTree and flatten ---"
    let t' = treeInsert goodTree 14
    print $ flattenTreeOrd t'

    putStrLn "--- isBSTree checks ---"
    print $ isBSTree goodTree
    print $ isBSTree notBSTree

    putStrLn "--- smallTree examples ---"
    printTree smallTree
    print $ elemBSTree (5 :: Integer) smallTree

    putStrLn "--- Nat examples ---"
    print $ (S (S Z) == S (S Z))
    print $ (S Z <= S (S Z))

    putStrLn "--- Type examples ---"
    print $ cow True 'a' "abc"
    print $ foo 'a' "abc" ["abc","def"]

    putStrLn "--- Fruit ordering sample ---"
    print $ (Apple <= Banana, Orange <= Apple)
