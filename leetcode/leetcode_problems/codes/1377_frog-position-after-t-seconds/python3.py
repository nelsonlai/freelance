"""
Problem: Frog Position After T Seconds
Difficulty: Hard
Tags: array, tree, graph, search

Approach: BFS/DFS to find path to target, calculate probability
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for graph and visited
"""

from collections import defaultdict, deque

class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        queue = deque([(1, 1.0, 0)])
        visited = {1}
        
        while queue:
            node, prob, time = queue.popleft()
            
            if node == target:
                if time == t or (time < t and len([c for c in graph[node] if c not in visited]) == 0):
                    return prob
                return 0.0
            
            if time >= t:
                continue
            
            children = [c for c in graph[node] if c not in visited]
            if not children:
                continue
            
            for child in children:
                visited.add(child)
                queue.append((child, prob / len(children), time + 1))
        
        return 0.0