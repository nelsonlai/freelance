"""
Problem: Maximize Sum Of Array After K Negations
Difficulty: Easy
Tags: array, greedy, sort

Approach: Greedy - negate smallest numbers first, then smallest absolute value if k remains
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def largestSumAfterKNegations(self, nums: List[int], k: int) -> int:
        nums.sort()
        
        for i in range(len(nums)):
            if k > 0 and nums[i] < 0:
                nums[i] = -nums[i]
                k -= 1
        
        if k % 2 == 1:
            nums.sort()
            nums[0] = -nums[0]
        
        return sum(nums)