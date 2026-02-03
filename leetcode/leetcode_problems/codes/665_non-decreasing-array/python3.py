"""
Problem: Non-decreasing Array
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def checkPossibility(self, nums: List[int]) -> bool:
        count = 0
        for i in range(1, len(nums)):
            if nums[i] < nums[i-1]:
                count += 1
                if count > 1:
                    return False
                if i > 1 and nums[i] < nums[i-2]:
                    nums[i] = nums[i-1]
        return True