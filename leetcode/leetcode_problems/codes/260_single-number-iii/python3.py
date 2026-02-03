"""
Problem: Single Number III
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def singleNumber(self, nums: List[int]) -> List[int]:
        xor = 0
        for num in nums:
            xor ^= num
        
        diff = xor & (-xor)
        
        x = 0
        for num in nums:
            if num & diff:
                x ^= num
        
        return [x, xor ^ x]