-- Define the rucksack function
rucksack :: [Integer] -> Integer -> [[Integer]]
rucksack [] target
  | target == 0 = [[]]  -- Base case: if the target is 0, return a list containing an empty list
  | otherwise   = []    -- If the target is not 0, return an empty list
rucksack (x:xs) target =
  let withoutX = rucksack xs target          -- Subsets excluding x
      withX = rucksack xs (target - x)       -- Subsets including x
  in withoutX ++ map (x:) withX              -- Combine both cases