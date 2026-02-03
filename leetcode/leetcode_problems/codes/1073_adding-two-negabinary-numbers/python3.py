"""
Problem: Adding Two Negabinary Numbers
Difficulty: Medium
Tags: array, math

Approach: Add digit by digit, handle carries in base -2
Time Complexity: O(max(len(arr1), len(arr2)))
Space Complexity: O(max(len(arr1), len(arr2)))
"""

class Solution:
    def addNegabinary(self, arr1: List[int], arr2: List[int]) -> List[int]:
        result = []
        carry = 0
        i, j = len(arr1) - 1, len(arr2) - 1
        
        while i >= 0 or j >= 0 or carry:
            total = carry
            if i >= 0:
                total += arr1[i]
                i -= 1
            if j >= 0:
                total += arr2[j]
                j -= 1
            
            result.append(total & 1)
            carry = -(total >> 1)
        
        while len(result) > 1 and result[-1] == 0:
            result.pop()
        
        return result[::-1]