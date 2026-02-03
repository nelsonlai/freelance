"""
Problem: Count Vowels Permutation
Difficulty: Hard
Tags: string, dp

Approach: DP - track count ending with each vowel, apply transition rules
Time Complexity: O(n) where n is string length
Space Complexity: O(1) using variables
"""

class Solution:
    def countVowelPermutation(self, n: int) -> int:
        MOD = 10**9 + 7
        # a, e, i, o, u
        a = e = i = o = u = 1
        
        for _ in range(n - 1):
            a_new = e
            e_new = (a + i) % MOD
            i_new = (a + e + o + u) % MOD
            o_new = (i + u) % MOD
            u_new = a
            
            a, e, i, o, u = a_new, e_new, i_new, o_new, u_new
        
        return (a + e + i + o + u) % MOD