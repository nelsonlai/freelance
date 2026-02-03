"""
Problem: Three Divisors
Difficulty: Easy
Tags: math

Approach: Check if n is a perfect square of a prime number
Time Complexity: O(sqrt(n))
Space Complexity: O(1)
"""

class Solution:
    def isThree(self, n: int) -> bool:
        def is_prime(num):
            if num < 2:
                return False
            for i in range(2, int(num ** 0.5) + 1):
                if num % i == 0:
                    return False
            return True
        
        sqrt_n = int(n ** 0.5)
        return sqrt_n * sqrt_n == n and is_prime(sqrt_n)