"""
Problem: Minimum Non-Zero Product of the Array Elements
Difficulty: Medium
Tags: array, greedy, math, fast exponentiation

Approach: Minimize product by pairing (2^p-2) with 1, leaving (2^p-1) alone
Time Complexity: O(p) for exponentiation
Space Complexity: O(1)
"""

class Solution:
    def minNonZeroProduct(self, p: int) -> int:
        MOD = 10**9 + 7
        max_num = (1 << p) - 1  # 2^p - 1
        pairs = (max_num - 1) // 2
        
        # (max_num - 1) ^ pairs mod MOD
        base = (max_num - 1) % MOD
        exp = pairs
        
        result = pow(base, exp, MOD)
        result = (result * max_num) % MOD
        
        return result