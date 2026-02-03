"""
Problem: The K Weakest Rows in a Matrix
Difficulty: Easy
Tags: array, sort, search, queue, heap

Approach: Count soldiers in each row, sort by count then index, return first k
Time Complexity: O(m * n + m log m) where m, n are matrix dimensions
Space Complexity: O(m) for row strengths
"""

class Solution:
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
        row_strength = [(sum(row), i) for i, row in enumerate(mat)]
        row_strength.sort()
        return [i for _, i in row_strength[:k]]