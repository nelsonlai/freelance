"""
Problem: String to Integer (atoi)
Difficulty: Medium
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def myAtoi(self, s: str) -> int:
        INT_MAX = 2**31 - 1
        INT_MIN = -2**31
        
        s = s.strip()
        if not s:
            return 0
        
        sign = 1
        i = 0
        
        if s[0] == '-':
            sign = -1
            i = 1
        elif s[0] == '+':
            i = 1
        
        result = 0
        while i < len(s) and s[i].isdigit():
            digit = int(s[i])
            if result > (INT_MAX - digit) // 10:
                return INT_MAX if sign == 1 else INT_MIN
            result = result * 10 + digit
            i += 1
        
        return sign * result