"""
Problem: Find All Groups of Farmland
Difficulty: Medium
Tags: array, search, DFS/BFS

Approach: Find top-left corner, expand to find bottom-right corner
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(1)
"""

class Solution:
    def findFarmland(self, land: List[List[int]]) -> List[List[int]]:
        m, n = len(land), len(land[0])
        result = []
        
        for i in range(m):
            for j in range(n):
                if land[i][j] == 1:
                    # Find top-left corner
                    if (i == 0 or land[i-1][j] == 0) and (j == 0 or land[i][j-1] == 0):
                        # Find bottom-right corner
                        r2, c2 = i, j
                        while r2 + 1 < m and land[r2+1][j] == 1:
                            r2 += 1
                        while c2 + 1 < n and land[i][c2+1] == 1:
                            c2 += 1
                        
                        result.append([i, j, r2, c2])
        
        return result