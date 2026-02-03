"""
Problem: Tree of Coprimes
Difficulty: Hard
Tags: array, tree, graph, math, dfs

Approach: DFS - track path of values, for each node find nearest coprime ancestor
Time Complexity: O(n * 50) where 50 is max value range
Space Complexity: O(n)
"""

from collections import defaultdict
import math

class Solution:
    def getCoprimes(self, nums: List[int], edges: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        result = [-1] * len(nums)
        # path[val] = (node, depth) - track nearest node with each value
        path = {}
        
        def dfs(node, parent, depth):
            # Find nearest coprime ancestor
            best_node = -1
            best_depth = -1
            
            for val, (ancestor_node, ancestor_depth) in path.items():
                if math.gcd(nums[node], val) == 1:
                    if ancestor_depth > best_depth:
                        best_depth = ancestor_depth
                        best_node = ancestor_node
            
            result[node] = best_node
            
            # Add current node to path
            old_path = path.get(nums[node], None)
            path[nums[node]] = (node, depth)
            
            # DFS children
            for neighbor in graph[node]:
                if neighbor != parent:
                    dfs(neighbor, node, depth + 1)
            
            # Restore path
            if old_path:
                path[nums[node]] = old_path
            else:
                path.pop(nums[node], None)
        
        dfs(0, -1, 0)
        return result