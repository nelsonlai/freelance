import heapq

class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        heap = []
        i = 0
        result = 0
        fuel = startFuel
        
        while fuel < target:
            while i < len(stations) and stations[i][0] <= fuel:
                heapq.heappush(heap, -stations[i][1])
                i += 1
            
            if not heap:
                return -1
            
            fuel += -heapq.heappop(heap)
            result += 1
        
        return result
