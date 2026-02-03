"""
Problem: Missing Number In Arithmetic Progression
Difficulty: Easy
Tags: array, math

Approach: Calculate expected sum vs actual sum, or use binary search to find gap
Time Complexity: O(n) for sum approach, O(log n) for binary search
Space Complexity: O(1)
"""

class Solution:
    def missingNumber(self, arr: List[int]) -> int:
        n = len(arr)
        expected_sum = (arr[0] + arr[-1]) * (n + 1) // 2
        actual_sum = sum(arr)
        return expected_sum - actual_sum