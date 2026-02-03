-- Define the myFilter function
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ [] = []  -- Base case: if the list is empty, return an empty list
myFilter f (x:xs)
  | f x       = x : myFilter f xs  -- If the function evaluates to True, include the element
  | otherwise = myFilter f xs      -- Otherwise, skip the element

-- Function to filter valid marks (between 0 and 100)
filterMark :: [Integer] -> [Integer]
filterMark = myFilter (\x -> x >= 0 && x <= 100)

-- Function to filter palindromes
filterPalindromes :: [String] -> [String]
filterPalindromes = myFilter (\s -> s == reverse s)

-- Function to filter strings by length
filterByLength :: Int -> [String] -> [String]
filterByLength n = myFilter (\s -> length s >= n)
