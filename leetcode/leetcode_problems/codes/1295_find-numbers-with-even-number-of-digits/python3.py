"""
Problem: Find Numbers with Even Number of Digits
Difficulty: Easy
Tags: array, math

Approach: Count digits for each number, check if even
Time Complexity: O(n * log(max(nums)))
Space Complexity: O(1)
"""

class Solution:
    def findNumbers(self, nums: List[int]) -> int:
        count = 0
        for num in nums:
            digits = 0
            while num > 0:
                digits += 1
                num //= 10
            if digits % 2 == 0:
                count += 1
        return count