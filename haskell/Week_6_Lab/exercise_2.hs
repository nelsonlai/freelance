-- Part of Exercise 2
-- Define a custom myMap function
myMap :: (a -> b) -> [a] -> [b]
myMap _ [] = []
myMap f (x:xs) = (f x) : myMap f xs

-- Re-define the functions using myMap
incAll :: [Integer] -> [Integer]
incAll = myMap (+1)

negateAll :: [Bool] -> [Bool]
negateAll = myMap not

isLeast100All :: [Integer] -> [Bool]
isLeast100All = myMap (>= 100)
