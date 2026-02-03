"""
Problem: Regions Cut By Slashes
Difficulty: Medium
Tags: array, string, graph, hash, search

Approach: Union-Find - divide each cell into 4 triangles, union based on slashes
Time Complexity: O(n^2 * α(n^2)) where n is grid size
Space Complexity: O(n^2) for Union-Find
"""

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.count = n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px != py:
            self.parent[px] = py
            self.count -= 1

class Solution:
    def regionsBySlashes(self, grid: List[str]) -> int:
        n = len(grid)
        uf = UnionFind(4 * n * n)
        
        for i in range(n):
            for j in range(n):
                idx = 4 * (i * n + j)
                char = grid[i][j]
                
                # Connect triangles within the cell
                if char == '/':
                    uf.union(idx + 0, idx + 3)
                    uf.union(idx + 1, idx + 2)
                elif char == '\\':
                    uf.union(idx + 0, idx + 1)
                    uf.union(idx + 2, idx + 3)
                else:  # ' '
                    uf.union(idx + 0, idx + 1)
                    uf.union(idx + 1, idx + 2)
                    uf.union(idx + 2, idx + 3)
                
                # Connect with adjacent cells
                if i > 0:  # Top
                    uf.union(idx + 0, idx - 4 * n + 2)
                if j > 0:  # Left
                    uf.union(idx + 3, idx - 4 + 1)
        
        return uf.count