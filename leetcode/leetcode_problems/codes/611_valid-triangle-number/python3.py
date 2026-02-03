"""
Problem: Valid Triangle Number
Difficulty: Medium
Tags: array, greedy, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        nums.sort()
        count = 0
        for i in range(len(nums) - 2):
            k = i + 2
            for j in range(i + 1, len(nums) - 1):
                while k < len(nums) and nums[i] + nums[j] > nums[k]:
                    k += 1
                count += k - j - 1
        return count