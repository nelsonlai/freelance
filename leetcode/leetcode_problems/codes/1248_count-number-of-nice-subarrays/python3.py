"""
Problem: Count Number of Nice Subarrays
Difficulty: Medium
Tags: array, math, hash

Approach: Convert to prefix sum problem - count subarrays with exactly k odd numbers
Time Complexity: O(n) where n is length of nums
Space Complexity: O(n) for prefix map
"""

from collections import defaultdict

class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        prefix_map = defaultdict(int)
        prefix_map[0] = 1
        prefix_sum = 0
        count = 0
        
        for num in nums:
            prefix_sum += num % 2
            count += prefix_map.get(prefix_sum - k, 0)
            prefix_map[prefix_sum] += 1
        
        return count