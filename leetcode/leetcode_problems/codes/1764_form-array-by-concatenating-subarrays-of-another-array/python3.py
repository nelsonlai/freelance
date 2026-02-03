"""
Problem: Form Array by Concatenating Subarrays of Another Array
Difficulty: Medium
Tags: array, string, greedy, two pointers

Approach: Greedy matching - try to match each group sequentially in nums
Time Complexity: O(n * m) where n is nums length, m is max group length
Space Complexity: O(1)
"""

class Solution:
    def canChoose(self, groups: List[List[int]], nums: List[int]) -> bool:
        i = 0
        for group in groups:
            found = False
            while i <= len(nums) - len(group):
                if nums[i:i+len(group)] == group:
                    i += len(group)
                    found = True
                    break
                i += 1
            if not found:
                return False
        return True