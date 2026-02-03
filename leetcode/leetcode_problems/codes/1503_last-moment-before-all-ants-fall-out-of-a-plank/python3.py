"""
Problem: Last Moment Before All Ants Fall Out of a Plank
Difficulty: Medium
Tags: array

Approach: Ants passing each other is equivalent to passing through. Max time is max distance from left or (n - min distance from right)
Time Complexity: O(n) where n is length of arrays
Space Complexity: O(1)
"""

class Solution:
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:
        max_left = max(left) if left else 0
        min_right = min(right) if right else n
        return max(max_left, n - min_right)