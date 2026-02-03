"""
Problem: Lexicographically Smallest Equivalent String
Difficulty: Medium
Tags: string, graph, sort

Approach: Union-Find to group equivalent characters, assign smallest in each group
Time Complexity: O(n * α(n)) where α is inverse Ackermann
Space Complexity: O(1) for 26 characters
"""

class Solution:
    def smallestEquivalentString(self, s1: str, s2: str, baseStr: str) -> str:
        parent = list(range(26))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px < py:
                parent[py] = px
            else:
                parent[px] = py
        
        for c1, c2 in zip(s1, s2):
            union(ord(c1) - ord('a'), ord(c2) - ord('a'))
        
        result = []
        for char in baseStr:
            result.append(chr(find(ord(char) - ord('a')) + ord('a')))
        
        return ''.join(result)