-- Function to check if all words start with the same letter
allStartWithSameLetter :: [String] -> Bool
allStartWithSameLetter [] = True  -- Empty list returns True
allStartWithSameLetter (x:xs) = myAll (\s -> head s == head x) xs

-- Function to check if any two words start with the same letter
anyStartWithSameLetter :: [String] -> Bool
anyStartWithSameLetter [] = False  -- Empty list returns False
anyStartWithSameLetter [_] = False  -- Single-element list returns False
anyStartWithSameLetter (x:xs) = myAny (\s -> head s == head x) xs || anyStartWithSameLetter xs
