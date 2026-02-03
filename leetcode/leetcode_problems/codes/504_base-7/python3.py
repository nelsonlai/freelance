"""
Problem: Base 7
Difficulty: Easy
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def convertToBase7(self, num: int) -> str:
        if num == 0:
            return "0"
        
        negative = num < 0
        num = abs(num)
        result = []
        
        while num > 0:
            result.append(str(num % 7))
            num //= 7
        
        return ("-" if negative else "") + "".join(reversed(result))