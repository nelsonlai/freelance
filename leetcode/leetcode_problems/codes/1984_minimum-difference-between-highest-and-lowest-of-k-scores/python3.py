"""
Problem: Minimum Difference Between Highest and Lowest of K Scores
Difficulty: Easy
Tags: array, sort, sliding window

Approach: Sort and use sliding window of size k
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        nums.sort()
        min_diff = float('inf')
        
        for i in range(len(nums) - k + 1):
            min_diff = min(min_diff, nums[i + k - 1] - nums[i])
        
        return min_diff