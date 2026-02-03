"""
Problem: Find N Unique Integers Sum up to Zero
Difficulty: Easy
Tags: array, math

Approach: Return symmetric pairs: [-n//2, ..., -1, 0, 1, ..., n//2] (if odd) or without 0 (if even)
Time Complexity: O(n)
Space Complexity: O(n)
"""

class Solution:
    def sumZero(self, n: int) -> List[int]:
        result = []
        if n % 2 == 1:
            result.append(0)
        
        for i in range(1, n // 2 + 1):
            result.extend([i, -i])
        
        return result