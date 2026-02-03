"""
Problem: Stone Game IX
Difficulty: Medium
Tags: array, greedy, math

Approach: Count stones by remainder mod 3, analyze game strategy
Time Complexity: O(n) where n is number of stones
Space Complexity: O(1)
"""

class Solution:
    def stoneGameIX(self, stones: List[int]) -> bool:
        count = [0, 0, 0]  # count for remainder 0, 1, 2
        
        for stone in stones:
            count[stone % 3] += 1
        
        # If count[0] is even, it doesn't affect the outcome
        # If count[0] is odd, it flips the turn
        
        if count[0] % 2 == 0:
            # Even number of 0s: they cancel out
            return count[1] > 0 and count[2] > 0
        else:
            # Odd number of 0s: one extra turn
            return abs(count[1] - count[2]) > 2