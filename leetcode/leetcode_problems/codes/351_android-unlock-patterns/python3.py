"""
Problem: Android Unlock Patterns
Difficulty: Medium
Tags: dp

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def numberOfPatterns(self, m: int, n: int) -> int:
        skip = {}
        skip[(1, 3)] = 2
        skip[(3, 1)] = 2
        skip[(1, 7)] = 4
        skip[(7, 1)] = 4
        skip[(3, 9)] = 6
        skip[(9, 3)] = 6
        skip[(7, 9)] = 8
        skip[(9, 7)] = 8
        skip[(1, 9)] = 5
        skip[(9, 1)] = 5
        skip[(2, 8)] = 5
        skip[(8, 2)] = 5
        skip[(3, 7)] = 5
        skip[(7, 3)] = 5
        skip[(4, 6)] = 5
        skip[(6, 4)] = 5
        
        def dfs(visited, last, length):
            if length >= m:
                self.count += 1
            if length == n:
                return
            
            for i in range(1, 10):
                if i in visited:
                    continue
                
                edge = (last, i)
                if edge in skip and skip[edge] not in visited:
                    continue
                
                visited.add(i)
                dfs(visited, i, length + 1)
                visited.remove(i)
        
        self.count = 0
        visited = set()
        
        for i in range(1, 10):
            visited.add(i)
            dfs(visited, i, 1)
            visited.remove(i)
        
        return self.count