"""
Problem: Maximize Number of Nice Divisors
Difficulty: Hard
Tags: math, greedy

Approach: Maximize product by using as many 3s as possible, then 2s
Time Complexity: O(log n) for exponentiation
Space Complexity: O(1)
"""

MOD = 10**9 + 7

class Solution:
    def maxNiceDivisors(self, primeFactors: int) -> int:
        if primeFactors <= 3:
            return primeFactors
        
        if primeFactors % 3 == 0:
            return pow(3, primeFactors // 3, MOD)
        elif primeFactors % 3 == 1:
            return (pow(3, (primeFactors - 4) // 3, MOD) * 4) % MOD
        else:
            return (pow(3, (primeFactors - 2) // 3, MOD) * 2) % MOD