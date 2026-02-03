-- Define the join function
join :: [a] -> [a] -> [a]
join [] ys = ys  -- Base case: if the first list is empty, return the second list
join (x:xs) ys = x : join xs ys  -- Recursively prepend elements of the first list to the second list
