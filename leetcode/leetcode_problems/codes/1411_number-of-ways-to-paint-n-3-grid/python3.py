"""
Problem: Number of Ways to Paint N × 3 Grid
Difficulty: Hard
Tags: dp

Approach: DP - track patterns (ABA vs ABC), count valid transitions
Time Complexity: O(n) where n is number of rows
Space Complexity: O(1) using rolling variables
"""

class Solution:
    def numOfWays(self, n: int) -> int:
        MOD = 10**9 + 7
        aba = 6  # ABA pattern
        abc = 6  # ABC pattern
        
        for i in range(1, n):
            new_aba = (aba * 3 + abc * 2) % MOD
            new_abc = (aba * 2 + abc * 2) % MOD
            aba, abc = new_aba, new_abc
        
        return (aba + abc) % MOD