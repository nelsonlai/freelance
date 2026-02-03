from collections import deque, defaultdict

class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        if source == target:
            return 0
        
        stopToRoutes = defaultdict(list)
        for i, route in enumerate(routes):
            for stop in route:
                stopToRoutes[stop].append(i)
        
        queue = deque([source])
        visited = set()
        buses = 0
        
        while queue:
            buses += 1
            for _ in range(len(queue)):
                stop = queue.popleft()
                for routeIdx in stopToRoutes[stop]:
                    if routeIdx not in visited:
                        visited.add(routeIdx)
                        for nextStop in routes[routeIdx]:
                            if nextStop == target:
                                return buses
                            queue.append(nextStop)
        
        return -1
