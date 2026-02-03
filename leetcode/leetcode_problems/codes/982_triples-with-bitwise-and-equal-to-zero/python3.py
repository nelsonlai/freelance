"""
Problem: Triples with Bitwise AND Equal To Zero
Difficulty: Hard
Tags: array, hash

Approach: Count pairs with AND result, then count triplets
Time Complexity: O(n^2 + n * 2^16) where n is array length
Space Complexity: O(2^16) for pair counts
"""

from collections import defaultdict

class Solution:
    def countTriplets(self, nums: List[int]) -> int:
        pair_count = defaultdict(int)
        
        # Count all pairs
        for i in range(len(nums)):
            for j in range(len(nums)):
                pair_count[nums[i] & nums[j]] += 1
        
        # Count triplets
        result = 0
        for num in nums:
            for pair_and, count in pair_count.items():
                if (num & pair_and) == 0:
                    result += count
        
        return result