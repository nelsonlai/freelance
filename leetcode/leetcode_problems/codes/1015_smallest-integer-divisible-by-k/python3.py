"""
Problem: Smallest Integer Divisible by K
Difficulty: Medium
Tags: math, hash

Approach: Track remainders - if remainder repeats, no solution exists
Time Complexity: O(k)
Space Complexity: O(k) for remainder set
"""

class Solution:
    def smallestRepunitDivByK(self, k: int) -> int:
        if k % 2 == 0 or k % 5 == 0:
            return -1
        
        remainder = 0
        seen = set()
        
        for length in range(1, k + 1):
            remainder = (remainder * 10 + 1) % k
            if remainder == 0:
                return length
            if remainder in seen:
                return -1
            seen.add(remainder)
        
        return -1