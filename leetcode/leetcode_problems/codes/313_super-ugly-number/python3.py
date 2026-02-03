"""
Problem: Super Ugly Number
Difficulty: Medium
Tags: array, dp, math, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def nthSuperUglyNumber(self, n: int, primes: List[int]) -> int:
        ugly = [1]
        indices = [0] * len(primes)
        
        for _ in range(1, n):
            next_ugly = min(ugly[indices[i]] * primes[i] for i in range(len(primes)))
            ugly.append(next_ugly)
            
            for i in range(len(primes)):
                if ugly[indices[i]] * primes[i] == next_ugly:
                    indices[i] += 1
        
        return ugly[n - 1]