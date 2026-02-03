"""
Problem: Array Nesting
Difficulty: Medium
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def arrayNesting(self, nums: List[int]) -> int:
        visited = [False] * len(nums)
        max_length = 0
        
        for i in range(len(nums)):
            if not visited[i]:
                count = 0
                j = i
                while not visited[j]:
                    visited[j] = True
                    j = nums[j]
                    count += 1
                max_length = max(max_length, count)
        
        return max_length