"""
Problem: Count Square Sum Triples
Difficulty: Easy
Tags: math

Approach: Check all triplets (a, b, c) where a^2 + b^2 = c^2
Time Complexity: O(n^2) where n is limit
Space Complexity: O(1)
"""

class Solution:
    def countTriples(self, n: int) -> int:
        count = 0
        squares = {i*i: i for i in range(1, n + 1)}
        
        for a in range(1, n + 1):
            for b in range(a, n + 1):
                c_squared = a*a + b*b
                if c_squared in squares and squares[c_squared] <= n:
                    count += 2 if a != b else 1
        
        return count