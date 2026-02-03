"""
Problem: Number of Pairs of Strings With Concatenation Equal to Target
Difficulty: Medium
Tags: array, string, hash

Approach: Count occurrences of each string, check all pairs that form target
Time Complexity: O(n * m) where n is strings, m is target length
Space Complexity: O(n)
"""

from collections import Counter

class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        count = Counter(nums)
        result = 0
        
        for i, num1 in enumerate(nums):
            for j, num2 in enumerate(nums):
                if i != j and num1 + num2 == target:
                    result += 1
        
        return result