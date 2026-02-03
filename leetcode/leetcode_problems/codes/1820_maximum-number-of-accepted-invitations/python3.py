"""
Problem: Maximum Number of Accepted Invitations
Difficulty: Medium
Tags: array, graph, search, bipartite matching

Approach: Bipartite matching using DFS (Hungarian algorithm)
Time Complexity: O(m * n * k) where m, n are dimensions, k is edges
Space Complexity: O(m + n)
"""

class Solution:
    def maximumInvitations(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        match = [-1] * n  # Which boy is matched to each girl
        
        def dfs(boy, seen):
            for girl in range(n):
                if grid[boy][girl] == 1 and not seen[girl]:
                    seen[girl] = True
                    if match[girl] == -1 or dfs(match[girl], seen):
                        match[girl] = boy
                        return True
            return False
        
        result = 0
        for boy in range(m):
            seen = [False] * n
            if dfs(boy, seen):
                result += 1
        
        return result