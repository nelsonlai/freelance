"""
Problem: Smallest String With Swaps
Difficulty: Medium
Tags: array, string, graph, hash, sort, search

Approach: Union-Find to group connected indices, sort characters in each group
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for Union-Find and groups
"""

class Solution:
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
        n = len(s)
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        for u, v in pairs:
            union(u, v)
        
        groups = {}
        for i in range(n):
            root = find(i)
            if root not in groups:
                groups[root] = []
            groups[root].append(i)
        
        result = list(s)
        for indices in groups.values():
            chars = sorted([s[i] for i in indices])
            for idx, char in zip(sorted(indices), chars):
                result[idx] = char
        
        return ''.join(result)