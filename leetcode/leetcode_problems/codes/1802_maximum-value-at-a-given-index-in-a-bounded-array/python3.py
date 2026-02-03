"""
Problem: Maximum Value at a Given Index in a Bounded Array
Difficulty: Medium
Tags: array, greedy, math, binary search

Approach: Binary search on value, calculate minimum sum for given value at index
Time Complexity: O(log(maxSum))
Space Complexity: O(1)
"""

class Solution:
    def maxValue(self, n: int, index: int, maxSum: int) -> int:
        def getSum(val, length):
            if length == 0:
                return 0
            if val >= length:
                return (val + val - length + 1) * length // 2
            return (val + 1) * val // 2 + (length - val)
        
        left, right = 1, maxSum
        result = 1
        
        while left <= right:
            mid = (left + right) // 2
            left_sum = getSum(mid - 1, index)
            right_sum = getSum(mid - 1, n - index - 1)
            total = mid + left_sum + right_sum
            
            if total <= maxSum:
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result