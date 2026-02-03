-- Define the mapMaybe function
mapMaybe :: (a -> b) -> [Maybe a] -> [b]
mapMaybe _ [] = []  -- Base case: empty list returns an empty list
mapMaybe f (x:xs) =
  case x of
    Just value -> f value : mapMaybe f xs  -- Apply the function to the value inside Just and continue
    Nothing    -> mapMaybe f xs           -- Skip Nothing values and continue