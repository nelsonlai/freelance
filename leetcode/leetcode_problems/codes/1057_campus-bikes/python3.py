"""
Problem: Campus Bikes
Difficulty: Medium
Tags: array, sort, queue, heap

Approach: Sort all worker-bike pairs by distance, assign greedily
Time Complexity: O(n * m * log(n * m)) where n is workers, m is bikes
Space Complexity: O(n * m) for pairs
"""

class Solution:
    def assignBikes(self, workers: List[List[int]], bikes: List[List[int]]) -> List[int]:
        def manhattan(p1, p2):
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
        
        pairs = []
        for i, worker in enumerate(workers):
            for j, bike in enumerate(bikes):
                pairs.append((manhattan(worker, bike), i, j))
        
        pairs.sort()
        assigned_workers = set()
        assigned_bikes = set()
        result = [0] * len(workers)
        
        for dist, worker, bike in pairs:
            if worker not in assigned_workers and bike not in assigned_bikes:
                result[worker] = bike
                assigned_workers.add(worker)
                assigned_bikes.add(bike)
        
        return result