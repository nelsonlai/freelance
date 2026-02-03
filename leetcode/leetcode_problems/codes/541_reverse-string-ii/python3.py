"""
Problem: Reverse String II
Difficulty: Easy
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def reverseStr(self, s: str, k: int) -> str:
        result = list(s)
        for i in range(0, len(result), 2 * k):
            result[i:i+k] = reversed(result[i:i+k])
        return ''.join(result)