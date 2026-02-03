"""
Problem: Minimum Cost to Move Chips to The Same Position
Difficulty: Easy
Tags: array, greedy, math

Approach: Count chips at even and odd positions, move smaller group (cost 1 per move)
Time Complexity: O(n) where n is length of position
Space Complexity: O(1)
"""

class Solution:
    def minCostToMoveChips(self, position: List[int]) -> int:
        even_count = sum(1 for p in position if p % 2 == 0)
        odd_count = len(position) - even_count
        return min(even_count, odd_count)