"""
Problem: Sum of Square Numbers
Difficulty: Medium
Tags: array, math, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import math

class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        left = 0
        right = int(math.sqrt(c))
        
        while left <= right:
            sum_sq = left * left + right * right
            if sum_sq == c:
                return True
            elif sum_sq < c:
                left += 1
            else:
                right -= 1
        
        return False