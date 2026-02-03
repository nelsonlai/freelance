"""
Problem: Reformat The String
Difficulty: Easy
Tags: string

Approach: Separate digits and letters, interleave starting with larger group
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def reformat(self, s: str) -> str:
        digits = [c for c in s if c.isdigit()]
        letters = [c for c in s if c.isalpha()]
        
        if abs(len(digits) - len(letters)) > 1:
            return ""
        
        result = []
        if len(digits) >= len(letters):
            for i in range(len(letters)):
                result.append(digits[i])
                result.append(letters[i])
            if len(digits) > len(letters):
                result.append(digits[-1])
        else:
            for i in range(len(digits)):
                result.append(letters[i])
                result.append(digits[i])
            result.append(letters[-1])
        
        return ''.join(result)