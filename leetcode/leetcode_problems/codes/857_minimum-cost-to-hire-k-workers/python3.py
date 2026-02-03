import heapq

class Solution:
    def mincostToHireWorkers(self, quality: List[int], wage: List[int], k: int) -> float:
        workers = sorted((w / q, q) for w, q in zip(wage, quality))
        heap = []
        sumq = 0
        result = float('inf')
        
        for ratio, q in workers:
            heapq.heappush(heap, -q)
            sumq += q
            if len(heap) > k:
                sumq += heapq.heappop(heap)
            if len(heap) == k:
                result = min(result, ratio * sumq)
        
        return result
