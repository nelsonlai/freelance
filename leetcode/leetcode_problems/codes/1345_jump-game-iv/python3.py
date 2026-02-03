"""
Problem: Jump Game IV
Difficulty: Hard
Tags: array, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict, deque

class Solution:
    def minJumps(self, arr: List[int]) -> int:
        n = len(arr)
        if n == 1:
            return 0
        
        value_to_indices = defaultdict(list)
        for i, val in enumerate(arr):
            value_to_indices[val].append(i)
        
        queue = deque([0])
        visited = {0}
        steps = 0
        
        while queue:
            size = len(queue)
            for _ in range(size):
                curr = queue.popleft()
                
                if curr == n - 1:
                    return steps
                
                # Check neighbors
                for neighbor in [curr - 1, curr + 1]:
                    if 0 <= neighbor < n and neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
                
                # Check same values
                for neighbor in value_to_indices[arr[curr]]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
                
                # Clear to avoid revisiting
                value_to_indices[arr[curr]] = []
            
            steps += 1
        
        return steps