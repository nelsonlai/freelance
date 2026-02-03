"""
Problem: Minimum Difference Between Largest and Smallest Value in Three Moves
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort, try removing 0-3 smallest and 0-3 largest, find minimum difference
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minDifference(self, nums: List[int]) -> int:
        if len(nums) <= 4:
            return 0
        
        nums.sort()
        n = len(nums)
        
        # Try all combinations: remove i smallest and (3-i) largest
        result = float('inf')
        for i in range(4):
            result = min(result, nums[n - 1 - (3 - i)] - nums[i])
        
        return result