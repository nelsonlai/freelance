"""
Problem: Minimum Operations to Convert Number
Difficulty: Medium
Tags: array, search, BFS

Approach: BFS to find shortest path from start to goal using operations
Time Complexity: O(n * range) where range is [0, 1000]
Space Complexity: O(range)
"""

from collections import deque

class Solution:
    def minimumOperations(self, nums: List[int], start: int, goal: int) -> int:
        queue = deque([(start, 0)])
        visited = {start}
        
        while queue:
            current, steps = queue.popleft()
            
            if current == goal:
                return steps
            
            for num in nums:
                # Try all three operations
                for next_val in [current + num, current - num, current ^ num]:
                    if next_val == goal:
                        return steps + 1
                    
                    # Only consider values in valid range [0, 1000]
                    if 0 <= next_val <= 1000 and next_val not in visited:
                        visited.add(next_val)
                        queue.append((next_val, steps + 1))
        
        return -1