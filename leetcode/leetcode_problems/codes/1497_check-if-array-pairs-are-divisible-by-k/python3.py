"""
Problem: Check If Array Pairs Are Divisible by k
Difficulty: Medium
Tags: array, hash

Approach: Count remainders mod k, check if pairs can be formed
Time Complexity: O(n) where n is length of arr
Space Complexity: O(k) for remainder counts
"""

from collections import Counter

class Solution:
    def canArrange(self, arr: List[int], k: int) -> bool:
        remainder_count = Counter(num % k for num in arr)
        
        for remainder, count in remainder_count.items():
            if remainder == 0:
                if count % 2 != 0:
                    return False
            elif remainder * 2 == k:
                if count % 2 != 0:
                    return False
            else:
                complement = k - remainder
                if remainder_count[complement] != count:
                    return False
        
        return True