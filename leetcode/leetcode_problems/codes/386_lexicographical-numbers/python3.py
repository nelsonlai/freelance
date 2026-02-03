"""
Problem: Lexicographical Numbers
Difficulty: Medium
Tags: graph, sort, search

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def lexicalOrder(self, n: int) -> List[int]:
        result = []
        
        def dfs(current):
            if current > n:
                return
            result.append(current)
            for i in range(10):
                next_num = current * 10 + i
                if next_num > n:
                    return
                dfs(next_num)
        
        for i in range(1, 10):
            dfs(i)
        
        return result