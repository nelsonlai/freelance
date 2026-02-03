"""
Problem: Find Lucky Integer in an Array
Difficulty: Easy
Tags: array, hash

Approach: Count frequencies, find maximum number where count equals value
Time Complexity: O(n) where n is length of arr
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def findLucky(self, arr: List[int]) -> int:
        freq = Counter(arr)
        lucky = -1
        for num, count in freq.items():
            if num == count:
                lucky = max(lucky, num)
        return lucky