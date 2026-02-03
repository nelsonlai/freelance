from functools import lru_cache

class Solution:
    def racecar(self, target: int) -> int:
        @lru_cache(None)
        def dp(t):
            n = t.bit_length()
            if t == (1 << n) - 1:
                return n
            
            result = n + 1 + dp((1 << n) - 1 - t)
            for m in range(n - 1):
                result = min(result, n + m + 1 + dp(t - (1 << (n - 1)) + (1 << m)))
            return result
        
        return dp(target)
