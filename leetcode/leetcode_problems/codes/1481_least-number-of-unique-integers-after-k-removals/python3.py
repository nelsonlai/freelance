"""
Problem: Least Number of Unique Integers after K Removals
Difficulty: Medium
Tags: array, greedy, hash, sort

Approach: Count frequencies, sort by frequency, remove from smallest frequencies first
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        freq = Counter(arr)
        sorted_freq = sorted(freq.values())
        
        removed = 0
        for count in sorted_freq:
            if k >= count:
                k -= count
                removed += 1
            else:
                break
        
        return len(sorted_freq) - removed