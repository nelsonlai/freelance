"""
Problem: Count Pairs Of Nodes
Difficulty: Hard
Tags: array, graph, hash, two pointers

Approach: Count incident edges per node, for each query count pairs with sum > query
Time Complexity: O(n^2 + q) where n is nodes, q is queries
Space Complexity: O(n + e) where e is edges
"""

from collections import Counter

class Solution:
    def countPairs(self, n: int, edges: List[List[int]], queries: List[int]) -> List[int]:
        degree = [0] * (n + 1)
        edge_count = Counter()
        
        for u, v in edges:
            degree[u] += 1
            degree[v] += 1
            edge_count[(min(u, v), max(u, v))] += 1
        
        sorted_degree = sorted(degree[1:])
        result = []
        
        for q in queries:
            count = 0
            left, right = 0, n - 1
            
            # Count pairs with degree sum > q
            while left < right:
                if sorted_degree[left] + sorted_degree[right] > q:
                    count += right - left
                    right -= 1
                else:
                    left += 1
            
            # Subtract pairs where edge count makes sum <= q
            for (u, v), cnt in edge_count.items():
                if degree[u] + degree[v] > q and degree[u] + degree[v] - cnt <= q:
                    count -= 1
            
            result.append(count)
        
        return result