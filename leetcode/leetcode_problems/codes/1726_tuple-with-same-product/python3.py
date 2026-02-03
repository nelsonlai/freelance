"""
Problem: Tuple with Same Product
Difficulty: Medium
Tags: array, hash

Approach: Count pairs with same product, for each product with count c, add 8 * C(c,2)
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2) for product map
"""

from collections import Counter
from math import comb

class Solution:
    def tupleSameProduct(self, nums: List[int]) -> int:
        product_count = Counter()
        n = len(nums)
        
        for i in range(n):
            for j in range(i + 1, n):
                product_count[nums[i] * nums[j]] += 1
        
        result = 0
        for count in product_count.values():
            if count >= 2:
                result += 8 * comb(count, 2)
        
        return result