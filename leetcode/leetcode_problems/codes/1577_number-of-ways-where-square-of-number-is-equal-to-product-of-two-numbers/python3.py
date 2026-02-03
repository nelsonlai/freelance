"""
Problem: Number of Ways Where Square of Number Is Equal to Product of Two Numbers
Difficulty: Medium
Tags: array, math, hash

Approach: For each square in nums1, count pairs in nums2. Do same for nums2.
Time Complexity: O(n^2 + m^2) where n, m are array lengths
Space Complexity: O(n + m) for frequency maps
"""

from collections import Counter

class Solution:
    def numTriplets(self, nums1: List[int], nums2: List[int]) -> int:
        def count_triplets(arr1, arr2):
            result = 0
            freq = Counter(arr2)
            
            for num in arr1:
                target = num * num
                for a in freq:
                    if target % a == 0:
                        b = target // a
                        if b in freq:
                            if a == b:
                                result += freq[a] * (freq[a] - 1)
                            else:
                                result += freq[a] * freq[b]
            
            return result // 2
        
        return count_triplets(nums1, nums2) + count_triplets(nums2, nums1)