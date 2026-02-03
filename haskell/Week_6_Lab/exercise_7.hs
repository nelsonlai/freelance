-- Define the riffle function
riffle :: [a] -> [a] -> [a]
riffle [] ys = ys  -- If the first list is empty, return the second list
riffle xs [] = xs  -- If the second list is empty, return the first list
riffle (x:xs) (y:ys) = x : y : riffle xs ys  -- Alternate elements from both lists recursively
