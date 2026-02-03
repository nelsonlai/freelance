"""
Problem: The Earliest and Latest Rounds Where Players Compete
Difficulty: Hard
Tags: array, dp, recursion

Approach: Recursive DP to simulate tournament rounds
Time Complexity: O(n^2) where n is players
Space Complexity: O(n^2)
"""

from functools import lru_cache

class Solution:
    def earliestAndLatest(self, n: int, firstPlayer: int, secondPlayer: int) -> List[int]:
        @lru_cache(maxsize=None)
        def dp(players, first, second):
            if first + second == players + 1:
                return (1, 1)
            
            if first > second:
                first, second = second, first
            
            if first + second <= players + 1:
                # Both in first half
                return dp((players + 1) // 2, first, second)
            else:
                # Both in second half
                return dp((players + 1) // 2, 
                         first - (players - (players + 1) // 2),
                         second - (players - (players + 1) // 2))
        
        earliest, latest = dp(n, firstPlayer, secondPlayer)
        return [earliest, latest]