"""
Problem: License Key Formatting
Difficulty: Easy
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        s = s.replace('-', '').upper()
        n = len(s)
        first_group = n % k if n % k != 0 else k
        result = s[:first_group]
        
        for i in range(first_group, n, k):
            result += '-' + s[i:i+k]
        
        return result