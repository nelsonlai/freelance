-- Define a compose function that evaluates the composition of two functions, given an input.
compose :: (b -> c) -> (a -> b) -> a -> c
compose f g x = f (g x)

-- Given functions
square :: Integer -> Integer
square x = x^2

inc :: Integer -> Integer
inc x = x + 1

-- Computes the function f(x) = (x+1)^2
incThenSquare :: Integer -> Integer
incThenSquare = compose square inc

-- Computes the function f(x) = x^2 + 1
squareThenInc :: Integer -> Integer
squareThenInc = compose inc square

-- Computes the function f(x) = x+2
add2 :: Integer -> Integer
add2 = compose inc inc

-- Computes the function f(x) = x^4 + 1
quadThenInc :: Integer -> Integer
quadThenInc = compose inc (compose square square)
