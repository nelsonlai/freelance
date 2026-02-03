"""
Problem: 4Sum II
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def fourSumCount(self, nums1: List[int], nums2: List[int], nums3: List[int], nums4: List[int]) -> int:
        sum_count = defaultdict(int)
        for a in nums1:
            for b in nums2:
                sum_count[a + b] += 1
        
        count = 0
        for c in nums3:
            for d in nums4:
                count += sum_count[-(c + d)]
        
        return count