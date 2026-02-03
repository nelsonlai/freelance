"""
Problem: Range Frequency Queries
Difficulty: Medium
Tags: array, hash, binary search

Approach: Store indices for each value, use binary search for range queries
Time Complexity: O(n) init, O(log n) per query
Space Complexity: O(n)
"""

from collections import defaultdict
import bisect

class RangeFreqQuery:

    def __init__(self, arr: List[int]):
        self.indices = defaultdict(list)
        for i, val in enumerate(arr):
            self.indices[val].append(i)

    def query(self, left: int, right: int, value: int) -> int:
        if value not in self.indices:
            return 0
        
        indices = self.indices[value]
        # Find first index >= left
        left_idx = bisect.bisect_left(indices, left)
        # Find first index > right
        right_idx = bisect.bisect_right(indices, right)
        
        return right_idx - left_idx