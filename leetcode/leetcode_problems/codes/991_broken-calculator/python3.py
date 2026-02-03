"""
Problem: Broken Calculator
Difficulty: Medium
Tags: greedy, math

Approach: Work backwards from target - divide by 2 when even, add 1 when odd
Time Complexity: O(log target)
Space Complexity: O(1)
"""

class Solution:
    def brokenCalc(self, startValue: int, target: int) -> int:
        operations = 0
        
        while target > startValue:
            if target % 2 == 0:
                target //= 2
            else:
                target += 1
            operations += 1
        
        return operations + startValue - target