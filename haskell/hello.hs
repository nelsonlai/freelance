-- hello.hs
-- A simple Haskell program

-- A function to square a number
square :: Int -> Int
square x = x * x

addTwo :: Int -> Int -> Int
addTwo x y = x + y

main :: IO ()
main = do
    putStrLn "Hello, Haskell!"
    putStrLn ("Square of 5 is " ++ show (square 5))
    putStrLn ("Sum of 5 and 3 is " ++ show (addTwo 5 3))

-- Integer
-- Float
-- Double
-- Char