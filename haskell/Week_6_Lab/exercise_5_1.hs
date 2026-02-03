-- Define the unMaybe function
unMaybe :: [Maybe a] -> [a]
unMaybe [] = []  -- Base case: empty list returns an empty list
unMaybe (x:xs) =
  case x of
    Just value -> value : unMaybe xs  -- If the element is Just, extract the value and continue
    Nothing    -> unMaybe xs          -- If the element is Nothing, skip it and continue
    