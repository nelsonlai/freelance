module GPACalculator
  ( Grade(..)
  , Mark
  , markToGrade
  , markToGradeSafe
  ) where

data Grade
  = Fail            -- 0–49
  | Pass            -- 50–59
  | Credit          -- 60–69
  | Distinction     -- 70–79
  | HighDistinction -- 80–100
  deriving (Show, Eq, Ord, Enum, Bounded)
  -- Show: for string representation
  -- Eq: for comparison
  -- Ord: for ordering
  -- Enum: for enumeration
  -- Bounded: for minBound and maxBound


type Mark = Int -- type: define data type, alias for Int

markToGrade :: Mark -> Grade
markToGrade m
  | m < 0 || m > 100 = error "markToGrade: mark must be between 0 and 100"
  | m >= 80          = HighDistinction
  | m >= 70          = Distinction
  | m >= 60          = Credit
  | m >= 50          = Pass
  | otherwise        = Fail

-- Safe wrapper that never throws; out-of-range marks yield Nothing
markToGradeSafe :: Mark -> Maybe Grade
markToGradeSafe m
  | m < 0 || m > 100 = Nothing
  | otherwise        = Just (markToGrade m)