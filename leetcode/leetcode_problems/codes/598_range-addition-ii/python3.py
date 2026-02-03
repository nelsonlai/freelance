"""
Problem: Range Addition II
Difficulty: Easy
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def maxCount(self, m: int, n: int, ops: List[List[int]]) -> int:
        if not ops:
            return m * n
        
        min_row = min(op[0] for op in ops)
        min_col = min(op[1] for op in ops)
        
        return min_row * min_col