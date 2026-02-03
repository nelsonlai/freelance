"""
Problem: Super Pow
Difficulty: Medium
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def superPow(self, a: int, b: List[int]) -> int:
        MOD = 1337
        
        def pow_mod(base, exp, mod):
            result = 1
            base %= mod
            while exp > 0:
                if exp % 2 == 1:
                    result = (result * base) % mod
                base = (base * base) % mod
                exp //= 2
            return result
        
        result = 1
        for digit in b:
            result = pow_mod(result, 10, MOD) * pow_mod(a, digit, MOD) % MOD
        
        return result