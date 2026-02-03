"""
Problem: Kth Distinct String in an Array
Difficulty: Easy
Tags: array, string, hash

Approach: Count occurrences, find kth distinct string
Time Complexity: O(n) where n is length
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def kthDistinct(self, arr: List[str], k: int) -> str:
        count = Counter(arr)
        distinct_count = 0
        
        for s in arr:
            if count[s] == 1:
                distinct_count += 1
                if distinct_count == k:
                    return s
        
        return ""