"""
Problem: Prime Arrangements
Difficulty: Easy
Tags: math

Approach: Count primes using Sieve of Eratosthenes, calculate factorial of prime and non-prime counts
Time Complexity: O(n log log n) for sieve + O(n) for factorial
Space Complexity: O(n) for sieve array
"""

class Solution:
    def numPrimeArrangements(self, n: int) -> int:
        MOD = 10**9 + 7
        
        def count_primes(n):
            if n < 2:
                return 0
            is_prime = [True] * (n + 1)
            is_prime[0] = is_prime[1] = False
            for i in range(2, int(n**0.5) + 1):
                if is_prime[i]:
                    for j in range(i * i, n + 1, i):
                        is_prime[j] = False
            return sum(is_prime)
        
        def factorial_mod(k):
            result = 1
            for i in range(2, k + 1):
                result = (result * i) % MOD
            return result
        
        prime_count = count_primes(n)
        non_prime_count = n - prime_count
        
        return (factorial_mod(prime_count) * factorial_mod(non_prime_count)) % MOD