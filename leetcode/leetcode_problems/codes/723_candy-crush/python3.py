class Solution:
    def candyCrush(self, board: List[List[int]]) -> List[List[int]]:
        m, n = len(board), len(board[0])
        stable = False
        
        while not stable:
            stable = True
            toCrush = set()
            
            for i in range(m):
                for j in range(n):
                    if board[i][j] == 0:
                        continue
                    if j < n - 2 and board[i][j] == board[i][j+1] == board[i][j+2]:
                        toCrush.update([(i, j), (i, j+1), (i, j+2)])
                    if i < m - 2 and board[i][j] == board[i+1][j] == board[i+2][j]:
                        toCrush.update([(i, j), (i+1, j), (i+2, j)])
            
            if toCrush:
                stable = False
                for i, j in toCrush:
                    board[i][j] = 0
            
            for j in range(n):
                write = m - 1
                for i in range(m - 1, -1, -1):
                    if board[i][j] != 0:
                        board[write][j] = board[i][j]
                        write -= 1
                for i in range(write, -1, -1):
                    board[i][j] = 0
        
        return board
