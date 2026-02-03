"""
Problem: Find the Town Judge
Difficulty: Easy
Tags: array, graph, hash

Approach: Count in-degree and out-degree - judge has in-degree n-1 and out-degree 0
Time Complexity: O(n + m) where m is trust length
Space Complexity: O(n)
"""

class Solution:
    def findJudge(self, n: int, trust: List[List[int]]) -> int:
        in_degree = [0] * (n + 1)
        out_degree = [0] * (n + 1)
        
        for a, b in trust:
            out_degree[a] += 1
            in_degree[b] += 1
        
        for i in range(1, n + 1):
            if in_degree[i] == n - 1 and out_degree[i] == 0:
                return i
        
        return -1