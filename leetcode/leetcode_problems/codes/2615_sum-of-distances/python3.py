"""
Problem: Sum of Distances
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def distance(self, nums: List[int]) -> List[int]:
        n = len(nums)
        value_to_indices = defaultdict(list)
        for i, val in enumerate(nums):
            value_to_indices[val].append(i)
        
        result = [0] * n
        
        for indices in value_to_indices.values():
            if len(indices) == 1:
                continue
            
            prefix = [0]
            for idx in indices:
                prefix.append(prefix[-1] + idx)
            
            m = len(indices)
            for i, idx in enumerate(indices):
                left_sum = i * idx - prefix[i]
                right_sum = (prefix[m] - prefix[i + 1]) - (m - i - 1) * idx
                result[idx] = left_sum + right_sum
        
        return result