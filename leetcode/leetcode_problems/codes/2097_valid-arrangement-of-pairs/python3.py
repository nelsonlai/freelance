"""
Problem: Valid Arrangement of Pairs
Difficulty: Hard
Tags: array, graph, Eulerian path, DFS

Approach: Find Eulerian path in directed graph using Hierholzer's algorithm
Time Complexity: O(n) where n is number of pairs
Space Complexity: O(n)
"""

from collections import defaultdict, deque

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(deque)
        in_degree = defaultdict(int)
        out_degree = defaultdict(int)
        
        for u, v in pairs:
            graph[u].append(v)
            out_degree[u] += 1
            in_degree[v] += 1
        
        # Find start node (node with out_degree > in_degree, or first node)
        start = pairs[0][0]
        for node in out_degree:
            if out_degree[node] > in_degree[node]:
                start = node
                break
        
        # Hierholzer's algorithm
        path = []
        stack = [start]
        
        while stack:
            node = stack[-1]
            if graph[node]:
                next_node = graph[node].popleft()
                stack.append(next_node)
            else:
                path.append(stack.pop())
        
        path.reverse()
        
        # Reconstruct pairs
        result = []
        for i in range(len(path) - 1):
            result.append([path[i], path[i + 1]])
        
        return result