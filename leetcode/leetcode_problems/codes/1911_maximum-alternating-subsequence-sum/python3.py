"""
Problem: Maximum Alternating Subsequence Sum
Difficulty: Medium
Tags: array, dp, greedy

Approach: DP - track max sum ending with even/odd index
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        even = 0  # max sum ending at even index (add)
        odd = 0   # max sum ending at odd index (subtract)
        
        for num in nums:
            even, odd = max(even, odd + num), max(odd, even - num)
        
        return max(even, odd)