import heapq
from collections import defaultdict

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        graph = defaultdict(list)
        for u, v, w in flights:
            graph[u].append((v, w))
        
        heap = [(0, src, k + 1)]
        visited = {}
        
        while heap:
            cost, node, stops = heapq.heappop(heap)
            if node == dst:
                return cost
            
            if stops > 0:
                for neighbor, weight in graph[node]:
                    newCost = cost + weight
                    if neighbor not in visited or visited[neighbor] < stops - 1:
                        visited[neighbor] = stops - 1
                        heapq.heappush(heap, (newCost, neighbor, stops - 1))
        
        return -1
