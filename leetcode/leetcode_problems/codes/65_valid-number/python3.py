"""
Problem: Valid Number
Difficulty: Hard
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isNumber(self, s: str) -> bool:
        s = s.strip()
        seen_digit = seen_dot = seen_exp = False
        
        for i, char in enumerate(s):
            if char.isdigit():
                seen_digit = True
            elif char == '.':
                if seen_dot or seen_exp:
                    return False
                seen_dot = True
            elif char in ['e', 'E']:
                if seen_exp or not seen_digit:
                    return False
                seen_exp = True
                seen_digit = False  # Reset for exponent part
            elif char in ['+', '-']:
                if i != 0 and s[i - 1] not in ['e', 'E']:
                    return False
            else:
                return False
        
        return seen_digit