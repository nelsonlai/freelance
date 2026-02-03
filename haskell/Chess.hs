module Chess where
import ChessGraphics

data PieceType = King | Queen | Knight | Bishop | Rook | Pawn
    deriving (Eq, Show)
data Colour = White | Black
    deriving (Eq, Show)
data Piece = Piece Colour PieceType
    deriving (Eq, Show)



-- Part 0
blackSquare :: Picture
blackSquare = undefined

backRankPieces :: Picture 
backRankPieces = undefined

-- Part 1
piecePicture :: Piece -> Picture
piecePicture = undefined

-- Part 2
repeatH :: Picture -> Int -> Picture
repeatH = undefined

repeatV :: Picture -> Int -> Picture
repeatV = undefined

board :: Picture 
board = undefined

-- Part 3

combineH :: [Picture] -> Picture
combineH = undefined
combineV :: [Picture] -> Picture
combineV = undefined

type Position = (Int, Int) -- row,column
type GameState = [(Position,Piece)]

-- backdropFor :: Position -> Picture
-- piecePictureFor :: GameState -> Position -> Maybe Picture
boardFor :: GameState -> Picture
boardFor = undefined
