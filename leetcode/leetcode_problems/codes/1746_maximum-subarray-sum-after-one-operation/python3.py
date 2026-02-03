"""
Problem: Maximum Subarray Sum After One Operation
Difficulty: Medium
Tags: array, dp

Approach: DP - track max sum with and without squaring one element
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maxSumAfterOperation(self, nums: List[int]) -> int:
        no_square = 0  # Max sum without squaring
        with_square = 0  # Max sum with one squared element
        result = float('-inf')
        
        for num in nums:
            # Update with square: either square current or add to previous with square
            with_square = max(num * num, with_square + num, no_square + num * num)
            # Update without square: Kadane's algorithm
            no_square = max(num, no_square + num)
            result = max(result, with_square)
        
        return result