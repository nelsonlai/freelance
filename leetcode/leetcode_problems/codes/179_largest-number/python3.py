"""
Problem: Largest Number
Difficulty: Medium
Tags: array, string, greedy, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from functools import cmp_to_key

class Solution:
    def largestNumber(self, nums: List[int]) -> str:
        def compare(a, b):
            return int(str(b) + str(a)) - int(str(a) + str(b))
        
        nums_sorted = sorted(nums, key=cmp_to_key(compare))
        
        if nums_sorted[0] == 0:
            return "0"
        
        return "".join(map(str, nums_sorted))