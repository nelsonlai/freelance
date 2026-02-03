"""
Problem: Delete Characters to Make Fancy String
Difficulty: Easy
Tags: string, greedy

Approach: Remove characters that appear 3+ times consecutively
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def makeFancyString(self, s: str) -> str:
        result = []
        for i, char in enumerate(s):
            if len(result) >= 2 and result[-1] == result[-2] == char:
                continue
            result.append(char)
        return ''.join(result)