"""
Problem: The kth Factor of n
Difficulty: Medium
Tags: math, sort

Approach: Find all factors up to sqrt(n), return k-th factor
Time Complexity: O(sqrt(n))
Space Complexity: O(sqrt(n)) for factors
"""

class Solution:
    def kthFactor(self, n: int, k: int) -> int:
        factors = []
        for i in range(1, int(n**0.5) + 1):
            if n % i == 0:
                factors.append(i)
                if i != n // i:
                    factors.append(n // i)
        
        factors.sort()
        return factors[k-1] if k <= len(factors) else -1