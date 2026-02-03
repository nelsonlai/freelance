"""
Problem: Digit Count in Range
Difficulty: Hard
Tags: dp, math

Approach: Count digits in [0, high] - count digits in [0, low-1]
Time Complexity: O(log n) where n is the number
Space Complexity: O(log n) for recursion
"""

from functools import lru_cache

class Solution:
    def digitsCount(self, d: int, low: int, high: int) -> int:
        def count_digits(n):
            s = str(n)
            @lru_cache(None)
            def dp(pos, tight, has_started, count):
                if pos == len(s):
                    return count
                
                limit = int(s[pos]) if tight else 9
                result = 0
                
                for digit in range(limit + 1):
                    new_tight = tight and (digit == limit)
                    new_started = has_started or (digit > 0)
                    new_count = count + (1 if digit == d and new_started else 0)
                    result += dp(pos + 1, new_tight, new_started, new_count)
                
                return result
            
            return dp(0, True, False, 0)
        
        return count_digits(high) - count_digits(low - 1)