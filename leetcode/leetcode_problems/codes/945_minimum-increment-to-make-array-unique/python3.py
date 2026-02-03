"""
Problem: Minimum Increment to Make Array Unique
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort array, then increment duplicates to next available value
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minIncrementForUnique(self, nums: List[int]) -> int:
        nums.sort()
        moves = 0
        expected = 0
        
        for num in nums:
            if num < expected:
                moves += expected - num
            expected = max(expected, num) + 1
        
        return moves