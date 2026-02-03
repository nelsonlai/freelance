"""
Problem: Two Out of Three
Difficulty: Easy
Tags: array, hash

Approach: Count occurrences in each array, return numbers appearing in at least 2 arrays
Time Complexity: O(n) where n is total elements
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def twoOutOfThree(self, nums1: List[int], nums2: List[int], nums3: List[int]) -> List[int]:
        count = defaultdict(set)
        
        for num in nums1:
            count[num].add(1)
        for num in nums2:
            count[num].add(2)
        for num in nums3:
            count[num].add(3)
        
        result = []
        for num, arrays in count.items():
            if len(arrays) >= 2:
                result.append(num)
        
        return result