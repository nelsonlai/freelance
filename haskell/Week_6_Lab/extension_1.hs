-- Define the powerset function
powerset :: [a] -> [[a]]
powerset [] = [[]]  -- Base case: the powerset of an empty list is a list containing an empty list
powerset (x:xs) = let ps = powerset xs
                  in ps ++ map (x:) ps  -- Combine subsets without x and subsets with x