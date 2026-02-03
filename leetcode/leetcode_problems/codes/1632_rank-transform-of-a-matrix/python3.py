"""
Problem: Rank Transform of a Matrix
Difficulty: Hard
Tags: array, graph, sort, union-find

Approach: Group equal values by row/column using Union-Find, assign ranks in sorted order
Time Complexity: O(m * n * log(m * n))
Space Complexity: O(m * n)
"""

from collections import defaultdict

class Solution:
    def matrixRankTransform(self, matrix: List[List[int]]) -> List[List[int]]:
        m, n = len(matrix), len(matrix[0])
        parent = list(range(m * n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        # Group same values in same row
        for i in range(m):
            row_values = {}
            for j in range(n):
                val = matrix[i][j]
                if val in row_values:
                    union(i * n + j, row_values[val])
                row_values[val] = i * n + j
        
        # Group same values in same column
        for j in range(n):
            col_values = {}
            for i in range(m):
                val = matrix[i][j]
                if val in col_values:
                    union(i * n + j, col_values[val])
                col_values[val] = i * n + j
        
        # Group by value and root
        groups = defaultdict(list)
        for i in range(m):
            for j in range(n):
                root = find(i * n + j)
                groups[(matrix[i][j], root)].append((i, j))
        
        # Sort by value
        sorted_groups = sorted(groups.items())
        
        rank_row = [0] * m
        rank_col = [0] * n
        result = [[0] * n for _ in range(m)]
        
        for (val, _), positions in sorted_groups:
            max_rank = 0
            for i, j in positions:
                max_rank = max(max_rank, rank_row[i] + 1, rank_col[j] + 1)
            
            for i, j in positions:
                result[i][j] = max_rank
                rank_row[i] = max(rank_row[i], max_rank)
                rank_col[j] = max(rank_col[j], max_rank)
        
        return result