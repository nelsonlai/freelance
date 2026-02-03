import heapq

class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        graph = defaultdict(list)
        for u, v, w in times:
            graph[u].append((v, w))
        
        dist = {i: float('inf') for i in range(1, n + 1)}
        dist[k] = 0
        heap = [(0, k)]
        
        while heap:
            d, node = heapq.heappop(heap)
            if d > dist[node]:
                continue
            for neighbor, weight in graph[node]:
                if dist[node] + weight < dist[neighbor]:
                    dist[neighbor] = dist[node] + weight
                    heapq.heappush(heap, (dist[neighbor], neighbor))
        
        maxDist = max(dist.values())
        return maxDist if maxDist != float('inf') else -1
