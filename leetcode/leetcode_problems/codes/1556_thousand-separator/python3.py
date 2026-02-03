"""
Problem: Thousand Separator
Difficulty: Easy
Tags: string

Approach: Convert to string, add dots every 3 digits from right
Time Complexity: O(log n) where n is the number
Space Complexity: O(log n) for result string
"""

class Solution:
    def thousandSeparator(self, n: int) -> str:
        s = str(n)
        result = []
        for i, char in enumerate(reversed(s)):
            if i > 0 and i % 3 == 0:
                result.append('.')
            result.append(char)
        return ''.join(reversed(result))