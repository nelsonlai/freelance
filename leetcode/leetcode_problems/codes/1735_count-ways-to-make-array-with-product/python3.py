"""
Problem: Count Ways to Make Array With Product
Difficulty: Hard
Tags: array, dp, math, combinatorics

Approach: Factorize product, use stars and bars to distribute factors
Time Complexity: O(q * sqrt(k)) where q is queries, k is product
Space Complexity: O(1)
"""

MOD = 10**9 + 7

class Solution:
    def waysToFillArray(self, queries: List[List[int]]) -> List[int]:
        def factorize(n):
            factors = {}
            i = 2
            while i * i <= n:
                while n % i == 0:
                    factors[i] = factors.get(i, 0) + 1
                    n //= i
                i += 1
            if n > 1:
                factors[n] = factors.get(n, 0) + 1
            return factors
        
        def comb(n, k):
            if k > n - k:
                k = n - k
            result = 1
            for i in range(k):
                result = result * (n - i) // (i + 1)
            return result % MOD
        
        result = []
        for n, k in queries:
            factors = factorize(k)
            ways = 1
            for count in factors.values():
                # Stars and bars: ways to put 'count' items into 'n' boxes
                ways = (ways * comb(n + count - 1, count)) % MOD
            result.append(ways)
        
        return result