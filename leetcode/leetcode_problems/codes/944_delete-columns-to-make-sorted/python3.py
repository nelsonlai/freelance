"""
Problem: Delete Columns to Make Sorted
Difficulty: Easy
Tags: array, string, graph, sort

Approach: Check each column to see if it's sorted
Time Complexity: O(n * m) where n is number of strings, m is length
Space Complexity: O(1)
"""

class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        count = 0
        n = len(strs)
        m = len(strs[0])
        
        for j in range(m):
            for i in range(1, n):
                if strs[i][j] < strs[i-1][j]:
                    count += 1
                    break
        
        return count