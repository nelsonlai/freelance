# Haskell in 50 Minutes — Teaching Pack

## Learning goals (by the end)
- Explain purity, immutability, and strong static typing.
- Read and write simple functions with type annotations.
- Use pattern matching, recursion, and higher-order functions (`map`, `filter`, `fold`).
- Define a small algebraic data type and derive typeclass instances.
- Write a tiny `IO` program with `do` notation.

---

## Agenda & timing (50 min)
1. (0–5) What is Haskell? Tooling + `ghci`
2. (5–15) Expressions, functions, and types
3. (15–25) Pattern matching + recursion
4. (25–35) Higher-order functions & list tricks
5. (35–42) Algebraic data types & typeclasses
6. (42–48) `IO` & `do` notation mini-app
7. (48–50) Wrap-up & homework

---

## 0–5: What is Haskell? Tooling + `ghci`
**Why Haskell**
- Pure (no side effects inside pure functions)
- Immutable by default
- Powerful type system and type inference
- Concise, expressive, parallel-friendly

**Quick setup**
- Install via **GHCup** (installs GHC, `cabal`, `stack`)  
- Open a terminal: `ghci` launches the REPL.

**`ghci` cheats**
```
:t expr     -- show the type
:i name     -- info about a function/typeclass
:r          -- reload current file
:l File.hs  -- load a file
:quit       -- leave ghci
:set -Wall  -- enable helpful warnings
```

---

## 5–15: Expressions, functions, and types
**Everything is an expression**, not a statement.

### Hello, Types
```haskell
-- File: Intro.hs
-- Top-level definitions need type signatures (good practice)
double :: Num a => a -> a
double x = x * 2

-- Function application is by space, not parentheses:
-- double 21  ==> 42
```

**If/guards vs pattern matching**
```haskell
absVal :: (Num a, Ord a) => a -> a
absVal x
  | x >= 0    = x
  | otherwise = -x
```

**Currying**
All functions are single-argument; “multiple parameters” are curried.
```haskell
add :: Int -> Int -> Int
add a b = a + b

inc :: Int -> Int
inc = add 1        -- partial application
```

**Immutable values**
```haskell
-- 'let' in ghci:
-- let y = 10
-- y = y + 1     -- ❌ not allowed; values don’t change
```

---

## 15–25: Pattern matching + recursion
```haskell
-- Tuples and lists
first :: (a, b) -> a
first (x, _) = x

safeHead :: [a] -> Maybe a
safeHead []    = Nothing
safeHead (x:_) = Just x
```

**Recursion**
```haskell
-- Factorial with pattern matching
fact :: (Eq a, Num a) => a -> a
fact 0 = 1
fact n = n * fact (n - 1)

-- Fibonacci (demo only; not efficient)
fib :: (Eq a, Num a) => a -> a
fib 0 = 0
fib 1 = 1
fib n = fib (n - 1) + fib (n - 2)
```

**Mini exercise (3–4 min)**
> Implement `len :: [a] -> Int` using recursion and pattern matching.  
> **Stretch**: write `sum' :: Num a => [a] -> a`.

---

## 25–35: Higher-order functions & list tricks
```haskell
-- map / filter / folds
squares :: Num a => [a] -> [a]
squares = map (\x -> x * x)

odds :: [Int] -> [Int]
odds = filter odd

sumSquaresOfOdds :: [Int] -> Int
sumSquaresOfOdds = foldr (+) 0 . map (^2) . filter odd
-- point-free: compose transformations
```

**List comprehensions**
```haskell
pythags :: Int -> [(Int,Int,Int)]
pythags n = [ (a,b,c)
            | a <- [1..n]
            , b <- [a..n]
            , let c = floor . sqrt . fromIntegral $ a*a + b*b
            , a*a + b*b == c*c
            , c <= n
            ]
```

**Mini exercise (3–4 min)**
> Write `evensDoubled :: [Int] -> [Int]` that keeps evens and doubles them.  
> (Try both `filter`/`map` and a list comprehension.)

---

## 35–42: Algebraic data types (ADTs) & typeclasses
**Define your own types**
```haskell
-- Product type (record syntax) + deriving common typeclasses
data Person = Person
  { name :: String
  , age  :: Int
  } deriving (Show, Eq, Ord)

-- Sum type (either/or)
data Shape
  = Circle Double
  | Rect   Double Double
  deriving (Show, Eq)

area :: Shape -> Double
area (Circle r)   = pi * r * r
area (Rect w h)   = w * h
```

**Typeclasses**
- Think “interfaces of behaviour” (e.g., `Eq`, `Ord`, `Show`, `Num`).
- `deriving` adds default instances when possible.

**Mini exercise (3–4 min)**
> Add a constructor `Square Double` to `Shape` and extend `area`.

---

## 42–48: `IO` & `do` notation mini-app
**Idea:** read a line of numbers, print the **sum of squares of odds**.

```haskell
-- File: Main.hs
import Data.Char (isSpace)

trim :: String -> String
trim = f . f
  where f = reverse . dropWhile isSpace

parseInts :: String -> [Int]
parseInts = map read . words . trim

sumSquaresOfOdds :: [Int] -> Int
sumSquaresOfOdds = foldr (+) 0 . map (^2) . filter odd

main :: IO ()
main = do
  putStrLn "Enter numbers separated by spaces:"
  line <- getLine
  let nums = parseInts line
  putStrLn ("Sum of squares of odds = " ++ show (sumSquaresOfOdds nums))
```

**Explain**
- `main :: IO ()` is an effectful action.
- `do` sequences actions; `<-` binds results of actions.
- `show` converts values to `String`.

**Run**
```
ghc Main.hs && ./Main
-- or in ghci:
-- :l Main.hs
-- main
```

---

## Wrap-up (48–50): key takeaways
- Pure functions + types make refactoring safe.
- Pattern matching & recursion are core.
- Higher-order functions and composition keep code concise.
- ADTs model your domain clearly.
- `IO` is explicit — great for reasoning and testing.

---

## Quick reference (handout)
- **Function type:** `f :: A -> B`
- **List:** `[a]`; **Tuple:** `(a,b)`; **Maybe:** `Nothing | Just a`
- **Common typeclasses:** `Eq`, `Ord`, `Show`, `Read`, `Enum`, `Bounded`, `Num`, `Foldable`, `Functor`, `Applicative`, `Monad`
- **Core HOFs:** `map`, `filter`, `foldr`, `foldl'` (strict), `zip`, `(.)` composition, `($)` low-precedence apply
- **`ghci`:** `:t`, `:i`, `:r`, `:l`, `:set -Wall`

---

## In-class checkpoints (answers ready)
- `len [] = 0; len (_:xs) = 1 + len xs`
- `sum' [] = 0; sum' (x:xs) = x + sum' xs`
- `evensDoubled = map (*2) . filter even`
- `Square s` case in `area`: `area (Square s) = s * s`

---

## Stretch ideas / homework
1. **Refactor** `sumSquaresOfOdds` to use a list comprehension.
2. **Define** `data Temperature = C Double | F Double` and write `toC :: Temperature -> Double`.
3. **Write** a small **word-count** program: read a file path from stdin and print number of lines/words/chars.
4. **Property tests (bonus):** describe a property for `reverse` (e.g., `reverse (reverse xs) == xs`) and try QuickCheck later.
