"""
Problem: Convert a Number to Hexadecimal
Difficulty: Easy
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def toHex(self, num: int) -> str:
        if num == 0:
            return "0"
        
        if num < 0:
            num = (1 << 32) + num
        
        hex_chars = "0123456789abcdef"
        result = []
        
        while num > 0:
            result.append(hex_chars[num % 16])
            num //= 16
        
        return ''.join(result[::-1])