"""
Problem: Missing Ranges
Difficulty: Easy
Tags: array, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        result = []
        prev = lower - 1
        
        for num in nums:
            if prev + 1 < num:
                result.append([prev + 1, num - 1])
            prev = num
        
        if prev < upper:
            result.append([prev + 1, upper])
        
        return result