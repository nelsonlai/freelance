"""
Problem: Find Smallest Common Element in All Rows
Difficulty: Medium
Tags: array, hash, sort, search

Approach: Count frequency of each element, return smallest element appearing in all rows
Time Complexity: O(m * n) where m is rows, n is columns
Space Complexity: O(k) where k is number of unique elements
"""

class Solution:
    def smallestCommonElement(self, mat: List[List[int]]) -> int:
        from collections import Counter
        
        freq = Counter()
        for row in mat:
            for num in row:
                freq[num] += 1
        
        m = len(mat)
        candidates = [num for num, count in freq.items() if count >= m]
        
        return min(candidates) if candidates else -1