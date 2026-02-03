-----------------------------------------------------------------------
-- This module is heavily inspired by the graphics module in:
-- 	Haskell: The Craft of Functional Programming, 3e
-- 	Simon Thompson
-- 	(c) Addison-Wesley, 1996-2011.
--
-- This code developed by Liam O'Connor for the Australian National University
-- (c) 2025
-----------------------------------------------------------------------

-- | This module defines a graphics library for COMP1100 assignments.
--   The 'Picture' type represents images that can be displayed with 'render'.
--   Use 'above', 'beside', and 'over' to combine images together.
--   Use 'flipH', 'flipV', and 'invert' to change the appearance of images.
--   See the final section of this module for a list of built-in 'Picture's.
module ChessGraphics
  ( Picture
  , render
  -- * Combining pictures
  , above, beside, over
  -- * Altering pictures
  , flipH, flipV, invert
  -- * Built-in pictures
  , empty, whiteSquare, king, queen, bishop, knight, rook, pawn
  ) where

import System.IO ( hClose, openFile, hPutStrLn, IOMode(WriteMode) )
import Data.Set (fromList)

-- | A type for 'Picture's. 
data Picture 
 = Img String (Int, Int) Filter
 | Above Picture Picture
 | Beside Picture Picture
 | Over Picture Picture
 | Empty
   deriving (Show)


-- A Filter represents which of the actions of flipH, flipV 
-- and invert is to be applied to an image.
data Filter = Filter {fH, fV, neg :: Bool}
  deriving (Show, Eq, Ord)

instance Eq Picture where
  (==) x y = fromList (flatten (0,0) x) ==  fromList (flatten (0,0) y)

-- Coordinates are pairs (x,y) of integers
--
--  o------> x axis
--  |
--  |
--  V
--  y axis
type Point = (Int,Int)

--
-- The functions over Pictures
--
-- | Given two 'Picture's @e1@ and @e2@, @above e1 e2@ produces a 
--  'Picture' where @e1@ is placed directly above @e2@
above :: Picture -> Picture -> Picture 
above  = Above

-- | Given two 'Picture's @e1@ and @e2@, @beside e1 e2@ produces a 
--  'Picture' where @e1@ is placed directly to the left of @e2@
beside  :: Picture -> Picture -> Picture
beside = Beside

-- | Given two 'Picture's @e1@ and @e2@, @over e1 e2@ produces a 
--  'Picture' where @e1@ is placed directly on top of @e2@
over :: Picture -> Picture -> Picture 
over   = Over


-- | The empty picture, containing no image.
empty :: Picture 
empty = Empty

-- | Given a 'Picture', 'flipH' produces a 'Picture' which is flipped along the horizontal axis.
flipH :: Picture -> Picture
flipH pic = case pic of 
  Above pic1 pic2  -> Above (flipH pic2) (flipH pic1)
  Beside pic1 pic2 -> Beside (flipH pic1) (flipH pic2)
  Over pic1 pic2   -> Over (flipH pic1) (flipH pic2)
  Img fn sz fil    -> Img fn sz (fil {fH = not (fH fil)})
  Empty            -> Empty

-- | Given a 'Picture', 'flipV' produces a 'Picture' which is flipped along the vertical axis.
flipV :: Picture -> Picture 
flipV pic = case pic of 
  Above pic1 pic2  -> Above (flipV pic1) (flipV pic2)
  Beside pic1 pic2 -> Beside (flipV pic2) (flipV pic1)
  Over pic1 pic2   -> Over (flipV pic1) (flipV pic2)
  Img fn sz fil    -> Img fn sz (fil {fV = not (fV fil)})
  Empty            -> Empty

-- | Given a 'Picture', 'invert' produces a 'Picture' which has each pixel colour inverted 
--  (i.e. white becomes black and vice versa).
invert :: Picture -> Picture 
invert pic = case pic of
  Above pic1 pic2  -> Above (invert pic1) (invert pic2)
  Beside pic1 pic2 -> Beside (invert pic1) (invert pic2)
  Over pic1 pic2   -> Over (invert pic1) (invert pic2)
  Img fn sz fil    -> Img fn sz (fil {neg = not (neg fil)})
  Empty            -> Empty

width :: Picture -> Int
width pic = case pic of 
  Img _ (x,_) _    -> x 
  Above pic1 pic2  -> max (width pic1) (width pic2)
  Beside pic1 pic2 -> width pic1 + width pic2
  Over pic1 pic2   -> max (width pic1) (width pic2)
  Empty            -> 0

height :: Picture -> Int
height pic = case pic of 
  Img _ (_,y) _    -> y 
  Above pic1 pic2  -> height pic1 + height pic2
  Beside pic1 pic2 -> max (height pic1) (height pic2)
  Over pic1 pic2   -> max (height pic1) (height pic2)
  Empty            -> 0

-- Converting pictures to a list of basic images.
data Basic = Basic String (Int, Int) Point Filter
  deriving (Show, Ord, Eq)

-- Flatten a picture into a list of Basic pictures.
-- The Point argument gives the origin for the coversion of the
-- argument.
flatten :: Point -> Picture -> [Basic]
flatten (x,y) pic = case pic of 
  Img image sz fil -> [Basic image sz (x,y) fil] 
  Above pic1 pic2  -> flatten (x,y) pic1 ++ flatten (x, y + height pic1) pic2
  Beside pic1 pic2 -> flatten (x,y) pic1 ++ flatten (x + width pic1 , y) pic2
  Over pic1 pic2   -> flatten (x,y) pic2 ++ flatten (x,y) pic1
  Empty            -> []
-- Convert a Basic picture to an SVG image, represented by a String.
convert :: Basic -> String
convert (Basic piece (w, h) (x,y) (Filter fH fV neg))
  = "\n  <image x=\"" ++ show x ++ 
    "\" y=\"" ++ show y ++ "\" width=\"" ++ show w ++ 
    "\" height=\"" ++ show h ++ "\" xlink:href=\"" ++ piece ++ "\"" ++ 
    flipPart ++ negPart ++ "/>\n"
  where
    flipPart 
      | fH && not fV = " transform=\"translate(0," ++ show (2*y + h) ++ ") scale(1,-1)\" " 
      | fV && not fH = " transform=\"translate(" ++ show (2*x + w) ++ ",0) scale(-1,1)\" " 
      | fV && fH     = " transform=\"translate(" ++ show (2*x + w) ++ "," ++ 
                       show (2*y + h) ++ ") scale(-1,-1)\" " 
      | otherwise    = ""
    negPart 
      | neg       = " filter=\"url(#negative)\"" 
      | otherwise = "" 


-- | Outputting a picture. Given a 'Picture' @pic@, the command @render pic@ will
--   save an image to a SVG file called @svgOut.svg@.
-- 
-- The provided @showPic.html@ file can be used, when opened in a browser, to view 
-- the produced SVG image.
render :: Picture -> IO ()
render pic = do
    outh <- openFile "svgOut.svg" WriteMode
    hPutStrLn outh newFile
    hClose outh
  where
    picList = flatten (0,0) pic
    svgString = concat (map convert picList)
    newFile = preamble ++ svgString ++ postamble
    preamble = 
      "<svg width=\"100%\" height=\"100%\" version=\"1.1\"\n" ++
      "xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n" ++
      "<filter id=\"negative\" color-interpolation-filters=\"sRGB\">"++
      "<feColorMatrix in=\"SourceGraphic\" type=\"matrix\" values=\"" ++ 
      "-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0\"/> </filter>\n"
    postamble = "\n</svg>\n"

whiteSquare,king,queen,bishop,knight,rook,pawn :: Picture
whiteSquare = Img "images/white.png"  (50,50) (Filter False False False)
king        = Img "images/king.png"   (50,50) (Filter False False False)
queen       = Img "images/queen.png"  (50,50) (Filter False False False)
bishop      = Img "images/bishop.png" (50,50) (Filter False False False)
knight      = Img "images/knight.png" (50,50) (Filter False False False)
rook        = Img "images/rook.png"   (50,50) (Filter False False False)
pawn        = Img "images/pawn.png"   (50,50) (Filter False False False)

