-- Define the myFilter function
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ [] = []  -- Base case: if the list is empty, return an empty list
myFilter f (x:xs)
  | f x       = x : myFilter f xs  -- If the function evaluates to True, include the element
  | otherwise = myFilter f xs      -- Otherwise, skip the element