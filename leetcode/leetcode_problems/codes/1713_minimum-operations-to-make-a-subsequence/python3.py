"""
Problem: Minimum Operations to Make a Subsequence
Difficulty: Hard
Tags: array, greedy, hash, search, LIS

Approach: Find LCS, answer = len(target) - LCS. Use LIS with binary search for efficiency
Time Complexity: O(n log m) where n is arr length, m is target length
Space Complexity: O(m)
"""

import bisect

class Solution:
    def minOperations(self, target: List[int], arr: List[int]) -> int:
        # Map target values to indices
        index_map = {val: i for i, val in enumerate(target)}
        
        # Convert arr to indices, filter out values not in target
        indices = [index_map[val] for val in arr if val in index_map]
        
        # Find LIS of indices
        lis = []
        for idx in indices:
            pos = bisect.bisect_left(lis, idx)
            if pos == len(lis):
                lis.append(idx)
            else:
                lis[pos] = idx
        
        return len(target) - len(lis)