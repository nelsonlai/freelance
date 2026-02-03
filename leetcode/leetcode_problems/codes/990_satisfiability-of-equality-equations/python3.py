"""
Problem: Satisfiability of Equality Equations
Difficulty: Medium
Tags: array, string, graph

Approach: Union-Find - first process all == equations, then check != equations
Time Complexity: O(n * α(26)) where n is number of equations
Space Complexity: O(1) for 26 letters
"""

class UnionFind:
    def __init__(self):
        self.parent = {chr(i): chr(i) for i in range(ord('a'), ord('z') + 1)}
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        self.parent[self.find(x)] = self.find(y)

class Solution:
    def equationsPossible(self, equations: List[str]) -> bool:
        uf = UnionFind()
        
        # Process all == equations first
        for eq in equations:
            if eq[1] == '=':
                uf.union(eq[0], eq[3])
        
        # Check all != equations
        for eq in equations:
            if eq[1] == '!':
                if uf.find(eq[0]) == uf.find(eq[3]):
                    return False
        
        return True