"""
Problem: Count Ways to Build Rooms in an Ant Colony
Difficulty: Hard
Tags: array, tree, graph, dp, math, combinatorics

Approach: Tree DP with combinatorics - count ways to order children
Time Complexity: O(n) where n is rooms
Space Complexity: O(n)
"""

from collections import defaultdict
import math

class Solution:
    def waysToBuildRooms(self, prevRoom: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(prevRoom)
        graph = defaultdict(list)
        
        for i in range(1, n):
            graph[prevRoom[i]].append(i)
        
        def dfs(node):
            total_size = 1
            ways = 1
            
            children_sizes = []
            for child in graph[node]:
                child_size, child_ways = dfs(child)
                children_sizes.append((child_size, child_ways))
                total_size += child_size
            
            # Calculate ways to interleave children
            remaining = total_size - 1
            for child_size, child_ways in children_sizes:
                ways = (ways * math.comb(remaining, child_size) % MOD * child_ways) % MOD
                remaining -= child_size
            
            return total_size, ways
        
        _, result = dfs(0)
        return result