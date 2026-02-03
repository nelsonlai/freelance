module GPACalculator
  ( Grade(..)
  , Course(..)
  , Mark
  , markToGradeScaled
  ) where

-- From earlier exercises
data Grade = Fail | Pass | Credit | Distinction | HighDistinction
  deriving (Show, Eq)

data Course = Art Int | Comp Int | Busn Int | Math Int
  deriving (Show, Eq)

type Mark = Int

-- Helper: convert a numeric score (can be fractional after scaling) to a Grade
scoreToGrade :: Double -> Grade
scoreToGrade s
  | s >= 80   = HighDistinction
  | s >= 70   = Distinction
  | s >= 60   = Credit
  | s >= 50   = Pass
  | otherwise = Fail

-- Scaling factor per course:
--   Busn 1000-level  -> * 0.90
--   Other Busn       -> * 0.95
--   All others       -> * 1.00
scaleFactor :: Course -> Double
scaleFactor (Busn code)
  | code >= 1000 && code < 2000 = 0.90
  | otherwise                   = 0.95
scaleFactor _ = 1.00

-- && , and, || or

markToGradeScaled :: (Course, Mark) -> Grade
markToGradeScaled (c, m) =
  let scaled = fromIntegral m * scaleFactor c   -- keep as Double; no rounding needed
  in scoreToGrade scaled