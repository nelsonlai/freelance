class Solution:
    def movesToChessboard(self, board: List[List[int]]) -> int:
        n = len(board)
        
        for i in range(n):
            for j in range(n):
                if board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j]:
                    return -1
        
        rowSum = sum(board[0])
        colSum = sum(board[i][0] for i in range(n))
        
        if rowSum < n // 2 or rowSum > (n + 1) // 2:
            return -1
        if colSum < n // 2 or colSum > (n + 1) // 2:
            return -1
        
        rowSwap = 0
        colSwap = 0
        
        for i in range(n):
            if board[i][0] == i % 2:
                rowSwap += 1
            if board[0][i] == i % 2:
                colSwap += 1
        
        if n % 2 == 1:
            if rowSwap % 2 == 1:
                rowSwap = n - rowSwap
            if colSwap % 2 == 1:
                colSwap = n - colSwap
        else:
            rowSwap = min(rowSwap, n - rowSwap)
            colSwap = min(colSwap, n - colSwap)
        
        return (rowSwap + colSwap) // 2
