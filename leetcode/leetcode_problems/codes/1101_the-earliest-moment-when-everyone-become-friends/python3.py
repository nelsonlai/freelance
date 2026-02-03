"""
Problem: The Earliest Moment When Everyone Become Friends
Difficulty: Medium
Tags: array, graph, sort

Approach: Union-Find - sort logs by time, union friends until all connected
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for Union-Find
"""

class Solution:
    def earliestAcq(self, logs: List[List[int]], n: int) -> int:
        logs.sort()
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
                return True
            return False
        
        components = n
        for time, x, y in logs:
            if union(x, y):
                components -= 1
                if components == 1:
                    return time
        
        return -1