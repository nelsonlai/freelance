"""
Problem: Numbers With Repeated Digits
Difficulty: Hard
Tags: dp, math

Approach: Count numbers without repeated digits, subtract from total
Time Complexity: O(log n)
Space Complexity: O(log n) for recursion
"""

from functools import lru_cache

class Solution:
    def numDupDigitsAtMostN(self, n: int) -> int:
        digits = list(map(int, str(n + 1)))
        
        @lru_cache(None)
        def dp(pos, tight, mask, started):
            if pos == len(digits):
                return 1 if started else 0
            
            limit = digits[pos] if tight else 9
            result = 0
            
            for d in range(limit + 1):
                new_tight = tight and (d == limit)
                new_started = started or (d > 0)
                
                if not new_started:
                    result += dp(pos + 1, new_tight, mask, new_started)
                elif mask & (1 << d) == 0:
                    result += dp(pos + 1, new_tight, mask | (1 << d), new_started)
            
            return result
        
        return n - dp(0, True, 0, False)