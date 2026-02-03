"""
Problem: K-diff Pairs in an Array
Difficulty: Medium
Tags: array, hash, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def findPairs(self, nums: List[int], k: int) -> int:
        count = Counter(nums)
        result = 0
        
        if k == 0:
            for num, cnt in count.items():
                if cnt > 1:
                    result += 1
        else:
            for num in count:
                if num + k in count:
                    result += 1
        
        return result