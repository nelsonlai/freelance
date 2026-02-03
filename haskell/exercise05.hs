module GPACalculator
  ( Grade(..)
  , Mark
  , markToGrade       -- throws on out-of-range (as in Ex. 3/4)
  , markToGradeSafe   -- Ex. 5: Maybe-based safe version
  ) where

data Grade
  = Fail            -- 0–49
  | Pass            -- 50–59
  | Credit          -- 60–69
  | Distinction     -- 70–79
  | HighDistinction -- 80–100
  deriving (Show, Eq, Ord, Enum, Bounded)

type Mark = Int

-- Original (kept for comparison): errors if mark is out of bounds
markToGrade :: Mark -> Grade
markToGrade m
  | m < 0 || m > 100 = error "markToGrade: Not a valid mark"
  | m >= 80          = HighDistinction
  | m >= 70          = Distinction
  | m >= 60          = Credit
  | m >= 50          = Pass
  | otherwise        = Fail

-- Exercise 5: safe version using Maybe
--   Out-of-range -> Nothing
--   In-range     -> Just <Grade>
markToGradeSafe :: Mark -> Maybe Grade
markToGradeSafe m
  | m < 0 || m > 100 = Nothing
  | m >= 80          = Just HighDistinction
  | m >= 70          = Just Distinction
  | m >= 60          = Just Credit
  | m >= 50          = Just Pass
  | otherwise        = Just Fail