"""
Problem: Process Restricted Friend Requests
Difficulty: Hard
Tags: array, graph, union-find

Approach: Use Union-Find to track friend groups, check restrictions
Time Complexity: O(m * n) where m is requests, n is nodes
Space Complexity: O(n)
"""

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True

class Solution:
    def friendRequests(self, n: int, restrictions: List[List[int]], requests: List[List[int]]) -> List[bool]:
        uf = UnionFind(n)
        result = []
        
        for u, v in requests:
            pu, pv = uf.find(u), uf.find(v)
            
            # Check if they're already friends
            if pu == pv:
                result.append(True)
                continue
            
            # Check restrictions
            valid = True
            for res_u, res_v in restrictions:
                rpu = uf.find(res_u)
                rpv = uf.find(res_v)
                
                # Check if request would violate restriction
                if (pu == rpu and pv == rpv) or (pu == rpv and pv == rpu):
                    valid = False
                    break
            
            if valid:
                uf.union(u, v)
                result.append(True)
            else:
                result.append(False)
        
        return result