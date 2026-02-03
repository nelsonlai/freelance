"""
Problem: Ugly Number II
Difficulty: Medium
Tags: dp, math, hash, queue, heap

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def nthUglyNumber(self, n: int) -> int:
        ugly = [1]
        i2 = i3 = i5 = 0
        
        for _ in range(1, n):
            next_ugly = min(ugly[i2] * 2, ugly[i3] * 3, ugly[i5] * 5)
            ugly.append(next_ugly)
            
            if next_ugly == ugly[i2] * 2:
                i2 += 1
            if next_ugly == ugly[i3] * 3:
                i3 += 1
            if next_ugly == ugly[i5] * 5:
                i5 += 1
        
        return ugly[n - 1]