"""
Problem: Check if Binary String Has at Most One Segment of Ones
Difficulty: Easy
Tags: string

Approach: Check if there's a '01' pattern (which would indicate two segments)
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        return '01' not in s