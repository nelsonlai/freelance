"""
Problem: Ugly Number III
Difficulty: Medium
Tags: math, search

Approach: Binary search + inclusion-exclusion principle to count numbers divisible by a, b, or c
Time Complexity: O(log(max_val)) where max_val is the search range
Space Complexity: O(1)
"""

import math

class Solution:
    def nthUglyNumber(self, n: int, a: int, b: int, c: int) -> int:
        def lcm(x, y):
            return x * y // math.gcd(x, y)
        
        ab = lcm(a, b)
        ac = lcm(a, c)
        bc = lcm(b, c)
        abc = lcm(ab, c)
        
        def count_ugly(num):
            return (num // a + num // b + num // c 
                   - num // ab - num // ac - num // bc 
                   + num // abc)
        
        left, right = 1, 2 * 10**9
        while left < right:
            mid = (left + right) // 2
            if count_ugly(mid) < n:
                left = mid + 1
            else:
                right = mid
        
        return left