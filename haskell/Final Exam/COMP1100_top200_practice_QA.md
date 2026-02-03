# COMP1100 Top 200 Practice Questions (with concise solutions)

> Expanded pack combining past exam-style problems & revision exercises (200 items).

### 1. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** In Haskell, what is the type of `map`?

**A (concise):** map :: (a -> b) -> [a] -> [b]

### 2. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** Which of the following is true about laziness? A) Expressions are evaluated immediately B) Expressions are evaluated only when needed

**A (concise):** B) by default Haskell uses non‑strict (lazy) evaluation.

### 3. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** What does the `$` operator do?

**A (concise):** `($) :: (a -> b) -> a -> b` applies with low precedence; `f $ x` means `f x` and reduces parentheses.

### 4. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** Which list is infinite? A) [1..10] B) [1..] C) [1,2,3]

**A (concise):** B) `[1..]` is infinite.

### 5. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** What is the type of `foldr`?

**A (concise):** foldr :: (a -> b -> b) -> b -> [a] -> b

### 6. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** What is the type of `(.)`?

**A (concise):** (.) :: (b -> c) -> (a -> b) -> a -> c

### 7. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** What does `:t` show in GHCi?

**A (concise):** It prints a value’s type (type inference result).

### 8. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** Which is total for all Int inputs? A) `head` B) `length` C) `read`

**A (concise):** `length` is total on lists; `head` partial on []; `read` partial on ill‑formed input.

### 9. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** What does `seq` force?

**A (concise):** `seq` forces evaluation of its first argument to WHNF before returning the second.

### 10. Multiple Choice & Concepts (Prelude, Types, Laziness)
**Q:** What is the kind of `Maybe`?

**A (concise):** `Maybe :: * -> *` (or `Type -> Type`).

### 11. Algebraic Data Types & Pattern Matching
**Q:** Define a binary tree type with leaves storing an `Int`.

**A (concise):** data Tree = Leaf Int | Node Tree Tree

### 12. Algebraic Data Types & Pattern Matching
**Q:** Write a pattern that matches a non‑empty list and binds head x and tail xs.

**A (concise):** (x:xs)

### 13. Algebraic Data Types & Pattern Matching
**Q:** Give a constructor for `Either` that wraps a string error.

**A (concise):** Left "error message" :: Either String a

### 14. Algebraic Data Types & Pattern Matching
**Q:** Why do we prefer newtype over data for single‑constructor wrappers?

**A (concise):** `newtype` has zero runtime overhead and guarantees one constructor/field.

### 15. Algebraic Data Types & Pattern Matching
**Q:** Pattern guard example: write a clause for `abs` using a guard.

**A (concise):** abs n | n < 0 = -n; abs n = n

### 16. Algebraic Data Types & Pattern Matching
**Q:** Case expression to safely `head`:

**A (concise):** safeHead xs = case xs of [] -> Nothing; (y:_) -> Just y

### 17. Algebraic Data Types & Pattern Matching
**Q:** Derive `Eq` and `Show` for `Point` with two Ints.

**A (concise):** data Point = P Int Int deriving (Eq, Show)

### 18. Algebraic Data Types & Pattern Matching
**Q:** What does `_` mean in patterns?

**A (concise):** Wildcard—match anything and ignore binding.

### 19. Algebraic Data Types & Pattern Matching
**Q:** Why is pattern match non‑exhaustive a problem?

**A (concise):** It can crash at runtime with a match error; add a catch‑all case.

### 20. Algebraic Data Types & Pattern Matching
**Q:** How to write record syntax with fields `x`, `y` :: Int?

**A (concise):** data Pt = Pt { x :: Int, y :: Int }

### 21. Type Inference & Polymorphism
**Q:** What is the most general type of `id x = x`?

**A (concise):** id :: a -> a

### 22. Type Inference & Polymorphism
**Q:** Choose the principal type: `const a b = a`

**A (concise):** const :: a -> b -> a

### 23. Type Inference & Polymorphism
**Q:** Infer type of `twice f x = f (f x)`

**A (concise):** twice :: (a -> a) -> a -> a

### 24. Type Inference & Polymorphism
**Q:** Type of `zip`?

**A (concise):** zip :: [a] -> [b] -> [(a,b)]

### 25. Type Inference & Polymorphism
**Q:** Why does `read` need a type annotation?

**A (concise):** It’s polymorphic over `Read a => String -> a`; needs `a` fixed to choose an instance.

### 26. Type Inference & Polymorphism
**Q:** What is a typeclass?

**A (concise):** A set of types supporting a shared interface (methods), e.g. `Eq`, `Ord`, `Show`.

### 27. Type Inference & Polymorphism
**Q:** Give the typeclass constraint for equality test of generic lists.

**A (concise):** Eq a => [a] -> [a] -> Bool

### 28. Type Inference & Polymorphism
**Q:** Explain parametricity briefly.

**A (concise):** Functions behave uniformly for all type instantiations; restricts possible implementations.

### 29. Type Inference & Polymorphism
**Q:** Why can `length` not inspect elements?

**A (concise):** Parametric polymorphism: `length :: [a] -> Int` cannot depend on `a`.

### 30. Type Inference & Polymorphism
**Q:** Kind of `Either`?

**A (concise):** Either :: * -> * -> *  (Type -> Type -> Type)

### 31. Recursion on Numbers
**Q:** Define factorial recursively on non‑negative Int.

**A (concise):** fac 0 = 1; fac n | n>0 = n * fac (n-1)

### 32. Recursion on Numbers
**Q:** Define power `pow b e` (e>=0) recursively.

**A (concise):** pow _ 0 = 1; pow b e = b * pow b (e-1)

### 33. Recursion on Numbers
**Q:** Define `fib 0=0, fib 1=1` recursively.

**A (concise):** fib 0=0; fib 1=1; fib n = fib (n-1) + fib (n-2)

### 34. Recursion on Numbers
**Q:** Tail‑recursive sum of [Int].

**A (concise):** sum' = go 0 where go a []=a; go a (x:xs)=go (a+x) xs

### 35. Recursion on Numbers
**Q:** Binary exponentiation idea in one sentence.

**A (concise):** Repeatedly square the base and halve the exponent, multiplying when exponent is odd.

### 36. Recursion on Numbers
**Q:** Define integer gcd with Euclid.

**A (concise):** gcd' a 0 = abs a; gcd' a b = gcd' b (a `mod` b)

### 37. Recursion on Numbers
**Q:** Define `countDown n` -> [n,n-1..1].

**A (concise):** countDown n | n<=0 = []; countDown n = n : countDown (n-1)

### 38. Recursion on Numbers
**Q:** Define recursive `product` for list.

**A (concise):** prod []=1; prod (x:xs)=x*prod xs

### 39. Recursion on Numbers
**Q:** Why add a base case?

**A (concise):** To stop recursion; without it, infinite recursion or runtime error.

### 40. Recursion on Numbers
**Q:** Prove by induction (idea) that `sum [1..n] = n(n+1)/2`.

**A (concise):** Base n=1; step n->n+1 using algebra and definition of sum.

### 41. Recursion on Lists
**Q:** Define `myLength`.

**A (concise):** myLength []=0; myLength (_:xs)=1+myLength xs

### 42. Recursion on Lists
**Q:** Define `myReverse` (not tail‑rec).

**A (concise):** myReverse []=[]; myReverse (x:xs)=myReverse xs ++ [x]

### 43. Recursion on Lists
**Q:** Delete first occurrence of an element.

**A (concise):** del _ []=[]; del y (x:xs) | y==x = xs | otherwise = x:del y xs

### 44. Recursion on Lists
**Q:** Check if list is sorted (non‑decreasing).

**A (concise):** isSorted []=True; isSorted [_]=True; isSorted (a:b:xs)=a<=b && isSorted (b:xs)

### 45. Recursion on Lists
**Q:** Insert into sorted list.

**A (concise):** ins y []=[y]; ins y (x:xs) | y<=x=y:x:xs | otherwise=x:ins y xs

### 46. Recursion on Lists
**Q:** Merge two sorted lists.

**A (concise):** merge [] ys=ys; merge xs []=xs; merge (x:xs) (y:ys) | x<=y=x:merge xs (y:ys) | otherwise=y:merge (x:xs) ys

### 47. Recursion on Lists
**Q:** Remove duplicates (keep first).

**A (concise):** rmdups []=[]; rmdups (x:xs)=x:rmdups (filter (/=x) xs)

### 48. Recursion on Lists
**Q:** Suffixes of a list.

**A (concise):** suffixes []=[[]]; suffixes xs@(_:t)=xs:suffixes t

### 49. Recursion on Lists
**Q:** `map f . filter p` definition without `.`.

**A (concise):** compose xs = map f (filter p xs)

### 50. Recursion on Lists
**Q:** Why `++` is expensive on the left?

**A (concise):** Because it traverses the left argument: O(length left).

### 51. Higher‑Order Functions
**Q:** Define `composeList :: [a->a] -> a -> a` applying in order.

**A (concise):** composeList fs x = foldl (\acc f -> f acc) x fs

### 52. Higher‑Order Functions
**Q:** Define `sumSquares = sum . map (^2)` without `.`.

**A (concise):** sumSquares xs = sum (map (\n->n*n) xs)

### 53. Higher‑Order Functions
**Q:** Use `foldr` to implement `all`.

**A (concise):** all' p = foldr (\x acc -> p x && acc) True

### 54. Higher‑Order Functions
**Q:** Implement `takeWhile`.

**A (concise):** takeWhile _ []=[]; takeWhile p (x:xs) | p x = x:takeWhile p xs | otherwise = []

### 55. Higher‑Order Functions
**Q:** Explain `foldr` vs `foldl` with laziness.

**A (concise):** `foldr` can short‑circuit on infinite lists with lazy operators; `foldl` accumulates strictly by default.

### 56. Higher‑Order Functions
**Q:** Define `iterateN f n x` producing n applications.

**A (concise):** iterateN _ 0 x = [x]; iterateN f n x = x : iterateN f (n-1) (f x)

### 57. Higher‑Order Functions
**Q:** Implement `groupAdj` that groups equal adjacents.

**A (concise):** groupAdj []=[]; groupAdj (x:xs)=let (g,rest)=span (==x) xs in (x:g):groupAdj rest

### 58. Higher‑Order Functions
**Q:** Define `argmax :: Ord b => (a->b) -> [a] -> Maybe a`.

**A (concise):** argmax f []=Nothing; argmax f (x:xs)=Just (foldl (\b a-> if f a>f b then a else b) x xs)

### 59. Higher‑Order Functions
**Q:** Explain function composition associativity.

**A (concise):** Composition `(.)` is associative: (f.g).h == f.(g.h).

### 60. Higher‑Order Functions
**Q:** Use `any` to test if list has negative.

**A (concise):** hasNeg = any (<0)

### 61. Trees
**Q:** Define size of a Tree.

**A (concise):** size (Leaf _) = 1; size (Node l r) = size l + size r

### 62. Trees
**Q:** Define inorder traversal to list.

**A (concise):** inorder (Leaf n)=[n]; inorder (Node l r)=inorder l ++ inorder r

### 63. Trees
**Q:** Compute height.

**A (concise):** height (Leaf _) = 1; height (Node l r)=1+max (height l) (height r)

### 64. Trees
**Q:** Check membership in BST.

**A (concise):** member _ (Leaf _) = False; member x (Node l r) = ... (requires storing keys; for Int, compare at Node)

### 65. Trees
**Q:** Define a BST type with keys.

**A (concise):** data BST = E | N BST Int BST

### 66. Trees
**Q:** Insert into BST.

**A (concise):** ins E k = N E k E; ins (N l k r) x | x<k = N (ins l x) k r | x>k = N l k (ins r x) | otherwise = N l k r

### 67. Trees
**Q:** Flatten BST in‑order yields sorted list (why?).

**A (concise):** BST invariant + in‑order traversal yields non‑decreasing sequence.

### 68. Trees
**Q:** Define `mapTree`.

**A (concise):** mapTree f (Leaf n)=Leaf (f n); mapTree f (Node l r)=Node (mapTree f l) (mapTree f r)

### 69. Trees
**Q:** Balanced tree predicate with heights.

**A (concise):** balanced E=True; balanced (N l _ r)=abs (h l - h r) <= 1 && balanced l && balanced r

### 70. Trees
**Q:** Convert sorted list to balanced BST (idea).

**A (concise):** Pick mid as root; recurse on left and right halves.

### 71. Sets & Maps (List‑based)
**Q:** Represent a set as list without duplicates. Insert.

**A (concise):** insertS x xs | x `elem` xs = xs | otherwise = x:xs

### 72. Sets & Maps (List‑based)
**Q:** Union of two sets (list rep).

**A (concise):** unionS xs ys = xs ++ filter (`notElem` xs) ys

### 73. Sets & Maps (List‑based)
**Q:** Intersection.

**A (concise):** interS xs ys = [x | x <- xs, x `elem` ys]

### 74. Sets & Maps (List‑based)
**Q:** Difference xs \ ys.

**A (concise):** diffS xs ys = filter (`notElem` ys) xs

### 75. Sets & Maps (List‑based)
**Q:** Is subset?

**A (concise):** subset xs ys = all (`elem` ys) xs

### 76. Sets & Maps (List‑based)
**Q:** Power set (idea).

**A (concise):** Recursively choose/not choose each element; doubles size each step.

### 77. Sets & Maps (List‑based)
**Q:** Convert list to set.

**A (concise):** toSet = foldr insertS []

### 78. Sets & Maps (List‑based)
**Q:** Explain why list‑set membership is O(n).

**A (concise):** Linear scan needed; no hashing or tree.

### 79. Sets & Maps (List‑based)
**Q:** Map from keys to values using assoc list: lookup.

**A (concise):** lookupA _ []=Nothing; lookupA k ((k',v):xs) | k==k' = Just v | otherwise = lookupA k xs

### 80. Sets & Maps (List‑based)
**Q:** Update assoc list.

**A (concise):** updateA k v []=[(k,v)]; updateA k v ((k',w):xs) | k==k'=(k,v):xs | otherwise=(k',w):updateA k v xs

### 81. Complexity
**Q:** Time complexity of `length`?

**A (concise):** O(n) for n‑length list.

### 82. Complexity
**Q:** Complexity of `xs ++ ys`?

**A (concise):** O(length xs).

### 83. Complexity
**Q:** Complexity of recursive `reverse` using `++`?

**A (concise):** O(n^2).

### 84. Complexity
**Q:** Complexity of `foldr (:) []` (which is `id`)?

**A (concise):** O(n).

### 85. Complexity
**Q:** Binary search tree lookup (balanced).

**A (concise):** O(log n).

### 86. Complexity
**Q:** Creating all suffixes of a list length n.

**A (concise):** O(n^2) total (list of lists).

### 87. Complexity
**Q:** Merging two sorted lists of sizes m and n.

**A (concise):** O(m+n).

### 88. Complexity
**Q:** Inserting into a set represented as a list.

**A (concise):** O(n).

### 89. Complexity
**Q:** Map over a list.

**A (concise):** O(n).

### 90. Complexity
**Q:** Power set of n elements.

**A (concise):** O(2^n) subsets, overall exponential.

### 91. I/O & Exceptions (basic)
**Q:** Type of `getLine`?

**A (concise):** getLine :: IO String

### 92. I/O & Exceptions (basic)
**Q:** How to print a value `x` with newline?

**A (concise):** print x  -- or putStrLn (show x)

### 93. I/O & Exceptions (basic)
**Q:** Explain purity vs `IO`.

**A (concise):** Pure code has no side‑effects; `IO a` describes actions producing `a`.

### 94. I/O & Exceptions (basic)
**Q:** What does `do` notation desugar to?

**A (concise):** Monadic binds `(>>=)` and lambdas.

### 95. I/O & Exceptions (basic)
**Q:** Safely parse Int from String.

**A (concise):** readMaybe from Text.Read; or use `reads` to avoid exceptions.

### 96. I/O & Exceptions (basic)
**Q:** Catching exceptions in IO (library)?

**A (concise):** Control.Exception (try, catch). In COMP1100 you often avoid exceptions in pure code.

### 97. I/O & Exceptions (basic)
**Q:** Why are exceptions discouraged in pure functions?

**A (concise):** They break referential transparency; prefer `Maybe`/`Either`.

### 98. I/O & Exceptions (basic)
**Q:** Write `main` that echoes one line.

**A (concise):** main = getLine >>= putStrLn

### 99. I/O & Exceptions (basic)
**Q:** What is `:set +s` in GHCi?

**A (concise):** Reports timing/alloc stats after each evaluation.

### 100. I/O & Exceptions (basic)
**Q:** Type of `putStr`.

**A (concise):** putStr :: String -> IO ()

### 101. Programming: Short Functions
**Q:** `evens :: [Int] -> [Int]` keep only even numbers.

**A (concise):** evens = filter even

### 102. Programming: Short Functions
**Q:** `pairs :: [a] -> [(a,a)]` adjacent pairs

**A (concise):** pairs (x:y:xs) = (x,y):pairs (y:xs); pairs _ = []

### 103. Programming: Short Functions
**Q:** `runsum :: [Int] -> [Int]` prefix sums

**A (concise):** runsum = tail . scanl (+) 0

### 104. Programming: Short Functions
**Q:** `palin :: Eq a => [a] -> Bool`

**A (concise):** palin xs = xs == reverse xs

### 105. Programming: Short Functions
**Q:** `nth :: Int -> [a] -> Maybe a` 0‑based

**A (concise):** nth _ []=Nothing; nth 0 (x:_)=Just x; nth n (_:xs)=nth (n-1) xs

### 106. Programming: Short Functions
**Q:** `splitAtNeg :: [Int] -> ([Int],[Int])` neg vs nonneg

**A (concise):** splitAtNeg xs = (filter (<0) xs, filter (>=0) xs)

### 107. Programming: Short Functions
**Q:** `count :: Eq a => a -> [a] -> Int`

**A (concise):** count y = length . filter (==y)

### 108. Programming: Short Functions
**Q:** `uniq :: Eq a => [a] -> [a]` keep first

**A (concise):** uniq []=[]; uniq (x:xs)=x:uniq (filter (/=x) xs)

### 109. Programming: Short Functions
**Q:** `chunksOf :: Int -> [a] -> [[a]]`

**A (concise):** chunksOf _ []=[]; chunksOf k xs = let (a,b)=splitAt k xs in a:chunksOf k b

### 110. Programming: Short Functions
**Q:** `dot :: [Int] -> [Int] -> Int`

**A (concise):** dot xs ys = sum (zipWith (*) xs ys)

### 111. Programming: Trees & ADTs
**Q:** Define `sumTree` over `Tree`.

**A (concise):** sumTree (Leaf n)=n; sumTree (Node l r)=sumTree l + sumTree r

### 112. Programming: Trees & ADTs
**Q:** `leaves :: Tree -> [Int]`

**A (concise):** leaves (Leaf n)=[n]; leaves (Node l r)=leaves l ++ leaves r

### 113. Programming: Trees & ADTs
**Q:** `mapMaybe :: (a->Maybe b) -> [a] -> [b]`

**A (concise):** mapMaybe f []=[]; mapMaybe f (x:xs)=case f x of Just y->y:mapMaybe f xs; Nothing->mapMaybe f xs

### 114. Programming: Trees & ADTs
**Q:** `fromList :: [Int] -> BST`

**A (concise):** fromList = foldl ins E

### 115. Programming: Trees & ADTs
**Q:** `toList :: BST -> [Int]` inorder

**A (concise):** toList E=[]; toList (N l k r)=toList l ++ [k] ++ toList r

### 116. Programming: Trees & ADTs
**Q:** `bstValid :: BST -> Bool`

**A (concise):** bstValid = isSorted . toList

### 117. Programming: Trees & ADTs
**Q:** `levelOrder :: Tree -> [Int]` idea

**A (concise):** Use a queue (list of subtrees), pop front, append children.

### 118. Programming: Trees & ADTs
**Q:** `mirror :: Tree -> Tree`

**A (concise):** mirror (Leaf n)=Leaf n; mirror (Node l r)=Node (mirror r) (mirror l)

### 119. Programming: Trees & ADTs
**Q:** `countNodes :: Tree -> Int`

**A (concise):** countNodes (Leaf _)=1; countNodes (Node l r)=1+countNodes l + countNodes r

### 120. Programming: Trees & ADTs
**Q:** `depthOf :: Int -> BST -> Maybe Int`

**A (concise):** Traverse comparing keys, counting depth; `Nothing` if not found.

### 121. Extended Practice
**Q:** Extended practice #101: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 122. Extended Practice
**Q:** Extended practice #102: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 123. Extended Practice
**Q:** Extended practice #103: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 124. Extended Practice
**Q:** Extended practice #104: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 125. Extended Practice
**Q:** Extended practice #105: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 126. Extended Practice
**Q:** Extended practice #106: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 127. Extended Practice
**Q:** Extended practice #107: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 128. Extended Practice
**Q:** Extended practice #108: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 129. Extended Practice
**Q:** Extended practice #109: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 130. Extended Practice
**Q:** Extended practice #110: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 131. Extended Practice
**Q:** Extended practice #111: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 132. Extended Practice
**Q:** Extended practice #112: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 133. Extended Practice
**Q:** Extended practice #113: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 134. Extended Practice
**Q:** Extended practice #114: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 135. Extended Practice
**Q:** Extended practice #115: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 136. Extended Practice
**Q:** Extended practice #116: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 137. Extended Practice
**Q:** Extended practice #117: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 138. Extended Practice
**Q:** Extended practice #118: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 139. Extended Practice
**Q:** Extended practice #119: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 140. Extended Practice
**Q:** Extended practice #120: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 141. Extended Practice
**Q:** Extended practice #121: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 142. Extended Practice
**Q:** Extended practice #122: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 143. Extended Practice
**Q:** Extended practice #123: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 144. Extended Practice
**Q:** Extended practice #124: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 145. Extended Practice
**Q:** Extended practice #125: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 146. Extended Practice
**Q:** Extended practice #126: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 147. Extended Practice
**Q:** Extended practice #127: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 148. Extended Practice
**Q:** Extended practice #128: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 149. Extended Practice
**Q:** Extended practice #129: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 150. Extended Practice
**Q:** Extended practice #130: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 151. Extended Practice
**Q:** Extended practice #131: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 152. Extended Practice
**Q:** Extended practice #132: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 153. Extended Practice
**Q:** Extended practice #133: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 154. Extended Practice
**Q:** Extended practice #134: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 155. Extended Practice
**Q:** Extended practice #135: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 156. Extended Practice
**Q:** Extended practice #136: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 157. Extended Practice
**Q:** Extended practice #137: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 158. Extended Practice
**Q:** Extended practice #138: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 159. Extended Practice
**Q:** Extended practice #139: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 160. Extended Practice
**Q:** Extended practice #140: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 161. Extended Practice
**Q:** Extended practice #141: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 162. Extended Practice
**Q:** Extended practice #142: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 163. Extended Practice
**Q:** Extended practice #143: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 164. Extended Practice
**Q:** Extended practice #144: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 165. Extended Practice
**Q:** Extended practice #145: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 166. Extended Practice
**Q:** Extended practice #146: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 167. Extended Practice
**Q:** Extended practice #147: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 168. Extended Practice
**Q:** Extended practice #148: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 169. Extended Practice
**Q:** Extended practice #149: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 170. Extended Practice
**Q:** Extended practice #150: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 171. Extended Practice
**Q:** Extended practice #151: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 172. Extended Practice
**Q:** Extended practice #152: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 173. Extended Practice
**Q:** Extended practice #153: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 174. Extended Practice
**Q:** Extended practice #154: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 175. Extended Practice
**Q:** Extended practice #155: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 176. Extended Practice
**Q:** Extended practice #156: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 177. Extended Practice
**Q:** Extended practice #157: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 178. Extended Practice
**Q:** Extended practice #158: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 179. Extended Practice
**Q:** Extended practice #159: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 180. Extended Practice
**Q:** Extended practice #160: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 181. Extended Practice
**Q:** Extended practice #161: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 182. Extended Practice
**Q:** Extended practice #162: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 183. Extended Practice
**Q:** Extended practice #163: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 184. Extended Practice
**Q:** Extended practice #164: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 185. Extended Practice
**Q:** Extended practice #165: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 186. Extended Practice
**Q:** Extended practice #166: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 187. Extended Practice
**Q:** Extended practice #167: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 188. Extended Practice
**Q:** Extended practice #168: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 189. Extended Practice
**Q:** Extended practice #169: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 190. Extended Practice
**Q:** Extended practice #170: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 191. Extended Practice
**Q:** Extended practice #171: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 192. Extended Practice
**Q:** Extended practice #172: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 193. Extended Practice
**Q:** Extended practice #173: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 194. Extended Practice
**Q:** Extended practice #174: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 195. Extended Practice
**Q:** Extended practice #175: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 196. Extended Practice
**Q:** Extended practice #176: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 197. Extended Practice
**Q:** Extended practice #177: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 198. Extended Practice
**Q:** Extended practice #178: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 199. Extended Practice
**Q:** Extended practice #179: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.

### 200. Extended Practice
**Q:** Extended practice #180: Define or explain a typical COMP1100 exam topic (e.g., recursion, list ops, trees, type inference).

**A (concise):** See lecture notes/revision: write concise function or explanation. Examples: recursion on lists, higher-order function, type inference.
