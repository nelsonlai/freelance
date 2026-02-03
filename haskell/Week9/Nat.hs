{-|
Module      : Nat
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Deriving equality and order on Nat
-}

module Nat where

{-
Exercise 3A, 3B: Defining equality and ordering on Nat

Using the template given, define all the functions required for
`Nat` to be a member of `Eq` and `Ord`.

DO NOT USE "deriving Eq" or "deriving Ord". 
You should define the instances of (==) and (<=) yourself.
-}

data Nat = Z | S Nat
    deriving (Show)

instance Eq Nat where
    Z == Z = True
    (S n) == (S m) = n == m
    _ == _ = False

instance Ord Nat where
    Z <= _ = True
    (S _) <= Z = False
    (S n) <= (S m) = n <= m

