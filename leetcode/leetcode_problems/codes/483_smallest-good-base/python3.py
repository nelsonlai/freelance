"""
Problem: Smallest Good Base
Difficulty: Hard
Tags: string, math, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import math

class Solution:
    def smallestGoodBase(self, n: str) -> str:
        num = int(n)
        
        for m in range(int(math.log2(num)), 1, -1):
            k = int(num ** (1.0 / m))
            if k >= 2:
                total = (k ** (m + 1) - 1) // (k - 1)
                if total == num:
                    return str(k)
        
        return str(num - 1)