"""
Problem: Nth Digit
Difficulty: Medium
Tags: math, search

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findNthDigit(self, n: int) -> int:
        length = 1
        count = 9
        start = 1
        
        while n > length * count:
            n -= length * count
            length += 1
            count *= 10
            start *= 10
        
        start += (n - 1) // length
        return int(str(start)[(n - 1) % length])