"""
Problem: Add to Array-Form of Integer
Difficulty: Easy
Tags: array, math

Approach: Add digit by digit from right to left, handle carry
Time Complexity: O(max(n, log k)) where n is num length
Space Complexity: O(1) excluding output
"""

class Solution:
    def addToArrayForm(self, num: List[int], k: int) -> List[int]:
        result = []
        carry = k
        i = len(num) - 1
        
        while i >= 0 or carry > 0:
            if i >= 0:
                carry += num[i]
                i -= 1
            result.append(carry % 10)
            carry //= 10
        
        return result[::-1]