"""
Problem: Reduction Operations to Make the Array Elements Equal
Difficulty: Medium
Tags: array, sort

Approach: Sort, count how many elements need to be reduced to each level
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def reductionOperations(self, nums: List[int]) -> int:
        nums.sort()
        result = 0
        distinct = 0
        
        for i in range(1, len(nums)):
            if nums[i] != nums[i-1]:
                distinct += 1
            result += distinct
        
        return result