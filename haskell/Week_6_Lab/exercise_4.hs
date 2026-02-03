-- Define the myAny function
myAny :: (a -> Bool) -> [a] -> Bool
myAny _ [] = False  -- Base case: empty list returns False
myAny f (x:xs)
  | f x       = True  -- If the function evaluates to True for any element, return True
  | otherwise = myAny f xs  -- Otherwise, check the rest of the list

-- Define the myAll function
myAll :: (a -> Bool) -> [a] -> Bool
myAll _ [] = True  -- Base case: empty list returns True
myAll f (x:xs)
  | f x       = myAll f xs  -- If the function evaluates to True for the current element, check the rest
  | otherwise = False  -- If any element fails the condition, return False
  