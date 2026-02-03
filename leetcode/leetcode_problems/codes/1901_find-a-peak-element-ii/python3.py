"""
Problem: Find a Peak Element II
Difficulty: Medium
Tags: array, search, binary search

Approach: Binary search on columns, find max in each column
Time Complexity: O(m log n) where m is rows, n is columns
Space Complexity: O(1)
"""

class Solution:
    def findPeakGrid(self, mat: List[List[int]]) -> List[int]:
        m, n = len(mat), len(mat[0])
        left, right = 0, n - 1
        
        while left < right:
            mid = (left + right) // 2
            max_row = 0
            for i in range(m):
                if mat[i][mid] > mat[max_row][mid]:
                    max_row = i
            
            if mid < n - 1 and mat[max_row][mid] < mat[max_row][mid + 1]:
                left = mid + 1
            else:
                right = mid
        
        max_row = 0
        for i in range(m):
            if mat[i][left] > mat[max_row][left]:
                max_row = i
        
        return [max_row, left]