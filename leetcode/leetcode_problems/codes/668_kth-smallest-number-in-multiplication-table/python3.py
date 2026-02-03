"""
Problem: Kth Smallest Number in Multiplication Table
Difficulty: Hard
Tags: math, search

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findKthNumber(self, m: int, n: int, k: int) -> int:
        def count_less_equal(x):
            count = 0
            for i in range(1, m + 1):
                count += min(x // i, n)
            return count
        
        left, right = 1, m * n
        
        while left < right:
            mid = (left + right) // 2
            if count_less_equal(mid) < k:
                left = mid + 1
            else:
                right = mid
        
        return left