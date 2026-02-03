"""
Problem: Diagonal Traverse II
Difficulty: Medium
Tags: array, sort, queue, heap

Approach: Group elements by (row + col), reverse each group, concatenate
Time Complexity: O(n) where n is total elements
Space Complexity: O(n) for groups
"""

from collections import defaultdict

class Solution:
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        groups = defaultdict(list)
        
        for i in range(len(nums)):
            for j in range(len(nums[i])):
                groups[i + j].append(nums[i][j])
        
        result = []
        for key in sorted(groups.keys()):
            result.extend(reversed(groups[key]))
        
        return result