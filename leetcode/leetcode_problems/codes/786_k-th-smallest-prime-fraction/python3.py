import heapq

class Solution:
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:
        heap = []
        n = len(arr)
        
        for i in range(n):
            for j in range(i + 1, n):
                heapq.heappush(heap, (arr[i] / arr[j], arr[i], arr[j]))
        
        for _ in range(k - 1):
            heapq.heappop(heap)
        
        _, num, den = heapq.heappop(heap)
        return [num, den]
