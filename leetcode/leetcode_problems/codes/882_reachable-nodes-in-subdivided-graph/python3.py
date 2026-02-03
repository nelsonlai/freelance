import heapq

class Solution:
    def reachableNodes(self, edges: List[List[int]], maxMoves: int, n: int) -> List[int]:
        graph = [[] for _ in range(n)]
        for u, v, w in edges:
            graph[u].append((v, w + 1))
            graph[v].append((u, w + 1))
        
        dist = [float('inf')] * n
        dist[0] = 0
        heap = [(0, 0)]
        
        while heap:
            d, node = heapq.heappop(heap)
            if d > dist[node]:
                continue
            for neighbor, weight in graph[node]:
                if dist[node] + weight < dist[neighbor]:
                    dist[neighbor] = dist[node] + weight
                    heapq.heappush(heap, (dist[neighbor], neighbor))
        
        result = sum(1 for d in dist if d <= maxMoves)
        
        for u, v, w in edges:
            a = max(0, maxMoves - dist[u])
            b = max(0, maxMoves - dist[v])
            result += min(a + b, w)
        
        return result
