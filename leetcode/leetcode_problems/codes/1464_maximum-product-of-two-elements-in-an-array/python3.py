"""
Problem: Maximum Product of Two Elements in an Array
Difficulty: Easy
Tags: array, sort, queue, heap

Approach: Find two largest numbers, return (max1-1) * (max2-1)
Time Complexity: O(n) where n is length of nums
Space Complexity: O(1)
"""

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        max1 = max2 = 0
        for num in nums:
            if num > max1:
                max2 = max1
                max1 = num
            elif num > max2:
                max2 = num
        return (max1 - 1) * (max2 - 1)