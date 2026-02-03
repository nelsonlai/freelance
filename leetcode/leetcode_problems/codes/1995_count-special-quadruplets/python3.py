"""
Problem: Count Special Quadruplets
Difficulty: Easy
Tags: array, hash

Approach: Use hash map to store nums[d] - nums[c], check for nums[a] + nums[b]
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2)
"""

from collections import defaultdict

class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        
        # nums[a] + nums[b] == nums[d] - nums[c]
        # Store nums[d] - nums[c] for all d > c
        diff_count = defaultdict(int)
        
        for c in range(n - 2, 0, -1):
            for d in range(c + 1, n):
                diff = nums[d] - nums[c]
                diff_count[diff] += 1
            
            for a in range(c):
                for b in range(a + 1, c):
                    target = nums[a] + nums[b]
                    count += diff_count.get(target, 0)
        
        return count