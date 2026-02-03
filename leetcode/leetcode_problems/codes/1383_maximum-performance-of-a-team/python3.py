"""
Problem: Maximum Performance of a Team
Difficulty: Hard
Tags: array, greedy, sort, queue, heap

Approach: Sort by efficiency descending, use min heap to track top k speeds
Time Complexity: O(n log n) for sorting
Space Complexity: O(k) for heap
"""

import heapq

class Solution:
    def maxPerformance(self, n: int, speed: List[int], efficiency: List[int], k: int) -> int:
        MOD = 10**9 + 7
        engineers = sorted(zip(efficiency, speed), reverse=True)
        heap = []
        total_speed = 0
        max_perf = 0
        
        for eff, spd in engineers:
            if len(heap) >= k:
                total_speed -= heapq.heappop(heap)
            
            heapq.heappush(heap, spd)
            total_speed += spd
            max_perf = max(max_perf, total_speed * eff)
        
        return max_perf % MOD