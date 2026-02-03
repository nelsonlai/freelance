"""
Problem: Time Based Key-Value Store
Difficulty: Medium
Tags: string, hash, search

Approach: Use hash map with sorted list of timestamps, binary search for get
Time Complexity: O(1) for set, O(log n) for get
Space Complexity: O(n) for storing all key-value pairs
"""

from collections import defaultdict
import bisect

class TimeMap:

    def __init__(self):
        self.store = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.store[key].append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        if key not in self.store:
            return ""
        
        values = self.store[key]
        idx = bisect.bisect_right(values, (timestamp, chr(127)))
        
        if idx == 0:
            return ""
        return values[idx - 1][1]