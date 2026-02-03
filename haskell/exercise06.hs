module GPACalculator
  ( Grade(..)
  , Mark, GPA
  , markToGradeSafe
  , gradeToGPA
  , maybeGradeToGPA
  , markToGPA
  ) where

-- ===== From earlier exercises =====
data Grade = Fail | Pass | Credit | Distinction | HighDistinction
  deriving (Show, Eq, Ord, Enum, Bounded)

type Mark = Int
type GPA  = Double

-- Safe mark->grade (Exercise 5)
markToGradeSafe :: Mark -> Maybe Grade
markToGradeSafe m
  | m < 0 || m > 100 = Nothing
  | m >= 80          = Just HighDistinction
  | m >= 70          = Just Distinction
  | m >= 60          = Just Credit
  | m >= 50          = Just Pass
  | otherwise        = Just Fail

-- ===== Exercise 6 =====
-- Grade -> GPA table (ANU-style)
gradeToGPA :: Grade -> GPA
gradeToGPA HighDistinction = 7
gradeToGPA Distinction     = 6
gradeToGPA Credit          = 5
gradeToGPA Pass            = 4
gradeToGPA Fail            = 0

-- Maybe Grade -> GPA (Nothing treated as 0)
maybeGradeToGPA :: Maybe Grade -> GPA
maybeGradeToGPA (Just g) = gradeToGPA g
maybeGradeToGPA Nothing  = 0

-- Convenience: Mark -> GPA using the safe pipeline
markToGPA :: Mark -> GPA
markToGPA = maybeGradeToGPA . markToGradeSafe