"""
Problem: Shuffle the Array
Difficulty: Easy
Tags: array

Approach: Interleave first n and last n elements
Time Complexity: O(n) where n is half the array length
Space Complexity: O(n) for result
"""

class Solution:
    def shuffle(self, nums: List[int], n: int) -> List[int]:
        result = []
        for i in range(n):
            result.append(nums[i])
            result.append(nums[i + n])
        return result