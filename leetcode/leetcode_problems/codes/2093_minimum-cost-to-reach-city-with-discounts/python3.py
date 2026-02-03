"""
Problem: Minimum Cost to Reach City With Discounts
Difficulty: Medium
Tags: array, graph, Dijkstra, heap

Approach: Modified Dijkstra with state (city, remaining_discounts)
Time Complexity: O((n + m) * log(n * d)) where n is cities, m is highways, d is discounts
Space Complexity: O(n * d)
"""

import heapq
from collections import defaultdict

class Solution:
    def minimumCost(self, n: int, highways: List[List[int]], discounts: int) -> int:
        graph = defaultdict(list)
        for city1, city2, toll in highways:
            graph[city1].append((city2, toll))
            graph[city2].append((city1, toll))
        
        # dist[city][discounts_used] = minimum cost
        dist = {}
        heap = [(0, 0, discounts)]  # (cost, city, remaining_discounts)
        
        while heap:
            cost, city, remaining = heapq.heappop(heap)
            
            if city == n - 1:
                return cost
            
            if (city, remaining) in dist:
                continue
            dist[(city, remaining)] = cost
            
            for neighbor, toll in graph[city]:
                # Without discount
                new_cost = cost + toll
                if (neighbor, remaining) not in dist or dist.get((neighbor, remaining), float('inf')) > new_cost:
                    heapq.heappush(heap, (new_cost, neighbor, remaining))
                
                # With discount
                if remaining > 0:
                    new_cost = cost + toll // 2
                    if (neighbor, remaining - 1) not in dist or dist.get((neighbor, remaining - 1), float('inf')) > new_cost:
                        heapq.heappush(heap, (new_cost, neighbor, remaining - 1))
        
        return -1