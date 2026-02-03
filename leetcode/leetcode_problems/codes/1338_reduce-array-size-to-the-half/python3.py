"""
Problem: Reduce Array Size to The Half
Difficulty: Medium
Tags: array, greedy, hash, sort, queue, heap

Approach: Count frequencies, sort descending, greedily remove most frequent
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def minSetSize(self, arr: List[int]) -> int:
        freq = Counter(arr)
        sorted_freq = sorted(freq.values(), reverse=True)
        
        removed = 0
        count = 0
        target = len(arr) // 2
        
        for f in sorted_freq:
            removed += f
            count += 1
            if removed >= target:
                break
        
        return count