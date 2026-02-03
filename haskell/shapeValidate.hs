module Shapes
  ( Shape(..)
  , Validity(..)
  , validShape
  ) where

-- Sum + product type
data Shape
  = Circle Double           -- radius
  | Rectangle Double Double -- height, width
  deriving (Show, Eq)

data Validity = Valid | Invalid
  deriving (Show, Eq)

-- A circle is valid iff radius ≥ 0.
-- A rectangle is valid iff height ≥ 0 and width ≥ 0.
validShape :: Shape -> Validity
validShape shape =
  case shape of
    Circle r
      | r < 0     -> Invalid
      | otherwise -> Valid
    Rectangle h w
      | h < 0 || w < 0 -> Invalid
      | otherwise      -> Valid