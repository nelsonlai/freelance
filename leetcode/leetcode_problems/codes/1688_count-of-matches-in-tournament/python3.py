"""
Problem: Count of Matches in Tournament
Difficulty: Easy
Tags: math, simulation

Approach: In single elimination, n-1 matches are needed (one team eliminated per match)
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def numberOfMatches(self, n: int) -> int:
        return n - 1