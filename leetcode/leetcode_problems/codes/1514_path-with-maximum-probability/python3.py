"""
Problem: Path with Maximum Probability
Difficulty: Medium
Tags: array, graph, queue, heap

Approach: Dijkstra's algorithm - find maximum probability path (use negative log for max heap)
Time Complexity: O((V + E) log V) where V is nodes, E is edges
Space Complexity: O(V + E) for graph
"""

import heapq
from collections import defaultdict

class Solution:
    def maxProbability(self, n: int, edges: List[List[int]], succProb: List[float], start_node: int, end_node: int) -> float:
        graph = defaultdict(list)
        for (u, v), prob in zip(edges, succProb):
            graph[u].append((v, prob))
            graph[v].append((u, prob))
        
        max_prob = [0.0] * n
        max_prob[start_node] = 1.0
        
        heap = [(-1.0, start_node)]
        
        while heap:
            neg_prob, node = heapq.heappop(heap)
            current_prob = -neg_prob
            
            if node == end_node:
                return current_prob
            
            if current_prob < max_prob[node]:
                continue
            
            for neighbor, edge_prob in graph[node]:
                new_prob = current_prob * edge_prob
                if new_prob > max_prob[neighbor]:
                    max_prob[neighbor] = new_prob
                    heapq.heappush(heap, (-new_prob, neighbor))
        
        return 0.0