"""
Problem: Walls and Gates
Difficulty: Medium
Tags: array, tree, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import deque

class Solution:
    def wallsAndGates(self, rooms: List[List[int]]) -> None:
        if not rooms or not rooms[0]:
            return
        
        m, n = len(rooms), len(rooms[0])
        queue = deque()
        
        for i in range(m):
            for j in range(n):
                if rooms[i][j] == 0:
                    queue.append((i, j))
        
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        while queue:
            row, col = queue.popleft()
            
            for dr, dc in directions:
                r, c = row + dr, col + dc
                if 0 <= r < m and 0 <= c < n and rooms[r][c] == 2147483647:
                    rooms[r][c] = rooms[row][col] + 1
                    queue.append((r, c))