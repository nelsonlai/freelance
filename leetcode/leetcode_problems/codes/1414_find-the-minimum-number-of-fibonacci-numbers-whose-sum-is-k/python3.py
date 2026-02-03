"""
Problem: Find the Minimum Number of Fibonacci Numbers Whose Sum Is K
Difficulty: Medium
Tags: greedy, math

Approach: Generate Fibonacci numbers up to k, greedily subtract largest
Time Complexity: O(log k)
Space Complexity: O(log k) for Fibonacci list
"""

class Solution:
    def findMinFibonacciNumbers(self, k: int) -> int:
        fib = [1, 1]
        while fib[-1] < k:
            fib.append(fib[-1] + fib[-2])
        
        count = 0
        i = len(fib) - 1
        while k > 0:
            if fib[i] <= k:
                k -= fib[i]
                count += 1
            i -= 1
        
        return count