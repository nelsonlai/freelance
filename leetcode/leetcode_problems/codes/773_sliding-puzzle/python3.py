from collections import deque

class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:
        target = "123450"
        start = ''.join(str(num) for row in board for num in row)
        
        neighbors = {
            0: [1, 3],
            1: [0, 2, 4],
            2: [1, 5],
            3: [0, 4],
            4: [1, 3, 5],
            5: [2, 4]
        }
        
        queue = deque([(start, 0)])
        visited = {start}
        
        while queue:
            state, moves = queue.popleft()
            if state == target:
                return moves
            
            zeroIdx = state.index('0')
            for neighbor in neighbors[zeroIdx]:
                newState = list(state)
                newState[zeroIdx], newState[neighbor] = newState[neighbor], newState[zeroIdx]
                newStateStr = ''.join(newState)
                if newStateStr not in visited:
                    visited.add(newStateStr)
                    queue.append((newStateStr, moves + 1))
        
        return -1
