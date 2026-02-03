"""
Problem: Hexspeak
Difficulty: Easy
Tags: string, math

Approach: Convert to hex, replace 0 with O and 1 with I, check if valid
Time Complexity: O(log num)
Space Complexity: O(log num)
"""

class Solution:
    def toHexspeak(self, num: str) -> str:
        hex_str = hex(int(num))[2:].upper()
        result = hex_str.replace('0', 'O').replace('1', 'I')
        
        valid_chars = set('ABCDEFIO')
        if all(c in valid_chars for c in result):
            return result
        return "ERROR"