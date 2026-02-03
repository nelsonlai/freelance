"""
Problem: Check if All the Integers in a Range Are Covered
Difficulty: Easy
Tags: array, hash

Approach: Mark all covered numbers, check if range is fully covered
Time Complexity: O(n * range_size) where n is ranges
Space Complexity: O(range_size)
"""

class Solution:
    def isCovered(self, ranges: List[List[int]], left: int, right: int) -> bool:
        covered = set()
        for start, end in ranges:
            for i in range(start, end + 1):
                covered.add(i)
        
        for i in range(left, right + 1):
            if i not in covered:
                return False
        
        return True