from collections import deque

class Solution:
    def openLock(self, deadends: List[str], target: str) -> int:
        dead = set(deadends)
        if "0000" in dead:
            return -1
        
        queue = deque([("0000", 0)])
        visited = {"0000"}
        
        while queue:
            state, moves = queue.popleft()
            if state == target:
                return moves
            
            for i in range(4):
                for d in [-1, 1]:
                    newState = state[:i] + str((int(state[i]) + d) % 10) + state[i+1:]
                    if newState not in visited and newState not in dead:
                        visited.add(newState)
                        queue.append((newState, moves + 1))
        
        return -1
