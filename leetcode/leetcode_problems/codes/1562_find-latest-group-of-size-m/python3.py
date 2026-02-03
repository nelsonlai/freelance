"""
Problem: Find Latest Group of Size M
Difficulty: Medium
Tags: array, string, tree, hash, search

Approach: Union-Find or track group sizes, count groups of size m
Time Complexity: O(n) where n is length of arr
Space Complexity: O(n) for parent and size arrays
"""

class Solution:
    def findLatestStep(self, arr: List[int], m: int) -> int:
        n = len(arr)
        parent = list(range(n + 1))
        size = [0] * (n + 1)
        count_m = 0
        result = -1
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            nonlocal count_m
            px, py = find(x), find(y)
            if px == py:
                return
            
            if size[px] == m:
                count_m -= 1
            if size[py] == m:
                count_m -= 1
            
            if size[px] < size[py]:
                px, py = py, px
            
            parent[py] = px
            size[px] += size[py]
            
            if size[px] == m:
                count_m += 1
        
        for step, pos in enumerate(arr, 1):
            size[pos] = 1
            if m == 1:
                count_m += 1
            
            if pos > 1 and size[pos - 1] > 0:
                union(pos, pos - 1)
            if pos < n and size[pos + 1] > 0:
                union(pos, pos + 1)
            
            if count_m > 0:
                result = step
        
        return result