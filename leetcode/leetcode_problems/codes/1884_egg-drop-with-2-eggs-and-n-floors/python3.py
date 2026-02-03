"""
Problem: Egg Drop With 2 Eggs and N Floors
Difficulty: Medium
Tags: dp, math

Approach: DP - dp[moves][eggs] = max floors we can test
Time Complexity: O(n) where n is floors
Space Complexity: O(1)
"""

class Solution:
    def twoEggDrop(self, n: int) -> int:
        moves = 0
        floors = 0
        
        while floors < n:
            moves += 1
            floors += moves
        
        return moves