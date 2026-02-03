"""
Problem: Closest Room
Difficulty: Hard
Tags: array, sort, search, binary search

Approach: Sort queries by size descending, use sorted list for room IDs
Time Complexity: O(n log n + q log q) where n is rooms, q is queries
Space Complexity: O(n)
"""

import bisect

class Solution:
    def closestRoom(self, rooms: List[List[int]], queries: List[List[int]]) -> List[int]:
        queries = [(minSize, preferred, i) for i, (preferred, minSize) in enumerate(queries)]
        queries.sort(reverse=True)
        
        rooms.sort(key=lambda x: x[1], reverse=True)
        
        available_rooms = []
        result = [0] * len(queries)
        j = 0
        
        for minSize, preferred, idx in queries:
            while j < len(rooms) and rooms[j][1] >= minSize:
                bisect.insort(available_rooms, rooms[j][0])
                j += 1
            
            if not available_rooms:
                result[idx] = -1
            else:
                pos = bisect.bisect_left(available_rooms, preferred)
                candidates = []
                if pos < len(available_rooms):
                    candidates.append(available_rooms[pos])
                if pos > 0:
                    candidates.append(available_rooms[pos-1])
                result[idx] = min(candidates, key=lambda x: abs(x - preferred))
        
        return result