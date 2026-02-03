-- Exercise 1
{-|
Module      : Library
Description : Core types for an online video library (movies and TV shows) and their availability.
Maintainer  : <your.email@example.com>

This module defines the foundational domain types for a small online library
that stores videos (movies and TV shows) along with their availability.
The goal here is to demonstrate good Haskell module structure and
documentation style.
-}
module Library
  ( Title(..)
  , Year(..)
  , Rating(..)
  , Availability(..)
  , Video(..)
  , Library
  ) where

-- | A 'Title' is the human-readable name of a video.
newtype Title = Title String
  deriving (Eq, Ord, Show, Read)

-- | Production 'Year' of a video.
newtype Year = Year Int
  deriving (Eq, Ord, Show, Read)

-- | A simple content rating.
data Rating
  = G | PG | PG13 | R | NC17 | Unrated
  deriving (Eq, Ord, Show, Read)

-- | Availability status of a library item.
data Availability
  = InStock      -- ^ Available now.
  | CheckedOut   -- ^ On loan to a patron.
  | ComingSoon   -- ^ Announced, not yet available.
  | Unavailable  -- ^ Not available in the catalogue.
  deriving (Eq, Ord, Show, Read)

-- | A 'Video' in the library is either a 'Movie' or a TV 'Show'.
data Video
  = Movie
      { movieTitle  :: Title      -- ^ Movie title.
      , movieYear   :: Year       -- ^ Release year.
      , movieRating :: Rating     -- ^ Content rating.
      , movieAvail  :: Availability -- ^ Current availability.
      }
  | Show
      { showTitle   :: Title      -- ^ Show title.
      , seasons     :: Int        -- ^ Number of seasons.
      , showRating  :: Rating     -- ^ Content rating.
      , showAvail   :: Availability -- ^ Current availability.
      }
  deriving (Eq, Show, Read)

-- | A 'Library' is a collection of videos.
type Library = [Video]

---------------
-- Exercise 2 
{-|
Module      : Library
Description : Exercise 2 — basic types and an example library.
Maintainer  : <your.email@example.com>
-}
module Library where

-- | Human-readable title.
type Name = String

-- | Production year.
type Year = Int

-- | Availability flag: 'True' = available, 'False' = not available.
type Availability = Bool

-- | A video is either a 'Movie' or a TV 'Show'.
data Video
  = Movie
      { movieName :: Name  -- ^ Movie title.
      , movieYear :: Year  -- ^ Release year.
      }
  | Show
      { showName  :: Name  -- ^ Show title.
      , showYear  :: Year  -- ^ First air/release year.
      }
  deriving (Eq, Ord, Show, Read)

-- | A library pairs each 'Video' with its 'Availability'.
type Library = [(Video, Availability)]

-- | Example list aligned over several lines.
exampleLibrary :: Library
exampleLibrary =
  [ ( Show  "Westworld"                            2017, False )
  , ( Movie "Harry Potter and the Prisoner of Azkaban" 2004, False )
  , ( Show  "Game of Thrones"                      2011, True  )
  , ( Movie "Thor: Ragnarok"                       2017, False )
  , ( Movie "Avengers: Endgame"                    2019, False )
  , ( Show  "Attack on Titan"                      2009, True  )
  , ( Show  "Stranger Things"                      2016, False )
  , ( Movie "Star Wars: The Force Awakens"         2015, True  )
  , ( Show  "The Walking Dead"                     2010, True  )
  , ( Movie "Deadpool"                             2016, True  )
  ]

------------------------- Exercise 3
{-|
Module      : Library
Description : Types for a small video library and 'isAvailable' by title.
-}
module Library
  ( Name, Year, Availability
  , Video(..)
  , Library
  , exampleLibrary
  , isAvailable
  ) where

-- === Exercise 2 recap (needed for Exercise 3) ===============================

-- | Title of a video.
type Name = String

-- | Release / first-air year.
type Year = Int

-- | Availability flag. 'True' = available, 'False' = not available.
type Availability = Bool

-- | A video in our catalogue.
data Video
  = Movie Name Year  -- ^ A movie with its 'Name' and release 'Year'.
  | Show  Name Year  -- ^ A TV show with its 'Name' and first-air 'Year'.
  deriving (Eq, Ord, Show, Read)

-- | The library stores each 'Video' with its 'Availability'.
type Library = [(Video, Availability)]

-- | Example catalogue (aligned over multiple lines per the style guide).
exampleLibrary :: Library
exampleLibrary =
  [ (Show  "Westworld"                        2017, False)
  , (Movie "Harry Potter and the Prisoner of Azkaban" 2004, False)
  , (Show  "Game of Thrones"                  2011, True)
  , (Movie "Thor: Ragnarok"                   2017, False)
  , (Movie "Avengers: Endgame"                2019, False)
  , (Show  "Attack on Titan"                  2009, True)
  , (Show  "Stranger Things"                  2016, False)
  , (Movie "Star Wars: The Force Awakens"     2015, True)
  , (Show  "The Walking Dead"                 2010, True)
  , (Movie "Deadpool"                         2016, True)
  ]

-- === Exercise 3 =============================================================

-- | Get the title stored inside a 'Video' value.
videoName :: Video -> Name
videoName (Movie n _) = n
videoName (Show  n _) = n

-- | Check whether a video with the given title is available in the library.
-- Returns 'True' only if the title exists and is marked available.
-- If the title is not present in the library, returns 'False'.
isAvailable :: Name -> Library -> Bool
isAvailable wanted = go
  where
    go [] = False
    go ((v, avail) : rest)
      | videoName v == wanted = avail
      | otherwise             = go rest

--- Exercise 4
{-|
Module      : Library
Description : Types for a small video library plus 'availableVideos'.
-}
module Library
  ( Name, Year, Availability
  , Video(..)
  , Library
  , exampleLibrary
  , availableVideos
  ) where

-- === Types from Exercise 2/3 =================================================

type Name = String
type Year = Int
type Availability = Bool

-- | Custom video type. We derive 'Eq' and 'Show' so values can be compared and
-- printed in the REPL and by tests.
data Video
  = Movie Name Year
  | Show  Name Year
  deriving (Eq, Show)

-- | A library stores each 'Video' with its availability flag.
type Library = [(Video, Availability)]

exampleLibrary :: Library
exampleLibrary =
  [ (Show  "Westworld"                        2017, False)
  , (Movie "Harry Potter and the Prisoner of Azkaban" 2004, False)
  , (Show  "Game of Thrones"                  2011, True)
  , (Movie "Thor: Ragnarok"                   2017, False)
  , (Movie "Avengers: Endgame"                2019, False)
  , (Show  "Attack on Titan"                  2009, True)
  , (Show  "Stranger Things"                  2016, False)
  , (Movie "Star Wars: The Force Awakens"     2015, True)
  , (Show  "The Walking Dead"                 2010, True)
  , (Movie "Deadpool"                         2016, True)
  ]

-- === Exercise 4 ===============================================================

-- | Return all videos that are currently available in the given library.
-- If none are available (or the library is empty), returns an empty list.
availableVideos :: Library -> [Video]
availableVideos =
  map fst . filter snd
  -- alternatively:
  -- \lib -> [ v | (v, True) <- lib ]

-- Exercise 5 ---
-- BoxTesting.hs
-- Exercise 5 — Black-box tests for `secondMinimum`

-- ---------- Black-box tests ----------

data TestCase = TestCase
  { testName  :: String
  , input     :: [Int]
  , expected  :: Maybe Int
  } deriving (Show)

-- | A focused set of test cases covering distinct behaviours from the spec.
blackBoxTests :: [TestCase]
blackBoxTests =
  [ -- Should return Nothing
    TestCase "empty list"                    []                 Nothing
  , TestCase "singleton"                     [7]                Nothing
  , TestCase "two equal elements"            [5,5]              Nothing
  , TestCase "all equal"                     [3,3,3,3]          Nothing

    -- Should return Just second-smallest *distinct* value
  , TestCase "two ascending"                 [1,2]              (Just 2)
  , TestCase "two descending"                [2,1]              (Just 2)
  , TestCase "duplicate minimum"             [1,1,2]            (Just 2)
  , TestCase "duplicate second"              [1,2,2,2]          (Just 2)
  , TestCase "unsorted, mixed"               [3,1,4,2]          (Just 2)
  , TestCase "negatives present"             [-10,-3,-2,-2]     (Just (-3))
  , TestCase "with zero and large numbers"   [1_000_000,-1,0,2] (Just 0)
  , TestCase "repeated maxima, several vals" [1,5,5,5,3,2]      (Just 2)
  ]

--- Exercise 6
module BoxTesting (secondMinimum) where

-- | Return the second smallest distinct value in a list of 'Int's, if any.
--   Examples:
--     secondMinimum []            == Nothing
--     secondMinimum [1]           == Nothing
--     secondMinimum [1,1]         == Nothing
--     secondMinimum [1,2]         == Just 2
--     secondMinimum [1,2,1]       == Just 2
secondMinimum :: [Int] -> Maybe Int
secondMinimum = scan Nothing Nothing
  where
    -- scan m1 m2 xs keeps current minimum m1 and second minimum m2.
    scan :: Maybe Int -> Maybe Int -> [Int] -> Maybe Int
    scan m1 m2 [] = m2
    scan Nothing m2 (x:xs) = scan (Just x) m2 xs
    scan (Just a) m2 (x:xs)
      | x == a    = scan (Just a) m2 xs
      | x <  a    = scan (Just x) (Just a) xs
      | otherwise =
          case m2 of
            Nothing -> scan (Just a) (Just x) xs
            Just b
              | x == b  -> scan (Just a) (Just b) xs
              | x <  b  -> scan (Just a) (Just x) xs
              | otherwise -> scan (Just a) (Just b) xs

-- Exercise 7
module BoxTesting (secondMinimum) where

-- Keep your Exercise 6 implementation here (or import it).
secondMinimum :: [Int] -> Maybe Int
secondMinimum = scan Nothing Nothing
  where
    scan :: Maybe Int -> Maybe Int -> [Int] -> Maybe Int
    scan m1 m2 [] = m2
    scan Nothing m2 (x:xs) = scan (Just x) m2 xs
    scan (Just a) m2 (x:xs)
      | x == a    = scan (Just a) m2 xs
      | x <  a    = scan (Just x) (Just a) xs
      | otherwise =
          case m2 of
            Nothing -> scan (Just a) (Just x) xs
            Just b
              | x == b  -> scan (Just a) (Just b) xs
              | x <  b  -> scan (Just a) (Just x) xs
              | otherwise -> scan (Just a) (Just b) xs

----------------------------------------------------------------------
-- Exercise 7: WHITE-BOX TESTS (doctest)
-- These tests specifically cover each guard/case in the code above.
-- Run them with:   doctest BoxTesting.hs
----------------------------------------------------------------------

-- Base case of recursion: empty list returns m2 (Nothing).
-- >>> secondMinimum []
-- Nothing

-- Single element: we never discover a distinct second min -> Nothing.
-- >>> secondMinimum [5]
-- Nothing

-- Seeds m1 via the (Nothing, _) branch; first candidate for m2 is created.
-- >>> secondMinimum [10, 11]
-- Just 11

-- x == a guard (duplicate minimum is ignored).
-- >>> secondMinimum [1, 1, 2, 3]
-- Just 2

-- x < a guard (new minimum; old minimum becomes second).
-- >>> secondMinimum [5, 1, 7]
-- Just 5

-- m2 == Nothing branch inside the 'otherwise' case (first candidate for m2).
-- >>> secondMinimum [1, 4]
-- Just 4

-- x == b guard (duplicate of current second is ignored).
-- >>> secondMinimum [1, 3, 4, 3, 9]
-- Just 3

-- x < b guard (we improve the current second).
-- >>> secondMinimum [1, 6, 3, 8]
-- Just 3

-- Many duplicates; ensures we don’t “skip” the true second.
-- >>> secondMinimum [2, 2, 2, 5, 5, 7]
-- Just 5

-- Negatives + duplicates to exercise ordering with < and ==.
-- >>> secondMinimum [-5, -2, -2, -1]
-- Just (-2)

-- All equal elements: no distinct second value exists.
-- >>> secondMinimum [3, 3, 3, 3]
-- Nothing

-- Exercise 8
{-|
Module      : Library
Description : Video library core + doctests for 'isAvailable' and 'availableVideos'.
-}
module Library
  ( Name, Year, Availability
  , Video(..)
  , Library
  , exampleLibrary
  , isAvailable
  , availableVideos
  ) where

-- ===== Core types (from Exercises 2–4) ======================================

type Name = String
type Year = Int
type Availability = Bool

-- | Custom video type; deriving enables printing and equality in tests/REPL.
data Video
  = Movie Name Year
  | Show  Name Year
  deriving (Eq, Show)

-- | A library maps each 'Video' to its availability flag.
type Library = [(Video, Availability)]

-- | Example catalogue (kept small but varied).
exampleLibrary :: Library
exampleLibrary =
  [ (Show  "Westworld"                        2017, False)
  , (Movie "Harry Potter and the Prisoner of Azkaban" 2004, False)
  , (Show  "Game of Thrones"                  2011, True)
  , (Movie "Thor: Ragnarok"                   2017, False)
  , (Movie "Avengers: Endgame"                2019, False)
  , (Show  "Attack on Titan"                  2009, True)
  , (Show  "Stranger Things"                  2016, False)
  , (Movie "Star Wars: The Force Awakens"     2015, True)
  , (Show  "The Walking Dead"                 2010, True)
  , (Movie "Deadpool"                         2016, True)
  ]

-- ===== Exercise 3 function (needed for tests) ===============================

-- Helper to read the stored title.
videoName :: Video -> Name
videoName (Movie n _) = n
videoName (Show  n _) = n

-- | Check whether the given title exists in the library and is available.
--
-- Black-box doctests:
--
-- >>> let lib = [ (Movie "A" 2001, True)
-- ...           , (Show  "B" 2010, False)
-- ...           , (Show  "C" 2015, True) ]
-- >>> isAvailable "A" lib
-- True
-- >>> isAvailable "B" lib
-- False
-- >>> isAvailable "Missing" lib
-- False
-- >>> isAvailable "Game of Thrones" exampleLibrary
-- True
-- >>> isAvailable "game of thrones" exampleLibrary  -- case-sensitive titles
-- False
isAvailable :: Name -> Library -> Bool
isAvailable wanted = go
  where
    go [] = False
    go ((v, avail) : rest)
      | videoName v == wanted = avail
      | otherwise             = go rest

-- ===== Exercise 4 function (needed for tests) ===============================

-- | Return all videos that are currently available.
--
-- Black-box doctests:
--
-- >>> availableVideos [] 
-- []
-- >>> let lib = [ (Movie "A" 2001, True)
-- ...           , (Show  "B" 2010, False)
-- ...           , (Show  "C" 2015, True) ]
-- >>> availableVideos lib
-- [Movie "A" 2001,Show "C" 2015]
-- >>> length (availableVideos exampleLibrary)  -- sanity check on sample data
-- 5
availableVideos :: Library -> [Video]
availableVideos = map fst . filter snd
