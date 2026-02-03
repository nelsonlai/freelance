"""
Problem: Sort Characters By Frequency
Difficulty: Medium
Tags: string, tree, hash, sort, queue, heap

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import Counter

class Solution:
    def frequencySort(self, s: str) -> str:
        count = Counter(s)
        sorted_chars = sorted(count.items(), key=lambda x: x[1], reverse=True)
        result = []
        for char, freq in sorted_chars:
            result.append(char * freq)
        return ''.join(result)