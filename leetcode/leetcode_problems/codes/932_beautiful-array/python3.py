"""
Problem: Beautiful Array
Difficulty: Medium
Tags: array, math

Approach: Divide and conquer - split into odd and even parts, recursively build beautiful arrays
Time Complexity: O(n log n)
Space Complexity: O(n log n) for recursion stack
"""

class Solution:
    def beautifulArray(self, n: int) -> List[int]:
        memo = {1: [1]}
        
        def f(N):
            if N not in memo:
                odds = [2 * x - 1 for x in f((N + 1) // 2)]
                evens = [2 * x for x in f(N // 2)]
                memo[N] = odds + evens
            return memo[N]
        
        return f(n)