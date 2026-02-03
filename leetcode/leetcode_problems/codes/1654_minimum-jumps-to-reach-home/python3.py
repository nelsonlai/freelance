"""
Problem: Minimum Jumps to Reach Home
Difficulty: Medium
Tags: array, dp, search, bfs

Approach: BFS - try forward and backward jumps, avoid forbidden positions
Time Complexity: O(max_pos) where max_pos is maximum reachable position
Space Complexity: O(max_pos) for visited set
"""

from collections import deque

class Solution:
    def minimumJumps(self, forbidden: List[int], a: int, b: int, x: int) -> int:
        forbidden_set = set(forbidden)
        max_pos = max(forbidden) + a + b + x if forbidden else x + a + b
        
        queue = deque([(0, 0, False)])  # (position, jumps, was_backward)
        visited = {(0, False)}
        
        while queue:
            pos, jumps, was_backward = queue.popleft()
            
            if pos == x:
                return jumps
            
            # Forward jump
            next_pos = pos + a
            if next_pos <= max_pos and next_pos not in forbidden_set and (next_pos, False) not in visited:
                visited.add((next_pos, False))
                queue.append((next_pos, jumps + 1, False))
            
            # Backward jump (only if previous jump was forward)
            if not was_backward:
                next_pos = pos - b
                if next_pos >= 0 and next_pos not in forbidden_set and (next_pos, True) not in visited:
                    visited.add((next_pos, True))
                    queue.append((next_pos, jumps + 1, True))
        
        return -1