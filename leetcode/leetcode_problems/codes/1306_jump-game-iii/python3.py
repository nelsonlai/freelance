"""
Problem: Jump Game III
Difficulty: Medium
Tags: array, search

Approach: BFS/DFS from start, try jumping left and right
Time Complexity: O(n) where n is length of arr
Space Complexity: O(n) for visited set
"""

from collections import deque

class Solution:
    def canReach(self, arr: List[int], start: int) -> bool:
        n = len(arr)
        queue = deque([start])
        visited = {start}
        
        while queue:
            pos = queue.popleft()
            if arr[pos] == 0:
                return True
            
            for next_pos in [pos + arr[pos], pos - arr[pos]]:
                if 0 <= next_pos < n and next_pos not in visited:
                    visited.add(next_pos)
                    queue.append(next_pos)
        
        return False