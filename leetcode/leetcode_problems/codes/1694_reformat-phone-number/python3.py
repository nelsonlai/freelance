"""
Problem: Reformat Phone Number
Difficulty: Easy
Tags: string

Approach: Remove non-digits, group into 3s, handle last group of 4 specially
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def reformatNumber(self, number: str) -> str:
        digits = ''.join(c for c in number if c.isdigit())
        n = len(digits)
        result = []
        
        i = 0
        while i < n:
            remaining = n - i
            if remaining > 4:
                result.append(digits[i:i+3])
                i += 3
            elif remaining == 4:
                result.append(digits[i:i+2])
                result.append(digits[i+2:i+4])
                break
            else:
                result.append(digits[i:])
                break
        
        return '-'.join(result)