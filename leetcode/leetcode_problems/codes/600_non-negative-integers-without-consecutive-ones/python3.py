"""
Problem: Non-negative Integers without Consecutive Ones
Difficulty: Hard
Tags: dp

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findIntegers(self, n: int) -> int:
        fib = [1, 2]
        for i in range(2, 32):
            fib.append(fib[i-1] + fib[i-2])
        
        result = 0
        prev_bit = 0
        
        for i in range(30, -1, -1):
            if (n >> i) & 1:
                result += fib[i]
                if prev_bit:
                    return result
                prev_bit = 1
            else:
                prev_bit = 0
        
        return result + 1