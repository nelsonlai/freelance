"""
Problem: Number of Unique Good Subsequences
Difficulty: Hard
Tags: string, dp

Approach: DP - track count of subsequences ending with 0 and 1, handle leading zeros
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def numberOfUniqueGoodSubsequences(self, binary: str) -> int:
        MOD = 10**9 + 7
        ends_with_0 = 0
        ends_with_1 = 0
        has_zero = False
        
        for char in binary:
            if char == '0':
                has_zero = True
                ends_with_0 = (ends_with_0 + ends_with_1) % MOD
            else:
                ends_with_1 = (ends_with_0 + ends_with_1 + 1) % MOD
        
        result = (ends_with_0 + ends_with_1) % MOD
        if has_zero:
            result = (result + 1) % MOD
        
        return result