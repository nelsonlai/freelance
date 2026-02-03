module Fruit where

data Fruit = Apple | Banana | Orange

instance Eq Fruit where
    (==) Apple Apple = True
    (==) Banana Banana = True
    (==) Orange Orange = True
    (==) _ _           = False

instance Show Fruit where
    show fruit = case fruit of
        Apple -> "An apple."
        Banana -> "A banana! Yum!"
        Orange -> "Yuck, an orange."

instance Ord Fruit where
    (<=) Orange Apple = True
    (<=) Apple Banana = True
    (<=) Orange Banana = True

    (<=) Banana Apple = False
    (<=) Apple Orange = False
    (<=) Banana Orange = False

    (<=) Banana Banana = True
    (<=) Apple Apple = True
    (<=) Orange Orange = True
