module Area
  ( isValidTriangle
  , areaTriangleSafe
  ) where

-- | Check triangle validity (positive sides + strict triangle inequality).
-- >>> isValidTriangle 1 2 4
-- False
-- >>> isValidTriangle 3 4 5
-- True
isValidTriangle :: Double -> Double -> Double -> Bool
isValidTriangle a b c =
  let pos x = x > 0
  in  all pos [a,b,c]
      && a + b > c
      && a + c > b
      && b + c > a

-- | Safe area using Heron's formula; returns Nothing for invalid triangles.
-- >>> areaTriangleSafe 3 4 5
-- Just 6.0
-- >>> areaTriangleSafe 1 2 4
-- Nothing
areaTriangleSafe :: Double -> Double -> Double -> Maybe Double
areaTriangleSafe a b c
  | not (isValidTriangle a b c) = Nothing
  | otherwise                   = Just area
  where
    s     = (a + b + c) / 2
    -- guard against tiny negative due to floating-point rounding
    radicand = max 0 (s * (s - a) * (s - b) * (s - c))
    area = sqrt radicand