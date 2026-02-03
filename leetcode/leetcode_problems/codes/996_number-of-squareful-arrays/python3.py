"""
Problem: Number of Squareful Arrays
Difficulty: Hard
Tags: array, dp, math, hash

Approach: Backtracking with memoization - generate permutations where adjacent sum is perfect square
Time Complexity: O(n!) in worst case
Space Complexity: O(n) for recursion stack
"""

from collections import Counter
from math import sqrt

class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        count = Counter(nums)
        
        def is_square(n):
            root = int(sqrt(n))
            return root * root == n
        
        def backtrack(prev, remaining):
            if remaining == 0:
                return 1
            
            result = 0
            for num in list(count.keys()):
                if count[num] == 0:
                    continue
                if prev is None or is_square(prev + num):
                    count[num] -= 1
                    result += backtrack(num, remaining - 1)
                    count[num] += 1
            
            return result
        
        return backtrack(None, len(nums))