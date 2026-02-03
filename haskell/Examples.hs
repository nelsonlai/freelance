{-# OPTIONS_GHC -fno-warn-unused-imports #-}
module Examples where
import Chess
import ChessGraphics(render)


emptyBoard :: GameState
emptyBoard = []

starting :: GameState
starting =
  [ ((0,0),Piece Black Rook)
  , ((0,1),Piece Black Knight)
  , ((0,2),Piece Black Bishop)
  , ((0,3),Piece Black Queen)
  , ((0,4),Piece Black King)
  , ((0,5),Piece Black Bishop)
  , ((0,6),Piece Black Knight)
  , ((0,7),Piece Black Rook)
  , ((1,0),Piece Black Pawn)
  , ((1,1),Piece Black Pawn)
  , ((1,2),Piece Black Pawn)
  , ((1,3),Piece Black Pawn)
  , ((1,4),Piece Black Pawn)
  , ((1,5),Piece Black Pawn)
  , ((1,6),Piece Black Pawn)
  , ((1,7),Piece Black Pawn)
  , ((6,0),Piece White Pawn)
  , ((6,1),Piece White Pawn)
  , ((6,2),Piece White Pawn)
  , ((6,3),Piece White Pawn)
  , ((6,4),Piece White Pawn)
  , ((6,5),Piece White Pawn)
  , ((6,6),Piece White Pawn)
  , ((6,7),Piece White Pawn)
  , ((7,0),Piece White Rook)
  , ((7,1),Piece White Knight)
  , ((7,2),Piece White Bishop)
  , ((7,3),Piece White Queen)
  , ((7,4),Piece White King)
  , ((7,5),Piece White Bishop)
  , ((7,6),Piece White Knight)
  , ((7,7),Piece White Rook)
  ]

scholarsMate:: GameState
scholarsMate =
  [ ((0,0),Piece Black Rook)
  , ((2,2),Piece Black Knight)
  , ((0,2),Piece Black Bishop)
  , ((0,3),Piece Black Queen)
  , ((0,4),Piece Black King)
  , ((0,5),Piece Black Bishop)
  , ((2,5),Piece Black Knight)
  , ((0,7),Piece Black Rook)
  , ((1,0),Piece Black Pawn)
  , ((1,1),Piece Black Pawn)
  , ((1,2),Piece Black Pawn)
  , ((1,3),Piece Black Pawn)
  , ((3,4),Piece Black Pawn)
  , ((1,6),Piece Black Pawn)
  , ((1,7),Piece Black Pawn)
  , ((6,0),Piece White Pawn)
  , ((6,1),Piece White Pawn)
  , ((6,2),Piece White Pawn)
  , ((6,3),Piece White Pawn)
  , ((4,4),Piece White Pawn)
  , ((6,5),Piece White Pawn)
  , ((6,6),Piece White Pawn)
  , ((6,7),Piece White Pawn)
  , ((7,0),Piece White Rook)
  , ((7,1),Piece White Knight)
  , ((7,2),Piece White Bishop)
  , ((1,5),Piece White Queen)
  , ((7,4),Piece White King)
  , ((4,2),Piece White Bishop)
  , ((7,6),Piece White Knight)
  , ((7,7),Piece White Rook)
  ]

