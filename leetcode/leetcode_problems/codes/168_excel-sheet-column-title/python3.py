"""
Problem: Excel Sheet Column Title
Difficulty: Easy
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def convertToTitle(self, columnNumber: int) -> str:
        result = []
        
        while columnNumber > 0:
            columnNumber -= 1
            result.append(chr(ord('A') + columnNumber % 26))
            columnNumber //= 26
        
        return "".join(reversed(result))