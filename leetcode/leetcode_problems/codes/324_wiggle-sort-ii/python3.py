"""
Problem: Wiggle Sort II
Difficulty: Medium
Tags: array, greedy, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def wiggleSort(self, nums: List[int]) -> None:
        nums.sort()
        n = len(nums)
        mid = (n + 1) // 2
        left = nums[:mid][::-1]
        right = nums[mid:][::-1]
        
        nums[::2] = left
        nums[1::2] = right