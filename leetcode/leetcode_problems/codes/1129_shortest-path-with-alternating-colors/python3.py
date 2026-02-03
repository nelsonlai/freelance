"""
Problem: Shortest Path with Alternating Colors
Difficulty: Medium
Tags: array, graph, search

Approach: BFS with state (node, last_color) - alternate between red and blue edges
Time Complexity: O(V + E) where V is number of nodes, E is number of edges
Space Complexity: O(V + E) for graph and queue
"""

class Solution:
    def shortestAlternatingPaths(self, n: int, redEdges: List[List[int]], blueEdges: List[List[int]]) -> List[int]:
        from collections import deque, defaultdict
        
        # Build graph: graph[node][color] = list of neighbors
        graph = defaultdict(lambda: defaultdict(list))
        for u, v in redEdges:
            graph[u]['red'].append(v)
        for u, v in blueEdges:
            graph[u]['blue'].append(v)
        
        result = [-1] * n
        result[0] = 0
        
        # BFS: (node, last_color, distance)
        queue = deque([(0, 'red', 0), (0, 'blue', 0)])
        visited = set()
        
        while queue:
            node, last_color, dist = queue.popleft()
            
            if (node, last_color) in visited:
                continue
            visited.add((node, last_color))
            
            next_color = 'blue' if last_color == 'red' else 'red'
            for neighbor in graph[node][next_color]:
                if (neighbor, next_color) not in visited:
                    if result[neighbor] == -1:
                        result[neighbor] = dist + 1
                    queue.append((neighbor, next_color, dist + 1))
        
        return result