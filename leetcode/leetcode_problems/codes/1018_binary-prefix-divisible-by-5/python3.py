"""
Problem: Binary Prefix Divisible By 5
Difficulty: Easy
Tags: array

Approach: Track remainder modulo 5, update as we process each bit
Time Complexity: O(n)
Space Complexity: O(1) excluding output
"""

class Solution:
    def prefixesDivBy5(self, nums: List[int]) -> List[bool]:
        result = []
        remainder = 0
        
        for num in nums:
            remainder = (remainder * 2 + num) % 5
            result.append(remainder == 0)
        
        return result