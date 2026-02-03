"""
Problem: Finding Pairs With a Certain Sum
Difficulty: Medium
Tags: array, hash

Approach: Use hash map to count nums2, update on add
Time Complexity: O(1) for count, O(1) for add
Space Complexity: O(n)
"""

from collections import Counter

class FindSumPairs:

    def __init__(self, nums1: List[int], nums2: List[int]):
        self.nums1 = nums1
        self.nums2 = nums2
        self.count2 = Counter(nums2)

    def add(self, index: int, val: int) -> None:
        old_val = self.nums2[index]
        self.count2[old_val] -= 1
        if self.count2[old_val] == 0:
            del self.count2[old_val]
        
        new_val = old_val + val
        self.nums2[index] = new_val
        self.count2[new_val] = self.count2.get(new_val, 0) + 1

    def count(self, tot: int) -> int:
        result = 0
        for num in self.nums1:
            target = tot - num
            result += self.count2.get(target, 0)
        return result