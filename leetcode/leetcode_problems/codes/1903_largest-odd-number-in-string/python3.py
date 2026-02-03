"""
Problem: Largest Odd Number in String
Difficulty: Easy
Tags: string, greedy

Approach: Find rightmost odd digit, return substring up to that digit
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def largestOddNumber(self, num: str) -> str:
        for i in range(len(num) - 1, -1, -1):
            if int(num[i]) % 2 == 1:
                return num[:i + 1]
        return ""