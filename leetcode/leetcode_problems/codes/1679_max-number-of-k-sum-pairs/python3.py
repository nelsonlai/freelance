"""
Problem: Max Number of K-Sum Pairs
Difficulty: Medium
Tags: array, hash, sort, two pointers

Approach: Use hash map to count frequencies, find pairs that sum to k
Time Complexity: O(n) where n is length
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def maxOperations(self, nums: List[int], k: int) -> int:
        freq = Counter(nums)
        result = 0
        
        for num in freq:
            complement = k - num
            if complement in freq:
                if num == complement:
                    result += freq[num] // 2
                else:
                    pairs = min(freq[num], freq[complement])
                    result += pairs
                    freq[num] = 0
                    freq[complement] = 0
        
        return result