class Solution:
    def validTicTacToe(self, board: List[str]) -> bool:
        xCount = sum(row.count('X') for row in board)
        oCount = sum(row.count('O') for row in board)
        
        def win(player):
            for i in range(3):
                if all(board[i][j] == player for j in range(3)):
                    return True
                if all(board[j][i] == player for j in range(3)):
                    return True
            if all(board[i][i] == player for i in range(3)):
                return True
            if all(board[i][2-i] == player for i in range(3)):
                return True
            return False
        
        xWin = win('X')
        oWin = win('O')
        
        if xWin and oWin:
            return False
        if xWin:
            return xCount == oCount + 1
        if oWin:
            return xCount == oCount
        return xCount == oCount or xCount == oCount + 1
