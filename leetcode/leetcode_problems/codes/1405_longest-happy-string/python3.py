"""
Problem: Longest Happy String
Difficulty: Medium
Tags: string, tree, greedy, queue, heap

Approach: Greedy - use heap to always pick most frequent char (if can't use same twice)
Time Complexity: O(n log 3) where n is total characters
Space Complexity: O(n) for result
"""

import heapq

class Solution:
    def longestDiverseString(self, a: int, b: int, c: int) -> str:
        heap = []
        if a > 0:
            heapq.heappush(heap, (-a, 'a'))
        if b > 0:
            heapq.heappush(heap, (-b, 'b'))
        if c > 0:
            heapq.heappush(heap, (-c, 'c'))
        
        result = []
        
        while heap:
            count1, char1 = heapq.heappop(heap)
            count1 = -count1
            
            if len(result) >= 2 and result[-1] == result[-2] == char1:
                if not heap:
                    break
                count2, char2 = heapq.heappop(heap)
                count2 = -count2
                result.append(char2)
                count2 -= 1
                if count2 > 0:
                    heapq.heappush(heap, (-count2, char2))
                heapq.heappush(heap, (-count1, char1))
            else:
                result.append(char1)
                count1 -= 1
                if count1 > 0:
                    heapq.heappush(heap, (-count1, char1))
        
        return ''.join(result)