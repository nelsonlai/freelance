from collections import deque

class Solution:
    def snakesAndLadders(self, board: List[List[int]]) -> int:
        n = len(board)
        target = n * n
        
        def get_pos(num):
            row = (num - 1) // n
            col = (num - 1) % n
            if row % 2 == 1:
                col = n - 1 - col
            row = n - 1 - row
            return row, col
        
        queue = deque([(1, 0)])
        visited = {1}
        
        while queue:
            curr, moves = queue.popleft()
            if curr == target:
                return moves
            
            for i in range(1, 7):
                next_pos = curr + i
                if next_pos > target:
                    break
                
                r, c = get_pos(next_pos)
                if board[r][c] != -1:
                    next_pos = board[r][c]
                
                if next_pos not in visited:
                    visited.add(next_pos)
                    queue.append((next_pos, moves + 1))
        
        return -1
