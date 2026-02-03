"""
Problem: Most Stones Removed with Same Row or Column
Difficulty: Medium
Tags: array, graph, hash, search

Approach: Union-Find to group stones in same row/column, answer is total - number of groups
Time Complexity: O(n * α(n)) where α is inverse Ackermann function
Space Complexity: O(n) for Union-Find
"""

class Solution:
    def removeStones(self, stones: List[List[int]]) -> int:
        parent = {}
        
        def find(x):
            if x not in parent:
                parent[x] = x
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            parent[find(x)] = find(y)
        
        for i, j in stones:
            union(i, ~j)  # Use ~j to differentiate row and column
        
        return len(stones) - len({find(i) for i, j in stones})