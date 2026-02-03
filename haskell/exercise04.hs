module GPACalculator
  ( Grade(..)
  , Mark
  , Course(..)
  , markToGrade
  , markToGradeSafe
  , markToGrade'         -- Exercise 4
  , markToGrade'Safe     -- (optional safe version)
  ) where

-- ===== Exercise 3 bits (kept here so this file is standalone) =====

data Grade
  = Fail            -- 0–49
  | Pass            -- 50–59
  | Credit          -- 60–69
  | Distinction     -- 70–79
  | HighDistinction -- 80–100
  deriving (Show, Eq, Ord, Enum, Bounded)

type Mark = Int

markToGrade :: Mark -> Grade
markToGrade m
  | m < 0 || m > 100 = error "markToGrade: mark must be between 0 and 100"
  | m >= 80          = HighDistinction
  | m >= 70          = Distinction
  | m >= 60          = Credit
  | m >= 50          = Pass
  | otherwise        = Fail

markToGradeSafe :: Mark -> Maybe Grade
markToGradeSafe m
  | m < 0 || m > 100 = Nothing
  | otherwise        = Just (markToGrade m)

-- ===== Exercise 4 =====

-- Course identified by a code in each school
data Course
  = Art  Int
  | Comp Int
  | Busn Int
  | Math Int
  deriving (Show, Eq, Ord)

-- Ignore the course for grading; grade depends only on the mark.
markToGrade' :: (Course, Mark) -> Grade
markToGrade' (_, m) = markToGrade m

-- Safe version that never throws
markToGrade'Safe :: (Course, Mark) -> Maybe Grade
markToGrade'Safe (_, m) = markToGradeSafe m