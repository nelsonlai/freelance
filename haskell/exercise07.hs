-- GPACalculator.hs
module GPACalculator
  ( Grade(..)
  , Mark, GPA
  , markToGradeSafe
  , maybeGradeToGPA
  , markToGPA        -- Exercise 7
  ) where

-- Grades
data Grade = Fail | Pass | Credit | Distinction | HighDistinction
  deriving (Show, Eq, Ord, Enum, Bounded)

type Mark = Int
type GPA  = Double

-- From Exercise 5: safe mark → grade
markToGradeSafe :: Mark -> Maybe Grade
markToGradeSafe m
  | m < 0 || m > 100 = Nothing
  | m >= 80          = Just HighDistinction
  | m >= 70          = Just Distinction
  | m >= 60          = Just Credit
  | m >= 50          = Just Pass
  | otherwise        = Just Fail

-- Helper: grade → GPA table
gradeToGPA :: Grade -> GPA
gradeToGPA HighDistinction = 7
gradeToGPA Distinction     = 6
gradeToGPA Credit          = 5
gradeToGPA Pass            = 4
gradeToGPA Fail            = 0

-- From Exercise 6: Maybe Grade → GPA
maybeGradeToGPA :: Maybe Grade -> GPA
maybeGradeToGPA (Just g) = gradeToGPA g
maybeGradeToGPA Nothing  = 0

-- Exercise 7: Mark → GPA by linking the two previous functions
markToGPA :: Mark -> GPA
markToGPA = maybeGradeToGPA . markToGradeSafe
-- This function provides a convenient way to convert a mark directly to GPA