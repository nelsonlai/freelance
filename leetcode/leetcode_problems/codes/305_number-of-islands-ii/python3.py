"""
Problem: Number of Islands II
Difficulty: Hard
Tags: array, graph, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def numIslands2(self, m: int, n: int, positions: List[List[int]]) -> List[int]:
        parent = {}
        rank = {}
        count = 0
        result = []
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            nonlocal count
            px, py = find(x), find(y)
            if px == py:
                return
            if rank[px] < rank[py]:
                px, py = py, px
            parent[py] = px
            if rank[px] == rank[py]:
                rank[px] += 1
            count -= 1
        
        for r, c in positions:
            pos = (r, c)
            if pos in parent:
                result.append(count)
                continue
            
            parent[pos] = pos
            rank[pos] = 0
            count += 1
            
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = r + dr, c + dc
                neighbor = (nr, nc)
                if 0 <= nr < m and 0 <= nc < n and neighbor in parent:
                    union(pos, neighbor)
            
            result.append(count)
        
        return result