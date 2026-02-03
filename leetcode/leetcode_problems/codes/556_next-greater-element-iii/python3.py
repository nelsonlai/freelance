"""
Problem: Next Greater Element III
Difficulty: Medium
Tags: array, string, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def nextGreaterElement(self, n: int) -> int:
        digits = list(str(n))
        
        i = len(digits) - 2
        while i >= 0 and digits[i] >= digits[i + 1]:
            i -= 1
        
        if i < 0:
            return -1
        
        j = len(digits) - 1
        while digits[j] <= digits[i]:
            j -= 1
        
        digits[i], digits[j] = digits[j], digits[i]
        digits[i+1:] = reversed(digits[i+1:])
        
        result = int(''.join(digits))
        return result if result <= 2**31 - 1 else -1