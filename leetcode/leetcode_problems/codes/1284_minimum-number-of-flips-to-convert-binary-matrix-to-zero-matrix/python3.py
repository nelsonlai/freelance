"""
Problem: Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
Difficulty: Hard
Tags: array, hash, search

Approach: BFS - try all possible flip combinations, use bitmask to represent state
Time Complexity: O(2^(m*n) * m*n) in worst case
Space Complexity: O(2^(m*n)) for visited states
"""

from collections import deque

class Solution:
    def minFlips(self, mat: List[List[int]]) -> int:
        m, n = len(mat), len(mat[0])
        directions = [(0, 0), (0, 1), (1, 0), (0, -1), (-1, 0)]
        
        def encode(mat):
            state = 0
            for i in range(m):
                for j in range(n):
                    if mat[i][j]:
                        state |= 1 << (i * n + j)
            return state
        
        def flip(state, r, c):
            new_state = state
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n:
                    pos = nr * n + nc
                    new_state ^= 1 << pos
            return new_state
        
        start = encode(mat)
        if start == 0:
            return 0
        
        queue = deque([(start, 0)])
        visited = {start}
        
        while queue:
            state, flips = queue.popleft()
            
            for i in range(m):
                for j in range(n):
                    new_state = flip(state, i, j)
                    if new_state == 0:
                        return flips + 1
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((new_state, flips + 1))
        
        return -1