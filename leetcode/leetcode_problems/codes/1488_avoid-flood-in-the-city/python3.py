"""
Problem: Avoid Flood in The City
Difficulty: Medium
Tags: array, greedy, hash, search, queue, heap

Approach: Track full lakes, use heap to find earliest dry day to empty lake
Time Complexity: O(n log n) where n is length of rains
Space Complexity: O(n) for heap and full_lakes
"""

import heapq

class Solution:
    def avoidFlood(self, rains: List[int]) -> List[int]:
        result = [-1] * len(rains)
        full_lakes = {}
        dry_days = []
        
        for i, lake in enumerate(rains):
            if lake == 0:
                heapq.heappush(dry_days, i)
            else:
                if lake in full_lakes:
                    if not dry_days:
                        return []
                    dry_day = heapq.heappop(dry_days)
                    if dry_day < full_lakes[lake]:
                        return []
                    result[dry_day] = lake
                full_lakes[lake] = i
        
        while dry_days:
            result[heapq.heappop(dry_days)] = 1
        
        return result