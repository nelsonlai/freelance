"""
Problem: Count Good Numbers
Difficulty: Medium
Tags: string, math, fast exponentiation

Approach: Even positions: 5 choices (0,2,4,6,8), odd positions: 4 choices (2,3,5,7)
Time Complexity: O(log n) for exponentiation
Space Complexity: O(1)
"""

class Solution:
    def countGoodNumbers(self, n: int) -> int:
        MOD = 10**9 + 7
        
        def power(base, exp):
            result = 1
            while exp:
                if exp & 1:
                    result = (result * base) % MOD
                base = (base * base) % MOD
                exp >>= 1
            return result
        
        even_count = (n + 1) // 2
        odd_count = n // 2
        
        return (power(5, even_count) * power(4, odd_count)) % MOD